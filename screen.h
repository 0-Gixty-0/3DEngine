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
	int activePolygonIndex;

public:
	Screen() {
		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer(640*2, 360*2, 0, &window, &renderer);
		SDL_RenderSetScale(renderer, 2, 2);
		activePolygonIndex = 0;
	}

	void addPolygon(Polygon &polygon) {
		polygons.emplace_back(polygon);
	}

	void showPolygons() {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawPointF(renderer, 319, 180);
		SDL_RenderDrawPointF(renderer, 320, 180);
		SDL_RenderDrawPointF(renderer, 321, 180);
		SDL_RenderDrawPointF(renderer, 320, 181);
		SDL_RenderDrawPointF(renderer, 320, 179);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		for (auto& point : polygons[activePolygonIndex].getPoints()) {
			SDL_RenderDrawPointF(renderer, point.x, point.y);
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

	Polygon& getActivePolygon() {
		return polygons[activePolygonIndex];
	}

	void input() {
		// Loop until there are no more pending events to process.
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				SDL_Quit(); // Stop running if the window is closed
				exit(0);
			}
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_RIGHT) {
					if (activePolygonIndex < polygons.size() - 1) {
						activePolygonIndex += 1;
					}
					else {
						activePolygonIndex = 0;
					}
				} else if (event.key.keysym.sym == SDLK_LEFT) {
					if (activePolygonIndex > 0) {
						activePolygonIndex -= 1;
					}
					else {
						activePolygonIndex = polygons.size() - 1;
					}
				}
			}
		}
	}
};