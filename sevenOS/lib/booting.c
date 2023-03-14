/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            booting.c
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

#define DELAY_TIME 6000



/*****************************************************************************
 *                                开机动画
 *****************************************************************************/
void bootAnimation()
{
  emptyWindow();
  starting();
  emptyWindow();
  booting();
  Loading();
}

void emptyWindow()
{
  printf("      ====================================================================\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      ====================================================================\n");

  milli_delay(DELAY_TIME);
  clear();
}
void starting()
{
  printf("      ====================================================================\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                    ***************************                   #\n");
  printf("      #                    ***************************                   #\n");
  printf("      #                    ***************************                   #\n");
  printf("      #                                        *******                   #\n");
  printf("      #                                       *******                    #\n");
  printf("      #                                      *******                     #\n");
  printf("      #                                     *******                      #\n");
  printf("      #                                    *******                       #\n");
  printf("      #                                   *******                        #\n");
  printf("      #                                  *******                         #\n");
  printf("      #                                 *******                          #\n");
  printf("      #                                *******                           #\n");
  printf("      #                               *******                            #\n");
  printf("      #                              *******                             #\n");
  printf("      #                             *******                              #\n");
  printf("      #                            *******                               #\n");
  printf("      #                           *******                                #\n");
  printf("      #                          *******                                 #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      ====================================================================\n");

  milli_delay(DELAY_TIME);
  clear();

  printf("      ====================================================================\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                    ***       *****    **   **                    #\n");
  printf("      #                    *   ***    **         * *                     #\n");
  printf("      #                    **  **              *******                   #\n");
  printf("      #                                        *  ** *                   #\n");
  printf("      #                                         ** **                    #\n");
  printf("      #                                      **  **                      #\n");
  printf("      #                                        ****                      #\n");
  printf("      #                                    *  * **                       #\n");
  printf("      #                                   ****                           #\n");
  printf("      #                                  * **  *                         #\n");
  printf("      #                                 *   ***                          #\n");
  printf("      #                                ** *  *                           #\n");
  printf("      #                                  ****                            #\n");
  printf("      #                              **   **                             #\n");
  printf("      #                             ** *  *                              #\n");
  printf("      #                            * ***                                 #\n");
  printf("      #                           **  * *                                #\n");
  printf("      #                          * * * *                                 #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      ====================================================================\n");

  milli_delay(DELAY_TIME);
  clear();

  printf("      ====================================================================\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                    *         *   *    **   **                    #\n");
  printf("      #                    *   * *    **         * *                     #\n");
  printf("      #                        *               *   * *                   #\n");
  printf("      #                                        *  *  *                   #\n");
  printf("      #                                         *  *                     #\n");
  printf("      #                                          *                       #\n");
  printf("      #                                        *                         #\n");
  printf("      #                                    *  *                          #\n");
  printf("      #                                     *                            #\n");
  printf("      #                                  * *   *                         #\n");
  printf("      #                                 *   *                            #\n");
  printf("      #                                   *  *                           #\n");
  printf("      #                                  **                              #\n");
  printf("      #                               *   **                             #\n");
  printf("      #                                *  *                              #\n");
  printf("      #                            * *                                   #\n");
  printf("      #                               * *                                #\n");
  printf("      #                          * * * *                                 #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      ====================================================================\n");

  milli_delay(DELAY_TIME);
  clear();
}

void booting()
{
  printf("      ====================================================================\n");
  printf("      #                                                                  #\n");
  printf("      #                          *            ** *                       #\n");
  printf("      #                                * *      *                        #\n");
  printf("      #                           *         *                            #\n");
  printf("      #                                       *                          #\n");
  printf("      #                                   *                              #\n");
  printf("      #                                     *                            #\n");
  printf("      #                                  * *                             #\n");
  printf("      #                                *                                 #\n");
  printf("      #                               *  *                               #\n");
  printf("      #                                 *                                #\n");
  printf("      #                             *                                    #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      ====================================================================\n");

  milli_delay(DELAY_TIME);
  clear();

  printf("      ====================================================================\n");
  printf("      #                                                                  #\n");
  printf("      #                         *   ****      ** *                       #\n");
  printf("      #                          *     * *    ***                        #\n");
  printf("      #                         * *         *                            #\n");
  printf("      #                                       *                          #\n");
  printf("      #                                   * *                            #\n");
  printf("      #                                   * *                            #\n");
  printf("      #                                  * *                             #\n");
  printf("      #                                * *                               #\n");
  printf("      #                               *  *                               #\n");
  printf("      #                               * *                                #\n");
  printf("      #                             ****                                 #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      ====================================================================\n");

  milli_delay(DELAY_TIME);
  clear();

  printf("      ====================================================================\n");
  printf("      #                                                                  #\n");
  printf("      #                         **  ****      ** *                       #\n");
  printf("      #                         **     * *    ***                        #\n");
  printf("      #                         ***         ***                          #\n");
  printf("      #                                    *  *                          #\n");
  printf("      #                                   * **                           #\n");
  printf("      #                                  ** *                            #\n");
  printf("      #                                 ** *                             #\n");
  printf("      #                                ** *                              #\n");
  printf("      #                               * **                               #\n");
  printf("      #                               ***                                #\n");
  printf("      #                             ****                                 #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      ====================================================================\n");

  milli_delay(DELAY_TIME);
  clear();

  printf("      ====================================================================\n");
  printf("      #                                                                  #\n");
  printf("      #                         ******************                       #\n");
  printf("      #                         *****************                        #\n");
  printf("      #                         ***         ****                         #\n");
  printf("      #                                    ****                          #\n");
  printf("      #                                   ****                           #\n");
  printf("      #                                  ****                            #\n");
  printf("      #                                 ****                             #\n");
  printf("      #                                ****                              #\n");
  printf("      #                               ****                               #\n");
  printf("      #                              ****                                #\n");
  printf("      #                             ****                                 #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #      ########    ########   ##    ##   ########   ###   ##       #\n");
  printf("      #      ##          ##         ##    ##   ##         ####  ##       #\n");
  printf("      #      ########    ########    ##  ##    ########   ## ## ##       #\n");
  printf("      #            ##    ##           ####     ##         ##   ###       #\n");
  printf("      #      ########    ########      ##      ########   ##    ##       #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      #                                                                  #\n");
  printf("      ====================================================================\n");
  milli_delay(18000);
}

void Loading() {
  printf("seven Operate System is loading,waiting...");

  for (int i = 0; i < 25; ++i)
  {
    milli_delay(DELAY_TIME / 5);
    printf(".");
  }
}