#include <math.h>
#include "Point.h"

Point::Point(float x, float y)
{
	pos = prevPos = initPos = Vec2(x, y);
}

void Point::AddStick(Stick* stick, int index)
{
	sticks[index] = stick;
}

void Point::SetPosition(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void Point::Pin()
{
	isPinned = true;
}

void Point::Update(float deltaTime, float drag, const Vec2& acceleration, float elasticity, Mouse* mouse, int windowWidth, int windowHeight)
{
	Vec2 cursorToPosDir = pos - mouse->GetPosition();
	float cursorToPosDist = cursorToPosDir.x * cursorToPosDir.x + cursorToPosDir.y * cursorToPosDir.y;
	float cursorSize = mouse->GetCursorSize();
	isSelected = cursorToPosDist < cursorSize * cursorSize;

	for (Stick* stick : sticks) 
	{
		if(stick != nullptr)
			stick->SetIsSelected(isSelected);
	}

	if(mouse->GetLeftButtonDown() && isSelected)
	{
		Vec2 difference = mouse->GetPosition() - mouse->GetPreviousPosition();

		if (difference.x > elasticity) difference.x = elasticity;
		if (difference.y > elasticity) difference.y = elasticity;
		if (difference.x < -elasticity) difference.x = -elasticity;
		if (difference.y < -elasticity) difference.y = -elasticity;

		prevPos = pos - difference;
	}

	if (mouse->GetRightMouseButton() && isSelected) 
	{
		for (Stick* stick : sticks)
		{
			if (stick != nullptr)
				stick->Break();
		}
	}

	if (isPinned) {
		pos = initPos;
		return;
	}

	Vec2 newPos = pos + (pos - prevPos) * (1.0f - drag) + acceleration * (1.0f - drag) * deltaTime * deltaTime;
	prevPos = pos;
	pos = newPos;

	KeepInsideView(windowWidth, windowHeight);
}

void Point::KeepInsideView(int windowWidth, int windowHeight)
{
	if (pos.x > windowWidth)
	{
		pos.x = windowWidth;
		prevPos.x = pos.x;
	}
	else if (pos.x < 0)
	{
		pos.x = 0;
		prevPos.x = pos.x;
	}

	if (pos.y > windowHeight)
	{
		pos.y = windowHeight;
		prevPos.y = pos.y;
	}
	else if (pos.y < 0)
	{
		pos.y = 0;
		prevPos.y = pos.y;
	}
}