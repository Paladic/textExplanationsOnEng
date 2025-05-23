#include <QCoreApplication>
#include <QTest>
#include "test_isfunction.h"
int runTest(int argc, char *argv[]) //-- Нужно, чтобы парсер тестов нашёл этот тест, поэтому запускаем мы его из main
{

    int result = 0;

    try {
        test_isFunction function;
        result |= QTest::qExec(&function, argc, argv);
    } catch (...) {}

    return result;
}

#define TESTS
#include "../textExplanationsOnEng/main.cpp"






