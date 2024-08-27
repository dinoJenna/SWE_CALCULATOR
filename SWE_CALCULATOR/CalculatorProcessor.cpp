#include "CalculatorProcessor.h"
#include "wx/tokenzr.h"
#include <cmath>
#include <stdexcept>

Singleton* Singleton::_instance = 0; 
Singleton::Singleton() {}

Singleton* Singleton::Instance() {
	if (_instance == 0) {
		_instance = new Singleton;
	}
	return _instance;
}

//carried old calculate from Window class
double Singleton::Calculate(const wxString& expression) {
	wxStringTokenizer tokenizer(expression, " ");

    if (!tokenizer.HasMoreTokens())
        throw std::runtime_error("Empty expression");

    wxString token = tokenizer.GetNextToken();

    if (token == "sin" || token == "cos" || token == "tan") {
        double val = wxAtof(tokenizer.GetNextToken());
        if (token == "sin") return std::sin(val);
        if (token == "cos") return std::cos(val);
        if (token == "tan") return std::tan(val);
    }

    double left = wxAtof(token);

    if (!tokenizer.HasMoreTokens())
        return left;

    token = tokenizer.GetNextToken();

    if (!tokenizer.HasMoreTokens())
        throw std::runtime_error("Operator missing second operand");

    double right = wxAtof(tokenizer.GetNextToken());

    if (token == "+") return left + right;
    if (token == "-") return left - right;
    if (token == "*") return left * right;
    if (token == "/") {
        if (right == 0) throw std::runtime_error("Division by zero");
        return left / right;
    }
    if (token == "%") {
        if (right == 0) throw std::runtime_error("Mod by zero");
        return std::fmod(left, right);
    }
    throw std::runtime_error("Invalid operation");
}
