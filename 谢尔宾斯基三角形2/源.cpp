#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>

#define TIMES 200000	  //����Ĵ���
#define SPEED 2000000      //��ʼ�ٶ�(��ֵԽ�󻭵�Խ������ѭ������)

POINT pts_tri[3] = { {-200,0} , {200,0} , {0,350} }; //��������
int x, y; //����
int dir; //�����

//�������α߿�
void draw_flame()
{
	polygon(pts_tri, 3);
}

void draw()
{
	switch ( (rand() % 3) + 1 )
	{
	case 1 : 
		putpixel((getx() + (-200)) / 2 , gety() / 2 , GREEN); 
		x = (getx() + (-200)) / 2;
		y = gety() / 2;
		moveto(x, y);
		break;
	case 2 : 
		putpixel((getx() + 200) / 2 , gety() / 2 , GREEN);
		x = (getx() + 200) / 2;
		y = gety() / 2;
		moveto(x, y);
		break;
	case 3 : 
		putpixel(getx() / 2, (gety() + 350) / 2 , GREEN);
		x = getx() / 2;
		y = (gety() + 350) / 2;
		moveto(x, y);
		break;
	}
}

int recieve_direction(int speed)
{
    dir = getch();
    if (-32 == dir)
        dir = getch();

	//up ����
	if (72 == dir)
	{
		speed -= 999999;
		if ((speed - 999999) <= 0)
		{
			speed = 0;
			return speed;
		}
		return speed;
	}
	
	//down ����
    if (80 == dir)
		speed += 999999;
    return speed;
}

//itoa���ܴ���TCHAR��outtextxy��ֻ����TCHAR-_-
void print_text(int speed, TCHAR* text_1)
{
	settextcolor(WHITE);
	outtextxy(-180, 320, text_1);

	/*	
	TCHAR text_speed[10] = {0};
	_itoa(speed, text_speed, 10);
	wcscpy(text_speed, speed);
	outtextxy(-180, 300, text_speed);
	*/
}


int main()
{
	int speed = SPEED; //�ٶ�
	
	srand((unsigned)time(NULL));

	initgraph(640, 480);	//����
	setorigin(320, 400);	//����ԭ��
	setaspectratio(1, -1);	//����������

	draw_flame(); //���߿�

	moveto(0, 0); //��ʼ�㣬�������Ч��

	TCHAR text_1[] = _T("�� +   �� -"); //�������Ѿ����·���������ô��-_-
	
	for (int i = 0; i < TIMES; i++)
	{
		draw();
		print_text(speed, text_1); //��ʾ�ٶ�

		//������°������ı��ٶ�
		while (kbhit())
		{
			speed = recieve_direction(speed);
		} 
		
		//����
		for (int j = 0; j < speed; j++)
			;
	}

	getchar();
	return 0;
}
