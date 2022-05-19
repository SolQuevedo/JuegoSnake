//tutorial snake
#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>

#define ARRIBA     72
#define IZQUIERDA  75
#define DERECHA    77    //NÚMEROS ASOCIADOS A LAS FLECHAS del teclado, le indicamos 
#define ABAJO      80
#define ESC        27

int cuerpo[200][2];//hacemos una matriz para hacer el cuerpo d la serpiente, tiene 200 de valor j, porque al comer crece
//y como no sabemos cuando va a crecer ponemos 200 y pones 2 de valor i
int n = 1;//guardamos las posiciones del cuerpo desde el 1, va a ir cambiando con cada iteración para guardar las distintas posiciones del cuerpo
int tam = 10;//guarda el tamaño que va tomando el cuerpo, se va a agrandar con una iteración, 3 es el valor al alzar que se eleigió
//se pintan dos asteríscos aunque ponga 3, porque nunca dejamos que se guarden coordenadas en la pos tam,cuando n es = a tam
int x = 10, y = 12;//variables que controlan la posición de la serpiente en pantalla, y simplemente les dimos un valor inicial
int dir = 3;//lo vamos a usar para las direcciones en las que va a ir la serpiente
int xc = 30, yc = 15;//coordenadas de la comida
int velocidad = 100, h = 1;//velocidad:para que cada vez que vaya creciendo la serpeinte, se mueva más rápido
int score = 0;//para el puntaje del juego
char tecla;//ponemos esta variable para poder controlar el presionado de las flechas

void gotoxy(int x, int y){//solo queremos que haga algo, no que nos retorne por eso usamos void, esta función posiciona
	//instrucciones de la función, función que posiciona el cursor en las coordenadas
        HANDLE hCon;
        hCon=GetStdHandle(STD_OUTPUT_HANDLE);
        
        COORD dwPos;
        dwPos.X=x;
        dwPos.Y=y;
        SetConsoleCursorPosition(hCon,dwPos);
}
void pintar(){//acá vamos a delimitar la pantalla de juego
	//lineas horizontales
	 for(int i=2;i<78;i++){//la linea del eje x empieza en 2 y el eje y en el 77, la  x es la que va a ir cambiando
		//horizontales de arriba
		gotoxy(i,3); printf("%c",205);//la x que es la i ees la que cmbia y el 3 es la y
		//con %c especificamos que vamos a usar un caracter del código ascii , el  205
		//horizontales de abajo
		gotoxy(i,23); printf("%c",205);
	    //lineas verticales
	    for(int i=4;i<23;i++){
	 	gotoxy(2,i); printf("%c",186);
	 	gotoxy(77,i); printf("%c",186);
	  }
	    //esquinas, tenemos 4 esquinas
	    gotoxy(2,3); printf("%c",201);
	    gotoxy(2,23); printf("%c",200);
	    gotoxy(77,3); printf("%c",187);
	    gotoxy(77,23); printf("%c",188);
	}
}
void guardar_posicion(){//solo la queremos para guardar info
//posición de la cqabeza de la serpiente
	cuerpo[n][0] = x;//esta pocisión corresponde a la coordenada de x
	cuerpo[n][1] = y;//esta pocisión corresponde a la coordenada de y
	n++;//iteramos n ,guardamos cada posición en un nuevo espacio cuando iteramos  n
	if(n == tam) n = 1;//si n llega al valor tam, que vuelva a valer 1, no dejamos que n sobrepase a tam	
}

void dibujar_cuerpo(){
	//si i cumple el bucle entonces que en esas coordenadas diubuje el cuerpo/ponga un asterísco
	for(int i= 1;i<tam;i++){
		gotoxy(cuerpo[i][0], cuerpo[i][1]); printf("*");
	}
}

void borrar_cuerpo(){
	gotoxy(cuerpo[n][0], cuerpo[n][1]); printf(" ");//ponemos el espacio para que se "borre"	
}

void teclear(){
	    if(kbhit()){//cuando se presione una tecla
	    	tecla = getch();//entonces que tome el valor de la tecla que se presiono antes
	    	switch(tecla){
	    		case ARRIBA ://como se mueve como en rectángulos la serpiente
	    			if(dir != 2){//si no estaba yendo hacia bajo que podamos ir hacia arriba
	    			  dir = 1;
	    			  break;
	    			}
	    		case ABAJO :
	    			if(dir != 1){//si no estaba yendo hacia arriba que podamos ir hacia abajo
	    			  dir = 2;
	    			  break;
	    			}
	    		case DERECHA :
	    			if(dir != 4){//si dir es diferente de 4 le permitimos que sea 3
	    				dir = 3;
	    				break;
	    			}
	    		case IZQUIERDA ://si dir es diferente de 3 le permitimos que sea 4
	    			if(dir != 3){
	    				dir = 4;
	    				break;
	    			}
	    	}
	    }
	
}
void cambiar_velocidad(){//mientras más puntaje más lento
	if(score == h*20){//cuando el puntaje sea igual a tanto por 20
		velocidad -= 10;//que la velocidad suba, mientra más bajo sea el valor de velocidad, más rápido va
		h++;//incrementos h
	}
}
void comida(){
	if(x == xc && y == yc){//cuando la coordenada x(que es la cabeza) sea igual a la que tiene la coordenada comida, y la y (cola) sea igual a la yc de la comida
       xc = (rand()%73)+4;//rand()sirve para generar un número aleatorio,puede generar números aleatorios dentro de cualquier rango utilizando el operador de módulo.
       yc = (rand()%19)+4;//divide un número aleatorio entre 0 y18 y lo divide en 2, da resto cero y se le suma 4
       
       tam++;
       score += 10;
       gotoxy(xc,yc);printf("%c",4);//pintamos la comida
       cambiar_velocidad();
	}
}

bool game_over(){
	if(y == 3 || y == 23 || x == 2 || x == 77) return true;//si choca con el margen de arriba, o el margen de abajo, o el margen del costado izq o el der.
	//esto es para que si se choca con el mismo cuerpo se termine el juego
	for(int j= tam -1; j> 0; j--){
		if(cuerpo[j][0] == x && cuerpo[j][1] == y){//cuando cuerpo[j][0] que es la coordenada x, sea igual a x, y cuando cuerpo[j][1] que es la coordenada y sea igual a y
			return true;
		}
	}
	return false;
}

void puntos(){
	gotoxy(3,1);printf("score %d", score);//3 y 1 son las coordenadas donde quiero que aparazce el puntaje en pantalla, e imprimimos la palabra score seguido del valor del score
	//%d sirve para aclarar que vamos a poner un entero, y ponemos la variable
}


int main(){
	pintar();//con esto delimitamos el área de juego
	gotoxy(xc,yc);printf("%c",4);//pintamos la comida
    //este while va a contener toda la rutina del juego  
	while(tecla != ESC && !game_over()){// si no se presiona la tecla esc y si no se termino eljuego
	    borrar_cuerpo();//primero borramos
	    guardar_posicion();//luego guardamos la pos
	    dibujar_cuerpo();//luego pintamos, entonces en la primer pos no hay nada, entonces guarda la pos,luego la pinta y así sucesivamente, eso logra que se "mueva"
     
        comida();//la llamamos constantemente porque no sabemos cuando va a comer
        puntos();
        teclear();
        teclear();//ponemos  la función nuevamente para poder presionar una tecla en una misma interacción
        
	    if(dir == 1) y--;//hacia arriba
	    if(dir == 2) y++;//hacia abajo
	    if(dir == 3) x++;//vamos a la der
	    if(dir == 4) x--;//vamos a la izq
	    
	    Sleep(velocidad);//hace que el programa o el proceso en el que se llama, suspenda su ejecución temporalmente durante un período de tiempo en segundos especificado por el parámetro de la función
	}

	pintar();//con esto delimitamos el área de juego
	
	system("pause>NULL");//para ver todo lo que hacemos, si ponemos>NULL no muestra el mensaje predeterminddo
	return 0;
}
