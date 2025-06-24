/*!
 * \file
 * \brief Заголовочный файл, содержащий описание класса Expression — представления выражения и связанных сущностей
 */

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "expressionnode.h"
#include "teexception.h"

#include <QHash>
#include <QString>
#include <QStack>

/*!
 * \brief Класс, представляющий выражение и связанные с ним переменные, функции и пользовательские типы
 */
class Expression
{
public:
    Expression(

    /*!
     * \brief Конструктор Expression
     * \param[in] expr Строковое выражение
     * \param[in] vars Словарь переменных
     * \param[in] funcs Словарь функций
     * \param[in] unns Словарь объединений
     * \param[in] strucs Словарь структур
     * \param[in] cls Словарь классов
     * \param[in] enms Словарь перечислений
     */
        const QString& expr = "",
        const QHash<QString, Variable>& vars = {},
        const QHash<QString, Function>& funcs = {},
        const QHash<QString, Union>& unns = {},
        const QHash<QString, Structure>& strucs = {},
        const QHash<QString, Class>& cls = {},
        const QHash<QString, Enum>& enms = {}
        )
        : expression(expr)
        , variables(vars)
        , functions(funcs)
        , unions(unns)
        , structures(strucs)
        , classes(cls)
        , enums(enms)
    {}

    /*!
     * \brief Создание Expression из XML-файла
     * \param[in] path Путь к XML-файлу
     * \return Объект Expression
     */
    static Expression fromFile(const QString& path);

    /*!
     * \brief Получение всех пользовательских типов данных
     * \return Множество имён пользовательских типов
     */
    QSet<QString> getCustomDataTypes() const;

    /*!
     * \brief Преобразование выражения в строку
     * \return Строка выражения
     */
    QString ToQstring();

    /*!
     * \brief Построение текстового объяснения выражения
     * \param[in] node Узел выражения
     * \param[out] intermediateDescription Промежуточное объяснение
     * \param[in] className Имя класса (если применимо)
     * \param[in] parentOperType Тип родительской операции
     * \return Объяснение выражения
     */
    QString ToExplanation(const ExpressionNode* node, QString& intermediateDescription, const QString& className = "", OperationType parentOperType = OperationType::None) const;

    /*!
     * \brief Получение англоязычного объяснения выражения
     * \return Строка объяснения
     */
    QString getExplanationInEn();

    /*!
     * \brief Преобразование строки выражения в дерево ExpressionNode
     * \return Корень дерева
     */
    ExpressionNode* expressionToNodes();

    /*!
     * \brief Получение всех имён переменных, функций и т.д.
     * \return Множество имён
     */
    QSet<QString> getAllNames();

    /*!
     * \brief Получение типа сущности по строке
     * \param[in] str Имя
     * \return Тип сущности
     */
    EntityType getEntityTypeByStr(const QString& str);

    /*!
     * \brief Проверка, является ли имя константой
     */
    bool isConst(const QString& str);

    /*!
     * \brief Проверка, является ли имя переменной
     */
    bool isVariable(const QString& str);

    /*!
     * \brief Проверка, является ли имя функцией
     */
    static bool isFunction(const QString& str);

    /*!
     * \brief Проверка, является ли имя пользовательским типом
     */
    bool isCustomTypeWithFields(const QString& str);

    /*!
     * \brief Проверка, является ли имя перечислением
     */
    bool isEnum(const QString& str);

    /*!
     * \brief Проверка, является ли строка допустимым идентификатором
     */
    static bool isIdentifier(const QString& str);

    /*!
     * \brief Проверка, является ли символ латинской буквой
     */
    static bool isLatinLetter(const QChar c);

    /*!
     * \brief Построение описания аргументов функции
     * \param[in] functionArgs Аргументы функции
     * \param[out] intermediateDescription Промежуточное описание
     * \param[in] customDataType Тип, если это метод класса/структуры
     * \param[in] parentOperType Родительская операция
     * \return Список аргументов в виде строк
     */
    QList<QString> argsToDescr(const QList<ExpressionNode*>* functionArgs, QString& intermediateDescription, QString customDataType = "", OperationType parentOperType = OperationType::None) const;

    /*!
     * \brief Получение OperationType по строке
     * \param[in] str Строка операции
     * \return Тип операции
     */
    OperationType getOperationTypeByStr(const QString& str);

    /*!
     * \brief Удаление повторяющихся символов
     * \param[in] str Входная строка
     * \return Обновлённая строка без подряд идущих дубликатов
     */
    static QString removeConsecutiveDuplicates(const QString& str);

    /*!
     * \brief Установка нового выражения
     */
    void setExpression(const QString& newExpression);

    /*!
     * \brief Получение указателя на строку выражения
     */
    const QString* getExpression() const;

    /*!
     * \brief Получение указателя на словарь переменных
     */
    const QHash<QString, Variable>* getVariables() const;

    /*!
     * \brief Установка словаря переменных
     */
    void setVariables(const QHash<QString, Variable>& newVariables);

    /*!
     * \brief Получение переменной по имени
     */
    const Variable getVarByName(const QString& name) const;

    /*!
     * \brief Получение указателя на словарь функций
     */
    const QHash<QString, Function>* getFunctions() const;

    /*!
     * \brief Установка словаря функций
     */
    void setFunctions(const QHash<QString, Function>& newFunctions);

    /*!
     * \brief Получение функции по имени
     */
    const Function getFuncByName(const QString& name) const;

    /*!
     * \brief Получение указателя на словарь объединений
     */
    const QHash<QString, Union>* getUnions() const;

    /*!
     * \brief Установка словаря объединений
     */
    void setUnions(const QHash<QString, Union>& newUnions);

    /*!
     * \brief Получение объединения по имени
     */
    const Union getUnionByName(const QString& name) const;

    /*!
     * \brief Получение указателя на словарь структур
     */
    const QHash<QString, Structure>* getStructures() const;

    /*!
     * \brief Установка словаря структур
     */
    void setStructures(const QHash<QString, Structure>& newStructures);

    /*!
     * \brief Получение структуры по имени
     */
    const Structure getStructByName(const QString& name) const;

    /*!
     * \brief Получение указателя на словарь классов
     */
    const QHash<QString, Class>* getClasses() const;

    /*!
     * \brief Установка словаря классов
     */
    void setClasses(const QHash<QString, Class>& newClasses);

    /*!
     * \brief Получение класса по имени
     */
    const Class getClassByName(const QString& name) const;

    /*!
     * \brief Получение указателя на словарь перечислений
     */
    const QHash<QString, Enum>* getEnums() const;

    /*!
     * \brief Установка словаря перечислений
     */
    void setEnums(const QHash<QString, Enum>& newEnums);

    /*!
     * \brief Получение перечисления по имени
     */
    const Enum getEnumByName(const QString& name) const;

    /*!
     * \brief Получение переменной по имени из пользовательского типа
     */
    const Variable getVariableByNameFromCustomData(QString varName, QString dataName) const;

    /*!
     * \brief Получение функции по имени из пользовательского типа
     */
    const Function getFunctionByNameFromCustomData(QString funcName, QString dataName) const;

    /*!
     * \brief Проверка, является ли значение элементом перечисления
     */
    bool isEnumValue(const QString& value, const QString& enumName) const;

    /*!
     * \brief Получение пользовательского типа по имени
     */
    const CustomTypeWithFields getCustomTypeByName(const QString& typeName) const;

    /*!
     * \brief Получение всех имён переменных и функций пользовательского типа
     */
    void getCustomTypeFields(QSet<QString>& names, const CustomTypeWithFields& customType);

    /*!
     * \brief Разделение выражения на компоненты
     * \param[in] str Входная строка выражения
     * \return Список компонентов выражения
     */
    static QStringList splitExpression(const QString& str);

    /*!
     * \brief Очистка и стандартизация типа данных
     * \param[in] dataType Исходный тип
     * \return Обновлённый тип
     */
    QString sanitizeDataType(const QString& dataType);
private:
    QString expression; ///< Исходное строковое выражение
    QHash<QString, Variable> variables; ///< Список переменных
    QHash<QString, Function> functions; ///< Список функций
    QHash<QString, Union> unions; ///< Пользовательские типы: объединения
    QHash<QString, Structure> structures; ///< Пользовательские типы: структуры
    QHash<QString, Class> classes; ///< Пользовательские типы: классы
    QHash<QString, Enum> enums; ///< Пользовательские типы: перечисления
};

#endif // EXPRESSION_H
