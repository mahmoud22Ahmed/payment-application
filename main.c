#include <stdio.h>
#include <stdlib.h>
#include  "application/app.h"
int main()
{
   /* to start the app you must type in terminal :
   gcc main.c application/app.c card/card.c terminal/terminal.c server/server.c -o main 
   and press enter and then type ./main*/
    appstart();
    printf("------Exit the programm\n");
    return 0;
}