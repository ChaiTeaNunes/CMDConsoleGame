#pragma once

class Entity
{
public:
	Vector2 position;
	char icon;
	char nextMove;

	Entity() : icon('?'), nextMove(0) {}
	Entity(Vector2 position, char icon) : position(position), icon(icon) {}

	void Update(int msPassed)
	{
		switch (nextMove) {
		case 'w':	--position.y;	break;
		case 'a':	--position.x;	break;
		case 's':	++position.y;	break;
		case 'd':	++position.x;	break;
		}
	}
};
