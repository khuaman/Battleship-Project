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

  Nave ***mapa;
  vector< Nave* >* naves;
  int rows;
  int cols;

public:

  Mapa(int _cols, int _rows){

	naves = new vector<Nave *>();
	cols = _cols;
	rows = _rows;

	mapa = new Nave**[ rows ];

	for( int i = 0; i < rows ; i++ ){
	  mapa[ i ] = new Nave*[ cols ];
	  for( int j = 0; j < cols ; j++ )
		mapa[ i ][ j ] == nullptr;
	}

  };

  void mostrar(){

	cout << "   ";
	for( int j = 0; j < cols ; j++ )
	  cout << char('A' + j) << " ";
	cout << endl;

	for( int i = 0; i < rows ; i++ ){
	  cout << i + 1 << ( i < 11 ? "  ":"   " );
	  for( int j = 0; j < cols ; j++ ){
		if( mapa[ i ][ j ] )
		  cout << (mapa[ i ][ j ] -> signo({i, j})) << " ";
		else
		  cout << "  ";
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

  Nave* getNave(point coords){
	return mapa[coords.F][coords.C];
  }

  bool ataque(point Acoords){
	if( getNave(Acoords) )
	  return getNave(Acoords) -> ataque(Acoords);
	else
	  return false;
  }

  void generar(int naves){
	srand(time(NULL));
	for( int i = 0; i < naves; i++ ){
	  Nave *nave = nullptr;
	  do{
		delete nave;
		nave = nullptr;
		nave = new Nave( "ABST"[rand()%4], "VH"[rand()%2], { rand()%rows , rand()%cols } );
	  } while(!validar_nave(nave));
	  registrar_nave( nave );
	}
  }

  ~Mapa(){
	for( int i = 0 ; i < rows ; i++ )
	  delete mapa[ i ];

	for( auto s: (*naves) )
	  delete s;

	delete naves;
	delete mapa;
  }

};
