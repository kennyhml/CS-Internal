#pragma once
#include <cstdint>
#include <Windows.h>

template <typename T>
class UtlVector {
public:
	UtlVector() : memory(nullptr), allocCount(0), growSize(0), size(0) {}

	~UtlVector() {
		if (memory) {
			delete[] memory;
		}
	}

	// Add a new element to the vector
	void push_back(const T& element) {
		if (size >= allocCount) {
			// The vector is full, allocate more memory.
			grow();
		}
		memory[size++] = element;
	}

	// Non-const indexing
	T& operator[](size_t index) {
		return memory[index];
	}

	// Const indexing
	const T& operator[](size_t index) const {
		return memory[index];
	}

	// Get the number of elements in the vector
	size_t getSize() const {
		return size;
	}

	// Clear all elements from the vector
	void clear() {
		size = 0;
	}

	void grow() {
		if (allocCount == 0) {
			allocCount = 4;  // Initial allocation size
		}
		else {
			allocCount *= 2; // Double the allocation size
		}

		T* newMemory = new T[allocCount];
		for (size_t i = 0; i < size; i++) {
			newMemory[i] = memory[i];
		}

		if (memory) {
			delete[] memory;
		}

		memory = newMemory;
	}

	T* memory;
	std::int32_t allocCount;
	std::int32_t growSize;
	size_t size;
};

class IRefCounted {
private:
	volatile long refCount;

public:
	virtual void destructor(char bDelete) = 0;
	virtual bool OnFinalRelease() = 0;

	void unreference() {
		if (InterlockedDecrement(&refCount) == 0 && OnFinalRelease()) {
			destructor(1);
		}
	}
};