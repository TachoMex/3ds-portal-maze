#ifndef PIEDRA_H
#define PIEDRA_H 

#include "objeto.h"
#include "constantes.h"

const int piedra_x = 8;
const int piedra_y = 8;

class Piedra: public _2D::ObjetoMovil{
public:
	bool colisionado;
	Piedra(const _2D::Punto& pos, const _2D::Punto& vel):_2D::ObjetoMovil(_2D::Rectangulo(pos, piedra_x, piedra_y),renders[piedrarender],fondo_renders, vel, v_grav*0.2){
		colisionado = false;
	}
};

#endif