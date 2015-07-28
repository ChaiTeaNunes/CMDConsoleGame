#include "game.h"

#include <iostream>

using namespace std;

#include "platform_conio.h"

#include "List.h"
#include "map2d.h"

int main() {
	char map[ 50 * 15 + 1 ] = // +1 for the null terminator
		"##################################################"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"##################################################";
	Map2D mapTest;
	mapTest.SetSize(Vector2(50, 15));
	mapTest.SetData(map);
	mapTest.Draw();
	platform_getch();
	Game g(map, Vector2(50, 15));
	long long lastKnownTime = platform_upTimeMS(), now, msPassed;
	while (g.running) {
		g.draw(); // display the game state
		g.throttleCode(5);
		g.getUserInput();
		now = platform_upTimeMS();
		msPassed = now - lastKnownTime;
		g.update((int)msPassed);
		lastKnownTime = now;
		printf("%d   ", msPassed);
	}
	return 0;
}