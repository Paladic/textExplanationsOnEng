/*!
 * \file
 * \brief Заголовочный файл, содержащий объявления функций для парсинга XML-файла в структуру Expression
 */

#ifndef EXPRESSIONXMLPARSER_H
#define EXPRESSIONXMLPARSER_H

#include "expression.h"
#include <QDomDocument>
#include <QString>
#include <QTemporaryFile>

/*!
 * \brief Класс для парсинга XML-файла в структуру Expression
 */
class ExpressionXmlParser
{
public:
    /*!
     * \brief Обработка XML-файла и преобразование его в структуру Expression
     * \param[in] inputFilePath Путь к XML-файлу
     * \param[out] expression Объект Expression, заполняемый данными из XML
     * \throw QList<TEException> Список ошибок, возникших при парсинге
     */
    static void readDataFromXML(const QString& inputFilePath, Expression& expression);

private:
    //////////////////////////////////////////////////
    /// Методы для работы с файлами
    //////////////////////////////////////////////////

    /*!
     * \brief Считывание XML-документа из файла
     * \param[in] filePath Путь к XML-файлу
     * \param[out] errors Список ошибок
     * \return Объект QDomDocument, считанный из файла
     * \throw NULL исключение при обработке
     */
    static QDomDocument readXML(const QString& filePath, QList<TEException>& errors);

    /*!
     * \brief Создание временной копии исходного XML-файла
     * \param[in] sourceFilePath Путь к исходному файлу
     * \param[out] errors Список ошибок
     * \return Указатель на временный файл
     * \throw TEException исключение при обработке
     */
    static QTemporaryFile* createTempCopy(const QString& sourceFilePath, QList<TEException>& errors);

    //////////////////////////////////////////////////
    /// Методы для исправления XML формата
    //////////////////////////////////////////////////

    /*!
     * \brief Экранирование специальных символов в XML-тексте
     * \param[in] text Исходный текст
     * \return Экранированный текст
     */
    static QString escapeXmlText(const QString& text);

    /*!
     * \brief Исправление флагов в XML
     * \param[in] xmlString XML-строка
     * \return Обновлённая строка XML
     */
    static QString fixXmlFlags(const QString& xmlString);

    /*!
     * \brief Исправление выражений в XML
     * \param[in] xmlString XML-строка
     * \return Исправленное выражение
     */
    static QString fixXmlExpression(const QString& xmlString);

    /*!
     * \brief Исправление описаний в XML
     * \param[in] xmlString XML-строка
     * \return Строка с исправленным описанием
     */
    static QString fixXmlDescriptions(const QString& xmlString);

    //////////////////////////////////////////////////
    /// Методы для обработки XML
    //////////////////////////////////////////////////

    /*!
     * \brief Основной метод для разбора XML-документа
     * \param[in] doc XML-документ
     * \param[out] expression Структура Expression
     * \param[out] errors Список ошибок
     * \throw TEException исключение при обработке
     */
    static void parseQDomDocument(const QDomDocument& doc, Expression& expression, QList<TEException>& errors);

    /*!
     * \brief Извлечение выражения из XML-элемента
     * \param[in] _expression Элемент XML
     * \param[out] errors Список ошибок
     * \return Выражение в виде строки
     */
    static QString parseExpression(const QDomElement& _expression, QList<TEException>& errors);

    /*!
     * \brief Парсинг списка переменных
     * \param[in] _variables Элемент <variables>
     * \param[out] errors Список ошибок
     * \return Хэш-таблица переменных
     */
    static QHash<QString, Variable> parseVariables(const QDomElement& _variables, QList<TEException>& errors);

    /*!
     * \brief Парсинг одной переменной
     * \param[in] _variable Элемент <variable>
     * \param[out] errors Список ошибок
     * \return Объект переменной
     */
    static Variable parseVariable(const QDomElement& _variable, QList<TEException>& errors);

    /*!
     * \brief Парсинг списка функций
     * \param[in] _functions Элемент <functions>
     * \param[out] errors Список ошибок
     * \return Хэш-таблица функций
     */
    static QHash<QString, Function> parseFunctions(const QDomElement& _functions, QList<TEException>& errors);

    /*!
     * \brief Парсинг одной функции
     * \param[in] _function Элемент <function>
     * \param[out] errors Список ошибок
     * \return Объект функции
     */
    static Function parseFunction(const QDomElement& _function, QList<TEException>& errors);

    /*!
     * \brief Парсинг списка объединений (union)
     * \param[in] _unions Элемент <unions>
     * \param[out] errors Список ошибок
     * \return Хэш-таблица объединений
     */
    static QHash<QString, Union> parseUnions(const QDomElement& _unions, QList<TEException>& errors);

    /*!
     * \brief Парсинг одного объединения
     * \param[in] _union Элемент <union>
     * \param[out] errors Список ошибок
     * \return Объект Union
     */
    static Union parseUnion(const QDomElement& _union, QList<TEException>& errors);

    /*!
     * \brief Парсинг списка структур (struct)
     * \param[in] _structures Элемент <structures>
     * \param[out] errors Список ошибок
     * \return Хэш-таблица структур
     */
    static QHash<QString, Structure> parseStructures(const QDomElement& _structures, QList<TEException>& errors);

    /*!
     * \brief Парсинг одной структуры
     * \param[in] _structure Элемент <structure>
     * \param[out] errors Список ошибок
     * \return Объект Structure
     */
    static Structure parseStructure(const QDomElement& _structure, QList<TEException>& errors);

    /*!
     * \brief Парсинг списка классов
     * \param[in] _classes Элемент <classes>
     * \param[out] errors Список ошибок
     * \return Хэш-таблица классов
     */
    static QHash<QString, Class> parseClasses(const QDomElement& _classes, QList<TEException>& errors);

    /*!
     * \brief Парсинг одного класса
     * \param[in] _class Элемент <class>
     * \param[out] errors Список ошибок
     * \return Объект Class
     */
    static Class parseClass(const QDomElement& _class, QList<TEException>& errors);

    /*!
     * \brief Парсинг списка перечислений
     * \param[in] _enums Элемент <enums>
     * \param[out] errors Список ошибок
     * \return Хэш-таблица перечислений
     */
    static QHash<QString, Enum> parseEnums(const QDomElement& _enums, QList<TEException>& errors);

    /*!
     * \brief Парсинг одного перечисления
     * \param[in] _enum Элемент <enum>
     * \param[out] errors Список ошибок
     * \return Объект Enum
     */
    static Enum parseEnum(const QDomElement& _enum, QList<TEException>& errors);

    /*!
     * \brief Парсинг значений перечисления
     * \param[in] _values Элемент <values>
     * \param[out] errors Список ошибок
     * \return Хэш-таблица значений
     */
    static QHash<QString, QString> parseEnumValues(const QDomElement& _values, QList<TEException>& errors);

    /*!
     * \brief Извлечение описания
     * \param[in] _description Элемент <description>
     * \param[out] errors Список ошибок
     * \return Строка описания
     */
    static QString parseDescription(const QDomElement& _description, QList<TEException>& errors);

    /*!
     * \brief Извлечение имени элемента
     * \param[in] element Элемент XML
     * \param[out] errors Список ошибок
     * \return Имя в виде строки
     */
    static QString parseName(const QDomElement& element, QList<TEException>& errors);

    /*!
     * \brief Извлечение типа данных
     * \param[in] element Элемент XML
     * \param[out] errors Список ошибок
     * \return Тип данных
     */
    static QString parseType(const QDomElement& element, QList<TEException>& errors);

    /*!
     * \brief Извлечение количества параметров
     * \param[in] element Элемент XML
     * \param[out] errors Список ошибок
     * \return Количество параметров
     */
    static int parseParamsCount(const QDomElement& element, QList<TEException>& errors);

    //////////////////////////////////////////////////
    /// Методы для валидации XML
    //////////////////////////////////////////////////

    /*!
     * \brief Проверка структуры элемента и его содержимого
     * \param[in] curElement Проверяемый элемент
     * \param[in] allowedAttributes Допустимые атрибуты
     * \param[in] allowedElements Допустимые дочерние элементы
     * \param[out] errors Список ошибок
     * \param[in] checkRequired Проверять ли обязательные атрибуты
     * \param[in] textIsError Считать ли текст внутри ошибкой
     */
    static void validateElement(const QDomElement& curElement, const QList<QString>& allowedAttributes, const QHash<QString, int>& allowedElements, QList<TEException>& errors, bool checkRequired = true, bool textIsError = true);

    /*!
     * \brief Проверка атрибутов элемента
     * \param[in] curElement Элемент XML
     * \param[in] attributes Список атрибутов
     * \param[out] errors Список ошибок
     */
    static void validateAttributes(const QDomElement& curElement, const QList<QString>& attributes, QList<TEException>& errors);

    /*!
     * \brief Проверка количества допустимых дочерних элементов
     */
    static void validateChildElements(const QDomElement& curElement, const QHash<QString, int>& allowedElements, QList<TEException>& errors);

    /*!
     * \brief Проверка обязательных атрибутов
     */
    static void validateRequiredAttributes(const QDomElement& curElement, const QList<QString>& attributes, QList<TEException>& errors);

    /*!
     * \brief Проверка обязательных дочерних элементов
     */
    static void validateRequiredChildElements(const QDomElement& curElement, const QList<QString>& elements, QList<TEException>& errors);

    /*!
     * \brief Подсчёт количества прямых потомков элемента по имени
     */
    static int countDirectChildren(const QDomElement& element, const QString& childName);

    /*!
     * \brief Проверка, является ли символ латинской буквой
     * \param[in] c Символ
     * \return true, если символ латинский
     */
    static bool isLatinLetter(const QChar c);

    //////////////////////////////////////////////////
    /// Константы
    //////////////////////////////////////////////////

    /*! \brief Максимальная длина имени */
    static constexpr int nameMaxLength = 32;

    /*! \brief Максимальная длина описания */
    static constexpr int descMaxLength = 256;

    /*! \brief Максимальная длина выражения */
    static constexpr int expressionMaxLength = 1024;

    /*! \brief Максимальное количество дочерних элементов */
    static constexpr int childElementsMaxCount = 20;

    /*! \brief Максимальное количество параметров функции */
    static constexpr int functionParamsMaxCount = 5;

    /*! \brief Поддерживаемые типы данных для переменных */
    static const QList<QString> supportedDataTypesForVar;
};

#endif // EXPRESSIONXMLPARSER_H
