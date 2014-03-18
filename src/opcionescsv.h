/************************************************************************
  			opcionescsv.h - Copyright baltasarq@yahoo.es

	Lleva las opciones para escribir el csv

This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#ifndef OPCIONESCSV_H
#define OPCIONESCSV_H

#include <cstring>

/**
 * Class OpcionesCsv
 * Esta clase lleva las opciones para escribir y leer documentos CSV
 */
class OpcionesCsv {
public:
	 bool esDNISinLetra;
	 bool excluirNoPresentados;
     char chSeparador;
     char chCambioLinea[3];
     char chDecimal;

	 OpcionesCsv():
            esDNISinLetra( false ), excluirNoPresentados( true ),
            chSeparador( ',' ), chDecimal( '.' )
	 	{ std::memset( &chCambioLinea, 0, 3 ); chCambioLinea[0] = '\n'; }

	 /**
      * Construye directamente todas las opciones
      * @param sep El separador de campos
      * @param dec El separador de decimales
      * @param finLn El cambio de línea (separador de filas)
     */
     OpcionesCsv(char sep, bool np, char dec, char finLn, bool crw = false)
	 	: esDNISinLetra( crw ), excluirNoPresentados( np ),
          chSeparador( sep ), chDecimal( dec )
	 {
		 memset( &chCambioLinea, 0, 3 );
		 chCambioLinea[0] = finLn;
	 }

	 /// Pone un tipo de cambio de línea compatible con DOS/Windows
	 void ponCambioLinDOS()
	 	{
			chCambioLinea[0] = '\n'; chCambioLinea[1] = '\r';
			chCambioLinea[2] = '\0';
		}
};
#endif //OPCIONESCSV_H
