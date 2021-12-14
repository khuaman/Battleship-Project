#ifndef JUGADOR_H
#define JUGADOR_H

#include "mapa.h"
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

#define F first
#define C second
#define point pair<int,int>
#define rep(i, n) for(int i=0;i<n;i++)

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

	string jugada(){

		point punto;

		rep(i, rows)
			rep(j, cols)
			if( getVal({i, j}) == 'Y' ){
				punto = dfs({i, j});
				if( punto.F != -1)
					return parse(punto);
				//else
				//	setRespuesta({i, j}, 'M');
			}


		// Dar vacio random
		vector< point > vacios[ 2 ];
		rep(i, rows)
			rep(j, cols)
			if( enemigo[ i ][ j ] == ' ' )
				vacios[ (i + j) % 2 ].push_back( {i, j} );

		if( vacios[ 0 ].size() + vacios[ 1 ].size() == 0 )
			return "-1";

		if( vacios[ 0 ].size() )
			punto = vacios[ 0 ][ rand()%(vacios[ 0 ].size()) ];
		else
			punto = vacios[ 1 ][ rand()%(vacios[ 1 ].size()) ];

		return parse(punto);
	}

	string parse(point punto){
		string respuesta = "";
		respuesta += (char)('A' + punto.C);
		if( punto.F < 9 )
			respuesta += (char)('1' + punto.F);
		else
			respuesta += "10";
		return respuesta;
	}

	point dfs(point coord){

		int F, C;
		tie( F, C ) = coord;

		point N = {F - 1 , C};
		point S = {F + 1 , C};
		point E = {F , C + 1};
		point O = {F , C - 1};

		if( N.F >= 0 && S.F < rows ){
			if( getVal( N ) == 'Y' and getVal( S ) == ' ' )
				return S;
			if( getVal( S ) == 'Y' and getVal( N ) == ' ' )
				return N;
		}

		if( O.C >= 0 && E.C < cols ){
			if( getVal( O ) == 'Y' and getVal( E ) == ' ' )
				return E;
			if( getVal( E ) == 'Y' and getVal( O ) == ' ' )
				return O;
		}

		if( N.F >= 0 && getVal(N) == ' ' )
			return N;

		if( S.F < rows && getVal(S) == ' ' )
			return S;

		if( O.C >= 0 && getVal(O) == ' ' )
			return O;

		if( E.C < cols && getVal(E) == ' ' )
			return E;

		return {-1, -1};
	}

	void empezar(){
		ofstream fileW(filename + ".in");
		if (fileW.is_open())
			fileW << "Handshake=" + teamname << endl;
		fileW.close();
		Sleep(1);
		ifstream fileR(filename + ".out");
		string line;
		getline(fileR, line);
		if( line != "ACCEPTED" ){
			cout << "El programa no otorgó el Token" << endl;
			return;
		}
		getline(fileR, line);
		token = line.substr(6);
		cout << token << endl;
	}

	bool jugar(){
		ifstream fileR;
		string line;
		while(true){
			Sleep(1);
			fileR.open(filename + ".not");
			getline(fileR, line);
			getline(fileR, line);
			if( line != "NOT YOUR TURN" )
				break;
			fileR.close();
		}
		fileR.close();
		if( line == "END" )
			return false;
		cout << "" << endl;
		return true;
	}

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

#endif //JUGADOR_H