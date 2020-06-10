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
#include <vector>
#include <SDL2/SDL.h>

#include "../common/Common.h"


namespace Frontend {

class SDLContext
{
	// window size
	int width, height, scale;
	// sdl components
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* lcdTexture;
	SDL_Event event;
	// front buffer (the one that is drawn)
	Color* frontBuffer;

	bool running = true;

public:
	SDLContext(int _width, int _height, int _scale);
	~SDLContext();

	void stop() { running = false; }
	bool isRunning() { return running; }

	void update(std::vector<Color>& backBuffer);
	void pollEvents();
};

} // namespace Frontend
