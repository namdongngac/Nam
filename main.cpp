#include<iostream>
#include<stdlib.h>
#include<string.h>
#include "Console.h"
#include<time.h>
#include<stdio.h>

using namespace std;

struct Pos2D{
	char s[20];
	int x,y;
	int hp;
};

const int ConsoleW=25;
const int ConsoleH=25;
bool endgame;
bool sumBoss;
int score,life;
Pos2D Plane;
Pos2D Fly1[20];
Pos2D Bullet[25];
Pos2D BulletFly[20];
Pos2D Boss;
Pos2D item;
int i,j,jz,k,jk,flyshoot;
int iBullet,iFly1,iBulletFly;
int Count,CountItem,CountFly;

//khoi tao mot vai gia tri ban dau
void init(){
	endgame=false;
	sumBoss=false;
	Plane.y=ConsoleH-1; Plane.x=ConsoleW/2;
	Boss.x=rand()%(ConsoleW-12); Boss.y=0;
	score=0,life=3,Boss.hp=20;
	j=0;jz=0;flyshoot=0;k=0;
	iBullet=0; iFly1=1 ;
	Count=1;CountFly=1;CountItem=1;
}

//khoi tao may bay
void drawPlane(){
	SetColor(18);
	gotoxy(Plane.x,Plane.y);
	cout<<">)^(<";
}
//khoi tao dan cua may bat
void drawBullet(){
	for(i=0;i<30;i++){
		strcpy(Bullet[i].s,"|");
	}
}
//khoi tao dan cua Boss
void drawBulletFly(){
	for(i=0;i<20;i++){
		strcpy(BulletFly[i].s,"vv");
	}
}
//khoi tao ruoi
void drawFly1(){
	for(i=0;i<20;i++){
		strcpy(Fly1[i].s,"}0{");
	}
	int temp=rand()%15;
	if(temp==10){
		Fly1[iFly1].x=rand()%ConsoleW; Fly1[iFly1].y=0;
		iFly1++;	
	}
	jz++;
	if(iFly1==19)iFly1=1;
	for(i=0;i<19;i++){
		if(jz%5==0){
			if(Fly1[i].y>=0){
				Fly1[i].y++;
			}
		}
		if(Fly1[i].y>=0&&Fly1[i].y<=ConsoleH&&Fly1[i].x<=ConsoleW+2){
			SetColor(14);
			gotoxy(Fly1[i].x,Fly1[i].y);
			cout<<Fly1[i].s;
		}
	}
	for(i=0;i<19;i++){
			if(((Plane.x == Fly1[i].x||Plane.x+1 == Fly1[i].x||Plane.x+2 == Fly1[i].x||Plane.x+3 == Fly1[i].x||Plane.x+4 == Fly1[i].x)||
			(Plane.x == Fly1[i].x+1||Plane.x+1 == Fly1[i].x+1||Plane.x+2 == Fly1[i].x+1||Plane.x+3 == Fly1[i].x+1||Plane.x+4 == Fly1[i].x+1)||
			(Plane.x == Fly1[i].x+2||Plane.x+1 == Fly1[i].x+2||Plane.x+2 == Fly1[i].x+2||Plane.x+3 == Fly1[i].x+2||Plane.x+4 == Fly1[i].x+2))&&Plane.y == Fly1[i].y){
				score++;
				Fly1[i].x = 40; 
    			Fly1[i].y = 0;
				life--;
				gotoxy(Plane.x,Plane.y-1);
				cout<<"=====";
				if(life==0)endgame=true;
			}
		}	
}
//khoi tao Boss
void drawBoss(){
	strcpy(Boss.s,"=|=[]=|=");	
	SetColor(11);
	gotoxy(Boss.x,Boss.y);
	cout<<Boss.s;
	Boss.y++;
	int ran=rand()%2+1;
	if(ran%2==0){
		Boss.x++;
		if(Boss.x>=ConsoleW-4)Boss.x--;
	}
	if(ran%2==1){
		Boss.x--;
		if(Boss.x<=0)Boss.x++;
	}
	if(Boss.y==3)Boss.y--;
	flyshoot++;
	if(flyshoot%15==0){
		if(CountFly>0){
				BulletFly[iBulletFly].x=Boss.x+3;
				BulletFly[iBulletFly].y=Boss.y+1;
				iBulletFly++;
				CountFly--;
		}
	}
	k++;
	if(k%5==0)if(CountFly<1)CountFly++;	
	if(iBulletFly==19)iBulletFly=0;
		
	for(i=0;i<20;i++){
		if(BulletFly[i].y>=0&&BulletFly[i].y<=ConsoleH&&BulletFly[i].x<=ConsoleW+2){
			SetColor(14);
			gotoxy(BulletFly[i].x,BulletFly[i].y);
			cout<<BulletFly[i].s;
			
		}
	}
	for(i=0;i<20;i++){
		BulletFly[i].y++;
		
			if((BulletFly[i].x == Plane.x || BulletFly[i].x == Plane.x+1 || BulletFly[i].x == Plane.x+2||BulletFly[i].x == Plane.x+3||BulletFly[i].x == Plane.x+4||
				BulletFly[i].x+1==Plane.x || BulletFly[i].x+1==Plane.x+1 || BulletFly[i].x+1==Plane.x+2||BulletFly[i].x+1==Plane.x+3||BulletFly[i].x==Plane.x+4) && BulletFly[i].y == Plane.y){
				BulletFly[i].x=40;
				BulletFly[i].y=0;
				life--;
				for(i=0;i<shield;i++){
					shield--;
				}
				if(shield>0){
					gotoxy(Plane.x,Plane.y-1);
					cout<<"=====";
				}
				if(life==0)endgame=true;
				
			}
	}
		
}
void drawitem(){
	int ran=rand()%500;
	if(ran==50){
		item.x=rand()%ConsoleW;
		item.y=0;		
	}
	if(item.y>=0&&item.y<=ConsoleH&&item.x<=ConsoleW){
		SetColor(12);
		gotoxy(item.x,item.y);
		cout<<(char)3;
		item.y++;
	}
	if(((item.x-Plane.x)>=0&&(item.x-Plane.x)<=4 )&& item.y == Plane.y){
		if(life<5)life++;
		item.x=40;
		item.y=0;
	}
}
//dieu khien may bay
void controlPlane(){
	if (checkKey(KEY_LEFT)){
		Plane.x--;
		if(Plane.x<0)Plane.x++;
	}
    else if (checkKey(KEY_RIGHT)){
		Plane.x++;
		if(Plane.x>=ConsoleW)Plane.x--;
	}
    else if (checkKey(KEY_UP)){
		Plane.y--;
		if(Plane.y<0)Plane.y++;
	}
    else if (checkKey(KEY_DOWN)){
		Plane.y++;
		if(Plane.y>=ConsoleH)Plane.y--;
	}
}

//ban va kiem tra dan
void shoot(){
		
	if (checkKey(KEY_A)){
		if(Count>0){
			Bullet[iBullet].x=Plane.x+2;
			Bullet[iBullet].y=Plane.y-1;
			iBullet++;
			Count--;
		}
	}
	j++;
	if(j%5==0)if(Count<1)Count++;	
	if(iBullet==25)iBullet=0;
		
	for(i=0;i<25;i++){
		if(Bullet[i].y>=0&&Bullet[i].y<=ConsoleH&&Bullet[i].x<=ConsoleW+2){
			SetColor(19);
			gotoxy(Bullet[i].x,Bullet[i].y);
			cout<<Bullet[i].s;	
		}
	}
	
	for(i=0;i<25;i++){
		Bullet[i].y--;
		//kiem tra dan voi ruoi loai 1
		for(int n=0;n<19;n++){
			if(((Bullet[i].x-Fly1[n].x)>=0&&(Bullet[i].x-Fly1[n].x)<=2 )&& Bullet[i].y == Fly1[n].y){
				Bullet[i].x=40;
				Bullet[i].y=0;
				score++;
				Fly1[n].x = 40; 
    			Fly1[n].y = 0;
			}
		}
		//kiem tra dan voi Boss
		if(((Bullet[i].x-Boss.x)>=0&&(Bullet[i].x-Boss.x)<=7 )&& Bullet[i].y == Boss.y){
			Bullet[i].x=40;
			Bullet[i].y=0;
			Boss.hp--;
			if(Boss.hp<=0){
				Boss.x = rand()%15; 
    			Boss.y = 0;
				score+=10;
			}	
		}	
	}	
}
//khoi tao man hinh game
void drawgame(){
	clrscr();
	SetColor(15);
	for(i=0;i<=ConsoleH;i++){
		gotoxy(ConsoleW+4,i);
		cout<<(char)179;
	}
	gotoxy(0,ConsoleH);
	for(i=0;i<ConsoleW+4;i++){
		cout<<"_";
	}
	drawPlane();
    drawFly1();
    if(score>0&&score%50==0)sumBoss=true;
    drawBulletFly();
    drawBullet();
    drawitem();
    SetColor(6);
    gotoxy(ConsoleW+10, ConsoleH/2);
    cout<<"Score: "<<score*100;
    gotoxy(ConsoleW+10,ConsoleH/2+1);
    cout<<"Life: ";
    SetColor(12);
    for(int h=0;h<life;h++)cout<<(char)3<<" ";
    if(checkKey(KEY_ESC))endgame=true;
}
//khoi tao man hinh danh Boss
void drawgameBoss(){
	clrscr();
	SetColor(15);
	for(i=0;i<=ConsoleH;i++){
		gotoxy(ConsoleW+4,i);
		cout<<(char)179;
	}
	gotoxy(0,ConsoleH);
	for(i=0;i<ConsoleW+4;i++){
		cout<<"_";
	}
	drawPlane();
    drawBoss();
    drawBulletFly();
    drawBullet();
    SetColor(6);
    gotoxy(ConsoleW+10, ConsoleH/2);
    cout<<"Score: "<<score*100;
    gotoxy(ConsoleW+10,ConsoleH/2+1);
    cout<<"Life: ";
    SetColor(12);
    for(int h=0;h<life;h++)cout<<(char)3<<" ";
    if(checkKey(KEY_ESC))endgame=true;
}

//ham main
int main(){
	resetgame:;
	ShowCur(false);
	init();
	srand(time(NULL));
	reset:;
	while(!endgame){	
		drawgame();
		controlPlane();
		shoot();
		if(sumBoss)	break;
		Sleep(25);
	}
	while(!endgame){
		drawgameBoss();
		controlPlane();
		shoot();
		if(Boss.hp<=0){
			sumBoss=false;
			Boss.hp=20;
			goto reset;
		}
		Sleep(25);
	}
	if(endgame){
		gotoxy(ConsoleW/2-4,ConsoleH/2);
		cout<<"GameOver\n\n\n";
	}
	while(1){
		gotoxy(ConsoleW/2-10,ConsoleH/2+2);
		cout<<"Do you want play again ?";
		gotoxy(ConsoleW/2-10,ConsoleH/2+3);
		cout<<"Press Y: YES  Press N: NO";
		if(checkKey(KEY_Y))goto resetgame;
		if(checkKey(KEY_N))break;
	}
	return 0;
}
