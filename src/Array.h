#pragma once
#include <cstring>
#include <iostream>

// Array class declaration
template <typename T>
class Array {
private:
	T* m_array;
	int m_start_index;
	int m_length; //Starts at 1
	int m_newArray;

public:
	// default constructor
	Array() : m_array(nullptr), m_start_index(0), m_length(0) {};
	// paramaterized constructor
	Array(int length, int start_index = 0);
	// copy constructor
	Array (const Array<T>& copy);
	// move constructor
	Array(Array<T>&& move) noexcept;
	//destructor
	~Array();

	// copy assignment
	Array<T>& operator = (const Array<T>& copy);
	// move assignment
	Array<T>& operator = (Array<T>&& move) noexcept;
	// subscript
	T& operator [] (const int);

	// get start index
	const int getStartIndex();
	// set start index
	void setStartIndex(const int start_index);
	// get length of array
	const int getLength();
	// set length of array
	void setLength(int length);

	//Friend Queue Class
	template <typename U>
	friend class Queue;
};






