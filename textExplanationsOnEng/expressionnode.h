/*!
 * \file
 * \brief Заголовочный файл, содержащий описание класса ExpressionNode — элемента дерева выражения
 */

#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H

#include <QString>
#include "codeentity.h"

/*!
 * \brief Класс, представляющий узел дерева выражения
 *
 * Используется для хранения структуры выражения в виде бинарного дерева,
 * где каждый узел может быть переменной, константой, операцией, функцией и т.п.
 */
class ExpressionNode
{
public:
    /*!
     * \brief Конструктор по умолчанию
     */
    explicit ExpressionNode();

    /*!
     * \brief Конструктор узла выражения
     * \param[in] nodeType Тип узла (переменная, операция и т.д.)
     * \param[in] value Значение (имя переменной, операция и т.п.)
     * \param[in] left Левый потомок
     * \param[in] right Правый потомок
     * \param[in] dataType Тип данных узла
     * \param[in] operType Тип операции (если это операция)
     * \param[in] functionArgs Аргументы функции (если это функция)
     */
    explicit ExpressionNode(EntityType nodeType, const QString& value,
                   ExpressionNode* left = nullptr,
                   ExpressionNode* right = nullptr,
                   const QString& dataType = "",
                   OperationType operType = OperationType::None,
                   QList<ExpressionNode*>* functionArgs = {});

    /*!
     * \brief Получение строкового представления узла (рекурсивное)
     * \return Строка, представляющая поддерево с текущим узлом
     */
    QString toString() const;

    /*!
     * \brief Проверка, является ли унарная операция самоуничтожающейся
     * \return true, если операция обратима сама себе (например, `--(--x)` = `x`)
     */
    bool isReducibleUnarySelfInverse() const;

    /*!
     * \brief Получение типа операции
     */
    OperationType getOperType() const;

    /*!
     * \brief Получение типа сущности узла
     */
    EntityType getNodeType() const;

    /*!
     * \brief Получение значения узла
     */
    QString getValue() const;

    /*!
     * \brief Получение типа данных узла
     */
    QString getDataType() const;

    /*!
     * \brief Получение аргументов функции
     */
    QList<ExpressionNode*>* getFunctionArgs() const;

    /*!
     * \brief Получение правого потомка
     */
    ExpressionNode* getRightNode() const;

    /*!
     * \brief Получение левого потомка
     */
    ExpressionNode* getLeftNode() const;

    /*!
     * \brief Установка типа операции
     */
    void setOperType(OperationType newOperType);

    /*!
     * \brief Установка типа узла
     */
    void setNodeType(EntityType newNodeType);

    /*!
     * \brief Установка значения узла
     */
    void setValue(QString newValue);

    /*!
     * \brief Установка типа данных
     */
    void setDataType(QString newDataType);

    /*!
     * \brief Установка аргументов функции
     */
    void setFunctionArgs(QList<ExpressionNode*>* newFunctionArgs);

    /*!
     * \brief Установка правого потомка
     */
    void setRightNode(ExpressionNode* newRightNode);

    /*!
     * \brief Установка левого потомка
     */
    void setLeftNode(ExpressionNode* newLeftNode);

    /*!
     * \brief Оператор сравнения (равенство)
     */
    bool operator==(const ExpressionNode& other) const;

    /*!
     * \brief Оператор сравнения (неравенство)
     */
    bool operator!=(const ExpressionNode& other) const;

    /*!
     * \brief Сравнение списков аргументов функций
     * \param[in] args1 Первый список
     * \param[in] args2 Второй список
     * \return true, если аргументы совпадают
     */
    bool compareFunctionArgs(const QList<ExpressionNode*>& args1, const QList<ExpressionNode*>& args2) const;

    /*!
     * \brief Проверка, является ли операция сравнением
     */
    bool isComparisonOperation() const;

    /*!
     * \brief Проверка, является ли операция инкрементом или декрементом
     */
    bool isIncrementOrDecrement() const;

private:
    QString value; ///< Содержимое узла (имя переменной, значение и т.д.)
    ExpressionNode* right; ///< Правый потомок
    ExpressionNode* left; ///< Левый потомок
    EntityType nodeType; ///< Тип узла
    OperationType operType; ///< Тип операции (если применимо)
    QString dataType; ///< Тип данных
    QList<ExpressionNode*>* FunctionArgs; ///< Аргументы функции (если узел — функция)
};

#endif // EXPRESSIONNODE_H
