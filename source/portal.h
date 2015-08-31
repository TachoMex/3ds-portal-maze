#ifndef PORTAL_H
#define PORTAL_H 

#include "muro.h"

class Portal: public Muro{
public:
	Portal* salida;
protected:
	static const int angulos[4];
	int orientacion_;
	void recibirObjeto(_2D::ObjetoMovil *p, const _2D::Punto& posRelativa, int orientacion);
	void recibirPiedra(Piedra *p, const _2D::Punto& posRelativa , int orientacion);
public:
	void colisionConPiedra(Piedra *);
	virtual void colisionConGlobero(Globero *g);
	virtual void dibujar();

	Portal(const _2D::Rectangulo& r, int o):Muro(r){
		orientacion_ = o;
	}
};

const int Portal::angulos[4]={90, 0, 270, 180};


class PortalGrande: public Portal{
public:
	PortalGrande * salida;
	PortalGrande(const _2D::Rectangulo& r, int o):Portal(r,o){
	}
	void dibujar();
	void recibirGlobero(Globero *, const _2D::Punto&, int);
	virtual void colisionConGlobero(Globero *);
	virtual void colisionConPiedra(Piedra *);
};

void Portal::recibirObjeto(_2D::ObjetoMovil *p, const _2D::Punto& posRelativa, int orientacion){
	_2D::Punto direccion;
	switch(orientacion_){
		case 1:
			direccion.x = posRelativa.y;
			direccion.y = this->posicion.altura()+posRelativa.x;
		break;
		case 2:
			direccion.x = this->posicion.base()+posRelativa.x;
			direccion.y = posRelativa.y;
		break;
		case 3:
			direccion.x = posRelativa.y;
			direccion.y = -posRelativa.x;
		break;
		case 4:
			direccion.x = -posRelativa.x;
			direccion.y = posRelativa.y;
		break;
	}
	//int ajuste = (orientacion_&1 or orientacion&1? 180 : 0);
	p->moverA(posicion.inicio+direccion);
	//p->velocidad = _2D::Punto::polar(p->velocidad.norma(), -(angulos[orientacion-1]+angulos[orientacion_-1]-p->velocidad.angulo()-M_PI+ajuste));		
}

void Portal::recibirPiedra(Piedra *p, const _2D::Punto& posRelativa , int orientacion){
	recibirObjeto(p, posRelativa, orientacion);
}

void Portal::colisionConPiedra(Piedra *p){
	//auto ruta = p->desplazamiento();
	//auto ruta2 = p->desplazamientoSuperior();
	int caso = 0; //TODO
	if(orientacion_ == caso){
		int altura = 0;
		int distancia = 0;
		switch(orientacion_){
			case 1:
				altura = p->posicion.inicio.x - this->posicion.inicio.x;
				distancia = p->posicion.inicio.y - this->posicion.inicio.y;
			break;
			case 2:
				altura = p->posicion.inicio.y - this->posicion.inicio.y;
				distancia = this->posicion.fin.x - p->posicion.inicio.x;
			break;
			case 3:
				distancia = p->posicion.fin.y- this->posicion.inicio.y;
				altura = p->posicion.inicio.x- this->posicion.inicio.x;
			break;
			case 4:
				altura = p->posicion.inicio.y - this->posicion.inicio.y;
				distancia = p->posicion.fin.x - this->posicion.inicio.x;
			break;
		}
		salida -> recibirPiedra(p, _2D::Punto(altura, distancia), orientacion_);
	}else{
		Muro::colisionConPiedra(p);
	}
}

void Portal::colisionConGlobero(Globero *g){
	Muro::colisionConGlobero(g);
}

void Portal::dibujar(){
	gfxFillRect(GFX_TOP, GFX_LEFT,this->posicion, ColorPortal);
}

void PortalGrande::dibujar(){
	gfxFillRect(GFX_TOP, GFX_LEFT,this->posicion, ColorPortalGrande);
}

void PortalGrande::recibirGlobero(Globero *g, const _2D::Punto& posRelativa, int orientacion){
	Portal::recibirObjeto(g,posRelativa, orientacion);
}

void PortalGrande::colisionConGlobero(Globero *g){
	//auto ruta = g->desplazamiento();
	//auto ruta2 = g->desplazamientoSuperior();
	int caso = 0; // TODO
	if(orientacion_ == caso){
		int altura = 0;
		int distancia = 0;
		switch(orientacion_){
			case 1:
				altura = g->posicion.inicio.x - this->posicion.inicio.x;
				distancia = g->posicion.inicio.y - this->posicion.inicio.y;
			break;
			case 2:
				altura = g->posicion.inicio.y - this->posicion.inicio.y;
				distancia = this->posicion.fin.x - g->posicion.inicio.x;
			break;
			case 3:
				distancia = g->posicion.fin.y- this->posicion.inicio.y;
				altura = g->posicion.inicio.x- this->posicion.inicio.x;
			break;
			case 4:
				altura = g->posicion.inicio.y - this->posicion.inicio.y;
				distancia = g->posicion.fin.x - this->posicion.inicio.x;
			break;
		}
		salida -> recibirGlobero(g, _2D::Punto(altura, distancia), orientacion_);
	}else{
		Portal::colisionConGlobero(g);
	}
}

void PortalGrande::colisionConPiedra(Piedra *p){
	Portal::salida = salida;
	Portal::colisionConPiedra(p);
}



#endif
