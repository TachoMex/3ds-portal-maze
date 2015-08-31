#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H 


class Temporizador{
private:
	u64 marca;

public:
	Temporizador(){
		marca = svcGetSystemTick();
	}

	void reiniciar(){
		marca = svcGetSystemTick();
	}

	u64 msegundos(){
		return (svcGetSystemTick()-marca)/100000;
	}

	u64 segundos(){
		return (svcGetSystemTick()-marca)/100000000;
	}

};
#endif