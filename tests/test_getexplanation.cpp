#include "test_getexplanation.h"
#include <QtTest/QTest>
#include <expression.h>
#include <expressiontranslator.h>
#include <QString>
#include <QHash>
#include <QTest>


test_getExplanation::test_getExplanation(QObject *parent)
    : QObject{parent}
{}

void test_getExplanation::getExplanation()
{
    QFETCH(QString, description);
    QFETCH(QList<QString>, arguments);
    QFETCH(QString, expectedResult);

    try {
        // Получаем результат вызова функции
        QString actualResult = ExpressionTranslator::getExplanation(description, arguments);

        // Выводим результаты для отладки
        qDebug() << "Description:" << description;
        qDebug() << "Arguments:";
        for (int i = 0; i < arguments.size(); ++i) {
            qDebug() << QString("  Argument %1: %2").arg(i + 1).arg(arguments[i]);
        }
        qDebug() << "Actual result:" << actualResult;
        qDebug() << "Expected result:" << expectedResult;

        // Сравниваем результаты
        if (actualResult != expectedResult) {
            QString errorMessage = QString("Test failed");
            QFAIL(qPrintable(errorMessage));
        }
    } catch (const TEException &error) {
        // Если было выброшено исключение, проверяем тип ошибки
        QFETCH(ErrorType, expectedError);

        qDebug() << "Caught TEException with error type:" << TEException::ErrorTypeNames.value(error.getErrorType(), "UnknownError");
        if (error.getErrorType() != expectedError) {
            QString errorMessage = QString("Test failed");
            QFAIL(qPrintable(errorMessage));
        }
    }
}

void test_getExplanation::getExplanation_data()
{    
    QTest::addColumn<QString> ("description");
    QTest::addColumn<QList<QString>> ("arguments");
    QTest::addColumn<QString> ("expectedResult");
    QTest::addColumn<ErrorType>("expectedError");

    // Тест 1: В строке только одно место для замены
    QTest::newRow("single-placeholder")
        << "{1}"
        << QList<QString>{"hello"}
        << "hello";

    // Тест 2: В строке только одно место для замены, аргумент пустой
    QTest::newRow("single-placeholder-empty-argument")
        << "{1}"
        << QList<QString>{""}
        << "{1}";

    // Тест 3: В строке нет мест для замены
    QTest::newRow("no-placeholder")
        << "hello"
        << QList<QString>{"hello"}
        << "hello";

    // Тест 4: В строке место для замены с неподходящим форматом
    QTest::newRow("invalid-placeholder")
        << "{hello}"
        << QList<QString>{"hello"}
        << "{hello}";

    // Тест 5: В строке одно место для замены и подстрока
    QTest::newRow("placeholder-with-substring")
        << "{1} world!"
        << QList<QString>{"hello"}
        << "hello world!";

    // Тест 6: Строка пустая, аргументов нет
    QTest::newRow("empty-string-no-arguments")
        << ""
        << QList<QString>{}
        << "";

    // Тест 8: В строке два места для замены, аргументы содержат строки с местом для замены, не хватает аргументов для замены
    QTest::newRow("missing-replacement-arguments")
        << "{1} {3}"
            << QList<QString>{"{2}", "{4}"} << ""
        << ErrorType::MissingReplacementArguments;

    // Тест 9: В строке два места для замены, аргументы содержат строки с местом и обычной строкой
    QTest::newRow("mixed-placeholders-and-strings")
        << "{1} {2}"
        << QList<QString>{"{2}", "hello"}
        << "{2} hello";

    // Тест 10: Строка содержит только место для замены второго аргумента
    QTest::newRow("second-placeholder-only")
        << "{2}"
        << QList<QString>{"hello", "world!"}
        << "world!";

    // Тест 11: Строка содержит подстроку и место для замены первого аргумента в конце строки
    QTest::newRow("substring-placeholder-end")
        << "hello{1}"
        << QList<QString>{"world!"}
        << "helloworld!";

    // Тест 12: Строка содержит подстроку и место для замены первого аргумента в начале строки
    QTest::newRow("substring-placeholder-start")
        << "{1}world!"
        << QList<QString>{"hello"}
        << "helloworld!";

    // Тест 13: Строка содержит вложенные места для замены, два аргумента пустые
    QTest::newRow("nested-placeholders-with-empty-arguments")
        << "{3{2{1}}}"
        << QList<QString>{"", "", "hello!"}
        << "{3{2}}";

    // Тест 14: Строка содержит места для замены с подстановкой аргументов в обратном порядке
    QTest::newRow("reversed-placeholders")
        << "{2} {1}"
        << QList<QString>{"hello", "world!"}
        << "world! hello";

    // Тест 15: Строка содержит два места для замены первого аргумента
    QTest::newRow("duplicate-placeholder")
        << "{1} {1}"
        << QList<QString>{"hello!"}
        << "hello! hello!";

    // Тест 16: Строка и аргумент содержат место для замены
    QTest::newRow("string-and-argument-placeholder")
        << "{1}"
        << QList<QString>{"{1}"}
        << "{1}";

    // Тест 17: Строка содержит место для замены, аргумент содержит два места для замены
    QTest::newRow("placeholder-with-nested-placeholders")
        << "{1}"
        << QList<QString>{"{1} {1}"}
        << "{1} {1}";

}

