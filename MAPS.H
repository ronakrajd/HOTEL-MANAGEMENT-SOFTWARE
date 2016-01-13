#include<iostream.h>
#include<conio.h>
#include<graphics.h>
class maps {
	   int mapchoice;
	   public:
	   void parking_map();
	   void room_map();
	   }m;
void maps::parking_map()
{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
	setcolor(RED);
	setfillstyle(SOLID_FILL,BLACK);rectangle(50,30,590,450);bar(52,32,588,445);
	setfillstyle(HATCH_FILL,BROWN);rectangle(50,200,100,300);bar(52,202,98,298);
	setfillstyle(CLOSE_DOT_FILL,DARKGRAY);rectangle(50,30,500,200);bar(52,32,498,198);
	setfillstyle(WIDE_DOT_FILL,DARKGRAY);rectangle(50,300,500,450);bar(52,302,498,448);
	setfillstyle(HATCH_FILL,BROWN);rectangle(560,200,590,300);bar(562,202,588,300);
	setfillstyle(SLASH_FILL,LIGHTRED);
	rectangle(520,30,580,80);bar(522,32,578,78); //for lift 1
	rectangle(520,400,580,450);bar(522,402,578,448);//for lift 2
	setcolor(GREEN);
	settextstyle(19,0,5);
	outtextxy(528,50,"LIFT 1");
	outtextxy(528,420,"LIFT 2");
	settextstyle(19,1,5);
	outtextxy(580,220,"E X I T");
	settextstyle(19,0,5);
	outtextxy(100,120,"P A R K I N G   F O R   T W O   W H E E L E R S");
	outtextxy(80,375,"P A R K I N G   F O R   F O U R   W H E E L E R S");
	settextstyle(19,1,5);
	outtextxy(80,215,"ENTERANCE");
	settextstyle(1,0,3);
	setcolor(BROWN);
	outtextxy(100,450,"MAP OF PARKING FLOOR(UNDER GROUND)");
	setfillstyle(SOLID_FILL,WHITE);bar(120,240,220,250);
	setfillstyle(SOLID_FILL,WHITE);bar(270,240,370,250);
	setfillstyle(SOLID_FILL,WHITE);bar(420,240,520,250);
	getch();
	closegraph();
	}
void maps::room_map()
{
int gdriver=DETECT,gmode;initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
setcolor(RED);setfillstyle(SOLID_FILL,BLACK);rectangle(30,30,610,450);
rectangle(30,30,520,210);
rectangle(30,280,520,450);
rectangle(540,30,600,80); //for lift 1
rectangle(540,400,600,450);//for lift 2
setcolor(GREEN);
settextstyle(19,0,5);
outtextxy(542,50,"LIFT  1");
outtextxy(542,420,"LIFT  2");
setcolor(BROWN);
for(int x=30;x<490;x+=70)
rectangle(x,30,x+70,210);
for(int y=30;y<490;y+=70)
rectangle(y,280,y+70,450);
}
