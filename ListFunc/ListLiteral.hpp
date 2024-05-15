#pragma once
#include "Expression.hpp"
#include <stdexcept> // out_of_range
#include <vector>

template <typename Type>
class ListLiteral : public Expression {
public:
	ListLiteral();
	
	~ListLiteral();
	ListLiteral(const ListLiteral& other);
	ListLiteral& operator=(const ListLiteral& other);

	virtual Expression* clone() const override;
	
	size_t getSize() const;
	
	void add(const Type& element);
	void remove(size_t index);

	const Type& operator[](size_t index) const;
	Type& operator[](size_t index);
	
private:
	void free();
	void copy(const ListLiteral& other);

private:
	std::vector<Type*> data;

	static const size_t DEFAULT_CAPACITY = 8;
};

template <typename Type>
inline ListLiteral<Type>::ListLiteral()
	: Expression(ExpressionType::LIST_LITERAL), data(DEFAULT_CAPACITY) {}

template<typename Type>
inline ListLiteral<Type>::~ListLiteral() {
	free();
}

template<typename Type>
inline ListLiteral<Type>::ListLiteral(const ListLiteral& other) {
	copy(other);
}

template<typename Type>
inline ListLiteral<Type>& ListLiteral<Type>::operator=(const ListLiteral& other) {
	if (this != &other) {
		free();
		copy(other);
	}
	
	return *this;
}

template<typename Type>
inline Expression* ListLiteral<Type>::clone() const {
	return new ListLiteral(*this);
}

template <typename Type>
inline size_t ListLiteral<Type>::getSize() const {
	return data.size();
}

template <typename Type>
inline void ListLiteral<Type>::add(const Type& element) {
	data.push_back(new Type(element));
}

template <typename Type>
inline void ListLiteral<Type>::remove(size_t index) {
	size_t size = getSize();

	if (index >= size)
		throw std::out_of_range("Index out of range\n");

	std::swap(data[index], data[size - 1]);
	delete data[size - 1];
	data.pop_back();
}

template <typename Type>
inline const Type& ListLiteral<Type>::operator[](size_t index) const {
	return data[index];
}

template <typename Type>
inline Type& ListLiteral<Type>::operator[](size_t index) {
	return data[index];
}

template<typename Type>
inline void ListLiteral<Type>::free() {
	for (size_t i = 0; i < data.size(); ++i) {
		delete data[i];
	}
}

template<typename Type>
inline void ListLiteral<Type>::copy(const ListLiteral& other) {
	data.reserve(other.data.capacity());
	
	for (size_t i = 0; i < other.data.size; ++i) {
		add(*other.data[i]);
	}
}