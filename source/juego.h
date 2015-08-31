#ifndef JUEGO_H
#define JUEGO_H 

#include "globero.h"
#include "piedra.h"
#include "gadget.h"
#include "muro.h"
#include "portal.h"
#include "meta.h"
#include "trampa.h"
#include "boton.h"
#include "rehilete.h"
#include "puerta.h"
#include "temporizador.h"
#include <vector>




class Juego{
public:
	Globero * jugador;
	Temporizador cronometro;
	Temporizador cronometroPiedras;
	std::vector<Piedra*> piedras;
	std::vector<Gadget*> gadgets;
	_2D::Rectangulo pos_ventana;
	void evento(unsigned char);
	void iterar();
	void inicializaJuego(int , int );
};


void Juego::evento(unsigned char e){
/*	switch(e){
		case 'w':
			jugador->salto();
			break;
		case 'a':
			jugador->izquierda();
			break;
		case 'd':
			jugador->derecha();
			break;
		case ' ':
			if(cronometroPiedras.msegundos() >= delayPiedra){	
				piedras.push_back(new Piedra(jugador->posicion.inicio+_2D::Punto(jugador_x/2,jugador_y/2), (jugador->orientacion()==IZQUIERDA?v_piedrai:v_piedrad)));
				cronometroPiedras.reiniciar();
			}
			break;
	} 
*/
}

void Juego::iterar(){
		gfxClearBuffer(GFX_TOP, GFX_LEFT);
		int now_time;
		int last_time =  svcGetSystemTick();
		if(jugador->meta){
			std::cout<<"Ya gano :P"<<std::endl;
			//Evento de terminacion de nivel
		}
		if(jugador->colisionado){
			std::cout<<"Ya perdio :v"<<std::endl;
			//Evento de reiniciar nivel y gestion de vidas
		}

		for(Gadget* g:gadgets){
			g->dibujar();
		}
		jugador->dibujar();
		jugador->iterar();
		jugador->limitar(pos_ventana);
		jugador->aplicarFriccion(v_friccion);

		for(Gadget* g : gadgets){
			if(g->colisiona(jugador)){
				g->colisionConGlobero(jugador);
			}
			for(Piedra * p : piedras){
				if(g->colisiona(p)){
					g->colisionConPiedra(p);
				}
			}
		}

		for(int i=0;i<piedras.size();i++){
			if(!pos_ventana.colision(piedras[i]->posicion) or piedras[i]->colisionado){	
				delete piedras[i];
				piedras.erase(piedras.begin()+i--);
			}
		}

		for(auto p: piedras){
			p->dibujar();
			p->iterar();
			//p->aplicarFriccion(v_friccion);
		}
		gspWaitForVBlank();
		gfxFlushBuffers();
		gfxSwapBuffers();
		now_time = svcGetSystemTick ();
		if (now_time < last_time + FPS) 
			svcSleepThread (last_time + FPS - now_time);
}

void Juego::inicializaJuego(int mapax, int mapay){
	pos_ventana = _2D::Rectangulo(_2D::Punto(), mapax, mapay);
	jugador = new Globero(_2D::Rectangulo(_2D::Punto(), jugador_x, jugador_y), renders[BFSaltoIzq], fondo_renders, _2D::Punto(),v_grav );
	gadgets.push_back(new Muro(_2D::Rectangulo(_2D::Punto(100,100),100, 100)));
	gadgets.push_back(new Puerta(_2D::Rectangulo(_2D::Punto(100,0),20, 100)));
	gadgets.push_back(new Boton(_2D::Rectangulo(_2D::Punto(250,200),20,20), (Puerta*)gadgets.back()));
	gadgets.push_back(new Rehilete(_2D::Punto(300,150), 1, 0, 1, 1, 10,70));
	Portal * p1;
	Portal * p2;

	p1 = new Portal(_2D::Rectangulo(_2D::Punto(0,250),20, 40),2); //
	p2 = new Portal(_2D::Rectangulo(_2D::Punto(380,250),20, 40),4);//
	p1->salida = p2;
	p2->salida = p1;
	gadgets.push_back(p1);
	gadgets.push_back(p2);

	p1 = new Portal(_2D::Rectangulo(_2D::Punto(150,0),40,20),1);
	p2 = new Portal(_2D::Rectangulo(_2D::Punto(200,280),40,20),3);
	p1->salida = p2;
	p2->salida = p1;
	gadgets.push_back(p1);
	gadgets.push_back(p2);

	PortalGrande * pg1;
	PortalGrande * pg2;

	pg1 = new PortalGrande(_2D::Rectangulo(_2D::Punto(50,0), 80, 40), 1);
	pg2 = new PortalGrande(_2D::Rectangulo(_2D::Punto(320,0), 80, 40), 1);

	pg1 -> salida = pg2;
	pg2 -> salida = pg1;

	gadgets.push_back(pg1);
	gadgets.push_back(pg2);
}

#endif