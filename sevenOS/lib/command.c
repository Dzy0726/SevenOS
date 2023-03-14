/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            command.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Dong Zhenyu, 2020
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"

/*****************************************************************************
 *                                指令界面
 *****************************************************************************/
void commandList()
{
    printf("      ====================================================================\n");
    printf("      #    ******************                                            #\n");
    printf("      #    *****************               Welcome to  sevenOS           #\n");
    printf("      #    ***         ****                                              #\n");
    printf("      #               ****                    [COMMAND LIST]             #\n");
    printf("      #              ****           $ help --- show the command list     #\n");
    printf("      #             ****            $ clear --- clear the cmd            #\n");
    printf("      #            ****             $ more [command]                     #\n");
    printf("      #           ****                  --- know more about the command  #\n");
    printf("      #          ****               $ game [-option]                     #\n");
    printf("      #         ****                    --- play the built-in game       #\n");
    printf("      #        ****                 $ cal --- show the calendar          #\n");
    printf("      #                             $ math [-option] [expression]        #\n");
    printf("      #                                 --- calculate the value          #\n");
    printf("      #                             $ file --- file manager              #\n");
    printf("      #                             $ watch --- show the stop watch      #\n");
    printf("      #                                                                  #\n");
    printf("      #                                                                  #\n");
    printf("      #                        Powered by Group7                         #\n");
    printf("      #                       ALL RIGHT REVERSED                         #\n");
    printf("      ====================================================================\n");


    printf("\n\n");
}

/*没找到该指令窗口*/
void notFound()
{
    printf("      ====================================================================\n");
    printf("      #                                                                  #\n");
    printf("      #    ******************                                            #\n");
    printf("      #    *****************                                             #\n");
    printf("      #    ***         ****                                              #\n");
    printf("      #               ****                                               #\n");
    printf("      #              ****                                                #\n");
    printf("      #             ****                        Sorry                    #\n");
    printf("      #            ****                Your command is not found         #\n");
    printf("      #           ****                                                   #\n");
    printf("      #          ****                                                    #\n");
    printf("      #         ****                                                     #\n");
    printf("      #        ****                                                      #\n");
    printf("      #                                                                  #\n");
    printf("      #                                                                  #\n");
    printf("      #                                                                  #\n");
    printf("      #                                                                  #\n");
    printf("      #                 Input [help] for more information.               #\n");
    printf("      #                                                                  #\n");
    printf("      #                                                                  #\n");
    printf("      ====================================================================\n");
    printf("\n\n");
}

void moreMain(char* option)
{
    if (!strcmp(option, "NULL")) 
    {
        printf("Sorry, you should add an option.\n");
    }

    else if (!strcmp(option, "help")) 
    {
        clear();
        printf("      ====================================================================\n");
        printf("      #                                                                  #\n");
        printf("      #    ******************            Welcome to sevenOS              #\n");
        printf("      #    *****************                                             #\n");
        printf("      #    ***         ****                                              #\n");
        printf("      #               ****                <COMMAND --- help>             #\n");
        printf("      #              ****                                                #\n");
        printf("      #             ****                                                 #\n");
        printf("      #            ****               Show the command list again.       #\n");
        printf("      #           ****              And you can input these commands     #\n");
        printf("      #          ****                to interact with the sevenOS.       #\n");
        printf("      #         ****                                                     #\n");
        printf("      #        ****                                                      #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                        Powered by Group7                         #\n");
        printf("      #                       ALL RIGHT REVERSED                         #\n");
        printf("      ====================================================================\n");

    }
   
    else if (!strcmp(option, "clear")) 
    {
        clear();
        printf("      ====================================================================\n");
        printf("      #                                                                  #\n");
        printf("      #    ******************            Welcome to sevenOS              #\n");
        printf("      #    *****************                                             #\n");
        printf("      #    ***         ****                                              #\n");
        printf("      #               ****               <COMMAND --- clear>             #\n");
        printf("      #              ****                                                #\n");
        printf("      #             ****            Clear the whole command station.     #\n");
        printf("      #            ****               You can enjoy yourself in          #\n");
        printf("      #           ****               interacting with the sevenOS.       #\n");
        printf("      #          ****                                                    #\n");
        printf("      #         ****                                                     #\n");
        printf("      #        ****                                                      #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                        Powered by Group7                         #\n");
        printf("      #                       ALL RIGHT REVERSED                         #\n");
        printf("      ====================================================================\n");

    }
    else if (!strcmp(option, "game")) 
    {
        clear();
        printf("      ====================================================================\n");
        printf("      #                                                                  #\n");
        printf("      #    ******************             Welcome to sevenOS             #\n");
        printf("      #    *****************                                             #\n");
        printf("      #    ***         ****                                              #\n");
        printf("      #               ****                  <COMMAND --- game>           #\n");
        printf("      #              ****                  by adding [-option].          #\n");
        printf("      #             ****                                                 #\n");
        printf("      #            ****           [OPTION LIST]                          #\n");
        printf("      #           ****               -box -> for PushBox game            #\n");
        printf("      #          ****                -saolei -> for Mine Sweeping game   #\n");
        printf("      #         ****                 -maze -> for Maze game              #\n");
        printf("      #        ****                  -sudoku -> for Sudoku game          #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                           [EXAMPLE]                              #\n");
        printf("      #                              game -box -> play PushBox game      #\n");
        printf("      #                                                                  #\n");
        printf("      #                        Powered by Group7                         #\n");
        printf("      #                       ALL RIGHT REVERSED                         #\n");
        printf("      ====================================================================\n");

    }
    else if (!strcmp(option, "cal")) 
    {
        clear();
        printf("      ====================================================================\n");
        printf("      #                                                                  #\n");
        printf("      #    ******************            Welcome to sevenOS              #\n");
        printf("      #    *****************                                             #\n");
        printf("      #    ***         ****                                              #\n");
        printf("      #               ****                <COMMAND --- cal>              #\n");
        printf("      #              ****                                                #\n");
        printf("      #             ****                                                 #\n");
        printf("      #            ****                    Show the calendar             #\n");
        printf("      #           ****                   for a specified month           #\n");
        printf("      #          ****                     in a specified year            #\n");
        printf("      #         ****                                                     #\n");
        printf("      #        ****                                                      #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                                                                  #\n");
        printf("      #                        Powered by Group7                         #\n");
        printf("      #                       ALL RIGHT REVERSED                         #\n");
        printf("      ====================================================================\n");

    }
    else if (!strcmp(option, "math")) 
    {
        clear();
        printf("      ====================================================================\n");
        printf("      #                                                                  #\n");
        printf("      #    ******************             Welcome to sevenOS             #\n");
        printf("      #    *****************                                             #\n");
        printf("      #    ***         ****                                              #\n");
        printf("      #               ****                  <COMMAND --- math>           #\n");
        printf("      #              ****         Calculate the value of the expression  #\n");
        printf("      #             ****          and you can do more by adding options. #\n");
        printf("      #            ****             The operator we support: [+-*/()]    #\n");
        printf("      #           ****                                                   #\n");
        printf("      #          ****             [EXAMPLE]                              #\n");
        printf("      #         ****                 math -beauty 9 -  4   +3*7          #\n");
        printf("      #        ****                  math -rev 1 * ( 2 - 3 ) + 4 / 5     #\n");
        printf("      #                              math 1+2-(3*4)/5                    #\n");
        printf("      #         [OPTION LIST]                                            #\n");
        printf("      #             -beauty [exp] -> beautify the expression             #\n");
        printf("      #             -rev [exp] -> output the reverse polish notation     #\n");
        printf("      #             no option -> just calculate the value                #\n");
        printf("      #                                                                  #\n");
        printf("      #                        Powered by Group7                         #\n");
        printf("      #                       ALL RIGHT REVERSED                         #\n");
        printf("      ====================================================================\n");

    }
    else if (!strcmp(option, "file")) {
        clear();
        printf("      ====================================================================\n");
        printf("      #                                                                  #\n");
        printf("      #    ******************            Welcome to sevenOS              #\n");
        printf("      #    *****************                                             #\n");
        printf("      #    ***         ****                                              #\n");
        printf("      #               ****               <COMMAND --- file>              #\n");
        printf("      #              ****                                                #\n");
        printf("      #             ****            You can do file management           #\n");
        printf("      #            ****           at our File Management System.         #\n");
        printf("      #           ****                                                   #\n");
        printf("      #          ****             [COMMAND LIST]                         #\n");
        printf("      #         ****                                                     #\n");
        printf("      #        ****               create [filename] |   mkdir [dirname]  #\n");
        printf("      #                                  ls         |       help         #\n");
        printf("      #                             cd [dirname]    |       cd ..        #\n");
        printf("      #                             rm [filename]   |    rm  [dirname]   #\n");
        printf("      #                             read [filename] |   edit [filename]  #\n");
        printf("      #                                  save       |       quit         #\n");
        printf("      #                                                                  #\n");
        printf("      #                        Powered by Group7                         #\n");
        printf("      #                       ALL RIGHT REVERSED                         #\n");
        printf("      ====================================================================\n");

    }
    
    else 
    {
        printf("Sorry, there no such option for sevenOS.\n");
        printf("You can input [help] to know more.\n");
    }

    printf("\n");
}

void gameMain(char* option, int fd_stdin, int fd_stdout)
{
    if (!strcmp(option, "NULL")) 
    {
        printf("Sorry, you should add an option.\n");
    }
    else if (!strcmp(option, "-maze")) 
    {
        migong(fd_stdin, fd_stdout);
    }
    else if (!strcmp(option, "-box")) 
    {
        pushBox(fd_stdin, fd_stdout);
    }
    else if (!strcmp(option, "-saolei")) 
    {
        StartGame(fd_stdin, fd_stdout);
    }
    else 
    {
        printf("Sorry, there no such option for game.\n");
        printf("You can input [more game] to know more.\n");
    }

    printf("\n");
}