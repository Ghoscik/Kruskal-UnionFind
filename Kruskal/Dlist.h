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
	bool owner;

	void swap(T& var1, T& var2);
	T* arr;

public:
	Dlist() : size(0), capacity(1), arr(new T[capacity]), owner(true) { std::fill(arr, arr + capacity, T()); }
	Dlist(uint32_t cap) : size(0), capacity(cap), arr(new T[cap]), owner(true) { std::fill(arr, arr + cap, T()); }
	Dlist(uint32_t cap, T fillValue) : size(cap), capacity(cap), arr(new T[cap]), owner(true) { std::fill(arr, arr + cap, fillValue); }

	Dlist(T* arr, uint32_t size) : arr(arr), size(size), capacity(size), owner(false) {}


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

	// Indexing operator
	T& operator[](int index)
	{
		if (index < 0 || index > capacity)
			throw std::out_of_range("Index out of range!");
		return arr[index];
	}


	bool push(T data);
	bool push(T data, int index);

	T pop();
	T remove(int index);

	bool edit(int atIndex, T toReplace);

	uint32_t getSize() { return size; }
	uint32_t getCapacity() { return capacity; }

	void display(const char* sep = ", ", uint32_t end = 0);

	std::string getAllData(std::string sep = ",", uint32_t end = 0);
	std::string dataString(T item);

	void sort(bool (*comp)(const T&, const T&) = nullptr);
	void resize();

	bool empty() const { return size == 0; }

	bool exist(uint32_t index) const
	{
		if (index >= capacity) return false;
		return arr[index] != T();
	}

	void fill(T value)
	{
		std::fill(arr, arr + capacity, value);
	}

	T* begin() { return arr; }
	T* end() { return arr + size; }

	void clear()
	{
		if (owner && arr)
		{
			delete[] arr;
		}
		arr = new T[1];
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

	~Dlist() { if (owner && arr) delete[] arr; }
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

	if (owner && arr)
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
	if (size <= 1) return;
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