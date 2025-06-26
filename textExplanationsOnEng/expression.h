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
    explicit Expression(
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

    /*!
 * \brief Обрабатывает операцию и добавляет соответствующий узел в стек.
 * \param[in] token Токен, представляющий операцию.
 * \param[in,out] nodeStack Стек узлов выражения.
 * \param[in,out] operationCounter Счётчик операций в выражении.
 * \param[in] tokens Полный список токенов выражения.
 * \param[in] i Итератор текущей позиции в списке токенов.
 */
    void processOperation(const QString &token, QStack<ExpressionNode *> &nodeStack, int &operationCounter, const QStringList &tokens, QStringList::const_iterator i);

    /*!
 * \brief Обрабатывает константу и добавляет соответствующий узел в стек.
 * \param[in] token Токен, представляющий константу.
 * \param[in,out] nodeStack Стек узлов выражения.
 */
    void processConst(const QString &token, QStack<ExpressionNode *> &nodeStack);

    /*!
 * \brief Обрабатывает переменную и добавляет соответствующий узел в стек.
 * \param[in] token Токен, представляющий переменную.
 * \param[in,out] nodeStack Стек узлов выражения.
 * \param[in,out] usedElements Набор используемых переменных.
 * \param[in] customDataTypes Набор пользовательских типов данных.
 * \param[in] tokens Полный список токенов выражения.
 * \param[in] i Итератор текущей позиции в списке токенов.
 */
    void processVariable(const QString &token, QStack<ExpressionNode *> &nodeStack, QSet<QString> &usedElements, const QSet<QString> &customDataTypes, const QStringList &tokens, QStringList::const_iterator i);

    /*!
 * \brief Обрабатывает перечисление (enum) и добавляет соответствующий узел в стек.
 * \param[in] token Токен, представляющий элемент перечисления.
 * \param[in,out] nodeStack Стек узлов выражения.
 * \param[in,out] usedElements Набор используемых элементов перечисления.
 */
    void processEnum(const QString &token, QStack<ExpressionNode *> &nodeStack, QSet<QString> &usedElements);

    /*!
 * \brief Обрабатывает функцию и добавляет соответствующий узел в стек.
 * \param[in] token Токен, представляющий функцию.
 * \param[in,out] nodeStack Стек узлов выражения.
 * \param[in] customDataTypes Набор пользовательских типов данных.
 * \param[in,out] usedElements Набор используемых элементов.
 * \param[in] tokens Полный список токенов выражения.
 * \param[in] i Итератор текущей позиции в списке токенов.
 */
    void processFunction(const QString &token, QStack<ExpressionNode *> &nodeStack, const QSet<QString> &customDataTypes, QSet<QString> &usedElements, const QStringList &tokens, QStringList::const_iterator i);

    /*!
 * \brief Определяет тип переменной на основе контекста.
 * \param[in] token Токен, представляющий переменную.
 * \param[in,out] nodeStack Стек узлов выражения.
 * \param[in] tokens Полный список токенов выражения.
 * \param[in] i Итератор текущей позиции в списке токенов.
 * \param[out] className Название класса, к которому принадлежит переменная.
 * \return Тип переменной.
 */
    QString handleVariableTypeInference(const QString &token, QStack<ExpressionNode *> &nodeStack, const QStringList &tokens, QStringList::const_iterator i, QString &className);

    /*!
 * \brief Завершает обработку узлов и формирует результирующее выражение.
 * \param[in,out] nodeStack Стек узлов выражения.
 * \param[in] expression Исходное строковое выражение.
 * \param[in] operationCounter Счётчик операций в выражении.
 * \param[in] usedElements Набор используемых элементов.
 */
    void finalizeNodeProcessing(QStack<ExpressionNode *> &nodeStack, const QString &expression, int operationCounter, const QSet<QString> &usedElements);

    /*!
     * \brief Обрабатывает узел типа переменной.
     * \param[in] node Узел выражения, представляющий переменную.
     * \param[in] className Название класса, если переменная принадлежит классу.
     * \param[in] parentOperType Тип родительской операции.
     * \return Описание узла в виде строки.
     */
    QString handleVariableNode(const ExpressionNode *node, const QString &className, OperationType parentOperType) const;

    /*!
     * \brief Обрабатывает узел типа функции.
     * \param[in] node Узел выражения, представляющий функцию.
     * \param[in,out] intermediateDescription Промежуточное описание функции.
     * \param[in] className Название класса, если функция принадлежит классу.
     * \return Описание узла в виде строки.
     */
    QString handleFunctionNode(const ExpressionNode *node, QString &intermediateDescription, const QString &className) const;

    /*!
     * \brief Обрабатывает узел типа константы.
     * \param[in] node Узел выражения, представляющий константу.
     * \return Описание узла в виде строки.
     */
    QString handleConstNode(const ExpressionNode *node) const;

    /*!
     * \brief Обрабатывает узел типа операции.
     * \param[in] node Узел выражения, представляющий операцию.
     * \param[in,out] intermediateDescription Промежуточное описание операции.
     * \param[in] className Название класса, если операция связана с классом.
     * \param[in] parentOperType Тип родительской операции.
     * \param[in,out] descOfLeftNode Описание левого поддерева.
     * \param[in,out] descOfRightNode Описание правого поддерева.
     * \return Описание узла в виде строки.
     */
    QString handleOperationNode(const ExpressionNode *node, QString &intermediateDescription, const QString &className, OperationType parentOperType, QString &descOfLeftNode, QString &descOfRightNode) const;
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
