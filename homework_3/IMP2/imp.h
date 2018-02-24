#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

using namespace std;

class exp_node {
  public:

    // print function for pretty printing an expression
    virtual void print() = 0;

    // evaluation function for a leaf, replaced for interior nodes
    virtual float evaluate() = 0;
};

class binaryOp_node : public exp_node {
public:
    exp_node *left;
    exp_node *right;

  // the constructor for node links the node to its children,
  // and stores the character representation of the operator.
    binaryOp_node(exp_node *L, exp_node *R);
};

class number_node : public exp_node {
 private:
    float num;

 public:
  number_node(float value);
  void print();
  float evaluate();
};

class neg_node : public exp_node {
 protected:
  exp_node *exp;
 public:
  neg_node(exp_node *exp);
  void print();
  float evaluate();
};

class variable_node : public exp_node {
protected:
  string id;

public:
  variable_node(string value);
  void print();
  float evaluate();
};

// add_node inherits the characteristics of node and adds its own evaluate function
class add_node : public binaryOp_node {
  public:

  // add_node's constructor just uses node's constructor
  add_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};


// subtract_node inherits the characteristics of node and adds its own evaluate function
class subtract_node : public binaryOp_node {
  public:

  subtract_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};


// multiply_node inherits the characteristics of node and adds its own evaluate function
class multiply_node : public binaryOp_node {
  public:

  multiply_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};


// divide_node inherits the characteristics of node and adds its own evaluate function
class divide_node : public binaryOp_node {
  public:

  divide_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

// MODIFY(ADD): or_node inherits from binaryOp_node and is used to boolean or operations
class or_node : public binaryOp_node {
  public:
    or_node(exp_node *L, exp_node *R);
    void print();
    float evaluate();
};

// MODIFY(ADD): and_node inherits from binaryOp_node and is used to boolean or operations
class and_node : public binaryOp_node {
  public:
    and_node(exp_node *L, exp_node *R);
    void print();
    float evaluate();
};

// MODIFY(ADD): not_node inherits from exp_node and is used to boolean or operations
class not_node : public exp_node {
  protected:
    exp_node *exp;
  public:
    not_node(exp_node *R);
    void print();
    float evaluate();
};

// MODIFY(ADD): bool_equal_node inherits from binaryOp_node and is used to boolean or operations
class bool_equal_node : public binaryOp_node {
  public:
    bool_equal_node(exp_node *L, exp_node *R);
    void print();
    float evaluate();
};

// MODIFY(ADD): bool_greater_equal_node inherits from binaryOp_node and is used to boolean or operations
class bool_greater_equal_node : public binaryOp_node {
  public:
    bool_greater_equal_node(exp_node *L, exp_node *R);
    void print();
    float evaluate();
};

// MODIFY(ADD): bool_less_equal_node inherits from binaryOp_node and is used to boolean or operations
class bool_less_equal_node : public binaryOp_node {
  public:
    bool_less_equal_node(exp_node *L, exp_node *R);
    void print();
    float evaluate();
};

// MODIFY(ADD): bool_greater_node inherits from binaryOp_node and is used to boolean or operations
class bool_greater_node : public binaryOp_node {
  public:
    bool_greater_node(exp_node *L, exp_node *R);
    void print();
    float evaluate();
};

// MODIFY(ADD): bool_less_node inherits from binaryOp_node and is used to boolean or operations
class bool_less_node : public binaryOp_node {
  public:
    bool_less_node(exp_node *L, exp_node *R);
    void print();
    float evaluate();
};

// MODIFY(ADD): bool_not_equal_node inherits from binaryOp_node and is used to boolean or operations
class bool_not_equal_node : public binaryOp_node {
  public:
    bool_not_equal_node(exp_node *L, exp_node *R);
    void print();
    float evaluate();
};

class stmt_node {
 public:
  virtual void print() {}
  virtual void evaluate() = 0;
};

class assign_node : public stmt_node {
 protected:
  string id;
  exp_node *exp;
 public:
  assign_node(string name, exp_node *expression);
  void print();
  void evaluate();
};

class print_node: public stmt_node {
 protected:
  exp_node *exp;
 public:
  print_node(exp_node *myexp);
  void print();
  void evaluate();
};

// MODIFY(ADD): read_node inherits from stmt_node and is used in the read statments
class read_node: public stmt_node {
 protected:
  string id;
 public:
  read_node(string name);
  void print();
  void evaluate();
};

// MODIFY(ADD): if_else_node inherits from stmt_node and is used to if statments
class if_else_node: public stmt_node {
 protected:
   exp_node *compopt1;
   stmt_node *stmt1, *stmt2;
 public:
  if_else_node(exp_node *mycompopt1, stmt_node *mystmt1, stmt_node *mystmt2);
  void print();
  void evaluate();
};

// MODIFY(ADD): while_node inherits from stmt_node and is used for while statments
class while_node: public stmt_node {
 protected:
   exp_node *compopt1;
   stmt_node *stmt1;
 public:
  while_node(exp_node *mycompopt1, stmt_node *mystmt1);
  void print();
  void evaluate();
};

class skip_node: public stmt_node {
 public:
  skip_node();
  void print();
  void evaluate();
};


class sequence_node: public stmt_node {
 protected:
  stmt_node *stmt1, *stmt2;
 public:
  sequence_node(stmt_node *mystmt1, stmt_node *mystmt2);
  void print();
  void evaluate();
};

// the object at the base of our tree
extern map<string, float> state;

