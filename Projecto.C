#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<process.h>
#include<mouse.h>
#include<alloc.h>
#include<dos.h>
#include<math.h>
int P[100][2];
void func_itoa(int x,int y);
void logo();
void muestra_puntos(int num);
void diagonales(int p);
void main (void){
	char r,counter[10];
	int adapter=DETECT,modo,t=0,c=320,e=240,men=0,n=0,h,k,c1,e1,mayo=-99999,meno=99999,l=0;
	initgraph (&adapter,&modo,"C:\\tc20\\bin");
	setbkcolor(BLACK);
	logo();
	mver();
	msituar(1,320,240);

	while(!kbhit()){
		n=0;
		c=mxpos(1);
		e=mypos(1);

		func_itoa(c,e);

			if(mclick()==1&&n!=1){
			delay(100);
			if(t==0){

				P[t][0]=mxpos(1);
				P[t][1]=mypos(1);
			  	mocultar();
				putpixel(P[t][0],P[t][1],YELLOW);
				mver();
				c1=h=P[t][0];
				e1=k=P[t][1];
				itoa(t,counter,10);
				outtextxy(0,0,counter);
				n=1;
				t++;
			}
			else if(t==1){
				P[t][0]=mxpos(1);
				P[t][1]=mypos(1);
				setcolor(YELLOW);
				line(h,k,P[t][0],P[t][1]);

				h=P[t][0];
				k=P[t][1];
				itoa(t,counter,10);
				setfillstyle(1,BLACK);
				bar(0,0,20,20);
				outtextxy(0,0,counter);

				t++;

				n=1;
			}else if(t>=2){
			P[t][0]=mxpos(1);
			P[t][1]=mypos(1);
			setcolor(YELLOW);
			mocultar();
			line(h,k,P[t][0],P[t][1]);
			mver();
			h=mxpos(1);
			k=mypos(1);
				itoa(t,counter,10);
				setfillstyle(1,BLACK);
				bar(0,0,20,20);
				outtextxy(0,0,counter);

			t++;
			n=1;
			}
		} else if(mclick()==2){
			setcolor(YELLOW);
			line(h,k,c1,e1);

			muestra_puntos(t);


			n=1;
		}
	}


	do{
	r=getch();
	switch(r)
	case 13:{

	itoa(t,counter,10);
	outtextxy(290,440,"n� puntos");
	outtextxy(290,450,counter);
	diagonales(t);


	}

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
bar(460,0,640,440);
outtextxy(490,50,"x");
outtextxy(530,50,"y");

for(ini=0;ini<num;ini++){
	setcolor(YELLOW);
	itoa(P[ini][0],equis,10);
	itoa(P[ini][1],ye,10);

	outtextxy(490,g=g+15,equis);
	outtextxy(530,g,ye);

	setcolor(RED);
	itoa(oc,oie,10);
	outtextxy(470,g,oie);
	outtextxy(P[ini][0]-15,P[ini][1],oie);
	oc++;
}

}
void diagonales(int p){
int n,l;
char m[10],h[10];
setcolor(RED);
	for(n=0;n<=p-1;n++){
		for(l=0;l<=p-1;l++){
		if((n-l)==1){
		setcolor(BLUE);
		line(P[n][0],P[n][1],P[l][0],P[l][1]);
		delay(1000);
		}else if((n-l)<=0){
		setcolor(RED);
		line(P[n][0],P[n][1],P[l][0],P[l][1]);
		itoa(n,m,10);
		itoa(l,h,10);
		setfillstyle(1,BLACK);
		bar(0,0,30,25);
		outtextxy(0,0,m);
		outtextxy(0,10,h);
		delay(1000);
		}else if((n-l)==(p-1)){
			delay(1000);
			setcolor(BLUE);
			line(P[n][0],P[n][1],P[l][0],P[l][1]);
		}
		}
	}
}
void logo(){
	setfillstyle(1,GREEN);
	bar(0,440,640,480);
	setfillstyle(1,BLUE);
	bar(460,0,640,440);
}