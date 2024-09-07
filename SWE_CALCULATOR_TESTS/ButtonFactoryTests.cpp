#include "../SWE_CALCULATOR/SWE_CALCULATOR/ButtonFactory.h"
#include "../SWE_CALCULATOR/SWE_CALCULATOR/Window.h"
#include "CppUnitTest.h"
#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ButtonFactoryTests
{
	TEST_CLASS(ButtonFactoryTests)
	{
	public:
		//struggled getting the pathing just right, which is such a bummer, but I tried my hardest

		TEST_METHOD(TestCreateNumButton0)
		{
			wxWindow* parent = new wxFrame(nullptr, wxID_ANY, "Test");
			wxButton* button = ButtonFactory::CreateNumButton(parent, 0);
			Assert::IsNotNull(button);
			Assert::AreEqual("0", button->GetLabel().ToStdString().c_str());
			delete parent;
		}

		TEST_METHOD(TestCreateNumButton9)
		{
			wxWindow* parent = new wxFrame(nullptr, wxID_ANY, "Test");
			wxButton* button = ButtonFactory::CreateNumButton(parent, 9);
			Assert::IsNotNull(button);
			Assert::AreEqual("3", button->GetLabel().ToStdString().c_str());
			delete parent;
		}

		TEST_METHOD(TestCreateOpButtonPlus)
		{
			wxWindow* parent = new wxFrame(nullptr, wxID_ANY, "Test");
			wxButton* button = ButtonFactory::CreateNumButton(parent, "+");
			Assert::IsNotNull(button);
			Assert::AreEqual("+", button->GetLabel().ToStdString().c_str());
			delete parent;
		}

		TEST_METHOD(TestCreateOpButtonMinus)
		{
			wxWindow* parent = new wxFrame(nullptr, wxID_ANY, "Test");
			wxButton* button = ButtonFactory::CreateNumButton(parent, "-");
			Assert::IsNotNull(button);
			Assert::AreEqual("-", button->GetLabel().ToStdString().c_str());
			delete parent;
		}

		TEST_METHOD(TestCreateOpButtonSin)
		{
			wxWindow* parent = new wxFrame(nullptr, wxID_ANY, "Test");
			wxButton* button = ButtonFactory::CreateNumButton(parent, "sin");
			Assert::IsNotNull(button);
			Assert::AreEqual("sin", button->GetLabel().ToStdString().c_str());
			delete parent;
		}

		TEST_METHOD(TestCreateOpButtonCos)
		{
			wxWindow* parent = new wxFrame(nullptr, wxID_ANY, "Test");
			wxButton* button = ButtonFactory::CreateNumButton(parent, "cos");
			Assert::IsNotNull(button);
			Assert::AreEqual("cos", button->GetLabel().ToStdString().c_str());
			delete parent;
		}

		TEST_METHOD(TestCreateOpButtonEquals)
		{
			wxWindow* parent = new wxFrame(nullptr, wxID_ANY, "Test");
			wxButton* button = ButtonFactory::CreateNumButton(parent, "=");
			Assert::IsNotNull(button);
			Assert::AreEqual("=", button->GetLabel().ToStdString().c_str());
			delete parent;
		}

		TEST_METHOD(TestCreateOpButtonClear)
		{
			wxWindow* parent = new wxFrame(nullptr, wxID_ANY, "Test");
			wxButton* button = ButtonFactory::CreateNumButton(parent, "C");
			Assert::IsNotNull(button);
			Assert::AreEqual("C", button->GetLabel().ToStdString().c_str());
			delete parent;
		}

		TEST_METHOD(TestCreateOpButtonDecimal)
		{
			wxWindow* parent = new wxFrame(nullptr, wxID_ANY, "Test");
			wxButton* button = ButtonFactory::CreateNumButton(parent, ".");
			Assert::IsNotNull(button);
			Assert::AreEqual(".", button->GetLabel().ToStdString().c_str());
			delete parent;
		}

		TEST_METHOD(TestCreateOpButtonNegative)
		{
			wxWindow* parent = new wxFrame(nullptr, wxID_ANY, "Test");
			wxButton* button = ButtonFactory::CreateNumButton(parent, "+/-");
			Assert::IsNotNull(button);
			Assert::AreEqual("+/-", button->GetLabel().ToStdString().c_str());
			delete parent;
		}
	};
}