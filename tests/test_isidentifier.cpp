#include "test_isidentifier.h"
#include <QtTest/QTest>
#include <expression.h>


test_isIdentifier::test_isIdentifier(QObject *parent)
    : QObject{parent}
{}

void test_isIdentifier::isIdentifier()
{
    QFETCH(QString, string);
    QFETCH(bool, result);

    QCOMPARE(Expression::isIdentifier(string), result);
}

void test_isIdentifier::isIdentifier_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<bool>("result");
    QTest::newRow("first-latin-character") << "a" << true;
    QTest::newRow("last-latin-character") << "z" << true;
    QTest::newRow("single-uppercase-latin-character") << "V" << true;
    QTest::newRow("contains-special-character-underscore") << "_" << true;
    QTest::newRow("contains-single-digit") << "1" << false;
    QTest::newRow("contains-minimum-range-digit") << "a0" << true;
    QTest::newRow("contains-maximum-range-digit") << "a9" << true;
    QTest::newRow("starts-with-underscore-and-ends-with-latin") << "_z" << true;
    QTest::newRow("empty-string") << "" << false;
    QTest::newRow("only-invalid-character") << "$" << false;
    QTest::newRow("ends-with-invalid-character") << "a$" << false;
    QTest::newRow("contains-invalid-character-in-middle") << "a$a" << false;
    QTest::newRow("contains-cyrillic-letter") << "Ъ" << false;
}
