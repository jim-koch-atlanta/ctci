#include <algorithm>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <string>
#include <sstream>

#include "../jim/bit-manipulation.h"

namespace ctci {
    namespace ch5 {
        /**
         * Draws a horizontal line on a "monochrome screen" from (x1, y) to (x2, y).
         * 
         * @param screen The "screen".
         * @param widthInBytes The width of the screen (in bits)
         * 
         * @return The result.
         */
        void drawLine(std::uint8_t* screen, std::uint8_t widthInBits, std::uint8_t x1, std::uint8_t x2, std::uint8_t y) {
            int startingBit = (widthInBits * y) + x1;
            int endingBit = (widthInBits * y) + x2;

            int startingByte = startingBit / 8;
            int endingByte = endingBit / 8;

            // If startingByte and endingByte are not the same, fill in the middle.
            for (int middleByte = startingByte + 1; middleByte < endingByte; middleByte++) {
                screen[middleByte] = 0xFF;                
            }

            // Fill the starting and ending bytes.
            if (startingByte != endingByte) {
                int startingBitInThatByte = startingBit % 8;
                for (int i = startingBitInThatByte; i < 8; i++) {
                    screen[startingByte] |= (0x80 >> i);
                }

                int endingBitInThatByte = endingBit % 8;
                for (int i = 0; i <= endingBitInThatByte; i++) {
                    screen[endingByte] |= (0x80 >> i);
                }
            } else {
                // Special case when the start and end of the line in the same byte.
                int startingBitInThatByte = startingBit % 8;
                int endingBitInThatByte = endingBit % 8;
                for (int i = startingBitInThatByte; i <= endingBitInThatByte; i++) {
                    screen[startingByte] |= (0x80 >> i);
                }
            }
        }

        int main(int argc, char** argv) {
            constexpr std::uint8_t widthInBits = 80;
            constexpr std::uint8_t heightInBits = 2;
            std::uint8_t screen1[(widthInBits / 8) * (heightInBits)] = { 0 };
            drawLine(screen1, widthInBits, 5, 75, 0);
            std::uint8_t expectedScreen1[(widthInBits / 8) * (heightInBits)] = 
                { 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
            if (!std::ranges::equal(screen1, expectedScreen1)) throw std::runtime_error("Test failed");

            std::uint8_t screen2[(widthInBits / 8) * (heightInBits)] = { 0 };
            drawLine(screen2, widthInBits, 5, 75, 1);
            std::uint8_t expectedScreen2[(widthInBits / 8) * (heightInBits)] = 
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                  0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0};
            if (!std::ranges::equal(screen2, expectedScreen2)) throw std::runtime_error("Test failed");

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch5::main(argc, argv);
}