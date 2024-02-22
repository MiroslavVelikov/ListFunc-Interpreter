#pragma once
#include "expression.h"
#include <string>

class placeHolder : public expression {
public:
	placeHolder(const std::string& name);
	placeHolder(const char* name);

	~placeHolder() = default;

	const std::string& getName() const;
	expression* clone() const override {
		return new placeHolder(*this);
	}
private:
	std::string name;
};

inline placeHolder::placeHolder(const std::string& name)
	: expression(ExpressionType::PLACE_HOLDER), name(name) {};

inline placeHolder::placeHolder(const char* name)
	: expression(ExpressionType::PLACE_HOLDER), name(name) {};

inline const std::string& placeHolder::getName() const {
	return name;
}