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

bool Expression::isEnumValue(const QString &value, const QString &enumName) const
{
    bool ok = false;
    if(getEnumByName(enumName).values.contains(value)) ok = true;
    return ok;
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
ExpressionNode* Expression::expressionToNodes() {
    // Разделяем выражение на лексемы
    QStringList tokens = expression.split(' ', Qt::SkipEmptyParts);
    //...Считаем, что стек узлов пустой
    QStack<ExpressionNode*> nodeStack;

    QStringList::const_iterator i;
    // Для каждой лексемы
    for(i = tokens.constBegin(); i != tokens.constEnd(); i++){
        // Получить тип лексемы
        EntityType nodeType = getEntityTypeByStr(*i);
        // Если лексема является операцией
        if(nodeType == EntityType::Operation){
            OperationType operType = getOperationTypeByStr(*i);
            ExpressionNode* right = nullptr;
            ExpressionNode* left = nullptr;
            // Если в стеке есть два операнда и операция бинарная
            if(nodeStack.size() >= 2 && OperationMap.value(*i).arity == OperationArity::Binary){
                // извлекаем из стека
                right = nodeStack.pop();
                left = nodeStack.pop();
            }
            //Иначе если в стеке один операнд и операция унарная
            else if(nodeStack.size() == 1 && (OperationMap.value(*i).arity == OperationArity::Unary || operType == OperationType::Subtraction)){
                // извлекаем один операнд
                left = nodeStack.pop();
                if(operType == OperationType::Subtraction) operType = OperationType::UnaryMinus;
            }
            // Иначе если операндов меньше чем два
            else if (nodeStack.size() < 2) {
                // выдать ошибку об отсутствии операнда у операции
                throw TEException(ErrorType::MissingOperand, QList<QString>{*i});
            }
            // Иначе если операндов больше чем два
            else if (nodeStack.size() > 2) {
                // выдать ошибку об отсутствии операции у операнда
                throw TEException(ErrorType::MissingOperations, QList<QString>{nodeStack.pop()->getValue()});
            }
            nodeStack.push(new ExpressionNode(EntityType::Operation, *i, left, right, "", operType));
        }
        // Иначе если лексема яаляется константой
        else if(nodeType == EntityType::Const){
            nodeStack.push(new ExpressionNode(EntityType::Const, *i, nullptr, nullptr));
        }
        // Иначе если лексема яаляется переменной
        else if(nodeType == EntityType::Variable){
            // Определить тип данных переменной
            QString dataType = getVariables()->value(*i).type;
            // если тип данных не определен
            if(dataType == ""){
                ExpressionNode *rightSibling = nodeStack.top();
                // если следующая лексема существует
                if(i+1 != tokens.end()){
                    // если эта лексема обращение к полю
                    if(*(i+1) == "."){
                        // то найдем переменную по пользовательскому типу данных
                        dataType = getVariableByNameFromCustomData(*i, rightSibling->getDataType()).name;
                    }
                    // иначе если эта лексема обращение к статическому элементу
                    else if(*(i+1) == "::"){
                        // если является вариантом перечисления, то считаем имя перечисления типом данных
                        dataType = isEnumValue(*i, rightSibling->getValue()) ? rightSibling->getValue() : "";
                    }
                }
            }
            // если тип данных был определен добавить элемент в стек
            if (dataType != "") nodeStack.push(new ExpressionNode(EntityType::Variable, *i, nullptr, nullptr, dataType));
            // иначе ошибка о неидентифицированном значении
            else throw TEException(ErrorType::UndefinedId, QList<QString>{*i});
        }
        else if (nodeType == EntityType::Enum){
            nodeStack.push(new ExpressionNode(EntityType::Enum, *i, nullptr, nullptr, ""));
        }
        // Иначе если лексема яаляется функцией
        else if (nodeType == EntityType::Function) {
            // Определить количество аргументов функции
            int argCountStart = i->indexOf('(');
            int argCountEnd = i->indexOf(')');
            int argCount = i->mid(argCountStart + 1, argCountEnd - argCountStart - 1).toInt();
            QString funcName = i->left(argCountStart);
            // Определить возвращаемый тип данных
            QString funcDataType = getFunctions()->value(funcName).type;
            // если возвращаемый тип данных не был определен
            if(funcDataType == ""){
                ExpressionNode *rightSibling = nodeStack.top();
                // если следующая лексема существует
                if(i+1 != tokens.end()){
                    // если эта лексема обращение к полю
                    if(*(i+1) == "."){
                        // то найдем функцию по пользовательскому типу данных
                        funcDataType = getFunctionByNameFromCustomData(*i, rightSibling->getDataType()).name;
                    }
                }
            }
            // если тип данных был определен
            if(funcDataType != ""){
                // Если количество параметров в выражении не соостветствует количеству параметров в атрибуте функции,
                // то вызвать ошибку о несоответствии параметров
                if(argCount != getFunctions()->value(funcName).paramsCount)
                    throw TEException(ErrorType::ParamsCountFunctionMissmatch, QList<QString>{*i});
                QList<ExpressionNode*>* functionArgs = new QList<ExpressionNode*>();
                // В соответствии с количеством параметров извлекаем операнды
                for (int j = 0; j < argCount; j++) {
                    functionArgs->prepend(nodeStack.pop());
                }
                // добавляем функцию в стек
                ExpressionNode* functionNode = new ExpressionNode(EntityType::Function, i->left(argCountStart), nullptr, nullptr, getFunctions()->value(*i).type, OperationType::None, functionArgs);
                nodeStack.push(functionNode);
            }
            // иначе ошибка о неидентифицированном значении
            else throw TEException(ErrorType::UndefinedId, QList<QString>{funcName});
        }
        // Если тип лексемы неопределен
        if(nodeType == EntityType::Undefined) TEException(ErrorType::UndefinedId, QList<QString>{*i});
    }

    // Если в стеке остался более чем один операнд, то выдать ошибку об отсутствии операции у операнда
    if(nodeStack.size() > 1)throw TEException(ErrorType::MissingOperations, QList<QString>{nodeStack.pop()->getValue()});

    return nodeStack.pop();
}

EntityType Expression::getEntityTypeByStr(const QString &str)
{
    //...Считаем, что тип неопределен
    EntityType type = EntityType::Undefined;
    if(isConst(str)) type = EntityType::Const;
    else if(isFunction(str)) type = EntityType::Function;
    else if(isCustomTypeWithFields(str)) type = EntityType::CustomTypeWithFields;
    else if(isEnum(str)) type = EntityType::Enum;
    else if(getOperationTypeByStr(str) != OperationType::None) type = EntityType::Operation;
    else if(isVariable(str)) type = EntityType::Variable;
    return type;
}

bool Expression::isConst(const QString &str)
{
    //...Считаем что строка не является константой
    bool ok = false;
    // Если строку можно перевести в число, то
    if(str.toInt() || str.toFloat() || str.toDouble()){
        // строка является константой
        ok = true;
    }
    return ok;
}

bool Expression::isVariable(const QString &str)
{
    bool ok = false;
    if(isIdentifier(str)){
        ok = true;
    }
    else throw TEException(ErrorType::InvalidSymbol, QList<QString>{str});
    return ok;
}



bool Expression::isCustomTypeWithFields(const QString &str)
{
    bool ok = false;
    if(getCustomTypeByName(str).name != ""){
        ok = true;
    }
    return ok;
}

bool Expression::isEnum(const QString &str)
{
    bool ok = false;
    if(getEnumByName(str).name != ""){
        ok = true;
    }
    return ok;
}





QList<QString> Expression::argsToDescr(const QList<ExpressionNode *> *functionArgs, QString customDataType) const
{
    QList<QString> descriptions;
    QList<ExpressionNode *>::const_iterator i;
    for(i = functionArgs->constBegin(); i != functionArgs->constEnd(); i++){
        descriptions.append(ToExplanation(*i));
    }
    return descriptions;
}

OperationType Expression::getOperationTypeByStr(const QString &str)
{
    OperationType type = OperationType::None;
    if(OperationMap.contains(str)){
        type = OperationMap.value(str).type;
    }
    return type;
}

