#include "jugador.h"
#include<string>

int main(){

	Jugador *luchito = new Jugador();
	Jugador *PC = new Jugador();

	string jugada;
	int x, y;


	int t = 1;
	while(!(PC -> derrotado()) ){
		cout << "Turno: " << t++ << endl;
		luchito -> mostrarEnemigo();
		jugada = luchito -> jugada();
		x = stoi( jugada.substr(1, (int)jugada.size() - 1) ) - 1;
		y = toupper(jugada[ 0 ]) - 'A';
		cout << jugada << endl;
		char respuesta = PC -> responder( {x , y} );
		luchito -> setRespuesta( {x, y}, respuesta );
		cout << "Respuesta: " << respuesta << endl;
	}

	PC -> mostrar();

	delete luchito;
	delete PC;

	return 0;
}
