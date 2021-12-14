#ifndef MAPA_H
#define MAPA_H

#include "nave.h"
#include <cstdlib>
#include <ctime>
#include <vector>

#define F first
#define C second
#define point pair<int,int>

using namespace std;

class Mapa{

private:

	Zona ***mapa;
	vector< Nave* >* naves;
	vector< Zona* >* fallas;
	int rows;
	int cols;

public:

	Mapa(int _cols, int _rows){

		naves = new vector<Nave *>();
		fallas = new vector<Zona *>();
		cols = _cols;
		rows = _rows;

		mapa = new Zona**[ rows ];

		for( int i = 0; i < rows ; i++ )
			mapa[ i ] = new Zona*[ cols ];

		for( int i = 0; i < rows ; i++ )
			for( int j = 0; j < cols ; j++ )
				mapa[ i ][ j ] = nullptr;

	};

	void mostrar(){

		string espacio = "  ";

		cout << espacio << "  ";
		for( int j = 0; j < cols ; j++ )
			cout << char('A' + j) << espacio;
		cout << endl;

		for( int i = 0; i < rows ; i++ ){
			cout << i + 1 << ( i + 1 < 10 ? espacio + " " : espacio );
			for( int j = 0; j < cols ; j++ ){
				if( mapa[ i ][ j ] )
					cout << (mapa[ i ][ j ] -> signo({i, j})) << espacio;
				else
					cout << espacio + " ";
			}
			cout << endl;
		}
	}

	bool validar_nave(Nave *nave){
		point coords = nave -> coords;
		int len = nave -> len;
		if( nave -> orientacion == 'H' ){
			if( coords.C + len > cols ) return false;
			for( int i = 0 ; i < len ; i++ )
				if( mapa[ coords.F ][ coords.C + i ] )
					return false;
		}
		else{
			if( coords.F + len > rows ) return false;
			for( int i = 0 ; i < len ; i++ )
				if( mapa[ coords.F + i ][ coords.C ] )
					return false;
		}
		return true;
	}

	void registrar_nave(Nave *nave){

		if( !validar_nave(nave) ){
			cout << "No se pudo registrar la nave." << endl;
			delete nave;
			return;
		}

		naves -> push_back(nave);

		point coords = nave -> coords;
		int len = nave -> len;

		if( nave -> orientacion == 'H' )
			for( int i = 0 ; i < len ; i++ )
				mapa[ coords.F ][ coords.C + i ] = nave;

		else
			for( int i = 0 ; i < len ; i++ )
				mapa[ coords.F + i ][ coords.C ] = nave;
	}

	Zona* getZona(point coords){
		
		return mapa[coords.F][coords.C];
	}

	void setZona(point coords, Zona* zona){
		mapa[coords.F][coords.C] = zona;
	}

	char ataque(point Acoords){

		Zona *lugar = getZona(Acoords);	
		if( lugar != nullptr ){
			cout << lugar -> isAgua() << endl;
			if( lugar -> isAgua() )
				return '.';
			lugar -> ataque(Acoords);
			return lugar -> signo(Acoords);
		}

		Zona *tmp = new Zona('.', Acoords);
		setZona(Acoords, tmp);
		fallas -> push_back( tmp );
		
		return '.';
	}

	void generar(){

		for( int i = 0; i < 4; i++ ){
			for( int j = 0; j < i + 1 ; j++ ){
				Nave *nave = nullptr;
				do{
					delete nave;
					nave = nullptr;
					nave = new Nave( "ABST"[i], "VH"[rand()%2], { rand()%rows , rand()%cols } );
				} while(!validar_nave(nave));
				registrar_nave( nave );
			}
		}
	}

	~Mapa(){
		for( int i = 0 ; i < rows ; i++ )
			delete mapa[ i ];

		for( auto s: (*naves) )
			delete s;

		for( auto s: (*fallas) )
			delete s;

		delete naves;
		delete fallas;
		delete mapa;
	}

	friend class Jugador;
};

#endif //MAPA_H