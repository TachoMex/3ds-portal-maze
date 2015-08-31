#ifndef GLOBERO_H
#define GLOBERO_H 

#include "objeto.h"
#include "constantes.h"

class Globero: public _2D::ObjetoMovil{
	private:
		int orientacion_;
		bool dibujaPaso;
	public:
		bool suelo;
		bool colisionado;
		bool meta;
		
		int orientacion();
		void izquierda();
		void derecha();
		void salto();
		void dibujar();
		void iterar();
		Globero(const _2D::Rectangulo& pos, Imagen * r,const Color& f = Color::negro , const _2D::Punto& v = _2D::Punto(), const _2D::Punto& a = _2D::Punto()):_2D::ObjetoMovil(pos, r, f, v, a){
			orientacion_ = DERECHA;
			suelo = true;
			dibujaPaso = false;
			meta = false;
			colisionado = false;
		}

};

int Globero::orientacion(){
	return orientacion_;
}


void Globero::izquierda(){
	this->velocidad.x=-v_mov.x;
	orientacion_ = IZQUIERDA;
	if(dibujaPaso){
		dibujaPaso = false;
	}else{
		dibujaPaso = true;
		this->render = (suelo?renders[BFPasoIzq]:renders[BFSaltoIzq]);
	}
}

void Globero::derecha(){
	this->velocidad.x=v_mov.x;
	this->orientacion_ = DERECHA;
	if(dibujaPaso){
		dibujaPaso = false;
	}else{
		dibujaPaso = true;
		this->render = (suelo?renders[BFPasoDer]:renders[BFSaltoDer]);
	}
}

void Globero::salto(){
	this->velocidad.y=v_salto.y;
	if(dibujaPaso){
		dibujaPaso = false;
	}else{
		dibujaPaso = true;
		if(this->orientacion_==IZQUIERDA){
			this->render = renders[BFSaltoIzq];
		}else{
			this->render = renders[BFSaltoDer];
		}
	}

	suelo = false;
}

void Globero::dibujar(){
	_2D::ObjetoMovil::dibujar();
	if(suelo){
		if(this->orientacion_==IZQUIERDA){
			this->render = renders[BFParadoIzq];
		}else{
			this->render = renders[BFParadoDer];
		}
	}else{
		if(this->orientacion_==IZQUIERDA){
			this->render = renders[BFAireIzq];
		}else{
			this->render = renders[BFAireDer];
		}
	}
}

void Globero::iterar(){
	_2D::ObjetoMovil::iterar();
	if(posicion.inicio.y==0){
		suelo = true;
	}
}



#endif
