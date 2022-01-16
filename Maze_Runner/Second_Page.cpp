#include<iostream>
#include<graphics.h>
#ifndef LOVELYBOY
#define LOVELYBOY
#include "function.h"
#endif
using namespace std;
IMAGE introduction;
void Second_Page()
{
	loadimage(&introduction, _T("¼ò½é.jpg"));
	initgraph(1000, 562);
	putimage(0, 0,&introduction);
}