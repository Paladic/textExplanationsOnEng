#ifndef CODEENTITY_H
#define CODEENTITY_H

#include <QList>
#include <QHash>
#include <QString>


// Переменная
struct Variable {

    QString name;           // имя
    QString type;           // тип
    QString description;    // описание

    Variable(const QString& name = "", const QString& type = "", const QString& description = "");

    QString toQString(const QString& startLine = "") const;
};

// Функция
struct Function {

    QString name;           // Имя
    QString type;           // Тип
    int paramsCount;        // Количество входных параметров
    QString description;    // Описание

    Function(const QString& name = "", const QString& type = "", int paramsCount = 0, const QString& description = "");

    QString toQString(const QString& startLine = "") const;

};

// Объединение
struct Union {

    QString name;               // Имя
    QHash<QString, Variable> variables;  // Поля
    QHash<QString, Function> functions;  // Методы

    Union(const QString& name = "", const QHash<QString, Variable>& variables = {}, const QHash<QString, Function>& functions = {});

    QString toQString(const QString& startLine = "") const;
};

// Структура
struct Structure {

    QString name;               // Имя
    QHash<QString, Variable> variables;  // Поля
    QHash<QString, Function> functions;  // Методы

    Structure(const QString& name = "", const QHash<QString, Variable>& variables = {}, const QHash<QString, Function>& functions = {});

    QString toQString(const QString& startLine = "") const;
};

// Класс
struct Class {

    QString name;               // Имя
    QHash<QString, Variable> variables;  // Поля
    QHash<QString, Function> functions;  // Методы

    Class(const QString& name = "", const QHash<QString, Variable>& variables = {}, const QHash<QString, Function>& functions = {});

    QString toQString(const QString& startLine = "") const;
};

// Перечисление
struct Enum {

    QString name;                   // Имя
    QHash<QString, QString> values;  // Значения

    Enum(const QString& name = "", const QHash<QString, QString>& values = {});

    QString toQString(const QString& startLine = "") const;
};

#endif // CODEENTITY_H
