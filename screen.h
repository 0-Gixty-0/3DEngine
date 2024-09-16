#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include "polygon.h"
#include <iostream>

class Screen {
	SDL_Event event;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<Polygon> polygons;
	int activePolygonIndex;
	TTF_Font* font;

public:
	Screen() {
		SDL_Init(SDL_INIT_VIDEO);

		if (TTF_Init() == -1) {
			std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
			exit(1);
		}

		SDL_CreateWindowAndRenderer(640*2, 360*2, 0, &window, &renderer);
		SDL_RenderSetScale(renderer, 2, 2);
		activePolygonIndex = 0;

		// Load a font
		font = TTF_OpenFont("font/Roboto-Regular.ttf", 24); // Specify your font path and size
		if (font == nullptr) {
			std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
			exit(1);
		}
	}

	void showText(const std::string& text, SDL_Color color) {
		// Render text to a surface using TTF_RenderUTF8_Solid
		SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
		if (textSurface == nullptr) {
			std::cerr << "TTF_RenderUTF8_Solid Error: " << TTF_GetError() << std::endl;
			return;
		}

		// Convert the surface to a texture
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);
		if (textTexture == nullptr) {
			std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
			return;
		}

		// Get the width and height of the texture for positioning
		int textWidth, textHeight;
		SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

		// Create a destination rectangle for the text
		SDL_Rect dstRect = { 320 - (textWidth/2), (textHeight/2), textWidth, textHeight};

		// Render the text to the screen
		SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);

		// Clean up the texture
		SDL_DestroyTexture(textTexture);
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

		showText(polygons[activePolygonIndex].getName(), {255, 255, 255, 255});

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