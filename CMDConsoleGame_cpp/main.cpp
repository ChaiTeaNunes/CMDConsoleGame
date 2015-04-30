#include "game.h"

#include <iostream>

using namespace std;

#include "platform_conio.h"

void draw(Game g, long long msPassed, long long now, long long lastKnownTime);

int main() {
	char map[ 50 * 15 + 1 ] = // +1 for the null terminator
		"##################################################"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                    #                           #"
		"#                                                #"
		"#                             QQ                 #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"#                                                #"
		"##################################################";
	Game g(map, Vector2(50, 15));
	long long lastKnownTime = platform_upTimeMS(), now, msPassed;
	while (g.running) {
		g.draw(); // display the game state
		g.throttleCode(20);
		g.getUserInput();
		now = platform_upTimeMS();
		msPassed = now - lastKnownTime;
		g.update((int)msPassed);
		lastKnownTime = now;
		printf("%d   ", msPassed);
	}
	return 0;
}

void draw(Game g, long long msPassed, long long now, long long lastKnownTime) {
	while (g.running) {
		g.draw(); // display the game state
		g.throttleCode(20);
		g.getUserInput();
		now = platform_upTimeMS();
		msPassed = now - lastKnownTime;
		g.update((int)msPassed);
		lastKnownTime = now;
		printf("%d   ", msPassed);
	}
}
