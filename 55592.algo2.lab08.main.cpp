// ALGO2 IS1 214B LAB06
// Paweł Ewald
// ep55592@zut.edu.pl

#pragma once
#define DLIST
#ifdef DLIST

#include <iostream>
#include <string>
#include <sstream>

using namespace std;


template <typename T>
class Dlist
{
private:
	uint32_t size;
	uint32_t capacity;

	void swap(T& var1, T& var2);
	T* arr;
	

public:
	void resize();

	Dlist()	: size(0), capacity(1), arr(new T[capacity]) { std::fill(arr, arr + capacity, T()); }


	Dlist(uint32_t cap) : size(0), capacity(cap), arr(new T[cap]) {	std::fill(arr, arr + cap, T());	}


	// Copy constructor
	Dlist(const Dlist& other)
		: arr(new T[other.capacity]),
		size(other.size),
		capacity(other.capacity) 
	{
		for (size_t i = 0; i < size; ++i) 
			arr[i] = other.arr[i];
	}

	// Move constructor
	Dlist(Dlist&& other) noexcept
		: arr(other.arr),
		size(other.size),
		capacity(other.capacity) 
	{
		other.arr = nullptr;
		other.size = other.capacity = 0;
	}

	// Assignment operator
	Dlist& operator=(const Dlist& other) 
	{
		if (this != &other) 
		{
			delete[] arr;
			arr = new T[other.capacity];

			size = other.size;
			capacity = other.capacity;

			for (size_t i = 0; i < capacity; ++i) 
				arr[i] = other.arr[i];
		}
		return *this;
	}


	bool empty() const 
	{
		return size == 0;
	}


	T& front() 
	{
		if (empty()) 
			throw std::out_of_range("Array is empty");
		
		return arr[0];
	}

	T& back() 
	{
		if (empty()) 
			throw std::out_of_range("Array is empty");
		
		return arr[size - 1];
	}

	bool push(T data);
	bool push(T data, int index);

	T pop();
	T remove(int index);

	//T find(int index);
	bool edit(int atIndex, T toReplace);

	uint32_t getSize() { return size; }
	uint32_t getCapacity() { return capacity; }

	void display(const char* sep = ", ", uint32_t end = 0);
	
	std::string getAllData(std::string sep = ",", uint32_t end = 0);
	std::string dataString(T item);

	void sort(bool (*comp)(const T&, const T&) = nullptr);



	T& operator[](int index)
	{
		if (index < 0 || index > capacity)
			throw std::out_of_range("Index out of range!");
		return arr[index];
	}

	bool exist(uint32_t index) const 
	{
		if (index >= capacity) return false;
		return arr[index] != T();
	}
	~Dlist()
	{
		delete[]arr;
	}

};

template<typename T>
void Dlist<T>::resize()
{
	capacity *= 2;
	T* newArr = new T[capacity];
	for (int i = 0; i < size; i++)
	{
		newArr[i] = std::move(arr[i]);
	}

	delete[]arr;
	arr = newArr;
}

template<typename T>
void Dlist<T>::swap(T& var1, T& var2)
{
	T temp = var1;
	var1 = var2;
	var2 = temp;
}

template<typename T>
bool Dlist<T>::push(T data)
{
	return push(data, size);
}

template<typename T>
bool Dlist<T>::push(T data, int index)
{
	if (index < 0 || index > capacity)
	{
		return false;
	}

	if (size == capacity)
		resize();

	for (int i = size; i > index; --i)
	{
		arr[i] = std::move(arr[i - 1]);
	}

	arr[index] = data;
	size++;

	return true;
}

template<typename T>
T Dlist<T>::pop()
{
	if (size == 0)
		throw std::out_of_range("List is empty");

	return arr[--size];
}

template<typename T>
T Dlist<T>::remove(int index)
{
	if (index < 0 || index > size)
		throw std::out_of_range("Index out of range");
	
	T removed = arr[index];

	for (int i = index; i < size - 1; i++)
	{
		arr[i] = std::move(arr[i + 1]);
	}
	size--;
	return removed;
}

//template<typename T>
//T Dlist<T>::find(int index)
//{
//	if (index < 0 || index > size)
//		throw std::out_of_range("Index out of range");
//	return arr[index];
//}

template<typename T>
bool Dlist<T>::edit(int atIndex, T toReplace)
{
	if (atIndex < 0 || atIndex > size)
		throw std::out_of_range("Index out of range");

	arr[atIndex] = toReplace;

	return true;
}

template<typename T>
void Dlist<T>::display(const char* sep, uint32_t end)
{
	if (end == 0)
		end = size;
	std::cout << "[ ";
	std::cout << getAllData(sep, end);
	std::cout << " ]";
}

template <typename T>
std::string Dlist<T>::getAllData(std::string sep, uint32_t end)
{
	if (end == 0)
		end = size;
	std::stringstream listString;
	for (int i = 0; i < end; i++)
	{
		listString << arr[i];
		if (i != end - 1)
			listString << sep;
	}
	return listString.str();
}

template<typename T>
std::string Dlist<T>::dataString(T item)
{
	std::stringstream dataString;
	dataString << item;
	return dataString.str();
}

template<typename T>
void Dlist<T>::sort(bool (*comp)(const T&, const T&)) 
{
	int count = 0;
    for (int i = 0; i < size - 1; i++) 
	{
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) 
		{
            if (comp ? comp(arr[j + 1], arr[j]) : arr[j + 1] < arr[j]) 
			{
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}
#endif


#pragma once
#define BINARYHEAP
#ifdef BINARYHEAP


#include <iostream>
#include <sstream>

#include "Dlist.h"

template <typename T>
class BinaryHeap : Dlist<T>
{
private:
	Dlist<T> arr;

	uint32_t getParent(uint32_t childIndex) { return childIndex > 0 ? (childIndex - 1) / 2 : 0; }
	uint32_t getLeftChild(uint32_t parentIndex) { return parentIndex * 2 + 1; }
	uint32_t getRightChild(uint32_t parentIndex) { return parentIndex * 2 + 2; }

	bool hasLeftChild(uint32_t index) { return getLeftChild(index) < arr.getSize(); }
	bool hasRightChild(uint32_t index) { return getRightChild(index) < arr.getSize(); }
	bool hasParent(uint32_t index) { return getParent(index) >= 0; }

	T leftChild(uint16_t index) { return arr[getLeftChild(index)]; }
	T rightChild(uint16_t index) { return arr[getRightChild(index)]; }
	T parent(uint16_t index) { return arr[getParent(index)]; }

	bool isEmpty() { return arr.getSize() == 0; }
	bool isFull() { return arr.getSize() == arr.getCapacity(); }

	void swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}


public:

	BinaryHeap() : arr(10) {}


	T poll()
	{
		if (isEmpty()) throw std::out_of_range("List is empty");

		T data = arr[0];
		arr[0] = arr.pop();

		shiftDown(0);

		return data;
	}

	void insert(T data)
	{
		arr.push(data);
		
		shiftUp(arr.getSize() - 1);
	}
	
	void display()
	{
		arr.display();
	}

	std::string toString()
	{
		return arr.getAllData();
	}

	void shiftUp(uint32_t index)
	{
		uint32_t curr = index;
		uint32_t parent = getParent(index);

		if (arr[curr] <= arr[parent] || curr == 0) return;
		
		swap(arr[curr], arr[parent]);
		shiftUp(parent);
	}

	void shiftDown(uint32_t index)
	{
		uint32_t largest = index;
		uint32_t left = getLeftChild(index);
		uint32_t right = getRightChild(index);

		if (hasLeftChild(index) && arr[left] > arr[largest]) 
			largest = left;

		if (hasRightChild(index) && arr[right] > arr[largest]) 
			largest = right;

		if (largest != index)
		{
			swap(arr[largest], arr[index]);
			shiftDown(largest);
		}
	}
};

#endif

#include <iostream>


#include "BinaryHeap.h"


using namespace std;

int main()
{
	BinaryHeap<int> bin;

	for (int i = 0; i < 10; i++)
	{
		bin.insert(i + 1);
	}
	bin.insert(11);
	bin.insert(12);

	bin.display();

	bin.poll();
	bin.poll();
	bin.poll();
	cout << "\n\n\n";

	bin.display();
	string data = bin.toString();

	cout << data;
}
