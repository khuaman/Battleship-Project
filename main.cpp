#include "nave.h"
#include "mapa.h"

int main(){


	Mapa *mapa = new Mapa(10, 10);

	Nave *naveA = new Nave('A', 'H', {0, 0});
	Nave *naveB = new Nave('B', 'V', {1, 0});

	mapa -> registrar_nave(naveA);
	mapa -> registrar_nave(naveB);

	mapa -> ataque({0, 0});

	mapa -> mostrar();

	delete mapa;
	delete naveA;
	delete naveB;

	return 0;
}
