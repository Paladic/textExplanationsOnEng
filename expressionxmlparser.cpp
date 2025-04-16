#include "expressionxmlparser.h"
#include "teexception.h"

const QList<QString> ExpressionXmlParser::supportedDataTypesForVar = { "int", "float", "double", "char", "bool", "string" };

void ExpressionXmlParser::readDataFromXML(const QString& inputFilePath, Expression &expression) {
bool ExpressionXmlParser::isLatinLetter(const QChar c) {
    // Явная проверка латинских букв
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void ExpressionXmlParser::validateAttributes(const QDomElement& curElement, const QList<QString>& attributes) {

    QDomNamedNodeMap getAttributes = curElement.attributes();
    for (int i = 0; i < getAttributes.length(); i++) {
        QDomAttr attribute = getAttributes.item(i).toAttr();

        // Проверяем, есть ли этот атрибут в списке elements
        if (!attributes.contains(attribute.name()) || attributes.count() == 0) {
            throw TEException(ErrorType::UnexpectedAttribute, attribute.lineNumber(), QList<QString>{attribute.name(), attributes.join("; ")});
        }
    }
}

void ExpressionXmlParser::validateChildElements(const QDomElement& curElement, const QHash<QString, int>& elements) {

    QDomNode childNode = curElement.firstChild();
    while (!childNode.isNull()) {
        if (childNode.isElement()) {
            QDomElement childElement = childNode.toElement();
            QString childName = childElement.tagName();

            if (!elements.contains(childName) || elements.count() == 0) {
                throw TEException(ErrorType::UnexpectedElement, childElement.lineNumber(), QList<QString>{childName, elements.keys().join("; ")});
            }
            else {
                int count = countDirectChildren(curElement, childName);
                int value = elements.value(childName);
                if(count > value)
                    throw TEException(ErrorType::DuplicateElement, childElement.lineNumber(), QList<QString>{childName});
            }
        }

        childNode = childNode.nextSibling();
    }
}

void ExpressionXmlParser::validateRequiredAttributes(const QDomElement& curElement, const QList<QString>& attributes) {

    QListIterator<QString> iter(attributes);

    while(iter.hasNext()){
        QString it = iter.next();
        if (!curElement.hasAttribute(it)) {
            throw TEException(ErrorType::MissingRequiredAttribute, curElement.lineNumber(), QList<QString>{it});
        }
    }

}

void ExpressionXmlParser::validateRequiredChildElements(const QDomElement& curElement, const QList<QString>& elements) {

    QListIterator<QString> iter(elements);
    while(iter.hasNext()){
        QString it = iter.next();

        bool foundCurElement = false;
        QDomNode childNode = curElement.firstChild();
        while (!childNode.isNull()) {
            if (childNode.isElement() && childNode.toElement().tagName() == it) {
                foundCurElement = true;
                break;
            }
            childNode = childNode.nextSibling();
        }

        if (!foundCurElement) {
            throw TEException(ErrorType::MissingRequiredChildElement, curElement.lineNumber(), QList<QString>{it});
        }
    }
}

int ExpressionXmlParser::countDirectChildren(const QDomElement& element, const QString& childName) {
    int count = 0;

    QDomNode childNode = element.firstChild();
    while (!childNode.isNull()) {
        if (childNode.isElement() && childNode.toElement().tagName() == childName) {
            count++;
        }
        childNode = childNode.nextSibling();
    }

    return count;
}

