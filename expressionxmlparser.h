#ifndef EXPRESSIONXMLPARSER_H
#define EXPRESSIONXMLPARSER_H
#include "expression.h"
#include <QString>
class ExpressionXmlParser
{
public:

    static void readDataFromXML(const QString& inputFilePath, Expression& expression);

};

#endif // EXPRESSIONXMLPARSER_H
