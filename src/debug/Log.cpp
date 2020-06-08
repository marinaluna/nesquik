// Copyright (C) 2020 Marina Terry
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "Log.h"

#include <iostream>
#include <iomanip>

#include "../core/Cpu.h"


namespace Debug
{

	void LogInfo(const std::string& msg)
	{
		std::cout << YELLOW << "INFO: " << msg << NOCOLOR << std::endl;
	}

	void LogHex(const std::string& msg, int width, int num)
	{
		std::cout << YELLOW << msg << NOCOLOR << PRINTHEX(width) << std::uppercase << num << std::endl;
	}

	void LogError(const std::string& msg)
	{
		std::cout << RED << "ERROR: " << NOCOLOR << msg << std::endl;
	}

	void LogRegisters(const Registers& regs)
	{
		std::cout << CYAN << "Registers:"
		<< CYAN << "\nX: " << NOCOLOR << PRINTHEX(2) << std::uppercase << (int) regs.X
		<< CYAN << "\nY: " << NOCOLOR << PRINTHEX(2) << std::uppercase << (int) regs.Y
		<< CYAN << "\nA: " << NOCOLOR << PRINTHEX(2) << std::uppercase << (int) regs.A
		<< CYAN << "\nP: " << NOCOLOR << PRINTHEX(2) << std::uppercase << (int) regs.P
		<< CYAN << "\nSP: " << NOCOLOR << PRINTHEX(2) << std::uppercase << (int) regs.SP
		<< CYAN << "\nPC: " << NOCOLOR << PRINTHEX(4) << std::uppercase << (int) regs.PC << std::endl;
	}

	void LogMemory(u16 addr, int bytes, std::shared_ptr<Core::Bus>& bus)
	{
		std::vector<u8> mem;
		mem.resize(bytes);
		// Populate the vector with the bytes we want to print
		bus->readBytes(addr, mem, bytes);

		std::cout << YELLOW << "       00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F" << NOCOLOR << std::endl;
		// Get the number of rows, and add
		// a row if not evenly divisible by 16
		int rows = bytes / 16;
		if(bytes % 16 != 0) {
			rows++;
		}

		for(int row = 0; row < rows; row++) {
			int rowLen = 16;
			// If there is only one row or if we are on the last
			// row of a non-16-byte aligned chunk, then print
			// the last <= 16 bytes
			if((row == rows - 1) && (bytes % 16) != 0) {
				rowLen = bytes % 16;
			}
			if(rows == 1) {
				if(bytes == 16)
					rowLen = 16;
				else
					rowLen = bytes % 16;
			}

			// Print the address base
			std::cout << YELLOW << "0h" << PRINTHEX(4) << std::uppercase << addr + (row * 16) << NOCOLOR;
			// Print the row, one byte at a time
			for(int byte = 0; byte < rowLen; byte++) {
				std::cout << " " << PRINTHEX(2) << std::uppercase << (int) mem.at(byte + (row * 16));
			}
			std::cout << std::endl;
		}
	}

} // namespace Debug
