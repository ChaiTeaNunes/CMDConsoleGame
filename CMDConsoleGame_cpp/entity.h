#pragma once

#include <functional>
#include "list.h"
using namespace std;

class Entity
{
public:

	struct BehaviorInfo {
		char icon;
		std::function<void(Entity*self, Entity*other)> whatToDo;
		BehaviorInfo(char icon, function<void(Entity*self, Entity*other)> what) : icon(icon), whatToDo(what) {}
		BehaviorInfo(){}
	};
	List<BehaviorInfo> behaviors;
	void addBehavior(char icon, function<void(Entity*self, Entity*other)> what) {
		behaviors.add(BehaviorInfo(icon, what));
	}
	void behave(char icon, Entity * other){
		for (int i = 0; i < behaviors.getSize(); ++i){
			if (behaviors[i].icon == icon) {
				behaviors[i].whatToDo(this, other);
			}
		}
	}

	Vector2 position;
	char icon, nextMove;
	int damaged, hp;

	Entity() : icon('?'), nextMove(0), hp(10), damaged(0) {}
	Entity(Vector2 position, char icon) : position(position), icon(icon), hp(10), damaged(0) {}

	bool isDead() {
		return damaged >= hp;
	}

	virtual void Update(int msPassed)
	{
		switch (nextMove) {
		case 'w':	--position.y;	break;
		case 'a':	--position.x;	break;
		case 's':	++position.y;	break;
		case 'd':	++position.x;	break;
		}
	}
};
