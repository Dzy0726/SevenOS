
#include <stdio.h>
#include <time.h>  
#include <sys/time.h>  
#include <signal.h>  
      
static int time_count = 0;  
static struct itimerval oldtv;  
 
void set_timer()  
{  
    struct itimerval itv;  
    itv.it_interval.tv_sec = 1;  //设置为1秒 
    itv.it_interval.tv_usec = 0;  
    itv.it_value.tv_sec = 1;  
    itv.it_value.tv_usec = 0;  
    setitimer(ITIMER_REAL, &itv, &oldtv);  //Linux--api 
}  
 
void signal_handler(int m)  
{  
    time_count ++;  
    printf("%d\n", time_count);  
}  
 
int main()  
{  
    printf("|*********                      *********| \n");
    printf("|*********                      *********| \n");
    printf("|*********                      *********| \n");
    printf("|*********                      *********| \n");
    printf("|********* Welcome to Seven OS! *********| \n");
    printf("|*********                      *********| \n");
    printf("|*********                      *********| \n");
    printf("|*********                      *********| \n");
    printf("|*********    **************    *********| \n");
    printf("|*********    **************    *********| \n");
    printf("|*********    ***       ****    *********| \n");
    printf("|*********             ****     *********| \n");
    printf("|*********            ****      *********| \n");
    printf("|*********           ****       *********| \n");
    printf("|*********          ****        *********| \n");
    printf("|*********         ****         *********| \n");
    printf("|*********        ****          *********| \n");
    printf("|*********       ****           *********| \n");
    printf("|*********                      *********| \n");
    printf("|*********                      *********| \n");
    printf("|*********                      *********| \n");
    printf("|*********                      *********| \n");
    printf("|*********Welcome to time watch!*********| \n");
    printf("|*********                      *********| \n");
	
    signal(SIGALRM, signal_handler);  
    set_timer();  //启动定时器 
    while(1)
	{
        if(time_count==10)
        {
            printf("Count 10 seconds.\n");
            time_count=0;
        }
    }
    return 1;  
}
