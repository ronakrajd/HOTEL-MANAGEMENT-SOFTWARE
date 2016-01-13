#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<process.h>
#include<graphics.h>
#include<time.h>
#include<dos.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<maps.h>
int gdriver=DETECT,gmode;
void stpage();
void password();
void maincontrol();
void mainmenu();
void editmenu();
void editroomrecord();
void wrongchoice();
void  reportmenu();
void thanks();
int func1(int);
int modifyvalue=1;
char choice=9;
char single;
void drawbar();
void verline(int row1, int column, int row2)
{
 for(row1;row1<=row2;row1++)
 {
  gotoxy(column,row1);
  cout<<(char)179;
 }
}
void horline(int column1, int row, int column2)
{
 for(column1;column1<=column2;column1++)
 {
  gotoxy(column1,row);
  cout<<(char)196;
 }
}
void createbox()
{
 gotoxy(2,1);
 cout<<(char)218;
 gotoxy(2,25);
 cout<<(char)192;
 gotoxy(79,1);
 cout<<(char)191;
 gotoxy(79,25);
 cout<<(char)217;
 verline(2,2,24);
 verline(2,79,24);
 horline(3,1,78);
 horline(3,25,78);
}
void createbox2()
{
 gotoxy(18,5);
 cout<<(char)218;
 gotoxy(18,24);
 cout<<(char)192;
 gotoxy(60,5);
 cout<<(char)191;
 gotoxy(60,24);
 cout<<(char)217;
 verline(6,18,23);
 verline(6,60,23);
 horline(19,5,59);
 horline(19,24,59);
 horline(19,7,59);
 verline(6,26,23);
 verline(6,53,23);
 gotoxy(21,6);cout<<"CODE";
 gotoxy(34,6);cout<<"FOOD NAME";
 gotoxy(54,6);cout<<"PRICE";
}
void printdate()
{
   struct date d;
  getdate(&d);
  struct dostime_t t;
  _dos_gettime(&t);
  int hour;
  if(t.hour>=12&&t.minute>=00)
   {
	gotoxy(65,2);printf("Time: %2d:%02dPM\n", t.hour, t.minute);
	if(t.hour>12&&t.minute>00)
		{
		hour=t.hour-12;
		gotoxy(65,2);printf("Time: %2d:%02dPM\n", hour, t.minute);
		}
   }
  else
  {
	gotoxy(65,2);printf("Time: %2d:%02dAM\n", t.hour, t.minute);
  }
  gotoxy(65,1);cout<<"Date:";cprintf("%d", d.da_day);cprintf("/%d", d.da_mon);cprintf("/%d", d.da_year);
 gotoxy(1,23);cout<<"Information Bar:";
 }
class custrecord{
	       int room_no;
	       int book_no;
	       char name[30];
	       char address[25];
	       char nationality[20];
	       char m_no[15];
	       char passport_no[15];
	       long  advance;
	       int d1_day;     /* day of the month */
	       int d1_mon;     /* month (1 = Jan) */
	       int d1_year;     /* current year */
	       long rserviceb;
	       public:
	       int result;
	       ~custrecord(){}
	       int check(int rno) //used to check whether the room already exist or not
		{
		 fstream rrco;
		 rrco.open("rooms.dat",ios::in);
		 while(rrco.read((char*)&rrec,sizeof(rrec)))
		 {
		   if(rno==rrec.getrroom_no()&&rrec.getroom_status()=='V')
		   {
		    result=1;
		    break;
		   }
		 }
		 return result;
		}
	       void input_customer_data(char choice);
	       void calbill(long pos);
	       void room_service();
	       void set_room_status(int rno);
	       void chot_set_room_status(int rno);
	       void displaybox();
	       void display();
	       void view_custrecord();
	       void filecustomer(char choice);
	       void ccheck();
	       void dispcust();
	       int get_roomno()
	       {
		 return room_no;
	       }

	     }crec;
class edit{
	       int room_no;
	       char name[50];
	       int book_no;
	       char passport_no[10];
	       char m_no[12];
	       long  advance;
	       char address[80];
	       char nationality[20];
	       public:
	       void cust_recordmodify();
	       void room_recordmodify();
	       int getroom_no()
	       {
		 return room_no;
	       }
	       };
class roomrecord{
	    int  rroom_no;
	    char room_status;
	    char room_type[5];
	   long   room_tarrif;
	    public:
	    int result;//0 for room not found
	    void input_room_data();//used to get the data of the room
	    void fileroom(); //used to store the data of rooms in the file
	    void room_file_modify();
	    void delete_room_record();
	    long returntarrif(int);
	    void show_rooms();
	    int recordfound(int t_roomno);
	    void view_roomrecord();
	    void disproom();
	    void change_room_status()
	    {
	     room_status='O';
	    }
	    void chot_change_room_status()
	    {
	     room_status='V';
	    }

	    int getrroom_no()
	    {
	     return rroom_no;
	    }
	    char getroom_status()
	    {
	     return room_status;
	    }
	    unsigned int getroom_tarrif()
	    {
	     return room_tarrif;
	    }
	    int check(int rno) //used to check whether the room already exist or not
		{
		 fstream rrco;
		 rrco.open("rooms.dat",ios::in);
		 while(rrco.read((char*)&rrec,sizeof(rrec)))
		 {
		   if(rno==rrec.getrroom_no())
		   {
		    result=1;
		    break;
		   }
		 }
		 return result;
		}
	  }rrec;
class view_record:public custrecord
		{
		   public:
		   void get_recordinfo(char type);
		   void display_record();
		}vrec;
class checkout{
		public:
		void chekout();
		void calbill();
	      }chot;
class income{
	     int i_day,i_mon,i_year;
	     long double room_rent,rsbill;
	     public:
	     void daily_income(long r_rent,long r_service);
	     void dis_daily_income();
	    }din;
main()
{
stpage();
password();
mainmenu();
getch();
}
void drawbar()
{
setcolor(GREEN);
rectangle(400,50,getmaxx(),350);
setfillstyle(SOLID_FILL,BLACK);
bar(405,55,getmaxx()-2,345);
settextstyle(3,0,2);setcolor(LIGHTCYAN);outtextxy(415,60,"INFORMATION WINDOW");
setcolor(LIGHTRED);
outtextxy(425,355,"Instruction Window");
settextstyle(2,0,5);setcolor(LIGHTMAGENTA);
}

void mainmenu()
{
   closegraph();
clrscr();
int gdriver=DETECT,gmode;
LABEL:
initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
setcolor(GREEN);
rectangle(10,10,getmaxx(),getmaxy());
rectangle(10,50,getmaxx(),getmaxy());
drawbar();
settextstyle(4,0,3);setcolor(LIGHTGRAY);
outtextxy(415,385,"To select press Enter");
setcolor(GREEN);
rectangle(400,350,getmaxx(),getmaxy());
settextstyle(3,0,5);
setcolor(RED);outtextxy(280,0,"MENU");
settextstyle(3,0,2);
settextstyle(2,0,7);
setcolor(LIGHTBLUE);outtextxy(40,95,"MAPS");
setcolor(GREEN);outtextxy(40,135,"INTRODUCTION");
setcolor(YELLOW);outtextxy(40,175,"CHECK IN");
setcolor(BROWN);outtextxy(40,215,"EDIT");
setcolor(CYAN);outtextxy(40,255,"CUSTOMER RECORD");
setcolor(MAGENTA);outtextxy(40,295,"ROOM RECORD");
setcolor(LIGHTGREEN);outtextxy(40,335,"REPORT");
setcolor(LIGHTRED);outtextxy(40,375,"CHECK OUT");
setcolor(LIGHTMAGENTA);outtextxy(40,415,"ROOM SERVICE");
setcolor(LIGHTGRAY);outtextxy(40,455,"EXIT");
	int count=0,option_code;
	int x=20,y=95;
	setcolor(LIGHTRED);
	outtextxy(x,y,"¯");drawbar();
	outtextxy(405,90,"Displays the maps of the hotel");
	outtextxy(405,105,"Room Status Colour code:");
	outtextxy(405,120,"1.Green=Vacant");
	outtextxy(405,135,"2.Blue=Occupied");
	char W;
	do
	{
	 count++;
	 W=getch();
	 if(W=='\0'+'H')
	 {
	  settextstyle(2,0,7);setcolor(BLACK);
	  outtextxy(x,y,"¯");
	  y-=40;
	  if(y<95)
	  {
	   y=455;
	  settextstyle(2,0,7); setcolor(WHITE);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"To exit from the software");
	   option_code=10;
	  }
	  else if(y==95)
	  {
	  settextstyle(2,0,7); setcolor(LIGHTRED);
	   outtextxy(x,y,"¯"); drawbar();
	   outtextxy(405,90,"Displays the maps of the hotel");
	   outtextxy(405,105,"Room Status Colour code:");
	   outtextxy(405,120,"1.Green=Vacant");
	   outtextxy(405,135,"2.Blue=Occupied");
	   option_code=1;
	  }
	  else if(y==135)
	  {
	  settextstyle(2,0,7); setcolor(RED);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Gives the information of the"); outtextxy(405,105,"programmer,hotel,software");
	   option_code=2;
	  }
	  else if(y==175)
	  {
	  settextstyle(2,0,7); setcolor(BLUE);
	   outtextxy(x,y,"¯"); drawbar();
	   outtextxy(405,90,"To be used to check in the");outtextxy(405,105,"customer");
	   option_code=3;
	  }
	  else if(y==215)
	  {
	  settextstyle(2,0,7); setcolor(DARKGRAY);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Displays the edit menu");outtextxy(405,105,"having options to edit the");
	   outtextxy(405,120,"customer and room records");
	   option_code=4;
	  }
	  else if(y==255)
	  {
	  settextstyle(2,0,7); setcolor(CYAN);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Displays the record of a");outtextxy(405,105,"customer staying in the hotel");
	   outtextxy(405,120,"by getting the room number");
	   option_code=5;
	  }
	  else if(y==295)
	  {
	  settextstyle(2,0,7); setcolor(MAGENTA);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Displays the complete informati");outtextxy(405,105,"on of a room including current");
	   outtextxy(405,120,"status by getting the room");
	   outtextxy(405,135,"number");
	   option_code=6;
	  }
	  else if(y==335)
	  {
	  settextstyle(2,0,7); setcolor(GREEN);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Gateway to report menu");outtextxy(405,105,"which has the following option:");
	   outtextxy(405,120,"1.Display customers records");
	   outtextxy(405,135,"2.Display room records");
	   outtextxy(405,150,"3.Daily income(till today)");
	   option_code=7;
	  }
	  else if(y==375)
	  {
	  settextstyle(2,0,7); setcolor(BROWN);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Creates the bill of the");outtextxy(405,105,"customer leaving hotel");
	   outtextxy(405,120,"also writes the checked out");
	   outtextxy(405,135,"record into the database");
	   option_code=8;
	  }
	  else if(y==415)
	  {
	  settextstyle(2,0,7); setcolor(LIGHTBLUE);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Provides the facility to add the");outtextxy(405,105,"room service bill to customer's");
	   outtextxy(405,120,"account also shows the list of the");
	   outtextxy(405,135,"items included in the room");
	   outtextxy(405,150,"service");
	   option_code=9;
	  }
	  else if(y==455)
	  {
	  settextstyle(2,0,7); setcolor(LIGHTGREEN);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"To exit from the software");
	   option_code=10;
	  }

	 }
	 else if(W=='\0'+'P')
	 {
	  settextstyle(2,0,7);setcolor(BLACK);
	  outtextxy(x,y,"¯"); drawbar();
	  y+=40;
	  if(y>455)
	  {
	   y=95;
	  settextstyle(2,0,7); setcolor(LIGHTRED);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Displays the maps of the hotel");
	   option_code=1;
	  }
	  else if(y==95)
	  {
	  settextstyle(2,0,7); setcolor(LIGHTRED);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Displays the maps of the hotel");
	   option_code=1;
	  }
	  else if(y==135)
	  {
	  settextstyle(2,0,7); setcolor(RED);
	   outtextxy(x,y,"¯"); drawbar();
	   outtextxy(405,90,"Gives the information of the"); outtextxy(405,105,"programmer,hotel,software");
	   option_code=2;
	  }
	  else if(y==175)
	  {
	  settextstyle(2,0,7); setcolor(BLUE);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"To be used to check in the");outtextxy(405,105,"customer");
	   option_code=3;
	  }
	  else if(y==215)
	  {
	  settextstyle(2,0,7); setcolor(DARKGRAY);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Displays the edit menu");outtextxy(405,105,"having options to edit the");
	   outtextxy(405,120,"customer and room records");
	   option_code=4;
	  }
	  else if(y==255)
	  {
	  settextstyle(2,0,7); setcolor(CYAN);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Displays the record of a");outtextxy(405,105,"customer staying in the hotel");
	   outtextxy(405,120,"by getting the room number");

	   option_code=5;
	  }
	  else if(y==295)
	  {
	  settextstyle(2,0,7); setcolor(MAGENTA);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Displays the complete informati");outtextxy(405,105,"on of a room including current");
	   outtextxy(405,120,"status by getting the room");
	   outtextxy(405,135,"number");
	   option_code=6;
	  }
	  else if(y==335)
	  {
	  settextstyle(2,0,7); setcolor(GREEN);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Gateway to report menu");outtextxy(405,105,"which has the following option:");
	   outtextxy(405,120,"1.Display customers records");
	   outtextxy(405,135,"2.Display room records");
	   outtextxy(405,150,"3.Daily income(till today)");
	   option_code=7;
	  }
	  else if(y==375)
	  {
	  settextstyle(2,0,7); setcolor(BROWN);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Creates the bill of the");outtextxy(405,105,"customer leaving hotel");
	   outtextxy(405,120,"also writes the checked out");
	   outtextxy(405,135,"record into the database");
	   option_code=8;
	  }
	  else if(y==415)
	  {
	  settextstyle(2,0,7); setcolor(LIGHTBLUE);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"Provides the facility to add the");outtextxy(405,105,"room service bill to customer's");
	   outtextxy(405,120,"account also shows the list of the");
	   outtextxy(405,135,"items included in the room");
	   outtextxy(405,150,"service");
	   option_code=9;
	  }
	  else if(y==455)
	  {
	  settextstyle(2,0,7); setcolor(LIGHTGREEN);
	   outtextxy(x,y,"¯");drawbar();
	   outtextxy(405,90,"To exit from the software");
	   option_code=10;
	  }

	 }
	 else if(count==1&&W==13)
	 {
	  closegraph();
	  m.parking_map();
	  m.room_map();
	  rrec.show_rooms();
	  goto LABEL;
	 }
	}while(W!=13);
	closegraph();
switch(option_code)
{
 case 2:stpage();mainmenu();
	break;
 case 3:custrecord chi;
	chi.filecustomer('c');mainmenu();
	break;
 case 4:editmenu();mainmenu();
	break;
 case 5:crec.view_custrecord();mainmenu();
	break;
 case 6:rrec.view_roomrecord();mainmenu();
	break;
 case 7:reportmenu();
	break;
 case 8:chot.chekout();mainmenu();
	break;
 case 9:crec.room_service();mainmenu();
	break;
 case 10:thanks();exit(0);
 break;
}
getch();
closegraph();
}
void custrecord::room_service()
{
	int price[113]={245,245,245,245,240,240,240,240,235,235,250,235,235,
	220,215,230,215,240,250,250,250,250,250,250,250,255,245,245,245,245,
	250,240,240,360,290,360,290,370,295,360,290,360,290,250,360,290,360,
	290,250,370,290,360,290,250,250,280,245,290,235,265,240,290,300,256,
	240,265,270,255,255,240,240,235,220,25,30,25,30,35,35,25,30,35,25,35,
	25,25,30,100,105,105,100,105,100,105,125,105,105,100,105,110,115,100,
	100,100,105,105,105,105,125,105,120,120,100};
	char food[113][30]={"SHAHI PANEER","KADAI PANEER","CHEESE KORMA",
	"MALAI KOFTA","MATAR PANEER","PALAK PANEER","MIX VEG.","ALOO GOBI",
	"ALOO JEERA","CHANA MASALA","MATAR MUSHROOM","RAJMA MAKHANI",
	"DAL MAKHANI","MIXED RAITA","BUNDI RAITA","PINEAPPLE RAITA",
	"SALAD(GREEN)","DUM ALOO","MUSHROOM PANEER","MUTTON MASALA",
	"MUTTON MUGHLAI","MUTTON KORMA","MUTTON DO PYAZA","MUTTON SAGH",
	"MUTTON DAHI","MUTTON ROGAN JOSH","MUTTON CURRY","KADAI MUTTON",
	"KEEMA LEVER","KEEMA MATAR","KEEMA EGG","BRAIN CURRY","EGG CURRY",
	"BUTTER CHICKEN","BUTTER CHICKEN(1/2)","KADAI CHICKEN",
	"KADAI CHICKEN(1/2)","BUTTER CHICKEN(BL)","BUTTER CHICKEN(BL)(1/2)",
	"CHICKEN MUGHLAI","CHICKEN MUGHLAI(1/2)","CHICKEN MASALA",
	"CHICKEN MASALA(1/2)","CHICKEN MASALA(1/4)","CHICKEN SAGH",
	"CHICKEN SAGH(1/2)","CHICKEN DAHI","CHICKEN DAHI(1/2)",
	"CHICKEN DAHI(1/4)","CHICKEN KORMA","CHICKEN KORMA(1/2)",
	"CHICKEN DO PYAZA","CHICKEN DO PYAZA(1/2)","FISH CURRY",
	"CHICKEN CURRY","CHICKEN CURRY(1/2)","CHICKEN CURRY(1/4)",
	"CHILLI CHICKEN","TANDOORI ALOO","CHICKEN TIKKA","SEEKH KABAB",
	"FISH TIKKA","CHICKEN TANDOORI","CHICKEN TANDOORI(1/2)",
	"PANEER TIKKA","CHICKEN SEEKH KABAB","CHICKEN HARA KABAB",
	"CHICKEN BIRYANI","MUTTON BIRYANI","PANEER PULAO","VEG.PULAO",
	"JEERA RICE","STEAMED RICE","RUMALI ROTI","ROTI","NAN","ALOO NAN",
	"PANEER NAN","KEEMA NAN","PARANTHA","ALOO PARANTHA",
	"PANEER PARANTHA","PUDINA PARANTHA","BUTTER NAN","LACHCHA PARANTHA",
	"MISSI ROTI","KHASTA ROTI","VEG.BURGER","PANEER BURGER",
	"CHEESE SANDWICH","VEG.PATTI","CHICKEN PATTI","TEA","COFFEE",
	"COLD COFFEE","PINEAPPLE","STRAWBERRY","CHOCOLATE","BLACK FOREST",
	"DOUBLE STORIED","TRIPLE STORIED","SOFT CONE","VANILLA","STRAWBERRY",
	"CHOCOLATE","CHOCO CHIPS","MANGO","TUTTI FRUITY","LICHI",
	"PISTA BADAM","CHOCOLATE PISTA BADAM","CHOCO DIP","CHOCOLATE LICHI"};
	START:
	textcolor(4);
	clrscr();createbox2();
	gotoxy(31,1); cout<<"*********";
	gotoxy(31,2); cout<<"MENU CARD";
	gotoxy(31,3); cout<<"*********";
	gotoxy(34,4); cout<<"VEGETARIAN";
	for(int i=0,j=8;i<16;i++,j++)
	{
	  gotoxy(20,j); cout<<i+1;
	  gotoxy(30,j); cout<<food[i];
	  gotoxy(55,j); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();createbox2();
	for(i=16,j=8;i<19;i++,j++)
	{
	  gotoxy(20,j); cout<<i+1;
	  gotoxy(30,j); cout<<food[i];
	  gotoxy(55,j); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();createbox2();
	gotoxy(34,3); cout<<"MUTTON";
	for(i=19,j=8;i<33;i++,j++)
	{
	  gotoxy(20,j); cout<<i+1;
	  gotoxy(30,j); cout<<food[i];
	  gotoxy(55,j); cout<<price[i];
	}
	gotoxy(25,25) ;cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();createbox2();
	gotoxy(34,3); cout<<"CHICKEN";
	for(i=33,j=8;i<48;i++,j++)
	{
	  gotoxy(20,j); cout<<i+1;
	  gotoxy(30,j); cout<<food[i];
	  gotoxy(55,j); cout<<price[i];
	}
	gotoxy(25,25) ;cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();createbox2();
	for(i=48,j=8;i<58;i++,j++)
	{
	  gotoxy(20,j); cout<<i+1;
	  gotoxy(30,j); cout<<food[i];
	  gotoxy(55,j); cout<<price[i];
	}
	gotoxy(25,25) ;cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();createbox2();
	gotoxy(34,3); cout<<"BAR-BE-QUE";
	for(i=58,j=8;i<73;i++,j++)
	{
	  gotoxy(20,j); cout<<i+1;
	  gotoxy(30,j); cout<<food[i];
	  gotoxy(55,j); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();createbox2();
	gotoxy(34,3); cout<<"ROTI-NAN-PARANTHA";
	for(i=73,j=8;i<88;i++,j++)
	{
	  gotoxy(20,j); cout<<i+1;
	  gotoxy(30,j); cout<<food[i];
	  gotoxy(55,j); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();createbox2();
	for(i=88,j=8;i<92;i++,j++)
	{
	  gotoxy(20,j); cout<<i+1;
	  gotoxy(30,j); cout<<food[i];
	  gotoxy(55,j); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();createbox2();
	gotoxy(34,3); cout<<"BEVERAGES";
	for(i=92,j=8;i<95;i++,j++)
	{
	  gotoxy(20,j); cout<<i+1;
	  gotoxy(30,j); cout<<food[i];
	  gotoxy(55,j); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();createbox2();
	gotoxy(34,3) ;cout<<"PASTRIES";
	for(i=95,j=8;i<101;i++,j++)
	{
	  gotoxy(20,j); cout<<i+1;
	  gotoxy(30,j); cout<<food[i];
	  gotoxy(55,j); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();createbox2();
	gotoxy(34,3); cout<<"ICE-CREAMS";
	for(i=101,j=8;i<113;i++,j++)
	{
	  gotoxy(20,j); cout<<i+1;
	  gotoxy(30,j); cout<<food[i];
	  gotoxy(55,j); cout<<price[i];
	}
	gotoxy(25,25);cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();createbox2();
	int answ,fc,fch[113],z=-1;
	long fe=0;
	char fi[113][30],answe;
	RETRY:
	clrscr();
	cout<<"PRESS 0 TO GO BACK TO MENU CARD\n"
	    <<"PRESS 1 TO CONTINUE ";
	cin>>answ;
	switch(answ)
	{
	  case 0 : goto START;
		   break;
	  case 1 : clrscr();
		   do
		   {
		     z++;
		     cout<<"ENTER THE FOOD CODE YOU WANT TO HAVE :: ";
		     cin>>fc;
		     fch[z]=price[fc-1];
		     fe+=price[fc-1];
		     strcpy(fi[z],food[fc-1]);
		     cout<<"DO YOU WANT MORE(Y/N) :: ";
		     cin>>answe;
		   } while(answe=='y' || answe=='Y');
		   clrscr();
		   for(int y=0;y<z+1;y++)
		   {
		     cout<<fi[y];
		     gotoxy(40,y+1); cout<<fch[y]<<"\n";
		   }
		   cout<<"TOTAL";
		   gotoxy(40,y+1); cout<<fe<<"\n";
		   cout<<"ARE YOU STAYING IN THIS HOTEL (Y/N) ? ";
		   char ans;
		   cin>>ans;

		   if(ans=='y' || ans=='Y')
		   {
		     char na[30];
		     int rn;
		     cout<<"ROOM NO. :: ";
		     cin>>rn;
		     cout<<"NAME     :: ";
		     gets(na);
		     for(i=0;na[i]!='\0';i++) na[i]=toupper(na[i]);
		     //VERIFYING THE ENTERED DATA
		     fstream f1;
		     f1.open("CUSTOMER.DAT",ios::in|ios::out);
		     long pos=0;
		     while(f1.read((char *)&crec,sizeof(crec)))
		     {
		       if(crec.room_no==rn && strcmp(crec.name,na)==0)
		       {
			goto BILL;
		       }
		      pos=f1.tellg();
		     }
		     f1.close();
		     cout<<"ENTERED DATA IS NOT MATCHING THE ACTUAL DATA";
		     gotoxy(25,25); cout<<"PRESS ANY KEY AFTER PAYING THE BILL ";
		     getch();
		     return;
		     BILL:
		     crec.rserviceb+=fe;
		     f1.seekg(0);
		     f1.seekg(pos);
		     f1.write((char *)&crec,sizeof(crec));
		     f1.close();
		     cout<<"\nTHE RESTAURANT BILL HAS BEEN ENTERED INTO YOUR RECORD";
		   }
		   else
		   {
		     gotoxy(25,25);
		     cout<<"PRESS ANY KEY AFTER PAYING THE BILL ";
		     din.daily_income(0,fe);
		     getch();
		     return;
		   }
		   gotoxy(25,25);
		   cout<<"PRESS ANY KEY TO CONTINUE";
		   getch();
		   break;
	  default: cout<<"YOU HAVE PRESSED A WRONG KEY\nRETRY\n";
		   getch();
		   goto RETRY;
	}
	clrscr();
}
void editmenu()
{
   closegraph();
   initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
   ifstream mamen;
   mamen.open("editmenu",ios::in);
   char line[50];
   int y=20;
   cleardevice();
   while(!mamen.eof())
    {
      mamen.getline(line,50);
      if(y==20)
	{
	  settextstyle(8,0,4);setcolor(GREEN);
	  outtextxy(140,y,line);
	  y+=20;
	  continue;
	}
      settextstyle(4,0,4);
      setcolor(LIGHTBLUE);
      outtextxy(180,y,line);
      y+=50;
    }
   settextstyle(4,0,3);setcolor(RED);
   outtextxy(50,240,"Please Enter Your Choice");
   mamen.close();
   do{
      choice=getch();
      switch(choice)
      {
	case '1':editroomrecord();
		 break;
	case '2':edit ed;
		 ed.cust_recordmodify();
		 break;
	case '3':mainmenu();
		 break;
	default :wrongchoice();
		 editmenu();
		 break;
      }
   }while(choice!=9);
}
void editroomrecord()
{
  closegraph();
  initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
  fstream mamn;
   mamn.open("rrecord",ios::in);
   char line[50];
   int y=20;

   while(!mamn.eof())
    {
      mamn.getline(line,50);
      if(y==20)
	{
	  settextstyle(8,0,4);setcolor(RED);
	  outtextxy(140,y,line);
	  y+=50;
	  continue;
	}
      settextstyle(4,0,4);
      setcolor(CYAN);
      outtextxy(180,y,line);
      y+=50;
    }
   settextstyle(4,0,3);setcolor(RED);
   outtextxy(50,270,"Please Enter Your Choice");
   mamn.close();
   do{
      choice=getch();
      switch(choice)
      {
	case '1':rrec.input_room_data();
		 rrec.fileroom();
		 editroomrecord();
		 break;
	case '2':rrec.room_file_modify();
		 editroomrecord();
		 break;
	case '3':rrec.delete_room_record();
		 editroomrecord();
		 break;
	case '4':editmenu();
		 break;
	default :wrongchoice();
		 editroomrecord();
		 break;
      }
   }while(choice!=9);
}
void reportmenu()
{
 men:
 clrscr();
 gotoxy(35,3);cout<<"==REPORT MENU==";
 gotoxy(20,5);cout<<"1.CUSTOMER RECORDS";
 gotoxy(20,6);cout<<"2.ROOM RECORDS";
 gotoxy(20,7);cout<<"3.DAILY INCOME RECORDS(TILL TODAY)";
 gotoxy(20,8);cout<<"4.BACK";
 gotoxy(19,11);cout<<"Enter your choice:";
 cin>>choice;
 switch(choice)
 {
  case '1':crec.dispcust();
	   goto men;
	   break;
  case '2':rrec.disproom();
	   goto men;
	   break;
  case '3':din.dis_daily_income();
	   goto men;
	   break;
  case '4':mainmenu();
	 break;
  default:gotoxy(20,12);cout<<"ENTER CORRECT NUMBER";
 }
}
void wrongchoice()
{
  closegraph();
  initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
  settextstyle(4,0,4);
  outtextxy(50,200,"Enter the correct choice.Press any key...");
  getch();
  return;
}
void stpage()
{
initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
settextstyle(10,0,2);
setcolor(LIGHTMAGENTA);
rectangle(10,10,getmaxx(),getmaxy());
setcolor(YELLOW);
outtextxy(20,20,"KENDRIYA VIDYALAYA NO.1,UDAIPUR");
outtextxy(220,60,"RAJASTHAN");
settextstyle(6,0,3);
setcolor(GREEN);
outtextxy(50,150,"Computer Science Project-'HOTEL MANAGEMENT SYSTEM'");
settextstyle(8,0,3);
setcolor(LIGHTRED);
outtextxy(20,240,"Submitted to and");
outtextxy(20,270,"under guidance of-");
settextstyle(1,0,3);
setcolor(BROWN);
outtextxy(20,310,"Mrs.K.Acharya");
outtextxy(20,340,"(TGT COMP. SCIENCE)");
settextstyle(8,0,3);
setcolor(LIGHTRED);
outtextxy(380,240,"Developed by-");
settextstyle(1,0,3);
setcolor(BROWN);
outtextxy(380,310,"Ronak Raj Doongarwal");
outtextxy(420,340,"XII-A");
getch();
closegraph();
initgraph(&gdriver, &gmode, "C:\\TC\\BGI");
ifstream fil;
fil.open("intro",ios::in);
initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
char line[70];
int y=20;
setcolor(LIGHTRED);
rectangle(10,5,getmaxx(),getmaxy());
setcolor(LIGHTRED);
while(!fil.eof())
{
fil.getline(line,70);
if((y==20)||(y==420))
{settextstyle(8,0,3);setcolor(CYAN);}
outtextxy(50,y,line);
setcolor(LIGHTRED);
settextstyle(6,0,3);
y+=40;
}
fil.close();
getch();
closegraph();
initgraph(&gdriver, &gmode, "C:\\TC\\BGI");
 settextstyle(4,0,10);
       setcolor(LIGHTRED);
 outtextxy(50,0,"hotel");
  outtextxy(150,120,"horizon");
      setcolor(BROWN);
	settextstyle(8,0,3);
	outtextxy(170,350,"LOADING PLEASE WAIT");
  rectangle(10,10,getmaxx(),getmaxy());
      rectangle(getmaxx()/2-100,395,(getmaxx()/2)+100,415);
      setviewport((getmaxx()/2)-98,400,(getmaxx()/2)+98,410,1);
 int i=0;
 while(i<(getmaxx()/2)-120)
   {
      clearviewport();
      /* set the fill style */
      setfillstyle(INTERLEAVE_FILL,LIGHTGREEN);
	/* draw the bar */
      setcolor(CYAN);
      bar(0,0,i,(getmaxy()));
      delay(100);

      if(getmaxx()==i)
       {
       closegraph(); break;}
      i++;
   }
closegraph();
}
void  custrecord::displaybox()
{
   clrscr();
   createbox();
   horline(3,3,78);
   verline(2,19,24);
   verline(2,29,24);
   verline(2,41,24);
   verline(2,51,24);
   verline(2,60,24);
   gotoxy(6,2);cout<<"Name";
   gotoxy(21,2);cout<<"Book No";
   gotoxy(30,2);cout<<" Mobile No";
   gotoxy(42,2);cout<<" Advance";
   gotoxy(52,2);cout<<"  Misc.";
   gotoxy(61,2);cout<<"   Room Service";

}
int roomrecord::recordfound(int t_roomno)
 {
     fstream file ;
     file.open("ROOMS.DAT", ios::in) ;
     file.seekg(0) ;
     int found=0 ;
     while (file.read((char *)&rrec, sizeof(rrec)))
     {
	 if (t_roomno == rrec.getrroom_no())
	     { found=1;
	     break ; }
     }
     file.close() ;
     return found;
 }
void custrecord::display()
{
 gotoxy(3,4);cout<<name;
 gotoxy(22,4);cout<<book_no;
 gotoxy(30,4);cout<<m_no;
 gotoxy(42,4);cout<<advance;
 gotoxy(62,4);cout<<rserviceb;
}
void custrecord::input_customer_data(char choice)
{
  struct date d;
  getdate(&d);
 d1_year=d.da_year;
 d1_mon=toascii(d.da_mon);
 d1_day=toascii(d.da_day);
  int valid;
  int value = 0;
  printdate();
  do{
  value = 0;
  valid=0;
  value = peek(0x0040, 0x0017);
  if(value&64)
  {
   valid=1;gotoxy(1,24);clreol();
  }
  else
  {gotoxy(1,24);cprintf("Press Caps Lock to on");
   continue;
  }
    }while(valid==0);
  int rno;
  do{
     gotoxy(1,24);cprintf("Enter the room number '0' to exit ");
     gotoxy(1,3);clreol();cout<<"Enter the room number:";
     cin>>room_no;
     if(choice=='e')
      break;
     if(room_no==0)
     mainmenu();
     check(room_no);
     if(result!=1)
      {
       gotoxy(1,24);cprintf("The room doesn't exist or not vaccant.Press any key....");
       getch();gotoxy(1,24);clreol();
      }
  }while(result!=1);
  cout<<"Enter the booking code number:";
  cin>>book_no;
  cout<<"Enter the name of the customer:";
  gets(name);
  cout<<"Enter the adress of the customer:";
  gets(address);
  cout<<"Enter the nationality:";
  gets(nationality);
  do{
		 valid=0;
		 gotoxy(1,24.5);clreol();
		 cprintf("Mobile number should be of 10 numbers");
		 gotoxy(1,8);cout<<"Enter the mobile number:";
		 gets(m_no);
		 if(strlen(m_no)<10)
		  {
		    valid=1;
		    gotoxy(1,24.5);
		    cprintf("!!Invalid number!!Mobile number should be of 10 numbers.Press any key...");
		    getch();gotoxy(1,8); clreol();
		  }
    }while(valid==1);
  do{
		valid=0;
		gotoxy(1,24.5);clreol();
		cprintf("Passport number should be of 12 numbers");
		gotoxy(1,9);cout<<"Enter the passport number for identification:";
		gets(passport_no);
		if(strlen(passport_no)<12)
		 {
		   valid=1;
		   gotoxy(1,24.5);clreol();
		   cprintf("!!Invalid entry!!Passport number should be of 12 numbers.Press any key...");
		   getch();
		   gotoxy(1,9); clreol();
		 }
    }while(valid==1);
  do{
		valid=0;
		gotoxy(1,24.5);clreol();
		cprintf("Amount of the advance should be or greater than min. advance shown.");
		gotoxy(40,18);cout<<"ROOM NO    MIN. ADVANCE";
		gotoxy(40,19);cout<<room_no;gotoxy(52,19);cout<<rrec.returntarrif(room_no)*5;
		gotoxy(1,10);cout<<"Enter the amount for advance:";
		cin>>advance;
		if(advance<rrec.returntarrif(room_no)*5)
		 {
		  valid=1;
		  gotoxy(1,24.5);clreol();
		  cprintf("!!Invalid entry!!Amount should be greater than Rs.2000.Press any key...");
		  getch();
		  gotoxy(1,10); clreol();
		 }
    }while(valid==1);
  rserviceb=0;
  char ans,ch;
  do{
	  gotoxy(1,24.5);clreol();
	  cout<<"Confirm Checkin??(y/n)";
	  cin>>ans;
	  if(ans=='Y')
	  break;
	  if(ans=='N')
	  mainmenu();
    }while(ans!='Y'||ans!='N');
    crec.set_room_status(room_no);
}
void custrecord::filecustomer(char choice)
{
  char ch='c';
  if(choice=='e')
  ch='e';
  ofstream checkn;
  crec.input_customer_data(ch);
  checkn.open("customer.dat",ios::app);
  checkn.write((char*)&crec,sizeof(crec));
  gotoxy(1,24.5);clreol();
  cout<<"$$Successfully Checked In$$";
  getch();
  checkn.close();
}


void edit::cust_recordmodify()
{
     getch();
     closegraph();
     edit mo;
     fstream modi("customer.dat",ios::in|ios::out);
     int rno;
     modi.seekg(0) ;
     long pos=0;
     char found=0;
     cout<<"Enter The Room Number:";
     cin>>rno;
     while(modi.read((char*)&mo,sizeof(mo)))
     {
	     if(mo.getroom_no()==rno)
		 {

		   found=1;
		   break;
		 }
     pos=modi.tellg();
     }
     if(found==0)
	cprintf("Record not found");
     if(found==1)
       {
	crec.input_customer_data('e');
	modi.seekg(pos);
	modi.write((char*)&mo,sizeof(mo));
       }

}
void roomrecord::input_room_data()
{
  closegraph();
  printdate();
  int valid;
  do{
  int value= 0;
  valid=0;
  value = peek(0x0040, 0x0017);
  if(value&64)
  {
   valid=1;gotoxy(1,24);clreol();
  }
  else
  {gotoxy(1,24);cprintf("Press Caps Lock to on");
   continue;
  }
    }while(valid==0);
  int rno;
  result=0;
  do{
      gotoxy(1,24);clreol();
      gotoxy(1,3);clreol();cprintf("Enter the room number:");
      cin>>rno;
     check(rno);
      if(modifyvalue==1)
      result=0;
      if(result==1)
      {
       gotoxy(1,24);cprintf("The room already exist.Press any key....");
       getch();clreol();
      }
  }while(result==1);
  rroom_no=rno;
  do{
      gotoxy(1,24);clreol();cprintf("V=VACANT AND O=OCCUPIED");
      gotoxy(1,4);clreol();cprintf("Enter the room status:");
      cin>>room_status;
      if(room_status!='V'&&room_status!='O')
      {
	gotoxy(1,24);cprintf("Enter correct room status.Press any key....");
	gotoxy(1,24);getch();clreol();
      }
    }while(room_status!='V'&&room_status!='O');
  char condition='f',*room_codes[6]={"GS","GD","PS","PD","KD","KS"};
  do{
      gotoxy(1,24);clreol();
      gotoxy(40,16);cprintf("Code    Room type");
      gotoxy(40,17);cprintf(" GS     Single Bed Garden View");
      gotoxy(40,18);cprintf(" GD     Double Bed Garden View");
      gotoxy(40,19);cprintf(" PS     Single Bed Pool View");
      gotoxy(40,20);cprintf(" PD     Double Bed Pool View");
      gotoxy(40,21);cprintf(" KS     Single Bed Kohinoor Suite");
      gotoxy(40,22);cprintf(" KD     Double Bed Kohinoor Suite");
      gotoxy(1,5);clreol();cprintf("Enter the room type code:");
      cin>>room_type;
      for(int i=0;i<6;i++)
      {
	if(strcmp(room_type,room_codes[i]))
	  condition='f';
	else
	 {
	  condition='t';
	  break;
	 }
      }
       if(condition=='f')
       {
	  gotoxy(1,24);cprintf("Invalid Code.Choose one from the list.Press any key...");
	  getch();gotoxy(1,24);clreol();
       }
     }while(condition=='f');
  do{
      gotoxy(1,24);cprintf("Tarrif shoul be geater than Rs.1000");
      gotoxy(1,6);clreol();cprintf("Enter the tarrif for the room");
      cin>>room_tarrif;
      result=0;
      if(room_tarrif<=1000)
      {
       result=1;
       gotoxy(1,24);cprintf("Tarrif shoul be geater than Rs.1000.Press any key...");
       getch();gotoxy(1,24);clreol();
      }
    }while(result==1);
}
void roomrecord::fileroom()
{
  fstream room_fil;
  room_fil.open("rooms.dat",ios::app);
  room_fil.write((char*)&rrec,sizeof(rrec));
  gotoxy(1,24);clreol();cprintf("##Record updated successfully##");
  getch();
  room_fil.close();
}
void roomrecord::room_file_modify()
{    modifyvalue=1;
     closegraph();
     roomrecord rrec1;
     fstream modir("rooms.dat",ios::in|ios::out);
     int rno,f=0; long pos=0;
     cout<<"Enter The Room Number:";
     cin>>rno;
     while(modir.read((char*)&rrec,sizeof(rrec)))
     {
      if(rno==rrec.getrroom_no())
       {
	f=1;
	break;
       }
      pos=modir.tellg();
     }
     if(f==0)
	cprintf("Record not found");
     if(f==1)
       {
	  rrec.input_room_data();
	  modir.seekg(pos);
	  modir.write((char*)&rrec,sizeof(rrec));
	  gotoxy(1,24);clreol();cprintf("##Record modified successfully##.Press any key...");
	  modir.close();
	 getch();
       }
}
void custrecord::set_room_status(int rno)
{
  fstream srs;
  srs.open("rooms.dat",ios::in|ios::out);
  char found;
  long pos=0;
  srs.seekg(0);
  while(srs.read((char*)&rrec,sizeof(rrec)))
  {
    if(rno==rrec.getrroom_no())
     {
       found='y';
       break;
     }
   pos=srs.tellg();
  }
  if(found=='y')
  {
   rrec.change_room_status();
   srs.seekg(pos);
   srs.write((char*)&rrec,sizeof(rrec));
  }
}
void custrecord::chot_set_room_status(int rno)
{
  fstream srs;
  srs.open("rooms.dat",ios::in|ios::out);
  char found;
  long pos=0;
  srs.seekg(0);
  while(srs.read((char*)&rrec,sizeof(rrec)))
  {
    if(rno==rrec.getrroom_no())
     {
       found='y';
       break;
     }
  pos=srs.tellg();
  }
  if(found=='y')
  {
   rrec.chot_change_room_status();
   srs.seekg(pos);
   srs.write((char*)&rrec,sizeof(rrec));
  }
}
void checkout::chekout()
{
  int rno;
  long pos=0;
  gotoxy(2,3);cprintf("Enter the room no. of the customer:");
  cin>>rno;
  char found;
  fstream vrec;
  vrec.open("customer.dat",ios::in|ios::out);
  while(vrec.read((char*)&crec,sizeof(crec)))
  {
   if(rno==crec.get_roomno())
     {
       found='y';
       break;
     }
  pos=vrec.tellg();
  }
  if(found=='y')
  {
    gotoxy(4,5);cprintf("Displaying the record of the customer.Please wait");
    for(int i=0;i<7;i++)
    {
      cprintf(".");
      delay(1000);
    }
    crec.displaybox();
    crec.display();
    getch();
    crec.calbill(pos);
    fstream fil,fil1;
    fil.open("temp.dat",ios::out);
    fil1.open("checked out.dat",ios::app);
    vrec.seekg(0);
    while(vrec.read((char*)&crec,sizeof(crec)))
    {
     if(rno!=crec.get_roomno())
      fil.write((char*)&crec,sizeof(crec));
     if(rno==crec.get_roomno())
      fil1.write((char*)&crec,sizeof(crec));
    }
    fil.close();
    vrec.close();
    remove("customer.dat");
    rename("temp.dat","customer.dat");
    crec.chot_set_room_status(rno);
    vrec.close();
    getch();
  }
  else
  {gotoxy(4,5);cprintf("Record not found");}
  getch();
  mainmenu();
  }
void roomrecord::delete_room_record()
{
 closegraph();
 clrscr();
 int rno,found;
 cprintf("Enter the room nummber to delete the record");
 cin>>rno;
 fstream fil,fil1;
 fil.open("rooms.dat",ios::in);
 fil1.open("temp.dat",ios::app);
 while(fil.read((char*)&rrec,sizeof(rrec)))
 {
   if(rno==rrec.getrroom_no())
    {
     found=1; break;
    }
   else
    found=0;
  }
 if(found==0)
 { cprintf("Record of the entered room number not found");
   getch();
 }
 if(found==1)
 {
  fil.seekp(0);
  while(fil.read((char*)&rrec,sizeof(rrec)))
  {
   if(rno!=rrec.getrroom_no())
     fil1.write((char*)&rrec,sizeof(rrec));
  }
  fil.close();
  fil1.close();
  remove("rooms.dat");
  rename("temp.dat","rooms.dat");
  cout<<"Record deleted";
  getch();
 }
}
void custrecord::view_custrecord()
{
 int rno,found;
 ifstream fil;
 fil.open("customer.dat",ios::in);
 cprintf("Enter the room Number");
 cin>>rno;
 while(fil.read((char*)&crec,sizeof(crec)))
 {
   if(rno==crec.get_roomno())
    {
     found=1; break;
    }
  else
    found=0;
  }
 if(found==0)
 { cprintf("Record of the entered room number not found");
   getch();
 }
 if(found==1)
 {
 clrscr();
 gotoxy(35,1);
 cprintf("Customer Record");
 gotoxy(5,4);cprintf("Room Number:-  ");cout<<room_no;
 gotoxy(5,6);cprintf("Booking Number:-  ");cout<<book_no;
 gotoxy(5,8);cprintf("Name:-  ");cprintf(name,30);
 gotoxy(5,10);cprintf("Address:-  ");cprintf(address,90);
 gotoxy(5,12);cprintf("Nationality:-  ");cprintf(nationality,20);
 gotoxy(5,14);cprintf("Mobile Number:-  ");cprintf(m_no,15);
 gotoxy(5,16);cprintf("Passport Number:-  ");cprintf(passport_no,15);
 gotoxy(5,18);cprintf("Advance:-  ");cout<<advance;
 getch();
 }
}
void roomrecord::view_roomrecord()
{
 int rno,found;
 ifstream fil;
 fil.open("ROOMS.DAT",ios::in);
 cprintf("Enter the room Number");
 cin>>rno;
 while(fil.read((char*)&rrec,sizeof(rrec)))
 {
   if(rno==rrec.getrroom_no())
    {
     found=1; break;
    }
  else
    found=0;
  }
 if(found==0)
 { cprintf("Record of the entered room number not found");
   getch();
 }
 if(found==1)
 {
  clrscr();
  gotoxy(36,1);
  cprintf("Room Record");
  gotoxy(5,4);cprintf("Room Number:-  ");cout<<rroom_no;
  gotoxy(5,6);cprintf("Room Status:-  ");cout<<room_status;
  gotoxy(5,8);cprintf("Room Type Code:-  ");cout<<room_type;
  gotoxy(5,10);cprintf("Room Tarrif:-  ");cout<<room_tarrif;
  gotoxy(1,23);cprintf("Information Bar");
  gotoxy(1,24);cprintf("Press Any Key.......");
  getch();
 }
}
void view_record::get_recordinfo(char type)
{
  ifstream cfil,rfil;
  cfil.open("customer.dat",ios::in);
  rfil.open("ROOMS.DAT",ios::in);
  for(;;)
  {
   if(type=='c')
   {
    if(cfil.eof())
     break;
    cfil.read((char*)&crec,sizeof(crec));
    //crec.viewrecord();
   }
   if(type=='r')
   {
    if(cfil.eof())
     break;
    rfil.read((char*)&rrec,sizeof(rrec));
   }
  }
}
void custrecord::calbill(long pos)
{
 clrscr();
 printdate();
  struct date d;
  getdate(&d);
  int p_day=toascii(d.da_day);
  int p_mon = toascii(d.da_mon);
  int p_year=d.da_year;
  int ref;
  ifstream fil;
  fil.open("CUSTOMER.DAT",ios::in);
  fil.seekg(pos);
  fil.read((char*)&crec,sizeof(crec));
  int d2_day=d1_day;
  int d2_mon =d1_mon;
  int d2_year=d1_year;
  ref=p_year;
  if(d2_year<p_year)
  ref=d2_year;
  int dd1=0;
  dd1=func1(p_mon);
  for(int i=ref;i<p_year;i++)
  {
   if(i%4==0)
   dd1+=1;
  }
  dd1=dd1+p_day+(p_year-ref)*365;
  int dd2=0;
  for(i=ref;i<d2_year;i++)
  {
   if(i%4==0)
    dd2+=1;
  }
  dd2=func1(d2_mon)+dd2+d1_day+((d2_year-ref)*365);
  int d_stay=abs(dd2-dd1);
  if(d_stay==0)
  d_stay=1;
  gotoxy(1,3);cout<<"Days stayed by the customer:"<<d_stay;
  long tarrif=rrec.returntarrif(room_no);
  cout<<"\nThe tarrif of the room is:"<<tarrif;
  cout<<"\nThe tarrif bill is:"<<(d_stay*tarrif);
  cout<<"\nThe room service bill is:"<<rserviceb;
  cout<<"\nThe total bill is:"<<((d_stay*tarrif)+rserviceb);
  cout<<"\nThe total payable bill after deducting from the advance is:"<<(((d_stay*tarrif)+rserviceb)-advance);
  gotoxy(1,24);cout<<"If the total payable bill come in negative, amount has to be payed to customer";
  din.daily_income(((d_stay*tarrif)+rserviceb),0);
  }
  int func1(int x)
  {
   int y=0;
   switch(x)
   {
    case 1:y=0;break;
    case 2:y=31;break;
    case 3:y=59;break;
    case 4:y=90;break;
    case 5:y=120;break;
    case 6:y=151;break;
    case 7:y=181;break;
    case 8:y=212;break;
    case 9:y=243;break;
    case 10:y=273;break;
    case 11:y=304;break;
    case 12:y=334;break;
    default:cout<<"Error encountered";getch();
	    exit(0);
    }
    return(y);
  }
 long roomrecord::returntarrif(int room)
 {
  ifstream fil;
  fil.open("ROOMS.DAT",ios::in);
  long tarrif;
  while(fil.read((char*)&rrec,sizeof(rrec)))
  {
   if(room==rroom_no)
   {
    tarrif=room_tarrif;
    break;
   }
  }
 fil.close();
 return tarrif;
 }
void custrecord::dispcust()
{
 ifstream fil;
 int found=0;
 fil.open("customer.dat",ios::in);
 int y=4;
 while(fil.read((char*)&crec,sizeof(crec)))
 {
   found=1;
   if(y==22)
   {
    gotoxy(3,24);cout<<"Press any key to go to next page";
    y=4;
    getch();
   }
  if(y==4)
 {
  clrscr();
  createbox();
  horline(3,3,78);
  verline(2,7,24);//rno
  verline(2,16,24);//bno
  verline(2,30,24);//name
  verline(2,40,24);//phone
  verline(2,52,24);//nationality
  verline(2,63,24);//advance
  gotoxy(3,2);cout<<"Room";
  gotoxy(8,2);cout<<"Book No";
  gotoxy(17,2);cout<<"   Name";
  gotoxy(31,2);cout<<"Phone No";
  gotoxy(41,2);cout<<"Nationality";
  gotoxy(53,2);cout<<" Advance";
  gotoxy(64,2);cout<<"Room Srvice";
 }
  gotoxy(3,y);cout<<room_no;
  gotoxy(8,y);cout<<book_no;
  gotoxy(17,y);cout<<name;
  gotoxy(31,y);cout<<m_no;
  gotoxy(42,y);cout<<nationality;
  gotoxy(53,y);cout<<advance;
  gotoxy(64,y);cout<<rserviceb;
  delay(800);
  y++;
}
fil.close();
if(found==0)
{
 clrscr();
 createbox();
 gotoxy(3,24);cout<<"Sorry for inconvinience No Records to display or records are corrupted";
}
getch();
}
void roomrecord::disproom()
{
 ifstream fil;
 fil.open("rooms.dat",ios::in);
 int y=4,found=0;
 while(fil.read((char*)&rrec,sizeof(rrec)))
 {
    found=1;
    if(y==22)
   {
    gotoxy(3,24);cout<<"Press any key to go to next page";
    y=4;
    getch();
   }
  if(y==4)
 {
  clrscr();
  createbox();
  horline(3,3,78);
  verline(2,10,24);//rno
  verline(2,30,24);//bno
  verline(2,60,24);//name
  gotoxy(3,2);cout<<"Room No";
  gotoxy(15,2);cout<<"Room Status";
  gotoxy(32,2);cout<<"Room Type";
  gotoxy(64,2);cout<<"Room Tarrif";
   }
  gotoxy(3,y);cout<<rroom_no;
  gotoxy(16,y);
  if(room_status=='V')cout<<"Vacant";
  if(room_status=='O')cout<<"Occupied";
  gotoxy(32,y);
  if(!strcmp(room_type,"GS"))cprintf(" Single Bed Garden View");
  if(!strcmp(room_type,"GD"))cprintf(" Double Bed Garden View");
  if(!strcmp(room_type,"PS"))cprintf(" Single Bed Pool View");
  if(!strcmp(room_type,"PD"))cprintf(" Double Bed Pool View");
  if(!strcmp(room_type,"KS"))cprintf(" Single Bed Kohinoor Suite");
  if(!strcmp(room_type,"KD"))cprintf(" Double Bed Kohinoor Suite");
  gotoxy(65,y);cout<<room_tarrif;
  delay(800);
  y++;
}
fil.close();
if(found==0)
{
 clrscr();
 createbox();
 gotoxy(3,24);cout<<"Sorry for inconvinience No Records to display or records are corrupted";
}
getch();
}
void income::daily_income(long r_rent,long r_service)
{
  struct date d;
  getdate(&d);
  int p_day=toascii(d.da_day);
  int p_mon = toascii(d.da_mon);
  int p_year=d.da_year;
 fstream fil;
 fil.open("INCOME.DAT",ios::in|ios::out);
 long pos=0;char found='n';
 while(fil.read((char*)&din,sizeof(din)))
 {
  if(p_day==i_day&&p_mon==i_mon&&p_year==i_year)
   {
   found='y';  break;
   }
  pos=fil.tellg();
 }
 if(found=='y')
 {
  room_rent+=r_rent;
  rsbill+=r_service;
  fil.seekg(pos);
  fil.write((char*)&din,sizeof(din));
  fil.close();
 }
 else
 {
  ofstream fil1;
  fil1.open("INCOME.DAT",ios::app);
  i_day=p_day;
  i_mon=p_mon;
  i_year=p_year;
  room_rent=r_rent;
  rsbill=r_service;
  fil1.write((char*)&din,sizeof(din));
  fil1.close();
 }
}
void income::dis_daily_income()
{
 ifstream fil;
 fil.open("INCOME.DAT",ios::in);
 int y=4;
 while(fil.read((char*)&din,sizeof(din)))
 {
    if(y==22)
   {
    gotoxy(3,24);cout<<"Press any key to go to next page";
    y=4;
    getch();
   }
  if(y==4)
 {
  clrscr();
  createbox();
  horline(3,3,78);
  verline(2,13,24);//till date
  verline(2,50,24);//till room rent
  gotoxy(3,2);cout<<"Date";
  gotoxy(15,2);cout<<"Income through customers";
  gotoxy(51,2);cout<<"Income through Restaurent";
 }
  gotoxy(3,y);cout<<i_day<<"/"<<i_mon<<"/"<<i_year;
  gotoxy(15,y);cout<<room_rent;
  gotoxy(51,y);cout<<rsbill;
  delay(200);
  y++;
 }
getch();
fil.close();
}
void roomrecord::show_rooms()
{
 ifstream fil;
 fil.open("ROOMS.DAT",ios::in);
 int count=0,x=30,y=30;
 char str[5];
 while(fil.read((char*)&rrec,sizeof(rrec)))
 {
  if(count<7)
  {
   if(room_status=='V')
    setfillstyle(SOLID_FILL,GREEN);
   if(room_status=='O')
    setfillstyle(SOLID_FILL,BLUE);
   bar(x+5,35,x+65,205);
   itoa(rroom_no, str, 10);
   setcolor(BLACK);
   outtextxy(x+25,195,str);
   x+=70;
  }
  if(count>=7)
  {
   if(room_status=='V')
    setfillstyle(SOLID_FILL,GREEN);
   if(room_status=='O')
    setfillstyle(SOLID_FILL,BLUE);
   bar(y+5,285,y+65,445);
   itoa(rroom_no, str, 10);
   setcolor(BLACK);
   outtextxy(y+25,438,str);
   y+=70;
  }
 count++;
 if(count==14)
 {
  count=0;
  m.room_map();
 }
 }
 getch();
}
void thanks()
{
initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
settextstyle(4,1,7);
setcolor(LIGHTRED);
rectangle(5,5,getmaxx(),getmaxy());
outtextxy(50,150,"Thanks");
setcolor(CYAN);
settextstyle(4,0,4);
outtextxy(150,50,"   Have A Nice Day");
setcolor(BROWN);
settextstyle(2,0,9);
outtextxy(250,100,"CREDITS:-");
setcolor(LIGHTRED);
settextstyle(4,0,4);
outtextxy(150,150,"Ronak Raj Doongarwal");
outtextxy(150,200,"Class XII-A");
getch();
}
void password()
{
 char u_name[15],pass[10],ch;
 createbox();
 textcolor(RED);gotoxy(30,2);cprintf("Password Protection");
 gotoxy(10,6);cprintf("Enter Username And Password to Login");
 gotoxy(13,8);cout<<(char)218;
 gotoxy(13,12);cout<<(char)192;
 gotoxy(45,8);cout<<(char)191 ;
 gotoxy(45,12);cout<<(char)217;
 horline(14,8,44);
 horline(14,12,44);
 verline(9,13,11);
 verline(9,45,11);
 horline(14,10,44);
 horline(3,3,78);
 horline(3,23,78);
 gotoxy(15,9);cprintf("Username:-");
 gotoxy(15,11);cprintf("Password:-");
 gotoxy(26,9);gets(u_name);gotoxy(26,11);
 int i=0;
 while(1)
 {
  ch=getch();
  if(ch==13)
  { pass[i]='\0';
   break;
  }
  cout<<"*";
  pass[i]=ch;
  i++;
 }
 if(strcmp(u_name,"rrddevlp")!=0||strcmp(pass,"raj8519hm")!=0)
 {
  gotoxy(3,24);cout<<"Wrong Username Or Password!!Exiting...";
  getch();
  exit(0);
 }
 else
 gotoxy(3,24);cout<<"Username And Password Correct. Access Granted. Press Any Key...";
 getch();
}


