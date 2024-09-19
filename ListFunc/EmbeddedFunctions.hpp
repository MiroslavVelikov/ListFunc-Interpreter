#pragma once
#include <vector>
#include "ListLiteral.h"
#include <stdexcept>
#include "ListInfinity.hpp"
#include "Stack.hpp"
#include <math.h>

enum class EmbeddedType {
	UNKNOWN,
	EQ,
	LE,
	NAND,
	LENGTH,
	HEAD,
	TAIL,
	LIST,
	CONCAT,
	IF,
	READ,
	WRITE,
	INT,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	SQRT
};

class BaseEmbedded : public Expression {
public:
	BaseEmbedded(ExpressionType type) : Expression(type) {}
	virtual ~BaseEmbedded() = default;

	virtual Expression* callFunction(Stack<Expression*>& args) const = 0;
	virtual EmbeddedType getEmbType() const = 0;
};

class eq : public BaseEmbedded {
public:
	eq() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {};

	RealNumber* operator()(const Comparable* arg1, const Comparable* arg2) const {
		return new RealNumber(*arg1 == arg2);
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		if (args.getSize() < 2)
			throw std::invalid_argument("Not enough arguments");

		Expression* arg1 = args.pop();
		Expression* arg2 = args.pop();

		if ((arg1->getType() != ExpressionType::REAL_NUMBER && arg1->getType() != ExpressionType::LIST_LITERAL)
			&& (arg2->getType() != ExpressionType::REAL_NUMBER && arg2->getType() != ExpressionType::LIST_LITERAL))
			throw std::invalid_argument("Not suitable arguments\n");

		return (*this)((Comparable*)arg1, (Comparable*)arg2);
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::EQ;
	}
};

class le : public BaseEmbedded {
public:
	le() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	RealNumber* operator()(const RealNumber* arg1, const RealNumber* arg2) const {
		return new RealNumber(arg1->getValue() < arg2->getValue());
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		if (args.getSize() < 2)
			throw std::invalid_argument("Not enough arguments\n");

		Expression* arg1 = args.pop();
		Expression* arg2 = args.pop();

		if (arg1->getType() != ExpressionType::REAL_NUMBER 
			&& arg2->getType() != ExpressionType::REAL_NUMBER)
			throw std::invalid_argument("Not suitable arguments\n");

		return (*this)((RealNumber*)arg1, (RealNumber*)arg2);
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::LE;
	}
};

class nand : public BaseEmbedded {
public:
	nand() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	RealNumber* operator()(const Comparable* arg1, const Comparable* arg2) const {
		return new RealNumber(!(*arg1) || !(*arg2)); // might change in the system
		// I might leave it just for the presence but its functionality
		// will be within the system logic
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		if (args.getSize() < 2)
			throw std::invalid_argument("Not enough arguments\n");

		Expression* arg1 = args.pop();
		Expression* arg2 = args.pop();

		if ((arg1->getType() != ExpressionType::REAL_NUMBER && arg1->getType() != ExpressionType::LIST_LITERAL)
			|| (arg2->getType() != ExpressionType::REAL_NUMBER && arg2->getType() != ExpressionType::LIST_LITERAL))
			throw std::invalid_argument("Not suitable arguments\n");

		return (*this)((Comparable*)arg1, (Comparable*)arg2);
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::NAND;
	}
};

class length : public BaseEmbedded {
public:
	length() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	RealNumber* operator()(const Comparable* arg) const {
		if (arg->getType() == ExpressionType::REAL_NUMBER)
			return new RealNumber(-1);
		
		const ListLiteral* list = (const ListLiteral*)arg;
		return new RealNumber(list->getSize());
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		if (args.getSize() < 1)
			throw std::invalid_argument("Not enough arguments\n");

		Expression* arg = args.pop();
		
		if (arg->getType() != ExpressionType::REAL_NUMBER && arg->getType() != ExpressionType::LIST_LITERAL)
			throw std::invalid_argument("Not suitable arguments\n");

		return (*this)((Comparable*)arg);
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::LENGTH;
	}
};

class head : public BaseEmbedded {
public:
	head() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	RealNumber* operator()(const BaseList* arg) const {
		if (!arg) // make check if it is empty !!!!!
			throw std::out_of_range("Not enough elements\n"); // FIXXX

		return new RealNumber((*arg)[0]);
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		if (args.getSize() < 1)
			throw std::invalid_argument("Not enough arguments\n");

		Expression* arg = args.pop();

		if (arg->getType() != ExpressionType::LIST_INFINITY && arg->getType() != ExpressionType::LIST_LITERAL)
			throw std::invalid_argument("Not suitable arguments\n");
		
		return (*this)((BaseList*)arg);
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::HEAD;
	}
};

class tail : public BaseEmbedded { // FIX!!!!!!!!!!!!!!!!!!!!!!!!
public:
	tail() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	void operator()(const std::vector<const Expression*>& args) {
		if (args.empty())
			throw std::invalid_argument("Invalid amount of arguments!\n");

		//return *args[0];
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		return nullptr;
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::TAIL;
	}
};

class list : public BaseEmbedded {
public:
	list() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	BaseList* operator()(const std::vector<const Expression*>& args) const {
		if(args.empty() || args.size() > 3)
			throw std::invalid_argument("Invalid amount of arguments!\n");
		
		switch (args.size()) {
		case 1:
			/*ListInfinity * li = new ListInfinity(args[0]);*/
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		return nullptr;
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::LIST;
	}
};

class read : public BaseEmbedded { // Also must be fixed
public:
	read() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		return nullptr;
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::READ;
	}
};

class concat : public BaseEmbedded {
public:
	concat() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	ListLiteral* operator()(const ListLiteral* arg1, const ListLiteral* arg2) const {
		return (*arg1) + (*arg2);
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		if (args.getSize() < 2)
			throw std::invalid_argument("Not enough arguments");

		Expression* arg1 = args.pop();
		Expression* arg2 = args.pop();

		if ((arg1->getType() != ExpressionType::REAL_NUMBER && arg1->getType() != ExpressionType::LIST_LITERAL)
			|| (arg2->getType() != ExpressionType::REAL_NUMBER && arg2->getType() != ExpressionType::LIST_LITERAL))
			throw std::invalid_argument("Not suitable arguments\n");

		return (*this)((ListLiteral*)arg1, (ListLiteral*)arg2);
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::CONCAT;
	}
};

class If : public BaseEmbedded {
public:
	If() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}
	
	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		return nullptr;
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::IF;
	}
};

class write : public BaseEmbedded {
public:
	write() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	void operator()() const { // Create Child of Expression Printable
		//...
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		return nullptr;
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::WRITE;
	}
};

class Int : public BaseEmbedded {
public:
	Int() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	RealNumber* operator()(const RealNumber* arg) const {
		int argValue = arg->getValue();
		return new RealNumber(argValue);
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		if (args.getSize() < 1)
			throw std::invalid_argument("Not enough arguments\n");

		Expression* arg = args.pop();
		
		if (arg->getType() != ExpressionType::REAL_NUMBER)
			throw std::invalid_argument("Not suitable arguments\n");

		return (*this)((RealNumber*)arg);
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::INT;
	}
};

class add : public BaseEmbedded {
public:
	add() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	RealNumber* operator()(const RealNumber* arg1, const RealNumber* arg2) const {
		return new RealNumber(arg1->getValue() + arg2->getValue());
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		if (args.getSize() < 2)
			throw std::invalid_argument("Not enough arguments\n");

		Expression* arg1 = args.pop();
		Expression* arg2 = args.pop();

		if (arg1->getType() != ExpressionType::REAL_NUMBER 
			&& arg2->getType() != ExpressionType::REAL_NUMBER)
			throw std::invalid_argument("Not suitable arguments\n");

		return (*this)((RealNumber*)arg1, (RealNumber*)arg2);
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::ADD;
	}
};

class sub : public BaseEmbedded {
public:
	sub() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	RealNumber* operator()(const RealNumber* arg1, const RealNumber* arg2) const {
		return new RealNumber(arg1->getValue() - arg2->getValue());
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		if (args.getSize() < 2)
			throw std::invalid_argument("Not enough arguments\n");

		Expression* arg1 = args.pop();
		Expression* arg2 = args.pop();

		if (arg1->getType() != ExpressionType::REAL_NUMBER
			&& arg2->getType() != ExpressionType::REAL_NUMBER)
			throw std::invalid_argument("Not suitable arguments\n");

		return (*this)((RealNumber*)arg1, (RealNumber*)arg2);
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::SUB;
	}
};

class mul : public BaseEmbedded {
public:
	mul() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	RealNumber* operator()(const RealNumber* arg1, const RealNumber* arg2) const {
		return new RealNumber(arg1->getValue() * arg2->getValue());
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		if (args.getSize() < 2)
			throw std::invalid_argument("Not enough arguments\n");

		Expression* arg1 = args.pop();
		Expression* arg2 = args.pop();

		if (arg1->getType() != ExpressionType::REAL_NUMBER
			&& arg2->getType() != ExpressionType::REAL_NUMBER)
			throw std::invalid_argument("Not suitable arguments\n");

		return (*this)((RealNumber*)arg1, (RealNumber*)arg2);
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::MUL;
	}
};

//DIV,
class Div : public BaseEmbedded {
public:
	Div() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	RealNumber* operator()(const RealNumber* arg1, const RealNumber* arg2) const {
		if (arg2->getValue() == 0)
			throw std::invalid_argument("Cannot divide by zero\n");

		return new RealNumber(arg1->getValue() / arg2->getValue());
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		if (args.getSize() < 2)
			throw std::invalid_argument("Not enough arguments\n");

		Expression* arg1 = args.pop();
		Expression* arg2 = args.pop();

		if (arg1->getType() != ExpressionType::REAL_NUMBER
			&& arg2->getType() != ExpressionType::REAL_NUMBER)
			throw std::invalid_argument("Not suitable arguments\n");

		return (*this)((RealNumber*)arg1, (RealNumber*)arg2);
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::DIV;
	}
};

class mod : public BaseEmbedded {
public:
	mod() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	RealNumber* operator()(const RealNumber* arg1, const RealNumber* arg2) const {
		int num1 = arg1->getValue(), num2 = arg2->getValue();
		
		if (arg1->getValue() != num1 || arg2->getValue() != num2)
			throw std::invalid_argument("Numbers must be integers\n");
		
		return new RealNumber(num1 % num2);
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		if (args.getSize() < 2)
			throw std::invalid_argument("Not enough arguments\n");

		Expression* arg1 = args.pop();
		Expression* arg2 = args.pop();

		if (arg1->getType() != ExpressionType::REAL_NUMBER
			&& arg2->getType() != ExpressionType::REAL_NUMBER)
			throw std::invalid_argument("Not suitable arguments\n");

		return (*this)((RealNumber*)arg1, (RealNumber*)arg2);
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::MOD;
	}
};

class Sqrt : public BaseEmbedded {
public:
	Sqrt() : BaseEmbedded(ExpressionType::EMBEDDED_FUNCTION) {}

	RealNumber* operator()(const RealNumber* arg) const {
		return new RealNumber(std::sqrt(arg->getValue()));
	}

	virtual Expression* callFunction(Stack<Expression*>& args) const override {
		if (args.getSize() < 1)
			throw std::invalid_argument("Not enough arguments\n");

		Expression* arg = args.pop();

		if (arg->getType() != ExpressionType::REAL_NUMBER)
			throw std::invalid_argument("Not suitable argument\n");

		return (*this)((RealNumber*)arg);
	}

	virtual EmbeddedType getEmbType() const override {
		return EmbeddedType::SQRT;
	}
};