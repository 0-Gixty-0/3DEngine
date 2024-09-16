#pragma once
#include<vector>
#include "SDL2/SDL.h"
#include <cmath>
#include <iostream>

struct Vector3D {
	float x, y, z;
};

struct Edge {
	int a, b;
};

void rotate(Vector3D& point, float x = 1, float y = 1, float z = 1) {
	float rad = 0;
	float rotatedX = 0;
	float rotatedY = 0;
	float rotatedZ = 0;

	rad = x;
	rotatedY = std::cos(rad) * point.y - std::sin(rad) * point.z;
	rotatedZ = std::sin(rad) * point.y + std::cos(rad) * point.z;
	point.y = rotatedY;
	point.z = rotatedZ;

	rad = y;
	rotatedX = std::cos(rad) * point.x + std::sin(rad) * point.z;
	rotatedZ = -std::sin(rad) * point.x + std::cos(rad) * point.z;
	point.x = rotatedX;
	point.z = rotatedZ;

	rad = z;
	rotatedX = std::cos(rad) * point.x - std::sin(rad) * point.y;
	rotatedY = std::sin(rad) * point.x + std::cos(rad) * point.y;
	point.x = rotatedX;
	point.y = rotatedY;
}

class Polygon {
	std::vector<SDL_FPoint> points;
	std::vector<Vector3D> vertices;
	std::vector<Edge> edges;
	Vector3D centroid;
	std::string name;

	Vector3D calculateCentroid() {
		Vector3D c{ 0,0,0 };
		for (auto& vertex : vertices) {
			c.x += vertex.x;
			c.y += vertex.y;
			c.z += vertex.z;
		}
		c.x /= vertices.size();
		c.y /= vertices.size();
		c.z /= vertices.size();

		return c;
	}

	void addLine(float x1, float y1, float x2, float y2) {
		float dx = x2 - x1;
		float dy = y2 - y1;

		float length = std::sqrt(dx * dx + dy * dy);
		float angle = std::atan2(dy, dx);

		for (float i = 0; i < length; i++) {
			addPoint(
				x1 + std::cos(angle) * i,
				y1 + std::sin(angle) * i
			);
		}
	}

	void translateToScreenCenter() {
		int xTranslation = 320 - centroid.x;
		int yTranslation = 180 - centroid.y;

		for (auto& vertex : vertices) {
			vertex.x += xTranslation;
			vertex.y += yTranslation;
		}
	}

public:
	Polygon(std::string _name, std::vector<Vector3D> _vertices, std::vector<Edge> _edges) {
		name = _name;
		vertices = _vertices;
		edges = _edges;
		centroid = calculateCentroid();
		translateToScreenCenter();
		centroid = calculateCentroid();
	}

	void addPoint(float x, float y) {
		points.emplace_back(SDL_FPoint{ x, y });
	}

	void clearPoints() {
		points.clear();
	}

	void applyRotation() {
		for (auto& vertex : vertices) {
			vertex.x -= centroid.x;
			vertex.y -= centroid.y;
			vertex.z -= centroid.z;

			rotate(vertex, 0.02, 0.00, 0.04);

			vertex.x += centroid.x;
			vertex.y += centroid.y;
			vertex.z += centroid.z;
			addPoint(vertex.x, vertex.y);
		}
	}

	void drawLines() {
		for (auto& edge : edges) {
			addLine(vertices[edge.a].x, vertices[edge.a].y, vertices[edge.b].x, vertices[edge.b].y);
		}
	}

	std::vector<SDL_FPoint> getPoints() {
		return points;
	}

	std::string getName() {
		return name;
	}
};