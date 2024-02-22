#pragma once
#include <vector>
#include "expression.h"
#include "oaHashTable.hpp"

class infiniteList : public expression {
private:
	struct indexHistory {
		size_t operator()(size_t index) const {
			return index;
		}
	};

public:
	infiniteList(double beginning, double step = 1);
	~infiniteList() = default;

	double at(size_t index);
	double begin() const {
		return beg;
	}
	//std::vector<double> take(size_t count) const;
	
	expression* clone() const override {
		return new infiniteList(*this);
	}

	infiniteList* tail() const {
		return new infiniteList(beg + step, step);
	}

private:
	double beg;
	double step;
	oaHashTable<size_t, double, indexHistory> searchHistory = oaHashTable<size_t, double, indexHistory>(indexHistory{});
};