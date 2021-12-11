#ifndef NAVE_H
#define NAVE_H

#include <iostream>
#include <utility>
#include <bitset>

#define F first
#define C second
#define point pair<int,int>

using namespace std;

class Zona{
protected:
	bool agua = true;
	char codigo;
	point coords;
public:
	Zona(char _codigo, point _coords){
		codigo = _codigo;
		coords = _coords;
	}
	virtual char signo(point _coords){
		return codigo;
	}
	virtual bool ataque(point _coords){
		return false;
	};
	virtual ~Zona(){
		codigo = 0;
		coords = {0, 0};
	}
	friend class Mapa;
};

class Nave: public Zona{

private:

	string nombre;
	bitset< 4 > estado;
	char orientacion;
	int len;

public:

	Nave(char _codigo ,char _orientacion, point _coords):Zona(_codigo, _coords){
		agua = false;
		orientacion = _orientacion;
		switch( codigo ){
		case 'A':
			nombre = "Aircfratf Carrier";
			len = 4;
			break;
		case 'B':
			nombre = "Battlecrucier";
			len = 3;
			break;
		case 'S':
			nombre = "Submarine";
			len = 2;
			break;
		case 'T':
			nombre = "Torpedo boat";
			len = 1;
			break;
		}
		estado = (1 << len) - 1;
	}

	char signo(point _coord){
		if( destruido() ) return 'X';
		int i = max(_coord.C - coords.C,  _coord.F - coords.F);
		return estado[ i ] ? codigo : 'Y';
	}

	void mostrar(){
		cout << "Nave " << nombre << endl;
		cout << "Ubicada en :(" << coords.C << ", " << coords.F << ")" << endl;
		for( int i = 0; i < len ; i++ )
			cout << (estado[ i ] ? codigo : 'Y') << ( orientacion == 'H' ? "":"\n" );
		cout << endl;
	}

	bool ataque(point ataque){

		point Rcoord;
		Rcoord.C = ataque.C - coords.C;
		Rcoord.F = ataque.F - coords.F;

		if( Rcoord.C < 0 || Rcoord.F < 0 ) return false;

		if( orientacion == 'V' ){

		  if( Rcoord.C || Rcoord.F >= len )
			  return false;

		  estado[ Rcoord.F ] = 0;
		  return true;
		}

		if( orientacion == 'H' ){
			if( Rcoord.F || Rcoord.C >= len )
				return false;

			estado[ Rcoord.C ] = 0;
			return true;
		}

		return false;
	}

	bool destruido(){
		return !estado.count();
	}

	~Nave(){
		codigo  = orientacion = 0;
		estado.reset();
		coords = {0, 0};
		nombre = "";
	}

	friend class Mapa;
	friend class Jugador;
};

#endif //NAVE_H
