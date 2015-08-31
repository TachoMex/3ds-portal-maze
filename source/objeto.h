#ifndef OBJETO2D_H
#define OBJETO2D_H 

#include "imagen/imagen.h"
#include "geometria.h"
#include "gfx2.h"


namespace _2D{
	
	class Objeto{
		public:
			virtual bool colisiona(Objeto*)const = 0;
			virtual bool colisiona(const Rectangulo&) const= 0;
			virtual void dibujar() const = 0;	
			
	};

	
	class ObjetoInmovil:public Objeto{
	public:
		Rectangulo posicion;
		Imagen * render;  
		Color fondo;

		ObjetoInmovil(const Rectangulo& pos, Imagen * r,const Color& f = Color::negro):posicion(pos), fondo(f){
			render = r;
		}

		virtual bool colisiona(const Rectangulo& r)const{
			return this->posicion.colision(r);
		}

		virtual bool colisiona(Objeto* o) const{
			return o->colisiona(posicion);
		}

		virtual void dibujar()const{
			gfxDrawPixels(GFX_TOP, GFX_LEFT, render ,posicion.inicio,fondo);
		}	

		virtual void moverA(const Punto& pos){
			posicion = Rectangulo(pos, posicion.base(), posicion.altura());
		}

	};

	
	class ObjetoMovil:public ObjetoInmovil{
	public:
		Punto aceleracion;
		Punto velocidad;
		Punto posicionAnterior;

		ObjetoMovil(const Rectangulo& pos, Imagen * r,const Color& f = Color::negro , const Punto& v = Punto(), 
			   const Punto& a = Punto()):ObjetoInmovil(pos,r,f), aceleracion(a), velocidad(v){
		}

		virtual void iterar(){
			posicionAnterior = this->posicion.inicio;
			this->posicion+=velocidad;
		}

		virtual void iterarAceleracion(){
			velocidad+=aceleracion;
		}

		virtual Linea desplazamiento(){
			return Linea(posicionAnterior, this->posicion.inicio);
		}

		virtual Linea desplazamientoSuperior(){
			return Linea(posicionAnterior, this->posicion.inicio)+(this->posicion.fin-this->posicion.inicio);
		}

		virtual void limitar(const Rectangulo& limite){
			Punto ajuste;
			if(this->posicion.inicio.x < limite.inicio.x){	
				ajuste.x -= this->posicion.inicio.x - limite.inicio.x;
				velocidad.x = 0;
			}
			if(this->posicion.inicio.y < limite.inicio.y){	
				ajuste.y -= this->posicion.inicio.y - limite.inicio.y;
				velocidad.y = 0;
			}
			if(this->posicion.fin.x > limite.fin.x){	
				ajuste.x -= this->posicion.fin.x - limite.fin.x;
				velocidad.x = 0;
			}
			if(this->posicion.fin.y > limite.fin.y){	
				ajuste.y -= this->posicion.fin.y - limite.fin.y;
				velocidad.y = 0;
			}
			this->posicion+=ajuste;
		} 

		virtual void aplicarFriccion(const Punto& f){
			int ax = std::abs(velocidad.x);
			int ay = std::abs(velocidad.y);

			int sx = velocidad.x/ax;
			int sy = velocidad.y/ay;

			velocidad.x = std::max(ax-velocidad.x/f.x,0)*sx;
			velocidad.y = std::max(ay-velocidad.y/f.y,0)*sy;
		}

		virtual bool colisiona(const Rectangulo& r){
			return ObjetoInmovil::colisiona(r);
		}
		
		virtual bool colisiona(Objeto* o){
			return ObjetoInmovil::colisiona(o);
		}

	};


}



#endif
