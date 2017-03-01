#include <iostream>
#include "function_arg.h"

//function checks what type of function a term requires
char function_arg::function_type(char term_in[])   
{ 
   n=strlen(term_in);
   constant=1;
   char toreturn=' ';
   for(int i=0;i<n;i++)
   {   
       if(i<2) {twochar[i]=term_in[i];   twochar[i+1]='\0'; }
       if(i<3) {threechar[i]=term_in[i]; threechar[i+1]='\0';}
       if(i<4) {fourchar[i]=term_in[i];  fourchar[i+1]='\0';} 
       if(i<5) {fivechar[i]=term_in[i];  fivechar[i+1]='\0';}
       if(i<6) {sixchar[i]=term_in[i];   sixchar[i+1]='\0';}
       if(i<7) {sevenchar[i]=term_in[i]; sevenchar[i+1]='\0';}
                
       if(term_in[i]=='x' || term_in[i]=='X')   //whether term is constant of not, a for constant
           constant=0;
       if(term_in[i]=='^')                          //check for exponentials
       {                                     
          if(constant ==0 )
          {
             for(int check=0;check<(n-i);check++)
               if(term_in[i+check]=='x' || term_in[i+check]=='X')
                 toreturn='e';             // e for exponentials like x^x
             if(toreturn!='e')
                 toreturn='c';                    // c for exponentials like x^5
          }
          else toreturn='d';             // d for exponentials like 5^x
       }
   }
   if(constant==1)
      return 'a';
   if(strcmp(twochar,"ln")==0)
       return 'f';                                // f for logarithm ln(x)
   if(strcmp(threechar,"log")==0)
       return 'g';                                //g for lagarithm with base a : log(x)
        //check for hyperbolic functions
   if(strcmp(fourchar,"sinh")==0)
       return 't';                                //t for sinh             
   if(strcmp(sixchar,"cosech")==0)
       return 'w';                                //w for cosech                
   if(strcmp(fourchar,"cosh")==0)
       return 'u';                                //u for cosh                
   if(strcmp(fourchar,"tanh")==0)
       return 'v';                                //v for tanh              
   if(strcmp(fourchar,"sech")==0)
       return 'x';                                //x for sech               
   if(strcmp(fourchar,"coth")==0)
       return 'y';                                //y for coth              
   if(strcmp(fivechar,"asinh")==0)
       return 'A';                                //A for asinh              
   if(strcmp(sevenchar,"acosech")==0)
       return 'D';                                //D for acosech          
   if(strcmp(fivechar,"acosh")==0)
       return 'B';                                //B for acosh          
   if(strcmp(fivechar,"atanh")==0)
       return 'C';                                //C for atanh         
   if(strcmp(fivechar,"asech")==0)
       return 'E';                                //E for asech             
   if(strcmp(fivechar,"acoth")==0)
       return 'F';                                //F for acoth
   if(strcmp(threechar,"sin")==0)
       return 'h';                                //h for sine    
   if(strcmp(fivechar,"cosec")==0)
       return  'k';                               //k for cosec
   if(strcmp(threechar,"cos")==0)
       return  'i';                               //i for cosine
   if(strcmp(threechar,"tan")==0)
       return 'j';                                //j for tangent
   if(strcmp(threechar,"sec")==0)
       return 'l';                                //l for sec
   if(strcmp(threechar,"cot")==0)
       return 'm';                                //m for cot
   if(strcmp(fourchar,"asin")==0)
       return 'n';                                //n for arc sine, i.e, (sin^(-1))(x)
   if(strcmp(sixchar,"acosec")==0)
       return 'q';                                //q for arc cosec
   if(strcmp(fourchar,"acos")==0)
       return 'o';                                //o for arc cosine 
   if(strcmp(fourchar,"atan")==0)
       return 'p';                                //p for arc tangent
   if(strcmp(fourchar,"asec")==0)
       return 'r';                                //r for arc sec
   if(strcmp(fourchar,"acot")==0)
       return 's';                                //s for arc cot 
   if(toreturn==' ')
     toreturn='b';                                //b for linear term like 2*x
   return toreturn;
} 
//to separate base & power in exponential
void function_arg::part_base_pow(char param[],char base1[],char power1[])
{
     m=0,flag=0;
     n=strlen(param);
     base1[0]='\0';
     power1[0]='\0';
     for(int i=0;i<n;i++)
     {
        if(param[i]=='^')
             {flag=1; continue;}
        if(flag!=1)
             {base1[i]=param[i]; base1[i+1]='\0';}
        else
             {power1[m++]=param[i]; power1[m]='\0';}
     }
}
//to separate the arguments of function like cos(x)
void function_arg::part_arg(char param[],char compare[],char argu[])
{
     m=strlen(compare),n=strlen(param);
     int j=0;
     argu[0]='\0';
     for(int i=0;i<n;i++)
       if(i>=m)
          argu[j++]=param[i];
     argu[j]='\0';     
}
