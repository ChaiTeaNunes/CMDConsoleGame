#pragma once

struct Vector2
{
	int x, y;
	// default constructor
	Vector2() : x(0), y(0) { }
	// parameterized constructor
	Vector2(int x, int y) : x(x), y(y) { }

	bool equals(int x, int y)
	{
		return this->x == x && this->y == y;
	}
};
