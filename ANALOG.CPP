/* Analog & Digital Clock - C Language */
/* Author : Md. Abdullah-al-MAMUN */
/* Tool   : Turbo C */
/* Date   : JULY 6, 2009 1:51 PM Friday */
/* Email  : mamunbd.ruet@gmail.com  */

#include<conio.h>				//To detect keyboard press
#include<graphics.h>				//Basic drawing operations
#include<dos.h>					//For Date & Time
#include<math.h>				//Cos,Sin
#include<stdlib.h>				//itoa
#include<string.h>				//strcpy,strcat,strlen
const float PI = 3.1415926535;			//PI value

int sec, min, hr;				//Store time

void BIG_CIR(int,int);
void abcd1(int,int,int);
void init_circle(int,int,int,int);
void abcd2(int,int,int,int);
void BIG_CIR2(int,int);

float oc[7]={130.81,146.83,164.81,174.61,196,220,246.94};

void start();
struct time t;					//Get time
struct dosdate_t d;				//Get Date

char p[8] = {0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55};//User defined fill pattern

char strhr[5] = "",strmin[5] = "",strsec[5] = "";//Store date.

char strdate[30];
//Select day of Month
char strday[][3]={"01", "02", "03", "04", "05", "06", "07", "08", "09", "10",
	       "11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
	       "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"};
//Select month of Year
char strmonth[][9]={"January", "February", "March", "April", "May", "June",
		    "July", "August", "September", "October", "November", "December"};
char stryr[5] = "";//Store year
//Select day of Week
char strwday[][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void GoodBye (void);//Shows close down screen

void main ()//Program entry
{
	int gd = DETECT, gm;			//Graphics initialisation
	sec = min = hr = 0;			//Remove garbage values
	initgraph    (&gd, &gm, "C:\\turboc3\\bgi");	//Switch to graphics
	start();

	setfillstyle (SOLID_FILL, RED);		//Background- style & color
	bar (0, 0, 639, 479);			//Background
	float angle;//Inclination of the hands of the clock

	setcolor     (YELLOW);		        //Dial border of the clock
	setfillstyle (SOLID_FILL, YELLOW);
	fillellipse  (320, 240, 240, 240);      //Dial border

	setcolor         (LIGHTBLUE);		//Dial of the clock
	setfillstyle     (SOLID_FILL, LIGHTBLUE);
	fillellipse      (320, 240, 235, 235);

	setcolor         (DARKGRAY);		//Inside color of the clock
	setfillstyle     (SOLID_FILL, LIGHTGRAY);
	fillellipse      (320, 240, 190, 190);

	setcolor         (BLACK);
	settextstyle     (10, 0, 1);		//Bold_Font
	outtextxy        (306, 5, "XII");
	outtextxy        (312, 430, "VI");
	outtextxy        (520, 215, "III");
	outtextxy        (102, 215, "IX");
	setfillpattern   (p, WHITE);
	bar              (560, 215, 575, 265);  //Showing the key to the watch
	bar              (575, 220, 580, 260);  //Just a sho


	setfillstyle     (SOLID_FILL, WHITE);   //Making the textbox for Date
	bar              (210, 310, 445, 350);
	setcolor         (DARKGRAY);
	rectangle        (210, 310, 445, 350);
	setcolor         (BLACK);
	rectangle        (211, 311, 444, 349);
	setcolor         (WHITE);
	line             (210, 350, 446, 350);
	line             (446, 350, 446, 310);
	setcolor         (LIGHTGRAY);
	rectangle        (212, 312, 443, 348);  //End of textbox for Date

	while( ! kbhit() ){
		gettime          (&t);//Load system time into structure t
		sec   = t.ti_sec;	//Store seconds
		min   = t.ti_min;	//Store minutes
		hr    = t.ti_hour;	//Store hours
	
		setfillstyle     (SOLID_FILL, BROWN);
		fillellipse      (320, 240, 10, 10); //  -------|
		setfillstyle     (SOLID_FILL, WHITE);//         |   Display center of
		fillellipse      (320, 240, 7, 7);   //  -------|->    the Clock
		setfillstyle     (SOLID_FILL, GREEN);//         |
		fillellipse      (320, 240, 4, 4);   //  -------|
	
		itoa             (hr, strhr, 10); //Get hours in a string
		if( strlen (strhr) == 1)          //Make it a string having len = 2
		{
			strhr[2]   = '\0';
			strhr[1]   = strhr[0];
			strhr[0]   = '0';
		}
		itoa             (min, strmin, 10);//Get minutes in a string
		if( strlen (strmin) == 1)          //Make it a string having len = 2
		{
			strmin[2]   = '\0';
			strmin[1]   = strmin[0];
			strmin[0]   = '0';
		}
		itoa             (sec, strsec, 10);//Get seconds in a string
		if( strlen (strsec) == 1)          //Make it a string heving len = 2
		{
			strsec[2]   = '\0';
			strsec[1]   = strsec[0];
			strsec[0]   = '0';
		}
		setcolor         (BLACK);
		settextstyle     (5, 0, 4);
		moveto           (244, 117);
		outtext          (strhr);outtext (":");
		outtext          (strmin);outtext (":");
		outtext          (strsec);         //Display the time in the given region
	
		_dos_getdate     (&d);             //Load system date into structure d
		strcpy (strdate, strwday[d.dayofweek]);strcat (strdate, ",");
		strcat (strdate, strmonth[d.month-1]);strcat (strdate, " ");
		strcat (strdate, strday[d.day-1]);strcat (strdate, ",");
		itoa   (d.year, stryr, 10);
		strcat (strdate, stryr);
		settextstyle (1, 0, 1);
		moveto (225, 320);outtext (strdate);
	
		setlinestyle(SOLID_LINE,0,3);
	
		int totsec = ((t.ti_hour%12)* 60)+(t.ti_min);
		angle = (float)(((float)totsec/(float)720)* 2 *PI);angle -= PI / 2;
		setcolor (BLACK);
	
		line (320+2,240+2,320 +(100 * cos(angle))+ 2,240 +(100 * sin(angle))+ 2);
		setcolor (BROWN);
		line (320, 240, 320 + (100 * cos(angle)),240 +(100 * sin(angle)));
	
	
		angle = ((float)min/60)* 2 *PI;angle = angle - (PI / 2);
		setcolor (BLACK);
	
		line (320+3,240+3,320 +(175 * cos(angle))+ 3,240 +(175 * sin(angle))+ 3);
		setcolor (RED);
		line (320, 240, 320 + (175 * cos(angle)), 240 + (175 * sin(angle)));
	
		setlinestyle (SOLID_LINE,0,1);
		angle = ((float)sec/60)* 2 *PI;angle   = angle - (PI / 2);
		setcolor (BLACK);
		line (320+5,240+5,320 +(180 * cos(angle))+ 5,240 +(180 * sin(angle))+ 5);
		setcolor (RED);
		line (320,240,320 +(180 * cos(angle)), 240 +(180 * sin(angle)));
	
		delay (900);  setcolor(LIGHTGRAY);
		setlinestyle (SOLID_LINE, 0, 3);
	
		totsec = ((t.ti_hour % 12) * 60) + (t.ti_min);
		angle = (float)(((float)totsec/(float)720)* 2 *PI);angle -= PI / 2;
		line (320,240,320 +(100 * cos(angle)),240 +(100 * sin(angle)));
		line (320+2, 240+2,320 +(100 * cos(angle))+ 2,240 +(100 * sin(angle))+ 2);
	
		angle = ((float)min/60)* 2 *PI;angle = angle - (PI / 2);
		line (320,240,320 +(175 * cos(angle)),240 +(175 * sin(angle)));
		line (320+3,240+3,320 +(175 * cos(angle))+ 3,240 +(175 * sin(angle))+ 3);
	
	
		setlinestyle (SOLID_LINE,0,3);
		angle = ((float)sec/60)* 2 *PI;angle = angle - (PI / 2);
		line (320+5,240+5,320 +(180 * cos(angle))+ 5,240 +(180 * sin(angle))+ 5);
		line (320,240,320 +(180 * cos(angle)),240 +(180 * sin(angle)));
	
		setlinestyle (SOLID_LINE, 0, 1);
		setfillstyle (SOLID_FILL, WHITE);
		bar (240, 127, 390, 160);
		setcolor (BLACK);
		rectangle (241, 128, 389, 159);
		setcolor (DARKGRAY);
		line (240, 160, 240, 127);
		line (240, 127, 390, 127);
		setcolor (WHITE);
		line (240, 160, 390, 160);
		line (390, 160, 390, 127);
		setcolor (LIGHTGRAY);
		rectangle (242, 129, 388, 158);
	
		if( (sec>19 && sec<41) || (hr>19 && hr<41) || (min>19&&min<41) )
		{
			setfillstyle (SOLID_FILL, WHITE);
			bar (210, 310, 445, 350);
			setcolor (DARKGRAY);
			rectangle (210, 310, 445, 350);
			setcolor (BLACK);
			rectangle (211, 311, 444, 349);
			setcolor (WHITE);
			line (210, 350, 446, 350);
			line (446, 350, 446, 310);
			setcolor (LIGHTGRAY);
			rectangle (212, 312, 443, 348);
		}
	}
	GoodBye();
}
void GoodBye (void)
{
	closegraph ();
	int i,j;i = 5;
	textbackground (BLACK);
	textcolor (RED);
	clrscr ();

	textcolor(CYAN);
	gotoxy (1, 20);cprintf ("Exiting.....");
	gotoxy (1, 21);
	for (i = 0;i < 80;i ++)
	{
		gotoxy (wherex(),21);
		cprintf ("Û");
		delay (50);
	}
	textcolor(RED);
	delay (200);
	gotoxy (5, wherey () - 1);
	textcolor (WHITE);textbackground (CYAN);
	cprintf ("UnIstalling Clock.....                  [50  %]                    ");
	delay (1500);gotoxy(5, wherey ());
	cprintf ("DeInitialising Clock.....               [100 %] Completed.         ");
	delay (1000);gotoxy(5, wherey ());
	cprintf ("UnLoading System Date/Time.....         Done.                ");
	delay (1300);gotoxy(5, wherey ());
	cprintf ("UnLoading Graphics.....                 In Progress          ");
	delay (1000);gotoxy(5, wherey ());
	cprintf ("Removing Loaded Objects Graphics.....      Done                 ");
	delay (1200);gotoxy(5, wherey ());
	cprintf ("UnInstanciating GUI(Graphical User Interface)                ");
	delay (1200);gotoxy(5, wherey ());
	cprintf("Destroying & Removing Registry Values of the Software on System ");
	delay (1000);
	gotoxy (5, 5);
	textbackground (BLACK);
	textcolor (LIGHTCYAN);
	clrscr ();
	cprintf ("Created by: ");
	textcolor(11);
	gotoxy(10,6);
	cprintf("MD. ABDULLAH-AL-MAMUN");
	textcolor(12);
	gotoxy(10,7);
	cprintf("Rajshahi University of Engineering & Technlogy(RUET)");
	gotoxy (5, 16);
	cprintf ("Mail me at  <");
	textcolor (13);
	cprintf (" mamunbd.ruet@gmail.com ");
	textcolor (LIGHTCYAN);
	cprintf (" > ");

textmode(C80);
gotoxy(5,20);
textcolor(GREEN | BLINK);
textbackground(BLACK);
cprintf("PRESS ANY KEY TO EXIT... ...");
getch ();
getch ();
}

void start(){
	int gdrive=DETECT,gmode;
	initgraph(&gdrive,&gmode,"C:\\turboc3\\bgi");
	
	settextstyle(0,0,2);
	setcolor(4);
	outtextxy(100,100,"PLEASE WAIT");
	setcolor(13);
	outtextxy(200,200,"Time remaining  ");
	setcolor(10);
	outtextxy(500,200,"Sce:");
	delay(1000);
	
	for(int j=0;j<5;j++){
		for(int i=0;i<3;i++){
			fillellipse(300+25*i,110,4,4);
			delay(400);
		}
		
	setcolor(14);
	outtextxy(450,200,"5");
	setcolor(0);
	
	for(int c=0;c<=20;c++)
		line(290,100+c,360,100+c);
		delay(500);
	}
	
	cleardevice();
	settextstyle(0,0,5);
	setcolor(13);
	outtextxy(200,200,"< OK >");
	
	while(!kbhit()){
		settextstyle(0,0,2);
		setcolor(12);
		outtextxy(100,300,"PRESS ANY KEY ... ...");
		delay(300);
		setcolor(BLACK);
		
		for(int c=0;c<=30;c++)
			line(90,290+c,450,290+c);
		delay(200);
	}
	
	setcolor(0);
	
	for(int i=0;i<300;i++){
		circle(300,200,0+i);
		delay(5);
	}
	
	cleardevice();
	abcd1(400,400,10);
	abcd1(200,200,11);
	abcd2(300,230,2,6);
	settextstyle(1,0,8);
	setcolor(13);
	outtextxy(200,200,"WELCOME");
	delay(500);
	cleardevice();
	abcd1(200,200,11);
	abcd2(300,230,2,6);
	abcd1(100,250,14);
	abcd1(300,250,13);
	cleardevice();
	
	for(int a=1;a<=4;a++)
		switch(a){
			case 1:
				settextstyle(0,0,4);
				setcolor(13);
				outtextxy(100,100,"ANALOG");
				delay(100);

				for(i=0;i<7;i++){
					sound(oc[i]*8);
					delay(300);
				}
				break;
	
			case 2:
				settextstyle(1,0,4);
				setcolor(12);
				outtextxy(200,200,"... AND ...");
				delay(100);
			
				for(i=0;i<15;i++){
					int n=random(7);
					sound(oc[n]*4);
					delay(300);
				}
				break;
	
			case 3:
				settextstyle(0,0,5);
				setcolor(11);
				outtextxy(100,300,"DIGITAL");
				delay(100);
				
				for(i=4;i>=0;i--){
					sound(oc[i]*4);
					delay(300);
				}
				break;
	
			case 4:
				settextstyle(0,0,6);
				setcolor(10);
				outtextxy(250,400,"CLOCK");
				delay(100);
				sound(oc[6]*2);
				delay(200);
				nosound();
				break; 
		}
	delay(1000);
	getch();
}

void abcd1(int xx,int yy ,int coll){
	init_circle(xx,480,480-yy,coll);
	BIG_CIR(xx,yy);
	
	for(int i=0;i<180;i++){
		for(int j=0;j<50;j++){
			setcolor(coll);
			setfillstyle(1,coll);
			
			circle(xx+i*sin(j),yy+i*cos(j),3);
			floodfill(xx+i*sin(j),yy+i*cos(j),coll);
			delay(0.1);
		}
		cleardevice();
	}
}

void BIG_CIR(int BC1,int BC2){
	setcolor(15);
	setfillstyle(1,15);
	circle(BC1,BC2,30);
	floodfill(BC1,BC2,15);
	delay(20);
	cleardevice();
}

void init_circle(int init_x,int init_y,int init_h,int coo){
	for(int i=0;i<init_h;i++){
		setcolor(coo);
		setfillstyle(1,coo);
		circle(init_x,init_y-i,3);
		floodfill(init_x,init_y-i,coo);
		cleardevice();
		delay(0.1);
	}
}

void abcd2(int xx2,int yy2 ,int coll2,int numbers){
	init_circle(xx2,480,480-yy2,coll2);
	BIG_CIR(xx2,yy2);
	
	for(int i=0;i<100;i++){
		for(int j=0;j<numbers;j++){
			setcolor(coll2);
			setfillstyle(1,coll2);
			circle(xx2+i*sin(j),yy2+i*cos(j),3);
			floodfill(xx2+i*sin(j),yy2+i*cos(j),coll2);
			delay(0.1);
		}
		cleardevice();
	}
	
	for(int j=0;j<numbers;j++){
		BIG_CIR2(xx2+100*sin(j),yy2+100*cos(j));
	}
}

void BIG_CIR2(int BC21,int BC22){
	setcolor(15);
	setfillstyle(1,15);
	circle(BC21,BC22,30);
	floodfill(BC21,BC22,15);
	delay(20);
	cleardevice();
}
