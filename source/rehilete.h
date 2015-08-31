#ifndef REHILETE_H
#define REHILETE_H 

#include "puerta.h"
#include "muro.h"

class Rehilete: public Muro{
private:
	Puerta *helices[4];
public:
	Rehilete(const _2D::Punto& centro, bool h1, bool h2, bool h3, bool h4, int grosor, int longitud):Muro(_2D::Rectangulo()){
		this-> posicion = _2D::Rectangulo(centro-_2D::Punto(grosor/2,grosor/2), grosor, grosor); 
		helices[0] = new Puerta(_2D::Rectangulo(_2D::Punto(posicion.inicio.x, posicion.inicio.y+grosor), grosor, longitud), h1);
		helices[1] = new Puerta(_2D::Rectangulo(_2D::Punto(posicion.inicio.x-longitud, posicion.inicio.y), longitud, grosor), h2);
		helices[2] = new Puerta(_2D::Rectangulo(_2D::Punto(posicion.inicio.x, posicion.inicio.y-longitud), grosor, longitud), h3);
		helices[3] = new Puerta(_2D::Rectangulo(_2D::Punto(posicion.inicio.x+grosor, posicion.inicio.y), longitud, grosor), h4);
	} 
	void dibujar();
	void colisionConPiedra(Piedra *p);
	void colisionConGlobero(Globero *g);
	bool colisiona(Objeto * o);
	bool colisiona(const _2D::Rectangulo& r);
};

void Rehilete::dibujar(){
	gfxFillRect(GFX_TOP, GFX_LEFT, this->posicion,  ColorHelices);
	if(not helices[0]->abierta)
		gfxFillRect(GFX_TOP, GFX_LEFT, helices[0]->posicion, ColorHelices);
	if(not helices[1]->abierta)
		gfxFillRect(GFX_TOP, GFX_LEFT, helices[1]->posicion, ColorHelices);
	if(not helices[2]->abierta)
		gfxFillRect(GFX_TOP, GFX_LEFT, helices[2]->posicion, ColorHelices);
	if(not helices[3]->abierta)
		gfxFillRect(GFX_TOP, GFX_LEFT, helices[3]->posicion, ColorHelices);
}

void Rehilete::colisionConPiedra(Piedra *p){
	Muro::colisionConPiedra(p);		
	std::swap(helices[0]->abierta, helices[1]->abierta);
	std::swap(helices[1]->abierta, helices[2]->abierta);
	std::swap(helices[2]->abierta, helices[3]->abierta);
}

void Rehilete::colisionConGlobero(Globero *g){
	for(int i=0;i<4;i++){
		if(g->colisiona(helices[i])){
			helices[i]->colisionConGlobero(g);
		}
	}
	if(g->colisiona(posicion)){
		Muro::colisionConGlobero(g);
	}
}

bool Rehilete::colisiona(_2D::Objeto * o){
	return Muro::colisiona(o) or helices[0]->colisiona(o) or 
		helices[1]->colisiona(o) or helices[2]->colisiona(o) 
		or helices[3]->colisiona(o);
}

bool Rehilete::colisiona(const _2D::Rectangulo& r){
	return Muro::colisiona(r) or helices[0]->colisiona(r) or 
		helices[1]->colisiona(r) or helices[2]->colisiona(r) 
		or helices[3]->colisiona(r);
}

#endif