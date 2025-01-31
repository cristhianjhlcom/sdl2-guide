#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void segmentation_error(void) {
  int *pointer = malloc(sizeof(int));
  if (pointer == NULL) {
    printf("Memory allocation failed.\n");
    exit(1);
  }

  *pointer = 50;
}

int main(void) {
  int idx = 0;

  while (idx < 5) {
    printf("idx %d\n", idx);
  }

  return EXIT_SUCCESS;
}
