#include "jugador.h"
#include<string>

int main(){

	srand(time(NULL));

	Jugador *Angel = new Jugador("FirstPlayer", "Team Angel");
	Jugador *Kevin = new Jugador("SecondPlayer", "Team Kevin");

	Jugador *Juega, *Espera;

	string jugada;
	int x, y;
	int t = 1;

	Juega = Angel;
	Espera = Kevin;

	while( !(Kevin -> derrotado()) && !(Angel -> derrotado()) ){
		cout << endl;
		cout << "Turno: " << (++t)/2 << " de " << Juega -> getTeam() << endl;
		jugada = Juega -> jugada();
		char respuesta = Espera -> responder( Espera -> deparse(jugada) );
		cout << Juega -> getTeam() << " ataca a " << Espera -> getTeam() << " con " << jugada << endl;
		Juega -> setRespuesta( Juega -> deparse(jugada) , respuesta );
		cout << "Respuesta: " << respuesta << endl;
		Juega -> mostrarEnemigo();
		swap(Juega, Espera);
	}

	cout << endl;
	if( Kevin -> derrotado() ){
		cout << "Angel derrotó a Kevin" << endl;
	} else
		cout << "Kevin derrotó a Angel" << endl;

	delete Angel;
	delete Kevin;

	return 0;
}
