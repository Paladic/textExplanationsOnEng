#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "codeentity.h"

#include <QHash>
#include <QString>


class Expression
{
public:
    Expression(const QString inputXMLFile);
    Expression(
        const QString& expr = "",
        const QHash<QString, Variable>& vars = {},
        const QHash<QString, Function>& funcs = {},
        const QHash<QString, Union>& unns = {},
        const QHash<QString, Structure>& strucs = {},
        const QHash<QString, Class>& cls = {},
        const QHash<QString, Enum>& enms = {}
        )
        : expression(expr)
        , variables(vars)
        , functions(funcs)
        , unions(unns)
        , structures(strucs)
        , classes(cls)
        , enums(enms)
    {}

    QString ToQstring();
    bool isConst(const QString& str);
    bool isVariable(const QString& str);
    static bool isFunction(const QString& str)
    {
        bool ok = false;
        if(str.contains('(') && str.endsWith(')')){
            if(isIdentifier(str.left(str.indexOf('(')))) ok = true;
            else throw TEException(ErrorType::InvalidSymbol, QList<QString>{str});
        }
        return ok;
    }
    bool isCustomTypeWithFields(const QString& str);
    bool isEnum(const QString& str);
    static bool isIdentifier(const QString& str)
    {
        bool isInd = true;
        // Первый символ - латинская буква или _
        if (str.isEmpty()) isInd = false;
        else{
            if (!(isLatinLetter(str[0]) || str[0] == '_')) {
                isInd = false;
            }
            // Остальные символы - латинские буквы, цифры или _
            for(int i = 0; i < str.length(); i++) {
                if (!(isLatinLetter(str[i]) || str[i].isDigit() || str[i] == '_')) {
                    isInd = false;
                }
            }
        }
        return isInd;
    }

    static bool isLatinLetter(const QChar c) {
        // Явная проверка латинских букв
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }
    
    QList<QString> argsToDescr(const QList<ExpressionNode *> *functionArgs, QString customDataType = "") const;

    OperationType getOperationTypeByStr(const QString& str);
    void setExpression(const QString &newExpression);
    const QString* getExpression() const;

    const QHash<QString, Variable>* getVariables() const;
    void setVariables(const QHash<QString, Variable> &newVariables);
    const Variable getVarByName(const QString &name) const;

    const QHash<QString, Function>* getFunctions() const;
    void setFunctions(const QHash<QString, Function> &newFunctions);
    const Function getFuncByName(const QString &name) const;

    const QHash<QString, Union>* getUnions() const;
    void setUnions(const QHash<QString, Union> &newUnions);
    const Union getUnionByName(const QString &name) const;

    const QHash<QString, Structure>* getStructures() const;
    void setStructures(const QHash<QString, Structure> &newStructures);
    const Structure getStructByName(const QString &name) const;

    const QHash<QString, Class>* getClasses() const;
    void setClasses(const QHash<QString, Class> &newClasses);
    const Class getClassByName(const QString &name) const;

    const QHash<QString, Enum>* getEnums() const;
    void setEnums(const QHash<QString, Enum> &newEnums);
    const Enum getEnumByName(const QString &name) const;

    const Variable getVariableByNameFromCustomData(QString varName, QString dataName) const;
    const Function getFunctionByNameFromCustomData(QString funcName, QString dataName) const;
    bool isEnumValue(const QString& value, const QString& enumName) const;

    const CustomTypeWithFields getCustomTypeByName(const QString &typeName) const;

private:
    QString expression; // Текстовое выражение
    QHash<QString, Variable> variables; //  Переменные
    QHash<QString, Function> functions; // функции
    // Пользовательские типы
    QHash<QString, Union> unions; // Объединения
    QHash<QString, Structure> structures; // Структуры
    QHash<QString, Class> classes; // Классы
    QHash<QString, Enum> enums; // Перечисления
};

#endif // EXPRESSION_H
