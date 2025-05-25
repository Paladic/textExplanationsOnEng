#ifndef TEST_EXPRESSIONTONODES_H
#define TEST_EXPRESSIONTONODES_H

#include <QObject>

class test_expressionToNodes : public QObject
{
    Q_OBJECT
public:
    explicit test_expressionToNodes(QObject *parent = nullptr);

private slots: // должны быть приватными
    void expressionToNodes(); // expressionToNodes...
    void expressionToNodes_data(); // expressionToNodes...
};

#endif // TEST_EXPRESSIONTONODES_H
