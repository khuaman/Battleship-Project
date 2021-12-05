#include "nave.h"

int main(){

	Nave *luchita = new Nave( 'A' , 'V' , {0, 0} );

	// AAAA

	luchita -> mostrar();
	if( luchita -> ataque({ 1 , 0 }) )
		cout << "Ataque realizado" << endl;
	else
		cout << "Ataque fallido" << endl;
	luchita -> mostrar();

	delete luchita;

	return 0;
}
