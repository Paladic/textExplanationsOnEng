#include "expressiontranslator.h"
#include "teexception.h"

const QHash<OperationType, QString> ExpressionTranslator::Templates = {
    {OperationType::Addition, "sum of {1} and {2}"},
    {OperationType::Concatenation, "concatenation of {1} and {2}"},
    {OperationType::Subtraction, "difference of {1} and {2}"},
    {OperationType::And, "{1} and {2}"},
    {OperationType::Or, "{1} or {2}"},
    {OperationType::LessThanOrEqual, "{1} is less than or equal to {2}"},
    {OperationType::GreaterThan, "{1} is greater than {2}"},
    {OperationType::NotEqual, "{1} is not equal to {2}"},
    {OperationType::Equal, "{1} is equal to {2}"},
    {OperationType::LessThan, "{1} is less than {2}"},
    {OperationType::GreaterThanOrEqual, "{1} is greater than or equal to {2}"},
    {OperationType::Multiplication, "product of {1} and {2}"},
    {OperationType::Division, "quotient of {1} and {2}"},
    {OperationType::Modulus, "remainder of {1} divided by {2}"},
    {OperationType::Not, "not {1}"},
    {OperationType::UnaryMinus, "negation of {1}"},
    {OperationType::AddressOf, "get the address of the element {1}"},
    {OperationType::Dereference, "accessing the value at {1}"},
    {OperationType::ArrayAccess, "element at index {2} of array {1}"},
    {OperationType::FieldAccess, "{1}'s {2}"},
    {OperationType::PointerFieldAccess, "{1}'s {2}"},
    {OperationType::StaticMemberAccess, "{2}"},
    {OperationType::PrefixIncrement, "increment {1}, then get {2}"},
    {OperationType::PostfixIncrement, "get {2}, then increment {1}"},
    {OperationType::PrefixDecrement, "decrement {1}, then get {2}"},
    {OperationType::PostfixDecrement, "get {2}, then decrement {1}"},
    {OperationType::Assignment, "assign {2} to {1}"},
    {OperationType::AdditionAssignment, "add {2} to {1} and assign the result to {1}"},
    {OperationType::SubtractionAssignment, "subtract {2} from {1} and assign the result to {1}"},
    {OperationType::MultiplicationAssignment, "multiply {1} by {2} and assign the result to {1}"},
    {OperationType::DivisionAssignment, "divide {1} by {2} and assign the result to {1}"},
    {OperationType::ModulusAssignment, "assign the remainder of {1} divided by {2} to {1}"},
    {OperationType::NotLessThan, "{1} is not less than {2}"},
    {OperationType::NotLessThanOrEqual, "{1} is not less than or equal to {2}"},
    {OperationType::NotGreaterThan, "{1} is not greater than {2}"},
    {OperationType::NotGreaterThanOrEqual, "{1} is not greater than or equal to {2}"},
    {OperationType::PointerIndexAccess, "get the element at the index equal to the pointer of {1}"},
    {OperationType::SubtractionSequence, "difference of {1} and the sum of {2}"},
    {OperationType::DivisionSequence, "quotient of {1} and the product of {2}"},
    {OperationType::SingleDecrement, "decrement {1}"},
    {OperationType::SingleIncrement, "increment {1}"},
    };

ExpressionTranslator::ExpressionTranslator()
{

}

QString ExpressionTranslator::getExplanation(const QString& description, const QList<QString>& arguments)
{
    QString pattern = description;

    QRegularExpression numberedPlaceholderRegex(R"(\{\s*(\d+)\s*\})");
    QRegularExpressionMatchIterator it = numberedPlaceholderRegex.globalMatch(pattern);

    // Пока есть вхождения плейсхолдера
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        int index = match.captured(1).toInt() - 1;
        QString caseStr = match.captured(2);
        // Если индекс в плейсхолдере корректный
        if (index >= 0 && index < arguments.size()) {
            QString replacement = arguments[index];
            // Заменить плейсхолдер в результирующей строке на соответствующий аргумент
            pattern.replace(match.captured(0), replacement);
        }
        // Иначе вызвать ошибку
        else throw TEException(ErrorType::MissingReplacementArguments, QList<QString>{pattern});
    }
    return pattern;
}

