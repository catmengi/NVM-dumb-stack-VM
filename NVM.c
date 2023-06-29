
#include "NVM_VARS.h"
int AP;
void VMexec(OPCODES INSTR,int FRST,int SECN,int THRD,int FOUR)
{
    switch(INSTR)
    {
        case PUSH:
        if(SP<STACK_SIZE)
        {                               //push FRST arg to stack
            SP++;
            STACK[SP] = FRST;
        }
        break;
        case POPR:
        sRAM[FRST] = STACK[SP];           //pop stack number to sRAM (address provided by FRST arg)
        if(SP>0)
        {
        STACK[SP] = 0;
        SP--;
        }
        break;
        case PUSR:
        if(SP<STACK_SIZE && FRST<sRAM_SIZE)
        {                                         //push mem[FRST] to stack
        SP++;
        STACK[SP] = sRAM[FRST];
        }
        break;
        case SCAL:                               //SYSCALL interface (yet another switch case)
           switch(FRST)
           {
            case 00001:
            printf("%d",STACK[SP]);              //print number from top of stack
            if(SP>0)
            {   
                STACK[SP] = 0;
                SP--;
            }
            break;
            case 00004:
            printf("\n");
            break;
           }
           break;
        case ADDS:
        int temp1 = STACK[SP];              //add two numbers from stack and push result back
        if(SP>0)
        {   
        STACK[SP] = 0;
        SP--;
        }
        int temp2 = STACK[SP];
        if(SP>0)
        {   
        STACK[SP] = 0;
        SP--;
        }
        if(SP<STACK_SIZE)
        {
        SP++;
        STACK[SP] = temp1 + temp2;
        }
        break;
        case MINS:
        temp1 = STACK[SP];              //minus two numbers from stack and push result back
        if(SP>0)
        {   
        STACK[SP] = 0;
        SP--;
        }
        temp2 = STACK[SP];
        if(SP>0)
        {   
        STACK[SP] = 0;
        SP--;
        }
        if(SP<STACK_SIZE)
        {
        SP++;
        STACK[SP] = temp1 - temp2;
        }
        break;
        case MULS:
        temp1 = STACK[SP];              //mult two numbers from stack and push result back
        if(SP>0)
        {   
        STACK[SP] = 0;
        SP--;
        }
        temp2 = STACK[SP];
        if(SP>0)
        {   
        STACK[SP] = 0;
        SP--;
        }
        if(SP<STACK_SIZE)
        {
        SP++;
        STACK[SP] = temp1 * temp2;
        }
        break;
        case DIVS:
        temp1 = STACK[SP];              //divide two numbers from stack and push result back
        if(SP>0)
        {   
        STACK[SP] = 0;
        SP--;
        }
        temp2 = STACK[SP];
        if(SP>0)
        {   
        STACK[SP] = 0;
        SP--;
        }
        if(SP<STACK_SIZE)
        {
        SP++;
        STACK[SP] = temp1 / temp2;
        }
        break;
        case VARC:
        VARADD(FRST,STACK[SP]);
        if(SP>0)                                    //creates new var with code from FRST arg with number from stack(like push)
        {
          STACK[SP] = NULL;
          SP--;
        }
        break;
        case VARR:
        if(SP<STACK_SIZE)
        {
            SP++;                                         //read var with code from FRST arg and push it to stack
            STACK[SP] = VARREAD(FRST);
        }
        break;
        case JUMP:                                            //jump to addr signed by FRST arg
        if(MAX_AMOUNT_OF_INSTRUCTIONS>FRST)
        {
            IP = FRST-1;
            if(DEBUG)
            {
               printf("JUMP TO:%d\n",FRST);    
            }
            
        }
        break;
        case VARE:
        int VTEMP = STACK[SP];            //edit var by his vcode provided by FRST arg  with number of stack top
        if(SP>0)
        {
        STACK[SP] = NULL;
        SP--;
        }
        VAREDIT(FRST,VTEMP);
        break;
        case VARD:
        VARDEL(FRST);                     //delete all vars with code provided by FRST arg
        break;
        case IFEE:
        temp1 = STACK[SP];              //if first num of stack and second num of stack  are equals jump to addr provided by FRST else jump to addr provided by SECN
        if(SP>0){   
        STACK[SP] = 0;
        SP--;
        }
        temp2 = STACK[SP];
        if(temp1 == temp2)
        {
          if(MAX_AMOUNT_OF_INSTRUCTIONS>FRST)
          {
            IP = FRST-1;
          }
        }else if(MAX_AMOUNT_OF_INSTRUCTIONS>SECN)
          {
            IP = SECN -1;
          }
        break;
        case IFNE:
        temp1 = STACK[SP];              //if first num of stack and second num of stack  are not equals jump to addr provided by FRST else jump to addr provided by SECN
        if(SP>0){   
        STACK[SP] = 0;
        SP--;
        }
        temp2 = STACK[SP];
        if(temp1 != temp2)
        {
          if(MAX_AMOUNT_OF_INSTRUCTIONS>FRST)
          {
            IP = FRST-1;
          }
        }else if(MAX_AMOUNT_OF_INSTRUCTIONS>SECN)
          {
            IP = SECN -1;
          }
        break;
        case ADDO:                                                //add one to element of stack
        STACK[SP]++;
        break;
        case MINO:                                                //minus one to element of stack
        STACK[SP]--;
        break;
        case HALT:
        for(int i  = 0;i<STACK_SIZE;i++){
          printf("STACK TRACE:%d\n",STACK[i]);                            //print STACK and halt VM
          printf("press any key to show next number\n");
          getchar();
        }
        printf("halting VM exit\n");
        exit(0);
        break;
        case FORE:
        int temp = STACK[SP];                                    //if number from stack is greater that FRST jump to addr provided by SECN else jump to addr provided by THDR
        if(FRST>temp)
        {
          if(MAX_AMOUNT_OF_INSTRUCTIONS>SECN)
          {
            IP = SECN-1;
          }
          break;
        }else
        {
          if(MAX_AMOUNT_OF_INSTRUCTIONS>THRD)
          {
            IP = THRD-1;
          }
        }
        break;
}
}
void EXECLOOP()
{
    for(;IP<MAX_AMOUNT_OF_INSTRUCTIONS;IP++)
    {  
        //printf("%d\n",IP);
       VMexec(OPCODEFLOWE[IP].OPCODE,OPCODEFLOWE[IP].ARGS[0],OPCODEFLOWE[IP].ARGS[1],OPCODEFLOWE[IP].ARGS[2],OPCODEFLOWE[IP].ARGS[3]);
    }
}
void ADDINST(OPCODES OPCODE,int FRST,int SECN,int THRD,int FOUR)
    {
    OPCODEFLOWE[AP].OPCODE = OPCODE;OPCODEFLOWE[AP].ARGS[0] = FRST;OPCODEFLOWE[AP].ARGS[1] = SECN;OPCODEFLOWE[AP].ARGS[2] = THRD,OPCODEFLOWE[AP].ARGS[3] = FOUR;  
    AP++;
    }
void main (void)
{     
ADDINST(PUSH,0,0,0,0); 
ADDINST(FORE,256,2,4,0);               //programm examble for cycle (result in 2nd element of stack(press enter once))
ADDINST(ADDO,0,0,0,0);
ADDINST(JUMP,1,0,0,0);
ADDINST(HALT,0,0,0,0);
    EXECLOOP();  
}
