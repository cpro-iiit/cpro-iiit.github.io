#include <stdio.h>
int main() {
  float x = 0.3f;
  float y = 0.2f;
  float z = 1.5f;
  printf("%d\n", sizeof(x));
  if (3*(x + y) == z) {
    printf("Equal\n");
  } else {
    printf("Not Equal\n");
  }
}