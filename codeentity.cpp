#include "codeentity.h"

Variable::Variable(const QString &name, const QString &type, const QString &description)
    : name(name), type(type), description(description) {}
Function::Function(const QString &name, const QString &type, int paramsCount, const QString &description)
    : name(name), type(type), paramsCount(paramsCount), description(description) {}

