/*
Name: Rohaan Renu John
Class: S5-CS1
Title: Pass 2 of 2 pass assembler
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char addr[10];

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

int main() {
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
