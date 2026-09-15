#include <stdio.h>

int main() {
  int x, y, z, n = 1000;
  scanf("%d%d%d", &x, &y, &z);
  int s, t;

  for (int i = 0; i < n; i++) {
    x++;
    y = x * z;
    z = n - 42;
    for (int j = -1; j < n; j++) {
      x = 5;
      s = 7 * j;
      t = n & 1;
    }
  }

  return 0;
}
