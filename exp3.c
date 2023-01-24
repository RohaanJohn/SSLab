/*
Name: Rohaan Renu John
Class: S5-CS1
Title: Pass 1 of 2 pass assembler
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// input files: input.txt & optab.txt
// output files: intermediate.txt & symtab.txt
int main() {
  FILE *fp1, *fp2, *fp3, *fp4, *fp5;

  fp1 = fopen("input.txt", "r");
  fp2 = fopen("intermediate.txt", "w");
  fp3 = fopen("symtab.txt", "r+");
  char label[10], opcode[10], operand[10];
  char op[10], code[10], sym[10], pos[10];
  int start;

  fscanf(fp1, "%s %s %x", label, opcode, &start);
  int locctr;
  int dup = 0;
  int invalid = 0;

  if (strcmp(opcode, "START") == 0) { // if both equal then 0
    locctr = start;
    fprintf(fp2, "\t\t%s\t%s\t\t%X\n", label, opcode, start);
    fscanf(fp1, "%s %s %s", label, opcode, operand);
  } else {
    locctr = 0;
  }
  do {
    fprintf(fp2, "%X\t\t%s\t\t%s\t\t%s\t\t\n", locctr, label, opcode, operand);

    if (strcmp(label, "**") != 0) {
      int flag1 = 0;
      while (!feof(fp3)) {
        fscanf(fp3, "%s %s \n", sym, pos);
        if (strcmp(sym, label) == 0) {
          dup = 1;
          flag1 = 1;
          break;
        }
      }
      if (flag1 == 0)
        fprintf(fp3, "%s\t\t%X\n", label, locctr);
    }
    int flag2 = 0;
    fp4 = fopen("optab.txt", "r");
    while (!feof(fp4)) {
      fscanf(fp4, "%s %s", op, code);
      if (strcmp(op, opcode) == 0)
        flag2 = 1;
    }
    if (flag2 == 1)
      locctr = locctr + 3;
    else if (strcmp(opcode, "WORD") == 0)
      locctr = locctr + 3;
    else if (strcmp(opcode, "RESW") == 0)
      locctr = 3 * atoi(operand) + locctr;
    else if (strcmp(opcode, "RESB") == 0)
      locctr = atoi(operand) + locctr;
    else if (strcmp(opcode, "BYTE") == 0) {
      locctr++;
    } else {
      invalid = 1;
    }
    fscanf(fp1, "%s %s %s", label, opcode, operand);
  } while (strcmp(opcode, "END") != 0);

  fprintf(fp2, "\t\t\t\t%s\t\t%s\t\t\n", opcode, operand);

  int length = locctr - start;
  printf("Program Length = %X\n", length);

  fp5 = fopen("length.txt", "w"); // writing length to length.txt
  fprintf(fp5, "%X", length);

  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  fclose(fp4);
  fclose(fp5);
}
