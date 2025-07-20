#ifndef INC_STM32_UART_H_
#define INC_STM32_UART_H_

#include <Arduino.h>
#include <buffer.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define UART_PACKET_SIZE               64
#define UART_PACKET_HEADER_SIZE        6
#define UART_PACKET_CRC_SIZE           4
#define UART_PACKET_FRAME_SIZE         (UART_PACKET_HEADER_SIZE + UART_PACKET_CRC_SIZE)
#define UART_PACKET_DATA_MAX_SIZE      (UART_PACKET_SIZE - UART_PACKET_FRAME_SIZE)

#define UART_CMD_WIFI_TOGGLE           0x01
#define UART_CMD_WIFI_GET_SSID         0x02
#define UART_CMD_WIFI_SET_SSID         0x03
#define UART_CMD_WIFI_GET_PWD          0x04
#define UART_CMD_WIFI_SET_PWD          0x05

#define UART_CMD_CFG_READ              0x11
#define UART_CMD_CFG_WRITE             0x12
#define UART_CMD_CFG_SET_DATETIME      0x13

#define UART_CMD_DATA_SEND_LIVE        0x21
#define UART_CMD_DATA_SEND_RUN         0x22
#define UART_CMD_DATA_SEND_RUN_DETAILS 0x23

#define UART_CMD_HISTORY_PAGE          0x31
#define UART_CMD_HISTORY_STATISTICS    0x32
#define UART_CMD_HISTORY_DETAILS       0x33

#define UART_CMD_ACK                   0xFE
#define UART_CMD_ERR                   0xFF

typedef struct STM32_UART_Packet {
    uint32_t id;            // 4 byte
    uint8_t command;        // 1 byte
    uint8_t length;         // 1 byte, length of the body without the header and CRC
    uint8_t data[53];       // 0-53 byte, data to be sent, length is defined by the header minus the checksum length
    uint32_t crcReceived;   // 4 byte, CRC checksum of the headers + body minus the CRC itself
    uint32_t crcCalculated; // 4 byte, CRC checksum of the headers + body minus the CRC itself
} STM32_UART_Packet;

void STM32_initCommunication(void);
uint8_t STM32_sendData(STM32_UART_Packet * packet);
uint8_t STM32_receiveData(STM32_UART_Packet * packet);

#endif