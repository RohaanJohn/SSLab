/*
Name: Rohaan Renu John
Class: S5-CS1
Title: Indexed File Allocation
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
    printf("Enter the indexed block of file %s:\n", files[i].name);
    scanf("%d", &files[i].start);
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
  printf("File\tStart\tLength\tIndexed block");
  for (int i = 0; i < m; i++) {
    printf("\n%s\t%d\t%d\t[ ", files[i].name, files[i].start, files[i].length);
    for (int j = 0; j < files[i].length; j++) {
      printf("%d ", files[i].link[j]);
    }
    printf(" ]");
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
Enter the indexed block of file ww:
12
Enter the total length of file ww:
13
Enter the file 2:
qq
Enter the indexed block of file qq:
32
Enter the total length of file qq:
5
Enter the file 3:
rrr
Enter the indexed block of file rrr:
21
Enter the total length of file rrr:
6

File	Start	Length	Indexed block
ww	  12	    13	    [ 7 6 9 19 17 31 10 13 26 11 18 27 3  ]
qq	  32	    5       [ 28 2 20 24 8  ]
rrr	  21		  6       [ 22 14 23 5 29 30  ]
Printing the status of the disk blocks:
The status of block 0: 0
The status of block 1: 0
The status of block 2: 1
The status of block 3: 1
The status of block 4: 0
The status of block 5: 1
The status of block 6: 1
The status of block 7: 1
The status of block 8: 1
The status of block 9: 1
The status of block 10: 1
The status of block 11: 1
The status of block 12: 1
The status of block 13: 1
The status of block 14: 1
The status of block 15: 0
The status of block 16: 0
The status of block 17: 1
The status of block 18: 1
The status of block 19: 1
The status of block 20: 1
The status of block 21: 1
The status of block 22: 1
The status of block 23: 1
The status of block 24: 1
The status of block 25: 0
The status of block 26: 1
The status of block 27: 1
The status of block 28: 1
The status of block 29: 1
The status of block 30: 1
The status of block 31: 1

*/
