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
#include <iostream>
#include <fstream>
#include <vector>

#include "NES.h"
#include "common/Common.h"


bool readFileToVector(std::string path, std::vector<u8>& vector)
{

	std::ifstream file_stream (path, std::ios::binary | std::ios::ate);
	if(file_stream.is_open())
	{
		unsigned int file_size = file_stream.tellg();
		file_stream.seekg(0, std::ios_base::beg);
		vector.resize(file_size);
		file_stream.read(reinterpret_cast<char*>(vector.data()), file_size);

		file_stream.close();

		return true;
	} else {

		std::cout << "Error opening file at path " << path << "!" << std::endl;

		return false;
	}
}

int main(int argc, char** argv)
{

	std::vector<u8> rom;

	if(!readFileToVector(argv[1], rom))
	{
		std::cout << "Rom failed to load! Aborting!" << std::endl;
		return -1;
	} else {

		std::cout << "Rom loaded!" << std::endl;

		NES* nes = new NES(rom);
		nes->start();
		// Main loop
		nes->tick();
	}
}
