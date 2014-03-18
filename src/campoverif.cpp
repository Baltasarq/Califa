/************************************************************************
  			campoverif.cpp - baltasarq@yahoo.es

	Implementación de campos de verificación.

This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#include "campoverif.h"
#include "stringman.h"
#include "ui.h"

// ---------------------------------------------------- CampoVerif::CampoVerif()
const std::string CampoVerif::Si = "Sí";
const std::string CampoVerif::No = "No";
const std::string CampoVerif::Sies = " 1 S T SI Sí SÍ TRUE VERDADERO V ";
const std::string CampoVerif::Noes = " 0 N F NO FALSE FALSO ";

// --------------------------------------------------- CampoVerif::getDescTipo()
const std::string CampoVerif::StrDescTipo = "CampoVerif";
const std::string &CampoVerif::getDescTipo() const
{
	return StrDescTipo;
}

// ---------------------------------------------------- CampoVerif::CampoVerif()
CampoVerif::CampoVerif(DocumentoCalifa *doc) : Campo ( doc )
{
}

// ------------------------------------------------- CampoVerif::esFmtCorrecto()
bool CampoVerif::esFmtCorrecto(const std::string &x)
{
	if ( Sies.find( StringMan::mays( x ) ) != std::string::npos
	  || Noes.find( StringMan::mays( x ) ) != std::string::npos )
	{
		return true;
	}
	
	return false;
}

// -------------------------------------------------- CampoVerif::CreaErrorFmt()
FmtError CampoVerif::creaErrorFmt(const std::string &valor)
{
	return FmtError(
			"Encontrado '" + valor + "' en lugar de '" 
		    + Si + '\'' + '/' + No + '\''
	);
}

// ------------------------------------------------------ CampoVerif::getValor()
bool CampoVerif::getValorBooleano(unsigned int pos) const
{
	std::string valor = getValor( pos );
	bool toret = false;
	
	// ¿Está todo bien?
	if ( !esFilaCorrecta( pos ) ) {
		throw creaErrorIndiceIncorrecto( pos,
				getNumFilas(),
				"tomando valor booleano"
		);
	}
	
	if ( !esFmtCorrecto( valor ) ) {
		throw creaErrorFmt( valor );
	}
	
	// Comprobar el valor
	if ( Sies.find( StringMan::maysCnvt( valor ) ) != std::string::npos ) {
		toret = true;
	}
		
	return toret;
}

// -------------------------------------------------------- CampoVerif::copiar()
CampoVerif * CampoVerif::copiar() const
{
	CampoVerif * toret = new CampoVerif( *this );
	toret->eliminarTodosObservadores();
	
	return toret;
}

// ----------------------------------------------- CampoVerif::getEstadisticas()
std::string CampoVerif::getEstadisticas() const
{
	int numSi = 0;
	int numNo = 0;
	unsigned int numCalifas = getNumFilas();
	std::string toret;
		
	if ( numCalifas > 0 ) {
		for(unsigned int i = 0; i < numCalifas; ++i) {
			
			if ( getValorBooleano( i ) )
					++numSi;
			else	++numNo;
			
			ponProgreso( "Calculando estadísticas ...", 0, i, numCalifas );			
		}

		// Visualizar número de califas
		toret +=
			"Número de calificaciones: "
		  + StringMan::toString( numCalifas )
		;
		
		// Guardar número de aptos
		toret +=
			"\nNúmero de aptos: "
		  + StringMan::toString( numSi )
		  + " ("
		  + StringMan::toString( ( (double) numSi / numCalifas ) * 100, 5, 2 )
		  + "%)"		
		;		
		
		// Guardar número de no aptos
		toret +=
			"\nNúmero de no aptos: "
		  + StringMan::toString( numNo )
		  + " ("
		  + StringMan::toString( ( (double) numNo / numCalifas ) * 100, 5, 2 )
		  + "%)"		
		;				
	}
	else toret = "\nNo existen calificaciones en " + nombre;
	
	return toret;
}
