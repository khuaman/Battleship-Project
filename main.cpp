#include "jugador.h"
#include <string>

int main(){

	srand(time(NULL));

	Jugador *Angel = new Jugador("FirstPlayer", "Angel");
	Jugador *PC = new Jugador("SecondPlayer", "PC");

	string ataque;
	int t = 1;

	PC -> mostrar();

	while( !(PC -> derrotado()) ){
		cout << endl;
		cout << "Turno: " << t++ << " de " << Angel -> getTeam() << endl;
		ataque = Angel -> jugada();
		cout << ataque << endl;
		char respuesta = PC -> responder( PC -> deparse(ataque) );
		cout << Angel -> getTeam() << " ataca a " << PC -> getTeam() << " con " << ataque << endl;
		Angel -> setRespuesta( Angel -> deparse(ataque) , respuesta );
		cout << "Respuesta: " << respuesta << endl;
		Angel -> mostrarEnemigo();
	}

	PC -> mostrar();

	delete Angel;
	delete PC;

	return 0;
}
