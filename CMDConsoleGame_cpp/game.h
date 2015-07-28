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

	Entity player;
	static const int ENEMY_COUNT = 5;
	// Enemy enemies[ENEMY_COUNT];
	List<Enemy> enemies;
	Vector2 size;
	AABB playArea;
	bool running;

	Game(char * map, Vector2 size) : player(Vector2(4, 5), '@'), running(true), size(size),
		playArea(Vector2(0, 0), size), map(map) {
		enemies.setSize(ENEMY_COUNT);
		for (int i = 0; i < ENEMY_COUNT; ++i) {
			enemies[i] = Enemy(Vector2(i * 3 + 1, i * 2 + 1), 'a' + i, &player, 200 + (i * 200));
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

				for (int i = 0; i < enemies.getSize(); ++i) {

					enemyIsHere = enemies[i].position.equals(col, row);

					if (enemyIsHere) {
						putchar(enemies[i].icon);
						break;
					}
				}
				if (!enemyIsHere) {
					if (player.position.equals(col, row)) {
						putchar(player.icon);
					}
					else {
						putchar(map[mapIndex(row, col)]);
					}
				}
			}
			putchar('\n');
		}
		putchar('\n');
	}

	bool IsEmptyLocation(int row, int col, int whoToIgnore) {
		if (map[mapIndex(row, col)] == ' ') {
			bool somebodyHere = false;
			for (int i = 0; i < enemies.getSize(); i++) {
				if (i != whoToIgnore
				&& enemies[i].position.x == col
				&& enemies[i].position.y == row) {
					somebodyHere = true;
					break;
				}
			}
			return !somebodyHere;
		}
		return false;
	}

	void update(int msPassed)
	{
		while (userInput.getSize() > 0) {
			int input = userInput[0];
			userInput.removeAt(0);
			switch (input) {
			case 27:	running = false;
			case '\\':
				enemies.add(Enemy(Vector2(3, 3), enemies.getSize() + 'a', &player, 300 + ((enemies.getSize() * 100) % 2000)));
			default:
				player.nextMove = input;
				break;
			}
		}
		Vector2 oldPosition = player.position;
		player.Update(msPassed);
		// if the player is outside of the area
		if (!playArea.Contains(player.position)
		// OR the place that the player is in now is not an empty space
		|| map[ mapIndex(player.position.y, player.position.x) ] != ' ') {
			player.position = oldPosition;
		}
		// aaaand do the exact same thing for each enemy, so the enemies have boundaries
		for (int i = 0; i < enemies.getSize(); ++i) {
			oldPosition = enemies[i].position;
			enemies[i].Update(msPassed);
			// if the player is outside of the area
			if (!playArea.Contains(enemies[i].position)
				// OR the place that the player is in now is not an empty space
			|| !IsEmptyLocation(enemies[i].position.y, enemies[i].position.x, i)) {
				//|| map[mapIndex(enemies[i].position.y, enemies[i].position.x)] != ' ') {
				enemies[i].position = oldPosition;
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
