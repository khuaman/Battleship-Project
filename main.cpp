#include "nave.h"
#include "mapa.h"

int main(){


	Mapa *mapa = new Mapa(10, 10);

	mapa -> generar(10);
	mapa -> mostrar();

	delete mapa;

	return 0;
}
