#include "expression.h"
#include "expressionxmlparser.h"

Expression::Expression(const QString inputXMLFile) {

    ExpressionXmlParser::readDataFromXML(inputXMLFile, *this);

}

void Expression::setExpression(const QString &newExpression)
{
    expression = newExpression;
}

const QString* Expression::getExpression() const
{
    return &expression;
}

const QHash<QString, Variable>* Expression::getVariables() const
{
    return &variables;
}

void Expression::setVariables(const QHash<QString, Variable> &newVariables)
{
    variables = newVariables;
}

const Variable Expression::getVarByName(const QString &name) const
{
    return getVariables()->value(name);
}

const QHash<QString, Function>* Expression::getFunctions() const
{
    return &functions;
}

void Expression::setFunctions(const QHash<QString, Function> &newFunctions)
{
    functions = newFunctions;
}

const Function Expression::getFuncByName(const QString &name) const
{
    return getFunctions()->value(name);
}

const QHash<QString, Union>* Expression::getUnions() const
{
    return &unions;
}

void Expression::setUnions(const QHash<QString, Union> &newUnions)
{
    unions = newUnions;
}

const Union Expression::getUnionByName(const QString &name) const
{
    return getUnions()->value(name);
}

const QHash<QString, Structure>* Expression::getStructures() const
{
    return &structures;
}

void Expression::setStructures(const QHash<QString, Structure> &newStructures)
{
    structures = newStructures;
}

const Structure Expression::getStructByName(const QString &name) const
{
    return getStructures()->value(name);
}

const QHash<QString, Class>* Expression::getClasses() const
{
    return &classes;
}

void Expression::setClasses(const QHash<QString, Class> &newClasses)
{
    classes = newClasses;
}

const Class Expression::getClassByName(const QString &name) const
{
    return getClasses()->value(name);
}

const QHash<QString, Enum>* Expression::getEnums() const
{
    return &enums;
}

void Expression::setEnums(const QHash<QString, Enum> &newEnums)
{
    enums = newEnums;
}

const Enum Expression::getEnumByName(const QString &name) const
{
    return getEnums()->value(name);
}

const Variable Expression::getVariableByNameFromCustomData(QString varName, QString dataName) const
{
    // Получить пользовательский тип данных по его имени
    CustomTypeWithFields customType = getCustomTypeByName(dataName);
    return customType.variables.value(varName);
}

const Function Expression::getFunctionByNameFromCustomData(QString funcName, QString dataName) const
{
    // Получить пользовательский тип данных по его имени
    CustomTypeWithFields customType = getCustomTypeByName(dataName);
    return customType.functions.value(funcName);
}

const CustomTypeWithFields Expression::getCustomTypeByName(const QString &typeName) const
{
    CustomTypeWithFields type;
    if (classes.contains(typeName)) {
        type = classes.value(typeName);
    }
    else if (structures.contains(typeName)) {
        type = structures.value(typeName);
    }
    else if (unions.contains(typeName)) {
        type = unions.value(typeName);
    }
    return type;
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
