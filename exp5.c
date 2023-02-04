/*
Name: Rohaan Renu John
Class: S5-CS1
Title: 1 Pass Assembler
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// input files: input.txt & optab.txt
// output files: intermediate.txt & symtab.txt
char addr[10];

char adop[10];

int searchOp(char opcode[10]) {
  FILE *fp2;
  char op[10];
  fp2 = fopen("optab.txt", "r");
  while (!feof(fp2)) {
    fscanf(fp2, "%s %s", op, adop);
    if (strcmp(op, opcode) == 0) {
      fclose(fp2);
      return 0;
    }
  }
  fclose(fp2);
  return 1;
}

int searchSym(char operand[10]) {
  FILE *fp3;
  char sym[10];
  fp3 = fopen("symtab.txt", "r");
  while (!feof(fp3)) {
    fscanf(fp3, "%s %s", sym, addr);
    if (strcmp(sym, operand) == 0) {
      fclose(fp3);
      return 0;
    }
  }
  fclose(fp3);
  return 1;
}

int searchStrSym(char operand[10]) {
  FILE *fp3;
  char sym[10];
  fp3 = fopen("symtab.txt", "r");
  while (!feof(fp3)) {
    fscanf(fp3, "%s %s", sym, addr);
    if (strstr(sym, operand) == 0) {
      fclose(fp3);
      return 0;
    }
  }
  fclose(fp3);
  return 1;
}

int pass1() {
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

  fprintf(fp2, "*\t\t\t*\t\t\t\t%s\t\t%s\t\t\n", opcode, operand);

  int length = locctr - start;

  fp5 = fopen("length.txt", "w"); // writing length to length.txt
  fprintf(fp5, "%X", length);

  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  fclose(fp4);
  fclose(fp5);
}

int pass2() {
  FILE *fp1, *fp4, *fp5, *fp6;

  fp1 = fopen("intermediate.txt", "r");
  fp4 = fopen("length.txt", "r");
  fp5 = fopen("record.txt", "w");

  char label[10], opcode[10], operand[10], pos[10];
  char op[10], code[10], sym[10], len[10], start[10];

  fscanf(fp1, " %s %s %s", label, opcode, start);

  fscanf(fp4, "%s", len);
  fclose(fp4);

  if (strcmp(opcode, "START") == 0) {
    fprintf(fp5, "H^%s^%s^%s\n", label, start, len);
    fprintf(fp5, "T^%s^%s^", start, len);
    fscanf(fp1, "%s %s %s %s", pos, label, opcode, operand);
  }

  do {

    if (searchOp(opcode) == 0) { // if true then o
      fprintf(fp5, "%s", adop);

      if (searchSym(operand) == 0) {
        fprintf(fp5, "%s^", addr);
      } else if (searchStrSym(operand) == 0) {
        fprintf(fp5, "%s^", addr);
      }

    } else if (strcmp(opcode, "BYTE") == 0) {
      char str1[10];
      for (int i = 0; i < strlen(operand); i++)
        if (operand[i] == 39) { //' ascii value is 39
          i++;
          while (operand[i] != 39) {
            fprintf(fp5, "%c", operand[i]);
            i++;
          }
        }
      fprintf(fp5, "^");
    } else if (strcmp(opcode, "WORD") == 0) {
      int a = atoi(operand);
      if (strlen(operand) == 1)
        fprintf(fp5, "00000%d^", a);
      if (strlen(operand) == 2)
        fprintf(fp5, "0000%d^", a);
      if (strlen(operand) == 3)
        fprintf(fp5, "000%d^", a);
      if (strlen(operand) == 4)
        fprintf(fp5, "00%d^", a);
      if (strlen(operand) == 5)
        fprintf(fp5, "0%d^", a);
      if (strlen(operand) == 6)
        fprintf(fp5, "%d^", a);
    }

    fscanf(fp1, "%s %s %s %s", pos, label, opcode, operand);

  } while (strcmp(opcode, "END") != 0);

  fprintf(fp5, "\nE^%s", start);

  fclose(fp1);
  fclose(fp5);
}

int main() {
  pass1();
  pass2();
}
