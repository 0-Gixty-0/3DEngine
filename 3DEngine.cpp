// Include SDL2 header file.
#include "SDL2/SDL.h"
#include <iostream>
#include "renderer3d.h"

Renderer3D::Renderer3D(SDL_Window* _window, SDL_Renderer* _renderer, std::vector<Point3D>& _points, std::vector<Edge>& _edges) {
	SDL_GetWindowSize(_window, &WindowSizeX, &WindowSizeY);
	renderer = _renderer;
	points = _points;
	edges = _edges;
}

int run(int argc, char* argv[]) {
	int screenWidth = 1280;
	int screenHeight = 720;

	// Initialize the SDL Video Subsystem. (Returns 0 on success)
	if (SDL_Init(SDL_INIT_VIDEO)) {
		// There was an error initializing SDL
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Could not initialize SDL: %s",
			SDL_GetError());
		return 3;
	}

	SDL_Window* window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_RESIZABLE);

	// If the window could not be created, log the error
	if (window == nullptr) {
		// There was an error initializing SDL
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Could not create window: %s",
			SDL_GetError());
		return 3;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// If the renderer could not be created, log the error
	if (renderer == nullptr) {
		// There was an error initializing SDL
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Could not create renderer: %s",
			SDL_GetError());
		return 3;
	}

	bool running{ true };

	while (running) {

		// Polling for SDL events
		SDL_Event event;

		// Loop until there are no more pending events to process.
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				running = false; // Stop running if the window is closed
			}
		}

		// Set render color to red
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);

		// Clear the renderer with the current render color
		SDL_RenderClear(renderer);

		// Set the render color to white
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0x00);

		SDL_RenderSetScale(renderer, 2, 2);

		SDL_RenderDrawLine(renderer, 20, 60, 40, 60);

		// Render everything to the screen
		SDL_RenderPresent(renderer);
	}

	// Cleanup SDL components and quit
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}