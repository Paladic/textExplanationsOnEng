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

};

// Функция
struct Function {

    QString name;           // Имя
    QString type;           // Тип
    int paramsCount;        // Количество входных параметров
    QString description;    // Описание

};

// Объединение
struct Union {

    QString name;               // Имя
    QList<Variable> variables;  // Поля
    QList<Function> functions;  // Методы

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
