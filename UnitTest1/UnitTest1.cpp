#include "pch.h"
#include "CppUnitTest.h"
#include <sstream>
#include <iostream>
#include "../Lab10.3/Lab10.3.cpp" // Шлях до реалізації функції Create

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
    TEST_CLASS(UnitTest_CreateFunction)
    {
    public:

        TEST_METHOD(TestCreateFunction)
        {
            const int N = 2;
            Enterprise enterprises[N];

            // Імітуємо введення користувача
            std::istringstream input("123456789\n1\n2\nJohn Doe\nJane Smith\n987654321\n2\n1\nAlice Wonderland\n");
            std::streambuf* cinbuf = std::cin.rdbuf(); // Зберігаємо буфер cin
            std::cin.rdbuf(input.rdbuf()); // Перенаправляємо std::cin на наш потік

            Create(enterprises, N);

            // Відновлюємо стандартний ввід
            std::cin.rdbuf(cinbuf);

            // Перевірка першого підприємства
            Assert::AreEqual(std::string("123456789"), enterprises[0].mobilePhone);
            Assert::AreEqual(1, enterprises[0].numBuilding);
            Assert::AreEqual(2, enterprises[0].employeeCount);
            Assert::AreEqual(std::string("John Doe"), enterprises[0].employees[0]);
            Assert::AreEqual(std::string("Jane Smith"), enterprises[0].employees[1]);

            // Перевірка другого підприємства
            Assert::AreEqual(std::string("987654321"), enterprises[1].mobilePhone);
            Assert::AreEqual(2, enterprises[1].numBuilding);
            Assert::AreEqual(1, enterprises[1].employeeCount);
            Assert::AreEqual(std::string("Alice Wonderland"), enterprises[1].employees[0]);
        }
    };
}
