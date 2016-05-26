#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<process.h>
#include<mouse.h>
#include<alloc.h>
#include<dos.h>
#include<math.h>
int x[100],y[100];
void func_itoa(int x,int y);
void muestra_puntos(int num);

void main (void){
	char r;
	int adapter=DETECT,modo,t=0,c=320,e=240,men=0,n=0,h,k,c1,e1,mayo=-99999,meno=99999,l=0;
	initgraph (&adapter,&modo,"C:\\tc20\\bin");
	setbkcolor(BLACK);

	mver();
	msituar(1,320,240);

	while(!kbhit()){
		c=mxpos(1);
		e=mypos(1);
		func_itoa(c,e);

			if(mclick()==1&&men!=1){

			while(n==0){
				x[t]=mxpos(1);
				y[t]=mypos(1);
			  	setcolor(YELLOW);
			  	mocultar();
				line(c,e,x[t],y[t]);
				mver();
				c1=h=x[t];
				e1=k=y[t];
				n=1;
				t++;
			}
			x[t]=mxpos(1);
			y[t]=mypos(1);
			setcolor(YELLOW);
			mocultar();
			line(h,k,x[t],y[t]);
			mver();
			h=mxpos(1);
			k=mypos(1);
			t++;
	    } else if(mclick()==2){
			line(h,k,c1,e1);
			men=1;
		}
	}
	muestra_puntos(t);
	do{
	r=getch();
	switch(r)
	case 13:{
	for(n=0;n<=t;n++){
		if(y[n]>mayo){
			mayo=y[n];
			h=n;

		}else if(y[n]<meno){
			meno=y[n];
			k=n;

		}
	}
	setcolor(RED);
	line(x[h],y[h],x[k],y[k]);}

	}while(r!=27);
	getch();
	closegraph();
}
void func_itoa(int x, int y){
   char x1[10],x2[10];
   delay(100);
   settextstyle(11,0,1);
  itoa(x,x1,10);
  itoa(y,x2,10);
  setfillstyle(1,GREEN);
  bar(40,450,100,460);
  outtextxy(40,450,"X=");
  outtextxy(60,450,x1);
  bar(580,450,640,460);
  outtextxy(580,450,"Y=");
  outtextxy(600,450,x2);
}

void muestra_puntos(int num){
int ini,g=50,oc=0;
char equis[10],ye[10],oie[100];
setfillstyle(1,BLUE);
bar(460,0,640,480);
for(ini=1;ini<num-1;ini++){
	setcolor(YELLOW);
	itoa(x[ini],equis,10);
	itoa(y[ini],ye,10);
	outtextxy(490,g=g+15,equis);
	outtextxy(510,g=g+15,ye);
	setcolor(RED);
	itoa(oc,oie,10);
	outtextxy(x[ini]-15,y[ini],oie);
	oc++;
}
}
