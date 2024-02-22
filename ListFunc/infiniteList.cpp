#include "infiniteList.h"
#include <stdexcept>

inline infiniteList::infiniteList(double beginning, double step)
	: expression(ExpressionType::INFINITE_LIST), beg(beginning), step(step) {}

inline double infiniteList::at(size_t index) {
	try {
		return searchHistory.get(index);
	}
	catch (const std::invalid_argument&) {
		size_t sum = beg + step * index;
		searchHistory.insert(index, sum);
		return sum;
	}
}