#include "expression.h"
void Expression::setExpression(const QString &newExpression)
{
    expression = newExpression;
}

QString Expression::getExpression() const
{
    return expression;
}

QHash<QString, Variable> Expression::getVariables() const
{
    return variables;
}

void Expression::setVariables(const QHash<QString, Variable> &newVariables)
{
    variables = newVariables;
}

QHash<QString, Function> Expression::getFunctions() const
{
    return functions;
}

void Expression::setFunctions(const QHash<QString, Function> &newFunctions)
{
    functions = newFunctions;
}

QHash<QString, Union> Expression::getUnions() const
{
    return unions;
}

void Expression::setUnions(const QHash<QString, Union> &newUnions)
{
    unions = newUnions;
}

QHash<QString, Structure> Expression::getStructures() const
{
    return structures;
}

void Expression::setStructures(const QHash<QString, Structure> &newStructures)
{
    structures = newStructures;
}

QHash<QString, Class> Expression::getClasses() const
{
    return classes;
}

void Expression::setClasses(const QHash<QString, Class> &newClasses)
{
    classes = newClasses;
}

QHash<QString, Enum> Expression::getEnums() const
{
    return enums;
}

void Expression::setEnums(const QHash<QString, Enum> &newEnums)
{
    enums = newEnums;
}
