#pragma once

// Entity * ptr = new Entity;

#include "vector2.h"
#include "entity.h"
#include "enemy.h"
#include "platform_conio.h"
#include <stdio.h>
#include "aabb.h"
#include "List.h"

class Game
{
	List<int> userInput;
public:
	char * map;

	static const int ENEMY_COUNT = 5;
	Entity * player;
	List<Entity*> entities;
	Vector2 size;
	AABB playArea;
	bool running;

	Game(char * map, Vector2 size) : running(true), size(size), playArea(Vector2(0, 0), size), map(map) {
		entities.setSize(ENEMY_COUNT + 1);
		entities[0] = new Entity(Vector2(4, 5), '@');
		player = entities[0];
		for (int i = 1; i < entities.getSize(); ++i) {
			entities[i] = new Enemy(Vector2(i * 3 + 1, i * 2 + 1), 'a' + i, player, 200 + (i * 200));
		}
		player->addBehavior('f', [&](Entity * self, Entity * other) {
			printf("Oh no! %c defeats you!\n", other->icon);
			running = false;
		});
		player->addBehavior('e', [&](Entity * self, Entity * other) {
			printf("YOU WIN!");
			running = false;
		});
	}

	~Game() {
		for (int i = 0; i < entities.getSize(); ++i) {
			delete entities[i];
		}
	}

	int mapIndex(int row, int col) { 
		return row * size.x + col;
	}

	void draw() {

		platform_move(6, 0);

		for (int row = 0; row < size.y; ++row) {

			for (int col = 0; col < size.x; ++col) {

				bool enemyIsHere = false;

				for (int i = 0; i < entities.getSize(); ++i) {

					enemyIsHere = entities[i]->position.equals(col, row);

					if (enemyIsHere) {
						putchar(entities[i]->icon);
						break;
					}
				}
				if (!enemyIsHere) {
					putchar(map[mapIndex(row, col)]);
				}
			}
			putchar('\n');
		}
		putchar('\n');
	}

	int GetAtLocation(int row, int col, int whoToIgnore) {
		int somebodyHere = -1;
		if (map[mapIndex(row, col)] == ' ') {
			for (int i = 0; i < entities.getSize(); i++) {
				if (i != whoToIgnore
					&& entities[i]->position.x == col
					&& entities[i]->position.y == row) {
					somebodyHere = i;
					break;
				}
			}
		}
		return somebodyHere;
	}

	void update(int msPassed)
	{
		while (userInput.getSize() > 0) {
			int input = userInput[0];
			userInput.removeAt(0);
			switch (input) {
			case 27:	running = false;
			case '\\':
				entities.add(new Enemy(Vector2(3, 3), entities.getSize() + 'a', 
					player, 300 + ((entities.getSize() * 100) % 2000)));
			default:
				player->nextMove = input;
				break;
			}
		}
		// aaaand do the exact same thing for each enemy, so the enemies have boundaries
		for (int i = 0; i < entities.getSize(); ++i) {
			Vector2 oldPosition = entities[i]->position;
			entities[i]->Update(msPassed);
			int whoIsHere = -1;
			// if the player is outside of the area
			if (!playArea.Contains(entities[i]->position)
				// OR the place that the player is in now is not an empty space
				|| (whoIsHere = GetAtLocation(entities[i]->position.y, entities[i]->position.x, i)) != -1
				|| map[mapIndex(entities[i]->position.y, entities[i]->position.x)] != ' ') {
				entities[i]->position = oldPosition; 
				if (whoIsHere != -1){
//					printf("collision happening! %c and %c\n", entities[i]->icon, entities[whoIsHere]->icon);
					entities[i]->behave(entities[whoIsHere]->icon, entities[whoIsHere]);
				}
			}
		}

	}

	void getUserInput() {
		while (platform_kbhit()) {
			userInput.add(platform_getchar());
		}
	}

	void throttleCode(int msDelay) {
		long long now = platform_upTimeMS();
		while (!platform_kbhit() && platform_upTimeMS() < now + msDelay) {
			platform_sleep(1);
		}
	}
};
