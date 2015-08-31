#ifndef RECTANGULO2D_H
#define RECTANGULO2D_H
#include "linea.h"
	namespace _2D{

	class Rectangulo : public Linea{
		public:
			Rectangulo():Linea(){}
			Rectangulo(Punto a, Punto b):Linea(a, b){}
			Rectangulo(Punto a, int b, int c): Linea(a,a+Punto(b,c)){}
			int base() const{
				return this->fin.x-this->inicio.x;
			}
			int altura() const{
				return this->fin.y-this->inicio.y;
			}
			int area() const{
				return base()*altura();
			}
			Punto centro()const{
				return Punto((this->inicio.x+this->fin.x)/2,(this->inicio.y+this->fin.y)/2);
			}
			Rectangulo interseccion(const Rectangulo& o)const{
				Punto a(std::max(this->inicio.x, o.inicio.x), std::max(this->inicio.y, o.inicio.y));
				Punto b(std::min(this->fin.x, o.fin.x), std::min(this->fin.y, o.fin.y));
				if(a.x > b.x or a.y > b.y)
					return Rectangulo();
				else 
					return Rectangulo(a, b);
			}
			bool colision(const Rectangulo& o)const{
				return std::min(this->fin.x, o.fin.x)-std::max(this->inicio.x, o.inicio.x) >= 0 and 
					   std::min(this->fin.y, o.fin.y)-std::max(this->inicio.y, o.inicio.y) >= 0;
			}


			Rectangulo operator+=(const Punto& p){
				this->inicio+=p;
				this->fin+=p;
				return *this;
			}
			Rectangulo operator-=(const Punto& p){
				this->inicio-=p;
				this->fin-=p;
				return *this;
			}

			inline Linea lado1()const{
				return Linea(this->inicio, Punto(this->fin.x, this->inicio.y));
			}
			inline Linea lado2()const{
				return Linea(Punto(this->fin.x, this->inicio.y), this->fin);
			}
			inline Linea lado3()const{
				return Linea(Punto(this->inicio.x, this->fin.y), this->fin);
			}
			inline Linea lado4()const{
				return Linea(this->inicio, Punto(this->inicio.x, this->fin.y));
			}

	};

	
	class RectanguloGirado{
	public:
		Punto p1, p2, p3, p4;
		RectanguloGirado():p1(), p2(), p3(), p4(){

		}
		RectanguloGirado(const Rectangulo& r){
			p1 = r.inicio; 
			p2 = Punto(r.fin.x, r.inicio.y); 
			p3 = Punto(r.inicio.x, r.fin.y); 
			p4 = r.fin; 
		}		

		Punto centro(){
			return (p1+p2+p3+p4)*int(0.25);
		}

		RectanguloGirado rotar(int ang, const Punto& p){
			RectanguloGirado res;
			res.p1 = p1.rotar(ang, p);
			res.p2 = p2.rotar(ang, p);
			res.p3 = p3.rotar(ang, p);
			res.p4 = p4.rotar(ang, p);
			return res;
		}

		int base(){
			return distancia(p1, p2);
		}

		int altura(){
			return distancia(p1, p3);
		}

		int area(){
			return base()*altura();
		}

		int angulo(){
			return (p4-p3).angulo();
		}
	};

}
#endif