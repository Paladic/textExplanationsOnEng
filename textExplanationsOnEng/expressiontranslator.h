#ifndef EXPRESSIONTRANSLATOR_H
#define EXPRESSIONTRANSLATOR_H

#include "codeentity.h"
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

#include <QHash>
#include <QString>

class ExpressionTranslator
{
public:
    ExpressionTranslator();

    static const QHash<OperationType, QString> Templates;

    static QString getExplanation(const QString &description, const QList<QString> &arguments);
};

#endif // EXPRESSIONTRANSLATOR_H
