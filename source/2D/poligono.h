#ifndef POLIGONO_H
#define POLIGONO_H 
#include "punto.h"
#include "linea.h"
#include "rectangulo.h"
#include <vector>



namespace _2D{

class Poligono{
public:
	std::vector<Punto> vertices;
	Poligono(){
	}
	void agregaPunto(const Punto& p){
		vertices.push_back(p);
	}
	Punto centro() const {
		Punto c;
		for(auto p: vertices){
			c+=p;
		}
		c.x/=vertices.size();
		c.y/=vertices.size();
		return c;
	}
	int tam() const{
		return vertices.size();
	}
	const Punto operator[](int i)const {
		return vertices[i];
	}

	bool colisiona(const Linea& l)const{
		for(unsigned i=1;i<vertices.size();i++){
			if(l.colisiona(Linea(vertices[i], vertices[i-1]))){
				return true;
			}
		}
		return l.colisiona(Linea(vertices[0],vertices[tam()-1]));
	}

	Rectangulo rectanguloRecubridor()const{
		Rectangulo resultado(vertices[0],vertices[0]);
		for(auto p: vertices){
			resultado.inicio.x = std::min(resultado.inicio.x,p.x);
			resultado.inicio.y = std::min(resultado.inicio.y,p.y);
			resultado.fin.x = std::max(resultado.fin.x,p.x);
			resultado.fin.y = std::max(resultado.fin.y,p.y);
		}
		return resultado;
	}

	Poligono rotar(int angulo)const{
		Punto c = centro();
		Poligono resultado;
		for(auto p: vertices){
			resultado.agregaPunto(c+(p-c).rotar(angulo));
		}
		return resultado;
	}

/*	RectanguloGirado rectanguloRecubridorMinimo(int iteraciones=36)const{
		double da = 2.0*M_PI/iteraciones; //diferencia de angulo
		RectanguloGirado resultado = this->rectanguloRecubridor();
		for(int i=1;i<iteraciones;i++){
			int angulo = (int)i*da;
			Poligono p=this->rotar(angulo);
			RectanguloGirado calculado = p.rectanguloRecubridor();
			calculado=calculado.rotar(-angulo, p.centro());
			if(calculado.area()<resultado.area()){
				resultado=calculado;
			}
		}
		return resultado;
	}*/

	bool contiene(const Punto& p){
		for(int i=1;i<tam();i++){
			if(ccw(p,vertices[i-1], vertices[i])<0){
				return false;
			}
		}
		return true;
	}
};

}
#endif
