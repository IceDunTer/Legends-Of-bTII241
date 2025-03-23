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

struct FunctionCall : expression
{
    FunctionCall(std::string name, expression const* arg)
        : name_(name), arg_(arg)
    {
        assert(arg_);
    }
    ~FunctionCall() 
    {
        delete arg_;
    }
    expression const* arg() const { return arg_; }
    std::string const& name() const { return name_; }
    double evaluate() const override
    {
        double arg = arg_->evaluate();
        if (name_ == "abs") return abs(arg);
        if (name_ == "sqrt") return sqrt(arg);
        assert(0);
        return 0.0;
    }
private:
    expression const* arg_;
    std::string name_;
};

int main()
{
    expression* n32 = new number(32.0);
    expression* n16 = new number(16.0);
    expression* minus = new binaryOperation(n32, binaryOperation::minus, n16);
    expression* callsqrt = new FunctionCall("sqrt", minus);
    expression* n2 = new number(2.0);
    expression* mult = new binaryOperation(n2, binaryOperation::mul, callsqrt);
    expression* callabs = new FunctionCall("abs", mult);
    cout << callabs->evaluate() << endl;

}
