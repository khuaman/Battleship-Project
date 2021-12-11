#include "jugador.h"
#include <cstdlib>
#include <ctime>
#include <tuple>

#define rep(i, n) for(int i=0;i<n;i++)

string Jugador::parse(point punto){
	string respuesta = "";
	respuesta += (char)('A' + punto.C);
	if( punto.F < 9 )
		respuesta += (char)('1' + punto.F);
	else
		respuesta += "10";
	return respuesta;
}

point Jugador::dfs(point coord){

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

string Jugador::jugada(){

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
	vector< point > vacios;
	rep(i, rows)
		rep(j, cols)
		if( enemigo[ i ][ j ] == ' ' )
			vacios.push_back( {i, j} );

	cout << vacios.size() << endl;

	if( vacios.size() == 0 )
		return "-1";

	punto = vacios[ rand()%(vacios.size()) ];

	return parse(punto);
}
