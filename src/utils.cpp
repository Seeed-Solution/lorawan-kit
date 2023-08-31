#include "utils.h"

int clean_serial(Stream &serial)
{
    while (serial.available()) {
        delay(2);
        // serial.println("Clearing Serial Incoming Buffer.");
        serial.read();
    }
    if (serial.read() == -1) {
        // serial.println("Incoming Buffer is Clear.");
        return 0;
    }
    return -1;
}

int ATCommand(SoftwareSerial *swSerial, const char *expected_response, int timeout, const char *command_format, const char *command_args)
{
    char send_buffer[256];
    char recv_buffer[256];

    snprintf(send_buffer, sizeof(send_buffer), command_format, command_args);

    LOGSS.print("<<<" + String(send_buffer));
    swSerial->print(send_buffer); // Send the command to the Wio-E5

    int index = 0;
    if (expected_response == NULL) {
        return 0;
    }

    LOGSS.print(">>>");
    uint32_t startMillis = millis();
    do {
        while (swSerial->available() > 0) {
            char ch = swSerial->read();
            if (index >= sizeof(recv_buffer) - 1) {
                LOGSS.println("recv_buff overflow");
                break;
            }
            recv_buffer[index++] = ch;
            LOGSS.print(ch);
            delay(3);
            if (strstr(recv_buffer, expected_response) != NULL) {
                LOGSS.println("\n");
                if (clean_serial(*swSerial) != ESP_OK)
                    continue;

                return 0;
            }
        }
    } while (millis() - startMillis < timeout);
    return -1;
}

void printHex(uint8_t *data, size_t len, String startLine, String endLine)
{
    PRINT(startLine);
    for (uint8_t i = 0; i < len; i++) {
        PRINTF("%02X,", data[i]);
    }
    PRINT(endLine);
}

void printHex(std::vector<uint8_t> &data, String startLine, String endLine)
{
    printHex(&data[0], data.size(), startLine, endLine);
}
