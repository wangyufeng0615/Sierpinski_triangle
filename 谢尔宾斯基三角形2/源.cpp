#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>

#define TIMES 200000	  //画点的次数
#define SPEED 2000000      //初始速度(数值越大画得越慢，空循环次数)

POINT pts_tri[3] = { {-200,0} , {200,0} , {0,350} }; //画布顶点
int x, y; //坐标
int dir; //方向键

//画三角形边框
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

	//up 加速
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
	
	//down 减速
    if (80 == dir)
		speed += 999999;
    return speed;
}

//itoa不能处理TCHAR，outtextxy又只能用TCHAR-_-
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
	int speed = SPEED; //速度
	
	srand((unsigned)time(NULL));

	initgraph(640, 480);	//画布
	setorigin(320, 400);	//坐标原点
	setaspectratio(1, -1);	//坐标轴正向

	draw_flame(); //画边框

	moveto(0, 0); //初始点，尚无随机效果

	TCHAR text_1[] = _T("↓ +   ↑ -"); //坐标轴已经上下反过来了怎么办-_-
	
	for (int i = 0; i < TIMES; i++)
	{
		draw();
		print_text(speed, text_1); //显示速度

		//检测上下按键，改变速度
		while (kbhit())
		{
			speed = recieve_direction(speed);
		} 
		
		//调速
		for (int j = 0; j < speed; j++)
			;
	}

	getchar();
	return 0;
}
