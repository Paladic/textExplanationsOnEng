#include "expressionnode.h"

// Конструктор по умолчанию
ExpressionNode::ExpressionNode()
    : value(""),
    right(nullptr),
    left(nullptr),

    nodeType(EntityType::Undefined),
    operType(OperationType::None),
    dataType(""),
    FunctionArgs(nullptr) {}
QString ExpressionNode::toString() const {
    QString result;

    // Добавляем информацию об узле
    result += value.isEmpty() ? "Unknown" : value;

    // Если это функция, добавляем аргументы
    if (nodeType == EntityType::Function && FunctionArgs) {
        result += "(";
        QStringList args;
        for (auto* arg : *FunctionArgs) {
            args << arg->toString(); // Рекурсивно вызываем для аргументов
        }
        result += args.join(", "); // Соединяем аргументы через запятую
        result += ")";
    }

    // Обрабатываем левый и правый узлы
    if (left || right) {
        result += " (";
        if (left) {
            result += left->toString();
        }
        result += "; ";
        if (right) {
            result += right->toString();
        }
        result += ")";
    }

    return result;
}
bool ExpressionNode::operator!=(const ExpressionNode& other) const {
    return !(*this == other);
bool ExpressionNode::operator==(const ExpressionNode& other) const {
    // Сравниваем основные поля узла
    bool areBasicFieldsEqual =
        value == other.value &&
        nodeType == other.nodeType &&
        operType == other.operType &&
        dataType == other.dataType;

    // Сравниваем дочерние узлы (рекурсивно)
    bool areLeftNodesEqual = (left == nullptr && other.left == nullptr) ||
                             (left != nullptr && other.left != nullptr && *left == *other.left);

    bool areRightNodesEqual = (right == nullptr && other.right == nullptr) ||
                              (right != nullptr && other.right != nullptr && *right == *other.right);

    // Сравниваем аргументы функции
    bool areFunctionArgsEqual = (FunctionArgs == nullptr && other.FunctionArgs == nullptr) ||
                                (FunctionArgs != nullptr && other.FunctionArgs != nullptr && compareFunctionArgs(*FunctionArgs, *other.FunctionArgs));

    // Итоговое сравнение
    return areBasicFieldsEqual && areLeftNodesEqual && areRightNodesEqual && areFunctionArgsEqual;
}
// Вспомогательная функция для сравнения списков аргументов функции
bool ExpressionNode::compareFunctionArgs(const QList<ExpressionNode*>& args1, const QList<ExpressionNode*>& args2) const {
    if (args1.size() != args2.size()) {
        return false; // Разные размеры списков
    }

    // Сравниваем содержимое списков
    for (int i = 0; i < args1.size(); ++i) {
        if (*args1[i] != *args2[i]) {
            return false; // Если хотя бы один узел отличается
        }
    }
    return true; // Все узлы совпадают
}
