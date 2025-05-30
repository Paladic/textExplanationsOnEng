#include "test_removeduplicates.h"
#include <QtTest/QTest>
#include <expression.h>


test_removeDuplicates::test_removeDuplicates(QObject *parent)
    : QObject{parent}
{}

void test_removeDuplicates::removeDuplicates()
{
    QFETCH(QString, string);
    QFETCH(QString, result);

    // Выполняем удаление дубликатов
    QString actualResult = Expression::removeDuplicates(string);

    // Сравниваем результаты
    if (actualResult != result) {
        qDebug() << "Actual result: " << actualResult;
        qDebug() << "Expected result:" << result;
        QFAIL("Test failed.");
    }
}

void test_removeDuplicates::removeDuplicates_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    // Test 1: Строка содержит одно слово
    QTest::newRow("single-word")
        << "word"
        << "word";

    // Test 2: Пустая строка
    QTest::newRow("empty-string")
        << ""
        << "";

    // Test 3: Два одинаковых слова подряд
    QTest::newRow("two-identical-words-consecutive")
        << "word word"
        << "word";

    // Test 4: Два одинаковых слова подряд с разным регистром
    QTest::newRow("two-identical-words-different-case")
        << "Word word"
        << "Word";

    // Test 5: Три одинаковых слова подряд с разным регистром
    QTest::newRow("three-identical-words-different-case")
        << "Word word word"
        << "Word";

    // Test 6: Два одинаковых слова, не стоящих рядом
    QTest::newRow("two-identical-words-non-consecutive")
        << "My word is not your word"
        << "My word is not your word";

    // Test 7: Два одинаковых слова, не стоящих рядом (короткая строка)
    QTest::newRow("two-identical-words-separated")
        << "word to word"
        << "word to word";

    // Test 8: Второе слово является подстрокой первого
    QTest::newRow("second-word-is-substring-of-first")
        << "words word"
        << "words word";

    // Test 9: Первое слово является подстрокой второго
    QTest::newRow("first-word-is-substring-of-second")
        << "word words"
        << "word words";

    // Test 10: Строка не содержит одинаковых слов
    QTest::newRow("no-duplicate-words")
        << "Hello word"
        << "Hello word";

    // Test 11: Два одинаковых слова подряд, разделенных запятой
    QTest::newRow("two-identical-words-separated-by-comma")
        << "word, word"
        << "word";

    // Test 12: Два не разделенных одинаковых слова
    QTest::newRow("two-identical-words-not-separated")
        << "wordword"
        << "wordword";
}
