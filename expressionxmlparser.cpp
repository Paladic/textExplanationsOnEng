#include "expressionxmlparser.h"
#include "teexception.h"

const QList<QString> ExpressionXmlParser::supportedDataTypesForVar = { "int", "float", "double", "char", "bool", "string" };

void ExpressionXmlParser::readDataFromXML(const QString& inputFilePath, Expression &expression) {
QHash<QString, Enum> ExpressionXmlParser::parseEnums(const QDomElement &_enums)
{

    validateElement(_enums, QList<QString>{}, QHash<QString, int>{{"enum", 20}}, false);

    QHash<QString, Enum> result;
    if(_enums.childNodes().isEmpty()) return result;

    QDomNode childNode = _enums.firstChild();
    while (!childNode.isNull()) {

        Enum child = parseEnum(childNode.toElement());
        result.insert(child.name, child);

        childNode = childNode.nextSibling();

    }

    return result;

}

Enum ExpressionXmlParser::parseEnum(const QDomElement &_enum)
{
    validateElement(_enum, QList<QString>{"name"}, QHash<QString, int>{{"value", 20}}, true);

    QString name = parseName(_enum);
    QHash<QString, QString> values = parseEnumValues(_enum);

    return Enum(name, values);
}

QHash<QString, QString> ExpressionXmlParser::parseEnumValues(const QDomElement &_values)
{
    QHash<QString, QString> result;
    // Перебираем все элементы <value> внутри <enum>
    QDomNodeList valueNodes = _values.elementsByTagName("value");
    for (int i = 0; i < valueNodes.size(); ++i) {
        QDomElement valueElement = valueNodes.at(i).toElement();

        validateElement(valueElement, QList<QString>{"name"}, QHash<QString, int>{{"description", 1}}, true);

        QString valueName = valueElement.attribute("name");
        QString description = valueElement.firstChildElement("description").text();

        result.insert(valueName, description);
    }

    return result;
}

QString ExpressionXmlParser::parseName(const QDomElement &element) {

    QString res = element.attribute("name");
    if(res.isEmpty() || res.length() < 1) throw TEException(ErrorType::EmptyAttributeName);
    if(res.length() > nameMaxLength) throw TEException(ErrorType::InputSizeExceeded, element.lineNumber(), QList<QString>{"name", QString::number(res.length()), QString::number(nameMaxLength)});

    // Первый символ - латинская буква или _
    const QChar first = res[0];
    if (!(isLatinLetter(first) || first == '_')) {
        throw TEException(ErrorType::InvalidName, element.lineNumber());
    }

    // Остальные символы - латинские буквы, цифры или _
    for(int i = 0; i < res.length(); i++) {
        if (!(isLatinLetter(res[i]) || res[i].isDigit() || res[i] == '_')) {
            throw TEException(ErrorType::InvalidName, element.lineNumber(), QList<QString>{res});
        }
    }

    return res;

}

QString ExpressionXmlParser::parseDescription(const QDomElement &_description) {

    QString res = _description.text();

    if(res.isEmpty()) throw TEException(ErrorType::EmptyElementValue);

    if(res.length() > descMaxLength) throw TEException(ErrorType::InputSizeExceeded, _description.lineNumber(), QList<QString>{"description", QString::number(res.length()), QString::number(descMaxLength)});

    return res;
}

bool ExpressionXmlParser::isLatinLetter(const QChar c) {
    // Явная проверка латинских букв
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void ExpressionXmlParser::validateElement(const QDomElement& curElement, const QList<QString>& allowedAttributes, const QHash<QString, int>& allowedElements, bool checkRequired, bool textIsError) {

    //if(textIsError && (curElement.isText() || curElement) throw TEException(ErrorType::XML_INPUT_SIZE_EXCEEDED, this->inputFilePath, curElement.lineNumber(), QList<QString>{curElement.text(), QString::number(curElement.text().length()), "0"});

    validateAttributes(curElement, allowedAttributes);
    validateChildElements(curElement, allowedElements);

    if (checkRequired) {
        validateRequiredAttributes(curElement, allowedAttributes);
        validateRequiredChildElements(curElement, allowedElements.keys());
    }

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

