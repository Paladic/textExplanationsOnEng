#include "test_isfunction.h"
#include <QtTest/QTest>
#include <expression.h>

test_isFunction::test_isFunction(QObject *parent)
    : QObject{parent}
{}

void test_isFunction::isFunction()
{
    QFETCH(QString, string);
    QFETCH(bool, result);

    QCOMPARE(Expression::isFunction(string), result);
}

void test_isFunction::isFunction_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<bool>("result");

    QTest::newRow("function-has-1-argument") << "factorial(1)" << true;
    QTest::newRow("function-has-no-arguments") << "helloWorld(0)" << true;
    QTest::newRow("function-with-multiple-arguments") << "sum(3,4)" << false;
    QTest::newRow("function-has-string-argument") << "printf(oleg)" << false;
    QTest::newRow("space-between-function-and-arguments") << "helloWorld (0)" << false;
    QTest::newRow("operand-in-parentheses") << "(3)" << false;
    QTest::newRow("regular-string-without-arguments") << "helloWorld" << false;
    QTest::newRow("empty-string") << "" << false;
    QTest::newRow("function-name-in-cyrillic") << "факториал(1)" << false;
}
