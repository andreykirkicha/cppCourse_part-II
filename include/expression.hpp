struct Expression
{
    virtual double evaluate() const = 0;
    virtual ~Expression() {}
};

struct Number : Expression
{
    Number(double value)
        : value(value)
    {}

    double evaluate() const { return this->value; }

private:
    double value;
};

struct BinaryOperation : Expression
{
    BinaryOperation(Expression const *left, char op, Expression const *right)
        : left(left), op(op), right(right)
    {}

    double evaluate() const
    {
        switch (this->op)
        {
        case '+':
            return (this->left)->evaluate() + (this->right)->evaluate();
            break;

        case '-':
            return (this->left)->evaluate() - (this->right)->evaluate();
            break;

        case '*':
            return (this->left)->evaluate() * (this->right)->evaluate();
            break;

        case '/':
            return (this->left)->evaluate() / (this->right)->evaluate();
            break;
        
        default:
            break;
        }

        return 0;
    }

    ~BinaryOperation()
    {
        delete this->left;
        delete this->right;
    }

private:
    Expression const *left;
    Expression const *right;
    char op;
};