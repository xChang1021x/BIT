#ifndef PDU_H
#define PDU_H

#include <cstdint>
#include <vector>
#include <string>

// Constants
const int MAX_DATA_SIZE = 4096;
const uint8_t TYPE_DATA = 0;
const uint8_t TYPE_ACK = 1;
const uint8_t TYPE_LAST_DATA = 2;

// PDU Structure
struct PDU {
    uint8_t type;        // 0: data, 1: ACK, 2: last data
    uint32_t seqNum;     // Sequence number or ACK number
    uint16_t checksum;   // CRC-CCITT checksum
    char data[MAX_DATA_SIZE]; // Data payload (for data PDUs)
};

// CRC16-CCITT Calculation
uint16_t calculateCRC(const char* data, size_t length) {
    const uint16_t POLYNOMIAL = 0x1021;
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < length; ++i) {
        crc ^= (static_cast<uint16_t>(data[i]) << 8);
        for (int j = 0; j < 8; ++j) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ POLYNOMIAL;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

// Serialize PDU to buffer
std::vector<char> serializePDU(const PDU& pdu, size_t dataSize) {
    size_t totalSize = (pdu.type == TYPE_ACK) ? 7 : (7 + dataSize);
    std::vector<char> buffer(totalSize);
    buffer[0] = pdu.type;
    memcpy(&buffer[1], &pdu.seqNum, sizeof(pdu.seqNum));
    memcpy(&buffer[5], &pdu.checksum, sizeof(pdu.checksum));
    if (pdu.type == TYPE_DATA || pdu.type == TYPE_LAST_DATA) {
        memcpy(&buffer[7], pdu.data, dataSize);
    }
    return buffer;
}

// Deserialize buffer to PDU
PDU deserializePDU(const std::vector<char>& buffer, size_t dataSize) {
    PDU pdu{};
    pdu.type = static_cast<uint8_t>(buffer[0]);
    memcpy(&pdu.seqNum, &buffer[1], sizeof(pdu.seqNum));
    memcpy(&pdu.checksum, &buffer[5], sizeof(pdu.checksum));
    if (pdu.type == TYPE_DATA || pdu.type == TYPE_LAST_DATA) {
        memcpy(pdu.data, &buffer[7], dataSize);
    }
    return pdu;
}

#endif // PDU_H