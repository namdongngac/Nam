
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "Console.h"

using namespace std;

const int ConsoleW = 25;
const int ConsoleH = 25;

class Pos2D
{
	public:
		char s[20];
		int x; int y;
		int hp;	
};

class Object
{
	public:
		Pos2D multi[25];
};

Pos2D Plane;
Object Bullet;
Object Fly;
Pos2D Boss;
Object BulletBoss;
Object Item;
bool endgame, sumBoss;
int score, life, newBosshp ;
int j, k, l, h;
int iBullet, iFly, iBulletBoss;
int bulPlane, bulBoss;
int CountFly;
int speedFly; 
int tempFly;

void create(Pos2D & Object,int x,int y)
{
	Object.x = x;
	Object.y = y;
}

void Init()
{
	create(Plane,ConsoleW/2,ConsoleH-1);
	create(Boss,rand()%ConsoleH-10,0);
	Boss.hp=10;
	newBosshp=Boss.hp;
	speedFly=5;
	tempFly=15;
	endgame = false; sumBoss = false;
	score = 0; life = 3; 
	j=0; k=0; l=0; h=0;
	iBullet=0; iFly=0; iBulletBoss=0;
	bulPlane=0; bulBoss=0;
	strcpy(Plane.s,">}^{<"); 
	for(int i=0;i<25;i++){
		strcpy(Bullet.multi[i].s,"^");
	}
	for(int i=0;i<30;i++){
		strcpy(Fly.multi[i].s,">0<");
	}
	strcpy(Boss.s,"=|[<>]|=");
	for(int i=0;i<25;i++){
		strcpy(BulletBoss.multi[i].s,"vv");
	}
	for(int i=0;i<25;i++){
		strcpy(Item.multi[i].s,"O");
	}
}

void sum(Pos2D & Boss, Object & BulletBoss)
{
	Boss.y++;
	int ran=rand()%2+1;
	if(ran%2==0)
	{
		Boss.x++;
		if(Boss.x>=ConsoleW-4)Boss.x--;
	}
	if(ran%2==1)
	{
		Boss.x--;
		if(Boss.x<=0)Boss.x++;
	}
	if(Boss.y==3)Boss.y--;
	l++;
	if(l%15==0){
		if(bulBoss>0)
		{
			BulletBoss.multi[iBulletBoss].x=Boss.x+3;
			BulletBoss.multi[iBulletBoss].y=Boss.y+1;
			iBulletBoss++;
			bulBoss=0;
		}
	}
	h++;
	if(h%5==0)bulBoss=1;	
	if(iBulletBoss==24)iBulletBoss=0;
		
	for(int i=0;i<25;i++)
	{
		BulletBoss.multi[i].y++;
			
	}
}

void createMul(Object & Object,int x, int y,int speed, int temp)
{
	int ran=rand()%temp;
	if(ran==10&&!sumBoss)
	{
		Object.multi[iFly].x=x;
		Object.multi[iFly].y=y;
		iFly++;	
	}
	if(iFly==24)iFly=0;	
	k++;
	for(int i=0;i<25;i++)
	{
		if(k%speed==0)
		{
			if(Object.multi[i].y>=0&&Object.multi[i].x<=ConsoleW)
			{
				Object.multi[i].y++;
			}
		}		
	}
}


void draw(Pos2D & Object,int color)
{
	SetColor(color);
	gotoxy(Object.x, Object.y);
	cout<<Object.s;
}

void drawMul(Object & Object,int color)
{	
	for(int i=0;i<25;i++)
	{
		if(Object.multi[i].y>=0&&Object.multi[i].y<=ConsoleH&&Object.multi[i].x<=ConsoleW+2)
		{
			SetColor(color);
			gotoxy(Object.multi[i].x,Object.multi[i].y);
			cout<<Object.multi[i].s;
		}
	}
	
}
void impact1(Object & Object1, Pos2D & Object2, int left, int right, int mid,int tt,int hp,int point)
{
	for(int i=0;i<25;i++){
			if((((Object2.x-Object1.multi[i].x)<=left&&(Object2.x-Object1.multi[i].x)>=mid)||((Object1.multi[i].x-Object2.x)<=right&&(Object1.multi[i].x-Object2.x)>=mid))&& Object2.y == Object1.multi[i].y)
			{
				Object1.multi[i].x = 40; 
    			Object1.multi[i].y = 0;
    			if(life>=4)life--;
				life+=tt;
				score+=point;
				Object2.hp-=hp;
				if(life==0)endgame=true;
			}
		}
}
void impact2(Object & Object1, Object & Object2,int left, int right)
{
	for(int i=0;i<25;i++){
		for(int j=0;j<25;j++){
			if(((Object1.multi[i].x-Object2.multi[j].x)>= left &&(Object1.multi[i].x-Object2.multi[j].x)<= right )&& Object1.multi[i].y == Object2.multi[j].y)
			{
				Object1.multi[i].x = 40;
				Object1.multi[i].y = 0;
				score++;
				Object2.multi[j].x = 50; 
    			Object2.multi[j].y = 0;
			}
		}
	}
}
void movePlane(Pos2D & Plane)
{
	if (checkKey(KEY_LEFT))
	{
		Plane.x--;
		if(Plane.x < 0) Plane.x++;
	}
    else if (checkKey(KEY_RIGHT))
	{
		Plane.x++;
		if(Plane.x >= ConsoleW) Plane.x--;
	}
    else if (checkKey(KEY_UP))
	{
		Plane.y--;
		if(Plane.y < 0) Plane.y++;
	}
    else if (checkKey(KEY_DOWN))
	{
		Plane.y++;
		if(Plane.y >= ConsoleH) Plane.y--;
	}
	else if(checkKey(KEY_ESC))
		endgame=true;
}

void shoot(Pos2D & Plane,Object & Bullet)
{
	if (checkKey(KEY_A))
	{
		if(bulPlane>0)
		{
			Bullet.multi[iBullet].x=Plane.x+2;
			Bullet.multi[iBullet].y=Plane.y-1;
			iBullet++;
			bulPlane=0;
		}
	}
	if(iBullet==20)iBullet=0;
	
	j++;
	if(j%5==0)bulPlane=1;	
	
	for(int i=0;i<20;i++)
	{
		if(Bullet.multi[i].y>=0&&Bullet.multi[i].y<=ConsoleH&&Bullet.multi[i].x<=ConsoleW+2)
		{
			SetColor(19);
			gotoxy(Bullet.multi[i].x,Bullet.multi[i].y);
			cout<<Bullet.multi[i].s;	
		}
		Bullet.multi[i].y--;
	}
		
}

void cregame()
{
	createMul(Fly,rand()%ConsoleW+1,0,5,15);
	createMul(Item,rand()%ConsoleW+1,0,2,500);
	shoot(Plane,Bullet);
	impact2(Bullet,Fly,0,2);
	impact1(Item,Plane,0,4,0,1,0,0);
	impact1(Fly,Plane,2,4,0,-1,0,1);
	impact1(Bullet,Boss,0,7,0,0,1,0);
	movePlane(Plane);
	if(score!=0&&score%20==0) sumBoss=true;
	if(sumBoss&&Boss.hp>0) sum(Boss,BulletBoss);
	if(Boss.hp==0)
	{
		score+=10;
		sumBoss=false;
		Boss.hp=newBosshp+10;
		newBosshp=Boss.hp;
		if(speedFly>2) speedFly--;
		if(tempFly>10) tempFly--;
	} 
	
}

void drawgame()
{
	SetColor(15);
	for(int i=0;i<=ConsoleH;i++)
	{
		gotoxy(ConsoleW+4,i);
		cout<<(char)179;
	}
	gotoxy(0,ConsoleH);
	for(int i=0;i<ConsoleW+4;i++)
	{
		cout<<"_";
	}
    if(score>0&&score%50==0)sumBoss=true;
    SetColor(6);
    gotoxy(ConsoleW+10, ConsoleH/2);
    cout<<"Score: "<<(score-5)*100;
    gotoxy(ConsoleW+10,ConsoleH/2+1);
    cout<<"Life: ";
    SetColor(12);
    for(int i=0; i<life; i++) cout<<(char)3<<" ";
    draw(Plane,18);
    drawMul(Fly,10);
    drawMul(Item,12);
    if(sumBoss)
	{
		draw(Boss,18);
		drawMul(BulletBoss,16);
	} 
   			
}

int main()
{
	resetgame:;
	ShowCur(false);
	srand(time(NULL));
	Init();
	while(!endgame)
	{	
		clrscr();
		cregame();
		drawgame();
		Sleep(25);
	}
	while(1)
	{
		SetColor(12);
		gotoxy(ConsoleW/2-10,ConsoleH/2+2);
		cout<<"Do you want play again ?";
		gotoxy(ConsoleW/2-10,ConsoleH/2+3);
		cout<<"Press Y: YES  Press N: NO";
		if(checkKey(KEY_Y))goto resetgame;
		if(checkKey(KEY_N))break;
	}
	return 0;
}
