#include<iostream>
#include<stdlib.h>
#include<time.h>
#include <graphics.h>
#include<conio.h>
#ifndef LOVELYBOY
#define LOVELYBOY
#include "function.h"
#endif

IMAGE GPA4_8;
IMAGE GPA4_9;
IMAGE GPA5_0;
IMAGE cheers;
SYSTEMTIME start;

void Last_page()
{
    loadimage(&GPA4_8, _T("4.8����.jpg"));
    loadimage(&GPA4_9, _T("4.9����.jpg"));
    loadimage(&GPA5_0, _T("5.0����.jpg"));
    loadimage(&cheers, _T("�ٽ�����.jpg"));
    SYSTEMTIME ti;
    int sum = 0;
    GetLocalTime(&ti);		// ��ȡ��ǰʱ��
    sum += ti.wHour - start.wHour;
    sum *= 60;
    sum += ti.wMinute - start.wMinute;
    sum *= 60;
    sum += ti.wSecond - start.wSecond;
    initgraph(1000, 562);
    if (sum <= 180)
    {
        putimage(0, 0, &GPA5_0);
    }
    else if (sum <= 240)
    {
        putimage(0, 0, &GPA4_9);
    }
    else if (sum<= 300)
    {
        putimage(0, 0, &GPA4_8);
    }
    else
    {
        putimage(0, 0, &cheers);
    }
    FlushBatchDraw();
}