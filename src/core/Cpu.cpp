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
#include "Cpu.h"

namespace Core
{

Cpu::Cpu(std::shared_ptr<Core::Bus>& _bus)
:	bus(_bus)
{}

void Cpu::reset()
{
	reg_P = STATUS_BREAKCMD | STATUS_DISABLEINT;
	reg_A = reg_X = reg_Y = 0x00;
	reg_SP = 0xFD;
	reg_PC = bus->read16(0xFFFC, MemorySpace::SYS);
}

void Cpu::run(int cycles)
{
	// TODO - cycle
}

} // namespace Core
