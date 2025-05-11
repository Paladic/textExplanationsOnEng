#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H

class ExpressionNode
{
public:
    ExpressionNode();
    bool operator ==(const ExpressionNode& other) const;
    bool operator !=(const ExpressionNode &other) const;
    bool compareFunctionArgs(const QList<ExpressionNode *> &args1, const QList<ExpressionNode *> &args2) const;
private:
    QString value; // содержание ноды
    ExpressionNode* right;
    ExpressionNode* left;
    EntityType nodeType;

    OperationType operType;
    QString dataType; // тип данных
    QList<ExpressionNode*>* FunctionArgs; // аргументы функции

};

#endif // EXPRESSIONNODE_H
