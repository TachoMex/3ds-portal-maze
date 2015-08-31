#ifndef TRIANGULO2D_H
#define TRIANGULO2D_H

#include "punto.h"

namespace _2D{

	class Triangulo{
		public:
			Punto p1,p2,p3;
		Triangulo():p1(),p2(),p3(){

		}
		Triangulo(const Punto& a,const Punto& b,const Punto& c){
			p1 = a;
			p2 = b;
			p3 = c;
		}
		Triangulo operator+(const Punto& a)const{
			return Triangulo(p1+a,p2+a,p3+a);
		}
		Triangulo operator+=(const Punto& a){
			p1 += a;
			p2 += a;
			p3 += a;
			return *this;
		}
		Triangulo operator-(const Punto&a)const{
			return Triangulo(p1-a,p2-a,p3-a);
		}
		Triangulo operator-=(const Punto& a){
			p1 -= a;
			p2 -= a;
			p3 -= a;
			return *this;
		}
		int perimetro()const {
			return distancia(p1,p2)+distancia(p2,p3)+distancia(p3,p1);
		}
		int area()const {
			int a = distancia(p1,p2);
			int b = distancia(p2,p3);
			int c = distancia(p3,p1);
			int s = (a+b+c)/2;
			return sqrt(s*(s-a)*(s-b)*(s-c));	
		}


		Punto centroDeGravedad()const{
			return (p1+p2+p3)/3;
		}		
	};

	bool operator==(const Triangulo&a, const Triangulo&b){
		return a.p1==b.p1 and a.p2==b.p2 and a.p3==b.p3; 
	}

	bool comparteLado(const Triangulo&a, const Triangulo&b){
		int iguales = 0;

		iguales += a.p1 == b.p1;
		iguales += a.p1 == b.p2;
		iguales += a.p1 == b.p3;

		iguales += a.p2 == b.p1;
		iguales += a.p2 == b.p2;
		iguales += a.p2 == b.p3;

		iguales += a.p3 == b.p1;
		iguales += a.p3 == b.p2;
		iguales += a.p3 == b.p3;

		return iguales >= 2;
	}


}





#endif