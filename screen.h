#pragma once

#include "SDL2/SDL.h"
#include<vector>

class Screen {
	SDL_Event event;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<SDL_FPoint> points;

public:
	Screen() {
		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer(640*2, 360*2, 0, &window, &renderer);
		SDL_RenderSetScale(renderer, 2, 2);
	}

	void pixel(float x, float y) {
		points.emplace_back(SDL_FPoint{x, y});
	}

	void show() {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		for (auto& point : points) {
			SDL_RenderDrawPointF(renderer, point.x, point.y);
		}

		SDL_RenderPresent(renderer);
	}

	void clear() {
		points.clear();
	}

	void input() {
		// Loop until there are no more pending events to process.
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				SDL_Quit(); // Stop running if the window is closed
				exit(0);
			}
		}
	}
};