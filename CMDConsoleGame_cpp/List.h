#pragma once

template <typename TYPE>
class List {
private:
	TYPE * numbers;
	int size;
public:
	List() :numbers(nullptr), size(0){}
	int GetCount() { return size; }
	TYPE Get(int index) { return numbers[index]; }

	TYPE & operator [] (int index) { return numbers[index]; }

	void Set(int index, TYPE value) { numbers[index] = value; }
	void SetCount(int newSize) {
		TYPE * newnumbers = new TYPE[newSize];
		if (numbers != nullptr) {
			for (int i = 0; i < size && i < newSize; ++i) {
				newnumbers[i] = numbers[i];
			}
			// before losing track of numbers, we need to deallocate it
			delete[] numbers;
		}
		numbers = newnumbers;
		size = newSize;
	}
	void Add(TYPE value) {
		SetCount(GetCount() + 1);
		Set(GetCount() - 1, value);
	}
	void Insert(int index, TYPE value) {
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
		if (numbers != nullptr){
			delete[] numbers;
			numbers = nullptr;
			size = 0;
		}
	}
	~List() {
		Release();
	}
};