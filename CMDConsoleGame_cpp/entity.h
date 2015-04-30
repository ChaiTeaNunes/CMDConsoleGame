#pragma once

class Entity
{
public:
	Vector2 position;
	char icon, nextMove;
	int damaged, hp;

	Entity() : icon('?'), nextMove(0), hp(10), damaged(0) {}
	Entity(Vector2 position, char icon) : position(position), icon(icon), hp(10), damaged(0) {}

	bool isDead() {
		return damaged >= hp;
	}

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
