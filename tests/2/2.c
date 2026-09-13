#include <stdio.h>

int foo(int n) {
  int x = 5;
  int result = 0;

  /*
    loading x and x+10 are invariant
    loading n (loop condition check) is invariant
  */
  for (int k = 0; k < n; k++) {
    result += k * k - (x * 10);
  }
  return result;
}

int main() {
  int s;
  int p = 10;
  // s = p & 1 is invariant
  for (int i = 10; i >= 0; i--) {
    s = p & 1;
    printf("%d %d\n", s, foo(i));
  }
}
