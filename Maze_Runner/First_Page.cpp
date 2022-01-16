#include<iostream>
#include<graphics.h>
#define  PI 3.1415926 
#define  WIDTH 814   // 画面宽度
#define  HEIGHT 610  // 画面高度度
double offsetAngle = PI / 6; // 左右枝干和父枝干偏离的角度
double shortenRate = 0.65;  // 子枝干比父枝干变短的倍数
int isShowAnimation = 0; // 是否显示树生成的过程动画
// 把[inputMin,inputMax]范围的input变量，映射为[outputMin,outputMax]范围的output变量
double mapValue(double input, double inputMin, double inputMax, double outputMin, double outputMax)
{
	double output;
	if (abs(input - inputMin) < 0.000001) 
		output = outputMin;
	else
		output = (input - inputMin) * (outputMax - outputMin) / (inputMax - inputMin) + outputMin;
	return output;
}

// 生成[min,max]之间的随机小数 
double randBetween(double min, double max)
{
	double t = rand() / double(RAND_MAX); // 生成[0,1]的随机小数
	// 调用mapValue函数，把值范围从[0,1]映射到[min,max]
	double r = mapValue(t, 0, 1, min, max);
	return r;
}

// 枝干生成和绘制递归函数
// 输入参数：枝干起始x y坐标，枝干长度，枝干角度，枝干绘图线条宽度，第几代
void brunch(double x_start, double y_start, double length, double angle, double thickness, int generation)
{
	// 利用三角函数求出当前枝干的终点x,y坐标
	double x_end, y_end;
	x_end = x_start + length * cos(angle);
	y_end = y_start + length * sin(angle);

	if (x_end >= WIDTH || x_end <= 0)
	{
		COLORREF  color = HSVtoRGB((float)randBetween(300, 350), (float)randBetween(0.2, 0.3), 1);
		setlinecolor(color); // 设定线条颜色
		setfillcolor(color); // 设定填充颜色
	    fillcircle((int)x_end, (int)y_end, 2); // 圆的半径为2（再小就看不清了）
		return;
	}

	// 画线条枝干
	setlinestyle((int)PS_SOLID,(int) thickness); // 设定当前枝干线宽
	// 设置枝干为灰褐色，主树干最黑，子枝干逐渐变亮
	COLORREF  color = HSVtoRGB((float)15, (float)0.75, (float)(0.4 + generation * 0.05));
	setlinecolor(color); // 设定当前枝干颜色

	line((int)x_start, (int)y_start, (int)x_end, (int)y_end); // 画出当前枝干（画线）

	// 求出子枝干的代数
	int childGeneration = generation + 1;
	// 生成左、右、中间三个子枝干的长度，逐渐变短，并有一定随机性
	double childLength = shortenRate * length;
	double leftChildLength = childLength * randBetween(0.9, 1.1);
	double rightChildLength = childLength * randBetween(0.9, 1.1);
	double centerChildLength = childLength * randBetween(0.8, 1.1);

	// 当子枝干长度大于2，并且代数小于等于10，递归调用产生子枝干
	if (childLength >= 2 && childGeneration <= 9)
	{
		// 生成子枝干的粗细，逐渐变细
		double childThickness = thickness * 0.8;
		if (childThickness < 2) // 枝干绘图最细的线宽为2
			childThickness = 2;

		// 一定概率产生左、右、中子枝干
		if (randBetween(0, 1) < 0.95)
			brunch(x_end, y_end, leftChildLength, angle + offsetAngle * randBetween(0.5, 1), childThickness, childGeneration);
		if (randBetween(0, 1) < 0.95)
			brunch(x_end, y_end, rightChildLength, angle - offsetAngle * randBetween(0.5, 1), childThickness, childGeneration);
		if (randBetween(0, 1) < 0.85)
			brunch(x_end, y_end, centerChildLength, angle + offsetAngle / 5 * randBetween(-1, 1), childThickness, childGeneration);
	}
	else // 最末端绘制樱花，画一个粉色填充圆
	{
		setlinestyle(PS_SOLID, 1); // 线宽
		// 樱花粉色HSVtoRGB(325,0.3,1)，有一定随机性
		COLORREF  color = HSVtoRGB((float)randBetween(300, 350), (float)randBetween(0.2, 0.3), (float)1);
		setlinecolor(color); // 设定线条颜色
		setfillcolor(color); // 设定填充颜色
		if (childLength <= 4) // 如果子枝干长度小于等于4
			fillcircle((int)x_end, (int)y_end, 2); // 圆的半径为2（再小就看不清了）
		else
			fillcircle((int)x_end, (int)y_end, (int)(childLength / 2)); // 画一个圆，半径为子枝干长度的一半
	}

	if (isShowAnimation) // 如果为1，绘制樱花树生成的过程动画
	{
		FlushBatchDraw(); // 批量绘制
		Sleep(1); 
	}
}

void startup()  // 初始化
{
	srand((unsigned)time(0)); // 随机初始化
	initgraph(WIDTH, HEIGHT); // 新开一个画面
	
	cleardevice(); // 清屏
	IMAGE tongji;
	loadimage(&tongji, _T("同济草坪.jpg"));
	putimage(0, 0, &tongji);
	//BeginBatchDraw(); // 开始批量绘制
	brunch(WIDTH / 5, HEIGHT, 0.45 * HEIGHT * shortenRate, -PI / 2, 15 * shortenRate, 1); // 递归函数调用,左侧
	brunch(4*WIDTH / 5, HEIGHT, 0.45 * HEIGHT * shortenRate, -PI / 2, 15 * shortenRate, 1);//递归函数调用,右侧
	//FlushBatchDraw(); // 批量绘制
}
/*备用函数，用鼠标调节树的形态*/
void update()  // 每帧更新
{
	MOUSEMSG m;
	if (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE) // 当鼠标移动时，设定递归函数的参数
		{
			// 鼠标从左到右，左右子枝干偏离父枝干的角度逐渐变大
			offsetAngle = mapValue(m.x, 0, WIDTH, PI / 10, PI / 4);
			// 鼠标从上到下，子枝干比父枝干的长度缩短的更快
			shortenRate = mapValue(m.y, 0, HEIGHT, 0.7, 0.3);
		}
		if (m.uMsg == WM_LBUTTONDOWN) // 当鼠标左键点击时，以当前参数开始绘制一棵新数
		{
			cleardevice(); // 清屏
			brunch(WIDTH / 2, HEIGHT, 0.45 * HEIGHT * shortenRate, -PI / 2, 15 * shortenRate, 1); // 递归调用
			FlushBatchDraw(); // 批量绘制
		}
	}
}

int Gateway()
{
	settextstyle(40, 20, _T("微软雅黑"));
	setfillcolor(HSVtoRGB((float)randBetween(300, 350), (float)randBetween(0.2, 0.3), (float)1));
	setlinecolor(RGB(134, 61, 12));
	fillroundrect(WIDTH / 2 - 200, HEIGHT-10, WIDTH / 2 + 200, HEIGHT-200, 5, 5);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(134, 61, 12));
	outtextxy(WIDTH / 2 - 80, HEIGHT - 85 - 80, _T("Tongji:"));
	outtextxy(WIDTH / 2 - 180, HEIGHT - 85 -40, _T("A Survivor's Guide"));
	settextstyle(16, 0, _T("黑体"));
	outtextxy(WIDTH / 2 - 120, HEIGHT - 85, _T("press enter to continue exploring"));
	return 0;
}

void First_Page()
{
	startup();  // 初始化 	
	Gateway();
	return ;
}