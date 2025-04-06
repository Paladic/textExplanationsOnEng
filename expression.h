#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "codeentity.h"

#include <QHash>
#include <QString>


class Expression
{

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
