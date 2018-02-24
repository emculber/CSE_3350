#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "imp.h"

using namespace std;

// the constructor for node links the node to its children,
// and stores the character representation of the operator.
binaryOp_node::binaryOp_node(exp_node *L, exp_node *R) {
  left    = L;
  right   = R;
}

number_node::number_node(float value) {
  num = value;
}

void number_node:: print() {
  cout << num;
}

float number_node::evaluate() { 
  return num; 
}

  variable_node::variable_node(string value) : id(value) {}

  void variable_node:: print() {
    cout << id;
  }

float variable_node::evaluate() { 
  return state[id]; 
}

// add_node inherits the characteristics of node and adds its own evaluate function
// add_node's constructor just uses node's constructor
add_node::add_node(exp_node *L, exp_node *R) : binaryOp_node(L,R) {
}

void add_node:: print() {
  cout << "(";
  left->print();
  cout << " + ";
  right->print();
  cout << ")";
}

float add_node::evaluate() {
  float left_num, right_num;

  left_num  = left->evaluate();
  right_num = right->evaluate();

  return left_num + right_num;

}


// subtract_node inherits the characteristics of node and adds its own evaluate function
subtract_node::subtract_node(exp_node *L, exp_node *R) : binaryOp_node(L,R) {
}

void subtract_node:: print() {
  cout << "(";
  left->print();
  cout << " - ";
  right->print();
  cout << ")";
}

float subtract_node::evaluate() {
  float left_num, right_num;

  left_num  = left->evaluate();
  right_num = right->evaluate();

  return  left_num - right_num;

}


// multiply_node inherits the characteristics of node and adds its own evaluate function
multiply_node::multiply_node(exp_node *L, exp_node *R) : binaryOp_node(L,R) {
}

void multiply_node:: print() {
  cout << "(";
  left->print();
  cout << " * ";
  right->print();
  cout << ")";
}

float multiply_node::evaluate() {
  float left_num, right_num;

  left_num = left->evaluate();
  right_num = right->evaluate();

  return left_num * right_num;

}


// divide_node inherits the characteristics of node and adds its own evaluate function

divide_node::divide_node(exp_node *L, exp_node *R) : binaryOp_node(L,R) {
}

void divide_node:: print() {
  cout << "(";
  left->print();
  cout << " / ";
  right->print();
  cout << ")";
}

float divide_node::evaluate() {
  float left_num, right_num;

  left_num = left->evaluate();
  right_num = right->evaluate();

  if(right_num)
  {
    return  left_num / right_num;
  }
  else
  {
    cout << "division by zero -> " << left_num << " / " << 0 << endl;
    //  include stdlib.h for exit
    exit(1);
  }
}

neg_node::neg_node(exp_node *L) : exp(L) {}

void neg_node:: print() {
  cout << "- ( ";
  exp->print();
  cout << " )";
}

float neg_node::evaluate() {
  float expValue = exp->evaluate();
  return  -expValue;
}

// MODIFY(ADD): functions that handle everything for the boolean or operations
or_node::or_node(exp_node *L, exp_node *R) : binaryOp_node(L,R) {
}

void or_node:: print() {
  cout << "(";
  left->print();
  cout << " || ";
  right->print();
  cout << ")";
}

float or_node::evaluate() {
  float left_num, right_num;

  left_num = left->evaluate();
  right_num = right->evaluate();

  return left_num || right_num;
}

// MODIFY(ADD): functions that handle everything for the boolean and operations
and_node::and_node(exp_node *L, exp_node *R) : binaryOp_node(L,R) {
}

void and_node:: print() {
  cout << "(";
  left->print();
  cout << " && ";
  right->print();
  cout << ")";
}

float and_node::evaluate() {
  float left_num, right_num;

  left_num = left->evaluate();
  right_num = right->evaluate();

  return left_num && right_num;
}

// MODIFY(ADD): functions that handle everything for the boolean not operations
not_node::not_node(exp_node *R) : exp(R) {}

void not_node:: print() {
  cout << "!(";
  exp->print();
  cout << ")";
}

float not_node::evaluate() {
  float expValue = exp->evaluate();
  return  !expValue;
}

// MODIFY(ADD): functions that handle everything for the boolean equal to operations
bool_equal_node::bool_equal_node(exp_node *L, exp_node *R) : binaryOp_node(L,R) {
}

void bool_equal_node:: print() {
  cout << "(";
  left->print();
  cout << " == ";
  right->print();
  cout << ")";
}

float bool_equal_node::evaluate() {
  float left_num, right_num;

  left_num = left->evaluate();
  right_num = right->evaluate();

  return left_num == right_num;
}

// MODIFY(ADD): functions that handle everything for the boolean greater then equal to operations
bool_greater_equal_node::bool_greater_equal_node(exp_node *L, exp_node *R) : 
  binaryOp_node(L,R) {
  }

void bool_greater_equal_node:: print() {
  cout << "(";
  left->print();
  cout << " >= ";
  right->print();
  cout << ")";
}

float bool_greater_equal_node::evaluate() {
  float left_num, right_num;

  left_num = left->evaluate();
  right_num = right->evaluate();

  return left_num >= right_num;
}

// MODIFY(ADD): functions that handle everything for the boolean less then equal to operations
bool_less_equal_node::bool_less_equal_node(exp_node *L, exp_node *R) : 
  binaryOp_node(L,R) {}

void bool_less_equal_node:: print() {
  cout << "(";
  left->print();
  cout << " <= ";
  right->print();
  cout << ")";
}

float bool_less_equal_node::evaluate() {
  float left_num, right_num;

  left_num = left->evaluate();
  right_num = right->evaluate();

  return left_num <= right_num;
}

// MODIFY(ADD): functions that handle everything for the boolean greater then operations
bool_greater_node::bool_greater_node(exp_node *L, exp_node *R) : 
  binaryOp_node(L,R) {
  }

void bool_greater_node:: print() {
  cout << "(";
  left->print();
  cout << " > ";
  right->print();
  cout << ")";
}

float bool_greater_node::evaluate() {
  float left_num, right_num;

  left_num = left->evaluate();
  right_num = right->evaluate();

  return left_num > right_num;
}

// MODIFY(ADD): functions that handle everything for the boolean less then operations
bool_less_node::bool_less_node(exp_node *L, exp_node *R) : 
  binaryOp_node(L,R) {
  }

void bool_less_node:: print() {
  cout << "(";
  left->print();
  cout << " < ";
  right->print();
  cout << ")";
}

float bool_less_node::evaluate() {
  float left_num, right_num;

  left_num = left->evaluate();
  right_num = right->evaluate();

  return left_num < right_num;
}

// MODIFY(ADD): functions that handle everything for the boolean not equal operations
bool_not_equal_node::bool_not_equal_node(exp_node *L, exp_node *R) : 
  binaryOp_node(L,R) {
  }

void bool_not_equal_node:: print() {
  cout << "(";
  left->print();
  cout << " != ";
  right->print();
  cout << ")";
}

float bool_not_equal_node::evaluate() {
  float left_num, right_num;

  left_num = left->evaluate();
  right_num = right->evaluate();

  return left_num != right_num;
}

assign_node::assign_node(string name, exp_node *expression)
  : id(name), exp(expression) {}

  void assign_node::print() {
    cout << id << " = ";
    exp->print();

  }

void assign_node::evaluate() {
  float result = exp->evaluate();

  state[id] = result;
}

print_node::print_node (exp_node *myexp) : exp(myexp) {}

void print_node::print() {
  cout <<  "print ";
  exp->print();
}


void print_node::evaluate() {
  cout << "output: " << exp->evaluate() << endl << endl;
}

// MODIFY(ADD): functions that handle everything for the read statment
read_node::read_node(string name) : 
  id(name) {}

  void read_node::print() {
    cout << "read " << id;
    //exp->print();
  }

void read_node::evaluate() {
  float result;
  cout << "read: ";
  cin >> result;

  state[id] = result;
}

// MODIFY(ADD): functions that handle everything for the if-else statment
if_else_node::if_else_node(exp_node* mycompopt1, stmt_node* mystmt1, stmt_node* mystmt2) : 
  compopt1(mycompopt1), stmt1(mystmt1), stmt2(mystmt2) {}

  void if_else_node::print() {
    cout << "if ("; 
    compopt1->print();
    cout << ") { ";
    stmt1->print();
    cout << " } else { "; 
    stmt2->print();
    cout << " }";
  }

void if_else_node::evaluate() {
  if(compopt1->evaluate()) {
    stmt1->evaluate();
  }else{
    stmt2->evaluate();
  }
}

// MODIFY(ADD): functions that handle everything for the while loop
while_node::while_node(exp_node* mycompopt1, stmt_node* mystmt1) : 
  compopt1(mycompopt1), stmt1(mystmt1) {}

  void while_node::print() {
    cout << "while ("; 
    compopt1->print();
    cout << ") { ";
    stmt1->print();
    cout << " }"; 
  }

void while_node::evaluate() {
  while(compopt1->evaluate()) {
    stmt1->evaluate();
  }
}

skip_node::skip_node ()  {}

void skip_node::evaluate() {}
void skip_node::print() {}

sequence_node::sequence_node(stmt_node* mystmt1, stmt_node* mystmt2): stmt1(mystmt1), stmt2(mystmt2) {}

void sequence_node::print() {
  stmt1->print();  cout << " ;" << endl;
  stmt2->print();
}


void sequence_node::evaluate() {
  stmt1->evaluate();
  stmt2->evaluate();
}

map<string, float> state;

