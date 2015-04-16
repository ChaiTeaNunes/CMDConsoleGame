#pragma once
#include "entity.h"
#include "vector2.h"

class Enemy : public Entity
{
public:
	int timer, moveDelay;
	/** pointer to the entity that is being followed */
	Entity * followed;

	/** automatically calls the Entity (parent class) default constructor */
	Enemy() : followed(0), timer(0), moveDelay(2000) {}

	/** explicitly calls the Entity (parent class) constructor */
	Enemy(Vector2 position, char icon, Entity * player, int delay)
		: Entity(position, icon), followed(player), timer(0), moveDelay(delay){}

	void Update(int msPassed)
	{
		timer += msPassed;
		if (timer >= moveDelay) {
			timer -= moveDelay;
			if (followed) {
				if (followed->position.y < position.y) nextMove = 'w';
				if (followed->position.x < position.x) nextMove = 'a';
				if (followed->position.y > position.y) nextMove = 's';
				if (followed->position.x > position.x) nextMove = 'd';
			}
			Entity::Update(msPassed);
		}
		else {
			nextMove = 0;
		}
	}
};
