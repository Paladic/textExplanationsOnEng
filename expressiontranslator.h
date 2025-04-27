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
    static QString replacePlaceholders(const QString &pattern, const QList<QString> &args, QRegularExpression& numberedPlaceholderRegex);
};

#endif // EXPRESSIONTRANSLATOR_H
