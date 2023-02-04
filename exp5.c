/*
Name:
Class: S5-CS1
Title: 1 Pass Assembler
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// input files: input.txt(program.txt) & optab.txt
// output files: intermediate.txt & symtab.txt

char addr[10];
int searchStrSym(char operand[10]) {
  FILE *fp3;
  char sym[10];
  fp3 = fopen("symtab.txt", "r");
  while (!feof(fp3)) {
    fscanf(fp3, "%s %s", sym, addr);
    if (strstr(operand, sym) == 0) {
      fclose(fp3);
      return 0;
    }
  }
  fclose(fp3);
  return 1;
}
int main() {
  FILE *fp1, *fp2, *fp3, *fp4, *fp5;

  fp1 = fopen("input.txt", "r");
  fp2 = fopen("record.txt", "w");
  fp5 = fopen("intermediate.txt", "w");
  char label[10], opcode[10], operand[10];
  char op[10], code[10], sym[10], pos[10];
  int start;
  int repl1, repl2;
  fscanf(fp1, "%s %s %X", label, opcode, &start);
  int locctr;
  int dup = 0;
  int invalid = 0;
  int flag3;
  int c = -1;

  if (strcmp(opcode, "START") == 0) { // if both equal then 0
    locctr = start;
    fprintf(fp2, "H^%s^%X^****^\n", label, start);
    fprintf(fp2, "T^%X^****^", start);
    fprintf(fp5, "%20s%11s%11X\n", label, opcode, start);
    fscanf(fp1, "%s %s %s", label, opcode, operand);
  } else {
    locctr = 0;
  }

  do {
    fprintf(fp5, "%X\t\t\t\t%-14s%-12s%-11s\t\t", locctr, label, opcode,
            operand);
    if (strcmp(label, "**") != 0) {
      int flag1 = 0;
      fp3 = fopen("symtab.txt", "r+");
      while (!feof(fp3)) {
        fscanf(fp3, "%s %s \n", sym, pos);
        if (strcmp(sym, label) == 0) {
          if (strcmp(pos, "----") == 0) {
            int ro = ftell(fp5);
            fscanf(fp3, "%d %d", &repl1, &repl2);
            fseek(fp2, repl1, SEEK_SET);
            fseek(fp5, repl2, SEEK_SET);
            fprintf(fp2, "%X^", locctr);
            fprintf(fp5, "%X\n", locctr);
            fseek(fp5, ro, SEEK_SET);
            fseek(fp3, -12, SEEK_END);
            fprintf(fp3, "%X          ", locctr); // here 4019 + blank space
            flag1 = 1;
            break;
          }
          dup = 1;
          flag1 = 1;
          break;
        }
      }
      if (flag1 == 0) {
        fprintf(fp3, "%s\t\t%X\n", label, locctr);
      }
      fclose(fp3);
    }
    int flag2 = 0;
    fp4 = fopen("optab.txt", "r");
    while (!feof(fp4)) {
      fscanf(fp4, "%s %s", op, code);
      if (strcmp(op, opcode) == 0) {
        flag2 = 1;
        fprintf(fp2, "%s", code);
        fprintf(fp5, "%s", code);
      }
    }
    fclose(fp4);
    if (flag2 == 1) {
      flag3 = 0;
      fp3 = fopen("symtab.txt", "r");
      while (!feof(fp3)) {
        fscanf(fp3, "%s %s \n", sym, addr);
        if (strcmp(sym, operand) == 0) {
          flag3 = 1;
          fprintf(fp2, "%s^", addr);
          fprintf(fp5, "%s", addr);
        } else {
          char cop[10];
          for (int i = 0; i < strlen(operand); i++)
            if (operand[i] == 44) { //, ascii value is 44
                                    // if (flag3 == 0) {
              flag3 = 1;
              int j = 0;
              int k = 0;
              while (j < i)
                cop[k++] = operand[j++];
              if (strcmp(sym, cop) == 0) {
                fprintf(fp2, "%s^", addr);
                fprintf(fp5, "%s", addr);
              }
              break;
            }
        }
      }
      fclose(fp3);
      if (flag3 == 0) {
        fprintf(fp5, "----");
        fprintf(fp2, "----^");
        fp3 = fopen("symtab.txt", "a");
        fprintf(fp3, "%s\t\t----\t%ld %ld", operand, ftell(fp2) - 5,
                ftell(fp5) - 4);
        fclose(fp3);
      }
    }

    if (flag2 == 1)
      locctr = locctr + 3;
    else if (strcmp(opcode, "WORD") == 0) {
      int a = atoi(operand);
      if (strlen(operand) == 1) {
        fprintf(fp2, "00000%d^", a);
        fprintf(fp5, "00000%d", a);
      }

      if (strlen(operand) == 2) {
        fprintf(fp2, "0000%d^", a);
        fprintf(fp5, "0000%d", a);
      }
      if (strlen(operand) == 3) {
        fprintf(fp2, "000%d^", a);
        fprintf(fp5, "000%d", a);
      }
      if (strlen(operand) == 4) {
        fprintf(fp2, "00%d^", a);
        fprintf(fp5, "00%d", a);
      }
      if (strlen(operand) == 5) {
        fprintf(fp2, "0%d^", a);
        fprintf(fp5, "0%d", a);
      }
      if (strlen(operand) == 6) {
        fprintf(fp2, "%d^", a);
        fprintf(fp5, "%d", a);
      }
      locctr = locctr + 3;
    } else if (strcmp(opcode, "RESW") == 0)
      locctr = 3 * atoi(operand) + locctr;
    else if (strcmp(opcode, "RESB") == 0)
      locctr = atoi(operand) + locctr;
    else if (strcmp(opcode, "BYTE") == 0) {
      for (int i = 0; i < strlen(operand); i++)
        if (operand[i] == 39) { //' ascii value is 39
          i++;
          while (operand[i] != 39) {
            fprintf(fp2, "%c", operand[i]);
            fprintf(fp5, "%c", operand[i]);
            i++;
          }
        }
      fprintf(fp2, "^");
      locctr++;
    } else {
      invalid = 1;
    }
    fprintf(fp5, "\n");
    fscanf(fp1, "%s %s %s", label, opcode, operand);
  } while (strcmp(opcode, "END") != 0);

  fprintf(fp2, "\nE^%X", start);
  fclose(fp2);

  int length = locctr - start;
  fp2 = fopen("record.txt", "r+");
  char rep;
  int l = -1;
  while (1) {
    rep = fgetc(fp2);
    l++;
    if (feof(fp2))
      break;
    if (rep == '*') {
      fseek(fp2, l, SEEK_SET);
      fprintf(fp2, "%X", length);
      fseek(fp2, l + 1, SEEK_SET);
    }
  }

  fclose(fp1);
  fclose(fp2);
  fclose(fp5);
}
