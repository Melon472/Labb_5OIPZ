#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\andre\source\repos\Labb_2\Labb_2\Source.cpp" // Замініть на ваш шлях

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    TEST_CLASS(UnitTests)
    {
    public:
        TEST_METHOD(CalculateY_XLessThanOrEqualZero)
        {
            double x = -5.0;
            int n = 5;

            double expected = 1.0;
            for (int i = 0; i < n - 1; ++i) {
                expected *= (i * i * i) + i;
            }

            double result = calculateY(x, n);
            Assert::AreEqual(expected, result, 0.0001, L"Помилка в обчисленні для x <= 0");
        }

        TEST_METHOD(CalculateY_XGreaterThanZero)
        {
            double x = 2.0;
            int n = 0;

            double expected = 0.0;
            for (int i = 0; i < n - 1; ++i) {
                for (int j = 0; j < n - 1; ++j) {
                    if (i == 0 && j == 0) continue;
                    expected += x / (i + j);
                }
            }

            double result = calculateY(x, n);
            Assert::AreEqual(expected, result, 0.0001, L"Помилка в обчисленні для x > 0");
        }

        TEST_METHOD(CalculateY_InvalidN)
        {
            double x = 2.0;
            int n = 0; 

            auto func = [&]() { calculateY(x, n); };
            Assert::ExpectException<std::invalid_argument>(func, L"Не було згенеровано виключення для n <= 4");
        }

        TEST_METHOD(FileWrite_Test)
        {
            ofstream file("test_results.txt");
            Assert::IsTrue(file.is_open(), L"Файл не вдалося відкрити");

            double x = 0.0;
            int n = 5;
            double y = calculateY(x, n);

            file << "x: " << x << " Y: " << y << endl;
            file.close();

            ifstream checkFile("test_results.txt");
            Assert::IsTrue(checkFile.is_open(), L"Файл не вдалося прочитати");
            string line;
            getline(checkFile, line);
            checkFile.close();

            Assert::IsFalse(line.empty(), L"Результати не записані у файл");
        }
    };
}
