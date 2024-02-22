#include "listLiteral.h"
#include <stdexcept>

inline listLiteral::listLiteral(const std::vector<expression*>& elements)
	: expression(ExpressionType::LIST_LITERAL), elements(elements) {}

inline listLiteral::~listLiteral() {
	for (expression* elem : elements) {
		delete elem;
		elem = nullptr;
	}
}

inline const expression* listLiteral::at(size_t index) const {
	if (index >= elements.size()) 
		throw std::out_of_range("Index out of range\n");
	
	return elements[index];
}

//inline myVector<double> listLiteral::evaluateList() const {
//	myVector<double> result(elements.getSize());
//
//	for (size_t i = 0; i < elements.getSize(); ++i) {
//		expression* currentElem = elements[i];
//
//		switch (currentElem->getType()) {
//		case ExpressionType::REAL_NUMBER:
//			result.push_back(currentElem->evaluate());
//			break;
//		case ExpressionType::LIST_LITERAL:
//			result += currentElem->evaluateList();
//			break;
//		case ExpressionType::FUNCTION:
//			break;
//		default:
//			throw std::invalid_argument("Invalid argument\n");
//			break;
//		}
//	}
//
//	return result;
//}