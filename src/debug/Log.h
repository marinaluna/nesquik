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
#pragma once
#include <string>
#include <memory>

#include "../core/Bus.h"
struct Registers;

// For colored text
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define NOCOLOR "\033[0m"

#define PRINTHEX(width) std::hex << std::setw(width) << std::setfill('0')


namespace Debug
{
	void LogInfo(const std::string& msg);
	void LogHex(const std::string& msg, int width, int num);
	void LogError(const std::string& msg);
	void LogRegisters(const Registers& regs);
	void LogMemory(u16 addr, int bytes, std::shared_ptr<Core::Bus>& bus);
} // namespace Debug
