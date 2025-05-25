#ifndef TEST_GETEXPLANATIONINEN_H
#define TEST_GETEXPLANATIONINEN_H

#include <QObject>

class test_getExplanationInEn : public QObject
{
    Q_OBJECT
public:
    explicit test_getExplanationInEn(QObject *parent = nullptr);

private slots: // должны быть приватными
    void getExplanationInEn();
    void getExplanationInEn_data(); // removeDuplicates...

};

#endif // TEST_GETEXPLANATIONINEN_H
