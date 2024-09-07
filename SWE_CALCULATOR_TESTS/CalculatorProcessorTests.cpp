#include "../SWE_CALCULATOR/SWE_CALCULATOR/CalculatorProcessor.h"
#include "CppUnitTest.h"
#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorProcessorTests
{
	TEST_CLASS(CalculatorProcessorTests)
	{
	public:

		TEST_METHOD(TestAddition)
		{
			double result = Singleton::Instance()->Calculate("2 + 3");
			Assert::AreEqual(5.0, result, 0.0001);
		}

		TEST_METHOD(TestSubtraction)
		{
			double result = Singleton::Instance()->Calculate("5 - 3");
			Assert::AreEqual(2.0, result, 0.0001);
		}

		TEST_METHOD(TestMultiplication)
		{
			double result = Singleton::Instance()->Calculate("4 * 5");
			Assert::AreEqual(20.0, result, 0.0001);
		}

		TEST_METHOD(TestDivision)
		{
			double result = Singleton::Instance()->Calculate("10 / 2");
			Assert::AreEqual(5.0, result, 0.0001);
		}

		TEST_METHOD(TestModulo)
		{
			double result = Singleton::Instance()->Calculate("7 % 3");
			Assert::AreEqual(1.0, result, 0.0001);
		}

		TEST_METHOD(TestSin)
		{
			double result = Singleton::Instance()->Calculate("sin 0");
			Assert::AreEqual(0.0, result, 0.0001);
		}

		TEST_METHOD(TestCos)
		{
			double result = Singleton::Instance()->Calculate("cos 0");
			Assert::AreEqual(1.0, result, 0.0001);
		}

		TEST_METHOD(TestTan)
		{
			double result = Singleton::Instance()->Calculate("tan 0");
			Assert::AreEqual(0.0, result, 0.0001);
		}

		TEST_METHOD(TestDivisionByZero)
		{
			auto func = [] { Singleton::Instance()->Calculate("5 / 0"); };
			Assert::ExpectException<std::runtime_error>(func);
		}

		TEST_METHOD(InvalidExpression)
		{
			auto func = [] { Singleton::Instance()->Calculate("2 + + 3"); };
			Assert::ExpectException<std::runtime_error>(func);
		}
	};
}