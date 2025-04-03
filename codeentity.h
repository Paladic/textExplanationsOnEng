#ifndef CODEENTITY_H
#define CODEENTITY_H

#include <QList>
#include <QMap>
#include <QString>


// Переменная
struct Variable {

    QString name;           // имя
    QString type;           // тип
    QString description;    // описание

    Variable(const QString& name = "", const QString& type = "", const QString& description = "");
};

// Функция
struct Function {

    QString name;           // Имя
    QString type;           // Тип
    int paramsCount;        // Количество входных параметров
    QString description;    // Описание

    Function(const QString& name = "", const QString& type = "", int paramsCount = 0, const QString& description = "");
};

// Объединение
struct Union {

    QString name;               // Имя
    QList<Variable> variables;  // Поля
    QList<Function> functions;  // Методы

    Union(const QString& name = "", const QList<Variable>& variables = {}, const QList<Function>& functions = {});

};

// Структура
struct Structure {

    QString name;               // Имя
    QList<Variable> variables;  // Поля
    QList<Function> functions;  // Методы

};

// Класс
struct Class {

    QString name;               // Имя
    QList<Variable> variables;  // Поля
    QList<Function> functions;  // Методы

};

// Перечисление
struct Enum {

    QString name;                   // Имя
    QMap<QString, QString> values;  // Значения

};

#endif // CODEENTITY_H
