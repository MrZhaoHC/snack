#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include <windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define SNACK_NUM 500

struct Dead
{
	int flag = 1;
}Dead;

struct Grade
{
	int num;
}grade;

struct Snack
{
	int size;//蛇的长度
	int direction;//蛇的方向
	int speed;//速度
	//位置
	POINT coor[SNACK_NUM];
}snack;

struct food
{
	int x;
	int y;
	int r;			//大小
	bool flag;		//是否被吃
	DWORD color;	//颜色初始
}food;

enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
















//
//int main()
//{
//	initgraph(1000, 680);
//	IMAGE image;
//	loadimage(&image, _T("1.jpg"));
//	putimage(0, 0, &image);
//	playmusic();
//	while (1)
//	{
//    }
//}