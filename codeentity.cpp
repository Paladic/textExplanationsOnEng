#include "codeentity.h"

const QHash<QString, OperatorInfo> OperationMap = {
    {"++_", {OperationArity::Unary, OperationType::PrefixIncrement}},       // Префиксный инкремент
    {"--_", {OperationArity::Unary, OperationType::PrefixDecrement}},       // Префиксный декремент
    {"[]",  {OperationArity::Binary, OperationType::ArrayAccess}},          // Обращение к элементу под индексом
    {".",   {OperationArity::Binary, OperationType::FieldAccess}},          // Обращение к полю элемента
    {"->",  {OperationArity::Binary, OperationType::PointerFieldAccess}},   // Обращение к полю по указателю
    {"*_",  {OperationArity::Unary, OperationType::Dereference}},           // Обращение к значению по адресу
    {"&",   {OperationArity::Unary, OperationType::AddressOf}},             // Обращение к адресу элемента
    {"-",   {OperationArity::Unary, OperationType::UnaryMinus}},            // Унарный минус
    {"!",   {OperationArity::Unary, OperationType::Not}},                   // Логическое «не»
    {"&&",  {OperationArity::Binary, OperationType::And}},                  // Логическое «и»
    {"||",  {OperationArity::Binary, OperationType::Or}},                   // Логическое «или»
    {"*",   {OperationArity::Binary, OperationType::Multiplication}},       // Умножение
    {"/",   {OperationArity::Binary, OperationType::Division}},             // Деление
    {"%",   {OperationArity::Binary, OperationType::Modulus}},              // Остаток от деления
    {"+",   {OperationArity::Binary, OperationType::Addition}},             // Сложение
    {"-",   {OperationArity::Binary, OperationType::Subtraction}},          // Вычитание
    {"<",   {OperationArity::Binary, OperationType::LessThan}},             // Оператор сравнения «меньше»
    {">",   {OperationArity::Binary, OperationType::GreaterThan}},          // Оператор сравнения «больше»
    {"<=",  {OperationArity::Binary, OperationType::LessThanOrEqual}},      // Оператор сравнения «меньше либо равно»
    {">=",  {OperationArity::Binary, OperationType::GreaterThanOrEqual}},   // Оператор сравнения «больше либо равно»
    {"==",  {OperationArity::Binary, OperationType::Equal}},                // Оператор сравнения «равно»
    {"!=",  {OperationArity::Binary, OperationType::NotEqual}},             // Оператор сравнения «не равно»
    {"%=",  {OperationArity::Binary, OperationType::ModulusAssignment}},    // Взятие остатка от деления с присваиванием
    {"/=",  {OperationArity::Binary, OperationType::DivisionAssignment}},   // Деление с присваиванием
    {"*=",  {OperationArity::Binary, OperationType::MultiplicationAssignment}}, // Умножение с присваиванием
    {"-=",  {OperationArity::Binary, OperationType::SubtractionAssignment}},// Вычитание с присваиванием
    {"+=",  {OperationArity::Binary, OperationType::AdditionAssignment}},   // Сложение с присваиванием
    {"=",   {OperationArity::Binary, OperationType::Assignment}},           // Присваивание
    {"_--", {OperationArity::Unary, OperationType::PostfixDecrement}},      // Постфиксный декремент
    {"_++", {OperationArity::Unary, OperationType::PostfixIncrement}},      // Постфиксный инкремент
    {"::",  {OperationArity::Binary, OperationType::StaticMemberAccess}}    // Обращение к статическому элементу
};

const QHash<EntityType, QString> EntityTypeNames = {
    {EntityType::Operation, "Operation"},
    {EntityType::Const, "Const"},
    {EntityType::Variable, "Variable"},
    {EntityType::Function, "Function"},
    {EntityType::CustomTypeWithFields, "CustomTypeWithFields"},
    {EntityType::Enum, "Enum"},
    {EntityType::Undefined, "Undefined"}
};

const QHash<OperationType, QString> OperationTypeNames = {
    {OperationType::PrefixIncrement, "PrefixIncrement"},
    {OperationType::PrefixDecrement, "PrefixDecrement"},
    {OperationType::ArrayAccess, "ArrayAccess"},
    {OperationType::FieldAccess, "FieldAccess"},
    {OperationType::PointerFieldAccess, "PointerFieldAccess"},
    {OperationType::Dereference, "Dereference"},
    {OperationType::AddressOf, "AddressOf"},
    {OperationType::UnaryMinus, "UnaryMinus"},
    {OperationType::Not, "Not"},
    {OperationType::And, "And"},
    {OperationType::Or, "Or"},
    {OperationType::Multiplication, "Multiplication"},
    {OperationType::Division, "Division"},
    {OperationType::Modulus, "Modulus"},
    {OperationType::Addition, "Addition"},
    {OperationType::Subtraction, "Subtraction"},
    {OperationType::LessThan, "LessThan"},
    {OperationType::GreaterThan, "GreaterThan"},
    {OperationType::LessThanOrEqual, "LessThanOrEqual"},
    {OperationType::GreaterThanOrEqual, "GreaterThanOrEqual"},
    {OperationType::Equal, "Equal"},
    {OperationType::NotEqual, "NotEqual"},
    {OperationType::ModulusAssignment, "ModulusAssignment"},
    {OperationType::DivisionAssignment, "DivisionAssignment"},
    {OperationType::MultiplicationAssignment, "MultiplicationAssignment"},
    {OperationType::SubtractionAssignment, "SubtractionAssignment"},
    {OperationType::AdditionAssignment, "AdditionAssignment"},
    {OperationType::Assignment, "Assignment"},
    {OperationType::PostfixDecrement, "PostfixDecrement"},
    {OperationType::PostfixIncrement, "PostfixIncrement"},
    {OperationType::StaticMemberAccess, "StaticMemberAccess"},
    {OperationType::None, "None"}
};

Variable::Variable(const QString &name, const QString &type, const QString &description)
    : name(name), type(type), description(description) {}

QString Variable::toQString(const QString& startLine) const {

    //QString result = startLine + "Variable:";
    //result += "\n" + startLine + "  name: " + name;
    //result += "\n" + startLine + "  type: " + type;
    //result += "\n" + startLine + "  description: " + description;

    QString result = startLine + "Variable:";
    result += "  name: " +          this->name;
    result += ";  type: " +         this->type;
    result += ";  description: " +  this->description;

    return result;
}


Function::Function(const QString &name, const QString &type, int paramsCount, const QString &description)
    : name(name), type(type), paramsCount(paramsCount), description(description) {}

QString Function::toQString(const QString& startLine) const {

    QString result = startLine + "Function:";
    result += "  name: " +          this->name;
    result += ";  type: " +         this->type;
    result += ";  description: " +  this->description;

    return result;

}

Union::Union(const QString &name, const QHash<QString, Variable> &variables, const QHash<QString, Function> &functions)
    : CustomTypeWithFields(name, variables, functions){}

QString Union::toQString(const QString& startLine) const {

    QString result = startLine + "Union:";
    result += " name: " + this->name;

    QHashIterator itV(this->variables);
    while(itV.hasNext())
        result += "\n" + itV.next().value().toQString(startLine + "    ");

    QHashIterator itF(this->functions);
    while(itF.hasNext())
        result += "\n" + itF.next().value().toQString(startLine + "    ");

    return result;
}

Structure::Structure(const QString &name, const QHash<QString, Variable> &variables, const QHash<QString, Function> &functions)
    : CustomTypeWithFields(name, variables, functions){}

QString Structure::toQString(const QString& startLine) const {

    QString result = startLine + "Structure:";
    result += " name: " + this->name;

    QHashIterator itV(this->variables);
    while(itV.hasNext())
        result += "\n" + itV.next().value().toQString(startLine + "    ");

    QHashIterator itF(this->functions);
    while(itF.hasNext())
        result += "\n" + itF.next().value().toQString(startLine + "    ");

    return result;
}


Class::Class(const QString &name, const QHash<QString, Variable> &variables, const QHash<QString, Function> &functions)
    : CustomTypeWithFields(name, variables, functions){}

QString Class::toQString(const QString& startLine) const {

    QString result = startLine + "Class:";
    result += " name: " + this->name;

    QHashIterator itV(this->variables);
    while(itV.hasNext())
        result += "\n" + itV.next().value().toQString(startLine + "    ");

    QHashIterator itF(this->functions);
    while(itF.hasNext())
        result += "\n" + itF.next().value().toQString(startLine + "    ");

    return result;

}

Enum::Enum(const QString &name, const QHash<QString, QString> &values)
    : name(name), values(values) {}

QString Enum::toQString(const QString& startLine) const {

    QString result = startLine + "Enum:";
    result += " name: " + name;

    QHashIterator itV(this->values);
    while(itV.hasNext()) {
        auto v = itV.next();
        result += "\n   " + startLine + v.key() + ": " + v.value();
    }
    return result;

}

CustomTypeWithFields::CustomTypeWithFields(const QString &name, const QHash<QString, Variable> &variables, const QHash<QString, Function> &functions)
    : name(name), variables(variables), functions(functions) {}

QString CustomTypeWithFields::toQString(const QString &startLine) const
{
    QString result = startLine + "Custom Type:";
    result += "  name: " +          this->name;
    return result;
}
