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
#include "SDLContext.h"

#include <stdexcept>
#include <string>


namespace Frontend
{

SDLContext::SDLContext(int _width, int _height, int _scale)
:	width(_width),
	height(_height),
	scale(_scale)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error("Error initializing frontend context! " + std::string(SDL_GetError()));
	}

	window = SDL_CreateWindow(	"nesquik NES Emulator",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								width*scale,
								height*scale,
								SDL_WINDOW_OPENGL);
	if(!window) {
		SDL_Quit();
		throw std::runtime_error("Error initializing window! " + std::string(SDL_GetError()));
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(!renderer) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		throw std::runtime_error("Error initializing renderer! " + std::string(SDL_GetError()));
	}

	lcdTexture = SDL_CreateTexture(	renderer,
									SDL_PIXELFORMAT_RGBA32,
									SDL_TEXTUREACCESS_STREAMING,
									width,
									height);

	if(!lcdTexture) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		throw std::runtime_error("Error initializing render texture! " + std::string(SDL_GetError()));
	}
}

SDLContext::~SDLContext()
{
	SDL_DestroyTexture(lcdTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void SDLContext::update(std::vector<Color>& backBuffer)
{
	int texturePitch;
	SDL_LockTexture(lcdTexture, NULL, reinterpret_cast<void**>(&frontBuffer), &texturePitch);
	memcpy((void*) frontBuffer, (void*) backBuffer.data(), width*height*sizeof(Color));
	SDL_UnlockTexture(lcdTexture);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, lcdTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void SDLContext::pollEvents()
{
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				stop();
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_q:
					case SDLK_ESCAPE:
						stop();
						break;
				}
				break;
		}
	}
}

} // namespace Frontend
