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
	void resize(uint64_t n = 2);

	Dlist()	: size(0), capacity(1), arr(new T[capacity])
	{
		std::fill(arr, arr + capacity, T());
	}


	Dlist(uint32_t cap) : size(0), capacity(cap), arr(new T[cap])
	{
		std::fill(arr, arr + cap, T());
	}


	// Copy constructor
	Dlist(const Dlist& other)
		: arr(new T[other.capacity]),
		size(other.size),
		capacity(other.capacity) 
	{
		for (size_t i = 0; i < size; ++i) 
		{
			arr[i] = other.arr[i];
		}
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
			{
				arr[i] = other.arr[i];
			}
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
		{
			throw std::out_of_range("Array is empty");
		}
		return arr[0];
	}

	T& back() 
	{
		if (empty()) 
		{
			throw std::out_of_range("Array is empty");
		}
		return arr[size - 1];
	}

	bool push(T data);
	bool push(T data, int index);

	bool pop();
	bool remove(int index);

	T find(int index);
	bool edit(int atIndex, T toReplace);

	uint32_t getSize() { return size; }
	void setSize(uint32_t newSize) { size = newSize; }
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
void Dlist<T>::resize(uint64_t n)
{
	capacity *= n;
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
bool Dlist<T>::pop()
{
	if (size == 0)
		throw std::out_of_range("List is empty");

	size--;
	return true;
}

template<typename T>
bool Dlist<T>::remove(int index)
{
	if (index < 0 || index > size)
		return false;
	
	T removed = arr[index];

	for (int i = index; i < size - 1; i++)
	{
		arr[i] = std::move(arr[i + 1]);
	}
	size--;
	return true;
}

template<typename T>
T Dlist<T>::find(int index)
{
	if (index < 0 || index > size)
		throw std::out_of_range("Index out of range");
	return arr[index];
}

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