#include "mapa.h"

using namespace std;

class Jugador{
private:

	int rows;
	int cols;
	Mapa *mapa;
	char **enemigo;

public:

	Jugador(){
		rows = cols = 10;
		mapa = new Mapa(rows, cols);
		mapa -> generar();
		enemigo = new char*[ rows ];
		for( int i = 0; i < rows ; i++ ){
			enemigo[ i ] = new char[ cols ];
			for( int j = 0 ; j < cols ; j++ )
				enemigo[ i ][ j ] = ' ';
		}
	}

	string jugada();

	void setRespuesta(point coords, char respuesta){
		enemigo[ coords.F ][ coords.C ] = respuesta;
	}

	void mostrarEnemigo(){

		string espacio = "  ";

		cout << espacio << "  ";
		for( int j = 0; j < cols ; j++ )
			cout << char('A' + j) << espacio;
		cout << endl;

		for( int i = 0; i < rows ; i++ ){
			cout << i + 1 << ( i + 1 < 10 ? espacio + " " : espacio );
			for( int j = 0; j < cols ; j++ )
				cout << enemigo[ i ][ j ] << espacio;
			cout << endl;
		}

	}

	char responder( point coords ){
		return mapa -> ataque( coords );
	}

	void mostrar(){
		mapa -> mostrar();
	}


	~Jugador(){
		delete mapa;
		for( int i = 0; i < rows ; i++ )
			delete enemigo[ i ];
		delete enemigo;
		rows = cols = 0;
	}

};
