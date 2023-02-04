/*
Name: Rohaan Renu John
Class: S5-CS1
Title: Loader
*/
#include <stdio.h>

#define MAX 100
// input file is object.txt and output is output.txt
int main() {
  char str[MAX];
  FILE *f1, *f2;
  f1 = fopen("object.txt", "r");
  f2 = fopen("output.txt", "w");
  int location = 0;
  // Program loaded into the memory with following addresses stored in output.txt
  while (fgets(str, MAX, f1) != NULL) {
    if (str[0] == 'H') {
      sscanf(str + 9, "%x", &location);
      continue;
    }
    if (str[0] == 'E')
      break;

    int startingAddress;

    sscanf(str, "T%x", &startingAddress);

    while (location < startingAddress) {
      fprintf(f2, "%x xx\n",
              location++); // after printing the location get incremented
    }

    char *ptr = str + 12;
    for (int i = 0; ptr[i] != '\0' && ptr[i] != '\n'; i += 2) {

      if (ptr[i] == ' ')
        i++;
      fprintf(f2, "%x %c%c\n", location++, ptr[i], ptr[i + 1]);
    }
  }
  return 0;
}
