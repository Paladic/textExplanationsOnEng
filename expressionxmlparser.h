#ifndef EXPRESSIONXMLPARSER_H
#define EXPRESSIONXMLPARSER_H
#include "expression.h"
#include <QString>
class ExpressionXmlParser
{
public:

    static void readDataFromXML(const QString& inputFilePath, Expression& expression);

    //////////////////////////////////////////////////
    /// Константы
    /////////////////////////////////////////////////

    static constexpr int nameMaxLength = 32;
    static constexpr int descMaxLength = 256;
    static constexpr int expressionMaxLength = 1024;
    static constexpr int childElementsMaxCount = 20;
    static constexpr int functionParamsMaxCount = 5;


};

#endif // EXPRESSIONXMLPARSER_H
