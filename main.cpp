#include "screen.h"
#include <cmath>
#include <iostream>
#include "polygon.h"

int main(int argc, char* argv[]) {
	Screen screen;

	std::vector<Vector3D> cubeVertices{
		{100, 100, 100},
		{200, 100, 100},
		{200, 200, 100},
		{100, 200, 100},

		{100, 100, 200},
		{200, 100, 200},
		{200, 200, 200},
		{100, 200, 200}
	};

	std::vector<Edge> cubeEdges{
		{0, 4},
		{1, 5},
		{2, 6},
		{3, 7},

		{0, 1},
		{1, 2},
		{2, 3},
		{3, 0},

		{4, 5},
		{5, 6},
		{6, 7},
		{7, 4}
	};
	Polygon cube{ cubeVertices, cubeEdges };

	std::vector<Vector3D> pyramidVertices{
		{300, 200, 100},
		{300, 200, 200},
		{400, 200, 200},
		{400, 200, 100},

		{350, 100, 150}
	};

	std::vector<Edge> pyramidEdges{
		{0, 1},
		{1, 2},
		{2, 3},
		{3, 0},

		{0, 4},
		{1, 4},
		{2, 4},
		{3, 4}
	};

	Polygon pyramid{ pyramidVertices, pyramidEdges };

	screen.addPolygon(cube);
	screen.addPolygon(pyramid);

	while (true) {
		for (auto& polygon : screen.getPolygons()) {
			polygon.applyRotation();
			polygon.drawLines();
		}

		screen.showPolygons();
		screen.clearPolygonPoints();
		screen.input();

		SDL_Delay(30);
	}
}