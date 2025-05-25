#ifndef TEST_REMOVEDUPLICATES_H
#define TEST_REMOVEDUPLICATES_H

#include <QObject>

class test_removeDuplicates : public QObject
{
    Q_OBJECT
public:
    explicit test_removeDuplicates(QObject *parent = nullptr);

private slots: // должны быть приватными
    void removeDuplicates(); // removeDuplicates...
    void removeDuplicates_data();

};

#endif // TEST_REMOVEDUPLICATES_H
