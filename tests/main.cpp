#include <QCoreApplication>
#include <QTest>
#include "test_isfunction.h"
#include "test_expressiontonodes.h"
#include "test_getexplanation.h"
#include "test_getexplanationinen.h"
#include "test_iscustomtypewithfileds.h"
#include "test_isidentifier.h"
#include "test_removeconsecutiveduplicates.h"
#include "test_toexplanation.h"
#include "test_isreducibleunaryselfinverse.h"

int runTest(int argc, char *argv[]) //-- Нужно, чтобы парсер тестов нашёл этот тест, поэтому запускаем мы его из main
{

    int result = 0;

    try {
        test_isFunction function;
        result |= QTest::qExec(&function, argc, argv);
    } catch (...) {}

    try {
        test_expressionToNodes expressionToNodes;
        result |= QTest::qExec(&expressionToNodes, argc, argv);
    } catch (...) {}

    try {
        test_getExplanation getExplanation;
        result |= QTest::qExec(&getExplanation, argc, argv);
    } catch (...) {}

    try {
        test_getExplanationInEn getExplanationInEn;
        result |= QTest::qExec(&getExplanationInEn, argc, argv);
    } catch (...) {}

    try {
        test_isCustomTypeWithFileds customTypeWithFields;
        result |= QTest::qExec(&customTypeWithFields, argc, argv);
    } catch (...) {}

    try {
        test_isIdentifier isIdentifier;
        result |= QTest::qExec(&isIdentifier, argc, argv);
    } catch (...) {}

    try {
        test_removeConsecutiveDuplicates removeConsecutiveDuplicates;
        result |= QTest::qExec(&removeConsecutiveDuplicates, argc, argv);
    } catch (...) {}

    try {
        test_toExplanation toExplanation;
        result |= QTest::qExec(&toExplanation, argc, argv);
    } catch (...) {}

    try {
        test_isReducibleUnarySelfInverse isReducibleUnarySelfInverse;
        result |= QTest::qExec(&isReducibleUnarySelfInverse, argc, argv);
    } catch (...) {}

    return result;
}

#define TESTS
#include "../textExplanationsOnEng/main.cpp"
