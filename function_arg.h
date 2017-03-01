#ifndef FUNCTION_ARG_H_
#define FUNCTION_ARG_H_
class function_arg           
{  
   private:     
        char twochar[3],threechar[4];
        char fourchar[5],fivechar[6];
        char sixchar[7],sevenchar[8];
        bool constant;
        int m,n,flag;
   public:
       char function_type(char term_in[]);   
       void part_base_pow(char param[],char base[],char power[]);
       void part_arg(char param[],char compare[],char argu[]);
};
#endif
