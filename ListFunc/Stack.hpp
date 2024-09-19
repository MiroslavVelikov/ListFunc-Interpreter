#pragma once
#include <exception>

template <typename T>
class Stack {
private:
	const static size_t DEFAULT_SIZE = 8;

public:
	Stack();
	~Stack();

	void push(const T& element);
	T& pop();

	const T& top() const;
	bool isEmpty() const;
	size_t getSize() const;

	void clear();

public:
	void resize();

private:
	T* data;
	size_t size;
	size_t capacity;
};

template<typename T>
inline Stack<T>::Stack() {
	capacity = DEFAULT_SIZE;
	data = new T[capacity];
	size = 0;
}

template<typename T>
inline Stack<T>::~Stack() {
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}

template<typename T>
inline void Stack<T>::push(const T& element) {
	if (size >= capacity)
		resize();

	data[size] = element;
	++size;
}

template<typename T>
inline T& Stack<T>::pop() {
	if (isEmpty())
		throw std::out_of_range("Not enough elements\n");

	--size;
	return data[size];
}

template<typename T>
inline const T& Stack<T>::top() const {
	if (isEmpty())
		throw std::out_of_range("Not enough elements\n");

	return data[size - 1];
}

template<typename T>
inline bool Stack<T>::isEmpty() const {
	return !size;
}

template<typename T>
inline size_t Stack<T>::getSize() const {
	return size;
}

template<typename T>
inline void Stack<T>::clear() {
	size = 0;
}

template<typename T>
inline void Stack<T>::resize() {
	T* copy = data;

	capacity *= 2;
	data = new T[capacity];

	for (size_t i = 0; i < size; ++i) {
		data[i] = copy[i];
	}
}