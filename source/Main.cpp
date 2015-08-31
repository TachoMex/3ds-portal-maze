#include <3ds.h>
#include <vector>
#include "imagen/gestor.h"
#include "gfx2.h"
//#include "piedra.h"
#include "constantes.h"
#include "temporizador.h"
#include <iostream>
using namespace std;
//using namespace _2D;


//Juego * juego;

void setup(){
	srvInit();
	aptInit();
	gfxInitDefault();
	gfxSet3D(0);
	gfxSetDoubleBuffering (GFX_TOP, 1);
	consoleInit(GFX_BOTTOM, NULL);
	hidInit(NULL);
}



int game_loop(){
	//Inicializar variables
	int ciclos_aceleracion = 0;
	int keys=0;
	bool salir = false;
	//srand(time(NULL));

	/*ofstream vvv("hola.txt");
	vvv.write("hola mundo", 10 );
	vvv.close();*/

	cout<<"hola mundo\n";
	gfxFlushBuffers();
	gfxSwapBuffers();
	gspWaitForVBlank();
	Temporizador temp;

	while(aptMainLoop() and not salir){
		hidScanInput ();
		keys = hidKeysDown ();
		if(keys & KEY_START){
			salir = true;
		}
		if(keys & KEY_A){
		//	printf("%i %i\n",p->x, p->y);
		}
		if(keys & KEY_B){
		}
		cout<<"hola mundo"<<temp.msegundos()<<'\n';
		gfxFlushBuffers();
		gfxSwapBuffers();
	}
	return -1;

}

int main (void) {
	setup();
	do {
		if (game_loop () == -1) break;
	} while (1 == 0);
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}
