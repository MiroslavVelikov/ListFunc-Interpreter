#pragma once
#include "embedded.hpp"
#include "listLiteral.h"
#include "infiniteList.h"
#include "realNumber.h"
#include <stdexcept>

// head, tail, list, concat

struct funcHead : public embedded {
	virtual expression* evaluate(const std::vector<expression*>& args) const override {
		if (args.size() != 1) throw std::invalid_argument("Invalid amount of arguments\n");

		const expression* list = args[0];

		if (list->getType() != ExpressionType::LIST_LITERAL 
			&& list->getType() != ExpressionType::INFINITE_LIST) 
			throw std::invalid_argument("Invalid argument\n");
		
		if (list->getType() == ExpressionType::LIST_LITERAL) {
			const listLiteral* listLit = dynamic_cast<const listLiteral*>(list);
			
			return listLit->at(0)->clone();
		}
		else if (list->getType() == ExpressionType::INFINITE_LIST) {
			const infiniteList* infList = dynamic_cast<const infiniteList*>(list);

			return new realNumber(infList->begin());
		}
	}

	expression* clone() const override {
		return new funcHead(*this);
	}
};

struct funcTail : public embedded {
	virtual expression* evaluate(const std::vector<expression*>& args) const override {
		if (args.size() != 1) throw std::invalid_argument("Invalid amount of arguments\n");

		const expression* list = args[0];

		if (list->getType() != ExpressionType::LIST_LITERAL
			&& list->getType() != ExpressionType::INFINITE_LIST)
			throw std::invalid_argument("Invalid argument\n");

		if (list->getType() == ExpressionType::LIST_LITERAL) {
			const listLiteral* listLit = dynamic_cast<const listLiteral*>(list);

			return listLit->tail();
		}
		else if (list->getType() == ExpressionType::INFINITE_LIST) {
			const infiniteList* infList = dynamic_cast<const infiniteList*>(list);

			return infList->tail();
		}
	}

	expression* clone() const override {
		return new funcTail(*this);
	}
};

struct funcList : public embedded {
	virtual expression* evaluate(const std::vector<expression*>& args) const override {
		if (args.size() == 1) {
			const realNumber* beg = dynamic_cast<const realNumber*>(args[0]);
			
			return new infiniteList(beg->getValue());
		}
		else if (args.size() == 2) {
			const realNumber* beg = dynamic_cast<const realNumber*>(args[0]);
			const realNumber* step = dynamic_cast<const realNumber*>(args[1]);
			
			return new infiniteList(beg->getValue(), step->getValue());
		}
		else if (args.size() == 3) {
			const realNumber* beg = dynamic_cast<const realNumber*>(args[0]);
			const realNumber* step = dynamic_cast<const realNumber*>(args[1]);
			const realNumber* count = dynamic_cast<const realNumber*>(args[2]);
		
			std::vector<expression*> vec(count->getValue());
			for (size_t i = 0; i < vec.size(); ++i) {
				vec[i] = new realNumber(beg->getValue() + step->getValue() * i);
			}

			return new listLiteral(vec);
		}

		throw std::invalid_argument("Invalid amount of arguments\n");
	}

	expression* clone() const override {
		return new funcList(*this);
	}
};

struct funcConcat : public embedded {
	virtual expression* evaluate(const std::vector<expression*>& args) const override {
		if (args.size() == 1 && args[0]->getType() == ExpressionType::REAL_NUMBER) {
			const realNumber* beg = dynamic_cast<const realNumber*>(args[0]);

			return new infiniteList(beg->getValue());
		}
		else if (args.size() == 2 && args[0]->getType() == ExpressionType::REAL_NUMBER 
			&& args[1]->getType() == ExpressionType::REAL_NUMBER) {
			const realNumber* beg = dynamic_cast<const realNumber*>(args[0]);
			const realNumber* step = dynamic_cast<const realNumber*>(args[1]);

			return new infiniteList(beg->getValue(), step->getValue());
		}
		else if (args.size() == 3 && args[0]->getType() == ExpressionType::REAL_NUMBER
			&& args[1]->getType() == ExpressionType::REAL_NUMBER && args[2]->getType() == ExpressionType::REAL_NUMBER) {
			const realNumber* beg = dynamic_cast<const realNumber*>(args[0]);
			const realNumber* step = dynamic_cast<const realNumber*>(args[1]);
			const realNumber* count = dynamic_cast<const realNumber*>(args[2]);

			std::vector<expression*> vec(count->getValue());
			for (size_t i = 0; i < vec.size(); ++i) {
				vec[i] = new realNumber(beg->getValue() + step->getValue() * i);
			}

			return new listLiteral(vec);
		}

		throw std::invalid_argument("Invalid amount of arguments\n");
	}

	expression* clone() const override {
		return new funcConcat(*this);
	}
};