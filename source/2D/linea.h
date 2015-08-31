#ifndef LINEA2D_H
#define LINEA2D_H

#include "punto.h"

namespace _2D{
	class Linea{
		public:
			Punto inicio;
			Punto fin;
			Linea();
			Linea(const Punto& a,const Punto& b);
			Linea(const Punto& ini, int r, int a);
			int angulo() const;
			Linea rotar(int ang)const ;		
			int longitud() const;
			int longitud2() const;
			Linea invierte()const;
			Linea operator*(int d) const;
			Linea operator*=(int d);
			Linea operator/(int d) const;
			Linea operator/=(int d);
			Linea operator+(const Punto& d) const;		
			bool colisiona(const Linea& b)const {
				return (ccw(inicio,fin,b.inicio) * ccw(inicio, fin, b.fin) <= 0) and (ccw(b.inicio, b.fin, inicio)*ccw(b.inicio, b.fin, fin)<=0);
			}
			Linea bisector(const int& x1, const int& x2)const{
				int dx = fin.x-inicio.x;
				int dy = fin.y-inicio.y;
				int m = -dx/dy;
				Punto centro;
				centro.x = (inicio.x+fin.x)/2;
				centro.y = (inicio.y+fin.y)/2;
				int b = centro.y - m * centro.x;
				auto f = [&](const int& p){
					return Punto(p,m*p+b);
				};
				return Linea(f(x1),f(x2));
			}
			Linea operator+=(const Punto& p){
				inicio+=p;
				fin+=p;
				return *this;
			}


	};

	/*
	Punto interseccion(const Linea& a,const Linea& b){
		int A1, B1, C1, dx1, dy1;
		dx1 = a.fin.x-a.inicio.x;
		dy1 = a.fin.y-a.inicio.y;
		A1 = dy1;
		B1 = -dx1;
		C1 = a.inicio.y*dx1-a.inicio.x*dy1;

		int A2, B2, C2, dx2, dy2;
		dx2 = b.fin.x-b.inicio.x;
		dy2 = b.fin.y-b.inicio.y;
		A2 = dy2;
		B2 = -dx2;
		C2 = b.inicio.y*dx2-b.inicio.x*dy2;

		//A1x + B1y = -C1x
		//A2x + B2y = -C2x
		int Dg = A1*B2-A2*B1;
		int Dx = -B1*C2+C1*B2;
		int Dy = -A1*C2+C1*A2;
		return Punto(-Dx/Dg,Dy/Dg);
	}*/
	
	Linea::Linea():inicio(),fin(){
	}

	Linea::Linea(const Punto& a,const Punto& b){
		inicio=a;
		fin=b;
	}
	
	Linea::Linea(const Punto& ini, int r, int a){
		inicio=ini;
		//fin=Punto(ini.x+r*cos(a), ini.y+r*sin(a));
	}

	int Linea::angulo()const {
		return (fin - inicio).angulo();
	}

	Linea Linea::rotar(int ang)const {
		return Linea(inicio, longitud(), angulo()+ang); 
	}


	int Linea::longitud()const{
		return (fin-inicio).norma();
	}
	int Linea::longitud2()const{
		return (fin-inicio).norma2();
	}

	Linea Linea::operator*(int d)const{
		return Linea(inicio, longitud()*d, angulo());
	}
	Linea Linea::operator*=(int d){
		*this=*this*d;
		return *this;
	}
	Linea Linea::invierte()const{
		return Linea(fin,inicio);
	}

	Linea Linea::operator/(int d) const{
		return Linea(inicio/d,fin/d);
	}

	Linea Linea::operator/=(int d){
		*this=*this/d;
		return *this;		
	}

	Linea Linea::operator+(const Punto& p) const{
		return Linea(inicio+p, fin+p);
	}

	int distancia(const Linea& l,const Punto& p){
		//int A, B, C, dx, dy, d;
	/*	dx = l.fin.x-l.inicio.x;
		dy = l.fin.y-l.inicio.y;
		A = dy;
		B = -dx;
		C = l.inicio.y*dx-l.inicio.x*dy;*/
		//d = abs(A*p.x+B*p.y+C)/sqrt(A*A+B*B);
		return 0;
	}
}
#endif
