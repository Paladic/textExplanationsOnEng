#include "teexception.h"

TEException::TEException(const ErrorType errorType, const QString &filename, const int line, const QList<QString> args) {

    this->errorType = errorType;
    this->filename = filename;
    this->line = line;
    this->args = args;

}

TEException::TEException(const ErrorType errorType, const QString &filename, const QList<QString> args) {

    TEException(errorType, filename, 0, args);

}

TEException::TEException(const ErrorType errorType, const QList<QString> args) {

    TEException(errorType, "", 0, args);
}
