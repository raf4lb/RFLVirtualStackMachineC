#include "ALU.h"

int add(int a, int b) { return a + b; }

int subtract(int a, int b) { return a - b; }

int multiply(int a, int b) { return a * b; }

int divide(int a, int b) { return a / b; }

int logic_and(int a, int b) { return a && b; }

ALU create_alu() {
  ALU alu;
  alu.add = add;
  alu.subtract = subtract;
  alu.multiply = multiply;
  alu.divide = divide;
  alu.logic_and = logic_and;
  return alu;
}