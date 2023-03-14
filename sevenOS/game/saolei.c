#define _CRT_SECURE_NO_WARNINGS
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
//#include "windows.h"
#include "time.h"


/*
	用 C 语言写一个简单的扫雷游戏
*/
// 1.写一个游戏菜单 Menu()
// 2.开始游戏
	// 1.初始化二维数组 Init_Interface()
	// 2.打印游戏界面 Print_Interface()
	// 3.玩家掀起指定位置 Play() --> 指定输入坐标（判断合法性）
		// 1.判断该位置是否是雷
		// 2.判断是否掀掉所有空地
		// 3.如果掀开的是空地，则判断该空地周围是否有雷
			// 1.如果周围有雷，则统计周围雷的个数
			// 2.如果周围没有雷，则掀开周围除了雷的所有空地，并且统计所掀开空地周围雷的个数
		// 4.更新地图
		// 5.继续 3 的循环

//定义全局变量：
//定义扫雷地图的长和宽
#define MAX_ROW 9
#define MAX_COL 9
//定义默认的雷数
#define DEFAULT_MINE 9
//定义两个二维数组，分别存放初始地图和雷阵
char show_map[MAX_ROW + 2][MAX_COL + 2];
char mine_map[MAX_ROW + 2][MAX_COL + 2];

char buf[10];
char buf2[10];
char buf3[10];
//写一个游戏菜单
//int Menu(int fd_stdin,int fd_stdout) {
	
	//return choice;
//}

//开始游戏
//初始化数组
void Init_Interface() 
{
	int row,col; 
	for (row = 0; row < MAX_ROW + 2; row++) {
		
		for (col = 0; col < MAX_COL + 2; col++) {
			show_map[row][col] = '*';
		}
	}

	for (row = 0; row < MAX_ROW + 2; row++) {
		for (col = 0; col < MAX_COL + 2; col++) {
			mine_map[row][col] = '0';
		}
	}
	
	//int mine_count = DEFAULT_MINE;
	//while (mine_count > 0) {
		//int row = rand() % MAX_ROW + 1;////////////////////////////
		//int col = rand() % MAX_COL + 1;///////////////////////////
		//if (mine_map[row][col] == '1') { //将雷设置为 1
			//此处已经有雷
			//continue;
		//}
		//mine_count--;
		//mine_map[row][col] = '1';
	//}
	mine_map[1][6] = '1';
	mine_map[3][1] = '1';
	mine_map[3][8] = '1';
	mine_map[4][9] = '1';
	mine_map[5][1] = '1';
	mine_map[5][3] = '1';
	mine_map[5][7] = '1';
	mine_map[7][6] = '1';
	mine_map[7][7] = '1';
}
//打印初始界面
void Print_Interface(char map[MAX_ROW + 2][MAX_COL + 2]) {
	printf("    ");
	int row,col;
	for (col = 1; col <= MAX_COL; col++) {
		printf("%d ", col);
	}
	printf("\n    ");
	for (col = 1; col <= MAX_COL; col++) {
		printf("--");
	}
	printf("\n");
	for (row = 1; row <= MAX_ROW ; row++) {
		printf("%02d |", row);
		for (col = 1; col <= MAX_COL; col++) {
			printf("%c ", map[row][col]);
		}
		printf("\n");
	}
}
//写一个统计周围雷数个数的函数
int Around_Mine_count(int row, int col) {
	return	(mine_map[row - 1][col - 1] - '0'
		+ mine_map[row - 1][col] - '0'
		+ mine_map[row - 1][col + 1] - '0'
		+ mine_map[row][col - 1] - '0'
		+ mine_map[row][col + 1] - '0'
		+ mine_map[row + 1][col - 1] - '0'
		+ mine_map[row + 1][col] - '0'
		+ mine_map[row + 1][col + 1] - '0');
}
//写一个判断该位置周围是否有雷的函数
int No_Mine(int row, int col) {
	if (Around_Mine_count(row, col) == 0) {
		return 1;
	}
	return 0;
}
//写一个掀开该位置周围空地的函数
void Open_Blank(int row, int col) {
	show_map[row - 1][col - 1] = '0' + Around_Mine_count(row - 1, col - 1);
	show_map[row - 1][col] = '0' + Around_Mine_count(row - 1, col);
	show_map[row - 1][col + 1] = '0' + Around_Mine_count(row - 1, col + 1);
	show_map[row][col - 1] = '0' + Around_Mine_count(row, col - 1);
	show_map[row][col + 1] = '0' + Around_Mine_count(row, col + 1);
	show_map[row + 1][col - 1] = '0' + Around_Mine_count(row + 1, col - 1);
	show_map[row + 1][col] = '0' + Around_Mine_count(row + 1, col);
	show_map[row + 1][col + 1] = '0' + Around_Mine_count(row + 1, col + 1);
}
//写一个判断游戏结束的函数
int Success_Sweep(char show_map[MAX_ROW + 2][MAX_COL + 2]) {
	int count = 0;
	int row,col;
	for (row = 1; row <= MAX_ROW; row++) {
		for (col = 1; col <= MAX_COL; col++) {
			if (show_map[row][col] == '*') {
				count++;
			}
		}
	}
	if (count == DEFAULT_MINE) {
		return 1;
	}
	return 0;
}
//开始游戏
PUBLIC void StartGame(int fd_stdin, int fd_stdout) 
{
    
        printf("=========\n");
	printf("1.start the game\n");
	printf("0.end the game\n");
	printf("=========\n");
	printf("please choose the chioce:");
	int choice = 0;
	while (1) {
	        
	        read(fd_stdin,buf,2);
	        choice=buf[0]-48;
		//scanf("%d", &choice);////////////////////////////////
		if (choice != 0 && choice != 1) {
			printf("wrong,please input again\n");
			continue;
		}
		break;
	}

//if (choice == 0) {
		//exit(0);/////////////////////////////////////////////////
//	}
	//srand((unsigned int)time(NULL));/////////////////////////////////
	Init_Interface();
	Print_Interface(show_map);

	while (1) {
		printf("Please enter the coordinates you want to open and press enter in the middle:");
		int row = 0;
		int col = 0;
		while (1) {
			//scanf("%d %d", &row, &col);/////////////////////////
			read(fd_stdin,buf2,2);
			if(buf2[0] == 'q')
			{
				printf("Quit the Saolei Game!");
				return;
			}
			row=buf2[0]-48;
			read(fd_stdin,buf3,2);
			col=buf3[0]-48;
			if (row < 1 || row > MAX_ROW || col < 1 || col > MAX_COL) {
				printf("input wrong,please input again!\n");
				continue;
			}
			if (show_map[row][col] != '*') {
				printf("This position has been opened, please select again\n");
				continue;
			}
			break;
		}
		//判断该地方是否有雷
		if (mine_map[row][col] == '1') {
			Print_Interface(mine_map);
			printf("There's mine in the place. Game over!!!\n");
			break;
		}
		if (No_Mine(row, col)) {
			show_map[row][col] = '0';
			Open_Blank(row, col);
		}
		show_map[row][col] = '0' + Around_Mine_count(row, col);
		//判断是否掀开所有空地
		if (Success_Sweep(show_map) == 1) {
			Print_Interface(mine_map);
			printf("You have successfully cleared mines,You WIN!!!\n");
			break;
		}
		clear();
		//更新地图
		Print_Interface(show_map);
	}
}

