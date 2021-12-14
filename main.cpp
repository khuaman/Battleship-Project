#include "jugador.h"
#include <string>

int main() {

	srand(time(NULL));

	Jugador* Angel = new Jugador("FirstPlayer", "Team Angel");
	Angel->empezar(); Angel->registrar();

	Jugador* Kevin = new Jugador("SecondPlayer", "Team Kevin");
	Kevin->empezar(); Kevin->registrar();

	while (true) {
		if (Angel->turno()) {
			if (Angel->jugar() == false) break;
		}
		else if (Kevin->turno()) {
			if (Kevin->jugar() == false) break;
		}
		else break;
		Angel->mostrarEnemigo();
		Kevin->mostrarEnemigo();
		cout << "--" << endl;
	}

	delete Angel;
	delete Kevin;

	return 0;
}
