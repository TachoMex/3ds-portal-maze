#ifndef MURO_H
#define MURO_H 

#include "gadget.h"

class Muro: public Gadget{
public:
	virtual void colisionConPiedra(Piedra* p);
	virtual void colisionConGlobero(Globero* g);
	virtual void dibujar();
	virtual bool colisiona(_2D::Objeto * o);
	virtual bool colisiona(const _2D::Rectangulo& r);
	Muro(const _2D::Rectangulo& r):Gadget(r,nullptr, fondo_renders){
	}
};


void Muro::colisionConPiedra(Piedra* p){
	p->colisionado = true;
}

void Muro::colisionConGlobero(Globero* g){
	int dif = 0;
	auto ruta = g->desplazamiento();
	auto ruta2 = g->desplazamientoSuperior();
	int caso = 0; //Pendiente
	switch(caso){
		case 1:
			dif = ruta.fin.y - this->posicion.fin.y;
			g->posicion -= _2D::Punto(0,dif);
			g->velocidad.y = 0; 
			g->suelo = true;
		break;
		case 2:
			dif = this->posicion.fin.x - ruta.fin.x;
			g->posicion += _2D::Punto(dif,0);
			g->velocidad.x = 0; 
		break;
		case 3:
			dif = ruta2.fin.y - this->posicion.inicio.y;
			g->posicion -= _2D::Punto(0,dif);
			g->velocidad.y = g->aceleracion.y; 
		break;
		case 4:
			dif = ruta2.fin.x - this->posicion.inicio.x;
			g->posicion -= _2D::Punto(dif,0);
			g->velocidad.x = 0; 

		break;
		default:
		break;
	}	
}

void Muro::dibujar(){
	gfxFillRect(GFX_TOP, GFX_LEFT, this->posicion,ColorMuros);
}


bool Muro::colisiona(_2D::Objeto * o){
	return  Gadget::colisiona(o);
}

bool Muro::colisiona(const _2D::Rectangulo& r){
	return  Gadget::colisiona(r);
}


#endif
