#include "pdu.h"
#include "utils.h"
#include <winsock2.h>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>

struct SendStats {
    int totalPDUs = 0;
    int totalSends = 0;
    int timeoutCount = 0;
    int retransmitCount = 0;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point endTime;
};

void sender(SOCKET sock, sockaddr_in remoteAddr, const Config& config, std::ofstream& logFile) {
    SendStats stats;
    std::ifstream file(config.fileToSend, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file to send: " << config.fileToSend << std::endl;
        return;
    }

    // Calculate total PDUs
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    stats.totalPDUs = (fileSize + config.dataSize - 1) / config.dataSize;
    file.seekg(0, std::ios::beg);

    std::vector<PDU> pdus(stats.totalPDUs);
    for (int i = 0; i < stats.totalPDUs; ++i) {
        pdus[i].type = (i == stats.totalPDUs - 1) ? TYPE_LAST_DATA : TYPE_DATA;
        pdus[i].seqNum = i;
        file.read(pdus[i].data, config.dataSize);
        size_t bytesRead = file.gcount();
        std::string crcData = std::string(1, pdus[i].type) + std::string(reinterpret_cast<char*>(&pdus[i].seqNum), 4) + std::string(pdus[i].data, bytesRead);
        pdus[i].checksum = calculateCRC(crcData.c_str(), crcData.size());
    }
    file.close();

    uint32_t base = 0;
    uint32_t nextSeqNum = 0;
    std::vector<std::chrono::steady_clock::time_point> sendTimes(stats.totalPDUs);
    bool timerRunning = false;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    int sendCount = 1;

    stats.startTime = std::chrono::steady_clock::now();
    while (base < stats.totalPDUs) {
        // Send PDUs within window
        while (nextSeqNum < base + config.windowSize && nextSeqNum < stats.totalPDUs) {
            PDU& pdu = pdus[nextSeqNum];
            bool shouldSend = dis(gen) >= config.lossRate;
            if (shouldSend) {
                PDU sendPdu = pdu;
                if (dis(gen) < config.errorRate) {
                    sendPdu.data[0] ^= 0x01; // Flip a bit to simulate error
                }
                std::vector<char> buffer = serializePDU(sendPdu, config.dataSize);
                sendto(sock, buffer.data(), buffer.size(), 0, (sockaddr*)&remoteAddr, sizeof(remoteAddr));
                std::string status = (nextSeqNum >= base) ? "New" : "TO";
                stats.totalSends++;
                if (status == "TO") stats.retransmitCount++;
                Logger logger("transfer.log");
                logger.log(std::to_string(sendCount++) + ", pdu_to_send=" + std::to_string(nextSeqNum) + ", status=" + status + ", ackedNo=" + std::to_string(base));
            }
            if (base == nextSeqNum) {
                sendTimes[nextSeqNum] = std::chrono::steady_clock::now();
                timerRunning = true;
            }
            nextSeqNum++;
        }

        // Set timeout for select
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);
        timeval tv{};
        tv.tv_sec = 0;
        tv.tv_usec = timerRunning ? (config.timeout * 1000) : 0;
        int result = select(0, &readfds, nullptr, nullptr, timerRunning ? &tv : nullptr);

        if (result > 0) { // ACK received
            char buffer[7];
            int len = recvfrom(sock, buffer, sizeof(buffer), 0, nullptr, nullptr);
            if (len == 7) {
                PDU ack = deserializePDU(std::vector<char>(buffer, buffer + len), 0);
                std::string crcData = std::string(1, ack.type) + std::string(reinterpret_cast<char*>(&ack.seqNum), 4);
                if (ack.type == TYPE_ACK && calculateCRC(crcData.c_str(), crcData.size()) == ack.checksum && ack.seqNum >= base) {
                    base = ack.seqNum + 1;
                    timerRunning = (base < nextSeqNum);
                }
            }
        } else if (result == 0 && timerRunning) { // Timeout
            stats.timeoutCount++;
            nextSeqNum = base;
            timerRunning = false;
        }
    }
    stats.endTime = std::chrono::steady_clock::now();

    // Output statistics
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stats.endTime - stats.startTime).count();
    std::cout << "Total PDUs: " << stats.totalPDUs << "\nTotal Sends: " << stats.totalSends << "\nTimeouts: " << stats.timeoutCount
              << "\nRetransmissions: " << stats.retransmitCount << "\nTotal Time (ms): " << duration << std::endl;
    Logger logger("transfer.log");
    logger.log("Stats: TotalPDUs=" + std::to_string(stats.totalPDUs) + ", TotalSends=" + std::to_string(stats.totalSends) +
           ", Timeouts=" + std::to_string(stats.timeoutCount) + ", Retransmissions=" + std::to_string(stats.retransmitCount) +
           ", TotalTime=" + std::to_string(duration));
}