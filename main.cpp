#include "screen.h"
#include <cmath>
#include <iostream>
#include "polygon.h"

//void rotate(Vector3D& point, float x = 1, float y = 1, float z = 1) {
//	float rad = 0;
//	float rotatedX = 0;
//	float rotatedY = 0;
//	float rotatedZ = 0;
//
//	rad = x;
//	rotatedY = std::cos(rad) * point.y - std::sin(rad) * point.z;
//	rotatedZ = std::sin(rad) * point.y + std::cos(rad) * point.z;
//	point.y = rotatedY;
//	point.z = rotatedZ;
//
//	rad = y;
//	rotatedX = std::cos(rad) * point.x + std::sin(rad) * point.z;
//	rotatedZ = -std::sin(rad) * point.x + std::cos(rad) * point.z;
//	point.x = rotatedX;
//	point.z = rotatedZ;
//
//	rad = z;
//	rotatedX = std::cos(rad) * point.x - std::sin(rad) * point.y;
//	rotatedY = std::sin(rad) * point.x + std::cos(rad) * point.y;
//	point.x = rotatedX;
//	point.y = rotatedY;
//}

//void line(Screen& screen, float x1, float y1, float x2, float y2) {
//	float dx = x2 - x1;
//	float dy = y2 - y1;
//
//	float length = std::sqrt(dx * dx + dy * dy);
//	float angle = std::atan2(dy, dx);
//
//	for (float i = 0; i < length; i++) {
//		screen.pixel(
//			x1 + std::cos(angle) * i,
//			y1 + std::sin(angle) * i
//		);
//	}
//}

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

	screen.addPolygon(cube);

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