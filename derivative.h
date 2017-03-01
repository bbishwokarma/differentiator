#ifndef DERIVATIVE_H_
#define DERIVATIVE_H_
#include "function_arg.h"
#include "simplification.h"
class Derivative
{
    private:
       function_arg func;   //func is object of function_arg
       mani_string simple;  //simple is object of mani_string 
       char sign[3],ch1;
       char answer[1000];
       char term1[1000],term2[1000];
       char in_expression[1000]; 
       int order_n,size,beginning,ending,is_done;
       void Nth_order();
       void if_constant(char  param[]);                  //a
       void if_linear(char param[]);                     //b  
       void if_x_pow_cons(char param[]);                 //c
       void if_cons_pow_x(char param[]);                 //d
       void if_x_pow_x( char param[]);                   //e
       void if_ln(char param[]);                         //f
       void if_log(char param[]);                        //g
       void if_sin(char param[]);                        //h
       void if_cos(char param[]);                        //i
       void if_tan(char param[]);                        //j 
       void if_cosec(char param[]);                      //k
       void if_sec(char param[]);                        //l
       void if_cot(char param[]);                        //m
       void if_asin(char param[]);                       //n
       void if_acos(char param[]);                       //o
       void if_atan(char param[]);                       //p
       void if_acosec(char param[]);                     //q
       void if_asec(char param[]);                       //r 
       void if_acot(char param[]);                       //s
       void if_sinh(char param[]);                       //t
       void if_cosh(char param[]);                       //u
       void if_tanh(char param[]);                       //v
       void if_cosech(char param[]);                     //w
       void if_sech(char param[]);                       //x
       void if_coth(char param[]);                       //y
       void if_asinh(char param[]);                      //A
       void if_acosh(char param[]);                      //B
       void if_atanh(char param[]);                      //C
       void if_acosech(char param[]);                    //D
       void if_asech(char param[]);                      //E
       void if_acoth(char param[]);                      //F
       void term_with_sign(char param[]);
       int with_multiplying(char param[]);
       void call_formulae(char small_term[]); 
       void operator_wise();                  // has formula of form u+v,u*v,u/v,u-v
       void start_with_braces(char expr[]);   //expressions starting with '('   
    public:
       Derivative();
       int read_expression();
       void initialize();
       void differentiate();
       void calc_derivative(char ques[]);
       int display();
       void diff_further();
       void der_at_point();
};
#endif
