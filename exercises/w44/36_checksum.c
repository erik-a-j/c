/**
 * @file exercise-36.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief The starter of Exercise 36.
 * @version 0.1
 * @date 2021-03-04
 *
 * @copyright Copyright (c) 2021
 *
 */

/*
Make a program to checksum a message and verify the checksummed message
using CRC according to the requirements below. 

The message is an N-element array of type uint8_t.
The minimum length of the message is 1 byte.
The maximum length of the message is 14 bytes.
The CRC-15 polynomial is 0xC599 (1100010110011001)
The message is processed from the first element to the last element in the array
Each element of the message is processed from the LSB to the MSB
Use the bitwise operators and avoid having magic numbers!
Download the exercise-36.c and complete the program.
-----------------------------------------------------
Cyclic Redundancy Check (CRC) is an error detection algorithm
which is used in transmitting data and storing data on
storage devices in order to check if data is corrupted or not.
In this technique blocks of data are entered to the system
and a checksum is calculated and appended to the original data.
The checksum is calculated as the remainder of the XOR division
of the data by a polynomial. It means that the data is divided
by a predefined polynomial and instead of subtraction, XOR is used.
The CRC and associated polynomial typically have a name of the form of CRC-N
and N is the number of the bits in the remainder of the division
which is appended to data and number of bits in the polynomial as the divisor is N + 1 bits.
For example, CRC-15 in CAN and CRC-32 in Ethernet communication protocols.
To calculate the CRC checksum of a message using CRC-N,
first we append N zeros to the message and then we should
do the xor division of the message with appended zeros by the polynomial as the divisor.
The remainder of such a division is the CRC checksum and we need to replace
the appended zeros with the calculated CRC checksum. Now if we transmit the result
or store it on a storage device, when we receive/read such data we can detect
if the data because of any reason has been altered or not.
To verify the health of the data we should again do the polynomial division
over the checksummed message using the same polynomial and if the remainder is zero,
it means that the data is healthy; otherwise, it is corrupted.

 

An example of CRC-3:

Message: 11010011101100
Polynomial: 1011
Checksummed message: 11010011101100100
*/

#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#define ARRAY_MAX_LEN 16U
#define POLYNOMIAL    0xC599U
#define MSB_ONE       ((uint16_t)0x8000U)
#define CRC_ERROR     ((uint16_t)0xFFFFU)

// Calculate the CRC
static uint16_t get_crc15(const uint8_t *data, uint8_t size) {
    uint16_t remainder = CRC_ERROR;

    if ((data != NULL) && (size > sizeof(remainder)) && (size <= ARRAY_MAX_LEN)) {
        remainder = 0;
        for (uint8_t i = 0; i < size; i++) {
            for (int8_t j = 0; j < CHAR_BIT; j++) {
                remainder <<= 1;
                remainder |= (data[i] >> j) & 1;
                if ((remainder & MSB_ONE) != 0) {
                    remainder ^= POLYNOMIAL;
                }
            }
        }
    }

    return remainder;
}

static uint8_t reverse_bits(uint8_t byte) {
    uint8_t reversed = 0;
    for (uint8_t i = 0; i < CHAR_BIT; i++) {
        reversed |= ((byte >> i) & 1) << (CHAR_BIT - 1 - i);
    }
    return reversed;
}

// Replace the padded zeros with the CRC accroding to the requirements.
static void checksum(uint8_t *data, uint8_t size, uint16_t crc) {
    if ((data != NULL) && (size > sizeof(crc)) && (size <= ARRAY_MAX_LEN)) {
        data[size - 2] = reverse_bits((uint8_t)(crc >> CHAR_BIT));
        data[size - 1] = reverse_bits((uint8_t)crc);
    }
}

int main(void) {
    uint8_t message[14] = {
        'H', 'e', 'l', 'l', 'o', ' ', 'W',
        'o', 'r', 'l', 'd', '!', 0,   0}; // Instead of 15 zeros, 16 zeros have been appended to the message.
                                          // We can assume that the MSB of message[12], which is a zero,
                                          // is a bit of the data.

    uint16_t crc = get_crc15(message, sizeof(message)); // Calculate the CRC.

    if (crc != CRC_ERROR) {
        (void)printf("The CRC of the message is: 0x%X\n",
                     crc); // For example the CRCs of "Hello World!" is 0xB35 and "AB" is 0x54FB

        checksum(message, sizeof(message), crc);

        if (0 == get_crc15(message, sizeof(message))) {
            (void)printf("The data is OK\n");
        } else {
            (void)printf("The data is not OK\n");
        }

        message[1] = 'a';

        if (0 == get_crc15(message, sizeof(message))) {
            (void)printf("The data is OK\n");
        } else {
            (void)printf("The data is not OK\n");
        }
    } else {
        (void)printf("Invalid arguments!\n");
    }

    return 0;
}
