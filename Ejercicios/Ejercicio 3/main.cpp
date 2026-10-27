#include <iostream>
#include <memory>
#include <string>
#include <cmath>

using namespace std;

class Expression {
public:
    virtual ~Expression() = default;
    virtual double eva(double x) const = 0;
    virtual shared_ptr<Expression> derivative() const = 0;
    virtual string toString() const = 0;
};

class Constant : public Expression {
    double value;
public:
    explicit Constant(double val) : value(val) {}
    double eva(double) const override { return value; }
    shared_ptr<Expression> derivative() const override {
        return make_shared<Constant>(0);
    }
    string toString() const override { return to_string((int)value); }
};

class Variable : public Expression {
public:
    double eva(double x) const override { return x; }
    shared_ptr<Expression> derivative() const override {
        return make_shared<Constant>(1);
    }
    string toString() const override { return "x"; }
};

// operaciones binarias
class Add : public Expression {
    shared_ptr<Expression> left, right;
public:
    Add(shared_ptr<Expression> l, shared_ptr<Expression> r)
        : left(move(l)), right(move(r)) {}

    double eva(double x) const override {
        return left->eva(x) + right->eva(x);
    }
    shared_ptr<Expression> derivative() const override {
        return make_shared<Add>(left->derivative(), right->derivative());
    }
    string toString() const override {
        return "(" + left->toString() + " + " + right->toString() + ")";
    }
};

class Multiply : public Expression {
    shared_ptr<Expression> left, right;
public:
    Multiply(shared_ptr<Expression> l, shared_ptr<Expression> r)
        : left(move(l)), right(move(r)) {}

    double eva(double x) const override {
        return left->eva(x) * right->eva(x);
    }
    shared_ptr<Expression> derivative() const override {
        auto term1 = make_shared<Multiply>(left->derivative(), right);
        auto term2 = make_shared<Multiply>(left, right->derivative());
        return make_shared<Add>(term1, term2);
    }
    string toString() const override {
        return "(" + left->toString() + " * " + right->toString() + ")";
    }
};

class Power : public Expression {
    shared_ptr<Expression> base;
    int exponent;
public:
    Power(shared_ptr<Expression> b, int exp)
        : base(move(b)), exponent(exp) {}

    double eva(double x) const override {
        return pow(base->eva(x), exponent);
    }
    shared_ptr<Expression> derivative() const override {
        auto coeff = make_shared<Constant>(exponent);
        auto newPow = make_shared<Power>(base, exponent - 1);
        auto chain = make_shared<Multiply>(coeff, newPow);
        return make_shared<Multiply>(chain, base->derivative());
    }
    string toString() const override {
        return "(" + base->toString() + "^" + to_string(exponent) + ")";
    }
};

class Sin : public Expression {
    shared_ptr<Expression> arg;
public:
    explicit Sin(shared_ptr<Expression> a) : arg(move(a)) {}

    double eva(double x) const override {
        return sin(arg->eva(x));
    }
    shared_ptr<Expression> derivative() const override;
    string toString() const override {
        return "sin(" + arg->toString() + ")";
    }
};

class Cos : public Expression {
    shared_ptr<Expression> arg;
public:
    explicit Cos(shared_ptr<Expression> a) : arg(move(a)) {}

    double eva(double x) const override {
        return cos(arg->eva(x));
    }
    shared_ptr<Expression> derivative() const override {
        auto negOne = make_shared<Constant>(-1);
        auto sinPart = make_shared<Sin>(arg);
        auto negSin = make_shared<Multiply>(negOne, sinPart);
        return make_shared<Multiply>(negSin, arg->derivative());
    }
    string toString() const override {
        return "cos(" + arg->toString() + ")";
    }
};

inline shared_ptr<Expression> Sin::derivative() const {
    return make_shared<Multiply>(make_shared<Cos>(arg), arg->derivative());
}