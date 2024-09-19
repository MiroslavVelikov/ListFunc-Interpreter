#pragma once
#include "Expression.hpp"
#include "RealNumber.h"
#include <vector>
#include <iostream>

class ListLiteral : public Comparable, public BaseList {
private:
	static const size_t DEFAULT_CAPACITY = 8;

public:
	ListLiteral(const std::vector<const RealNumber*> data);

	size_t getSize() const;
	virtual void print(std::ostream& os) const override;

	virtual RealNumber operator[](size_t index) const override;
	virtual bool operator==(const Comparable* other) const;
	virtual bool operator!() const override;

	friend ListLiteral* operator+(const ListLiteral& arg1, const ListLiteral& arg2);

protected:
	virtual bool operator==(const RealNumber* other) const override;
	virtual bool operator==(const ListLiteral* other) const override;

private:
	std::vector<const RealNumber*> data;
};

inline ListLiteral* operator+(const ListLiteral& arg1, const ListLiteral& arg2) {
	{
		std::vector<const RealNumber*> result(arg1.data.size() + arg2.data.size());

		for (size_t i = 0; i < arg1.data.size(); ++i) {
			result.push_back(arg1.data[i]);
		}

		for (size_t i = 0; i < arg2.data.size(); ++i) {
			result.push_back(arg2.data[i]);
		}

		return new ListLiteral(result);
	}
}