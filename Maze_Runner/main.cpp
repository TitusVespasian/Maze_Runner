#include<iostream>
#include<graphics.h>
#ifndef LOVELYBOY
#define LOVELYBOY
#include "function.h"
#endif
using namespace std;

void EnterNextPage()
{
	int c = 0;
	while (c != '\n')
		c = getchar();
	closegraph();
	return;
}
int main()
{
	First_Page();
	EnterNextPage();
	Second_Page();
	EnterNextPage();
	Maze_cord();
	EnterNextPage();
	Last_page();
	EnterNextPage();
	return 0;

}