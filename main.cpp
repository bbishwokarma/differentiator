#include <graphics.h>
#include "interface.h"
#include "function_arg.h"
#include "simplification.h"
#include "derivative.h"

int main()
{
    initwindow(1024,700,"Differentiator project");
    well_come();
    clearmouseclick(WM_LBUTTONUP);
    Derivative expr1;
    mani_string expr2;
    while(1)
    {
          clearmouseclick(WM_LBUTTONUP);
          int choice1= main_menu();
          int choice2;
          switch(choice1)
          {
             case 1:                      //calculation of derivative       
                  if(expr1.read_expression()==1)
                  {
                    do{
                         expr1.differentiate();
                         choice2=expr1.display();
                         if(choice2==1)
                              expr1.diff_further();
                    }while(choice2==1);
                    if(choice2==2)
                          expr1.der_at_point();
               }
               break;
          case 2:                         //numeric simplification
               if(expr2.read_expression()==1)
               {
                     expr2.simplify();
                     expr2.show_result();
               }
               break;
          case 3:                         //help
               help_user();
               break;
          case 4:                           //exit the program
               exit_program(); 
       }  
   }
closegraph();
system("pause");
return 0;
}
               
   
