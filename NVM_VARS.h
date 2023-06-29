#include "NVM.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
void VARADD(int VCODE,int num)
{
VARCODES[LFVC][0] = VCODE;
VARCODES[LFVC][1] = LFV;
VARS[LFV] = num;
if(DEBUG)
  printf("LFVC:%d___LFV:%d___VCODE:%d___VARCODE%d___VAR:%d\n",LFVC,LFV,VARCODES[LFVC][0],VARCODES[LFVC][1],VARS[VARCODES[LFVC][1]]);   //there is a bug: you can add multiple vars with same code(reads only first)
LFV++;
LFVC++;
}
int VARREAD(int VCODE)
{
    int temp;
    //printf("START");
    //printf("founding");
for(int i=0;i<65536;i++)
{   
    //printf(".");
    //printf("I:%dVCODE:%d,VARIND:%d,VAR:%d",i,VARCODES[i][0],VARCODES[i][1],VARS[VARCODES[i][1]]);
    if(VARCODES[i][0] == VCODE)
    {   
        if(DEBUG){
          printf("FOUND,VCODE:%d,VARIND:%d,VAR:%d\n",VARCODES[i][0],VARCODES[i][1],VARS[VARCODES[i][1]]);}
        temp = VARS[VARCODES[i][1]];
        break;
    } 
}
return temp;
}
void VARDEL(int VCODE)
{
    for(int i=0;i<65536;i++)
{   
    if(VARCODES[i][0] == VCODE)
    {   
        if(DEBUG){
          printf("FOUND,VCODE:%d,VARIND:%d,VAR:%d,DELETING NOW\n",VARCODES[i][0],VARCODES[i][1],VARS[VARCODES[i][1]]);}
        VARS[VARCODES[i][1]] = NULL;
        VARCODES[i][1] = NULL;
        VARCODES[i][0] = NULL;
    } 
}
}
void VAREDIT(int VCODE,int num)
{
    int VI;                                                       //varcode/var index
    for(int i = 0; i<65536;i++)
    {
        if(VARCODES[i][0] == VCODE)
        {
            VI = i;
            break;
        }
    }
  if(VARCODES[VI][0] == VCODE)
  {
    if(DEBUG){printf("succesfully edited from - %d to ",VARS[VARCODES[VI][1]]);}               //delete all variables with this number
    VARS[VARCODES[VI][1]] = num;
    if(DEBUG){printf("%d\n",VARS[VARCODES[VI][1]]);}
  }   
}