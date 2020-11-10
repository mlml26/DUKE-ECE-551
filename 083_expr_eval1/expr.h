#include <sstream>
#include <string>
#include <cstdlib>
class Expression{
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression(){}
};

class NumExpression: public Expression{
  long number;
 public:
 NumExpression(long n): number(n){}
  virtual std::string toString() const{
    std::stringstream sstream;
    sstream << number;
    return sstream.str();
  }
  virtual ~NumExpression(){}
};

class OpExpression: public Expression{
  char op;
  Expression * lhs;
  Expression * rhs;

 public:
 OpExpression(char op, Expression * lhs, Expression * rhs):
  op(op),
    lhs(lhs),
      rhs(rhs){}
  virtual std::string toString() const{
    std::stringstream sstream;
    sstream << '(' << lhs->toString() << ' ' << op << ' ' << rhs->toString() << ')';
    return sstream.str();
  }
  virtual ~OpExpression(){
    delete lhs;
    delete rhs;
  }    
};

class PlusExpression: public OpExpression{
 public:
 PlusExpression(Expression * lhs, Expression * rhs) : OpExpression('+', lhs, rhs){}
};
