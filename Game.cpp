
#include"Game.h"

const int TIME = 50;
const int MAX_ENEMY = 3;

int random(int a, int b)
{
	return (rand() % (b - a + 1)) + a;
}

Plane::Plane()
{
	COORD a = { 5,2 },b = { 45,2 };
	po[0].X = random(5, 45); po[0].Y = 2;
	po[1].X = po[3].X = po[0].X - 1;
	po[2].X = po[4].X = po[0].X + 1;
	po[1].Y = po[2].Y = po[0].Y - 1;
	po[3].Y = po[4].Y = po[0].Y + 1;
}

void Plane::InitMe()
{
	po[0].X = 25; po[0].Y = 26;
	po[1].X = po[3].X = po[0].X - 1;
	po[2].X = po[4].X = po[0].X + 1;
	po[1].Y = po[2].Y = po[0].Y - 1;
	po[3].Y = po[4].Y = po[0].Y + 1;
}

void Plane::drawPlane()
{
	for (int i = 0; i < 5; i++)
	{
		SetPos(po[i]);
		cout << 'O';
	}
}

void Plane::deletePlane()
{
	if (po[0].X > 1 && po[0].X < 49 && po[0].Y>1 && po[0].Y < 27)
	{
		for (int i = 0; i < 5; i++)
		{
			SetPos(po[i]);
			cout << ' ';
		}
	}
}

void Plane::planeMove(char x)
{
	if (x == 'a' || x == 'A')
		if (po[0].X > 3)
			for (int i = 0; i <= 4; i++)
				po[i].X -= 2;

	if (x == 's' || x == 'S')
		if (po[0].Y < 25)
			for (int i = 0; i <= 4; i++)
				po[i].Y += 1;

	if (x == 'd' || x == 'D')
		if (po[0].X < 47)
			for (int i = 0; i <= 4; i++)
				po[i].X += 2;

	if (x == 'w' || x == 'W')
		if (po[0].Y > 3)
			for (int i = 0; i <= 4; i++)
				po[i].Y -= 1;
}

bool Plane::JudgePlane()
{
	return (po[0].X > 0 && po[0].X < 50 && po[0].Y>0 && po[0].Y < 28);
}


void Plane::randMove()
{
	for (int i = 0; i <= 4; i++)
		po[i].Y++;
	int i = random(1, 3);
	switch (i)
	{
	case 1:planeMove('a'); break;
	case 2:planeMove('d'); break;
	case 3:break;
	default:break;
	}
}

void Game::newEnemy()
{
	if (enemy.size() < MAX_ENEMY)
		enemy.push_back(Plane());
}

void Game::drawBullet()
{
	for (vector<COORD>::iterator it = bullet.begin(); it != bullet.end(); ++it)
	{
		SetPos(*it); cout << "*";
	}
}

void Game::deleteBullet()
{
	for (vector<COORD>::iterator it = bullet.begin(); it != bullet.end(); ++it)
	{
		SetPos(*it); 
		cout << " ";
	}
}

void Game::bulletMove()
{
	for (vector<COORD>::iterator it = bullet.begin(); it != bullet.end(); )
	{
		it->Y--;
		if (it->Y < 1)
		{
			it = bullet.erase(it); 
		}
		else
		{
			it++;
		}
	}
}

void Game::BulletInEnemy()
{
	for (vector<COORD>::iterator it = bullet.begin(); it != bullet.end(); it++)
	{
		for (vector<Plane>::iterator itt = enemy.begin(); itt != enemy.end(); )
		{
			if (((itt->po[0].X == it->X + 1 || itt->po[0].X == it->X - 1)
				&& (itt->po[0].Y == it->Y + 1 || itt->po[0].Y == it->Y - 1))
				|| (itt->po[0].X == it->X&&itt->po[0].Y == it->Y))
			{
				itt->deletePlane();
				itt = enemy.erase(itt);
				score += 10;
			}
			else
			{
				itt++;
			}
		}
	}
}

bool Game::EnemyInMe()
{
	for (vector<Plane>::iterator it = enemy.begin(); it != enemy.end(); it++)
	{
		if (!it->JudgePlane())
			return true;
		else if ((abs(it->po[0].X - me.po[0].X )<= 1) && (abs(it->po[0].Y - me.po[0].Y )<= 1))
			return true;
	}
	return false;
}

void Game::Scorelist()
{
	ifstream fin("scorelist.txt");
	while (!fin.eof())
	{
		Scorestar x;
		fin >> x.name >> x.score;
		player.push_back(x);
		fin.get();
		if (fin.peek() == EOF)break;
	}
	fin.close();
	system("cls");
	sort(player.begin(), player.end(), [](Scorestar x, Scorestar y)->bool {return x.score > y.score; });
	SetPos(25, 0); cout << "排行榜";
	SetPos(25, 2); cout << "输入ESC退出";
	for (int i = 0; i < player.size(); i++)
	{
		SetPos(20, 4 + 2 * i); cout << player[i].name;
		SetPos(30, 2 + 2 * i); cout << player[i].score << endl;
	}
	while (1)
	{
		char x;
		x = _getch();
		if (x == 27)break;
	}
}

void Game::GameOver()
{
	system("cls");
	SetPos(25, 8); cout << "游戏结束！";
	SetPos(15, 10); cout << "您的分数：" << score << " ，是否保存？（Y/N）";
	while (1)
	{
		char x = _getch();
		if (x == 'Y' || x == 'y')
		{
			string x;
			SetPos(15, 12); cin.sync();
			cout << "请输入您的昵称："; cin >> x;
			ofstream fout("scorelist.txt", ios::app);
			fout << score << "	" << x << endl;
		}
		else if (x == 'N' || x == 'n')
			break;
	}
}

void Game::run()
{
	char x;
	while (1)
	{
		system("cls");
		SetPos(25, 8); cout << "游戏选择:" << endl;
		SetPos(25, 10); cout << "1: 开始游戏" << endl;
		SetPos(25, 12); cout << "2: 排行榜" << endl;
		SetPos(25, 14); cout << "3: 退出游戏" << endl;
		x = _getch();
		system("cls");
		switch (x)
		{
		case '1':Show(); break;
		case '2':Scorelist(); break;
		case '3':break;
		default:break;
		}
		if (x == '3')return;
		else if (x == '1')break;
	}
	enemy.push_back(Plane()); enemy.push_back(Plane()); enemy.push_back(Plane());
	int i = 0;
	while (1)
	{
		SetPos(59, 10);cout << "  ";SetPos(59, 10); cout << score;
		me.drawPlane();
		Sleep(TIME);
		if (_kbhit())
		{
			char x = _getch();
			if ('a' == x || 's' == x || 'd' == x || 'w' == x|| 'A' == x || 'S' == x || 'D' == x || 'W' == x)
			{
				if (me.JudgePlane())
				{
					me.deletePlane();
					me.planeMove(x);
					me.drawPlane();
				}
			}
			else if (' ' == x)
				bullet.push_back({ me.po[0].X,me.po[0].Y });
			else if (27 == x)
			{
				GameOver(); break;
			}
		}
		deleteBullet();bulletMove(); drawBullet();
		BulletInEnemy();
		newEnemy();
		if (EnemyInMe())
		{
			GameOver(); break;
		}
		if (i % 20== 0)
		{
			for (vector<Plane>::iterator it = enemy.begin(); it != enemy.end(); it++)
			{
				it->deletePlane();
				it->randMove();
				it->drawPlane();
			}
		}
		i++;
	}

	system("pause");
}