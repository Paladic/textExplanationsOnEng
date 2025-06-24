/*!
 * \file
 * \brief Заголовочный файл, содержащий определения сущностей кода, типов операций и пользовательских структур
 */

#ifndef CODEENTITY_H
#define CODEENTITY_H

#include <QList>
#include <QHash>
#include <QSet>
#include <QString>

/*! \brief Перечисление типов сущностей */
enum class EntityType {
    Operation,              /*!< Операция */
    Const,                  /*!< Константа */
    Variable,               /*!< Переменная */
    Function,               /*!< Функция */
    CustomTypeWithFields,   /*!< Пользовательский тип с полями */
    Enum,                   /*!< Перечисление */
    Undefined               /*!< Неопределённый тип */
};

/*! \brief Арность операции */
enum class OperationArity {
    Unary,      /*!< Унарная операция */
    Binary      /*!< Бинарная операция */
};

/*! \brief Типы операций */
enum class OperationType {
    PrefixIncrement, PrefixDecrement, ArrayAccess, FieldAccess, PointerFieldAccess,
    Dereference, AddressOf, UnaryMinus, Not, And, Or, Multiplication, Division,
    Modulus, Addition, Concatenation, Subtraction, LessThan, GreaterThan,
    LessThanOrEqual, GreaterThanOrEqual, Equal, NotEqual, ModulusAssignment,
    DivisionAssignment, MultiplicationAssignment, SubtractionAssignment, AdditionAssignment,
    Assignment, PostfixDecrement, PostfixIncrement, StaticMemberAccess, NotLessThan,
    NotLessThanOrEqual, NotGreaterThan, NotGreaterThanOrEqual, PointerIndexAccess,
    SubtractionSequence, DivisionSequence, SingleIncrement, SingleDecrement,
    FunctionCall, None
};

/*!
 * \brief Структура, содержащая информацию об операторе
 */
struct OperatorInfo {
    OperationArity arity;     /*!< Арность операции */
    OperationType type;       /*!< Тип операции */
};

/*!
 * \brief Набор допустимых типов данных
 */
extern const QSet<QString> DataTypes;

/*!
 * \brief Словарь для сопоставления операции сравнения с обратной
 */
extern const QHash<OperationType, OperationType> InverseComparisonOperationsMap;

/*!
 * \brief Словарь всех поддерживаемых операций и их характеристик
 */
extern const QHash<QString, OperatorInfo> OperationMap;

/*!
 * \brief Словарь текстовых представлений типов сущностей
 */
extern const QHash<EntityType, QString> EntityTypeNames;

/*!
 * \brief Словарь текстовых представлений типов операций
 */
extern const QHash<OperationType, QString> OperationTypeNames;

/*!
 * \brief Структура, представляющая переменную
 */
struct Variable {
    QString name;           /*!< Имя переменной */
    QString type;           /*!< Тип переменной */
    QString description;    /*!< Описание переменной */

    explicit Variable(const QString& name = "", const QString& type = "", const QString& description = {});

    /*!
     * \brief Преобразование переменной в строку
     * \param[in] startLine Префикс для первой строки
     * \return Строковое представление переменной
     */
    QString toQString(const QString& startLine = "") const;
};

/*!
 * \brief Структура, представляющая функцию
 */
struct Function {
    QString name;           /*!< Имя функции */
    QString type;           /*!< Возвращаемый тип */
    int paramsCount;        /*!< Количество параметров */
    QString description;    /*!< Описание функции */

    explicit Function(const QString& name = "", const QString& type = "", int paramsCount = 0, const QString& description = {});

    /*!
     * \brief Преобразование функции в строку
     * \param[in] startLine Префикс для первой строки
     * \return Строковое представление функции
     */
    QString toQString(const QString& startLine = "") const;
};

/*!
 * \brief Пользовательский тип данных с переменными и функциями
 */
struct CustomTypeWithFields {
    QString name;                               /*!< Имя типа */
    QHash<QString, Variable> variables;         /*!< Список переменных */
    QHash<QString, Function> functions;         /*!< Список функций */

    explicit CustomTypeWithFields(const QString& name = "", const QHash<QString, Variable>& variables = {}, const QHash<QString, Function>& functions = {});

    /*!
     * \brief Преобразование пользовательского типа в строку
     * \param[in] startLine Префикс для первой строки
     * \return Строковое представление
     */
    virtual QString toQString(const QString& startLine = "") const;
};

/*!
 * \brief Структура, представляющая объединение (union)
 */
struct Union : public CustomTypeWithFields {
    explicit Union(const QString& name = "", const QHash<QString, Variable>& variables = {}, const QHash<QString, Function>& functions = {});

    QString toQString(const QString& startLine = "") const override;
};

/*!
 * \brief Структура, представляющая структуру (struct)
 */
struct Structure : public CustomTypeWithFields {
    explicit Structure(const QString& name = "", const QHash<QString, Variable>& variables = {}, const QHash<QString, Function>& functions = {});

    QString toQString(const QString& startLine = "") const override;
};

/*!
 * \brief Структура, представляющая класс (class)
 */
struct Class : public CustomTypeWithFields {
    explicit Class(const QString& name = "", const QHash<QString, Variable>& variables = {}, const QHash<QString, Function>& functions = {});

    QString toQString(const QString& startLine = "") const override;
};

/*!
 * \brief Структура, представляющая перечисление (enum)
 */
struct Enum {
    QString name;                               /*!< Имя перечисления */
    QHash<QString, QString> values;             /*!< Значения перечисления */

    explicit Enum(const QString& name = "", const QHash<QString, QString>& values = {});

    /*!
     * \brief Преобразование перечисления в строку
     * \param[in] startLine Префикс для первой строки
     * \return Строковое представление перечисления
     */
    QString toQString(const QString& startLine = "") const;
};

#endif // CODEENTITY_H
