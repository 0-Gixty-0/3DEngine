#pragma once

#include "SDL2/SDL.h"
#include <vector>
#include "polygon.h"
#include <iostream>

class Screen {
	SDL_Event event;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<Polygon> polygons;

public:
	Screen() {
		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer(640*2, 360*2, 0, &window, &renderer);
		SDL_RenderSetScale(renderer, 2, 2);
	}

	void addPolygon(Polygon &polygon) {
		polygons.emplace_back(polygon);
	}

	void showPolygons() {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		for (auto& polygon : polygons) {
			for (auto& point : polygon.getPoints()) {
				SDL_RenderDrawPointF(renderer, point.x, point.y);
			}
		}

		SDL_RenderPresent(renderer);
	}

	void clearPolygonPoints() {
		for (auto& poly : polygons) {
			poly.clearPoints();
		}
	}

	std::vector<Polygon>& getPolygons() {
		return polygons;
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