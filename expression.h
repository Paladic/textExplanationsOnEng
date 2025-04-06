#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "codeentity.h"

#include <QHash>
#include <QString>


class Expression
{

    QString expression; // Текстовое выражение
    QHash<QString, Variable> variables; //  Переменные
    QHash<QString, Function> functions; // функции
    // Пользовательские типы
    QHash<QString, Union> unions; // Объединения
    QHash<QString, Structure> structures; // Структуры
    QHash<QString, Class> classes; // Классы
    QHash<QString, Enum> enums; // Перечисления

public:

    QString ToQstring();
    void setExpression(const QString &newExpression);
    QString getExpression() const;

    QHash<QString, Variable> getVariables() const;
    void setVariables(const QHash<QString, Variable> &newVariables);

    QHash<QString, Function> getFunctions() const;
    void setFunctions(const QHash<QString, Function> &newFunctions);

    QHash<QString, Union> getUnions() const;
    void setUnions(const QHash<QString, Union> &newUnions);

    QHash<QString, Structure> getStructures() const;
    void setStructures(const QHash<QString, Structure> &newStructures);

    QHash<QString, Class> getClasses() const;
    void setClasses(const QHash<QString, Class> &newClasses);

    QHash<QString, Enum> getEnums() const;
    void setEnums(const QHash<QString, Enum> &newEnums);
};

#endif // EXPRESSION_H
