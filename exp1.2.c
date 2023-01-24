/*
Name: Rohaan Renu John
Class: S5-CS1
Title: Linked File Allocation
*/
#include <stdio.h>
#include <stdlib.h>
int main() {
  int n, m;
  printf("Enter the number of disk blocks:\n");
  scanf("%d", &n);
  int status[n];
  for (int i = 0; i < n; i++) {
    status[i] = 0;
  }
  printf("Enter the number of files:\n");
  scanf("%d", &m);

  struct file {
    char name[10];
    int start;
    int length;
    int link[20];
  };
  struct file files[m];

  for (int i = 0; i < m; i++) {
    printf("Enter the file %d:\n", i + 1);
    scanf("%s", &files[i].name);
    // printf("Computed the starting length of file %s.\n", files[i].name);
    // scanf("%d",&files[i].start);
    files[i].start = rand() % n;
    status[files[i].start] = 1;
    printf("Enter the total length of file %s:\n", files[i].name);
    scanf("%d", &files[i].length);
    for (int j = 0; j < files[i].length; j++) {
      int r = rand() % n;
      while (status[r] != 0)
        r = rand() % n;
      status[r] = 1;
      files[i].link[j] = r;
    }
  }
  printf("\n");
  printf("File\tStart\tLength\tLink");
  for (int i = 0; i < m; i++) {
    printf("\n%s\t%d\t%d\t", files[i].name, files[i].start, files[i].length);
    for (int j = 0; j < files[i].length; j++) {
      printf("%d ", files[i].link[j]);
    }
  }
  printf("\n");
  printf("Printing the status of the disk blocks:\n");
  for (int i = 0; i < n; i++) {
    printf("The status of block %d: %d\n", i, status[i]);
  }
}

/*
Output:
Enter the number of disk blocks:
32
Enter the number of files:
3
Enter the file 1:
ww
Enter the total length of file ww:
4
Enter the file 2:
qq
Enter the total length of file qq:
6
Enter the file 3:
qe
Enter the total length of file qe:
7

File	Start	Length	Link
ww	  7	    4       6 9 19 17
qq	  31	  6	      10 12 13 26 11 18
qe	  27	  7	      3 28 2 20 24 8 22
Printing the status of the disk blocks:
The status of block 0: 0
The status of block 1: 0
The status of block 2: 1
The status of block 3: 1
The status of block 4: 0
The status of block 5: 0
The status of block 6: 1
The status of block 7: 1
The status of block 8: 1
The status of block 9: 1
The status of block 10: 1
The status of block 11: 1
The status of block 12: 1
The status of block 13: 1
The status of block 14: 0
The status of block 15: 0
The status of block 16: 0
The status of block 17: 1
The status of block 18: 1
The status of block 19: 1
The status of block 20: 1
The status of block 21: 0
The status of block 22: 1
The status of block 23: 0
The status of block 24: 1
The status of block 25: 0
The status of block 26: 1
The status of block 27: 1
The status of block 28: 1
The status of block 29: 0
The status of block 30: 0
The status of block 31: 1

*/
