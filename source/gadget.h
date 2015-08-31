#ifndef GADGET_H
#define GADGET_H 

#include "objeto.h"
#include "globero.h"
#include "piedra.h"

#include "constantes.h"

class Gadget: public _2D::ObjetoInmovil{
public:
	virtual void colisionConPiedra(Piedra* p) = 0;
	virtual void colisionConGlobero(Globero * g) = 0;
	Gadget(const _2D::Rectangulo& pos, Imagen * r, Color f = Color::negro):_2D::ObjetoInmovil(pos,r,f){

	}
	virtual void dibujar(){
		ObjetoInmovil::dibujar();
	}
	virtual bool colisiona(const _2D::Rectangulo& r){
		return ObjetoInmovil::colisiona(r);
	}
	virtual bool colisiona(_2D::Objeto* o){
		return _2D::ObjetoInmovil::colisiona(o);
	}
};

#endif