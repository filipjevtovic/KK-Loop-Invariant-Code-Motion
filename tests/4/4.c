#include <stdio.h>

int main() {
  int n, x = 42;
  scanf("%d", &n);
  int result = 0;

  for (int i = 0; i < n - 1; i++) {
    /* even tho x is invariant here, it cant be hoisted out of
        this loop because its changed in inner loop */
    result = x * 2;
    for (int j = i + 1; j < n; j++) {
      x++;
    }
  }

  printf("%d\n", result);
  return 0;
}
