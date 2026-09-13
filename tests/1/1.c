#include <stdio.h>

int main() {
  int n, x = 10;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) { // load n here is invariant
    x = n + 42;                 // load and n+42 are invariant
  }

  printf("%d\n", x);

  return 0;
}
