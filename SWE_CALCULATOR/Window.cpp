#include "Window.h"
#include "ButtonFactory.h"
#include "wx/tokenzr.h"
#include "wx/sizer.h"
#include <cmath>
#include <stdexcept>


wxBEGIN_EVENT_TABLE(Window, wxFrame)
EVT_BUTTON(wxID_ANY, Window::OnButtonClicked)
wxEND_EVENT_TABLE()


Window::Window() : wxFrame(nullptr, wxID_ANY, "swe calculator", wxPoint(30, 30), wxSize(450, 550))
{
    display = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 10), wxSize(380, 40));

    int buttonWidth = 70;
    int buttonHeight = 50;
    int colSpace = 10;
    int rowSpace = 50;

    //number buttons
    for (int i = 0; i < 10; i++) {
        int col = colSpace + (i % 3) * (buttonWidth + 10);
        int row = rowSpace + (3 - i / 3) * (buttonHeight + 10);
        if (i == 0) {
            col = colSpace + buttonWidth + 10;
            row = rowSpace + 4 * (buttonHeight + 10);
        }
        numButtons[i] = ButtonFactory::CreateButton(this, wxString::Format("%d", i), wxPoint(col, row), wxSize(buttonWidth, buttonHeight));
    }

    //binary buttons
    wxString bin[] = { "+", "-", "*", "/","%" };
    for (int i = 0; i < 5; i++) {
        binButtons[i] = ButtonFactory::CreateButton(this, bin[i], wxPoint(colSpace + 3 * (buttonWidth + 10), rowSpace + i * (buttonHeight + 10)), wxSize(buttonWidth, buttonHeight));
    }

    //unary buttons
    wxString unary[] = { "sin", "cos", "tan" };
    for (int i = 0; i < 3; i++) {
		unaryButtons[i] = ButtonFactory::CreateButton(this, unary[i], wxPoint(colSpace + 4 * (buttonWidth + 10), rowSpace + i * (buttonHeight + 10)), wxSize(buttonWidth, buttonHeight));
	}

    //other buttons
    eqlButton = ButtonFactory::CreateButton(this, "=", wxPoint(colSpace + 2 * (buttonWidth + 10), rowSpace + 4 * (buttonHeight + 10)), wxSize(buttonWidth, buttonHeight));
    clrButton = ButtonFactory::CreateButton(this, "C", wxPoint(colSpace + 4 * (buttonWidth + 10), rowSpace + 3 * (buttonHeight + 10)), wxSize(buttonWidth, buttonHeight));
    delButton = ButtonFactory::CreateButton(this, "DEL", wxPoint(colSpace + 4 * (buttonWidth + 10), rowSpace + 4 * (buttonHeight + 10)), wxSize(buttonWidth, buttonHeight));
    decButton = ButtonFactory::CreateButton(this, ".", wxPoint(colSpace + 2 * (buttonWidth + 10), rowSpace + 3 * (buttonHeight + 10)), wxSize(buttonWidth, buttonHeight));
    negButton = ButtonFactory::CreateButton(this, "+/-", wxPoint(colSpace, rowSpace + 4 * (buttonHeight + 10)), wxSize(buttonWidth, buttonHeight));

}

//on button clicked event handler
void Window::OnButtonClicked(wxCommandEvent& evt) {
    wxButton* clickedButton = (wxButton*)evt.GetEventObject();
    if (clickedButton) {
        wxString label = clickedButton->GetLabel();
        wxString showValue = display->GetValue();
        //try/catch block to handle exceptions
        try {
            if (label >= "0" && label <= "9") {
                display->AppendText(label);
            }
            else if (label == "." && showValue.Find('.') == wxNOT_FOUND) {
                display->AppendText(label);
            }
            else if (label == "C") {
                display->Clear();
            }
            else if (label == "DEL") {
                if (!showValue.IsEmpty()) {
                    display->SetValue(showValue.RemoveLast());
                }
            }
            else if (label == "+" || label == "-" || label == "*" || label == "/" || label == "%") {
                display->AppendText(" " + label + " ");
            }
            else if (label == "sin" || label == "cos" || label == "tan") {
                display->SetValue(label + "(" + showValue + ")");
            }
            else if (label == "=") {
                double result = Calculate(showValue);
                display->SetValue(wxString::Format("%g", result));
            }
        } 
        catch (const std::exception& exception) {
			display->SetValue("Error");
		}
    }
}

//this concept was a doozy/discord and wxWidgets/tokenizing documentation ftw
//calculates the result of an expression using the shunting yard algorithm
double Window::Calculate(const wxString& expression)
{
    wxStringTokenizer tokenizer(expression, " ");
    std::vector<wxString> tokens;
    while (tokenizer.HasMoreTokens()) {
		tokens.push_back(tokenizer.GetNextToken());
	}
    //handle unary operators
    if (tokens.size() == 1) {
        if (tokens[0].StartsWith("sin(")) {
            double val = std::stod(tokens[0].Mid(4, tokens[0].length() - 5).ToStdString());
            return std::sin(val);
        }
        else if (tokens[0].StartsWith("cos(")) {
            double val = std::stod(tokens[0].Mid(4, tokens[0].length() - 5).ToStdString());
            return std::cos(val);
        }
        else if (tokens[0].StartsWith("tan(")) {
            double val = std::stod(tokens[0].Mid(4, tokens[0].length() - 5).ToStdString());
            return std::tan(val);
        }
        return std::stod(tokens[0].ToStdString());
    }
    //handle binary operators
    else if (tokens.size() == 3) {
        double left = std::stod(tokens[0].ToStdString());
        double right = std::stod(tokens[2].ToStdString());
        wxString op = tokens[1];

        if (op == "+") return left + right;
        if (op == "-") return left - right;
        if (op == "*") return left * right;
        //handle division by 0
        if (op == "/") {
            if (right == 0) throw std::exception("Division by zero");
			return left / right;
        }
        //handle mod by 0
        if (op == "%") {
            if (right == 0) throw std::runtime_error("Modulo by zero");
            return std::fmod(left, right);
        }
    }
    throw std::runtime_error("Invalid expression, try again");
}
