#include "Window.h"
#include "ButtonFactory.h"
#include "wx/tokenzr.h"
#include <cmath>


wxBEGIN_EVENT_TABLE(Window, wxFrame)
    EVT_BUTTON(wxID_ANY, Window::OnButtonClicked)
wxEND_EVENT_TABLE()


Window::Window() : wxFrame(nullptr, wxID_ANY, "swe calculator", wxDefaultPosition, wxSize(450, 500))
{
    CreateUI();
    this->SetMinSize(wxSize(450, 500));
}

//creating calculator display
void Window::CreateUI() {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    display = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 50), wxTE_RIGHT);
    mainSizer->Add(display, 0, wxEXPAND | wxALL, 10);

    wxGridSizer* buttonSizer = new wxGridSizer(5, 5, 5);
    
    buttonSizer->Add(ButtonFactory::CreateOpButton(this, "%"), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateFnctnButton(this, "sin"), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateFnctnButton(this, "cos"), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateFnctnButton(this, "tan"), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateButton(this, "C"), 0, wxEXPAND);

    buttonSizer->Add(ButtonFactory::CreateNumButton(this, 7), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateNumButton(this, 8), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateNumButton(this, 9), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateOpButton(this, "*"), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateOpButton(this, "/"), 0, wxEXPAND);

    buttonSizer->Add(ButtonFactory::CreateNumButton(this, 4), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateNumButton(this, 5), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateNumButton(this, 6), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateButton(this, "DEL"), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateOpButton(this, "-"), 0, wxEXPAND);

    buttonSizer->Add(ButtonFactory::CreateNumButton(this, 1), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateNumButton(this, 2), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateNumButton(this, 3), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateOpButton(this, "+"), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateButton(this, "="), 0, wxEXPAND);

    buttonSizer->Add(ButtonFactory::CreateNumButton(this, 0), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateButton(this, "."), 0, wxEXPAND);
    buttonSizer->Add(ButtonFactory::CreateButton(this, "+/-"), 0, wxEXPAND);
    
    mainSizer->Add(buttonSizer, 1, wxEXPAND | wxALL, 10);

    SetSizer(mainSizer);
}

void Window::OnButtonClicked(wxCommandEvent& evt) {
    wxButton* button = wxDynamicCast(evt.GetEventObject(), wxButton);
    if (button) {
        wxString label = button->GetLabel();
        wxString currentTxt = display->GetValue();

        if (label >= "0" && label <= "9" || label == ".") {
            display->AppendText(label);
        }
        else if (label == "-" || label == "/" || label == "*" || label == "+" || label == "%") {
            if ((isOperator(label) && currentTxt.EndsWith(label)) || (label == "." && currentTxt.Contains("."))) {
                return;
            }
            display->AppendText(" " + label + " ");
        }
        else if (label == "+/-") {
            if (!currentTxt.IsEmpty()) {
                if (currentTxt[0] == '-')
                    display->SetValue(currentTxt.Mid(1));
                else
                    display->SetValue("-" + currentTxt);
            }
        }
        else if (label == "sin" || label == "cos" || label == "tan") {
            display->AppendText(label + " ");
        }
        else if (label == "C") {
            display->Clear();
        }
        else if (label == "DEL") {
            if (!currentTxt.IsEmpty()) {
                display->SetValue(currentTxt.RemoveLast());
            }
        }
        else if (label == "=") {
            if (!currentTxt.IsEmpty()) {
                try {
                    if (isValidExpression(currentTxt)) 
                    {
                        double result = Calculate(currentTxt);
                        display->SetValue(wxString::Format("%.6f", result));
                    }
                    else {
                        display->SetValue("Invalid expression");
                    }
                }
                catch (const std::exception e) {
                    display->SetValue("Error: " + wxString(e.what()));
                }
            }
        }
    }
}

//helper functions for exception handling
bool Window::isOperator(const wxString& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
}
bool Window::isValidExpression(const wxString& expression) {
    if (expression.IsEmpty() || isOperator(expression[0]) || isOperator(expression.Last())) {
        return false;
    }
    for (size_t i = 1; i < expression.Length(); ++i) {
        if (isOperator(expression[i]) && isOperator(expression[i - 1])) {
            return false;
        }
    }
    int decimal = 0;
    for (size_t i = 0; i < expression.Length(); ++i) {
        if (expression[i] == '.') {
            decimal++;
        }
        else if (isOperator(expression[i])) {
            decimal = 0;
        }
        if (decimal > 1) {
            return false;
        }
    }
    return true;
}

double Window::Calculate(const wxString& expression) {
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
