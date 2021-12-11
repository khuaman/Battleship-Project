#include "nave.h"
#include "mapa.h"

int main(){


	Mapa *mapa = new Mapa(10, 10);

	mapa -> generar();

	mapa -> ataque( { 5, 5} );

	mapa -> mostrar();

	delete mapa;

	return 0;
}
