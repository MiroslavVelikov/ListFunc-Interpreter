#pragma once
#include "Expression.h"
#include <stdexcept> // out_of_range
#include <vector>

template <typename Type>
class ListLiteral : public Expression {
public:
	ListLiteral(const std::string& name);
	
	~ListLiteral() = default;

	size_t getSize() const;
	
	void add(const Type& element);
	void remove(size_t index);

	const Type& operator[](size_t index) const;
	Type& operator[](size_t index);
	
private:
	std::vector<Type*> data;
};

template <typename Type>
inline ListLiteral<Type>::ListLiteral(const std::string& name)
{
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