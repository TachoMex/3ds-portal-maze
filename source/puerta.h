#ifndef PUERTA_H
#define PUERTA_H 

#include "muro.h"

class Puerta: public Muro{
public:
	bool abierta;
	void colisionConGlobero(Globero* g);
	void colisionConPiedra(Piedra *p);
	Puerta(const _2D::Rectangulo& r, bool a = false):Muro(r){
		abierta = a;
	}
	void dibujar();
	virtual bool colisiona(Objeto * o);
	virtual bool colisiona(const _2D::Rectangulo& r);
};

void Puerta::colisionConGlobero(Globero* g){
	if(not abierta){
		Muro::colisionConGlobero(g);
	}
}

void Puerta::colisionConPiedra(Piedra *p){
	if(not abierta){
		Muro::colisionConPiedra(p);
	}
}


void Puerta::dibujar(){
	if(abierta){
		gfxFillRect(GFX_TOP, GFX_LEFT, this->posicion, ColorPuertasAbierta);
	}else{
		gfxFillRect(GFX_TOP, GFX_LEFT, this->posicion, ColorPuertasCerrada);
	}
}

bool Puerta::colisiona(_2D::Objeto * o){
	return not abierta and Gadget::colisiona(o);
}

bool Puerta::colisiona(const _2D::Rectangulo& r){
	return not abierta and Gadget::colisiona(r);
}

#endif
