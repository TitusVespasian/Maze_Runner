#include<iostream>
#include<graphics.h>
#define  PI 3.1415926 
#define  WIDTH 814   // ������
#define  HEIGHT 610  // ����߶ȶ�
double offsetAngle = PI / 6; // ����֦�ɺ͸�֦��ƫ��ĽǶ�
double shortenRate = 0.65;  // ��֦�ɱȸ�֦�ɱ�̵ı���
int isShowAnimation = 0; // �Ƿ���ʾ�����ɵĹ��̶���
// ��[inputMin,inputMax]��Χ��input������ӳ��Ϊ[outputMin,outputMax]��Χ��output����
double mapValue(double input, double inputMin, double inputMax, double outputMin, double outputMax)
{
	double output;
	if (abs(input - inputMin) < 0.000001) 
		output = outputMin;
	else
		output = (input - inputMin) * (outputMax - outputMin) / (inputMax - inputMin) + outputMin;
	return output;
}

// ����[min,max]֮������С�� 
double randBetween(double min, double max)
{
	double t = rand() / double(RAND_MAX); // ����[0,1]�����С��
	// ����mapValue��������ֵ��Χ��[0,1]ӳ�䵽[min,max]
	double r = mapValue(t, 0, 1, min, max);
	return r;
}

// ֦�����ɺͻ��Ƶݹ麯��
// ���������֦����ʼx y���֦꣬�ɳ��ȣ�֦�ɽǶȣ�֦�ɻ�ͼ������ȣ��ڼ���
void brunch(double x_start, double y_start, double length, double angle, double thickness, int generation)
{
	// �������Ǻ��������ǰ֦�ɵ��յ�x,y����
	double x_end, y_end;
	x_end = x_start + length * cos(angle);
	y_end = y_start + length * sin(angle);

	if (x_end >= WIDTH || x_end <= 0)
	{
		COLORREF  color = HSVtoRGB((float)randBetween(300, 350), (float)randBetween(0.2, 0.3), 1);
		setlinecolor(color); // �趨������ɫ
		setfillcolor(color); // �趨�����ɫ
	    fillcircle((int)x_end, (int)y_end, 2); // Բ�İ뾶Ϊ2����С�Ϳ������ˣ�
		return;
	}

	// ������֦��
	setlinestyle((int)PS_SOLID,(int) thickness); // �趨��ǰ֦���߿�
	// ����֦��Ϊ�Һ�ɫ����������ڣ���֦���𽥱���
	COLORREF  color = HSVtoRGB((float)15, (float)0.75, (float)(0.4 + generation * 0.05));
	setlinecolor(color); // �趨��ǰ֦����ɫ

	line((int)x_start, (int)y_start, (int)x_end, (int)y_end); // ������ǰ֦�ɣ����ߣ�

	// �����֦�ɵĴ���
	int childGeneration = generation + 1;
	// �������ҡ��м�������֦�ɵĳ��ȣ��𽥱�̣�����һ�������
	double childLength = shortenRate * length;
	double leftChildLength = childLength * randBetween(0.9, 1.1);
	double rightChildLength = childLength * randBetween(0.9, 1.1);
	double centerChildLength = childLength * randBetween(0.8, 1.1);

	// ����֦�ɳ��ȴ���2�����Ҵ���С�ڵ���10���ݹ���ò�����֦��
	if (childLength >= 2 && childGeneration <= 9)
	{
		// ������֦�ɵĴ�ϸ���𽥱�ϸ
		double childThickness = thickness * 0.8;
		if (childThickness < 2) // ֦�ɻ�ͼ��ϸ���߿�Ϊ2
			childThickness = 2;

		// һ�����ʲ������ҡ�����֦��
		if (randBetween(0, 1) < 0.95)
			brunch(x_end, y_end, leftChildLength, angle + offsetAngle * randBetween(0.5, 1), childThickness, childGeneration);
		if (randBetween(0, 1) < 0.95)
			brunch(x_end, y_end, rightChildLength, angle - offsetAngle * randBetween(0.5, 1), childThickness, childGeneration);
		if (randBetween(0, 1) < 0.85)
			brunch(x_end, y_end, centerChildLength, angle + offsetAngle / 5 * randBetween(-1, 1), childThickness, childGeneration);
	}
	else // ��ĩ�˻���ӣ������һ����ɫ���Բ
	{
		setlinestyle(PS_SOLID, 1); // �߿�
		// ӣ����ɫHSVtoRGB(325,0.3,1)����һ�������
		COLORREF  color = HSVtoRGB((float)randBetween(300, 350), (float)randBetween(0.2, 0.3), (float)1);
		setlinecolor(color); // �趨������ɫ
		setfillcolor(color); // �趨�����ɫ
		if (childLength <= 4) // �����֦�ɳ���С�ڵ���4
			fillcircle((int)x_end, (int)y_end, 2); // Բ�İ뾶Ϊ2����С�Ϳ������ˣ�
		else
			fillcircle((int)x_end, (int)y_end, (int)(childLength / 2)); // ��һ��Բ���뾶Ϊ��֦�ɳ��ȵ�һ��
	}

	if (isShowAnimation) // ���Ϊ1������ӣ�������ɵĹ��̶���
	{
		FlushBatchDraw(); // ��������
		Sleep(1); 
	}
}

void startup()  // ��ʼ��
{
	srand((unsigned)time(0)); // �����ʼ��
	initgraph(WIDTH, HEIGHT); // �¿�һ������
	
	cleardevice(); // ����
	IMAGE tongji;
	loadimage(&tongji, _T("ͬ�ò�ƺ.jpg"));
	putimage(0, 0, &tongji);
	//BeginBatchDraw(); // ��ʼ��������
	brunch(WIDTH / 5, HEIGHT, 0.45 * HEIGHT * shortenRate, -PI / 2, 15 * shortenRate, 1); // �ݹ麯������,���
	brunch(4*WIDTH / 5, HEIGHT, 0.45 * HEIGHT * shortenRate, -PI / 2, 15 * shortenRate, 1);//�ݹ麯������,�Ҳ�
	//FlushBatchDraw(); // ��������
}
/*���ú�������������������̬*/
void update()  // ÿ֡����
{
	MOUSEMSG m;
	if (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE) // ������ƶ�ʱ���趨�ݹ麯���Ĳ���
		{
			// �������ң�������֦��ƫ�븸֦�ɵĽǶ��𽥱��
			offsetAngle = mapValue(m.x, 0, WIDTH, PI / 10, PI / 4);
			// �����ϵ��£���֦�ɱȸ�֦�ɵĳ������̵ĸ���
			shortenRate = mapValue(m.y, 0, HEIGHT, 0.7, 0.3);
		}
		if (m.uMsg == WM_LBUTTONDOWN) // �����������ʱ���Ե�ǰ������ʼ����һ������
		{
			cleardevice(); // ����
			brunch(WIDTH / 2, HEIGHT, 0.45 * HEIGHT * shortenRate, -PI / 2, 15 * shortenRate, 1); // �ݹ����
			FlushBatchDraw(); // ��������
		}
	}
}

int Gateway()
{
	settextstyle(40, 20, _T("΢���ź�"));
	setfillcolor(HSVtoRGB((float)randBetween(300, 350), (float)randBetween(0.2, 0.3), (float)1));
	setlinecolor(RGB(134, 61, 12));
	fillroundrect(WIDTH / 2 - 200, HEIGHT-10, WIDTH / 2 + 200, HEIGHT-200, 5, 5);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(134, 61, 12));
	outtextxy(WIDTH / 2 - 80, HEIGHT - 85 - 80, _T("Tongji:"));
	outtextxy(WIDTH / 2 - 180, HEIGHT - 85 -40, _T("A Survivor's Guide"));
	settextstyle(16, 0, _T("����"));
	outtextxy(WIDTH / 2 - 120, HEIGHT - 85, _T("press enter to continue exploring"));
	return 0;
}

void First_Page()
{
	startup();  // ��ʼ�� 	
	Gateway();
	return ;
}