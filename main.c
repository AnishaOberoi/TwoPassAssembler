/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int variable = 0;
struct OPcodes
{
  char opcode[4];
  char m_opcode[5];
};

struct OPcodes OPC[13]={
    {"CLA", "0000"},  {"LAC", "0001"},  {"SAC", "0010"},  {"ADD", "0011"},  {"SUB", "0100"},  {"BRZ", "0101"},  {"BRN", "0110"},  
    {"BRP", "0111"},  {"INP", "1000"},  {"DSP", "1001"},  {"MUL", "1010"},  {"DIV", "1011"},  {"STP", "1100"}
};


struct label_table
{
  char label[5];
  int address;
} LT[10];

struct symbol_table
{
  char symbol[5];
  int address;
} ST[10];

int check_stp(){ 
  char ch;
  int ans = 0;
  FILE *f1, *f2;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  f1 = fopen ("input.txt", "r");
  f2 = fopen ("input.txt", "r");
  if (f1 == NULL)
    exit (EXIT_FAILURE);

  while ((read = getline (&line, &len, f1)) != -1){
      if(strcmp(line,"STP")==0){
          ans = 1;
      }
  }
  return ans;
}


void add_symbol ()
{
    
  char ch, new_str[3];
  int sum = 0;
  FILE *f1, *f2;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  f1 = fopen ("input.txt", "r");
  f2 = fopen ("input.txt", "r");
  
  if (f1 == NULL)
    exit (EXIT_FAILURE);

  while ((read = getline (&line, &len, f1)) != -1){
      sum = read + sum;
      for (int i = 0; i < 3; i++){
          ch = fgetc (f2);
          new_str[i]=ch;
      }
      fseek (f2, sum, SEEK_SET);
      for(int i = 0; i<13; i++){
          if(strcmp(new_str,OPC[i].opcode)==0){
          printf ("\n%s", new_str);
        }
      }
  }
}




int add_label ()
{
  char ch, sym = '0', temp[5];
  int isLabel = 0, sum = 0, k = 0, label_addr = 100;
  FILE *f1, *f2;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  f1 = fopen ("input.txt", "r");
  f2 = fopen ("input.txt", "r");
  if (f1 == NULL)
    exit (EXIT_FAILURE);

  while ((read = getline (&line, &len, f1)) != -1)
    {
      isLabel = 0;
      sum = read + sum;
      for (int i = 0; i < read; i++)
      {
        ch = fgetc (f2);
	    if (ch == ':'){
	        int loc = 0;
	        fseek (f2, sum - read, SEEK_SET);
	        while (sym != ':')
		    {
		      
		        sym = fgetc (f2);
		        if (sym != ':')
		        {
		            LT[k].address = label_addr;
		            LT[k].label[loc] = sym;
		            loc++;
		        }
		        
		    }
	        int new_loc = sum - read + i + 1;
	        fseek (f2, new_loc, SEEK_SET);
	        k++;
	        sym = '0';
	        label_addr++;
	    }
	  printf ("%c", ch);
      }
    }

  fclose (f1);
  fclose (f2);

  if (line)
    free (line);
  printf ("\n");
  return k;
}
void addressToBinary (int addr)
{
  int a[8], n, i = 0, j = 0, product;
  n = addr;
  for (i = 0; i < 8; i++)
    {
      a[i] = 0;
    }
  i = 0;
  while (n > 0)
    {
      a[i] = n % 2;
      n = n / 2;
      i++;
    }
  if (addr == 0)
    printf ("0");
  for (i = 7; i >= 0; i--)
    {
      printf ("%d", a[i]);
    }
}

void print_labelTable (int k)
{
  printf ("\n------Label Table-----\n");
  for (int i = 0; i < k; i++)
    {
      printf ("\n%s \t", LT[i].label);
      addressToBinary (LT[i].address);
    }
}

void passOne(){ 
  char ch,sym = '0', new_str[4];
  int ans = 0, sum =0,x=0, answer[13], result=0, hasLabel = 0, error = 0,sym_addr=200,j=0;
  FILE *f1, *f2;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  
  for(int i = 0; i<13; i++){
          answer[i]=0;
      }

  f1 = fopen ("input.txt", "r");
  f2 = fopen ("input.txt", "r");
  if (f1 == NULL)
    exit (EXIT_FAILURE);

 while ((read = getline (&line, &len, f1)) != -1){
     ans = 0;
      sum = read + sum;
      for (int i = 0; i < 3; i++){
          ch = fgetc (f2);
          if (ch == ':'){
              hasLabel = 1;
              fseek(f2,(sum-read+3),SEEK_SET);
              for(int j=0; j<3; j++)
              {
                  ch=fgetc(f2);
                  new_str[j]=ch;
                  
              }
              break;
              
          }
          new_str[i]=ch;
      }
      //printf("%s\n",new_str);
      fseek (f2, sum, SEEK_SET);
      
      
          if(strcmp(new_str,"BRN")==0 && hasLabel ==0){
          
          error = 1;
        }
      
          if(strcmp(new_str,"CLA")!=0||strcmp(new_str,"STP")!=0||strcmp(new_str,"BRZ")!=0||strcmp(new_str,"BRN")!=0||strcmp(new_str,"BRP")!=0){
          ST[j].address=sym_addr;
          sym_addr++;
          j++;
          
        }
     
      
      for(int i = 0; i<13; i++){
          if(strcmp(new_str,OPC[i].opcode)==0){
          ans = 1;
          answer[x] = ans;
        }
      }
      x++;
     
  }
  
  
  
  for(int i = 0; i<x; i++){
      if(answer[i]==0){
          result = 0;
          break;
      }
      else{
          result = 1;
      }
     
      }
      if(check_stp()==1 && result == 1 && error != 1){
        variable = 1;
        int k = add_label ();
        print_labelTable (k);
        printf ("\n");
    }else if(check_stp()==0){
        printf("Error: STP missing at the end of assembly instructions");
    }else if(error == 1){
        printf("Undefined Label");
    }else {
        printf("Error: Invalid Opcode");
    
    }
}

void passTwo(){
    
    char ch,sym = '0', new_str[4];
  int ans = 0, sum =0, result=0, hasLabel = 0, error = 0,k=0;
  FILE *f1, *f2;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  
  
  f1 = fopen ("input.txt", "r");
  f2 = fopen ("input.txt", "r");
  if (f1 == NULL)
    exit (EXIT_FAILURE);

 while ((read = getline (&line, &len, f1)) != -1){
     ans = 0;
      sum = read + sum;
      for (int i = 0; i < 3; i++){
          ch = fgetc (f2);
           if (ch == ':'){
              hasLabel = 1;
              fseek(f2,(sum-read+3),SEEK_SET);
              for(int j=0; j<3; j++)
              {
                  ch=fgetc(f2);
                  new_str[j]=ch;
                  
              }
              break;
              
          }
          new_str[i]=ch;
      }
      fseek (f2, sum, SEEK_SET);
      
      
      for(int i = 0; i<13; i++){
          if(strcmp(new_str,OPC[i].opcode)==0){
              printf("\n%s", OPC[i].m_opcode );
              if(strcmp(new_str,"CLA")==0||strcmp(new_str,"STP")==0)
              {
                  
                  printf("00000000");
              }
            else if(strcmp(new_str,"BRN")==0||strcmp(new_str,"BRP")==0||strcmp(new_str,"BRZ")==0)
            {
                addressToBinary(LT[0].address);
            }
            else
            {
               
                    addressToBinary(ST[k].address);
                    k++;
            
            }
              
          }
      }
     
  }
  
    
}

int main ()
{
   passOne();
   printf("\n\n");
   if (variable==1){
   passTwo();
   }
   return 0;
}