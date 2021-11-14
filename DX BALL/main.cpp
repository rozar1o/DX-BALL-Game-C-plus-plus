#include<stdio.h>
#include<conio.h>
#include<dos.h>
//#include<graphics.h>
#include<dos.h>
//#include<mouse.h>
#include<string.h>

int x,y,a,b,i,area,px,py,stat,bx=20,by=200,bxspeed=2,byspeed=2,scr=0,DETECT;
static int sq[15][15];
char *paddal,*ball,dir[3]="br",score[4]="ss";
int main()
{
  char*img1,*img2;
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"c:\tc\bgi");
  x=getmaxx()/2,y=getmaxy()/2;

  backfrm();
  splace_form();
  initmouse();
while(1)
{
getmousepos(&stat ,&px ,&py);
delay(11);
if(stat==1)
break;
}
mainfrm();

  backfrm();
  dpaddal();
  backfrm();
  dball();
  backfrm();
  lavel(1);
  printlevel();
 restrictmouseptr(16,500,540,500);

while(!kbhit())
{
delay(10);
movepaddal();
moveball();
}

getch();
}




//---------------------move ball---------------///
moveball()
{
 setfillstyle(SOLID_FILL,1);
 bar(bx-2,by-2,bx+12,by+12);
 putimage(bx,by,ball,COPY_PUT);
 balldir();
 if(!strcmp(dir,"bl"))        bx-=bxspeed,by+=byspeed;
 if(!strcmp(dir,"br"))        bx+=bxspeed,by+=byspeed;
 if(!strcmp(dir,"tl"))        bx-=bxspeed,by-=byspeed;
 if(!strcmp(dir,"tr"))        bx+=bxspeed,by-=byspeed;
}

//-----------------------ball diraction---------------//
balldir()
{
if(!strcmp(dir,"bl") && by>440)         btp("tl");
if(!strcmp(dir,"br") && by>440)         btp("tr");
if(!strcmp(dir,"tl") && by<122&&sq[(by-55)/15][(bx-16)/50]==0)
bts("bl");
if(!strcmp(dir,"tr") && by<122&&sq[(by-55)/15][(bx-16)/50]==0)
bts("br");

if(!strcmp(dir,"bl") && by<122&&sq[(by-55)/15][(bx-16)/50]==0)
bts("tl");
if(!strcmp(dir,"br") && by<122&&sq[(by-55)/15][(bx-16)/50]==0)
bts("tr");

 if(!strcmp(dir,"tr") && by<40)        strcpy(dir,"br"),sndplay(500);
 if(!strcmp(dir,"tl") && by<40)        strcpy(dir,"bl"),sndplay(500);

 if(!strcmp(dir,"bl") && bx<20)         strcpy(dir,"br"),sndplay(500);
 if(!strcmp(dir,"tr") && bx>600)        strcpy(dir,"tl"),sndplay(500);
 if(!strcmp(dir,"tl") && bx<20)         strcpy(dir,"tr"),sndplay(500);
 if(!strcmp(dir,"br") && bx>600)        strcpy(dir,"bl"),sndplay(500);

}

//-------------------------move paddal---------------///
movepaddal()
{
setfillstyle(SOLID_FILL,1);
bar(16,450,612,460);
getmousepos(&stat ,&px ,&py);
putimage(px,450,paddal,COPY_PUT);
}

//-----------------paddal--------------------//
  dpaddal()
  {
  int area;
  setfillstyle(SOLID_FILL,15);
  fillellipse(x,y,35,4);
 area=imagesize(x-35,y-4,x+35,y+4);   //  find area of image
 paddal=malloc(area);
 getimage(x-35,y-4,x+35,y+4,paddal);		 //get image in *paddal
 }
//------------------ball------------------------//
dball()
{
  int area;
  setfillstyle(SOLID_FILL,4);
  fillellipse(x,y,5,5);
  area=imagesize(x-5,y-5,x+5,y+5);   //  find area of image
  ball=malloc(area);
  getimage(x-5,y-5,x+5,y+5,ball);		 //get image in *ball
}


//-----------------------print squar--------------//
squar(int a,int b ,int norm)
{
     setfillstyle(SOLID_FILL,13);
     if(b%2)
     setfillstyle(SOLID_FILL,3);
     if(norm==0)
     setfillstyle(SOLID_FILL,1);
     bar(b*50+16,a*15+55,b*50+63,a*15+54+13);

  setfillstyle(SOLID_FILL,1);
  bar(100,16,140,30);
  setcolor(15);
  settextstyle(2,0,6);
  outtextxy(20,15,"Score -");
  itoa(scr,score,10);
  outtextxy(100,15,score);

}

//------------------------backfrm-------------------//
backfrm()
{
setfillstyle(SOLID_FILL,1);
bar(15,15,615,465);

button(0,0,15,480,1);
button(615,0,630,480,1);
button(0,0,630,15,1);
button(0,465,630,480,1);
}

//---------------SPLACE FORM---------------------------//
splace_form()
{
setcolor(4);
settextstyle(4,0,6);
outtextxy(x-145,y-200, "  GAME");

outtextxy(x-145,y-50, "DX==BALL");
setcolor(2);
outtextxy(x-145,y-150, "--------");
settextstyle(1,0,1);
}

//--------------------------BUTTON-------------------------//
button(int xl,int yt,int xr,int yb, int status)
{
   setfillstyle(SOLID_FILL, LIGHTGRAY);
   bar(xl, yt, xr, yb);
   if (status) {
      setcolor(WHITE);
      line(xl,yt,xl,yb-1);
      line(xl,yt,xr-1,yt);
      setcolor(DARKGRAY);
      line(xr,yb,xl,yb);
      line(xr,yb,xr,yt);
		  }
   else {
       setcolor(DARKGRAY);
      line(xl,yt,xl,yb);
      line(xl,yt,xr,yt);
   }
 }		 /* Set_square */

 //--------------------------sound--------------------------//
 sndplay(int a)
 {
 sound(a);
 delay(20);
 nosound();
 }
 //-------------------------ball tuoch paddal---------------//
 btp(char s[3])
 {
  if(bx>=px&&bx<=px+10)      bxspeed=2,byspeed=1,strcpy(dir,"tl") ;
  if(bx>=px+11&&bx<=px+30)   bxspeed=2,byspeed=2,strcpy(dir,"tl") ;
  if(bx>=px+31&&bx<=px+35)   bxspeed=1,byspeed=2,strcpy(dir,"tl") ;
  if(bx>=px+35&&bx<=px+40)   bxspeed=1,byspeed=2,strcpy(dir,"tr") ;
  if(bx>=px+41&&bx<=px+60)   bxspeed=2,byspeed=2,strcpy(dir,"tr") ;
  if(bx>=px+61&&bx<=px+70)   bxspeed=2,byspeed=1,strcpy(dir,"tr") ;
  sndplay(500);
  if(bx<=px||bx>=px+70)      getch(),strcpy(dir,s) ;
 }
 //-------------------------ball tuoch square---------------//
 bts(char s[3])
 { scr+=100;
  squar((by-55)/15,(bx-16)/50,0);
  sq[(by-55)/15][(bx-16)/50]=1;
  strcpy(dir,s) ;
  sndplay(500);
  win();
  printlevel();
 // else   sndplay(1500),getch(),strcpy(dir,"tl") ;
 }

//-----------------------mainform--------------------------//
mainfrm()
{
backfrm();
setcolor(4);
settextstyle(4,0,6);
outtextxy(x-145,y-200, "  GAME");
outtextxy(x-145,y-100, "DX==BALL");
setcolor(2);
outtextxy(x-145,y-150, "---------");
outtextxy(x-145,y-50, "---------");
settextstyle(1,0,3);
outtextxy(x-170,y+20, "do you wnat to play the game");
setcolor(15);
outtextxy(x-170,y+40,"------------------------");

button(x+100,y+100,x+150,y+125,1);
button(x-100,y+100,x-50,y+125,1);
setcolor(15);
settextstyle(2,0,6);
outtextxy(x-90,y+100, " No");
outtextxy(x+110,y+100,"Yes");
 showmouseptr();
 while(1)
 {
   getmousepos(&stat ,&px ,&py);
   if(stat==1&&px>=420&&px<=470&&py>=340 &&py<=365)
   break;
   if(stat==1&&px>=220&&px<=270&&py>=340 &&py<=365)
   exit();
  // gotoxy(10,10);
  // printf("%d ,%d ,%d",px,py ,stat);
   }
  hidemouseptr();
   backfrm();
}
//--------------------win()-------------------------------//
win()
{
int temp=0;
for(a=0;a<5;a++)
  for(b=0;b<12;b++)
       if( sq[a][b]==1)   temp++;

 if(temp==60)
   {
   setcolor(4);
   settextstyle(4,0,4);
   outtextxy(x-145,y, " You Win The Game");
   initmouse();
   showmouseptr();
    while(1)
   {
    getmousepos(&stat ,&px ,&py);
   delay(11);
   if(stat==1)        break;
   }

   mainfrm();
   lavel(2);
   printlevel();
   restrictmouseptr(16,500,540,500);
   }
}
//--------------------------lavel-----------------------//
 lavel(int lbl)
{
switch(lbl)
  {
   case 1:
		    for(a=0;a<5;a++)
		     for(b=0;b<12;b++)
		        sq[a][b]=0;
      break;
   case 2:
		  for(a=0;a<5;a++)
		   for(b=0;b<12;b++)
		    if(b<=a||b>a+5)
		    sq[a][b]=1;
   break;
   default:
		    for(a=0;a<5;a++)
		      for(b=0;b<12;b++)
		        if(b<=a||b>a+5)
		 		 sq[a][b]=1;
   }
}
//------------------------print level---------------//
 printlevel()
{
for(a=0;a<5;a++)
  for(b=0;b<12;b++)
   {
   if(sq[a][b]==0)
   squar(a,b,1);

//   sq[a][b]=0;
   }
}
