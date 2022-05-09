#include"high.h"


void playmusic()
{
	mciSendString("open 3.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);
}
//��ʼ����
void InitGame()
{
	//��������
	playmusic();
	//��ʼ������
	initgraph(640, 480);
	snack.size = 3;//��ʼ���߽���
	snack.speed = 10;//��ʼ�����ٶ�
	snack.direction = RIGHT;//��ʼ���߷���
	snack.coor[0].x = 10;
	snack.coor[0].y = 10;
	//������
	for (int i = 0; i <snack.size; i++)
	{
		snack.coor[i].x = 40-10 * i;
		snack.coor[i].y = 10;
	}
	//��ʼ��ʳ��  stdlib.h
	//�������������  //GetTickCount()��ȡϵͳ����ʱ��
	srand(GetTickCount());
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = 5;
	food.flag = true;
	//��ʼ������
	grade.num = 0;
	//������ʼ��
	Dead.flag = 1;
}
//���ƶ�
void snackmove()
{
	//�����������ͷ�Ĺ켣
	for (int i = snack.size - 1; i > 0; i--)
	{
		snack.coor[i].x = snack.coor[i - 1].x;
		snack.coor[i].y = snack.coor[i - 1].y;
	}
	//��ͷ����
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
//ͨ�������ı䷽��
void KeyControl()
{
	//�ж���û������,�����Լ���
	if (_kbhit())//����а���
	{
		switch (_getch())
		{
		case 'w'://��
		case 'W':
		case 72:
			if (snack.direction!=DOWN)
				snack.direction = UP;
			break;
		case 's'://��
		case 'S':
		case 80:
			if (snack.direction != UP)
				snack.direction = DOWN;
			break;
		case 'a'://��
		case 'A':
		case 75:
			if (snack.direction!=RIGHT)
				snack.direction = LEFT;
			break;
		case 'd'://��
		case 'D':
		case 77:
			if (snack.direction != LEFT)
				snack.direction = RIGHT;
			break;
		//��Ϸ��ͣ
		case ' ':
			mciSendString("close BGM", 0, 0, 0);
			while (_getch() != ' ');
			playmusic();
			break;
		}
	}
	//72,80,75,77��������

}
//�Ƿ�
void CountGrades()
{
	if (!food.flag)
	{
		grade.num++;
	}
}
//��ʳ��
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
	if (!food.flag)//ˢ������
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
	//˫�����ͼ
	BeginBatchDraw();
	//������ɫ
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	//������
	
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
	//����ʳ��
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	//���Ƶ�ǰ����
	outtextxy(300, 240, _T("����:"));
	char num[20];
	int n = grade.num;
	sprintf(num, "%d", n);
	outtextxy(340, 240, num);
	EndBatchDraw();
}
//����
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