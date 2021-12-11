#include "jugador.h"
#include <cstdlib>
#include <ctime>

#define rep(i, n) for(int i=0;i<n;i++)

string Jugador::jugada(){

	// Buscar Y
	vector< point > vacios;
	rep(i, rows)
		rep(j, cols)
		if( enemigo[ i ][ j ] == ' ' )
			vacios.push_back( {i, j} );

	cout << vacios.size() << endl;

	if( vacios.size() == 0 )
		return "-1";

	point punto = vacios[ rand()%(vacios.size()) ];

	string respuesta = "";
	respuesta += (char)('A' + punto.C);
	if( punto.F < 9 )
		respuesta += (char)('1' + punto.F);
	else
		respuesta += "10";

	return respuesta;
}
