#include "expressionxmlparser.h"

const QList<QString> ExpressionXmlParser::supportedDataTypesForVar = { "int", "float", "double", "char", "bool", "string" };

void ExpressionXmlParser::readDataFromXML(const QString& inputFilePath, Expression &expression) {
bool ExpressionXmlParser::isLatinLetter(const QChar c) {
    // Явная проверка латинских букв
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

}
