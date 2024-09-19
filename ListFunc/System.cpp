#include "System.h"

System::System() {
	data.insert("eq", new eq());
	data.insert("le", new le());
	data.insert("nand", new nand());
	data.insert("length", new length());
	data.insert("head", new head());
	data.insert("tail", new tail());
	data.insert("list", new list());
	data.insert("concat", new concat());
	data.insert("if", new If());
	data.insert("read", new read());
	data.insert("write", new write());
	data.insert("int", new Int());

	data.insert("add", new add());
	data.insert("sub", new sub());
	data.insert("mul", new mul());
	data.insert("div", new Div());
	data.insert("mod", new mod());
	data.insert("sqrt", new Sqrt());
}

System::~System() {
	iterator_t iter = data.begin();

	while (iter != data.end()) {
		if (iter->value) {
			delete iter->value;
			iter->value = nullptr;
		}

		++iter;
	}
}

System& System::getInstance() {
	static System instance;
	return instance;
}

void System::startProgram() {
	std::string input;

	std::getline(std::cin, input);

	while (input != "end") {
		try {
			std::vector<std::string>* commands = &splitBySpace(input);

			if (commands->empty()) {
				delete commands;
				continue;
			}
			else if (commands->size() == 1) {
				std::vector<std::string> order;
				size_t args;
				fillOrder(order, input, args);

				Operation* opr = new Operation();
				buildOperation(order, args, opr);

				Function func;
				func.setOperations(opr);

				Comparable* result = (Comparable*)executeFunction(&func);
				std::cout << "> ";
				result->print(std::cout);
				std::cout << '\n';

				delete result;
			}
			else if ((*commands)[1] == "->" && commands->size() == 3) {
				bool existingFlag = false;

				createFunction((*commands)[0], (*commands)[2], existingFlag);

				if (existingFlag)
					std::cout << "> 1\n";
				else
					std::cout << "> 0\n";
			}
			else if ((*commands)[0] == "open") {
				popFirstWord(input);
				input = (input.c_str() + 1); // skip space at the beginning

				// TODO open file
			}
			else {
				std::cout << "> Invalid input\n";
			}

			delete commands;
		}
		catch (const std::invalid_argument& e) {
			std::cout << "> " << e.what();
		}
		catch (...) {
			std::cout << "> Due to unforeseen circumstances, the program stopped working\n";
			break;
		}

		std::getline(std::cin, input);
	}
}

Expression* System::createFunction(const std::string& funcName, const std::string& expression, bool& existingFlag) {
	size_t argsCount = 0;

	iterator_t exists = data.find(funcName);

	if (exists != data.end()) {
		existingFlag = true;
		delete exists->value;
	}

	std::vector<std::string> order;
	fillOrder(order, expression, argsCount);

	Function* currentExpr = new Function(funcName);
	data.insert(funcName, currentExpr);

	Operation* operation = new Operation();

	buildOperation(order, argsCount, operation);

	currentExpr->setArguments(argsCount);
	currentExpr->setOperations(operation);

	return currentExpr;
}

void System::buildOperation(std::vector<std::string>& order, size_t& argsCount, Operation*& operation) {
	size_t pos = 0, listPos = 0;
	for (const std::string& part : order) {
		if (part[0] == '#') {
			if (part.size() <= 1)
				throw std::invalid_argument("Invalid placeholder\n");

			const char* strNum = part.c_str();
			++strNum;

			int num = std::stoi(strNum);

			Placeholder* pl = new Placeholder(num);
			joinOperation(operation, pl);
		}
		else if (isNumber(part)) {
			double num = std::stod(part.c_str());

			RealNumber* rlNumber = new RealNumber(num);
			joinOperation(operation, rlNumber);
		}
		else if (part[0] == '[') {
			listPos = pos;
		}
		else if (part[0] == ']') {
			// logic behind list adding
			// count the pos - listPos to add the (list) node 
			// before the elements in it
			Operation* iter = operation;
			size_t elementsCount = pos - listPos;

			for (size_t i = 0; i < elementsCount; ++i) {
				iter = operation->operations[1];
			}

			//Operation* operationList = new Operation()
		}
		else if (part[0] == '(') {
			continue; // might be added complexity after if statement
		}
		else if (part[0] == ')') {
			continue;
		}
		else {
			iterator_t iter = data.find(part);

			if (iter == data.end())
				throw std::invalid_argument("Unexisting function is being used");

			joinOperation(operation, iter->value);
		}

		++pos;
	}
}

void System::joinOperation(Operation*& operation, Expression* expr, bool isIf) const {
	operation->operations[0] = new Operation(isIf);
	operation->operations[0]->operations[1] = operation;
	operation = operation->operations[0];

	operation->expr = expr;
}

Expression* System::executeFunction(const std::string& functionName, const std::vector<std::string>& arguments) {
	iterator_t iter = data.find(functionName);

	if (iter == data.end())
		throw std::invalid_argument("Unexisting function is being called");

	Expression* result = nullptr;

	if (iter->value->getType() == ExpressionType::FUNCTION) {
		Function* func = (Function*)iter->value;
		result = (*func)({});
	}
	else if (iter->value->getType() == ExpressionType::EMBEDDED_FUNCTION) {
		//BaseEmbedded* embedFunc = (BaseEmbedded*)iter->value;
		//embedFunc->callFunction({});
	}

	// 4 types arguments
	//  - real number
	//  - list literal
	//  - placeholder
	//  - function

	return result;
}

Expression* System::executeFunction(const Function* func) const {
	return (*func)({});;
}

bool System::isNumber(const std::string& str) const {
	bool isFloating = true;

	for (char ch : str) {
		if (ch == '.' && isFloating)
			isFloating = false;
		else if (!std::isdigit(ch))
			return false;
	}

	return true;
}

void System::fillOrder(std::vector<std::string>& order, const std::string& str, size_t& argsCount) const {
	std::string currentToken = "";
	bool isPlaceholder = false;
	int bracketsCount = 0, sqrBrackets = 0;

	for (char ch : str) {
		if (ch == '(') {
			if (isPlaceholder) {
				throw std::invalid_argument("Invalid input");
			}
			if (!currentToken.empty()) {
				order.push_back(currentToken);
				currentToken.clear();
			}

			order.push_back("(");
			++bracketsCount;
		}
		else if (ch == ')') {
			if (bracketsCount == 0) {
				throw std::invalid_argument("Invalid input");
			}
			if (!currentToken.empty()) {
				order.push_back(currentToken);
				currentToken.clear();

				isPlaceholder = false;
			}

			order.push_back(")");
			--bracketsCount;
		}
		else if (ch == '[') {
			if (!currentToken.empty()) {
				throw std::invalid_argument("Invalid Square Bracket");
			}

			order.push_back("[");
			++sqrBrackets;
		}
		else if (ch == ']') {
			if (sqrBrackets == 0) {
				throw std::invalid_argument("Invalid input");
			}
			if (!currentToken.empty()) {
				order.push_back(currentToken);
				currentToken.clear();

				isPlaceholder = false;
			}

			order.push_back("]");
			--sqrBrackets;
		}
		else if (isPlaceholder && std::isdigit(ch)) {
			currentToken += ch;
		}
		else if (currentToken.empty() && ch == '#') {
			currentToken += ch;
			isPlaceholder = true;
			++argsCount;
		}
		else if (std::isalnum(ch)) {
			currentToken += ch;
		}
		else {
			isPlaceholder = false;
			if (ch == ',' && !currentToken.empty()) {
				order.push_back(currentToken);
				currentToken.clear();
			}
			else if (ch == ' ' || ch == ',') {
				continue;
			}
			else {
				throw std::invalid_argument("Invalid input");
			}
		}
	}

	if (bracketsCount || sqrBrackets) {
		throw std::invalid_argument("Invalid amount of brackets");
	}
	if (!currentToken.empty()) {
		order.push_back(currentToken);
	}
}

std::vector<std::string>& System::splitBySpace(const std::string& str) const {
	std::vector<std::string>* result = new std::vector<std::string>();

	std::string currentToken = "";
	int bracketsCount = 0;

	for (char ch : str) {
		if (std::isalnum(ch) || ch == '#' || ch == '-' || ch == '>' || ch == ',' || ch == '.') {
			currentToken += ch;
		}
		else if (ch == '[' || ch == '(') {
			++bracketsCount;
			currentToken += ch;
		}
		else if (ch == ']' || ch == ')') {
			--bracketsCount;
			currentToken += ch;
		}
		else if (ch == ' ') {
			if (!bracketsCount && !currentToken.empty()) {
				result->push_back(currentToken);
				currentToken.clear();
			}
			else {
				ch += ' ';
			}

			continue;
		}
		else {
			delete result;
			throw std::invalid_argument("Invalid symbol found");
		}

		if (bracketsCount < 0) {
			delete result;
			throw std::invalid_argument("Invalid input");
		}
	}

	if (!currentToken.empty()) {
		result->push_back(currentToken);
	}

	return *result;
}

std::string System::popFirstWord(std::string& str) const {
	std::string output = "";

	for (char ch : str) {
		if (ch != ' ')
			output += ch;
		else
			break;
	}

	str = (str.c_str() + output.size());
	return output;
}
