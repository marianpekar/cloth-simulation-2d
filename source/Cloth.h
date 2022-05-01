#pragma once

#include <vector>
#include "Point.h"
#include "Stick.h"

class Cloth
{
private:
	Vec2 gravity = { 0.0f, 981.0f };
	float drag = 0.01f;
	float elasticity = 10.0f;

	std::vector<Point*> points;
	std::vector<Stick*> sticks;

public:
	Cloth() = default;
	Cloth(int width, int height, int spacing, int startX, int startY);
	~Cloth();

	void Update(Renderer* renderer, Mouse* mouse, float deltaTime);
	void Draw(Renderer* renderer) const;
};
