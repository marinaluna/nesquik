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
#include <thread>
#include "SDL2/SDL.h"

#include "NES.h"
#include "common/Common.h"
#include "frontend/SDLContext.h"


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

	if(argc < 2)
	{
		std::cout << "Not enough arguments! Aborting!" << std::endl;
		return -1;
	}
	if(!readFileToVector(argv[1], rom))
	{
		std::cout << "Rom failed to load! Aborting!" << std::endl;
		return -1;
	} else {

		std::cout << "Rom loaded!" << std::endl;


		int width = 640;
		int height = 480;
		
		NES* nes = new NES(rom);
		if(!nes->boot())
			nes->stop();

		Frontend::SDLContext* context = new Frontend::SDLContext(width, height, 1);


		//////////////////////////////
		////// Test backBuffer ///////
		//////////////////////////////
		std::vector<Color> backBuffer;
		backBuffer.resize(width*height);
		for(int i = 0; i < width*height; i++) {
			backBuffer.at(i) = 0x00FF00FF;
		}


		bool updateFrame;
		bool pollEvents;
		// Start SDL thread
		std::thread sdlThread([nes, context, &updateFrame, &pollEvents, &backBuffer](){
			while(nes->isRunning() && context->isRunning())
			{
				if(updateFrame) {
					context->update(backBuffer);
					updateFrame = false;
					pollEvents = true;
				}
			}
		});
		// Start main thread
		{
			while(nes->isRunning() && context->isRunning())
			{
				nes->tick();
				updateFrame = true;

				if(pollEvents) {
					// For some reason you have to poll
					// events on the main thread
					context->pollEvents();
					pollEvents = false;
				}
			}
		}

		sdlThread.join();
		if(nes)
			delete nes;
		if(context)
			delete context;
	}

	return 0;
}
