#include <stdio.h>

typedef struct {
  int (*add)(int a, int b);
  int (*subtract)(int a, int b);
  int (*multiply)(int a, int b);
  int (*divide)(int a, int b);
  int (*logic_and)(int a, int b);
} ALU;

int add(int a, int b) { return a + b; }

int subtract(int a, int b) { return a - b; }

int multiply(int a, int b) { return a * b; }

int divide(int a, int b) { return a / b; }

int logic_and(int a, int b) { return a && b; }
