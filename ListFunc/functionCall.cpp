#include "functionCall.h"
#include "functionEnvironment.h"

inline functionCall::functionCall(const std::string& body)
	: expression(ExpressionType::FUNCTION_CALL) {
	for (size_t i = 0; i < body.length(); ++i) {
		char current = body[i];

		if ((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z')) {
			std::string name = body.substr(i, body.find('('));

		}
		else if (current == '#') {

		}
		else if (current >= '0' && current <= '9') {

		}
		else if (current == ' ' || current == ',') continue;
		else throw std::invalid_argument("Incorrect expression\n");
	}
}

inline functionCall::~functionCall() {
	for (expression* expr : args) {
		delete expr;
		expr = nullptr;
	}
}

inline expression* functionCall::evaluate(const std::vector<expression*>& params) const {
	return 0;
}