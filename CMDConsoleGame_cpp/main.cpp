#include "game.h"

#define USING_GAME_CODE
#include <iostream>
using namespace std;

void printArray(int * arr, int count) {
	cout << "{";
	for (int i = 0; i < count; ++i) {
		if (i > 0)
			cout << ", ";
		cout << arr[i];
	}
	cout << "}" << endl;
}


int main() {
//	int data[5];
	int * data;
	int count;
	cout << "How many numbers?" << endl;
	cin >> count;
	data = new int[count]; // allocates memory on the heap
	cout << "Enter " << count << " numbers: " << endl;
	for (int i = 0; i < count; ++i) {
		cin >> data[i];
	}
	printArray(data, count);
	// add up all of the numbers in the array 'data'

	//int total = data[0] + data[1] + data[2] + data[3] + data[4];
	int total = 0;
	for (int i = 0; i < count; ++i) {
		total += data[i];
	}
	cout << total << endl;
	// make the bigger list
	int * biggerData = new int[count + 5];
	// copy the old list
	for (int i = 0; i < count + 5; i++) {
		biggerData[i] = data[i];
	}
	// delete the old list
	delete [] data;
	// replace the old list with the new list
	data = biggerData;
	count = count + 5;
	// show the new bigger array
	printArray(data, count);

	delete [] data; // releases memory on the heap. otherwise this makes a memory leak

#ifdef USING_GAME_CODE ////////////////////////////////////////////////////////////////////// GAME CODE VVVVVVVV
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
#endif ////////////////////////////////////////////////////////////////////// GAME CODE ^^^^^^^^^^
	return 0;
}
