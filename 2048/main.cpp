#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <easyx.h>
#include <string>
using namespace std;

//函数
void initail_coordinates(int** arr);
void generate_matrix(int** arr);
void new_tile(int** arr);
void move_up(int** arr);
void move_down(int** arr);
void move_left(int** arr);
void move_right(int** arr);
void main_GUI();	
void score_GUI();
void max_score_GUI();
void fail_GUI();
void win_GUI();

int generate_number();
int check_lose(int** board);

bool check_same(int** arr);

//全局变量
int score;
int max_score = 0;
int check[4][4];


int main()
{
start:
	//绘制基础GUI
	main_GUI();
	score = 0;
	score_GUI();
	max_score_GUI();

	/*初始化游戏内容*/
	int max_score_temp = max_score;
	int** array2048 = (int**)malloc(sizeof(int**) * 4);
	for (int i = 0;i < 4;i++)
	{
		array2048[i] = (int*)malloc(sizeof(int) * 4);
	}
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			array2048[i][j] = 0;
		}
	}
	initail_coordinates(array2048);
	generate_matrix(array2048);

	/*开始游戏*/
	while (check_lose(array2048) == 0)
	{
		for (int i = 0;i < 4;i++)
		{
			for (int j = 0;j < 4;j++)
			{
				check[i][j] = array2048[i][j];
			}
		}
		char c;
		c = _getch();
		switch (c)
		{
		default:
			continue;
		case 'w':
		case 72:
			move_up(array2048);
			break;
		case 's':
		case 80:
			move_down(array2048);
			break;
		case 'a':
		case 75:
			move_left(array2048);
			break;
		case 'd':
		case 77:
			move_right(array2048);
			break;
		case 'r':
			max_score = max_score_temp;
			goto start;
		case 27:
			goto exit;
		}
		if (score > max_score)
			max_score = score;
		score_GUI();
		max_score_GUI();
		check_lose(array2048);
		if (!check_same(array2048))
		{
			new_tile(array2048);
		}
		generate_matrix(array2048);
	}
	if (check_lose(array2048) == -1)
	{
		while (1)
		{
			fail_GUI();
			char c = _getch();
			switch (c)
			{
			default:
				continue;
				break;
			case 'r':
				goto start;
			case 27:
				goto exit;
			}
		}
	}
	if (check_lose(array2048) == 1)
	{
		while (1)
		{
			win_GUI();
			char c = _getch();
			switch (c)
			{
			default:
				continue;
				break;
			case 'r':
				goto start;
			case 27:
				goto exit;
			}
		}
	}
exit:
	free(array2048);
	exit(0);
}

//生成初始坐标
void initail_coordinates(int** arr)
{
	int x1, y1, x2, y2;
	srand(time(NULL));
	x1 = rand() % 4;
	y1 = rand() % 4;
	do {
		x2 = rand() % 4;
		y2 = rand() % 4;
	} while (x1 == x2 && y1 == y2);
	arr[y1][x1] = generate_number();
	arr[y2][x2] = generate_number();
}

//生成数字（10%可能性为4,90%可能性为2）
int generate_number()
{
	srand(time(NULL));
	int r = rand() % 10;
	if (r == 0) {
		return 4;
	}
	else {
		return 2;
	}
}

//绘制16个方块
void generate_matrix(int** arr)
{
	for (int y = 0;y < 4;y++)
	{
		for (int x = 0;x < 4;x++)
		{
			setfillcolor(RGB(205, 193, 180));
			solidroundrect(x * 125 + 50, y * 125 + 50, x * 125 + 162.5, y * 125 + 162.5, 20, 20);
		}
	}
	for (int y = 0;y < 4;y++)
	{
		for (int x = 0;x < 4;x++)
		{
			RECT pos = { x * 125 + 50, y * 125 + 50, x * 125 + 162.5, y * 125 + 162.5 };
			LOGFONT f;
			gettextstyle(&f);

			f.lfWeight = FW_ULTRABOLD;
			setbkmode(TRANSPARENT);

			switch (arr[y][x])
			{
			default:
				setfillcolor(RGB(205, 193, 180));
				break;
			case 2:
				f.lfHeight = 70;
				setfillcolor(RGB(238, 228, 218));
				settextcolor(RGB(119, 110, 101));
				solidroundrect(x * 125 + 50, y * 125 + 50, x * 125 + 162.5, y * 125 + 162.5, 20, 20);
				break;
			case 4:
				f.lfHeight = 70;
				setfillcolor(RGB(237, 224, 200));
				settextcolor(RGB(119, 110, 101));
				solidroundrect(x * 125 + 50, y * 125 + 50, x * 125 + 162.5, y * 125 + 162.5, 20, 20);
				break;
			case 8:
				f.lfHeight = 70;
				setfillcolor(RGB(242, 177, 121));
				settextcolor(RGB(249, 246, 242));
				solidroundrect(x * 125 + 50, y * 125 + 50, x * 125 + 162.5, y * 125 + 162.5, 20, 20);
				break;
			case 16:
				f.lfHeight = 60;
				setfillcolor(RGB(245, 149, 99));
				settextcolor(RGB(249, 246, 242));
				solidroundrect(x * 125 + 50, y * 125 + 50, x * 125 + 162.5, y * 125 + 162.5, 20, 20);
				break;
			case 32:
				f.lfHeight = 60;
				setfillcolor(RGB(246, 124, 95));
				settextcolor(RGB(249, 246, 242));
				solidroundrect(x * 125 + 50, y * 125 + 50, x * 125 + 162.5, y * 125 + 162.5, 20, 20);
				break;
			case 64:
				f.lfHeight = 60;
				setfillcolor(RGB(246, 94, 59));
				settextcolor(RGB(249, 246, 242));
				solidroundrect(x * 125 + 50, y * 125 + 50, x * 125 + 162.5, y * 125 + 162.5, 20, 20);
				break;
			case 128:
				f.lfHeight = 60;
				setfillcolor(RGB(237, 207, 114));
				settextcolor(RGB(249, 246, 242));
				solidroundrect(x * 125 + 50, y * 125 + 50, x * 125 + 162.5, y * 125 + 162.5, 20, 20);
				break;
			case 256:
				f.lfHeight = 60;
				setfillcolor(RGB(237, 204, 97));
				settextcolor(RGB(249, 246, 242));
				solidroundrect(x * 125 + 50, y * 125 + 50, x * 125 + 162.5, y * 125 + 162.5, 20, 20);
				break;
			case 512:
				f.lfHeight = 60;
				setfillcolor(RGB(237, 200, 80));
				settextcolor(RGB(249, 246, 242));
				solidroundrect(x * 125 + 50, y * 125 + 50, x * 125 + 162.5, y * 125 + 162.5, 20, 20);
				break;
			case 1024:
				f.lfHeight = 58;
				setfillcolor(RGB(237, 197, 63));
				settextcolor(RGB(249, 246, 242));
				solidroundrect(x * 125 + 50, y * 125 + 50, x * 125 + 162.5, y * 125 + 162.5, 20, 20);
				break;
			case 2048:
				f.lfHeight = 58;
				setfillcolor(RGB(237, 194, 46));
				settextcolor(RGB(119, 110, 101));
				solidroundrect(x * 125 + 50, y * 125 + 50, x * 125 + 162.5, y * 125 + 162.5, 20, 20);
				break;
			}
			settextstyle(&f);
			TCHAR num[5];
			_stprintf_s(num, _T("%d"), arr[y][x]);
			if (arr[y][x] != 0)
				drawtext(num, &pos, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}

//判断游戏是否输掉
int check_lose(int** arr)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (arr[i][j] == 2048) //检查是否有2048，如果有2048，则游戏获胜
			{
				return 1;
			}
			else if (arr[i][j] == 0) //检查是否有0，如果有0，则游戏继续
			{
				return 0;
			}
			if (i < 3 && j < 3)
			{
				if (arr[i][j] == arr[i + 1][j] || arr[i][j] == arr[i][j + 1]) // 检查相邻方块是否相同
				{
					return 0;
				}
				if (arr[3][i] == arr[3][i + 1])// 检查最后一行和最后一列
				{
					return 0;
				}
				if (arr[i][3] == arr[i + 1][3])
				{
					return 0;
				}
			}
		}
	}
	return -1; // 如果以上条件都不满足，判定游戏结束
}

//在空位置放置新方块
void new_tile(int** arr)
{
	int x, y;
	srand(time(NULL));
	do {
		x = rand() % 4;
		y = rand() % 4;
	} while (arr[y][x] != 0);
	arr[y][x] = generate_number();
}

//向上滑动
void move_up(int** arr)
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0;i < 4;i++)
		{
			for (int k = i + 1;k < 4;k++)
			{
				if (arr[k][j] == 0)
					continue;
				if (arr[k][j] == arr[i][j])
				{
					arr[k][j] = 0;
					arr[i][j] *= 2;
					score += arr[i][j];
					break;
				}
				else if (arr[k][j] != arr[i][j])
					break;
			}
		}
		int l = 0;
		for (int i = 0;i < 4;i++)
		{
			if (arr[i][j] != 0)
			{
				arr[l++][j] = arr[i][j];
			}
		}
		while (l < 4) {
			arr[l++][j] = 0;
		}
	}
}

//向下滑动
void move_down(int** arr)
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 3;i >= 0;i--)
		{
			if (arr[i][j] == 0)
				continue;
			for (int k = i - 1;k >= 0;k--)
			{
				if (arr[k][j] == 0)
					continue;
				if (arr[k][j] == arr[i][j])
				{
					arr[k][j] = 0;
					arr[i][j] *= 2;
					score += arr[i][j];
					break;
				}
				else if (arr[k][j] != arr[i][j])
					break;
			}
		}
		int l = 3;
		for (int i = 3;i >= 0;i--)
		{
			if (arr[i][j] != 0)
			{
				arr[l--][j] = arr[i][j];
			}
		}
		while (l >= 0)
		{
			arr[l--][j] = 0;
		}
	}
}

//向左滑动
void move_left(int** arr)
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0;i < 4;i++)
		{
			for (int k = i + 1;k < 4;k++)
			{
				if (arr[j][k] == 0)
					continue;
				if (arr[j][k] == arr[j][i])
				{
					arr[j][k] = 0;
					arr[j][i] *= 2;
					score += arr[j][i];
					break;
				}
				else if (arr[j][k] != arr[j][i])
					break;
			}
		}
		int l = 0;
		for (int i = 0;i < 4;i++)
		{
			if (arr[j][i] != 0)
			{
				arr[j][l++] = arr[j][i];
			}
		}
		while (l < 4) {
			arr[j][l++] = 0;
		}
	}
}

//向右滑动
void move_right(int** arr)
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 3;i >= 0;i--)
		{
			if (arr[j][i] == 0)
				continue;
			for (int k = i - 1;k >= 0;k--)
			{
				if (arr[j][k] == 0)
					continue;
				if (arr[j][k] == arr[j][i])
				{
					arr[j][k] = 0;
					arr[j][i] *= 2;
					score += arr[j][i];
					break;
				}
				else if (arr[j][k] != arr[j][i])
					break;
			}
		}
		int l = 3;
		for (int i = 3;i >= 0;i--)
		{
			if (arr[j][i] != 0)
			{
				arr[j][l--] = arr[j][i];
			}
		}
		while (l >= 0)
		{
			arr[j][l--] = 0;
		}
	}
}

//检查操作前后数组是否变化
bool check_same(int** arr)
{
	int result = 1;
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			if (arr[i][j] != check[i][j])
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

//初始化GUI等
void main_GUI()
{
	initgraph(800, 620);
	HWND hnd = GetHWnd();
	SetWindowText(hnd, _T("2048 by KuroTake"));
	setbkcolor(RGB(250, 248, 239));
	cleardevice();
	setfillcolor(RGB(187, 173, 160));
	solidroundrect(37.5, 37.5, 550, 550, 20, 20);
	solidroundrect(587.5, 37.5, 762.5, 125.5, 20, 20);
	solidroundrect(587.5, 163, 762.5, 251, 20, 20);
	RECT score_pos = { 587.5, 42.5, 762.5, 72.5 };
	RECT max_score_pos = { 587.5, 168, 762.5, 251 };
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 25;						// 设置字体大小
	settextcolor(RGB(238, 228, 218));       // 设置字体颜色
	_tcscpy_s(f.lfFaceName, _T("微软雅黑")); // 设置字体为微软雅黑
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿 
	setbkmode(TRANSPARENT);                 // 去掉文字背景
	settextstyle(&f);						// 设置字体样式
	drawtext(_T("SCORE"), &score_pos, DT_CENTER | DT_SINGLELINE);
	drawtext(_T("BEST"), &max_score_pos, DT_CENTER | DT_SINGLELINE);
	solidroundrect(587.5, 480, 762.5, 550, 20, 20);
	solidroundrect(587.5, 400, 762.5, 470, 20, 20);
	solidroundrect(587.5, 320, 762.5, 390, 20, 20);
	setfillcolor(RGB(215, 206, 195));
	solidroundrect(595, 487.5, 650, 542.5, 15, 15);
	solidroundrect(595, 407.5, 650, 462.5, 15, 15);
	solidroundrect(595, 327.5, 650, 382.5, 15, 15);
	RECT wasd_pos = { 595, 335, 650, 382.5 };
	RECT restart_pos = { 595, 407.5, 650, 462.5 };
	RECT esc_pos = { 595, 487.5, 650, 542.5 };
	f.lfWeight = FW_BOLD;
	f.lfHeight = 30;
	settextstyle(&f);
	settextcolor(RGB(119, 110, 101));
	drawtext(_T("Esc"), &esc_pos, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("R"), &restart_pos, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	f.lfHeight = 20;
	settextstyle(&f);
	drawtext(_T("WASD↑↓←→"), &wasd_pos, DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	settextcolor(RGB(238, 228, 218));
	RECT wasd_text = { 650, 327.5, 755, 382.5 };
	RECT restart_text = { 650, 407.5, 755, 462.5 };
	RECT esc_text = { 650, 487.5, 755, 542.5 };
	f.lfHeight = 30;
	settextstyle(&f);
	drawtext(_T("Exit Game"), &esc_text, DT_CENTER | DT_WORDBREAK);
	drawtext(_T("Restart Game"), &restart_text, DT_CENTER | DT_WORDBREAK);
	drawtext(_T("Move Tiles"), &wasd_text, DT_CENTER | DT_WORDBREAK);
	RECT instruction_text = { 595, 287.5, 762.5, 317.5 };
	RECT op_guide = { 37.5, 550, 762.5, 620 };
	settextcolor(RGB(119, 110, 101));
	f.lfHeight = 25;
	settextstyle(&f);
	drawtext(_T("INSTRUCTION"), &instruction_text, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	f.lfHeight = 30;
	settextstyle(&f);
	drawtext(_T("Join numbers to get to the 2048 tile!"), &op_guide, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//得分GUI
void score_GUI()
{
	RECT pos = { 587.5, 67.5, 762.5, 125.5 };
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 40;
	f.lfWeight = FW_ULTRABOLD;
	settextcolor(RGB(119, 110, 101));
	settextstyle(&f);
	setfillcolor(RGB(215, 206, 195));
	solidroundrect(587.5, 67.5, 762.5, 125.5, 20, 20);
	TCHAR s[10];
	_stprintf_s(s, _T("%d"), score);
	drawtext(s, &pos, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//最高得分GUI
void max_score_GUI()
{
	RECT pos = { 587.5, 193, 762.5, 251 };
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 40;
	f.lfWeight = FW_ULTRABOLD;
	settextcolor(RGB(119, 110, 101));
	settextstyle(&f);
	setfillcolor(RGB(215, 206, 195));
	solidroundrect(587.5, 193, 762.5, 251, 20, 20);
	TCHAR s[10];
	_stprintf_s(s, _T("%d"), max_score);
	drawtext(s, &pos, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//失败GUI
void fail_GUI()
{
	setfillcolor(RGB(235, 230, 219));
	solidroundrect(200, 150, 600, 450, 30, 30);
	RECT pos1 = { 200, 180, 600, 450 };
	RECT pos2 = { 200, 240, 600, 450 };
	RECT pos3 = { 200, 150, 600, 450 };
	RECT pos4 = { 200, 375, 600, 450 };
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 40;
	f.lfWeight = FW_ULTRABOLD;
	settextcolor(RGB(119, 110, 101));
	settextstyle(&f);
	setfillcolor(RGB(215, 206, 195));
	drawtext(_T("😭Oh no, You Lost!😭"), &pos1, DT_CENTER | DT_SINGLELINE);
	f.lfHeight = 30;
	settextstyle(&f);
	drawtext(_T("SCORE"), &pos2, DT_CENTER | DT_SINGLELINE);
	f.lfHeight = 70;
	settextstyle(&f);
	TCHAR s[10];
	_stprintf_s(s, _T("%d"), score);
	drawtext(s, &pos3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	f.lfHeight = 30;
	settextstyle(&f);
	drawtext(_T("Press R to Restart"), &pos4, DT_CENTER | DT_SINGLELINE);
}

//胜利GUI
void win_GUI()
{
	setfillcolor(RGB(235, 230, 219));
	solidroundrect(200, 150, 600, 450, 30, 30);
	RECT pos1 = { 200, 180, 600, 450 };
	RECT pos2 = { 200, 240, 600, 450 };
	RECT pos3 = { 200, 150, 600, 450 };
	RECT pos4 = { 200, 375, 600, 450 };
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 40;
	f.lfWeight = FW_ULTRABOLD;
	settextcolor(RGB(119, 110, 101));
	settextstyle(&f);
	setfillcolor(RGB(215, 206, 195));
	drawtext(_T("😀YOU WIN!😀"), &pos1, DT_CENTER | DT_SINGLELINE);
	f.lfHeight = 30;
	settextstyle(&f);
	drawtext(_T("SCORE"), &pos2, DT_CENTER | DT_SINGLELINE);
	f.lfHeight = 70;
	settextstyle(&f);
	TCHAR s[10];
	_stprintf_s(s, _T("%d"), score);
	drawtext(s, &pos3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	f.lfHeight = 30;
	settextstyle(&f);
	drawtext(_T("Press R to Restart"), &pos4, DT_CENTER | DT_SINGLELINE);
}