#ifndef GESTOR_H
#define GESTOR_H 

#include "imagen.h"
#include <map>
#include <fstream>

class sstring{
public:
	const char* ptr;
	sstring(const char* x){
		ptr = x;
	}
	bool operator<(const sstring& o)const{
		return strcmp(ptr,o.ptr)<0;
	}
};



class GestorImagenes{
	std::map<sstring, Imagen*> imagens;
public:
	Imagen* abrir(const sstring &s);
	Imagen* operator[](const sstring &s){
		return abrir(s);
	}
};

Imagen* GestorImagenes::abrir(const sstring &s){
	if(imagens.count(s))
		return imagens[s];
	std::ifstream f(s.ptr);
	if(f.good()){
		f.close();
		Imagen * i = new Imagen();
		i->leeBMP(s.ptr);
		return imagens[s]=i;
	}
	return nullptr;
}

#endif