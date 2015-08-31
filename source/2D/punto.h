#ifndef PUNTO2D_H
#define PUNTO2D_H

#include <cstdlib>
#include <algorithm>



namespace _2D{
	class Punto{
		public:
			int x,y;
			Punto(int,int);
			Punto();
			Punto operator+(const Punto& b) const{
				return Punto(x+b.x, y+b.y);
			}
			Punto operator+=(const Punto& b){
				x+=b.x;
				y+=b.y;
				return *this;
			}
			Punto operator-(const Punto& b)const {
				return Punto(x-b.x, y-b.y);
			}
			Punto operator-=(const Punto& b){
				*this=*this-b;
				return *this;
			}
			Punto operator*(int r)const {
				return Punto(x*r, y*r);
			}
			Punto operator/(int r)const{
				return Punto(x/r, y/r);
			}

			static Punto polar(double r , double ang){
				return Punto(r*cos(ang), r*sin(ang));
			}
			
			int angulo() const{
				return 0;//(int)fmod(atan2(y, x)+2*M_PI,2*M_PI);
			}
			int norma() const;
			int norma2() const{
				return x*x+y*y;
			}

			Punto rotar(int ang){
				return Punto::polar(norma(), angulo()+ang);
			}

			Punto rotar(int ang,const Punto& p){
				return (operator-(p).rotar(ang))+p;
			}
	

	};

	
	Punto::Punto(int x ,int y){
		this->x=x;
		this->y=y;
	}

	
	Punto::Punto():x(), y(){
	}


	
	int distancia(const Punto& a,const Punto& b){
		int dx= std::abs(a.x-b.x);
		int dy= std::abs(a.y-b.y);
		return sqrt( dx*dx + dy*dy);
	}


	
	int distanciaM(const Punto& a,const Punto& b){
		int dx= std::abs(a.x-b.x);
		int dy= std::abs(a.y-b.y);
		return dx+dy;
	}

	
	int distancia2(const Punto& a,const Punto& b){
		int dx= std::abs(a.x-b.x);
		int dy= std::abs(a.y-b.y);
		return  dx*dx + dy*dy;
	}

	
	int Punto::norma()const{
		return sqrt(x*x+y*y);
	}

	
	int productoPunto(const Punto& a,const Punto& b){
		return a.x*b.x+a.y*b.y;
	}

	
	int productoCruz(const Punto& a,const Punto& b){
		return a.x*b.y-a.y*b.x;
	}
	
	int ccw(const Punto & a, const Punto& b, const Punto& c){
		return productoCruz(b-a,c-a);
	}	

	
	int dentroDeintriangulo(const Punto& p, const Punto & a, const Punto& b, const Punto& c){
		int t[3];
		t[0]=ccw(a,b,p);
		t[1]=ccw(b,c,p);
		t[2]=ccw(c,a,p);
		if(t[0]<0 and t[1]<0 and t[2]<0){
			return true;
		}else if(t[0]>0 and t[1]>0 and t[2]>0){
			return true;
		}else{
			return false;
		}

	}

	
	bool operator==(const Punto& p,const Punto& q){
		return p.x==q.x and p.y==q.y;
	}

	
	bool colineares(const Punto&a, const Punto&b, const Punto&c){
		return (b.y-a.y)/(b.x-a.x)==(c.y-b.y)/(c.x-b.x);
	}


}


#endif