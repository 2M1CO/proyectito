/*este programa es un beta de lo que puede ser el reconocimiento si un poligono es monotono. ubica en pantalla el cursor y con el 
boton izquierdo del mouse selecciona un punto y va dibujando el poligono, podemos cerrar el poligono usando el click derecho del 
cursor lo demas esta en trabajo como hacer la linea del punto mas alto y el mas bajo con respecto al eje Y*/
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<process.h>
#include<mouse.h>
#include<alloc.h>
#include<dos.h>
#include<math.h>
void func_itoa(int x,int y);

void main (void){

	int adapter=DETECT,modo,c=320,e=240,x[100],y[100],i=0,n=0,h,k,c1,e1,mayo=-99999,meno=99999;
	initgraph (&adapter,&modo,"C:\\tc20\\bin");
	setbkcolor(BLACK);

	mver();
	msituar(1,320,240);
	while(!kbhit()){     /* mientras no se haya presionado ningun boton*/
		c=mxpos(1);  /*asignamos las variables del cursor en c para (x) y e para (y) */
		e=mypos(1);
		func_itoa(c,e);  /*esta funcion fue creada para poner en fondo de la pantalla la ubuicacion exacta del mouse */
			if(mclick()==1){     /* si clickeamos con el boton izquierdo  se tomaran devuelta los valores (x,y) de ese punto y se asignaran a un arreglo*/
		
	    		x[i]=mxpos(1);
			y[i]=mypos(1);
			while(n==0){                        /* lo que puse dentro de este ciclo es el capturar el primer punto solo para tenerlo en cuenta para cerrar*/
			  	setcolor(YELLOW);            /* el poligono */
			  	mocultar();
				line(c,e,x[i],y[i]);         /* toma el primer punto que se tomo antes de entrar al ciclo y cuando clickeamos por segunda ves dibuja una linea*/
				mver();                    /*desde el punto inicial al segundo*/
				c1=h=x[i];			/*asignamos a estas variables para no perder esos puntos (x,y) iniciales*/
				e1=k=y[i];
				n=1;                 /*rompemos el ciclo para que no vuelva a entrar ya que solo dibujaria lineas desde el primer punto a los otros*/
				i++;	
			}	
			setcolor(YELLOW);
			mocultar();
			line(h,k,x[i],y[i]);          /*ahora dibujamos lineas desde el ultimo punto registrado al actual que presionamos*/
			mver();													
			h=mxpos(1);
			k=mypos(1);
			i++;				/*esta variable contadora y controladora nos servira para registrar todos los puntos y su cantidad*/	
	    } else if(mclick()==2){                  /*click derecho*/
	    	line(h,k,c1,e1);                              /*linea desde el punto final al inicial cierre del poligono*/
		}  		
	}
	for(n=0;n<=i;n++){			/intento de hacer la linea del punto mas alto al menor*/
		if(y[n]>mayo){				/*si el punto en y es mayor que mayo se asignara a la variable mayo logrando asi capturar el indice del mayor y el mayor punto*/
			mayo=y[n];
			h=n;
		}else if(y[n]<meno){                     /*mismo proceso pero con el menor*/
			meno=y[n];
			k=n;
		}
	}
	setcolor(RED);
	line(x[h],y[h],x[k],y[k]);
	
	delay(1000);
	getch();
	closegraph();
}
void func_itoa(int x, int y){
   char x1[10],x2[10];
   delay(100);   /*este delay esta para evitar que se vea como un flasheo continuo al poner los numeros de la ubicacion del raton, cuestion estetica*/
   settextstyle(11,0,1);
  itoa(x,x1,10);      /*funcion que convierte un entero a una cadena de caracteres argumentos(int,char,formato siempre pongan 10)*/
  itoa(y,x2,10);
  setfillstyle(1,GREEN);
  bar(40,450,100,460);
  outtextxy(40,450,"X=");
  outtextxy(60,450,x1);
  bar(580,450,640,460);
  outtextxy(580,450,"Y=");
  outtextxy(600,450,x2);
}
