#ifndef INTERFACE_H_
#define INTERFACE_H_
class for_globals
{
   private:
      for_globals(); //so that no one can create an object from it
   public:
       static char Last_of_answer;
       static int whichwindow;
};
void saybye();
void show_error();
void error_box();
void well_come();
int main_menu();
int read_question(char ch1[],char name_of_operation[],char ch2[]); 
int show_derivative(char ques[],char ans[],char ch1[],char ch2[]);
void display_ans(char toshow[]);
void help_user();
int read_rep(char [],float &);
void give_der_at_point(char []);
void exit_program();
#endif
