#include "jugador.h"
#include <string>

int main() {

	srand(time(NULL));

	Jugador* Angel = new Jugador("C:\\Users\\Usuario\\CODIGO\\SecondPlayer", "Team Angel");
	Angel->empezar(); Angel->registrar();

	 while (true) {
        if (Angel->turno()) {
            if (Angel->jugar() == false) break;
        }
        cout << "--" << endl;
    }

	delete Angel;

	return 0;
}
