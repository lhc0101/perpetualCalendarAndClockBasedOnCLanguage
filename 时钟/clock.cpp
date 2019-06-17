#include <graphics.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <iostream>
#include <time.h>

#define PI 3.1415926
static bu_dong=0;
/*画表盘*/
void DralDial()
{
	int i;
	int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;										  //表心坐标系坐标
	char rome[][3] = {"12", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"}; //表盘数字

	//画四个圆
	circle(300, 300, 250);
	circle(300, 300, 30);
	circle(300, 300, 260);
	circle(300, 300, 270);

	for (i = 0; i < 59; i++)
	{

		// 画60条短线
		x1 = (int)(300 + (sin(i * PI / 30) * 250));
		y1 = (int)(300 - (cos(i * PI / 30) * 250));
		x2 = (int)(300 + (sin(i * PI / 30) * 260));
		y2 = (int)(300 - (cos(i * PI / 30) * 260));
		//	setbkcolor(RGB(245, 247, 222));
		line(x1, y1, x2, y2);

		//画12个三角形
		setfillstyle(BLACK);
		if (i % 5 == 0)
		{
			x3 = (int)(x1 + sin((i + 5) * PI / 30) * 12);
			y3 = (int)(y1 - cos((i + 5) * PI / 30) * 12);
			x4 = (int)(x1 + sin((i - 5) * PI / 30) * 12);
			y4 = (int)(y1 - cos((i - 5) * PI / 30) * 12);
			x5 = (int)(290 + (sin((i - 0.2) * PI / 30) * 220));
			y5 = (int)(290 - (cos((i - 0.2) * PI / 30) * 220));
			int triangle[6] = {x1, y1, x3, y3, x4, y4};
			//	setcolor(BLACK);
			fillpoly(3, triangle);

			//写表盘数字
			//	setbkcolor(RGB(245, 247, 222));
			setfont(24, 0, "黑体");
			outtextxy(x5, y5, rome[i / 5]);
		}
	}
}

//画指针
void DrawHand(int hour, int minute, int second)
{

	int xhour, yhour, xminute, yminute, xsecond, ysecond; //表心坐标系指针坐标

	xhour = (int)(130 * sin(hour * PI / 6 + minute * PI / 360 + second * PI / 1800));
	yhour = (int)(130 * cos(hour * PI / 6 + minute * PI / 360 + second * PI / 1800));
	xminute = (int)(145 * sin(minute * PI / 30 + second * PI / 1800));
	yminute = (int)(145 * cos(minute * PI / 30 + second * PI / 1800));
	xsecond = (int)(200 * sin(second * PI / 30));
	ysecond = (int)(200 * cos(second * PI / 30));

	//画时针
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 10);
	//	setcolor(LIGHTGRAY);
	line(300 + xhour, 300 - yhour, 300 - xhour / 6, 300 + yhour / 6);

	//画分针
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 10);
	//	setcolor(RGB(222, 158, 107));
	line(300 + xminute, 300 - yminute, 300 - xminute / 4, 300 + yminute / 4);

	//画秒针
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 10);
	//	setcolor(RED);
	line(300 + xsecond, 300 - ysecond, 300 - xsecond / 3, 300 + ysecond / 3);
}

int x1[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 闰年的每月天数
int x2[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 平年的每月天数

char *Week[] = {"星期天", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"}; // 定义星期
char num[3];																		   // 定义 num 字符串
char xy[30];																		   // 定义 xy 字符串,

struct Time // 定义了一个结构体
{
	int year, month, day;			  // 年月
	int yearFlag, monthFlag, dayFlag; // 用来标记年月是否改变
};

// 初始化
void Init()
{
	// 初始化绘图窗口
	initgraph(1400, 650);

	cleardevice();
}

// 绘制星期
void DrawWeek()
{
	char str[7];
	int x1 = 0;

	settextstyle(18, 0, "宋体");
	for (int i = 0; i < 7; i++)
	{
		sprintf(str, "%s", Week[i]);
		outtextxy(720 + x1, 100, str);
		x1 += 60;
	}
}

// 绘制星期2
void DrawWeek2()
{
	char str[7];
	int x1 = 0;

	settextstyle(18, 0, "宋体");
	for (int i = 0; i < 7; i++)
	{
		sprintf(str, "%s", Week[i]);
		outtextxy(120 + x1, 100, str);
		x1 += 60;
	}
}

// 计算现在的年月
void CalDate(Time &tm, char x)
{
	switch (x)
	{
	case 'q':
		tm.year++;
		break;
	case 'w':
		tm.year += 10;
		break;
	case 'e':
		tm.year += 100;
		break;
	case 'r':
		tm.year += 1000;
		break;
	case 't':
		if (tm.month < 12)
			tm.month++;
		break;
	case 'a':
		if (tm.year > 0)
			tm.year--;
		break;
	case 's':
		if (tm.year >= 10)
			tm.year -= 10;
		break;
	case 'd':
		if (tm.year >= 100)
			tm.year -= 100;
		break;
	case 'f':
		if (tm.year >= 1000)
			tm.year -= 1000;
		break;
	case 'g':
		if (tm.month > 1)
			tm.month--;
		break;
	}
}

// 判断年份和月份是否更改
bool DateFlag(int y1, int y2, int m1, int m2)
{
	return (y1 != y2 || m1 != m2);
}

// 判断是闰年还是平年
bool CalYear(int year)
{
	return ((year % 4 == 0 && year % 10 != 0) || year % 400 == 0);
}

// 绘制当月日历
void DrawDate(Time &tm)
{
	int y = 0, z = 0;
	int s;

	sprintf(xy, "当前为公元 %d 年 %d 月的日历", tm.year, tm.month);
	settextstyle(18, 0, "宋体");
	outtextxy(720, 50, xy);

	s = (5 + (tm.year + 1) + (tm.year - 1) / 4 - (tm.year - 1) / 100 + (tm.year - 1) / 400) % 7;

	if (CalYear(tm.year)) // 如果当前年份是闰年
	{
		for (int i = 1; i < tm.month; i++)
		{
			s = (x1[i] + s) % 7;
		}

		if (s / 6 != 1)
		{
			y = (s + 1) * 60;
		}

		settextstyle(36, 0, "Arial");
		for (i = 1; i <= x1[tm.month]; i++)
		{
			sprintf(num, " %d ", i);
			outtextxy(730 + y, 150 + z, num);
			y += 60;
			if ((i + s) % 7 == 6 && (i + s) >= 6)
			{
				z += 85;
				y = 0;
			}
		}
	}
	else // 如果当前年份不是闰年
	{
		for (int i = 1; i < tm.month; i++)
		{
			s = (x2[i] + s) % 7;
		}

		if (s / 6 != 1)
		{
			y = (s + 1) * 60;
		}

		settextstyle(36, 0, "Arial");
		for (i = 1; i <= x2[tm.month]; i++)
		{
			sprintf(num, "%2d", i);
			outtextxy(730 + y, 150 + z, num);
			y += 60;
			if ((i + s) % 7 == 6)
			{
				z += 85;
				y = 0;
			}
		}
	}
}

// 绘制当月日历2
void DrawDate2(Time &tm)
{
	int y = 0, z = 0;
	int s;

	sprintf(xy, "当前为公元 %d 年 %d 月的日历", tm.year, tm.month);
	settextstyle(18, 0, "宋体");
	outtextxy(120, 50, xy);

	s = (5 + (tm.year + 1) + (tm.year - 1) / 4 - (tm.year - 1) / 100 + (tm.year - 1) / 400) % 7;

	if (CalYear(tm.year)) // 如果当前年份是闰年
	{
		for (int i = 1; i < tm.month; i++)
		{
			s = (x1[i] + s) % 7;
		}

		if (s / 6 != 1)
		{
			y = (s + 1) * 60;
		}

		settextstyle(36, 0, "Arial");
		for (i = 1; i <= x1[tm.month]; i++)
		{
			sprintf(num, " %d ", i);
			outtextxy(130 + y, 150 + z, num);
			y += 60;
			if ((i + s) % 7 == 6 && (i + s) >= 6)
			{
				z += 85;
				y = 0;
			}
		}
	}
	else // 如果当前年份不是闰年
	{
		for (int i = 1; i < tm.month; i++)
		{
			s = (x2[i] + s) % 7;
		}

		if (s / 6 != 1)
		{
			y = (s + 1) * 60;
		}

		settextstyle(36, 0, "Arial");
		for (i = 1; i <= x2[tm.month]; i++)
		{
			sprintf(num, "%2d", i);
			outtextxy(130 + y, 150 + z, num);
			y += 60;
			if ((i + s) % 7 == 6)
			{
				z += 85;
				y = 0;
			}
		}
	}
}

// 主函数
int main()
{
	printf("按键介绍：\nq：+1 年/次，a：-1 年/次，\nw：+10年/次，s：-10年/次，\nt：+1 月/次，g：-1 月/次\n");
	printf("当前时间为系统标准时间；\n修改请输入1，\n查询日期输入2，\n否则输入任意字符后回车\n");
	int y;
	scanf("%d", &y);
	if (y == 1)
	{
		int hour1;
		int Second1;
		int min1;
		printf("请输入需要修改的小时，格式为0-23\n");
		scanf("%d", &hour1);
		printf("请输入需要修改的分钟，格式为0-59\n");
		scanf("%d", &min1);
		printf("请输入需要修改的秒，格式为0-59\n");
		scanf("%d", &Second1);
		SYSTEMTIME t0; //获取当前时间
		GetLocalTime(&t0);
		int a = 0, b = 0, c = 0;
		a = 23 - hour1 + t0.wHour; //逻辑思想：获取修改时间与24点之差。标准时间+差为逻辑24时整点day+1；
		b = 59 - min1 + t0.wMinute;
		c = 59 - Second1 + t0.wSecond;

		void DralDial();
		void DrawDecoration();
		void DrawHand(int hour, int minute, int second);

		initgraph(1400, 650); //初始化600×600的绘图窗口

		//	cleardevice();	//清空屏幕

		char add;
		tm *t1;		  // 在 time.h 中有定义为一个结构体，用法见 MSDN
		time_t Clock; // 在 time.h 中有定义为一个结构体，用法见 MSDN
		Time tm;	  // 结构体 tm

		// 初始化
		Init();

		// 获取结构体 Clock 的参数
		time(&Clock);

		// 获取时间
		t1 = localtime(&Clock);
		//	printf(t1);

		tm.year = t1->tm_year + 1900; // 当前系统时间所处年份, 至于为什么加 1900, 见 MSDN
		tm.month = t1->tm_mon + 1;	// 获取系统时间所在月份, 至于为什么加 1, 见 MSDN
		tm.day = t1->tm_mday;
		tm.yearFlag = tm.year;   // 标记当前年份份
		tm.monthFlag = tm.month; // 标记当前月份
		tm.dayFlag = tm.day;

		// 绘制星期
		DrawWeek();
		outtextxy(1150, 30, "按键介绍:");
		outtextxy(1150, 50, "q：+1 年/次，a：-1 年/次");
		outtextxy(1150, 80, "w：+10年/次，s：-10年/次");
		outtextxy(1150, 110, "t：+1 月/次，g：-1 月/次");

		// 绘制当月的日历
		DrawDate(tm);

		//刻名字
		//	setcolor(RED);
		setfont(32, 0, "华文新魏");
		outtextxy(260, 130, "TIME");

		setwritemode(R2_XORPEN); //设置异或绘图方式
		SYSTEMTIME t;			 //定义变量保存当前时间
		GetLocalTime(&t);		 //获取当前时间
		sprintf(xy, "今天是公元 %d 年 %d 月 %d 日 ", t.wYear, t.wMonth, t.wDay);
		settextstyle(25, 0, "宋体");
		outtextxy(0, 5, xy);
		//上面代码作用就是显示当前日期

		int day1 = 0;
		DralDial();  //画表盘
		int y, m, d; //定义全局变量年月日
		while (!kbhit())
		{
			Second1++;
			if (Second1 == 60)
			{
				Second1 = 0;
				min1++;
			}
			DrawHand(hour1, min1, Second1); //画表针
			Sleep(1000);
			DrawHand(hour1, min1, Second1); //擦表针

			SYSTEMTIME t;
			GetLocalTime(&t); //获取当前时间
			if (a == t.wHour && b == t.wMinute && c == t.wSecond)
			{
				t.wDay++;
				if (t.wDay == 32)
				{
					t.wMonth++;
					t.wDay = 1;
				}
				if (t.wMonth == 12)
				{
					t.wYear++;
					t.wMonth = 1;
				}
				y = t.wYear;
				m = t.wMonth;
				d = t.wDay;
				sprintf(xy, "今天是公元 %d 年 %d 月 %d 日", t.wYear, t.wMonth, t.wDay);
				settextstyle(25, 0, "宋体");
				outtextxy(0, 5, xy);
			}
			y = y;
			m = m;
			d = d;
		}

		/*		while(1){
		if (hour1==23 && min1== 59 && Second1 == 59 ) {			//判断时钟时间，满足条件day+1
		
/*		SYSTEMTIME t;
		GetLocalTime(&t);
		t.wDay++;
		sprintf(xy, "今天是公元 %d 年 %d 月 %d 日", t.wYear, t.wMonth, t.wDay);
	    settextstyle(25, 0, "宋体");
		outtextxy(0, 5, xy);

/*
		SYSTEMTIME t3;
		GetLocalTime(&t3);

		sprintf(xy, "今天是公元 %d 年 %d 月 %d 日", t.wYear, t.wMonth, t.wDay+1);
	    settextstyle(25, 0, "宋体");
		outtextxy(0, 5, xy);
		if(a==t3.wHour){
        sprintf(xy, "今天是公元 %d 年 %d 月 %d 日", t.wYear, t.wMonth, t.wDay+1);
	    settextstyle(25, 0, "宋体");
		outtextxy(0, 5, xy);

		}	
	}
*/
		// 主循环
		while (1)
		{
			// 从键盘获取按键
			add = getch();

			// 计算现在的年月
			CalDate(tm, add);

			// 判断年月是否更改, 改则进入 if 语句
			if (DateFlag(tm.year, tm.yearFlag, tm.month, tm.monthFlag))
			{
				// 清除屏幕
				//	cleardevice();
				initgraph(850, 650);
				// 从新绘制星期
				DrawWeek2();
				outtextxy(600, 30, "按键介绍:");
				outtextxy(600, 50, "q：+1 年/次，a：-1 年/次");
				outtextxy(600, 80, "w：+10年/次，s：-10年/次");
				outtextxy(600, 110, "t：+1 月/次，g：-1 月/次");
				// 从新绘制当月日历
				DrawDate2(tm);

				tm.yearFlag = tm.year;   // 更改新标记年份
				tm.monthFlag = tm.month; // 更改新标记月份
			}
		}

		// 返回
		return 0;
	}

	else if (y == 2)
	{
		int year1, month1;
		printf("请输入需要查询的年份，格式为2019\n");
		scanf("%d", &year1);
		printf("请输入需要查询的月份，格式为  05\n");
		scanf("%d", &month1);
		void DralDial();
		void DrawDecoration();
		void DrawHand(int hour, int minute, int second);
		initgraph(1400, 650); //初始化600×600的绘图窗口
		//	cleardevice();	//清空屏幕
		char add;
		Time tm; // 结构体 tm

		tm.year = year1;		 // 当前修改时间所处年份, 至于为什么加 1900, 见 MSDN
		tm.month = month1;		 // 获取修改时间所在月份, 至于为什么加 1, 见 MSDN
		tm.yearFlag = tm.year;   // 标记当前年份
		tm.monthFlag = tm.month; // 标记当前月份

		DrawWeek(); // 绘制星期
		outtextxy(1150, 30, "按键介绍:");
		outtextxy(1150, 50, "q：+1 年/次，a：-1 年/次");
		outtextxy(1150, 80, "w：+10年/次，s：-10年/次");
		outtextxy(1150, 110, "t：+1 月/次，g：-1 月/次");
		DrawDate(tm); // 绘制当月的日历
		//	DrawDecoration();		//画装饰
		DralDial(); //画表盘
		//刻名字
		//	setcolor(RED);
		setfont(32, 0, "华文新魏");
		outtextxy(260, 130, "TIME");
		setwritemode(R2_XORPEN); //设置异或绘图方式
		SYSTEMTIME t;			 //定义变量保存当前时间
		while (!kbhit())
		{
			GetLocalTime(&t); //获取当前时间
			sprintf(xy, "今天是公元 %d 年 %d 月 %d 日 %d:%d:%d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
			settextstyle(25, 0, "宋体");
			outtextxy(0, 5, xy);
			DrawHand(t.wHour, t.wMinute, t.wSecond); //画表针
			Sleep(1000);
			DrawHand(t.wHour, t.wMinute, t.wSecond); //擦表针
		}

		// 主循环
		while (1)
		{
			add = getch();	// 从键盘获取按键
			CalDate(tm, add); // 计算现在的年月
			// 判断年月是否更改, 改则进入 if 语句
			if (DateFlag(tm.year, tm.yearFlag, tm.month, tm.monthFlag))
			{

				cleardevice(); // 清除屏幕
				DralDial();	//画表盘
				DrawWeek();	// 从新绘制星期
				outtextxy(1150, 30, "按键介绍:");
				outtextxy(1150, 50, "q：+1 年/次，a：-1 年/次");
				outtextxy(1150, 80, "w：+10年/次，s：-10年/次");
				outtextxy(1150, 110, "t：+1 月/次，g：-1 月/次");
				DrawDate(tm);			 // 从新绘制当月日历
				tm.yearFlag = tm.year;   // 更改新标记年份
				tm.monthFlag = tm.month; // 更改新标记月份
				setfont(32, 0, "华文新魏");
				outtextxy(260, 130, "TIME");
				setwritemode(R2_XORPEN); //设置异或绘图方式
				while (!kbhit())
				{
					SYSTEMTIME t;	 //定义变量保存当前时间
					GetLocalTime(&t); //获取当前时间
					sprintf(xy, "今天是公元 %d 年 %d 月 %d 日 %d:%d:%d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
					settextstyle(25, 0, "宋体");
					outtextxy(0, 5, xy);
					DrawHand(t.wHour, t.wMinute, t.wSecond); //画表针
					Sleep(1000);
					DrawHand(t.wHour, t.wMinute, t.wSecond); //擦表针
				}
			}
		}

		// 返回
		return 0;
	}


	else
	{
		initgraph(1400, 650); //初始化600×600的绘图窗口

		//	cleardevice();	//清空屏幕

		char add;
		tm *t1;		  // 在 time.h 中有定义为一个结构体，用法见 MSDN
		time_t Clock; // 在 time.h 中有定义为一个结构体，用法见 MSDN
		Time tm;	  // 结构体 tm

		// 初始化
		Init();

		// 获取结构体 Clock 的参数
		time(&Clock);

		// 获取时间
		t1 = localtime(&Clock);
		//	printf(t1);

		tm.year = t1->tm_year + 1900; // 当前系统时间所处年份, 至于为什么加 1900, 见 MSDN
		tm.month = t1->tm_mon + 1;	// 获取系统时间所在月份, 至于为什么加 1, 见 MSDN
		tm.day = t1->tm_mday;
		tm.yearFlag = tm.year;   // 标记当前年份份
		tm.monthFlag = tm.month; // 标记当前月份
		tm.dayFlag = tm.day;

		// 绘制星期
		DrawWeek();
				outtextxy(1150, 30, "按键介绍:");
		outtextxy(1150, 50, "q：+1 年/次，a：-1 年/次");
		outtextxy(1150, 80, "w：+10年/次，s：-10年/次");
		outtextxy(1150, 110, "t：+1 月/次，g：-1 月/次");

		// 绘制当月的日历
		DrawDate(tm);
		//	DrawDecoration();		//画装饰
		DralDial(); //画表盘

		//刻名字
		//	setcolor(RED);
		setfont(32, 0, "华文新魏");
		outtextxy(260, 130, "TIME");

		setwritemode(R2_XORPEN); //设置异或绘图方式
		SYSTEMTIME t;			 //定义变量保存当前时间

		while (!kbhit())
		{
			GetLocalTime(&t); //获取当前时间
			sprintf(xy, "今天是公元 %d 年 %d 月 %d 日 %d:%d:%d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
			settextstyle(25, 0, "宋体");

			outtextxy(0, 5, xy);

			DrawHand(t.wHour, t.wMinute, t.wSecond); //画表针
			Sleep(1000);
			DrawHand(t.wHour, t.wMinute, t.wSecond); //擦表针
		}

		// 主循环
		while (1)
		{
			// 从键盘获取按键
			add = getch();

			// 计算现在的年月
			CalDate(tm, add);

			// 判断年月是否更改, 改则进入 if 语句
			if (DateFlag(tm.year, tm.yearFlag, tm.month, tm.monthFlag))
			{
				// 清除屏幕
				cleardevice();

				DralDial(); //画表盘

				// 从新绘制星期
				DrawWeek();
				outtextxy(1150, 30, "按键介绍:");
				outtextxy(1150, 50, "q：+1 年/次，a：-1 年/次");
				outtextxy(1150, 80, "w：+10年/次，s：-10年/次");
				outtextxy(1150, 110, "t：+1 月/次，g：-1 月/次");
				// 从新绘制当月日历
				DrawDate(tm);

				tm.yearFlag = tm.year;   // 更改新标记年份
				tm.monthFlag = tm.month; // 更改新标记月份

				setfont(32, 0, "华文新魏");
				outtextxy(260, 130, "TIME");

				while (!kbhit())
				{
					SYSTEMTIME t;	 //定义变量保存当前时间
					GetLocalTime(&t); //获取当前时间
					sprintf(xy, "今天是公元 %d 年 %d 月 %d 日 %d:%d:%d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
					settextstyle(25, 0, "宋体");
					outtextxy(0, 5, xy);

					DrawHand(t.wHour, t.wMinute, t.wSecond); //画表针
					Sleep(1000);
					DrawHand(t.wHour, t.wMinute, t.wSecond); //擦表针
				}
			}
		}

		// 返回
		return 0;
	}
}