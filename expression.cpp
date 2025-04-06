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
QString Expression::ToQstring()
{
    QString result = "Expression:   "  + this->expression;

    result += "\nVariables:";
    QHashIterator itV(this->variables);
    while(itV.hasNext()) {
        Variable val = itV.next().value();
        result += "\n" + val.toQString("    ");
    }

    result += "\nFunctions:";
    QHashIterator itF(this->functions);
    while(itF.hasNext()) {
        Function func = itF.next().value();
        result += "\n" + func.toQString("    ");
    }

    result += "\nUnions:";
    QHashIterator itU(this->unions);
    while(itU.hasNext()) {
        Union _union = itU.next().value();
        result += "\n" + _union.toQString("    ");
    }

    result += "\nStructures:";
    QHashIterator itS(this->structures);
    while(itS.hasNext()) {
        Structure structure = itS.next().value();
        result += "\n" + structure.toQString("    ");
    }

    result += "\nClasses:";
    QHashIterator itC(this->classes);
    while(itC.hasNext()) {
        Class _class = itC.next().value();
        result += "\n" + _class.toQString("    ");
    }

    result += "\nEnums:";
    QHashIterator itE(this->enums);
    while(itE.hasNext()) {
        Enum _enum = itE.next().value();
        result += "\n" + _enum.toQString("    ");
    }

    return result;
}
