#include "game.h"

#include <iostream>

using namespace std;

#include "platform_conio.h"

void draw(Game g, long long msPassed, long long now, long long lastKnownTime);

class List {
private:
	int * numbers;
	int size;
public:
	List():numbers(nullptr), size(0){}
	int GetCount() { return size; }
	int Get(int index) { return numbers[index]; }
	void Set(int index, int value) { numbers[index] = value; }
	void SetCount(int newSize) {
		int * newnumbers = new int[newSize];
		if(numbers != nullptr) {
			for(int i = 0; i < size && i < newSize; ++i) {
				newnumbers[i] = numbers[i];
			}
			// before losing track of numbers, we need to deallocate it
			delete [] numbers;
		}
		numbers = newnumbers;
		size = newSize;
	}
	void Add(int value) {
		SetCount(GetCount() + 1);
		Set(GetCount() -1, value);
	}
	void Insert(int index, int value) {
		SetCount(GetCount() + 1);
		for (int i = size - 1; i > index; i--) {
			Set(i, numbers[i - 1]);
		}
		Set(index, value);
	}
	void RemoveAt(int index) {
		for (int i = index; i < size; i++) {
			Set(i, numbers[i + 1]);
		}
		SetCount(GetCount() - 1);
	}
	void Release(){
		if(numbers != nullptr){
			delete [] numbers;
			numbers = nullptr;
			size = 0;
		}
	}
	~List() {
		Release();
	}
};

int main() {
	srand(time(0));
	int size = 3;
	//int * numbers = new int [size];
	//for(int i = 0; i < size; ++i) {
	//	numbers[i] = rand() % 50;
	//}
	//for(int i = 0; i < size; ++i) {
	//	cout << numbers[i] << endl;
	//}
	//cout << "the array with more numbers:" << endl;
	//// new code that increases the size of numbers
	//int * newnumbers = new int[size+1];
	//for(int i = 0; i < size; ++i) {
	//	newnumbers[i] = numbers[i];
	//}
	//newnumbers[size] = rand() % 50;
	//// before losing track of numbers, we need to deallocate it
	//delete [] numbers;

	//numbers = newnumbers;
	//for(int i = 0; i < size+1; ++i) {
	//	cout << numbers[i] << endl;
	//}
	List list;
	for(int i = 0; i < size; ++i)
	{
		list.Add(rand() % 50);
	}
	for(int i = 0; i < list.GetCount(); ++i) { cout << list.Get(i) << endl; }
	cout << "the array with more numbers:" << endl;
	list.Add(rand() % 50);
	for(int i = 0; i < list.GetCount(); ++i) { cout << list.Get(i) << endl; }
	list.Insert(2, 3);
	cout << endl;
	for (int i = 0; i < list.GetCount(); ++i) { cout << list.Get(i) << endl; }
	cout << endl;
	list.RemoveAt(2);
	for (int i = 0; i < list.GetCount(); ++i) { cout << list.Get(i) << endl; }
	platform_getch();
	return 0;
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
