#include "jugador.h"
#include<string>

int main(){

	Jugador *luchito = new Jugador();
	Jugador *PC = new Jugador();

	string jugada;
	int x, y;
	luchito -> mostrarEnemigo();

	jugada = luchito -> jugada();

	int t = 1;
	while(jugada != "-1"){
		cout << "Turno: " << t++ << endl;
		x = stoi( jugada.substr(1, (int)jugada.size() - 1) ) - 1;
		y = toupper(jugada[ 0 ]) - 'A';
		cout << jugada << endl;
		char respuesta = PC -> responder( {x , y} );
		luchito -> setRespuesta( {x, y}, respuesta );
		cout << "Respuesta: " << respuesta << endl;
		luchito -> mostrarEnemigo();
		jugada = luchito -> jugada();
	}

	PC -> mostrar();

	delete luchito;
	delete PC;

	return 0;
}
