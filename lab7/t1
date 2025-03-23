#include <iostream>
#include <cassert>
#include <string>
#include <cmath>
using namespace std;

struct expression
{
    virtual ~expression() = default;
    virtual double evaluate() const = 0;
};

struct number : expression
{
    number(double value) : value_(value) {}
    double value() const { return value_; }
    double evaluate() const override { return value_; }
private:
    double value_;
};

struct binaryOperation : expression
{
    enum Operation
    {
        plus = '+',
        minus = '-',
        div = '/',
        mul = '*'
    };

    binaryOperation(expression const* left, int op, expression const* right)
        : left_(left), op_(op), right_(right)
    {
        assert(left_ && right_);
    }

    ~binaryOperation()
    {
        delete left_;
        delete right_;
    }

    expression const* left() const { return left_; }
    expression const* right() const { return right_; }
    int operation() const { return op_; }

    double evaluate() const override
    {
        double left = left_->evaluate();
        double right = right_->evaluate();
        switch (op_)
        {
        case plus: return left + right;
        case minus: return left - right;
        case div: return left / right;
        case mul: return left * right;
        }
        assert(0);
        return 0.0;
    }

private:
    expression const* left_;
    expression const* right_;
    int op_;
};

struct FunctionCallL : expression
{

};

int main()
{
    expression* e1 = new number(1.234);
    expression* e2 = new number(-1.234);
    expression* e3 = new binaryOperation(e1, binaryOperation::div, e2);
    cout << e3->evaluate() << endl;

}
