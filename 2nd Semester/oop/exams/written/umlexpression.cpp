#include <iostream>
#include <vector>

class Expression
{
public:
  virtual double evaluate() const = 0;
  virtual ~Expression(){};
};

class Constant : public Expression
{
private:
  double value;

public:
  explicit Constant(double val) : value(val) {}

  double evaluate() const override
  {
    return value;
  }
};

class UnaryExpression : public Expression
{
protected:
  Expression *expr;

public:
  explicit UnaryExpression(Expression *exp) : expr(exp) {}

  virtual ~UnaryExpression()
  {
    delete expr;
  }
};

class Negate : public UnaryExpression
{
public:
  explicit Negate(Expression *exp) : UnaryExpression(exp) {}

  double evaluate() const override
  {
    return -expr->evaluate();
  }
};

class BinaryExpression : public Expression
{
protected:
  Expression *expr1;
  Expression *expr2;

public:
  BinaryExpression(Expression *exp1, Expression *exp2) : expr1(exp1), expr2(exp2) {}

  virtual ~BinaryExpression()
  {
    delete expr1;
    delete expr2;
  }
};

class Adder : public BinaryExpression
{
public:
  Adder(Expression *exp1, Expression *exp2) : BinaryExpression(exp1, exp2) {}

  double evaluate() const override
  {
    return expr1->evaluate() + expr2->evaluate();
  }
};

class Subtracter : public BinaryExpression
{
public:
  Subtracter(Expression *exp1, Expression *exp2) : BinaryExpression(exp1, exp2) {}

  double evaluate() const override
  {
    return expr1->evaluate() - expr2->evaluate();
  }
};

class MathHomework
{
private:
  std::vector<Expression *> expressions;

public:
  ~MathHomework()
  {
    for (auto expression : expressions)
      delete expression;
  }

  void addExpression(Expression *exp)
  {
    expressions.push_back(exp);
  }

  std::vector<double> getResults() const
  {
    std::vector<double> results;
    for (auto expression : expressions)
      results.push_back(expression->evaluate());
    return results;
  }
};

MathHomework createHomework()
{
  MathHomework homework;

  // Create the first expression: -5 + (9 - 3)
  Expression *exp1 = new Adder(new Constant(-5), new Subtracter(new Constant(9), new Constant(3)));
  homework.addExpression(exp1);

  // Create the second expression: -(4 + 2) - (-10)
  Expression *exp2 = new Subtracter(new Negate(new Adder(new Constant(4), new Constant(2))), new Negate(new Constant(-10)));
  homework.addExpression(exp2);

  return homework;
}

int main()
{
  MathHomework homework = createHomework();
  std::vector<double> results = homework.getResults();

  std::cout << "Results:" << std::endl;
  for (double result : results)
    std::cout << result << std::endl;

  return 0;
}
