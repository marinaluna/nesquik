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
#include "Instructions.h"

#include "Cpu.h"
#include "Bus.h"


namespace Core {

void Cpu::ORA(u8 op) {
	regs.A |= op;
}

void Cpu::ADC(u8 op) {
	u16 total = regs.A + op + regs.P.C;
	regs.P.C = total & 0x100;
}

void Cpu::AND(u8 op) {
	regs.A &= op;
}

void Cpu::ASL(u16 opAddr) {
	switch(currentOpcode) {
		case 0x0A: {
			regs.P.C = regs.A & 0x80;
			regs.A <<= 1;
			break;
		}
		default: {
			u8 byte = bus->read8(opAddr);
			regs.P.C = byte & 0x80;
			byte <<= 1;
			bus->write8(opAddr, byte);
		}
	}
}

void Cpu::BCC() {
	// TODO
}

void Cpu::BRK() {
	// TODO: Enable interrupt
	regs.PC++;
}


void Cpu::doInstruction() {
	currentOpcode = fetch8();
	AddressingMode mode = instrs[currentOpcode].mode;
	u8 op;
	u16 opAddr;

	switch(mode) {
		case AddressingMode::Acc:
			break;
		case AddressingMode::Abs:
			opAddr = fetch16();
			op =  bus->read8(opAddr);
			break;
		case AddressingMode::AbsX:
			opAddr = fetch16() + regs.X;
			op =  bus->read8(opAddr);
			break;
		case AddressingMode::AbsY:
			opAddr = fetch16() + regs.Y;
			op = bus->read8(opAddr);
			break;
		case AddressingMode::Imm:
			op = fetch8();
			break;
		case AddressingMode::Impl:
			break;
		case AddressingMode::Ind:
			opAddr = bus->read16(fetch16());
			op =  bus->read8(opAddr);
			break;
		case AddressingMode::IndX:
			opAddr = (fetch8() + regs.X) & 0xFF;
			op =  bus->read8(opAddr);
			break;
		case AddressingMode::IndY:
			opAddr = (bus->read16(fetch8()) + regs.Y) & 0xFFFF;
			op =  bus->read8(opAddr);
			break;
		case AddressingMode::Rel:
			break; // Operand will be determined when running the instruction
		case AddressingMode::Zpg:
			opAddr = fetch8();
			op = bus->read8(opAddr);
			break;
		case AddressingMode::ZpgX:
			opAddr = (fetch8() + regs.X) & 0xFF;
			op = bus->read8(opAddr);
			break;
		case AddressingMode::ZpgY:
			opAddr = (fetch8() + regs.Y) & 0xFF;
			op = bus->read8(opAddr);
			break;
	}

	switch(currentOpcode) {
		case 0x01: case 0x05: case 0x09: case 0x0D:
		case 0x11: case 0x15: case 0x19: case 0x1D:
			ORA(op);
			break;

		case 0x69: case 0x65: case 0x75: case 0x6D:
		case 0x7D: case 0x79: case 0x61: case 0x71:
			ADC(op);
			break;
		case 0x29: case 0x25: case 0x35: case 0x2D:
		case 0x3D: case 0x39: case 0x21: case 0x31:
			AND(op);
			break;
		case 0x06: case 0x0A: case 0x0E: case 0x16:
		case 0x1E:
			ASL(opAddr);
			break;
		case 0x90:
			BCC();
			break;
	}
}

} // namespace Core
