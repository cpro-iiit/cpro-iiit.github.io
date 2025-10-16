#include <stdio.h>

int main() {
  int n = 0, m = 0;
  scanf("%d", &n);

  scanf("%d", &m);
  int array[n*m*n];

  for(int i = 0; i < n*m*n; i++) {
    printf("%d ", array[i]);
  }
  
  return 0;
}