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

#define WIDTH 8
#define HEIGHT 8

/**
*	0	表示空
*	1	表示墙
*	2	表示人
*	3	表示箱子
*	4	表示球
*	5	表示推到目的地的箱子 
*/
int map[HEIGHT][WIDTH] = {
	{0, 0, 1, 1, 1, 0, 0, 0},
	{0, 0, 1, 4, 1, 0, 0, 0},
	{0, 0, 1, 0, 1, 1, 1, 1},
	{1, 1, 1, 3, 0, 3, 4, 1},
	{1, 4, 0, 3, 2, 1, 1, 1},
	{1, 1, 1, 1, 3, 1, 0, 0},
	{0, 0, 0, 1, 4, 1, 0, 0},
	{0, 0, 0, 1, 1, 1, 0, 0} 
};

//人的位置 
int x, y;

//箱子的个数 
int boxs; 
char buf[10] = { 0 };		//存储键盘按的方向 
//声明方法 
void initData2();
void drawMap();
void moveUp();
void moveLeft();
void moveDown();
void moveRight();

void pushBox(int fd_stdin,int fd_stdout) {
	printf("Welcome to pushBox Game!\n\n\n");
   	printf("LEFT: a    RIGHT: d\n");
   	printf("UP:   w    DOWN:  s\n");
    	printf("EXIT: press enter  \n\n\n");
	initData2();
	drawMap();
       while(read(fd_stdin,buf,1)){
		if(!boxs){
			break;
		}
		switch(buf[0]){
			case 'q':
				printf("Quit the PushBox Game!");
				return;
			case 'w':
				clear();
				moveUp();
				drawMap(); 
				break;
			case 'a':
				clear();
				moveLeft(); 
				drawMap(); 
				break;
			case 's':
				clear();
				moveDown();
				drawMap(); 
				break;
			case 'd':
				clear();
				moveRight();
				drawMap(); 
				break; 
			}
		}
		if(boxs==0){
			printf("you win");
			}
	}
/**
*	初始化一些必须的数据 
*/
void initData2(){
	int i, j;
	//获取人的位置
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			if(map[i][j] == 2){
				x = j;
				y = i;
			} 
			//遍历到3时，箱子的数目增加 
			if(map[i][j] == 3){
				boxs++;
			}
		}
	} 
}

/**
*	用于在控制台显示地图 
*/
void drawMap(){
	int i, j;
	for(i = 0; i < WIDTH; i++){
		for(j = 0; j < HEIGHT; j++){
			switch(map[i][j]){
				case 0:
					printf(" ");
					break;
				case 1:
					printf("#");
					break;
				case 2:
					printf("$");
					break;
				case 3:
					printf("@");
					break;
				case 4:
					printf("*");
					break;
				case 5:
					printf("O");
					break; 
			}
		}
		printf("\n");
	}
}
/**
*	人物向上移动 
*/
void moveUp(){
	//定义变量存放人物上方的坐标
	int ux, uy; 
	
	//当上方没有元素时，直接return	
	if(y == 0){
		return;
	}
	
	//记录上方坐标
	ux = x;
	uy = y - 1; 
	
	//上方为已完成方块
	if(map[uy][ux] == 5){
		return;
	} 
	
	//假设上方为墙，直接return 
	if(map[uy][ux] == 1){
		return;
	}
	
	//假设上方为箱子
	if(map[uy][ux] == 3){
		//判断箱子上方是否为墙 
		if(map[uy - 1][ux] == 1){
			return;
		}
		
		//判断箱子上方是否为球
		if(map[uy - 1][ux] == 4){
			//将箱子上面内容赋值为5★ 
			map[uy - 1][ux] = 5;
			map[uy][ux] = 0;
			//箱子的数目减1	
			boxs--; 
		}else{
			//移动箱子
			map[uy - 1][ux] = 3;
		}
	}
	map[y][x] = 0;
	map[uy][ux] = 2;
	y = uy; 
} 

/**
*	向左移动 
*/
void moveLeft(){
	//定义变量存放人物左边的坐标
	int lx, ly; 
	
	//当左边没有元素时，直接return	
	if(x == 0){
		return;
	}
	
	//记录左边坐标
	lx = x - 1;
	ly = y; 
	
	//左边为已完成方块
	if(map[ly][lx] == 5){
		return;
	} 
	
	//假设左边为墙，直接return 
	if(map[ly][lx] == 1){
		return;
	}
	
	//假设左边为箱子
	if(map[ly][lx] == 3){
		//判断箱子左边是否为墙 
		if(map[ly][lx - 1] == 1){
			return;
		}
		
		//判断箱子左边是否为球
		if(map[ly][lx - 1] == 4){
			//将箱子左边内容赋值为5★ 
			map[ly][lx - 1] = 5;
			map[ly][lx] = 0;
		
			//箱子的数目减1 
			boxs--; 
		}else{
			//移动箱子 
			map[ly][lx - 1] = 3; 
		}
	}
	map[y][x] = 0;
	map[ly][lx] = 2;
	x = lx; 
}

/**
*	向下移动
*/
void moveDown(){
	//定义变量存放人物下方的坐标
	int dx, dy; 
	
	//当下方没有元素时，直接return	
	if(y == HEIGHT - 1){
		return;
	}
	
	//记录下方坐标
	dx = x;
	dy = y + 1; 
	
	//下方为已完成方块
	if(map[dy][dx] == 5){
		return;
	} 
	
	//假设下方为墙，直接return 
	if(map[dy][dx] == 1){
		return;
	}
	
	//假设下方为箱子
	if(map[dy][dx] == 3){
		//判断箱子下方是否为墙 
		if(map[dy + 1][dx] == 1){
			return;
		}
		
		//判断箱子下方是否为球
		if(map[dy + 1][dx] == 4){
			//将箱子下面内容赋值为5★ 
			map[dy + 1][dx] = 5;
			map[dy][dx] = 0;
			
			//箱子的数目减1 
			boxs--; 
		}else{
			//移动箱子
			map[dy + 1][dx] = 3; 
		}
	}
	map[y][x] = 0;
	map[dy][dx] = 2;
	y = dy; 
}

/**
*	向右移动 
*/
void moveRight(){
	//定义变量存放人物右边的坐标
	int rx, ry; 
	
	//当右边没有元素时，直接return	
	if(x == WIDTH - 1){
		return;
	}
	
	//记录右边坐标
	rx = x + 1;
	ry = y; 
	
	//右边为已完成方块
	if(map[ry][rx] == 5){
		return;
	} 
	
	//假设右边为墙，直接return 
	if(map[ry][rx] == 1){
		return;
	}
	
	//假设右边为箱子
	if(map[ry][rx] == 3){
		//判断箱子右边是否为墙 
		if(map[ry][rx + 1] == 1){
			return;
		}
		
		//判断箱子左边是否为球
		if(map[ry][rx + 1] == 4){
			//将箱子右边内容赋值为5★ 
			map[ry][rx + 1] = 5;
			map[ry][rx] = 0;
			
			//箱子的数目减1 
			boxs--;
		}else{
			//移动箱子 
			map[ry][rx + 1] = 3; 
		}
	}
	map[y][x] = 0;
	map[ry][rx] = 2;
	x = rx; 
}
