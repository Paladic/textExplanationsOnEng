#ifndef TEST_ISFUNCTIONH_H
#define TEST_ISFUNCTIONH_H

#include <QObject>

class test_isFunction : public QObject
{
    Q_OBJECT
public:
    explicit test_isFunction(QObject *parent = nullptr);

private slots: // должны быть приватными
    void isFunction(); // bool isFunction(const QString& str)
    void isFunction_data();
};

#endif // TEST_ISFUNCTIONH_H
