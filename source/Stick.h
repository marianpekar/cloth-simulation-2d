#pragma once

#include "Renderer.h"

class Point;
class Stick
{
private:
	Point& p0;
	Point& p1;
	float length;

	bool isActive = true;
	bool isSelected = false;

	Uint32 color = 0xFF0048E3;
	Uint32 colorWhenSelected = 0xFFCC0000;

public:
	Stick(Point& p0, Point& p1, float lenght);
	~Stick() = default;

	void SetIsSelected(bool value);

	void Update();
	void Draw(const Renderer* renderer) const;
	void Break();
};