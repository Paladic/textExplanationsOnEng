#include "teexception.h"

TEException::TEException(const ErrorType errorType, const QString &filename, const int line, const QList<QString> args)
    : errorType(errorType), filename(filename), line(line), args(args)
{
}

TEException::TEException(const ErrorType errorType,  const QString &filename, const QList<QString> args)
    : TEException(errorType, filename, 0, args)
{
}

TEException::TEException(const ErrorType errorType,  const int line, const QList<QString> args)
    : TEException(errorType, "", line, args)
{
}

TEException::TEException(const ErrorType errorType, const QList<QString> args)
    : TEException(errorType, "", 0, args)
{
}

QString TEException::what() const {

    QString message = "Error: ";

    if(this->filename != ""){
        message += "\"" + this->filename + "\"" + (this->line > 0? " line " + QString::number(this->line) : "") + ": ";
    }

    switch(this->errorType) {

    case ErrorType::InputFileNotFound:
        message += "invalid input file path. The file may not exist or there is no read access.";
        break;
    case ErrorType::InputCopyFileCannotBeCreated:
        message += "";
        break;
    case ErrorType::OutputFileCannotBeCreated:
        message += "invalid output file path. The specified location may not exist or there are no write permissions.";
        break;
    case ErrorType::Parssing:
        message += "a syntax error was detected while processing an XML file.";
        break;
    case ErrorType::MissingRootElemnt:
        message += "The root element <root> is missing.";
        break;
    case ErrorType::UnexpectedElement:
        message += "the element got: <{1}>. The expected: {2}.";
        break;
    case ErrorType::UnexpectedAttribute:
        message += "the attribute got \"{1}\". The expected: {2}.";
        break;
    case ErrorType::MissingRequiredChildElement:
        message += "the element <{1}> is missing.";
        break;
    case ErrorType::MissingRequiredAttribute:
        message += "the attribute \"{1}\" is missing.";
        break;
    case ErrorType::DuplicateElement:
        message += "element \"{1}\" occurs more than the allowed number of times.";
        break;
    case ErrorType::DuplicateAttribute:
         message += "attribute <{1}> occurs more than the allowed number of times.";
        break;
    case ErrorType::EmptyElementValue:
        message += "the value of the <{1}> element is empty.";
        break;
    case ErrorType::EmptyAttributeName:
        message += "the value of the \"{1}\" attribute is empty.";
        break;
    case ErrorType::ParamsCountFunctionMissmatch:
        message += "the number of parameters specified in <expression> ({1}) does not match the specified number in <paramsCount> ({2}) for the \"{3}\" function.";
        break;
    case ErrorType::InputSizeExceeded:
        message += "the text value \"{1}\" exceeded the allowed length. Current - {2}, Expected - {3}.";
        break;
    case ErrorType::UndefinedId:
        message += "the identifier \"{1}\" is not defined in the value of the <expression> element.";
        break;
    case ErrorType::InvalidSymbol:
        message += "the value of the <expression> element contains an invalid character \"{1}\".";
        break;
    case ErrorType::MissingOperand:
        message += "in the context of the <expression> element, the operand \"{1}\" lacks an operation.";
        break;
    case ErrorType::MissingOperations:
        message += "in the context of the <expression> element, the operation \"{1}\" lacks an operands.";
        break;
    case ErrorType::MultipleIncrementDecrement:
        message += "in the context of the <expression> element, the value of the \"{1}\" element cannot be incremented or decremented more than once.";
        break;
    case ErrorType::NeverUsedElement:
        message += "element with name \"{1}\" never occurs in element <expression>";
        break;
    case ErrorType::ParamsCountDescriptionDifference:
        message += "the number of substitutions of sections in the <description> of the <function> element by the description of incoming arguments exceeds the value of the \"paramsCount\" attribute of the <function> element.";
        break;
    case ErrorType::NonUniqueName:
        message += "the value \"{1}\" of the attribute \"name\" for element <{2}> is not unique";
        break;
    case ErrorType::InvalidName:
        message += "The \"{1}\" value of the \"name\" attribute must begin with a Latin letter or the special character \"_\" (underscore) and contain only Latin letters, numbers, and the special character \"_\" (underscore).";
        break;
    case ErrorType::UnidentifedType:
        message += "the \"{1}\" value of the \"type\" attribute contains an unidentified type. The data type must be one of the supported types or it can be a user-defined data type described in the elements <unions>; <structures>; <classes>; <enums>.";
        break;
    case ErrorType::InvalidParamsCount:
        message += "value \"{1}\" of the \"paramsCount\" attribute contains an invalid value. Expected: positive integer from 0 to 20 inclusive.";
        break;
    default:
        message += "unknown error";
        break;
    }

    //TODO: добавить функцию замены переменных
    //if(args.count() > 0) {
    // message = ...
    //}

    return message;
}

ErrorType TEException::getErrorType() const
{
    return errorType;
}

int TEException::getLine() const
{
    return line;
}

QList<QString> TEException::getArgs() const
{
    return args;
}

QString TEException::replacePlaceholders(QString pattern, const QList<QString> args) const
{
    // Для каждого аргумента
    for (int i = 0; i < args.size(); i++) {
        // Формируем плейсхолдер вида {n} и т.д.
        QString placeholder = "{" + QString::number(i + 1) + "}";
        // Заменяем вхождение плейсхолдера на соответствующий ему аргумент
        pattern.replace(placeholder, args[i]);
    }
    return pattern;
}
