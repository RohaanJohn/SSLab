/*
Name: Rohaan Renu John
Class: S5-CS1
Title: Paging
*/
#include<stdio.h>
#include<stdlib.h>
int n;
struct pgtbl{
int pageno;
int frno;
}P[20];
struct laddr{
int pageno;
int offset;
}l;
int search(int pn){
int j, flag=0;
for(int j=0; j<n; j++){
if(pn==P[j].pageno){
flag=1;
break;
}
}
return flag;
}
int main(){
int pgsize,f,q,c,i;
printf("Enter the page size:\n");
scanf("%d",&pgsize);
printf("Enter the size of page table:\n");
scanf("%d", &n);
printf("Enter the content of the page:\n");
for(int i=0; i<n; i++){
printf("Enter the page number:\n");
scanf("%d",&P[i].pageno);
printf("Enter the frame number:\n");
scanf("%d",&P[i].frno);
}
printf("Print the logical address\n");
do{
printf("Enter the page number:\n");
scanf("%d",&l.pageno);
f=search(l.pageno);
if(f==0){
printf("Page number not found in table.\n");
}
}while(f!=1);
printf("Enter the offset:\n");
scanf("%d",&l.offset);
q=l.offset;
if(q>pgsize){
printf("Offset not valid.\n");
}
for(int i=0;i<n;i++){
if(l.pageno==P[i].pageno){
c=P[i].frno;
}
}
c=c*pgsize;
c=c+l.offset;
printf("Corresponding physical address: %d \n",c);
return 0;
}


/*
Output:
Enter the page size:
4
Enter the size of page table:
4
Enter the content of the page:
Enter the page number:
1
Enter the frame number:
4
Enter the page number:
2
Enter the frame number:
5
Enter the page number:
3
Enter the frame number:
6
Enter the page number:
4
Enter the frame number:
7
Print the logical address
Enter the page number:
2
Enter the offset:
2
Corresponding physical address: 22 
*/
