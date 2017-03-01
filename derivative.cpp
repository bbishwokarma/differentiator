#include <iostream>
#include <cmath>
#include "derivative.h"
#include "interface.h"

Derivative::Derivative() { }
void Derivative::Nth_order()
{
     if(order_n==1)
         strcpy(sign,"st");
     else if(order_n==2)
         strcpy(sign,"nd");
     else if(order_n==3)
         strcpy(sign,"rd");
     else
         strcpy(sign,"th");  
}     
void Derivative::operator_wise()
{
     char sign1=sign[0];
     char h_term1[1000];
     char h_term2[1000];
     strcpy(h_term1,term1);
     strcpy(h_term2,term2);
     switch(sign1)
     {
         case '+':
         case '-':
             calc_derivative(term1);
             if(sign1=='+')
                  strcat(answer,"+");
             else 
                  strcat(answer,"-");
             calc_derivative(h_term2);
             break;
         case '*':
              if((func.function_type(term1)=='a') && (func.function_type(term2)=='a'))
                   strcat(answer,"0");
              else if(func.function_type(term1)=='a')
              {
                   strcat(answer,term1);
                   strcat(answer,"*(");
                   calc_derivative(term2);
                   strcat(answer,")");
              }
              else if(func.function_type(term2)=='a')
              {
                   strcat(answer,"(");
                   calc_derivative(term1);
                   strcat(answer,")*(");
                   strcat(answer,h_term2);
                   strcat(answer,")");
              }
              else
              {
                   strcat(answer,"(");
                   calc_derivative(term1);
                   strcat(answer,")*");
                   strcat(answer,h_term2);
                   strcat(answer,"+(");
                   calc_derivative(h_term2); 
                   strcat(answer,")*");
                   strcat(answer,h_term1);
                   
              }
              break;
          case '/':  
               if((func.function_type(term1)=='a') && (func.function_type(term2)=='a'))
                   strcat(answer,"0");
               else if(func.function_type(term1)=='a')
               {   
                    char term3[1000]; 
                    int flag=0;
                    strcat(answer,"-((");
                    strcat(answer,term1);
                    strcat(answer,")/(");
                    if(func.function_type(term2)=='c')
                    {
                         simple.remove_outermost_brace(term2);
                         func.part_base_pow(term2,term1,term3);
                         simple.simplification(term3);
                         flag=1;
                    }
                    if(flag==1 && (strlen(term1)==1 || (term1[0]=='(' && term1[strlen(term1)-1]==')')))
                    {
                         strcat(answer,term1);
                         strcat(answer,")^");
                         strcat(answer,"(");
                         strcat(answer,term3);
                         strcat(answer,"+1))*(");
                         strcat(answer,term3);
                         strcat(answer,")*(");  
                         calc_derivative(term1);
                         strcat(answer,")");
                    }
                    else
                    {    strcat(answer,term2);
                         strcat(answer,")^2)*(");
                         calc_derivative(term2);
                         strcat(answer,")");
                    }
               }
               else if(func.function_type(term2)=='a')
              {
                   strcat(answer,"(");
                   calc_derivative(term1);
                   strcat(answer,")/(");
                   strcat(answer,h_term2);
                   strcat(answer,")");
              }
              else
              {
                   strcat(answer,"((");
                   calc_derivative(term1);
                   strcat(answer,")*"); 
                   strcat(answer,h_term2);
                   strcat(answer,"-(");
                   calc_derivative(h_term2);
                   strcat(answer,")*"); 
                   strcat(answer,h_term1);
                   strcat(answer,")/");
                   strcat(answer,h_term2);
                   strcat(answer,"^2");
              }
               break;
          case '^':
               if((func.function_type(term1)=='a') && (func.function_type(term2)=='a'))
                   strcat(answer,"0");
               else if(func.function_type(term1)=='a')
               {  
                   char *ht1, *ht2;
                   ht1=new char[strlen(term1)+1];
                   ht2=new char [strlen(term2)+1];
                   strcpy(ht1,term1);
                   strcpy(ht2,term2);
                   strcat(answer,"(");
                   calc_derivative(term2);
                   strcat(answer,")");
                    if(strcmp(ht1,"e")!=0)
                       {strcat(answer,"*ln");
                       strcat(answer,ht1);}
                   strcat(answer,"*");
                   strcat(answer,ht1);
                   strcat(answer,"^");
                   strcat(answer,ht2);
                  // strcat(answer,")");
                  delete []ht1;
                  delete []ht2;
               }
               else if(func.function_type(term2)=='a')
               {   
                    char *ht1, *ht2;
                    ht1=new char[strlen(term1)+1];
                    ht2=new char [strlen(term2)+1];
                    strcpy(ht1,term1);
                    strcpy(ht2,term2);
                   // simple.simplification(term2);
                 //   strcat(answer,"(");
                    strcat(answer,term2);
                    strcat(answer,"*(");
                    calc_derivative(term1);
                    strcat(answer,")*");
                    strcat(answer,ht1);
                    strcat(answer,"^(");
                    strcat(answer,ht2);
                    strcat(answer,"-1)"); 
                    delete []ht1;
                    delete []ht2;
               }
               else
               {
                   char *ht1, *ht2;
                   ht1=new char[strlen(term1)+1];
                   ht2=new char [strlen(term2)+1];
                   strcpy(ht1,term1);
                   strcpy(ht2,term2);
                   strcat(answer,"(");
                   strcat(term2,"*ln");
                   strcat(term2,term1);
                   calc_derivative(term2);
                   strcat(answer,")*");
                   strcat(answer,ht1);
                   strcat(answer,"^");
                   strcat(answer,ht2);
                   delete []ht1;
                   delete []ht2; 
               }
     }
}

void Derivative::start_with_braces(char expr[])
{
     size=strlen(expr);  
     term2[0]='\0';
     int k=2;
     simple.term_in_braces(expr,term1,beginning,ending);
     if(expr[ending+1]=='\0')
        {calc_derivative(term1); is_done=1; return; } 
     if(expr[ending+1]=='*' || expr[ending+1]=='/' || expr[ending+1]=='+' || 
        expr[ending+1]=='-' || expr[ending+1]=='^')
           sign[0]=expr[ending+1]; 
     else if(expr[ending+1]=='(')
         {sign[0]='*'; k=1;} 
     else return; 
     sign[1]='\0'; 
     int siz=strlen(term1);
     char *hterm=new char[siz+1];
     strcpy(hterm,term1);
     term1[0]='(';
     for(int z=0; z<siz; z++)
          {term1[z+1]=hterm[z]; term1[z+2]='\0';}
     delete [] hterm;
     strcat(term1,")"); 
     for(int i=0; i<(size-(ending+k));i++)
        {term2[i]=expr[ending+k+i]; term2[i+1]='\0';} 
     operator_wise();
     is_done=1;
}  
// if operator signs + - * / are there in between terms;                              
void Derivative::term_with_sign(char param[])
{
  char sign1=' ';   
  int brace=0,i=0;
  while(sign1==' ' &&  i<strlen(param))
  {
    if(param[i]=='(')
       brace++;
     else if(param[i]==')')
        brace--; 
     term1[i++]=param[i];
     term1[i]='\0';
     if(brace==0 && (param[i]==sign[0] || param[i]==sign[1]))
        sign1=param[i++];
  }
  int j=0;
  while(i<strlen(param))
  {
     term2[j++]=param[i++];
  } 
  term2[j]='\0';
  if(sign1==sign[0] || sign1==sign[1])
  {    
       if(sign1==sign[1])
            sign[0]=sign[1];
      operator_wise(); 
      is_done=1; 
  } 
} 
//if multiplication sign is there
int Derivative::with_multiplying(char param[])
{
    int braces=0;
    sign[0]=' ';
    int b=0;
    while (b<strlen(param) && sign[0]==' ')
    {
          if(param[b]=='(') braces++;
          else if(param[b]==')') braces--;
          term1[b++]=param[b];
          term1[b]='\0';
          if(braces==0 && param[b]=='*')
               sign[0]=param[b++];
    }
    int j=0;
    while(b<strlen(param))
    {
        term2[j++]=param[b++];
    } 
    term2[j]='\0';
    if(sign[0]=='*')
    {   
      operator_wise(); 
      return 1;
    } 
}                           
//takes a small term & returns the derivative
void Derivative::call_formulae(char small_term[])  
{
     if(small_term[0]=='-')
     {
         strcat(answer,"-");
         int i;
         for(i=1; i<strlen(small_term);i++)
             small_term[i-1]=small_term[i]; 
         small_term[i-1]='\0';
     }
     ch1=func.function_type(small_term);
     switch(ch1)
     {
       case 'a':
            if_constant(small_term);
            break;
       case 'b':
            if_linear(small_term);
            break;
       case 'c':
            if_x_pow_cons(small_term);
            break;
       case 'd':
            if_cons_pow_x(small_term);
            break;
       case 'e':
            if_x_pow_x(small_term);
            break;
       case 'f':
            if_ln(small_term);
            break;
       case 'g':
            if_log(small_term);
            break;
       case 'h':
            if_sin(small_term);
            break;
       case 'i':
            if_cos(small_term);
            break;
       case 'j':
            if_tan(small_term);
            break;
       case 'k':
            if_cosec(small_term);
            break;
       case 'l':
            if_sec(small_term);
            break;
       case 'm':
            if_cot(small_term);
            break;
       case 'n':
            if_asin(small_term);
            break;
       case 'o':
            if_acos(small_term);
            break;
       case 'p':
            if_atan(small_term);
            break;
       case 'q':
            if_acosec(small_term);
            break;
       case 'r':
            if_asec(small_term);
            break;
       case 's':
            if_acot(small_term);
            break;
       case 't':
            if_sinh(small_term);
            break;
       case 'u':
            if_cosh(small_term);
            break;
       case 'v':
            if_tanh(small_term);
            break;
       case 'w':
            if_cosech(small_term);
            break;
       case 'x':
            if_sech(small_term);
            break;
       case 'y':
            if_tanh(small_term);
            break;
       case 'A':
            if_asinh(small_term);
            break;
       case 'B':
            if_acosh(small_term);
            break;
       case 'C':
            if_atanh(small_term);
            break;
       case 'D':
            if_acosech(small_term);
            break;
       case 'E':
            if_asech(small_term);
            break;
       case 'F':
            if_acoth(small_term);
            break;
     }
}
//formulae part ----------------------------------------------------------------
//a. for constant term designated by a : dy/dx=0;
void Derivative::if_constant(char  param[])  
{   
   size=strlen(answer);
   if(size==0 || answer[size-1]=='+' || answer[size-1]=='-'  || answer[size-1]=='('
      || answer[size-1]=='*'|| answer[size-1]=='/'|| answer[size-1]=='^')
          strcpy(param,"0");
   else
      strcpy(param,"*0");
   strcat(answer,param);
}
//b. for linear term , designated by z :dy/dx=constant;
void Derivative::if_linear(char param[])    
{   
   int j=0;
   size=strlen(param);
   if(size==1)
     {strcat(answer,"1"); return; }
   for(int i=0;i<size;i++)
      if(param[i]=='x' || param[i]=='X')
          continue;                           
      else
          param[j++]=param[i];      //null and end of string
   param[j]='\0';
   simple.simplification(param);
   strcat(answer,param);
}
//c. for terms like x^a , designated by c: dy/dx=nx^(n-1); 
void Derivative::if_x_pow_cons(char param[])    
{
     int size=strlen(param);
     func.part_base_pow(param,term1,term2);//term2 is used as power
     simple.simplification(term2);
     strcat(answer,"(");
     strcat(answer,term2);
     strcat(answer,")*");
     strcpy(param,term1);
     strcat(param,"^(");
     strcat(param,term2);
     strcat(param,"-1)");
     simple.simplification(param); 
     char *param1=new char[strlen(param)+1];
     strcpy(param1,param);
     calc_derivative(term1);
     strcat(answer,"*");
     strcat(answer,param1);
     delete [] param1;   
    // strcat(answer,")");
}
//d. for terms like a^x, designated by d: dy/dx=a^x * ln(a)
void Derivative::if_cons_pow_x(char param[])     
{
     func.part_base_pow(param,term1,term2);
     if(strcmp(term1,"e")!=0)
     {
            strcat(param,"*ln(");
            strcat(param,term1);
            strcat(param,")");
     }
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}  
//e. for terms like x^x, designated by c: dy/dx=x^x *(1+lnx);
void Derivative::if_x_pow_x(char param[])     
{
     simple.simplification(param);
     func.part_base_pow(param,term1,term2);
     strcat(answer,param);
     strcpy(param,term2);
     strcat(param,"*ln");
     strcat(param,term1);
     simple.simplification(param);
     strcat(answer,"*(");
     calc_derivative(param); 
     strcat(answer,")"); 
}
//f. for ln(x) designated by f: dy/dx=1/x;
void Derivative::if_ln(char param[])             
{
     func.part_arg(param,"ln",term2);
     strcpy(param,"1/");
     strcat(param,term2);
   //  strcat(param,")");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
     
}
//g. for log(x) with base a designated by y: dy/dx=(1/x)*loge
void Derivative::if_log(char param[])           
{
     func.part_arg(param,"log",term2);
     strcpy(param,"(1/(");
     strcat(param,term2);
     strcat(param,"))*loge");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*(");
     calc_derivative(term2);
     strcat(answer,")");
} 
//h. for sin(x) designated by g: dy/dx=cos(x)
void Derivative::if_sin(char param[])            
{
     func.part_arg(param,"sin",term2);
     strcpy(param,"cos");
     strcat(param,term2);
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*(");
     calc_derivative(term2);
     strcat(answer,")");
}
//i.  for cos(x) designated by i: dy/dx=-sinx
void Derivative::if_cos(char param[])            
{
     func.part_arg(param,"cos",term2);
     strcpy(param,"(-sin");
     strcat(param,term2);
     strcat(param,")");
     if(strlen(answer)==0)
          for_globals::Last_of_answer='p';   //p for possible to remove (   ) 
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//j.  for tan(x) designated by j: dy/dx=(secx)^2
void Derivative::if_tan(char param[])            
{
     func.part_arg(param,"tan",term2);
     strcpy(param,"(sec");
     strcat(param,term2);
     strcat(param,")^2");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//k.  for cosec(x) designated by h: dy/dx=-cosecx.cotx
void Derivative::if_cosec(char param[])          
{
     func.part_arg(param,"cosec",term2);
     strcpy(param,"-cosec");
     strcat(param,term2);
     strcat(param,"*cot");
     strcat(param,term2);
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//l.  for sec(x) designated by k: dy/dx=secx.tanx;
void Derivative::if_sec(char param[])            
{
     func.part_arg(param,"sec",term2);
     strcpy(param,"sec");
     strcat(param,term2);
     strcat(param,"*tan");
     strcat(param,term2);
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//m.  for cot(x) designated by l: dy/dx=-(cosecx)^2
void Derivative::if_cot(char param[])            
{
     func.part_arg(param,"cot",term2);
     strcpy(param,"-(cosec");
     strcat(param,term2);
     strcat(param,")^2");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//n.  for asin(x) designated by m: dy/dx=1/(1-x^2)^(1/2)
void Derivative::if_asin(char param[])          
{
     func.part_arg(param,"asin",term2);
     strcpy(param,"(1/(1-");
     strcat(param,term2);
     strcat(param,"^2)^(1/2))");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//o.  for acos(x) designated by o: dy/dx=-1/(1-x^2)^(1/2)
void Derivative::if_acos(char param[])           
{
     func.part_arg(param,"acos",term2);
     strcpy(param,"(-1/(1-");
     strcat(param,term2);
     strcat(param,"^2)^(1/2))");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//p.  for atan(x) designated by p: dy/dx=1/(1+x^2);
void Derivative::if_atan(char param[])           
{
     func.part_arg(param,"atan",term2);
     strcpy(param,"(1/(1+");
     strcat(param,term2);
     strcat(param,"^2))");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//18.  for acosec(x) designated by n: dy/dx=-1/(1+x^2)
void Derivative::if_acosec(char param[])         
{
     func.part_arg(param,"acosec",term2);
     strcpy(param,"(-1/(1+");
     strcat(param,term2);
     strcat(param,"^2))");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//q.  for asec(x) designated by q: dy/dx=1/(x(x^2-1)^(1/2))
void Derivative::if_asec(char param[])           
{
     func.part_arg(param,"asec",term2);
     strcpy(param,"(1/(");
     strcat(param,term2);
     strcat(param,"*(");
     strcat(param,term2);
     strcat(param,"^2-1)^(1/2)))");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//r.  for acot(x) designated by r: dy/dx=-1/(x(x^2-1)^(1/2))
void Derivative::if_acot(char param[])           
{
     func.part_arg(param,"acot",term2);
     strcpy(param,"(-1/(");
     strcat(param,term2);
     strcat(param,"*(");
     strcat(param,term2);
     strcat(param,"^2-1)^(1/2)))");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//s.  for sinh(x) designated by s: dy/dx=coshx
void Derivative::if_sinh(char param[])           
{
     func.part_arg(param,"sinh",term2);
     strcpy(param,"cosh");
     strcat(param,term2);
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//t.  for cosh(x)  designated by u: dy/dx=sinhx
void Derivative::if_cosh(char param[])           
{
     func.part_arg(param,"cosh",term2);
     strcpy(param,"sinh");
     strcat(param,term2);
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//u.  for tanh(x) designated by v: dy/dx=(sechx)^2
void Derivative::if_tanh(char param[])           
{
     func.part_arg(param,"tanh",term2);
     strcpy(param,"(sech");
     strcat(param,term2);
     strcat(param,")^2");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//v.  for cosech(x) designated by t: dy/dx=-cosechx.cothx
void Derivative::if_cosech(char param[])         
{
     func.part_arg(param,"cosech",term2);
     strcpy(param,"-cosech");
     strcat(param,term2);
     strcat(param,".coth");
     strcat(param,term2);
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//w.  for sech(x)  designated by w: dy/dx=-sechx.tanhx
void Derivative::if_sech(char param[])            
{
     func.part_arg(param,"sech",term2);
     strcpy(param,"-sech");
     strcat(param,term2);
     strcat(param,".tanh");
     strcat(param,term2);
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//x.  for coth(x) designated by x: dy/dx=-(cosechx)^2
void Derivative::if_coth(char param[])            
{
     func.part_arg(param,"coth",term2);
     strcpy(param,"-(cosech");
     strcat(param,term2);
     strcat(param,")^2");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}    
//A.  for asinh(x) designated by A: dy/dx=1/(1+x^2)^(1/2)
void Derivative::if_asinh(char param[])            
{
     func.part_arg(param,"asinh",term2);
     strcpy(param,"(1/(1+");
     strcat(param,term2);
     strcat(param,"^2)^(1/2))");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//B.  for acosh(x) designated by C: dy/dx=1/(x^2-1)^(1/2)
void Derivative::if_acosh(char param[])            
{
     func.part_arg(param,"acosh",term2);
     strcpy(param,"(1/(");
     strcat(param,term2);
     strcat(param,"^2-1)^(1/2)))");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
} 
//C.  for atanh(x) designated by D: dy/dx=1/(1-x^2)
void Derivative::if_atanh(char param[])            
{
     func.part_arg(param,"acoth",term2);
     strcpy(param,"(1/(1-");
     strcat(param,term2);
     strcat(param,"^2))");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//D.  for acosech(x) designated by B: dy/dx=-1/(x(x^2+1)^(1/2))
void Derivative::if_acosech(char param[])            
{
     func.part_arg(param,"acosech",term2);
     strcpy(param,"(-1/(");
     strcat(param,term2);
     strcat(param,"*(");
     strcat(param,term2);
     strcat(param,"^2+1)^(1/2)))");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//E.  for asech(x) designated by E: dy/dx=-1/(x(1-x^2)^(1/2))
void Derivative::if_asech(char param[])            
{
     func.part_arg(param,"asech",term2);
     strcpy(param,"(-1/(");
     strcat(param,term2);
     strcat(param,"*(1-");
     strcat(param,term2);
     strcat(param,"^2)^(1/2)))");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
}
//F.  for acoth(x) designated by F: dy/dx=-1/(x^2-1)
void Derivative::if_acoth(char param[])            
{
     func.part_arg(param,"acoth",term2);
     strcpy(param,"(-1/(");
     strcat(param,term2);
     strcat(param,"^2-1))");
     simple.simplification(param);
     strcat(answer,param);
     strcat(answer,"*");
     calc_derivative(term2);
} 
//------------------------------------------------------------------------------

int Derivative::read_expression()
{   
      order_n=1;
     strcpy(answer,"\0");
     strcpy(in_expression,"\0");
     strcpy(term1,"\0");
     strcpy(term2,"\0");
     strcpy(sign,"\0");
     ch1='\0';
     return read_question(in_expression,"DIFFERENTIATION","     f(x)="); 
}
void Derivative::differentiate()
       {
           int y;
           calc_derivative(in_expression);
           simple.simplification(answer);
           if(strlen(answer)==0)
               strcpy(answer,"0");
           if(answer[0]=='+')
           {
              for(y=1; y<strlen(answer); y++)
                  answer[y-1]=answer[y];
              answer[y-1]='\0';
           }
       } 
void Derivative::calc_derivative(char ques[])
       {  
           char question[1000];
           is_done=0;  
           strcpy(question,ques);
           simple.simplification(question);  
           sign[0]='+';
           sign[1]='-';
           sign[2]='\0';
           term_with_sign(question); 
           if(is_done==1)
               return; 
           if(with_multiplying(question)==1)
               return;
           sign[0]='*';
           sign[1]='/';
           sign[2]='\0';
           term_with_sign(question); 
           if(is_done==1)
               return;  
           if(question[0]=='(')
             {  start_with_braces(question);}
           if(is_done==1)
                return;   
           call_formulae(question);
       }                         
int Derivative::display()
{
    Nth_order();
    char ch1[30];
    char ch2[30];
    char order[4];
    int k=0;
    simple.num_to_char(order,order_n,k);
    strcpy(ch1,"The ");
    strcat(ch1,order);
    strcat(ch1,sign);
    strcat(ch1," order derivative:");
    if(order_n==1)
      strcpy(ch2,"dy/dx=");
        else
        {strcpy(ch2,"d^");
          strcat(ch2,order);
          strcat(ch2,"(y)/dx^");
          strcat(ch2,order);
          strcat(ch2," = ");
        }
    return show_derivative(in_expression,answer,ch1,ch2);                
}

void Derivative::diff_further()
{
      order_n++;
      strcpy(in_expression,answer);
      strcpy(answer,"\0");
}
void Derivative::der_at_point()
{
     float rep;
     if(read_rep(answer,rep)==0)
       return;
     simple.rep_x(answer,rep);
     simple.simplification(answer);
     if(strlen(answer)==0)
          strcpy(answer,"0");
     int y;
     if(answer[0]=='+')
     {
            for(y=1; y<strlen(answer); y++)
                  answer[y-1]=answer[y];
            answer[y-1]='\0';
     }
     give_der_at_point(answer);
}
