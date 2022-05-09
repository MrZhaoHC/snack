#include"high.h"


void playmusic()
{
	mciSendString("open 3.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);
}
//初始化蛇
void InitGame()
{
	//播放音乐
	playmusic();
	//初始化窗口
	initgraph(640, 480);
	snack.size = 3;//初始化蛇节数
	snack.speed = 10;//初始化蛇速度
	snack.direction = RIGHT;//初始化蛇方向
	snack.coor[0].x = 10;
	snack.coor[0].y = 10;
	//蛇坐标
	for (int i = 0; i <snack.size; i++)
	{
		snack.coor[i].x = 40-10 * i;
		snack.coor[i].y = 10;
	}
	//初始化食物  stdlib.h
	//设置随机数种子  //GetTickCount()获取系统开机时间
	srand(GetTickCount());
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = 5;
	food.flag = true;
	//初始化分数
	grade.num = 0;
	//死亡初始化
	Dead.flag = 1;
}
//蛇移动
void snackmove()
{
	//蛇身体跟着蛇头的轨迹
	for (int i = snack.size - 1; i > 0; i--)
	{
		snack.coor[i].x = snack.coor[i - 1].x;
		snack.coor[i].y = snack.coor[i - 1].y;
	}
	//蛇头方向
	switch (snack.direction)
	{
	case UP:
		if (snack.coor[0].y-5 <= 0)
			snack.coor[0].y = 480;
		snack.coor[0].y -= snack.speed;
		break;	
	case DOWN:
		if (snack.coor[0].y+5 >= 480)
			snack.coor[0].y = 0;
		snack.coor[0].y += snack.speed;
		break;
	case LEFT:
		if (snack.coor[0].x-5 <= 0)
			snack.coor[0].x = 640;
		snack.coor[0].x -= snack.speed;
		break;
	case RIGHT:
		if (snack.coor[0].x+5 >= 640)
			snack.coor[0].x = 0;
		snack.coor[0].x += snack.speed;
		break;
	}
}
//通过按键改变方向
void KeyControl()
{
	//判断有没有输入,让蛇自己动
	if (_kbhit())//如果有按键
	{
		switch (_getch())
		{
		case 'w'://上
		case 'W':
		case 72:
			if (snack.direction!=DOWN)
				snack.direction = UP;
			break;
		case 's'://下
		case 'S':
		case 80:
			if (snack.direction != UP)
				snack.direction = DOWN;
			break;
		case 'a'://左
		case 'A':
		case 75:
			if (snack.direction!=RIGHT)
				snack.direction = LEFT;
			break;
		case 'd'://右
		case 'D':
		case 77:
			if (snack.direction != LEFT)
				snack.direction = RIGHT;
			break;
		//游戏暂停
		case ' ':
			mciSendString("close BGM", 0, 0, 0);
			while (_getch() != ' ');
			playmusic();
			break;
		}
	}
	//72,80,75,77上下左右

}
//记分
void CountGrades()
{
	if (!food.flag)
	{
		grade.num++;
	}
}
//吃食物
void Eatfood()
{
	if (food.x- food.r <= snack.coor[0].x&& food.x + food.r >= snack.coor[0].x 
		&& food.y- food.r <= snack.coor[0].y&& food.y+ food.r >= snack.coor[0].y
		&&food.flag==true)
	{
		food.flag = false;
		snack.size++;
	}
	CountGrades();
	if (!food.flag)//刷新事物
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = 5;
		food.flag = true;
	}
}

void GameDraw()
{
	//双缓冲绘图
	BeginBatchDraw();
	//背景颜色
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	//绘制蛇
	
	for (int i = 0; i < snack.size; i++)
	{
		if (i == 0)
		{
			setfillcolor(RED);
			solidcircle(snack.coor[i].x, snack.coor[i].y, 5);
		}
		else
		{
			setfillcolor(YELLOW);
			solidcircle(snack.coor[i].x, snack.coor[i].y, 5);
		}
	}
	//绘制食物
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	//绘制当前分数
	outtextxy(300, 240, _T("分数:"));
	char num[20];
	int n = grade.num;
	sprintf(num, "%d", n);
	outtextxy(340, 240, num);
	EndBatchDraw();
}
//判死
void Death()
{
	for (int i = 2; i < snack.size; i++)
	{
		if (snack.coor[0].x == snack.coor[i].x && snack.coor[0].y == snack.coor[i].y)
		{
			Dead.flag = 0;
		}
	}
}


int main()
{
	InitGame();
	while (true)
	{
		if (Dead.flag)
		{
			GameDraw();
			KeyControl();
			snackmove();
			Death();
			Eatfood();
		}
		else
		{
			InitGame();
		}
		Sleep(100);
	}
	return 0;
}