#ifndef test_removeConsecutiveDuplicates_H
#define test_removeConsecutiveDuplicates_H

#include <QObject>

class test_removeConsecutiveDuplicates : public QObject
{
    Q_OBJECT
public:
    explicit test_removeConsecutiveDuplicates(QObject *parent = nullptr);

private slots: // должны быть приватными
    void removeConsecutiveDuplicates(); // removeConsecutiveDuplicates...
    void removeConsecutiveDuplicates_data();

};

#endif // test_removeConsecutiveDuplicates_H
