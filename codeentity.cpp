#include "codeentity.h"

Variable::Variable(const QString &name, const QString &type, const QString &description)
    : name(name), type(type), description(description) {}
Function::Function(const QString &name, const QString &type, int paramsCount, const QString &description)
    : name(name), type(type), paramsCount(paramsCount), description(description) {}

Union::Union(const QString &name, const QList<Variable> &variables, const QList<Function> &functions)
    : name(name), variables(variables), functions(functions) {}




Structure::Structure(const QString &name, const QList<Variable> &variables, const QList<Function> &functions)
    : name(name), variables(variables), functions(functions) {}
