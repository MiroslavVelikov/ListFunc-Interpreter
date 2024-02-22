#pragma once
#include "embedded.hpp"
#include "realNumber.h"
#include <stdexcept>

// add, sub, mul, div, mod, sqrt. 

struct funcAdd : public embedded {
	virtual expression* evaluate(const std::vector<expression*>& args) const override {
		if (args.size() != 2) throw std::invalid_argument("Invalid amount of arguments\n");

		const expression* num1 = args[0]; 
		const expression* num2 = args[1];
		
		if (num1->getType() == num2->getType() && num1->getType() == ExpressionType::REAL_NUMBER) {
			const realNumber* rNum1 = dynamic_cast<const realNumber*>(num1);
			const realNumber* rNum2 = dynamic_cast<const realNumber*>(num2);

			return new realNumber(rNum1->getValue() + rNum2->getValue());
		}

		throw std::invalid_argument("Invalid argument\n");
	}

	expression* clone() const override {
		return new funcAdd(*this);
	}
};

struct funcSub : public embedded {
	virtual expression* evaluate(const std::vector<expression*>& args) const override {
		if (args.size() != 2) throw std::invalid_argument("Invalid amount of arguments\n");

		const expression* num1 = args[0];
		const expression* num2 = args[1];

		if (num1->getType() == num2->getType() && num1->getType() == ExpressionType::REAL_NUMBER) {
			const realNumber* rNum1 = dynamic_cast<const realNumber*>(num1);
			const realNumber* rNum2 = dynamic_cast<const realNumber*>(num2);

			return new realNumber(rNum1->getValue() - rNum2->getValue());
		}

		throw std::invalid_argument("Invalid argument\n");
	}

	expression* clone() const override {
		return new funcSub(*this);
	}
};

struct funcMul : public embedded {
	virtual expression* evaluate(const std::vector<expression*>& args) const override {
		if (args.size() != 2) throw std::invalid_argument("Invalid amount of arguments\n");

		const expression* num1 = args[0];
		const expression* num2 = args[1];

		if (num1->getType() == num2->getType() && num1->getType() == ExpressionType::REAL_NUMBER) {
			const realNumber* rNum1 = dynamic_cast<const realNumber*>(num1);
			const realNumber* rNum2 = dynamic_cast<const realNumber*>(num2);

			return new realNumber(rNum1->getValue() * rNum2->getValue());
		}

		throw std::invalid_argument("Invalid argument\n");
	}

	expression* clone() const override {
		return new funcMul(*this);
	}
};

struct funcDiv : public embedded {
	virtual expression* evaluate(const std::vector<expression*>& args) const override {
		if (args.size() != 2) throw std::invalid_argument("Invalid amount of arguments\n");

		const expression* num1 = args[0];
		const expression* num2 = args[1];

		if (num1->getType() == num2->getType() && num1->getType() == ExpressionType::REAL_NUMBER) {
			const realNumber* rNum1 = dynamic_cast<const realNumber*>(num1);
			const realNumber* rNum2 = dynamic_cast<const realNumber*>(num2);

			if (!rNum2->getValue()) throw std::invalid_argument("Can not divide by zero\n");

			return new realNumber(rNum1->getValue() / rNum2->getValue());
		}

		throw std::invalid_argument("Invalid argument\n");
	}

	expression* clone() const override {
		return new funcDiv(*this);
	}
};

struct funcMod : public embedded {
	virtual expression* evaluate(const std::vector<expression*>& args) const override {
		if (args.size() != 2) throw std::invalid_argument("Invalid amount of arguments\n");

		const expression* num1 = args[0];
		const expression* num2 = args[1];

		if (num1->getType() == num2->getType() && num1->getType() == ExpressionType::REAL_NUMBER) {
			const realNumber* rNum1 = dynamic_cast<const realNumber*>(num1);
			const realNumber* rNum2 = dynamic_cast<const realNumber*>(num2);

			int intNum1 = rNum1->getValue(), intNum2 = rNum2->getValue();
			if (intNum1 != rNum1->getValue() || intNum2 != rNum2->getValue())
				throw std::invalid_argument("Numbers must be integers");
			
			return new realNumber(intNum1 % intNum2);
		}

		throw std::invalid_argument("Invalid argument\n");
	}

	expression* clone() const override {
		return new funcMod(*this);
	}
};

struct funcInt : public embedded {
	virtual expression* evaluate(const std::vector<expression*>& args) const override {
		if (args.size() != 1) throw std::invalid_argument("Invalid amount of arguments\n");

		const expression* num = args[0];

		if (num->getType() == ExpressionType::REAL_NUMBER) {
			const realNumber* rNum = dynamic_cast<const realNumber*>(num);

			return new realNumber(rNum->getValue());
		}

		throw std::invalid_argument("Invalid argument\n");
	}

	expression* clone() const override {
		return new funcInt(*this);
	}
};