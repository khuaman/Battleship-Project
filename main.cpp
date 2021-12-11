#include "jugador.h"
#include<string>

int main(){

	Jugador *luchito = new Jugador();
	Jugador *PC = new Jugador();

	string coor;
	int x, y;
	luchito -> mostrarEnemigo();
	cin >> coor;

	while(coor != "-1"){

		x = stoi( coor.substr(1, (int)coor.size() - 1) ) - 1;
		y = toupper(coor[ 0 ]) - 'A';
		cout << x << " " << y << endl;

		char respuesta = PC -> responder( {x , y} );
		luchito -> setRespuesta( {x, y}, respuesta );
		cout << "Respuesta: " << respuesta << endl;
		luchito -> mostrarEnemigo();
		cin >> coor;
	}

	PC -> mostrar();

	delete luchito;
	delete PC;

	return 0;
}
