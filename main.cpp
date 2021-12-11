#include "nave.h"
#include "mapa.h"

int main(){


	Mapa *mapa = new Mapa(10, 10);

	mapa -> registrar_nave( new Nave('B', 'V', {0, 0}) );
	mapa -> generar(10);

	mapa -> ataque( { 0 , 0 } );
	mapa -> ataque( { 1 , 0 } );
	mapa -> ataque( { 2 , 0 } );

	mapa -> ataque( { 5, 5} );

	mapa -> mostrar();

	delete mapa;

	return 0;
}
