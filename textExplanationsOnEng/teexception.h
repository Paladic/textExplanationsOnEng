/*!
 * \file
 * \brief Заголовочный файл, содержащий описание класса TEException и перечисления типов ошибок ErrorType
 */

#ifndef TEEXCEPTION_H
#define TEEXCEPTION_H

#include <QList>
#include <QString>
#include <QHash>

/*! \brief Перечисление возможных типов ошибок при обработке XML */
enum class ErrorType {
    // Ошибки файлов
    InputFileNotFound,               //!< Входной файл не существует или недоступен
    InputCopyFileCannotBeCreated,   //!< Ошибка создания копии входного файла
    OutputFileCannotBeCreated,      //!< Ошибка создания выходного файла

    // Общие ошибки формата XML
    Parsing,                         //!< Ошибка разбора XML
    MissingRootElemnt,              //!< Отсутствие корневого элемента <root>
    UnexpectedElement,              //!< Неожиданный элемент в структуре XML
    UnexpectedAttribute,            //!< Неожиданный атрибут в элементе
    MissingRequiredChildElement,    //!< Отсутствие обязательного дочернего элемента
    MissingRequiredAttribute,       //!< Отсутствие обязательного атрибута
    DuplicateElement,               //!< Дублирование элемента
    DuplicateAttribute,             //!< Дублирование атрибута
    EmptyElementValue,              //!< Пустое значение элемента
    EmptyAttributeName,             //!< Пустое имя атрибута
    ParamsCountFunctionMissmatch,   //!< Несовпадение между expression и paramsCount
    InputSizeExceeded,              //!< Превышен допустимый размер входных данных
    InputElementsExceeded,          //!< Превышено допустимое количество элементов

    // Ошибки формата <expression>
    UndefinedId,                    //!< Использование неопределённой сущности
    InvalidSymbol,                  //!< Недопустимый символ в выражении
    InputDataExprSizeExceeded,      //!< Превышение размера выражения
    MissingOperand,                 //!< Отсутствует операнд для операции
    MissingOperations,              //!< Отсутствует операция для операндов
    MultipleIncrementDecrement,     //!< Несколько инкрементов/декрементов на одну переменную
    NeverUsedElement,               //!< Неиспользуемая сущность

    // Ошибки описания функции
    ParamsCountDescriptionDifference, //!< Несоответствие между количеством описаний и параметров

    // Ошибки атрибута name
    NonUniqueName,                  //!< Неуникальное имя
    InvalidName,                    //!< Недопустимые символы в имени

    // Ошибки атрибута type
    UnidentifedType,                //!< Неопределённый тип данных
    InvalidType,                    //!< Недопустимые символы в типе

    // Ошибки атрибута paramsCount
    InvalidParamsCount,             //!< Неверный формат paramsCount
    MissingReplacementArguments,    //!< Отсутствуют аргументы для замены в шаблоне
    VariableWithVoidType            //!< Переменная имеет недопустимый тип void
};

/*! \brief Класс TEException инкапсулирует информацию об ошибке при обработке выражения */
class TEException
{
public:

    TEException(const ErrorType errorType, const QString &filename, const int line, const QList<QString> args = QList<QString>());
    TEException(const ErrorType errorType, const int line, const QList<QString> args = QList<QString>());
    TEException(const ErrorType errorType, const QString &filename, const QList<QString> args = QList<QString>());
    TEException(const ErrorType errorType, const QList<QString> args = QList<QString>());

    /*!
     * \brief Конструктор с указанием типа ошибки, имени файла, строки и аргументов
     * \param[in] errorType Тип ошибки
     * \param[in] filename Имя файла, в котором возникла ошибка
     * \param[in] line Номер строки, на которой произошла ошибка
     * \param[in] args Аргументы для шаблона сообщения об ошибке
     */

    /*!
     * \brief Конструктор с указанием типа ошибки, строки и аргументов
     * \param[in] errorType Тип ошибки
     * \param[in] line Номер строки, на которой произошла ошибка
     * \param[in] args Аргументы для шаблона сообщения об ошибке
     */

    /*!
     * \brief Конструктор с указанием типа ошибки, имени файла и аргументов
     * \param[in] errorType Тип ошибки
     * \param[in] filename Имя файла, в котором произошла ошибка
     * \param[in] args Аргументы для шаблона сообщения об ошибке
     */

    /*!
     * \brief Конструктор с указанием типа ошибки и аргументов
     * \param[in] errorType Тип ошибки
     * \param[in] args Аргументы для шаблона сообщения об ошибке
     */

    /*!
     * \brief Получить текст сообщения об ошибке
     * \return Строка с сообщением об ошибке
     */
    QString what() const;

    /*!
     * \brief Получить тип ошибки
     * \return Значение перечисления ErrorType
     */
    ErrorType getErrorType() const;

    /*!
     * \brief Получить номер строки, где возникла ошибка
     * \return Номер строки (или -1, если не указан)
     */
    int getLine() const;

    /*!
     * \brief Получить аргументы, подставляемые в шаблон ошибки
     * \return Список аргументов
     */
    QList<QString> getArgs() const;

    /*!
     * \brief Подставить аргументы в строку-шаблон ошибки
     * \param[in] pattern Шаблон с плейсхолдерами (%1, %2, ...)
     * \param[in] args Список строк-аргументов
     * \return Строка с подставленными аргументами
     */
    QString replacePlaceholders(QString pattern, const QList<QString> args) const;

    /*! \brief Сопоставление типов ошибок и их шаблонов сообщений */
    static const QHash<ErrorType, QString> ErrorTypeNames;

private:
    ErrorType errorType;       //!< Тип ошибки
    QString filename;          //!< Имя файла, где возникла ошибка
    int line;                  //!< Номер строки
    QList<QString> args;       //!< Аргументы для подстановки в сообщение
};

#endif // TEEXCEPTION_H
