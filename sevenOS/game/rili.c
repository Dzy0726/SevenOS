
//#include"stdlib.h"
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
//#include "proto.h"


PUBLIC void rili(int fd_stdin,int fd_stdout)
{
        char buf[10];
        char buf2[10];
	int year;
	int month;
	int FirstdayOfYear,FirstdayOfMonth;
	int LeapYear;//���꣬0��ʾ���ǣ�1��ʾ��
	int i,d,y;
	char YN;
	int Days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31} ;
	printf("-------calendar--------\n");
	
	printf("input the year[0000~9999]:");
	read(fd_stdin,buf,5);
	year=(buf[0]-48)*1000+(buf[1]-48)*100+(buf[2]-48)*10+(buf[3]-48);
	
	printf("input the month[01~12]:");
	read(fd_stdin,buf2,3);
	month=(buf2[0]-48)*10+(buf2[1]-48);
	
	y=year;
	FirstdayOfYear=5*(y/4)+(y%4)-(y/100)+(y/400);//һ��ĵ�һ�������
	//�ж����� 
	if(y%4==0&&y%100!=0||y%400==0)
	{
		LeapYear=1;
	}
	else LeapYear=0;
	//�����޸�2������ 
	if(LeapYear==1)
	{
		Days[2]=29;
	}
	else Days[2]=28;
	

    //for(month=1;month<13;month++)
   // {
	


	for(i=1,d=0;i<month;i++)
	{
		d=d+Days[i];
		
	}
	FirstdayOfMonth=(d+FirstdayOfYear)%7;//ÿ�µ�һ������� 
	printf("\n-------------------------------------------------------\n");
	printf("              Ad %d year // %2d month",year,month);
	printf("\n-------------------------------------------------------\n");
	printf("    Sun    Mon    Tue    Wed    Thu    Fri    Sat\n");
	if(FirstdayOfMonth!=0)
	{

	for(i=1;i<FirstdayOfMonth;i++)//ÿ��1��֮ǰû�еĴ�ӡ�ո� 
	{
		printf("%7c",' ');
	}
	
	}
	else 
	{
		for(i=0;i<6;i++)
		printf("%7c",' ');
	}
	
	for(d=1;d<=Days[month];d++)//ÿһ�ܴ�ӡ�껻�� 
	{
		printf("%7d",d);
		if( ( (d+FirstdayOfMonth-1)%7 )==0 && d<Days[month] )
		{
			printf("\n");
		}
	}
	printf("\n-------------------------------------------------------\n");
	

printf("the year/month is ");
	printf("%d / %d        \n",year,month);
	
	
	
	
	
	
}
