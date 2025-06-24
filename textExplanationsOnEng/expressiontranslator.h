/*!
 * \file
 * \brief Заголовочный файл, содержащий определения класса ExpressionTranslator для перевода выражений в текстовую форму
 */

#ifndef EXPRESSIONTRANSLATOR_H
#define EXPRESSIONTRANSLATOR_H

#include "codeentity.h"
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QHash>

/*!
 * \brief Класс для преобразования операций и выражений в человекочитаемую текстовую форму
 */
class ExpressionTranslator
{
public:
    /*!
     * \brief Конструктор класса ExpressionTranslator
     *
     * Конструктор не выполняет инициализацию, так как все методы и поля статические.
     */
    explicit ExpressionTranslator();

    /*!
     * \brief Шаблоны строк, соответствующие различным типам операций
     *
     * Хранит отображение типа операции в строку-шаблон для объяснения.
     */
    static const QHash<OperationType, QString> Templates;

    /*!
     * \brief Генерация пояснительного текста по описанию и аргументам
     * \param[in] description Описание шаблона операции (например: "%1 меньше %2")
     * \param[in] arguments Список аргументов, подставляемых в шаблон
     * \return Строка с подставленными значениями (например: "a меньше b")
     * \throw TEException исключение при обработке
     */
    static QString getExplanation(const QString &description, const QList<QString> &arguments);
};

#endif // EXPRESSIONTRANSLATOR_H
