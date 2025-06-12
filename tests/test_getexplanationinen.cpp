#include "test_getexplanationinen.h"
#include <QtTest/QTest>
#include <expression.h>

test_getExplanationInEn::test_getExplanationInEn(QObject *parent)
    : QObject{parent}
{}

void test_getExplanationInEn::getExplanationInEn()
{
    QFETCH(Expression, expression);
    QFETCH(QVariant, result);

    // Тип, который хранит QVariant
    int userType = result.userType();

    if (userType == qMetaTypeId<QString>()) {
        // Если ожидается строковый результат
        QString actualResult;
        try {
            actualResult = expression.getExplanationInEn();
        } catch (const TEException& e) {
            qDebug() << "Expected result:" << result.toString();
            qDebug() << "Actual error:" << TEException::ErrorTypeNames.value(e.getErrorType());
            QFAIL("Unexpected exception thrown when a string result was expected.");
        }

        QString expectedResult = result.toString();
        qDebug() << "Actual result:" << actualResult;
        qDebug() << "Expected result:" << expectedResult;

        if (actualResult != expectedResult) {
            QFAIL("String results mismatch");
        }
    }
    else if (userType == qMetaTypeId<ErrorType>()) {
        // Если ожидается ошибка
        try {
            QString actualResult = expression.getExplanationInEn();
            qDebug() << "Actual result:" << actualResult;
            qDebug() << "Expected error:" << TEException::ErrorTypeNames.value(result.value<ErrorType>());
            QFAIL("Expected an exception, but got a string result.");
        } catch (const TEException& e) {
            ErrorType actualError = e.getErrorType();
            ErrorType expectedError = result.value<ErrorType>();

            qDebug() << "Actual error:" << TEException::ErrorTypeNames.value(actualError);
            qDebug() << "Expected error:" << TEException::ErrorTypeNames.value(expectedError);

            if (actualError != expectedError) {
                QFAIL("Error types mismatch");
            }
        }
    }
    else {
        QFAIL("Unexpected type in 'result' column");
    }
}

void test_getExplanationInEn::getExplanationInEn_data()
{
    QTest::addColumn<Expression>("expression");
    QTest::addColumn<QVariant>("result");

    // Тест 1: Сложение двух констант
    QTest::newRow("addition-of-two-constants")
        << Expression("1 1 +", {}, {}, {}, {}, {}, {})
        << QVariant("sum of 1 and 1");

    // Тест 2: Сложение двух одинаковых переменных
    QTest::newRow("addition-of-two-identical-variables")
        << Expression(
               "appleCount appleCount +",
               {{"appleCount", Variable("appleCount", "int",
                                        "apple count")}},
               {}, {}, {}, {}, {})
        << QVariant("sum of apple count and apple count");

    // Тест 3: Сложение двух разных переменных
    QTest::newRow("addition-of-two-different-variables")
        << Expression(
               "warnings errors +",
               {{"warnings", Variable("warnings", "int",
                                      "program warnings")},
                {"errors", Variable("errors", "int",
                                    "his errors")}},
               {}, {}, {}, {}, {})
        << QVariant("sum of program warnings and his errors");

    // Тест 4: Вывод одной переменной
    QTest::newRow("output-single-variable")
        << Expression(
               "appleCount",
               {{"appleCount", Variable("appleCount", "int",
                                        "apple count")}},
               {}, {}, {}, {}, {})
        << QVariant("apple count");

    // Тест 5: Ввод переменной с унарной операцией
    QTest::newRow("unary-operation-on-variable")
        << Expression(
               "isApple !",
               {{"isApple", Variable("isApple", "bool",
                                     "apple")}},
               {}, {}, {}, {}, {})
        << QVariant("not apple");

    // Тест 6: Ввод переменной с двойным отрицанием
    QTest::newRow("double-negation-on-variable")
        << Expression(
               "isApple ! !",
               {{"isApple", Variable("isApple", "bool",
                                     "apple")}},
               {}, {}, {}, {}, {})
        << QVariant("apple");

    // Тест 7: Ввод неиспользуемой переменной
    QTest::newRow("unused-variable")
        << Expression(
               "1",
               {{"isApple", Variable("isApple", "bool",
                                     "apple")}},
               {}, {}, {}, {}, {})
        << QVariant::fromValue<ErrorType>(ErrorType::NeverUsedElement);

    // Тест 8: Ввод неиспользуемой функции
    QTest::newRow("unused-function")
        << Expression(
               "1",
               {},
               {{"getApple", Function("getApple", "int", 0, "get apples")}},
               {},
               {},
               {},
               {})
        << QVariant::fromValue<ErrorType>(ErrorType::NeverUsedElement);

    // Тест 9: Ввод неиспользуемого класса
    QTest::newRow("unused-class")
        << Expression(
               "1",
               {},
               {},
               {},
               {},
               {{"Apple", Class("Apple", {}, {})}},
               {})
        << QVariant::fromValue<ErrorType>(ErrorType::NeverUsedElement);

    // Тест 10: Ввод неиспользуемого поля класса
    QTest::newRow("unused-class")
        << Expression(
               "1",
               {},
               {},
               {},
               {},
               {{"Apple", Class("Apple", {}, {})}},
               {})
        << QVariant::fromValue<ErrorType>(ErrorType::NeverUsedElement);

    // Тест 11: Ввод неиспользуемой структуры
    QTest::newRow("unused-structure")
        << Expression(
               "1",
               {},
               {},
               {},
               {{"Apple", Structure("Apple",
                                    {{"count", Variable("count", "int", "count")}},
                                    {})}},
               {},
               {})
        << QVariant::fromValue<ErrorType>(ErrorType::NeverUsedElement);

    // Тест 12: Ввод неиспользуемого поля структуры
    QTest::newRow("unused-structure-field")
        << Expression(
               "newApple age .",
               {{"newApple", Variable("newApple", "Apple")}},
               {},
               {},
               {{"Apple", Structure("Apple",
                                    {{"age", Variable("age", "int", "age")}}, {})}},
               {},
               {})
        << QVariant::fromValue<ErrorType>(ErrorType::NeverUsedElement);

    // Тест 13: Ввод неиспользуемого объединения
    QTest::newRow("unused-union")
        << Expression(
               "1",
               {},
               {},
               {{"Apple", Union("Apple", {}, {})}},
               {},
               {},
               {})
        << QVariant::fromValue<ErrorType>(ErrorType::NeverUsedElement);

    // Тест 14: Ввод неиспользуемого поля объединения
    QTest::newRow("unused-union-field")
        << Expression(
               "newApple age .",
               {{"newApple", Variable("newApple", "Apple")}},
               {},
               {{"Apple", Union("Apple",
                                {{"age", Variable("age", "int", "age")}}, {})}},
               {},
               {})
        << QVariant::fromValue<ErrorType>(ErrorType::NeverUsedElement);

    // Тест 15: Ввод неиспользуемого перечисления
    QTest::newRow("unused-enum")
        << Expression(
               "1",
               {},
               {},
               {},
               {},
               {},
               {{"Fruits", Enum("Fruits", {})}})
        << QVariant::fromValue<ErrorType>(ErrorType::NeverUsedElement);

    // Тест 16: Ввод неиспользуемого значения перечисления
    QTest::newRow("unused-enum-value")
        << Expression(
               "curFruit Fruits Apple :: == ",
               {{"curFruit", Variable("curFruit", "Fruits")}},
               {},
               {},
               {},
               {},
               {{"Fruits", Enum("Fruits",
                                {{"Apple", "apple"},
                                 {"NotApple", "not apple"}})}})
        << QVariant::fromValue<ErrorType>(ErrorType::NeverUsedElement);

    // Тест 17: Ввод двух одинаковых полей у разных классов
    QTest::newRow("duplicate-fields-different-classes")
        << Expression(
               "newApple sort . newPinApple sort . == ",
               {{"newApple", Variable("newApple", "Apple", "apple")},
                {"newPinApple", Variable("newPinApple", "PinApple", "pineapple")}},
               {},
               {},
               {},
               {{"Apple", Class("Apple",
                                {{"sort", Variable("sort", "string", "apple sort")}})},
                {"PinApple", Class("PinApple",
                                   {{"sort", Variable("sort", "string", "pineapple sort")}})}},
               {})
        << QVariant("apple sort equal pineapple sort");

    // Тест 18: Ввод двух одинаковых полей у разных структур
    QTest::newRow("duplicate-fields-different-structures")
        << Expression(
               "newApple sort . newPinApple sort . == ",
               {{"newApple", Variable("newApple", "Apple", "apple")},
                {"newPinApple", Variable("newPinApple", "PinApple", "pineapple")}},
               {},
               {},
               {{"Apple", Structure("Apple",
                                    {{"sort", Variable("sort", "string", "apple sort")}})},
                {"PinApple", Structure("PinApple",
                                       {{"sort", Variable("sort", "string", "pineapple sort")}})}},
               {},
               {})
        << QVariant("apple sort equal pineapple sort");

    // Тест 19: Ввод двух одинаковых полей у разных объединений
    QTest::newRow("duplicate-fields-different-unions")
        << Expression(
               "newApple sort . newPinApple sort . == ",
               {{"newApple", Variable("newApple", "Apple", "apple")},
                {"newPinApple", Variable("newPinApple", "PinApple", "pineapple")}},
               {},
               {{"Apple", Union("Apple",
                                {{"sort", Variable("sort", "string", "apple sort")}})},
                {"PinApple", Union("PinApple",
                                   {{"sort", Variable("sort", "string", "pineapple sort")}})}},
               {},
               {})
        << QVariant("apple sort equal pineapple sort");

    // Тест 20: Ввод двух одинаковых значений у разных перечислений
    QTest::newRow("duplicate-values-different-enums")
        << Expression(
               "notFruitSort Fruit Sort :: != notFruitSort Vegetable Sort :: == &&",
               {{"notFruitSort", Variable("notFruitSort", "Sort", "not fruit sort")}},
               {},
               {},
               {},
               {},
               {{"Fruit", Enum("Fruit",
                               {{"Sort", "sort"}})},
                {"Vegetable", Enum("Vegetable",
                                   {{"Sort", "sort"}})}})
        << QVariant("not fruit sort not equal sort and not fruit sort equal sort");

    // Тест 21: Одинаковое описание у разных переменных
    QTest::newRow("duplicate-descriptions-different-variables")
        << Expression(
               "oleg victor +",
               {{"oleg", Variable("oleg", "string", "name")},
                {"victor", Variable("victor", "string", "name")}},
               {},
               {},
               {},
               {},
               {})
        << QVariant("concatenation of name and name");

    // Тест 22: Использование класса в выражении
    QTest::newRow("undefined-class-in-expression")
        << Expression(
               "Apple",
               {},
               {},
               {},
               {},
               {{"Apple", Class("Apple")}},
               {})
        << QVariant::fromValue<ErrorType>(ErrorType::UndefinedId);

    // Тест 23: Использование структуры в выражении
    QTest::newRow("undefined-structure-in-expression")
        << Expression(
               "Apple",
               {},
               {},
               {},
               {{"Apple", Structure("Apple")}},
               {},
               {})
        << QVariant::fromValue<ErrorType>(ErrorType::UndefinedId);

    // Тест 24: Использование объединения в выражении
    QTest::newRow("undefined-union-in-expression")
        << Expression(
               "Apple",
               {},
               {},
               {{"Apple", Union("Apple")}},
               {},
               {},
               {})
        << QVariant::fromValue<ErrorType>(ErrorType::UndefinedId);

    // Тест 25: Максимальное количество операций
    QTest::newRow("maximum-operations")
        << Expression(
               "1 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 +",
               {},
               {},
               {},
               {},
               {},
               {})
        << QVariant("sum of 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 and 1");

    // Тест 26: Пустые данные
    QTest::newRow("empty-data")
        << Expression(
               "",
               {},
               {},
               {},
               {},
               {},
               {})
        << QVariant("");

    // Тест 27: Максимальное количество операндов в функции
    QTest::newRow("maximum-operands-in-function")
        << Expression(
               "1 2 3 4 5 sum(5)",
               {},
               {{"sum", Function("sum", "int", 5, "sum for {1}, {2}, {3}, {4}, {5}")}},
               {},
               {},
               {},
               {})
        << QVariant("sum for 1, 2, 3, 4, 5");

    // Тест 28: Отсутствие операндов в функции
    QTest::newRow("function-without-operands")
        << Expression(
               "helloworld(0)",
               {},
               {{"helloworld", Function("helloworld", "void", 0, "print hello world")}},
               {},
               {},
               {},
               {})
        << QVariant("print hello world");

    // Тест 29: Вызов функции в параметрах функции
    QTest::newRow("function-in-function-parameters")
        << Expression(
               "1 4 max(2) 3 sum(2)",
               {},
               {{"sum", Function("sum", "int", 2, "sum for {1} and {2}")},
                {"max", Function("max", "int", 2, "maximum in {1} and {2}")}},
               {},
               {},
               {},
               {})
        << QVariant("sum for maximum in 1 and 4, 3");

    // Тест 30: Операция в параметре функции
    QTest::newRow("operation-in-function-parameter")
        << Expression(
               "1 1 + tostring(1)",
               {},
               {{"tostring", Function("tostring", "string", 1, "print {1}")}},
               {},
               {},
               {},
               {})
        << QVariant("print sum of 1 and 1");

    // Тест 31: Вызов функции класса
    QTest::newRow("class-function-call")
        << Expression(
               "oleg getAge(0) .",
               {{"oleg", Variable("oleg", "Human", "oleg")}},
               {},
               {},
               {},
               {{"Human", Class("Human", {},
                                {{"getAge", Function("getAge", "int", 0, "age")}})}},
               {})
        << QVariant("oleg’s age");

    // Тест 32: Вызов функции объединения
    QTest::newRow("union-function-call")
        << Expression(
               "oleg getAge(0) .",
               {{"oleg", Variable("oleg", "Human", "oleg")}},
               {},
               {{"Human", Union("Human", {},
                                {{"getAge", Function("getAge", "int", 0, "age")}})}},
               {},
               {},
               {})
        << QVariant("oleg’s age");

    // Тест 33: Вызов функции структуры
    QTest::newRow("structure-function-call")
        << Expression(
               "oleg getAge(0) .",
               {{"oleg", Variable("oleg", "Human", "oleg")}},
               {},
               {},
               {{"Human", Structure("Human", {},
                                    {{"getAge", Function("getAge", "int", 0, "age")}})}},
               {},
               {})
        << QVariant("oleg’s age");
    // Тест 34: Количество аргументов функции выражения не совпадает с количеством, указанным в функции
    QTest::newRow("function-argument-mismatch")
        << Expression(
               "tostring(1)",
               {},
               {{"tostring", Function("tostring", "string", 2, "print {1} and {2}")}},
               {},
               {},
               {},
               {})
        << QVariant::fromValue<ErrorType>(ErrorType::MissingOperand);

    // Тест 35: В выражение передается не обрабатываемая операция
    QTest::newRow("invalid-operation-symbol")
        << Expression(
               "1 1 $",
               {},
               {},
               {},
               {},
               {},
               {})
        << QVariant::fromValue<ErrorType>(ErrorType::InvalidSymbol);

    // Тест 36: Функция содержит в описании дублирующее слово в переменной
    QTest::newRow("function-with-redundant-word-in-description")
        << Expression(
               "s v t getDistance(2) =",
               {{"v", Variable("v", "speed car", "speed of car")},
                {"s", Variable("s", "distance", "distance traveled")},
                {"t", Variable("t", "time travel", "time taken for travel")}},
               {{"getDistance", Function("getDistance", "distance", 2, "assign distance by speed {1} to time {2}")}},
               {},
               {},
               {},
               {})
        << QVariant("assign distance by speed car to time travel");

    // Тест 37: Префиксная инкрементация
    QTest::newRow("prefix-increment")
        << Expression(
               "a ++_ 1 +",
               {{"a", Variable("a", "int", "cool value")}},
               {},
               {},
               {},
               {},
               {})
        << QVariant("increment cool value, then get sum of cool value and 1");

    // Тест 38: Постфиксная инкрементация
    QTest::newRow("postfix-increment")
        << Expression(
               "a _++ 1 +",
               {{"a", Variable("a", "int", "cool value")}},
               {},
               {},
               {},
               {},
               {})
        << QVariant("get sum of cool value and 1, then increment cool value");

    // Тест 39: Постфиксная и префиксная инкрементация разных переменных
    QTest::newRow("postfix-and-prefix-increment-different-vars")
        << Expression(
               "a _++ b ++_ +",
               {{"a", Variable("a", "int", "cool value")},
                {"b", Variable("b", "int", "not cool value")}},
               {},
               {},
               {},
               {},
               {})
        << QVariant("increment not cool value, then get sum of cool value and not cool value, then increment cool value");

    // Тест 40: Постфиксная и префиксная инкрементация одной переменной
    QTest::newRow("postfix-and-prefix-increment-same-var")
        << Expression(
               "a _++ ++_",
               {{"a", Variable("a", "int", "cool value")}},
               {},
               {},
               {},
               {},
               {})
        << QVariant::fromValue<ErrorType>(ErrorType::MultipleIncrementDecrement);

    // Тест 41: Отрицание операции сравнения
    QTest::newRow("negation-of-comparison-operation")
        << Expression(
               "a < b !",
               {{"a", Variable("a", "int", "cool value")},
                {"b", Variable("b", "int", "not cool value")}},
               {},
               {},
               {},
               {},
               {})
        << QVariant("cool value is not less than not cool value");

    // Тест 42: Несколько операций разности подряд
    QTest::newRow("multiple-subtraction-operations")
        << Expression(
               "1 1 - 1 -",
               {},
               {},
               {},
               {},
               {},
               {})
        << QVariant("difference of 1 and the sum of 1 and 1");

    // Тест 43: Несколько операций деления подряд
    QTest::newRow("multiple-division-operations")
        << Expression(
               "1 1 / 1 /",
               {},
               {},
               {},
               {},
               {},
               {})
        << QVariant("quotient of 1 and the product of 1 and 1");

    // Тест 44: Указатель на адрес
    QTest::newRow("pointer-to-address")
        << Expression(
               "a & *",
               {{"a", Variable("a", "int", "cool value")}},
               {},
               {},
               {},
               {},
               {})
        << QVariant("cool value");

    // Тест 45: Разыменование суммы
    QTest::newRow("dereferencing-sum")
        << Expression(
               "1 2 + 3 + *",
               {},
               {},
               {},
               {},
               {},
               {})
        << QVariant("get the element at index equivalent sum of elements (2+3) of pointer 1");
}
