#include <stdio.h>

#define N 80

int main()
{
  FILE *file;
  char arr[N];

  file = fopen("board.txt", "r");
  while(fgets(arr, N, file) != NULL)
    printf("%s", arr);
  printf("\n");
  fclose(file);
}
