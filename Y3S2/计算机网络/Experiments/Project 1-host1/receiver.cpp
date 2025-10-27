#include "pdu.h"
#include "utils.h"
#include <winsock2.h>
#include <vector>
#include <iostream>

void receiver(SOCKET sock, sockaddr_in remoteAddr, const Config& config, std::ofstream& logFile) {
    std::ofstream outFile(config.fileToReceive, std::ios::binary);
    if (!outFile) {
        std::cerr << "Cannot open file to receive: " << config.fileToReceive << std::endl;
        return;
    }

    uint32_t expectedSeqNum = 0;
    int recvCount = 1;
    bool done = false;

    while (!done) {
        char buffer[7 + MAX_DATA_SIZE];
        int len = recvfrom(sock, buffer, sizeof(buffer), 0, nullptr, nullptr);
        if (len >= 7) {
            PDU pdu = deserializePDU(std::vector<char>(buffer, buffer + len), config.dataSize);
            std::string crcData = std::string(1, pdu.type) + std::string(reinterpret_cast<char*>(&pdu.seqNum), 4) +
                                 ((pdu.type != TYPE_ACK) ? std::string(pdu.data, config.dataSize) : std::string());
            uint16_t computedChecksum = calculateCRC(crcData.c_str(), crcData.size());
            std::string status;

            if (computedChecksum != pdu.checksum) {
                status = "DataErr";
            } else if (pdu.seqNum != expectedSeqNum) {
                status = "NoErr";
            } else {
                status = "OK";
                outFile.write(pdu.data, config.dataSize);
                expectedSeqNum++;
                if (pdu.type == TYPE_LAST_DATA) done = true;
            }

            Logger logger("transfer.log");
            logger.log(std::to_string(recvCount++) + ", pdu_exp=" + std::to_string(expectedSeqNum) + ", pdu_recv=" +
           std::to_string(pdu.seqNum) + ", status=" + status);

            // Send ACK
            PDU ack{};
            ack.type = TYPE_ACK;
            ack.seqNum = expectedSeqNum - 1;
            std::string ackCrcData = std::string(1, ack.type) + std::string(reinterpret_cast<char*>(&ack.seqNum), 4);
            ack.checksum = calculateCRC(ackCrcData.c_str(), ackCrcData.size());
            std::vector<char> ackBuffer = serializePDU(ack, 0);
            sendto(sock, ackBuffer.data(), ackBuffer.size(), 0, (sockaddr*)&remoteAddr, sizeof(remoteAddr));
        }
    }
    outFile.close();
}