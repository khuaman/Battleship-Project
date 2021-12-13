#include "mapa.h"

using namespace std;

class Jugador{
private:

	string filename;
	string teamname;
	string token;
	int rows;
	int cols;
	Mapa *mapa;
	char **enemigo;

public:

	Jugador(string _filename, string _teamname){
		filename = _filename;
		teamname = _teamname;
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

	string getTeam(){
		return teamname;
	}

	string jugada();
	string parse(point coord);
	point dfs(point coord);
	void empezar();
	bool jugar();

	bool derrotado(){
		for(auto nave: *(mapa -> naves))
			if( !(nave -> destruido()))
				return false;
		return true;
	}

	point deparse(string jugada){
		int x = stoi( jugada.substr(1, (int)jugada.size() - 1) ) - 1;
		int y = toupper(jugada[ 0 ]) - 'A';
		return {x, y};
	}

	char getVal(point coords){
		return enemigo[ coords.F ][ coords.C ];
	}

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
