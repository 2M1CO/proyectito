#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<process.h>
#include<mouse.h>
#include<alloc.h>
#include<dos.h>
#include<math.h>

#define CX mxpos(1)
#define CY mypos(1)
#define MouseC mclick()

#define X 0
#define Y 1
#define DIM 2  /*dimension de los puntos*/
#define TRI 3	/*numero de vertices de un triangulo*/
#define CORD 4	/*numero de coordenadas de 2 puntos*/
#define PMAX 50 /*numero maximo de puntos para poligono*/

#define COLCURS 8     /*Color del Cursor con las direccionales*/
#define TAM_CURS 8    /*Color del Cursor con las direccionales*/
#define ARRIBA 72
#define ABAJO  80
#define IZQUIERDA 75
#define DERECHA 77

typedef enum {FALSE,TRUE} bool;
typedef int tPointi[DIM];  /*puntos de tipo entero*/
typedef tPointi tPolygoni[PMAX];  /*poligono de enteros*/

bool Left(tPointi a, tPointi b, tPointi c), LeftOn(tPointi a,tPointi b,tPointi c), Collinear(tPointi a, tPointi b, tPointi c),Between(tPointi a, tPointi b, tPointi c),
Xor(bool x, bool y),Diagonalie(int i,int j,int n,tPolygoni P),InCone(int i,int j,int n,tPolygoni P),Diagonal(int i, int j, int n, tPolygoni P),
extreme(tPolygoni P,int s,int i,int j),IntersectProp(tPointi a, tPointi b, tPointi c, tPointi d),concavo(int i,int n,tPolygoni P),Imply(tPointi q,tPolygoni P,int n),antihorario(tPolygoni P,int n,int labels[]);

int Area2(tPointi a, tPointi b, tPointi c), aris_ext(tPolygoni P,int s,int aris[][CORD]), punt_ext(tPolygoni P,int labels[],int n),
ReadPoints(tPolygoni P), Border(tPointi q,tPolygoni P,int n);
int punto_medio(int t, int P[][2]);
int arriba_puntos(int t, int P[][2], int ggg);
int abajo_puntos(int t, int P[][2], int ggg);

void etiquetar(int labels[],int n);
void PointAssign(tPointi a,tPointi b);
void ClipEar1(int i,int n,tPolygoni P,int labels[]);
void Triangulate1(int n, tPolygoni P,int vertex[][TRI]);
void cusp(int t, int P[][2]);

int BANDERA=0, xc[100],yc[100];
char r,counter[10];
int t=0,c=320,e=240,men=0,n=0,h,k,c1,e1,P[100][2];


void func_itoa(int x,int y);
void LimpiarPuntos(void);
void muestra_puntos(int num,int [][2]);
void Interfaz(void);
void Archivo(void);
void Menu1(void);
void Edit(void);
void capun (void);
void Cerrar_Etiq(void);
void Triang_P(void);
void Ayuda(void);
void Ayuda2(void);
void Mouse(void);
void Teclado(void);
void dib_cursor(int x , int y);
void xor_pixel(int x, int y);

int x = 0, y = 0, click = 0, inf = 0;
void *ImageA, *ImageL, *Help;

void main(void){
	int opc=0;
	int driver=DETECT,modo;
	initgraph(&driver,&modo,"C:\\tc20\\bin");

	Interfaz();
	
	while(opc==0){
		if(MouseC==1){
			opc=1;
		}
		if(kbhit()){
			opc=2;
		}
	}
	if(opc==2){
		mocultar();
		setfillstyle(1,LIGHTMAGENTA);
		settextstyle(1,0,1);
		bar(512,411,619,454); rectangle(511,410,620,455); outtextxy(535,420,"Teclado");
		Teclado();
	}
	if(opc==1){
		mver();
		setfillstyle(1,LIGHTMAGENTA);
		settextstyle(1,0,1);
		fillellipse(70,437,40,25);
		ellipse(70,437,0,360,40,25);   outtextxy(45,425,"Mouse");
		Mouse();
	}


	getch();
	closegraph();
}

void Interfaz(void){
	int PartInf[52] = {
	12, 396
	,12, 468
	,628, 468
	,628, 395
	,586, 384
	,536, 377
	,501, 375
	,453, 374
	,425, 377
	,386, 381
	,346, 383
	,308, 388
	,270, 392
	,245, 395
	,214, 400
	,247, 394
	,206, 400
	,177, 403
	,152, 405
	,124, 406
	,88, 405
	,67, 406
	,46, 404
	,30, 399
	,14, 396
	,12, 396

	};

	/*********************CAMPO DE TRABAJO*********************/
	setfillstyle(1,CYAN);
	bar(0,0,640,480);

	setcolor(BLACK);
	rectangle(10,10,630,470);
	rectangle(11,11,629,469);

	line(10,60,630,60);
	line(10,61,630,61);

	/*******************Parte Inferior**************************/
	setfillstyle(1,GREEN);
	setcolor(BLACK);
	drawpoly(26,PartInf);
	fillpoly(26,PartInf);

	line(130,410,130,470); line(131,410,131,470);
	line(500,380,500,470); line(501,380,501,470);

	setfillstyle(1,LIGHTBLUE);
	settextstyle(1,0,1);
	fillellipse(70,437,40,25);
	ellipse(70,437,0,360,40,25);   outtextxy(45,425,"Mouse");

	bar(512,411,619,454); rectangle(511,410,620,455); outtextxy(535,420,"Teclado");
	bar(221,416,419,449); rectangle(220,415,420,450); outtextxy(240,420,"AYUDA DE ACCION");


	/*******************BOTONES PRINCIPALES*********************/
	settextstyle(1,0,1);
	setfillstyle(1,GREEN);
	bar(21,21,504,49);
	rectangle(20,20,210,50); outtextxy(35,24,"ARCHIVO");
	rectangle(210,20,505,50); outtextxy(225,24,"EDIT");
	setfillstyle(1,BLUE);
	rectangle(530,20,570,50);
	rectangle(580,20,620,50);
	setcolor(WHITE);
	bar(531,21,569,49); outtextxy(545,24,"?");
	setfillstyle(1,RED);
	bar(581,21,619,49); outtextxy(595,24,"X");
}

void Menu1(void){
	/**************************MENU 1***************************/
	setcolor(BLACK);
	setfillstyle(1,GREEN);
	bar(20,51,210,196);
	setfillstyle(1,BLUE);
	settextstyle(1,0,1);
	bar(26,57,204,85);
	rectangle(25,56,205,86); outtextxy(35,59,"NUEVO");
	bar(26,92,204,120);
	rectangle(25,91,205,121); outtextxy(35,95,"ABRIR");
	bar(26,127,204,155);
	rectangle(25,126,205,156); outtextxy(35,129,"GUARDAR PUNTOS");
	bar(26,162,204,190);
	rectangle(25,161,205,191); outtextxy(35,165,"SALIR");
}

void Archivo(void){
	int img;
	int L=0;
	img= imagesize(20,51,210,196);
	ImageA=malloc(img);
	mocultar();
	getimage(20,51,210,196,ImageA);
	Menu1();
	mver();
	mlimit(1,20,51,210,196);
	while(inf==0){
		if(mclick()==1){
			if( CX>=25 && CX<=205 && CY>=56 && CY<=86 ){
				L=1;
				break;
			}

			if( CX>=25 && CX<=205 && CY>=91 && CY<=121 ){
				break;
			}
			if( CX>=25 && CX<=205 && CY>=126 && CY<=156 ){
				img= imagesize(210,126,320,236);
				ImageL= malloc(img);
				mocultar();
				getimage(210,126,320,236,ImageL);
				/*********************SUB MENU 1.1****************************/
				setfillstyle(1,RED);
				bar(210,126,320,236);
				setfillstyle(1,BLUE);
				bar(216,132,314,160);
				rectangle(215,131,315,161); outtextxy(220,135,"ARCHIVO 1");
				bar(216,167,314,195);
				rectangle(215,166,315,196); outtextxy(220,170,"ARCHIVO 2");
				bar(216,202,314,230);
				rectangle(215,201,315,231); outtextxy(220,205,"ARCHIVO 3");
				mver();
				mlimit(1,210,126,320,236);
				while(inf==0){
					if(mclick()==1){
						if(CX>=215 && CX<=315 && CY>=131 && CY<=161){
							break;
						}
						if(CX>=215 && CX<=315 && CY>=166 && CY<=196){
							break;
						}
						if(CX>=215 && CX<=315 && CY>=201 && CY<=231){
							break;
						}
					}
					if(mclick()==2){
						break;
					}
				}
				mocultar();
				putimage(210,126,ImageL,COPY_PUT);
				free(ImageL);
				mver();
				break;
			}
			if(CX>=25 && CX<=205 && CY>=161 && CY<=191){
				exit(0);
			}
		}
		if(mclick()==2){
			break;
		}
	}
	mocultar();
	putimage(20,51,ImageA,COPY_PUT);
	free(ImageA);
	mver();
	mlimit(1,0,0,640,480);
	if(L==1)
		LimpiarPuntos();
	

}

void Edit(void){
	int img;
	img= imagesize(210,51,505,196);
	ImageA=malloc(img);
	mocultar();
	getimage(210,51,505,196,ImageA);
	/**************************MENU 2*****************************/
	setcolor(BLACK);
	settextstyle(1,0,1);
	setfillstyle(1,GREEN);
	bar(210,51,505,196);
	setfillstyle(1,BLUE);
	bar(216,57,499,85);
	rectangle(215,56,500,86); outtextxy(225,59,"CAPTURAR PUNTOS");
	bar(216,92,499,120);
	rectangle(215,91,500,121); outtextxy(225,95,"CERRAR POLIGONO/ETIQUETAR");
	bar(216,127,499,155);
	rectangle(215,126,500,156); outtextxy(225,129,"METODOS");
	bar(216,162,499,190);
	rectangle(215,161,500,191); outtextxy(225,165,"TRIANGULAR");
	mver();
	mlimit(1,210,51,505,196);
	while(inf==0){
		if(mclick()==1){
			if(CX>=215 && CX <= 500 && CY>=56 && CY<=86){
				BANDERA=1;
				break;					
			}
			if(CX>=215 && CX <= 500 && CY>=91 && CY<=121){
				BANDERA=2;	
				break;					
			}
			if( CX>=215 && CX<=500 && CY>=126 && CY<=156 ){
				img= imagesize(395,126,625,236);
				ImageL= malloc(img);
				mocultar();
				getimage(395,126,625,236,ImageL);
				/*********************SUB MENU 2.1****************************/
				setfillstyle(1,RED);
				bar(395,126,625,236);
				setfillstyle(1,BLUE);
				bar(401,132,619,160);
				rectangle(400,131,620,161); outtextxy(405,135,"1. EJE DE MONOTOMIA");
				bar(401,167,619,195);
				rectangle(400,166,620,196); outtextxy(405,170,"2. CUSPIDE");
				bar(401,202,619,230);
				rectangle(400,201,620,231); outtextxy(405,205,"3. TRAPEZOIDALIZACION");
				mver();
				mlimit(1,395,126,625,236);
				while(inf==0){
					if(mclick()==1){
						if(CX>=400 && CX<=620 && CY>=131 && CY<=161){
							break;
						}
						if(CX>=400 && CX<=620 && CY>=166 && CY<=196){
							/*break;*/
							cusp(t,P);
						}
						if(CX>=400 && CX<=620 && CY>=201 && CY<=231){
							break;
						}
					}
					if(mclick()==2){
						break;
					}
				}
				mocultar();
				putimage(395,126,ImageL,COPY_PUT);
				free(ImageL);
				mver();
				break;
			}
			if(CX>=215 && CX <= 500 && CY>=161 && CY<=191){
				BANDERA=4;
				break;
			}
			
		}
		if(mclick()==2){
			break;
		}
	}
	mocultar();
	putimage(210,51,ImageA,COPY_PUT);
	free(ImageA);
	mver();
	mlimit(1,0,0,640,480);
	if(BANDERA==1){
		capun();
	}
	if(BANDERA==2){
		Cerrar_Etiq();
	}
	if(BANDERA==4){
		Triang_P();
	}
	BANDERA=0;
}

void Ayuda(void){
	int img;
	img= imagesize(180,120,460,360);
	ImageA=malloc(img);
	mocultar();
	getimage(180,120,460,360,ImageA);
	/*****************************SUPPORT****************************/
	setcolor(BLACK);
	settextstyle(1,0,1);
	setfillstyle(1,GREEN);
	bar(181,121,459,159);
	rectangle(180,120,460,360); outtextxy(285,130,"SUPPORT");
	line(180,160,460,160);
	setfillstyle(1,7);
	bar(181,161,459,359);
	outtextxy(255,210,"BANEADO PAPU");
	setfillstyle(1,GREEN);
	bar(281,311,364,339);
	rectangle(280,310,365,340); outtextxy(285,314,"ACEPTAR");
	mver();
	mlimit(1,180,120,460,360);
	while(inf==0){
		if(mclick()==1){
			if( CX>=280 && CX<=365 && CY>=310 && CY<=340){
				break;
			}
		}
	}
	mocultar();
	putimage(180,120,ImageA,COPY_PUT);
	free(ImageA);
	mver();
	mlimit(1,0,0,640,480);
}

void Ayuda2(void){
	mocultar();
	setfillstyle(1,LIGHTRED); settextstyle(1,0,1); setcolor(BLACK);
	bar(221,416,419,449); rectangle(220,415,420,450); outtextxy(240,420,"AYUDA DE ACCION");
	mver();
	mlimit(1,0,0,640,480);

	while(inf==0){
		if(MouseC==2){
			mocultar();
			setfillstyle(1,LIGHTBLUE); settextstyle(1,0,1); setcolor(BLACK);
			bar(221,416,419,449); rectangle(220,415,420,450); outtextxy(240,420,"AYUDA DE ACCION");
			mver();
			break;
		}
	}
}

void Mouse(void){
	while(!kbhit()){
		CX;
		CY;
		func_itoa(CX, CY);
		if((click=mclick())==1){
			if(CX>=20 && CX<=210 && CY>=20 && CY<=50){
				Archivo();
				delay(100);
			}
			if(CX>=210 && CX<=505 && CY>=20 && CY<=50){
				Edit();
				delay(100);
			}
			/*if(CX>=530 && CX<=570 && CY>=20 && CY<=50){
				/*Ayuda();
				delay(100);*/
				
			/*}*/
			if(CX>=220 && CX<=420 && CY>=415 && CY<=450){
				Ayuda2();
				delay(100);
			}
			if(CX>=580 && CX<=620 && CY>=20 && CY<=50){
				exit(0);
			}
		}
		click=0;
	}
}

void Teclado(void){
	char r;
	do{
		func_itoa(x, y);
		r=getch();
		switch(r){
			case ARRIBA:
				/*dib_cursor(x, y);  */
				dib_cursor(x, y);
				y=y-1;
				dib_cursor(x,y);
				break;
			case ABAJO:
				/*dib_cursor(x, y);*/
				dib_cursor(x, y);
				y=y+1;
				dib_cursor(x, y);
				break;
			case DERECHA:
				/* dib_cursor(x, y);  */
				dib_cursor(x, y);
				x=x+1;
				dib_cursor(x, y);
				break;
			case IZQUIERDA:
				/* dib_cursor(x, y);   */
				dib_cursor(x, y);
				x=x-1;
				dib_cursor(x, y);
				break;
		}
		if(r==27)
			exit(0);
	}while(r!=27);
	getch();
}

void dib_cursor(int x, int y){
	int i;
	for (i=0; i<TAM_CURS; i++){
		xor_pixel(x-i,y);
		xor_pixel(x+i,y);
		xor_pixel(x,y-i);
		xor_pixel(x,y+i);
	}
	xor_pixel(x,y);
}

void xor_pixel(int x, int y){
	putpixel(x,y,COLCURS^getpixel(x,y));
}



void capun (void){
	
	mocultar();
	msituar(1,320,240);
	mlimit(1,17,67,495,365);
	mver();
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
				n=1;
				t++;
			}else if(t==1){
				P[t][0]=mxpos(1);
				P[t][1]=mypos(1);
				setcolor(YELLOW);
				line(h,k,P[t][0],P[t][1]);
				h=P[t][0];
				k=P[t][1];
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
				t++;
				n=1;
			}
		} 
		if(MouseC==2){
			mlimit(1,0,0,640,480);
			break;
		}
			
	}
}
			
void Cerrar_Etiq(void){
	mocultar();
	line(h,k,c1,e1);
	mver();
	muestra_puntos(t,P);
	mver();
	mlimit(1,0,0,640,480);	
}

void Triang_P(void){
	mocultar();
	Triangulate1(t,P,P);
	mver();
	mlimit(1,0,0,640,480);
}

void func_itoa(int x, int y){
	char x1[10],x2[10];
	delay(100);
	setcolor(BLACK);
	settextstyle(11,0,1);
	itoa(x,x1,10);
	itoa(y,x2,10);
	setfillstyle(1,GREEN);
	bar(175,430,200,440);
	outtextxy(155,430,"X=");
	outtextxy(175,430,x1);
	bar(455,430,499,440);
	outtextxy(435,430,"Y=");
	outtextxy(455,430,x2);
}

void muestra_puntos(int num,int P[][2]){
	int ini,g=90,oc=0;
	char equis[10],ye[10],oie[100];
	settextstyle(1,0,1);
	setfillstyle(1,LIGHTRED);
	bar(500,62,628,370);
	outtextxy(535,70,"x");
	outtextxy(585,70,"y");
	
	setcolor(BLACK);
	settextstyle(11,0,1);
	itoa(t,counter,10);
	outtextxy(530,355,"N?   Puntos");
	outtextxy(550,355,counter);

	for(ini=0;ini<num;ini++){
		settextstyle(11,0,1);
		setcolor(YELLOW);
		itoa(P[ini][0],equis,10);
		itoa(P[ini][1],ye,10);

		outtextxy(530,g=g+15,equis);
		outtextxy(580,g,ye);

		setcolor(RED);
		itoa(oc,oie,10);
		
		outtextxy(510,g,oie);
		settextstyle(11,0,1);
		outtextxy(P[ini][0]-15,P[ini][1],oie);
		oc++;
	}
}

void LimpiarPuntos(){
	int Ind;
	clrscr();
	Interfaz();
	for(Ind=0;Ind<100;Ind++){
		xc[Ind]=NULL;
		yc[Ind]=NULL;
	}
	n=0;
	t=0;
	men=0;
}
/****************************************************************************/
int Area2(tPointi a, tPointi b, tPointi c)
/*retorna dos veces el area del triangulo formado por a,b,c*/
{
	return((a[0] * b[1]) - (a[1] * b[0]) + (a[1] * c[0]) - (a[0] * c[1]) + (b[0] * c[1]) - (c[0] * b[1]));
}
/****************************************************************************/
bool Left(tPointi a, tPointi b, tPointi c)
/*retorna verdadero si c esta a la izquierda del segmento ab*/
{
	return Area2(a,b,c)>0;
}
/****************************************************************************/
bool LeftOn(tPointi a,tPointi b,tPointi c)
/*retorna verdadero si c esta a la izquierda o sobre el segmento ab*/
{
	return Area2(a,b,c)>=0;
}
/****************************************************************************/
bool Collinear(tPointi a, tPointi b, tPointi c)
/* retorna verdadero si los puntos a,b,c son colineales*/
{
	return Area2(a,b,c)==0;
}
/****************************************************************************/
bool Xor(bool x, bool y)
/*o exclusivo. Retorna verdadero si exactamente uno de los argumentos es
verdadero. Los argumentos son negados para asegurar que tienen valores 0/1*/
{
	return !x^!y;
}
/****************************************************************************/
bool IntersectProp(tPointi a, tPointi b, tPointi c, tPointi d)
{
	if(Collinear(a, b, c)||Collinear(a, b, d)||Collinear(c, d, a)||Collinear(c, d, b))
		return (FALSE);
	return Xor(Left(a, b, c), Left(a, b, d)) && Xor(Left(c, d, a), Left(c, d, b));
}
/****************************************************************************/
bool Between(tPointi a, tPointi b, tPointi c)
/*retorna verdadero si a,b y c son colineales y el punto c yace sobre el
segmento cerrado ab*/
{
	if(!Collinear(a, b, c))
		return FALSE;
	if(a[X] != b[X])
		return((a[X] <= c[X]) && (c[X] <= b[X])) || ((a[X] >= c[X]) && (c[X] >= b[X]));
	else
		return((a[Y] <= c[Y]) && (c[Y] <= b[Y])) || ((a[Y] >= c[Y]) && (c[Y] >= b[Y]));
}
/****************************************************************************/
bool Intersect(tPointi a, tPointi b, tPointi c, tPointi d)
/*retorna verdadero if los segmentos ab y cd se intersectan propia o
impropiamente*/
{
	if(IntersectProp(a, b, c, d))
		return TRUE;
	else
		if(Between(a, b, c)||Between(a, b, d)||Between(c, d, a)||Between(c, d, b))
			return TRUE;
	else
		return FALSE;
}
/****************************************************************************/
bool Diagonalie(int i,int j,int n,tPolygoni P)
/*retorna verdadero si vi,vj una diagonal interna o externa propia de P*/
{
	int k, k1;
	for(k=0;k<n;k++)
	{
		k1 = (k + 1)%n;
		if(!((k == i) || (k1 == i) || (k == j) || (k1 == j)))
			if(Intersect(P[i], P[j], P[k], P[k1]))
				return FALSE;
	}
	return TRUE;
}
/****************************************************************************/
bool InCone(int i,int j,int n,tPolygoni P)
/*retorna verdadero si la diagonal i,j es estrictamente interna al poligono P
en la vecindad del punto final i*/
{
	int i1, in1;
	i1 = (i + 1)%n;
	in1 = (i + n - 1)%n;
	if(LeftOn(P[in1], P[i],P[i1]))
		return Left(P[i], P[j], P[in1]) && Left(P[j], P[i], P[i1]);
	else
		return !(LeftOn(P[i], P[j], P[i1]) && LeftOn(P[j], P[i], P[in1]));
}
/****************************************************************************/
bool Diagonal(int i, int j, int n, tPolygoni P)
/*retorna verdadero si i,j es una diagonal propia interna de P*/
{
	return(InCone(i, j, n, P) && Diagonalie(i, j, n, P));
}
/****************************************************************************/
void PointAssign(tPointi a,tPointi b)
/*asigna los puntos de la coordenada a a b*/
{
	int i;
	for(i=0;i<DIM;i++)
		a[i] = b[i];
}
/****************************************************************************/
void ClipEar1(int i,int n,tPolygoni P,int labels[])
/*remueve P[i] al copiar p[i+1]. Actualiza los vertices del poligono una
vez hecha una triangulacion*/
{
	int k;
	for(k=i;k<(n-1);k++)
	{
		PointAssign(P[k],P[k+1]);
		labels[k] = labels[k+1];
	}
}
/****************************************************************************/
void TriRecurse(int n,tPolygoni P,int labels[],int vertex[][TRI],int *cont)
{
	int i,i1,i2,x,y,x1,y1;
	if(n>3)
		for(i=0;i<n;i++)
		{
			i1 = (i + 1)%n;
			i2 = (i + 2)%n;
			/*analiza si diagonal i es i2 es interna y si su interseccion con
			el poligono es apropiada*/
			if(Diagonal(i,i2,n,P))
			{ 	
				x=P[i][0];
				y=P[i][1];
				x1=P[i2][0];
				y1=P[i2][1];
				vertex[*cont][0]=labels[i];
				vertex[*cont][1]=labels[i1];
				vertex[*cont][2]=labels[2];
				line(x,y,x1,y1);
				*cont++;
				ClipEar1(i1,n,P,labels);
				TriRecurse(n-1,P,labels,vertex,cont);
				break;
			}
		}
}
/****************************************************************************/
void Triangulate1(int n, tPolygoni P,int vertex[][TRI])
/*triangula el poligono P, imprime las coordenadas de los puntos finales*/
{
	tPolygoni Pt;
	int labels[PMAX],cont=0,poly[2*PMAX],i;
	for(i=0;i<n;i++)
	{
		PointAssign(Pt[i],P[i]);
		labels[i]=i;
		poly[cont]=P[i][0];
		poly[++cont]=P[i][1];
		cont++;
	}
	/* printf("Diagonales de la triangulaci?n : \n");*/
	poly[cont]=P[0][0];
    poly[cont+1]=P[0][1];
    drawpoly(n+1,poly);	
	setcolor(RED);
	TriRecurse(n,Pt,labels,vertex,&cont);
}
/****************************************************************************/
bool concavo(int i,int n,tPolygoni P)
/*retorna  verdadero si el vertice es concavo. En otro caso retorna falso*/
{
	int i1,in1;
	i1=(i+1)%n;
	in1=(i+n-1)%n;
	if(!(LeftOn(P[in1],P[i],P[i1])))
		return TRUE;
	else
		return FALSE;
}
/****************************************************************************/
bool antihorario(tPolygoni P,int n,int labels[])
/*Encuentra el punto mas bajo(p) en Y y mas a la derecha en X.Luego calcula su
 punto anterior(p-) y posterior(p+) y calcula el area formada por p-,p,p+.
 Si esta es positiva los puntos estan en sentido antihorario y la funcion
 retorna TRUE, en otro caso retorna FALSE.*/
{
	int i,v,vplus,vless,low;
	low=P[0][1];
	v=labels[0];
	for(i=1;i<n;i++)
	{
		if(low>P[i][1])  /*comparando las coordenadas en y*/
		{
			low=P[i][1];    /*asignando el de menor coordenada en y*/
			v=labels[i];
		}
		if(low==P[i][1])      /*comparando la coordenada en x*/
		/*asignando el y de coordenada mayor en x*/
			v=(P[v][0]<P[i][0])?labels[i]:labels[v];
	}
	vplus=(v+1)%n;    /*calculando el v+*/
	vless=(v+n-1)%n;  /*calculando el v-*/
	if(Area2(P[vless],P[v],P[vplus])>0)   /*calculando el area */
		return TRUE; /*si el area es positiva return TRUE*/
	else
		return FALSE;   /*en otro caso return FALSE*/
}
/****************************************************************************/
bool Imply(tPointi q,tPolygoni P,int n)
/*retorna True si el punto q es interno al poligono P y False en otro caso*/
{
	int i,i1,d,cruce=0;
	tPolygoni Pt; /*se declara Pt para evitar errores al pedir un nuevo
					punto de consulta para el mismo poligono P*/
	double x;
	for(i=0;i<n;i++)
		for(d=0;d<DIM;d++)
			Pt[i][d]=P[i][d]-q[d];  /*trasladando el poligono al eje x*/
	for(i=0;i<n;i++)
	{
		i1=(i+n-1)%n;  /*el vertice anterior del poligono*/
		if(((Pt[i][Y]>0)&&(Pt[i1][Y]<=0))||((Pt[i1][Y]>0)&&(Pt[i][Y]<=0)))
		/*compara si uno de los puntos finales de la arista esta estrictamente
		arriba de la recta r (q) y el otro punto final esta abajo o sobre r*/
		{
			x=(Pt[i][X]*Pt[i1][Y]-Pt[i1][X]*Pt[i][Y])/(double)(Pt[i1][Y]-Pt[i][Y]);
			if(x>0)
				cruce++;
		}
	}
	if((cruce%2)==1)  /*si el numero de cruces es impar q es interno*/
		return TRUE;
	else
		return FALSE;
}
/****************************************************************************/
int Border(tPointi q,tPolygoni P,int n)
{
	int i,i1;
	for(i=0;i<n;i++)
	{
		i1=(i+n-1)%n;
		if(Between(P[i1],P[i],q)) /*si el punto q esta entre i,i1 esta en la frontera*/
			return(0);   /*el 1 indica que el punto q esta en la frontera de P*/
	}
	if(Imply(q,P,n))
		return(1); /*el 2 indica que el punto q es interno al poligono P*/
	else
		return(-1); /*el 0 indica que el punto q no pertenece al poligono P*/
}
/****************************************************************************/
void etiquetar(int labels[],int n)
{
	int i;
	for(i=0;i<n;i++)
		labels[i]=i;
}
/****************************************************************************/
bool extreme(tPolygoni P,int s,int i,int j)
/*Determina si una arista es extrema o no.Si P[k] no esta a la izquierda o
	en P[i],P[j](se utilizo la negacion de la funcion LeftOn),entonces, no
	es extrema(retornando FALSE).Retorna TRUE cuando la arista es extrema,
	es decir que todos los puntos estan a la izquierda de ella*/
{
	int k;
	for(k=0;k<s;k++)
		if((k!=i)&&(k!=j))
			if(!LeftOn(P[i],P[j],P[k]))
				return FALSE; /*retorna TRUE si todos los puntos
						  estan a la izquierda*/
	return TRUE;
}
/****************************************************************************/
int punt_ext(tPolygoni P,int labels[],int n)
/*Encuentra los puntos extremos que determinan el cierre convexo y
reasigna los puntos y sus coordenadas en labels y P respectivamente, ademas
retorna el numero de puntos extremos. La tecnica usada en la determinacion
de los puntos extremos es que si estos son no extremos se les asigna -1 en
labels, siendo los puntos extremos los que no tiene -1 en labels. */
{
	int i,j,k,l,s=0;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
				if(j!=i)
					for(k=0;k<n;k++)
						if((k!=i)&&(k!=j))
							for(l=0;l<n;l++)
								if((l!=i)&&(l!=j)&&(l!=k))
									if(LeftOn(P[i],P[j],P[l]))
										if(LeftOn(P[j],P[k],P[l]))
											if(LeftOn(P[k],P[i],P[l]))
												labels[l]=-1;
	/*se le asigna -1 a los puntos no extremos*/
	printf("\n\nPuntos\t\tCoordenadas");
	for(i=0;i<n;i++)
		if(labels[i]!=-1)
		{     /*reasignando el arreglo de etiquetas y el P con
		     las etiquetas y puntos extremos respectivamente*/
			printf("\n%d\t\t[%d,%d]",labels[i],P[i][0],P[i][1]);
			labels[s]=i;
			P[s][0]=P[i][0];
			P[s][1]=P[i][1];
			s+=1;
		}
	return s;
}
/****************************************************************************/
int aris_ext(tPolygoni P,int s,int aris[][CORD])
/*Encuentra las aristas extremas utilizando los puntos extremos almacenados
	en labels(labels y P ya fueron reasignados en la funcion punt_ext,
	conteniendo	los puntos extremos y sus coordenadas respectivamente). y ya estoy
	hasta la verga con este codigo atte Guarda 
	Si la funcion extreme retorna TRUE	entonces imprime : el listado	de
	aristas extremas y su conexion.*/
{
	int i,j,k=0;
	printf("\n\nAristas\t\tCoordenadas\n\n");
	for(i=0;i<s;i++)
		for(j=0;j<s;j++)
			if(j!=i)
			{
				if(extreme(P,s,i,j))
				{
					aris[k][0]=P[i][X];
					aris[k][1]=P[i][Y];
					aris[k][2]=P[j][X];
					aris[k][3]=P[j][Y];
					k++;
				}
			}
	return(k);
}
/*int punto_medio(int t, int P[][2])
{
	for(ggg=0;ggg<t;ggg++)
	{
		if(P[ggg][0]>P[ggg+1][0] && P[ggg+2][0]<P[ggg+1][0])
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}
int arriba_puntos(int t, int P[][2], int ggg)
{
	for(ggg=ggg;ggg<t;ggg++)
	{
		if(P[ggg][1]>P[ggg+1][1] && P[ggg+2][1]>P[ggg+1][1])
			{
				return 1;
			}
	}
}
int abajo_puntos(int t, int P[][2], int ggg)
{
	for(ggg=ggg;ggg<t;ggg++)
	{
		if(P[ggg][1]<P[ggg+1][1] && P[ggg+2][1]<P[ggg+1][1])
			{
				return 1;
			}
	}
}*/
void cusp(int t, int P[][2])
{
	int ggg;
	/*punto_medio(t,P);
	arriba_puntos(t,P);*/
	for(ggg=0;ggg<t;ggg++)
	{
		if(P[ggg][1]>P[ggg+1][1] && P[ggg+2][1]>P[ggg+1][1])
			{
				setcolor(RED);
				outtextxy(P[ggg+1][0],P[ggg+1][1],"CS");
			}	
		if(P[ggg][1]<P[ggg+1][1] && P[ggg+2][1]<P[ggg+1][1])
			{
				setcolor(RED);
				outtextxy(P[ggg+1][0],P[ggg+1][1],"CI");
			}	
	}
}

