#include <iostream>
#include <cmath>
#include <graphics.h>
#include "simplification.h"
#include "interface.h"
//function to remove outermost braces
int  mani_string::remove_outermost_brace(char expr_in[])
{ 
     if(expr_in[0]!='(' || expr_in[strlen(expr_in)-1]!=')' )
         return 0;
     else
     { 
           int brace=0,i=0;
           while(i<strlen(expr_in))
           {
                 if(expr_in[i]=='(')
                     brace++;
                 else if(expr_in[i]==')')
                     brace--; 
                 if(brace==0 && i!=(strlen(expr_in)-1))
                    return 2;
                 i++;
           }
      }
      expr_in[strlen(expr_in)-1]='\0';
      int q;
      for(q=1; q<strlen(expr_in);q++)
         expr_in[q-1]=expr_in[q];
      expr_in[q-1]='\0';
      return 1;
      
}
//a function to multiply signs like + -   
void mani_string::mult_signs()
{
     int a=0,i=0;
     if(input[0]=='+' || input[0]=='*')
         a++;
     if(input[strlen(input)-1]=='+' || input[strlen(input)-1]=='-' || 
        input[strlen(input)-1]=='*' || input[strlen(input)-1]=='/')
           input[strlen(input)-1]='\0';
     while((i+a)<strlen(input))
     {
          if((input[i+a]=='+' && input[i+a+1]=='-')
              || (input[i+a]=='-' && input[i+a+1]=='+'))
             {input[i]='-'; a++;}
          else if((input[i+a]=='+' && input[i+a+1]=='+')
                  || (input[i+a]=='-' && input[i+a+1]=='-'))
                     {input[i]='+'; a++;}
          else if((input[i+a]=='*' && input[i+a+1]=='*')
            || (input[i+a]=='/' && input[i+a+1]=='/'))
                a++;
          else
              input[i]=input[i+a];
          i++;
     }
     input[i]='\0';
}               
//float just before operator
int mani_string::pos_pre_float(int c_pos)
{
    int k=0;
    while((floatdata[c_pos-k]==0 && intdata[c_pos-k]!=10) || (operate[c_pos-k]=='u' && input[c_pos-k]=='.'))
       k++;
    if(intdata[c_pos-k]==10) k--;
    return c_pos-k;
}
//char after operator
int mani_string::pos_post_char(int c_pos)
{
    int k=1;
    while((input[c_pos+k]>47 && input[c_pos+k]<58) || operate[c_pos+k]=='u')
       k++;
    return c_pos+k;
}
//convert int into char
void mani_string::num_to_char(char input[],int data,int & i2)
{
   int rem=data%10;
   data/=10;
   if(data>0)
      num_to_char(input,data,i2);
   input[i2++]=rem+48;
   input[i2]='\0';
}  
//makes simplified string
void mani_string::make_string()
{   
   char *copy_input=new char[strlen(input)+1];
   int n=strlen(input);
   int i2=0,count=0;
   strcpy(copy_input,input);
   for(int i1=0;i1<n;i1++)
   {  
            if(floatdata[i1]!=0)
            {     
                      if(floatdata[i1]<0.)
                      {
                                switch(input[i2-1])
                                {
                                   case '+':
                                        input[i2-1]='-';
                                        break;
                                   case '-':
                                        input[i2-1]='+';
                                        break;
                                   default:
                                           input[i2++]='-';
                                }
                                floatdata[i1]*=-1.;
                      } 
                      if(floatdata[i1]>=10000)
                      {
                               double d=1;
                               while(floatdata[i1]/pow(10.,++d)>=10);
                               floatdata[i1]/=pow(10,d);
                               do{
                                  if(count==4 && (floatdata[i1]-int(floatdata[i1])>=.5))
                                  floatdata[i1]+=1;
                                  input[i2++]=int(floatdata[i1])+48;
                                  floatdata[i1]-=int(floatdata[i1]);
                                  floatdata[i1]*=10;
                                  if(count==0)
                                        input[i2++]='.';             
                                  input[i2]='\0';
                                  count++;
                               }while(count<5);
                               strcat(input,"*10^");
                               i2+=4;
                               count=0;
                               while(d>=10)
                                  {d=d/10.; count++; }
                               while(count>=0)
                                  {input[i2++]=int(d)+48; d-=int(d); d*=10; count--;}
                               input[i2++]='\0';
                               continue;
                      }
                      else if(floatdata[i1]<0.01)
                      {
                               double d=1;
                               while(floatdata[i1]*pow(10,++d)<1.0);
                               floatdata[i1]*=pow(10,d);
                               do{
                                  if(count==4 && (floatdata[i1]-int(floatdata[i1]))>=.5)
                                       floatdata[i1]+=1;
                                  input[i2++]=int(floatdata[i1])+48;
                                  floatdata[i1]-=int(floatdata[i1]);
                                  floatdata[i1]*=10;
                                  if(count==0)
                                       input[i2++]='.';             
                                  input[i2]='\0';
                                  count++;
                               }while(count<5);
                               strcat(input,"*10^(-");
                               i2+=6;
                               count=0;
                               while(d>=10)
                                  {d=d/10.; count++; }
                               while(count>=0)
                                  { input[i2++]=int(d)+48; d-=int(d); d*=10; count--;}
                               input[i2++]=')';
                               input[i2++]='\0';
                               continue;                  
                      }
                      else 
                      {                          
                              num_to_char(input,int(floatdata[i1]),i2);
                              floatdata[i1]-=int(floatdata[i1]);
                              if(floatdata[i1]!=0)
                                     input[i2++]='.';
                              while(floatdata[i1]!=0)
                              {
                                     if(count==3 && floatdata[i1]>=0.5)
                                     floatdata[i1]+=.1;
                                     floatdata[i1]*=10;
                                     input[i2++]=int(floatdata[i1]+48);
                                     floatdata[i1]-=int(floatdata[i1]);
                                     count++;
                                     if(count==4)
                                            {count=0; break;}
                              }
                      }
            }
            else if(operate[i1]=='u')
                   continue;
            else if(intdata[i1]!=10)
                   input[i2++]='0';
            else if(operate[i1]!=' ')
                   input[i2++]=operate[i1];
            else
                   input[i2++]=copy_input[i1];
   }
   input[i2]='\0';
   delete [] copy_input;
   mult_signs();
}
//identifies one digit integers from string
void mani_string::separate_int_char()
{
   int n=strlen(input);
   int k=1;
   intdata[0]=10;
   for(int i=0;i<n;i++)
   { 
     intdata[i+1]=10;
     operate[i]=' ';
     operate[i+1]='\0';
     if(input[i]==' ')
        operate[i]='u';
     if(input[i]>=48 && input[i]<=57)
     {
        intdata[i]=input[i]-48;
        continue;
     }
     if(input[i]=='+' || input[i]=='-' || 
     input[i]=='*' || input[i]=='/' || input[i]=='^')
     {
        operate[i]=input[i];
        continue;
     }
   }
   for(int j=0;j<n;j++)
     if(operate[j]!=' ' && (intdata[j-1]!=10 && j!=0) 
         && (intdata[j+1]!=10 && j!=n))
           {    
                k=1; int z=1;
                while(intdata[j-k]!=10) k++;
                while(intdata[j+z]!=10) z++;
                if((operate[j-k]=='+' || operate[j-k]=='-' || input[j-k]=='(') &&
                   (operate[j+z]=='+' || operate[j+z]=='-' || input[j+z]==')'))                                 
                        {next_simp=1; break;}
           }
}
//changes the one digit integers into floats/ints of more digit
void mani_string::separate_float_char()
{
   int k=0;
   double d=1;
   bool if_point=0;
   int n=strlen(input);
   for(int i=0;i<n;i++)
   {
      floatdata[i]=0;
      if(intdata[i]!=10)
      {
         if(if_point==1)
         { 
             floatdata[i-k]+=intdata[i]*pow(10,-d); 
             if(k!=0) operate[i]='u'; d++; 
         }
         else  d=1;
         if(if_point==0)
           { floatdata[i-k]=floatdata[i-k]*10+intdata[i]; if(k!=0) operate[i]='u';}
         k++;
         if(intdata[i+1]==10 && input[i+1]!='.')
           k=0;
      }
      else if (input[i]=='.')
      { if_point=1; operate[i]='u'; k++; }
      else if_point=0;
   }
}
//having power
void mani_string::calc_pow()
{
   int size=strlen(input);
   for(int i=0;i<size;i++)
   {
         if(operate[i]=='^')
         {
              int m=pos_pre_float(i-1);
              int n=pos_post_char(i);
              switch(input[n]) 
              {
                   case '+':
                   case '-':
                   case '*':
                   case '/':
                   case '\0':
                   case ' ':
                   case ')':
                         break;
                   default:
                         continue;
              }    
              if(floatdata[i+1]==1)
                    goto point;
              if(floatdata[i+1]==0 && operate[i+1]!='u' && intdata[i+1]!=10)
              {  
                   if(floatdata[m]==0 && intdata[m]!=10 && operate[m]!='u')
                       throw error2();
                   floatdata[m]=1; goto point;
              }
              if((floatdata[m]==0 && intdata[m]!=10 && operate[m]!='u') || floatdata[m]==1)
                    {  goto point; }        
              if(intdata[i-1]==10 || intdata[i+1]==10)
                     continue;                  
              floatdata[m]=pow(floatdata[m],floatdata[i+1]);
              point:
                   floatdata[i+1]=0;
                   operate[i]='u';
                   operate[i+1]='u';
         }
   }
}
//divide of multiply
void mani_string::div_mult()
{
   int size=strlen(input);
   for(int i=0;i<size;i++)
   {
      if(operate[i]=='/' || operate[i]=='*')
      {  
          if(operate[i]=='/' && floatdata[i+1]==0 && intdata[i]!=10 && operate[i]!='u')
             throw error1();
          if((floatdata[i-1]==0. && operate[i-1]!='u' && intdata[i-1]!=10) || 
             (floatdata[i+1]==0 && intdata[i]!=10 && operate[i]!='u'))
             {
                   int k=1;
                   while(operate[i-k]!='+' && operate[i-k]!='-' && i-k!=-1)
                   {
                        operate[i-k]='u';
                        floatdata[i-k]=0.;
                        k++;
                   }
                   k=1;
                   while(operate[i+k]!='+' && operate[i+k]!='-' && i+k!=size)
                   {
                        operate[i-k]='u';
                        floatdata[i-k]=0.;
                        k++;
                   }
             }        
          if(floatdata[i+1]==1.)
          {
             floatdata[i+1]=0;
             operate[i]='u';
             operate[i+1]='u';
             continue;
          }
          else if(floatdata[i-1]==1. && operate[i]=='*' )
          {
             floatdata[i-1]=0;
             operate[i]='u';
             operate[i-1]='u';
             continue;
          }             
          if(intdata[i+1]==10 || intdata[i-1]==10)                
             continue;
          int m=pos_pre_float(i-1);
          int n=pos_post_char(i);     
          if(operate[m-1]=='^' || operate[n]=='^')
             continue;
          if(operate[i]=='/')
             floatdata[m]/=floatdata[i+1];
          else
             floatdata[m]*=floatdata[i+1];
          floatdata[i+1]=0;
          operate[i]='u';
          operate[i+1]='u';
      }
  }
}     
//performs calculation between foats
void mani_string::simplify_floats()
{
   try
     {
        calc_pow();
        div_mult(); 
     }
   catch(error2)
     { throw ;}
   catch(error1)
     {throw ; }
   int size=strlen(input);
   for(int i=0;i<size;i++)
   {
         if(floatdata[i]==0. && intdata[i]!=10 && operate[i]!='u')
         {    
                   int k=1;
                   while(operate[i-k]!='+' && operate[i-k]!='-' && i-k!=-1 && input[i-k]!='(')
                   {
                        operate[i-k]='u';
                        floatdata[i-k]=0.;
                        k++;
                   }
                   int l=1;
                   while(operate[i+l]!='+' && operate[i+l]!='-' && i+l!=size && input[i+l]!=')')
                   {
                        operate[i+l]='u';
                        floatdata[i+l]=0.;
                        l++;
                   }
                   if((operate[i-k]=='+' || operate[i-k]=='-' || i-k==-1 || input[i-k]=='(') &&
                      (operate[i+l]=='+' || operate[i+l]=='-' || i+l==size|| input[i+l]==')'))
                       if(i-k!=-1 || i+l!=size)
                       {   
                              operate[i]='u';
                              if((i+l)==size || (input[i-k]!='(' && input[i+l]==')')) 
                                   operate[i-k]='u';
                               else if((i-k==-1 || (input[i-k]=='(' && input[i+l]!=')')) && input[i+l]!='-') 
                                    operate[i+l]='u';
                       }                            
         }        
      if(operate[i]=='+' || operate[i]=='-')
      {            
         if(intdata[i-1]==10 || intdata[i+1]==10)
            continue;
         int m=pos_pre_float(i-1);
         int n=pos_post_char(i); 
         if(operate[n]!='+' && operate[n]!='-' && input[n]!=')' && input[n]!='\0')
            continue;
         if(operate[i]=='+')
         {
            if(operate[m-1]=='-')
               floatdata[m]=floatdata[i+1]-floatdata[m];
            else if(operate[m]=='+' || input[m-1]=='('|| m==0)
               floatdata[m]+=floatdata[i+1];
            else
               continue;
         }
         if( operate[i]=='-')
         {
            if(operate[m-1]=='-')
              floatdata[m]+=floatdata[i+1];
            else if(operate[m-1]=='+' || input[m-1]=='(' || m==0)
              floatdata[m]-=floatdata[i+1];
            else 
              continue;
         }
         floatdata[i+1]=0;
         operate[i]='u'; 
         operate[i+1]='u'; 
      }
   }
   calc_pow();
}
//identifies term inside the brace ( )
int mani_string::term_in_braces(char expr[],char term1[],int & beginning, int & ending)
{
    int first=0,i=0,l=0; // first gives recording of first term is encountered 
    bool start=0;
    int braces=0,tbraces=0;
    int n=strlen(expr);
    beginning=0;
    ending=n-1;
    term1[0]='\0';
    while(first!=2 && i<n)
    {
       if(expr[i]=='(')
       {
          braces++;              //gives number of '(' - number of ')' if the term
          tbraces++;
          if(braces==1 && first==0)
             { start=1; first=1; beginning=i; }
       }
       else if(expr[i]==')')
          braces--;
       if(braces<0)
          throw error1(); 
       if(braces>0 && start==0)
          {  term1[l++]=expr[i]; term1[l]='\0'; }
       start=0; 
       if(first==1 && braces==0)
          {  first=2;  ending=i; }
       i++;
    }
    if(i==n && braces>0)
        throw error2();
    return tbraces;
}
//inserts a string over the given within given range
void mani_string::insert(char to_put[],int start,int finish)
{
     int j=0;
     int i=start;
     strcpy(argu_ment,input);
     for(int z=0; z<strlen(to_put);z++)
        if(invert_sign==1 && to_put[z]=='+')
            to_put[z]='-';
           else if(invert_sign==1 && to_put[z]=='-')
     if(intdata[start-1]!=10 )
               input[i++]='*';
     while(j<strlen(to_put))
     {
        if(j==strlen(to_put)-1)
        {
           if(to_put[j]=='+')
              { j++; continue; }
           else if(to_put[j]=='-')
              if(argu_ment[finish+1]=='-')
                 { j++; argu_ment[finish+1]='+'; continue; }
              else if(argu_ment[finish+1]=='+')
                 { j++; argu_ment[finish+1]='-'; continue; }
        }
        input[i++]=to_put[j++];
        input[i]='\0';
     }   
     if(argu_ment[finish+1]!='-' && argu_ment[finish+1]!='+' && argu_ment[finish+1]!='*' 
        && argu_ment[finish+1]!= '/' && argu_ment[finish+1]!='^' && argu_ment[finish+1]!=')' 
        && argu_ment[finish+1]!='\0')
           input[i++]='*';
     for(j=finish+1; j<strlen(argu_ment);j++)
           input[i++]=argu_ment[j];
     input[i++]='\0';
}
//removes braces if possible
bool mani_string::remove_braces()
{
       char term_in_b[50];
       char ch[50];
       bool to_cntd,is_removed=0;
       invert_sign=0; 
       int c;
       do{
           to_cntd=0; 
           bool if_num=1,if_operator=0;
           strcpy(ch,input);
           int a=0,a1,b=0,b1;  
           do{  
               try
               { 
                    c=term_in_braces(ch,term_in_b,a1,b1);
                    strcpy(ch,term_in_b);
                    if(c==1)
                         { a+=a1; b+=b1; }
                    else
                         {a+=a1+1; b=a; }
               }
               catch(error1)
               {
                    error_box(); 
                    setbkcolor(CYAN);
                    outtextxy(75,40,"UNBALANCED BRACES");
                    outtextxy(75,70," more ')' than '('"); 
                    show_error();
               }
               catch(error2)
               {
                    error_box();
                    setbkcolor(CYAN); 
                    outtextxy(75,40,"UNBALANCED BRACES");
                    outtextxy(75,70,"more '(' than ')'");
                    show_error();
               }
           }while(c>1);  
           if(input[a-1]=='+'|| input[a-1]=='-' || a==0 || input[a-1]=='(')
                if(input[b+1]=='+' || input[b+1]=='-' || input[b+1]=='\0' || input[b+1]==')')
                {    
                     if(a==0 && input[b+1]=='\0')
                       if(for_globals::Last_of_answer!='p')
                            break;                         
                     to_cntd=1;  
                     if(input[a-1]=='-') 
                     { 
                          invert_sign=1 ; 
                          if(ch[0]=='+' || ch[0]=='-') 
                             input[a-1]='+'; 
                     }
                     else invert_sign=0;
                }
           if(strlen(ch)==0 && a==1 && b==1)
                break;   
           for(int i=0; i<strlen(ch); i++)
           {
                if((ch[i]<48 || ch[i]>57) && ch[i]!='.')
                  if_num=0;
                if(ch[i]=='+' || ch[i]=='-')
                     if_operator=1;    
           }  
           if(if_num==1 || b-a==2 ||b-a==1)
                to_cntd=1;
           else
                 if((if_operator==0) && (input[a-1]=='x' || (input[a-1]>47 && input[a-1]<58)
                    || input[a-1]=='+' || input[a-1]=='-' || input[a-1]=='*' || a==0))
                    if(input[b+1]!='^' && input[b+1]!='/')
                         to_cntd=1;
           if(to_cntd==1)
                { 
                is_removed=1;
                insert(ch,a,b);separate_int_char();
                separate_float_char(); make_string(); 
                mult_signs();
                }
       }while(to_cntd==1); 
                 
       for(int z=0;z<strlen(input);z++)
        {  
             separate_int_char();
             separate_float_char();
             if(intdata[z]!=10 && operate[z]!='u')
               if(input[z-1]=='(')
               {
                   c=0;
                   while(intdata[z+c]!=10 && operate[z+c]!='u')
                       {ch[c++]=input[z+c]; ch[c]='\0'; }
                   if(input[z+c]==')')
                        {is_removed=1; insert(ch,z-1,z+c); mult_signs(); continue;}
               } 
             if(input[z]=='(' && input[z+1]==')')
                  {is_removed=1; floatdata[z]=0; operate[z+1]='u'; make_string(); continue;} 
             if((input[z]=='(' && operate[z]!='u') && input[z+1]!=')' &&
              (input[z+2]==')' && operate[z+2]!='u'))
                 {is_removed=1; operate[z]='u'; operate[z+2]='u';  make_string(); }
            
        } 
        return is_removed;                            
}
//main function to handle simplification
void mani_string::simplifying(char ch[])
{
     bool again;
     do
      {          
             next_simp=0;
             again=0;
             separate_int_char();  
             separate_float_char();
             try
                  {  simplify_floats(); }
             catch(error1)
             {
                  error_box();
                  outtextxy(75,40,"Division by zero!");
                  outtextxy(75,70," MATHEMATICAL ERROR!!!");
                  show_error(); 
             }
             catch(error2)
             {
                  error_box();
                  outtextxy(75,40,"Indeterminate form  0^0 !"); 
                  outtextxy(75,70," MATHEMATICAL ERROR!!!"); 
                  show_error(); 
             } 
              make_string();       
              again=remove_braces();       
      }while (next_simp==1 || again==1); 
      char term1[1000],term2[1000];
      char sign1=' ';   
      int brace=0,i=0;
      while(sign1==' ' &&  i<strlen(input))
      {
           if(input[i]=='(')
               brace++;
           else if(input[i]==')')
               brace--; 
           term1[i++]=input[i];
           term1[i]='\0';
           if(brace==0 && (input[i]=='+' || input[i]=='-'))
                   sign1=input[i++];
      }
     char ch11[2];
     ch11[0]=sign1;
     ch11[1]='\0';
      int j=0;
      while(i<strlen(input))
      {
           term2[j++]=input[i++];
      } 
      term2[j]='\0';
     if(strlen(term2)!=0)
     {
              remove_outermost_brace(term1);
              strcpy(input,term1);
              simplifying(ch);
              strcat(ch,ch11);
              strcpy(input,term2);
              simplifying(ch);
              
     }
     else
           strcat(ch,term1);
}
//a function to simplify the terms
void mani_string::simplification(char in_put[])
{ 
   for(int i=0; i<5;i++)
   {  
     strcpy(input,in_put);
     char ans_wer[1000];
     strcpy(ans_wer,"\0");
     simplifying(ans_wer);
     strcpy(in_put,ans_wer);
  }
}

int mani_string::read_expression()

{   
     return read_question(input,"SIMPLIFICATION","Expression=");
}

void mani_string::simplify()
{
     simplification(input);
}

void mani_string::show_result()
{
     display_ans(input);
}
     
void mani_string::rep_x(char ch[], float val)
{
    strcpy(input,ch);
    separate_int_char();
    separate_float_char();
    int i=0;
    while(input[i]!='\0')
    {
        if(input[i]=='x' || input[i]=='X')
            floatdata[i]=val;
        i++;
    }
    simplify_floats();
    make_string();
    strcpy(ch,input);
}     

     
     
     
     
