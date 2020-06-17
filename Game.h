#pragma once
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<time.h>  
#include<string>  
#include<vector>
#include<algorithm>
#include<fstream>
#include<cmath>
using namespace std;

struct Scorestar
{
	string name;
	int score;
};

class Frame
{
protected:
	HANDLE out;
public:
	//初始化
	Frame()
	{
		out = GetStdHandle(STD_OUTPUT_HANDLE);
		HideCursor();
	}
	void Show()
	{
		drawFrame(0, 0, 50, 28, '=', '|');//    draw map frame;  
		drawFrame(51, 0, 75, 8, '=', '|');//        draw output frame  
		drawFrame(51, 8, 75, 12, '=', '|');//        draw score frame  
		drawFrame(51, 12, 75, 24, '=', '|');//   draw operate frame  
		drawFrame(51, 24, 75, 28, '=', '|');//  draw other message frame  
		SetPos(59, 4); cout << "飞机大战";
		SetPos(53, 10);cout << "得分：";
		SetPos(53, 14);
		cout << "操作方式：";
		SetPos(53, 16);
		cout << "W,S,A,D 控制战机移动";
		SetPos(53, 18);
		cout << "SPACE 发射子弹";
		SetPos(53, 20);
		cout << "ESC 退出游戏";
	}

	//设置光标  
	void SetPos(COORD a)
	{
		SetConsoleCursorPosition(out, a);
	}
	void SetPos(int i, int j)
	{
		COORD pos = { i, j };
		SetPos(pos);
	}

	//隐藏光标
	void HideCursor()
	{
		CONSOLE_CURSOR_INFO cci;
		GetConsoleCursorInfo(out, &cci);
		cci.bVisible = false;
		SetConsoleCursorInfo(out, &cci);
	}

	//把第y行，x1，x2之间的坐标填充为 ch  
	void drawRow(int y, int x1, int x2, char ch)
	{
		SetPos(x1, y);
		for (int i = 0; i <= x2 - x1; i++)
			cout << ch;
	}

	//把第x列，y1, y2之间的坐标填充为 ch  
	void drawCol(int x, int y1, int y2, char ch)
	{
		for (int y = y1; y <= y2; ++y)
		{
			SetPos(x, y);
			cout << ch;
		}
	}

	//绘制(x1,y1)为左上角，(x2,y2)为右下角的边框
	void drawFrame(int x1, int y1, int x2, int y2, char row, char col)
	{
		drawRow(y1, x1 , x2 , row);
		drawRow(y2, x1 , x2 , row);
		drawCol(x1, y1 , y2 , col);
		drawCol(x2, y1 , y2 , col);
	}
};

class Plane:public Frame
{
public:
	COORD po[5];
	Plane();
	void InitMe();
	void planeMove(char x);
	void randMove();
	bool JudgePlane();
	void drawPlane();
	void deletePlane();
};
class Game:public Frame
{
protected:
	int score;
	vector<Plane> enemy;
	Plane me;
	vector<COORD> bullet;
	vector<Scorestar> player;
public:
	Game()
	{
		me.InitMe();
		score = 0;
	}
	void run();
	void Scorelist();
	void drawBullet();
	void newEnemy();
	void deleteBullet();
	void bulletMove();
	void BulletInEnemy();
	bool EnemyInMe();
	void GameOver();
};
