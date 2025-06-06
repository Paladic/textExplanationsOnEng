#include "qobject.h"
#include "test_toexplanation.h"
#include "expression.h"
#include "expressionnode.h"
#include "qtestcase.h"
#include "codeentity.h"
#include "teexception.h"
#include <QString>
#include <QHash>
#include <QTest>

test_toExplanation::test_toExplanation(QObject *parent)
    : QObject{parent}
{}

void test_toExplanation::toExplanation()
{
    QFETCH(Expression, expression);
    QFETCH(ExpressionNode*, node);
    QFETCH(QString, className);
    QFETCH(OperationType, parentOperType);
    QFETCH(QString, expectedExplanation);

    try {
        QString result = expression.ToExplanation(node, className, parentOperType);
        qDebug() << "Actual Explanation: " << result;
        qDebug() << "Expected Explanation: " << expectedExplanation;

        if (result != expectedExplanation) {
            QFAIL("Test failed.");
        }
    } catch (const TEException &error) {
        QFETCH(ErrorType, expectedError);
        qDebug() << "Caught Exception:" << TEException::ErrorTypeNames.value(error.getErrorType());
        qDebug() << "Expected Error: " << TEException::ErrorTypeNames.value(expectedError);

        if (error.getErrorType() != expectedError) {
            QFAIL("Test failed.");
        }
    }
}

void test_toExplanation::toExplanation_data()
{
    QTest::addColumn<Expression>("expression");
    QTest::addColumn<ExpressionNode*>("node");
    QTest::addColumn<QString>("className");
    QTest::addColumn<OperationType>("parentOperType");
    QTest::addColumn<QString>("expectedExplanation");
    QTest::addColumn<ErrorType>("expectedError");

    // Тест 1: Одна операция
    {
        Expression expression("1 1 +", {});
        ExpressionNode* node = new ExpressionNode(EntityType::Operation, "+",
                                                  new ExpressionNode(EntityType::Const, "1"),
                                                  new ExpressionNode(EntityType::Const, "1"), "", OperationType::Addition);
        QString explanation = "sum of 1 and 1";

        QTest::newRow("single-operation")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 2: Операция повторяется несколько раз
    {
        Expression expression("1 1 + 1 +", {});
        ExpressionNode* node = new ExpressionNode(EntityType::Operation, "+",
                                                  new ExpressionNode(EntityType::Operation, "+",
                                                                     new ExpressionNode(EntityType::Const, "1"),
                                                                     new ExpressionNode(EntityType::Const, "1"), "", OperationType::Addition),
                                                  new ExpressionNode(EntityType::Const, "1"), "", OperationType::Addition);
        QString explanation = "sum of 1, 1 and 1";

        QTest::newRow("repeated-operation")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 3: Один операнд
    {
        Expression expression("1", {});
        ExpressionNode* node = new ExpressionNode(EntityType::Const, "1");
        QString explanation = "1";

        QTest::newRow("single-operand")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 4: Двойная логическая операция, которая должна сократиться
    {
        Expression expression("1 ! !", {});
        ExpressionNode* node = new ExpressionNode(EntityType::Operation, "!",
                                                  new ExpressionNode(EntityType::Operation, "!",
                                                                     new ExpressionNode(EntityType::Const, "1"), nullptr, "", OperationType::Not),
                                                  nullptr, "", OperationType::Not);

        QString explanation = "1";

        QTest::newRow("double-logical-operation")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 5: Префиксный инкремент
    {
        Expression expression(
            "a ++_",
            {{"a", Variable("a", "int", "number of days")}},
            {}, {}, {}, {}, {}
            );

        ExpressionNode* node = new ExpressionNode(EntityType::Operation, "++_",
                                                  new ExpressionNode(EntityType::Variable, "a"),
                                                  nullptr, "", OperationType::PrefixIncrement);

        QString explanation = "increment number of days";

        QTest::newRow("prefix-increment")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 6: Постфиксный инкремент
    {
        Expression expression(
            "a _++",
            {{"a", Variable("a", "int", "number of days")}},
            {}, {}, {}, {}, {}
            );

        ExpressionNode* node = new ExpressionNode(EntityType::Operation, "_++",
                                                  new ExpressionNode(EntityType::Variable, "a"),
                                                  nullptr, "", OperationType::PostfixDecrement);

        QString explanation = "increment number of days";

        QTest::newRow("postfix-increment")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 7: Операция операнда с константой
    {
        Expression expression(
            "1 a +",
            {{"a", Variable("a", "int", "a")}},
            {}, {}, {}, {}, {}
            );

        ExpressionNode* node = new ExpressionNode(EntityType::Operation, "+",
                                                  new ExpressionNode(EntityType::Const, "1"),
                                                  new ExpressionNode(EntityType::Variable, "a"), "", OperationType::Addition);

        QString explanation = "sum of 1 and a";

        QTest::newRow("operand-operation-constant")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 8: Операция поля класса с переменной
    {
        Expression expression(
            "chel age . a +",
            {{"a", Variable("a", "int", "number of days")},
             {"chel", Variable("chel", "Human", "chel")}},
            {}, {}, {},
            {{"Human", Class("Human",
                             {{"age", Variable("age", "int", "age")}})}},
            {}
            );

        ExpressionNode* node = new ExpressionNode(EntityType::Operation, "+",
                                                  new ExpressionNode(EntityType::Operation, ".",
                                                                     new ExpressionNode(EntityType::Variable, "chel", nullptr, nullptr, "Human"),
                                                                     new ExpressionNode(EntityType::Variable, "age", nullptr, nullptr, "int"), "", OperationType::FieldAccess),
                                                  new ExpressionNode(EntityType::Variable, "a"), "", OperationType::Addition);

        QString explanation = "sum of chel’s age and number of days";

        QTest::newRow("class-field-operation-variable")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 9: Операция с полем структуры и переменной
    {
        Expression expression(
            "chel age . a +",
            {{"a", Variable("a", "int", "number of days")},
             {"chel", Variable("chel", "Human", "chel")}},
            {}, {},
            {{"Human", Structure("Human",
                                 {{"age", Variable("age", "int", "age")}})}},
            {}, {}
            );
        
        ExpressionNode* node = new ExpressionNode(EntityType::Operation, "+",
                                                  new ExpressionNode(EntityType::Operation, ".",
                                                                     new ExpressionNode(EntityType::Variable, "chel", nullptr, nullptr, "Human"),
                                                                     new ExpressionNode(EntityType::Variable, "age", nullptr, nullptr, "int"), "", OperationType::FieldAccess),
                                                  new ExpressionNode(EntityType::Variable, "a"), "", OperationType::Addition);

        QString explanation = "sum of chel’s age and number of days";

        QTest::newRow("structure-field-operation-variable")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 10: Операция с полем объединения и переменной
    {
        Expression expression(
            "chel age . a +",
            {{"a", Variable("a", "int", "number of days")},
             {"chel", Variable("chel", "Human", "chel")}},
            {},
            {{"Human", Union("Human",
                             {{"age", Variable("age", "int", "age")}})}},
            {}, {}, {}
            );

        ExpressionNode* node = new ExpressionNode(EntityType::Operation, "+",
                                                  new ExpressionNode(EntityType::Operation, ".",
                                                                     new ExpressionNode(EntityType::Variable, "chel", nullptr, nullptr, "Human"),
                                                                     new ExpressionNode(EntityType::Variable, "age", nullptr, nullptr, "int"), "", OperationType::FieldAccess),
                                                  new ExpressionNode(EntityType::Variable, "a"), "", OperationType::Addition);

        QString explanation = "sum of chel’s age and number of days";

        QTest::newRow("union-field-operation-variable")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 11: Вызов функции
    {
        Expression expression(
            "rnd(0)",
            {},
            {{"rnd", Function("rnd", "int", 0, "get random number")}},
            {}, {}, {}, {}
            );

        ExpressionNode* node = new ExpressionNode(EntityType::Function, "rnd", nullptr, nullptr, "int");

        QString explanation = "get random number";

        QTest::newRow("function-call")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 12: Вызов функции класса
    {
        Expression expression(
            "chel kill(0) .",
            {{"chel", Variable("chel", "Human", "person")}},
            {},
            {}, {},
            {{"Human", Class("Human", {},
                             {{"kill", Function("kill", "void", 0, "kill")}})}},
            {}
            );

        ExpressionNode* node = new ExpressionNode(EntityType::Operation, ".",
                                                  new ExpressionNode(EntityType::Variable, "chel", nullptr, nullptr, "Human"),
                                                  new ExpressionNode(EntityType::Function, "kill", nullptr, nullptr, "void"), "", OperationType::FieldAccess);

        QString explanation = "chel’s kill";

        QTest::newRow("class-method-call")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 13: Вызов функции структуры
    {
        Expression expression(
            "chel kill(0) .",
            {{"chel", Variable("chel", "Human", "person")}},
            {},
            {},
            {{"Human", Structure("Human", {},
                                 {{"kill", Function("kill", "void", 0, "kill")}})}},
            {},
            {}
            );

        ExpressionNode* node = new ExpressionNode(EntityType::Operation, ".",
                                                  new ExpressionNode(EntityType::Variable, "chel", nullptr, nullptr, "Human"),
                                                  new ExpressionNode(EntityType::Function, "kill", nullptr, nullptr, "void"), "", OperationType::FieldAccess);

        QString explanation = "chel’s kill";

        QTest::newRow("structure-method-call")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 14: Вызов функции объединения
    {
        Expression expression(
            "chel kill(0) .",
            {{"chel", Variable("chel", "Human", "person")}},
            {},
            {{"Human", Union("Human", {},
                             {{"kill", Function("kill", "void", 0, "kill")}})}},
            {},
            {},
            {}
            );

        ExpressionNode* node = new ExpressionNode(EntityType::Operation, ".",
                                                  new ExpressionNode(EntityType::Variable, "chel", nullptr, nullptr, "Human"),
                                                  new ExpressionNode(EntityType::Function, "kill", nullptr, nullptr, "void"), "", OperationType::FieldAccess);

        QString explanation = "chel’s kill";

        QTest::newRow("union-method-call")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 15: Получение значения перечисления
    {
        Expression expression(
            "Status Alive ::",
            {},
            {},
            {},
            {},
            {},
            {{"Status", Enum("Status", {{"Alive", "alive"}})}}
            );

        ExpressionNode* node = new ExpressionNode(EntityType::Operation, "::",
                                                  new ExpressionNode(EntityType::Enum, "Status", nullptr, nullptr, ""),
                                                  new ExpressionNode(EntityType::Variable, "Alive", nullptr, nullptr, ""), "", OperationType::StaticMemberAccess);

        QString explanation = "alive";

        QTest::newRow("enum-value-retrieval")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 16: Получение значения перечисления при нескольких значениях
    {
        Expression expression(
            "Status Alive ::",
            {},
            {},
            {},
            {},
            {},
            {{"Status", Enum("Status",
                             {{"Alive", "alive"},
                              {"Dead", "dead"}})}}
            );

        ExpressionNode* node = new ExpressionNode(EntityType::Operation, "::",
                                                  new ExpressionNode(EntityType::Enum, "Status", nullptr, nullptr, ""),
                                                  new ExpressionNode(EntityType::Variable, "Alive", nullptr, nullptr, ""), "", OperationType::StaticMemberAccess);

        QString explanation = "alive";

        QTest::newRow("enum-value-with-multiple-values")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 17: Сложение двух строк
    {
        Expression expression(
            "oleg cool +",
            {{"oleg", Variable("oleg", "string", "Oleg")},
             {"cool", Variable("cool", "string", "is cool")}},
            {},
            {},
            {},
            {},
            {}
            );

        ExpressionNode* node = new ExpressionNode(EntityType::Operation, "+",
                                                  new ExpressionNode(EntityType::Variable, "oleg"),
                                                  new ExpressionNode(EntityType::Variable, "cool"), "", OperationType::Addition);

        QString explanation = "concatenation of oleg and is cool";

        QTest::newRow("string-concatenation")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }

    // Тест 18: Сложение двух одинаковых переменных
    {
        Expression expression(
            "oleg oleg +",
            {{"oleg", Variable("oleg", "string", "Oleg")}},
            {},
            {},
            {},
            {},
            {}
            );

        ExpressionNode* node = new ExpressionNode(EntityType::Operation, "+",
                                                  new ExpressionNode(EntityType::Variable, "oleg"),
                                                  new ExpressionNode(EntityType::Variable, "oleg"), "", OperationType::Addition);

        QString explanation = "sum of oleg and oleg";

        QTest::newRow("addition-of-identical-variables")
            << expression
            << node
            << QString()
            << OperationType::None
            << explanation;
    }
}
