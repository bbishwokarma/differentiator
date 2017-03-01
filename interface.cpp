#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include "interface.h" 

char for_globals::Last_of_answer='p';
void show_error()
{
     int x1,y1;
     outtextxy(80,90,"sorry!!");
     outtextxy(80,110,"Error encountered!!!");
     outtextxy(80,130,"click on ok to terminate");
     while(1)
     {   
        setcolor(RED);
        rectangle(400,150,490,190);
        x1=mousex();
        y1=mousey();
        if(x1>400 && x1<490 && y1>150 && y1<190)
             {setfillstyle(1,BLUE); setbkcolor(BLUE);}
        else {setfillstyle(1,GREEN); setbkcolor(GREEN);}
        floodfill(402,160,RED);
        setcolor(WHITE);
        outtextxy(430,160,"ok");
        getmouseclick(WM_LBUTTONUP,x1,y1);
        if(x1>400 && x1<490 && y1>150 && y1<190)
             {
               closegraph();
               initwindow(1024,700,"Differentiator project");
               exit_program(); 
             }
        delay(200);
     }
}
void error_box()
{
     initwindow(500,200,"Error found: Differentiator project",250,200);
     setfillstyle(1,CYAN);
     bar(0,0,500,200);
     int coard[]={40,10,55,50,25,50,40,10};
     setcolor(RED);
     setfillstyle(1,RED);
     fillpoly(3,coard);
     setbkcolor(RED);
     setcolor(WHITE);
     outtextxy(38,30,"!");
}

void well_come()
{
     setfillstyle(3,MAGENTA);
     bar(0,0,1024,768);
     settextstyle(1,HORIZ_DIR,26);
     outtextxy(190,270,"WELCOME TO THE PROGRAM");
     settextstyle(1,HORIZ_DIR,24);
     outtextxy(250,310,"CLICK ON THE SCREEN ANYWHERE TO BEGIN");
     outtextxy(750,600,"Prepared by:");
     outtextxy(750,620,"Bikash B.K ");
     outtextxy(750,640,"Bidur B.K   ");
     outtextxy(750,660,"Pratik Shankar Hada");  
     delay(1000);
     while(!ismouseclick(WM_LBUTTONUP) && !kbhit());
}
int  main_menu()
{
       setbkcolor(BLACK);
       cleardevice();
       setfillstyle(9,RED);
       bar(0,0,1024,768);
       setfillstyle(1,BLACK);
       bar(0,575,1024,600);
       setcolor(WHITE);
       settextstyle(8,0,1);
       setbkcolor(BLACK);
       outtextxy(650,580," Click on a button and proceed ");
       setfillstyle(1,GREEN);
       setbkcolor(GREEN);
       setcolor(BLUE);
       bar3d(380,70,620,110,10,15);
       settextstyle(9,0,3);
       setcolor(RED);
       outtextxy(400,80,"MAIN MENU");
       setfillstyle(1,3);
       setbkcolor(3);
       for(int z=0; z<4 ;z++)
            bar(200*z+90,90*z+150,200*z+340,90*z+200);
       settextstyle(4,HORIZ_DIR,33);
       setcolor(WHITE);
       outtextxy(115,165,"DIFFERENTIATION");
       outtextxy(330,255,"SIMPLIFICATION");
       outtextxy(560,345,"HELP");
       outtextxy(765,435,"EXIT");
       setfillstyle(1,RED);
       bar(0,113,1024,147);
       setcolor(BLACK);
       line(0,117,1024,117);
       line(0,143,1024,143);
       static int loop=-200;
       while(1)
       {
            delay(50);
            setfillstyle(1,RED);
            bar(loop,119,loop+4,141);
            setcolor(WHITE);
            loop+=2;
            if(loop>=1000)
               loop=-200;
            setbkcolor(RED);
            outtextxy(loop+2,120,"d i f f e r e n t i a t o r  - 1");
            int x,y;
            x=mousex();
            y=mousey(); 
            setcolor(3);
            if(x>90 && x<340 && y>150 && y<200)
                    rectangle(90,150,340,200);
             else if(x>290 && x<540 && y>240 && y<290)
                    rectangle(290,240,540,290);
             else if(x>490 && x<740 && y>330 && y<380)
                    rectangle(490,330,740,380);
             else if(x>690 && x<940 && y>420 && y<470)
                    rectangle(690,420,940,470);
             else
             {
                    setcolor(BLACK); 
                    rectangle(90,150,340,200);
                    rectangle(290,240,540,290);
                    rectangle(490,330,740,380);
                    rectangle(690,420,940,470);
             }
             getmouseclick(WM_LBUTTONUP,x,y);
             if(x>90 && x<340 && y>150 && y<200)
                   return 1;
             else if(x>290 && x<540 && y>240 && y<290)
                   return 2;
             else if(x>490 && x<740 && y>330 && y<380)
                   return 3;
             else if(x>690 && x<940 && y>420 && y<470)
                   return 4;    
       }    
}  

int read_question(char ch1[],char name_of_operation[],char ch2[])
{
       cleardevice();
       setfillstyle(1,BLACK);
       bar(0,0,1024,768);
       setbkcolor(BLACK);
       outtextxy(100,120,name_of_operation);
       setcolor(3);
       settextstyle(8,HORIZ_DIR,1);      
       setbkcolor(BLACK);
       setcolor(YELLOW);
       outtextxy(100,200,"Enter the expression");
       outtextxy(125,230,ch2);
       outtextxy(250,230,"   ");
       char a[2];
       a[0]='\0';
       a[1]='\0';
       int i=0,j=0,k=0,x,y;
       setfillstyle(1,BLACK);
       do
       {  
           while(!kbhit())
           {
                          
                x=mousex();
                y=mousey();
                delay(50);
                setfillstyle(1,5); 
                setbkcolor(5);
                if(x>600&& x<750 && y>120 && y<170)
                {
                       bar(600,120,750,170);
                       outtextxy(620,135,"Proceed...");
                }
                else if(x>600 && x<750 && y>60&& y<110) 
                {
                       bar(600,60,750,110);  
                       outtextxy(620,75,"Reset Entry");
                }
                else if(x>600&&x<750&&y>500&&y<550)
                {
                       bar(600,500,750,550); 
                       outtextxy(650,520,"BACK");   
                }       
               else
               {
                    setfillstyle(1,BLUE); 
                    setbkcolor(BLUE);
                    bar(600,120,750,170);
                    bar(600,60,750,110);  
                    bar(600,500,750,550); 
                    outtextxy(620,135,"Proceed...");  
                    outtextxy(620,75,"Reset Entry");    
                    outtextxy(650,520,"BACK");                  
               }               
               getmouseclick(WM_LBUTTONUP,x,y);
               if(x>600 && y>40 && x<750 && y<110)
                         return read_question(ch1,name_of_operation,ch2);
               if(x>600 && y>120&& x<750 && y<170)
                        return  1;
               if(x>600&&x<750&&y>500&&y<550)
                        return 0;                      
            }
            a[0]=getch();
            if(a[0]==8 )
            {
                if(j!=0 && i==0)
                     {j-=20; i=649;} 
                else
                    if(j==0 && i==0)
                        continue;
                else i-=11;
               setfillstyle(1,BLACK);
                bar(270+i-10,230+j,270+i+2,250+j+5);
                ch1[k]='\0';
                k--;
           }
           else if(a[0]!='\r')
           {
                  ch1[k++]=a[0];
                  setbkcolor(BLACK);
                  outtextxy(270+i-9,230+j,a);
                  i+=11;
                  if(i>=660)
                     {j+=20; i=0;}
                  ch1[k]='\0';
           } 
      }while(a[0]!='\r');
      return 1;
}

int show_derivative(char ques[],char ans[],char ch1[],char ch2[])
{
       cleardevice();
       setfillstyle(1,BLACK);
       bar(0,0,1024,768);
       char a[2];
       a[1]='\0';
       int j=0,k=0;
       settextstyle(3,HORIZ_DIR,1);
       setbkcolor(BLACK);
       setcolor(YELLOW);
       outtextxy(50,50,"Previous: ");
       for(int i=0; i<strlen(ques); i++)
       {
          a[0]=ques[i];
          if(j>=770)
              {j=0; k+=20;}
          outtextxy(160+j,50+k,a);
          j+=11;
       }
       j=0;k+=20;
       outtextxy(100,100+k,ch1); k+=20;
       outtextxy(110,100+k,ch2);
       for(int i=0; i<strlen(ans); i++)
       {
          a[0]=ans[i];
          j+=11;
          if(j>=605)
              {j=0; k+=20; }
          outtextxy(110+11*strlen(ch2)+j,100+k,a);
       }
       setcolor(3);
       rectangle(50,440,300,490);
       rectangle(50,500,300,550);
       rectangle(50,560,300,610);
       settextstyle(8,HORIZ_DIR,1);
       while(1)
       {  
            int x=mousex();
            int y=mousey();
            setfillstyle(1,5); 
            setbkcolor(5);
            if(x>50 && y>440 && x<300 && y<490)
            {
                   floodfill(55,450,3);
                   outtextxy(55,450,"Next Order ");
            }
            else if(x>50 && y>500 && x<300 && y<550)
            {
                   setfillstyle(1,5); 
                   floodfill(55,510,3); 
                   outtextxy(55,510,"Derivative at point");
            }
            else if(x>50 && y>560 && x<300 && y<610)
            { 
                   setfillstyle(1,5); 
                   floodfill(55,570,3); 
                   outtextxy(55,570,"Main Menu");
            }
            else 
            {
                 setfillstyle(1,BLUE);
                 setbkcolor(BLUE);
                 floodfill(55,450,3); floodfill(55,510,3); floodfill(55,570,3);
                 outtextxy(55,450,"Next Order ");
                 outtextxy(55,510,"Derivative at point");
                 outtextxy(55,570,"Main Menu");
            }
            getmouseclick(WM_LBUTTONUP,x,y);
            if(x>50 && y>440 && x<300 && y<490)  return 1;
            if(x>50 && y>500 && x<300 && y<550)  return 2;
            if(x>50 && y>560 && x<300 && y<610)  return 0;
            delay(50);
       }
}

void display_ans(char toshow[])
{
     setbkcolor(BLACK);
     cleardevice();
     char a[2];
     a[1]='\0';
     setcolor(WHITE);
     setbkcolor(BLACK);
     outtextxy(50,50,"The simplified form is: ");
     int j=0,k=0;
     for(int i=0; i<strlen(toshow); i++)
       {
          a[0]=toshow[i];
          if(j>=660)
              {j=0; k+=20;}
          outtextxy(210+j,80+k,a);
          j+=11;
       }
     setcolor(3);
     rectangle(550,450,700,500);
     while(1)
     {
             int x,y;
             x=mousex();
             y=mousey();
             if(x>550&&x<700&&y>450&&y<500)
             {
                 setfillstyle(1,5);
                 floodfill(555,460,3);
                 setbkcolor(5);
                 outtextxy(570,465," Main menu");
             }
             else
             {
                     setfillstyle(1,BLUE);
                     floodfill( 555,460,3); 
                     setbkcolor(BLUE);
                     outtextxy(570,465," Main menu");
             }                        
             getmouseclick(WM_LBUTTONUP,x,y); 
             if(x>550 && y>450 && x<700 && y<500)  break;
             delay(50);
     }
}

void help_user()
{
     int x,y;    
     setfillstyle(1,LIGHTGREEN);
     bar(0,0,1024,768); 
     setfillstyle(1,BLACK);
     bar(160,10,1010,700);
     setcolor(WHITE);
     line(160,355,1010,355);
     settextstyle(1,HORIZ_DIR,20);
     setbkcolor(BLACK);
     outtextxy(300,20,"ABOUT THE DERIVATIVE");
     outtextxy(300,375,"ABOUT THE SIMPLIFICATION");
     settextstyle(1,HORIZ_DIR,100);
     outtextxy(165,60,"This program is about the derivate,the first order\
differential any kind of equation"); 
     outtextxy(165,80," as far as concerned.You can also get nth order differential\
as per your requirement."); 
     outtextxy(165,100,"INSTRUCTIONS");  
     outtextxy(170,120,"- To begin with the derivative,enter the expression and then either click");
     outtextxy(170,140,"  on the proceed button or just press\"Enter\" key to get the resul."); 
     outtextxy(170,160,"- To enter an expression some incentives should be followed.");
     outtextxy(170,180,"     1. Precedence should be maintained using braces.");
     outtextxy(170,200,"     2. Functions like sin,cos if contain large arguments like 2x,enter");
     outtextxy(170,220,"        as: sin(2x),(5x)^4,acosh(x^2) etc."); 
     outtextxy(170,240,"     3. use '^'symbol to represent power:   (sin(ax))^2,(acosecx)^5,etc.");
     outtextxy(170,260,"     4. To represent inverse of trigonometric & hyperbolic functions put"); 
     outtextxy(170,280,"        'a' at begening: atan(5x), acosecx, atanh(6x) etc.");
     outtextxy(170,300,"     5. Except in linear forms, term of x should be separated by *  from");
     outtextxy(170,320,"     6. coefficients and other tems:5*sinx,sinx*cosx (not,5sinx, sinxcosx"); 
     outtextxy(165,405,"-  Entering the expression an other and action to get the result is same as ");
     outtextxy(165,425,"    above case.");
     outtextxy(165,445,"-  Simplifies only numerical values so other characeter will be revealed as it is in ");
     outtextxy(165,465,"   the result.");
     outtextxy(165,485,"-  Will not give the value of expression log10,sin30,etc if entered single.");
     
     settextstyle(1,HORIZ_DIR,20);      
     while(1)
     {
           x=mousex();
           y=mousey();
           if(x>=10 && y>=150 && x<=145 && y<=225)
           {  
                setfillstyle(1,4);
                bar(10,150,145,225);
                setbkcolor(4);
                outtextxy(20,175,"BACK");  
           }
           else
           {
               setfillstyle(1,1);
               bar(10,150,145,225);
               setbkcolor(1);
               outtextxy(20,175,"BACK");  
           }
           getmouseclick(WM_LBUTTONUP,x,y);
           if(x>=10 && y>=150 && x<=145 && y<=225)
              break;
           delay(50);
     }                
}  
            
int read_rep(char ch[],float & n)
{
       setfillstyle(1,CYAN);
       bar(75,0,900,500);
       setfillstyle(1,RED);
       setbkcolor(RED);
       settextstyle(8,HORIZ_DIR,1);
       bar(600,120,750,170);
       outtextxy(620,135,"proceed...");
       bar(600,180,750,230);
       outtextxy(620,195,"main menu");
       setbkcolor(CYAN);
       setcolor(WHITE);
       outtextxy(100,60,"the derivative at x is:");
       outtextxy(100,80,ch);
       outtextxy(150,100,"only positive integer");
       outtextxy(150,120,"Enter point x= ");
       char ch1[20];
       char a[2];
       a[1]='\0';
       int i=0,j=0,k=0;
       int x,y,is_click=0;  
       while(1)
       {
               while(!kbhit())
               {          
                   x=mousex();
                   y=mousey();
                   if(x>600 && x<750 && y>120 && y<170)
                    { 
                       setcolor(GREEN); 
                       rectangle(600,120,750,170);
                    }
                    else if(x>600 && x<750 && y>180&& y<230)
                    { 
                        setcolor(GREEN); 
                        rectangle(600,180,750,230);
                    }
                    else
                    {
                         setcolor(RED); 
                         rectangle(600,120,750,170); 
                         rectangle(600,180,750,230);                 
                    }
                    getmouseclick(WM_LBUTTONUP,x,y);
                    if(x>600 && y>120 && x<750 && y<170)
                        {is_click=1; break;}
                    if(x>600 && y>180 && x<750 && y<230)
                         return 0;
               }  
               setcolor(WHITE);   
               if(is_click==1)
                    break;
               a[0]=getch();
               if(a[0]=='\r' || a[0]=='\n')
                    break;
               if(a[0]==8 )
               {
                      if(j!=0 && i==0)
                           {j-=20; i=649;} 
                      else if(j==0 && i==0)
                            continue;
                      else i-=11;
                      setfillstyle(1,CYAN);
                      bar(340+i-10,115+j,340+i+2,145+j+5);
                      ch1[k]='\0';
                      k--;
               }
               else if(a[0]<48 || a[0]>57)
               {
                      outtextxy(340,150,"Error in input!");
                      delay(1000);
                      return 0;
               }
               else
               {
                      ch1[k++]=a[0];
                      outtextxy(340+i-9,120+j,a);
                      i+=11;
                      if(i>=660)
                          {j+=20; i=0;}
                      ch1[k]='\0';
               }
       }
       setcolor(WHITE);
       if(strlen(ch1)==0)
           return read_rep(ch,n);
       n=0;
       for(i=0; i<strlen(ch1); i++)
           n=n*10+int(ch1[i])-48;
       if(n<1)
       {
              outtextxy(340,150,"0 or negative value!");
              delay(1000);
              return 0;
       }
       return 1;
} 
     
void give_der_at_point(char ch[])
{
     setfillstyle(1,BLACK);
     bar(150,300,850,450);
     settextstyle(8,HORIZ_DIR,1);
     setbkcolor(BLACK);
     outtextxy(200,350,"The derivative at the point=");
     outtextxy(200,370,ch);
     setfillstyle(1,RED);
     bar(350,400,500,430);
     setbkcolor(RED);
     outtextxy(355,410,"main menu");
     int x,y;
     while(!kbhit())
       {   
            x=mousex();
            y=mousey();
            if(x>350 && y>400 && x<500 && y<430)
                setcolor(GREEN); 
            else 
                setcolor(RED); 
            rectangle(350,400,500,430);           
           getmouseclick(WM_LBUTTONUP,x,y);
           if(x>350 && y>400 && x<500 && y<430)
           {
           setfillstyle(1,RED);
                 return ;    
       }
       }
};     
     
void exit_program()
{
     cleardevice();
     setfillstyle(1,BLACK);
     bar(0,0,1024,768);
     bar(100,0,700,450);
     setbkcolor(BLACK);
     setcolor(LIGHTGREEN);
     settextstyle(1,0,100);
     outtextxy(150,100,"A Project by...");
     outtextxy(200,140,"Bidur B.K.(063BCT504)");
     outtextxy(200,170,"Bikash B.K.(063BCT505)");
     outtextxy(200,200,"Pratik S Hada(063BCT522)");
     outtextxy(200,230,"063 bct batch IOE,Pulchowk");
     outtextxy(200,260," July-2008");
     outtextxy(400,400,"Press any key or click mouse to end the program");
     clearmouseclick(WM_LBUTTONDOWN);
     fflush(stdin);
     while(!kbhit() && !ismouseclick(WM_LBUTTONDOWN));
     closegraph();
     exit(0);
}                 
                     
                
           
