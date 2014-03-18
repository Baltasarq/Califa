// nota.cpp
/*
    Conversiones de notas tipo, cadena a nums. y viceversa.
*/

#include "nota.h"
#include "campo.h"
#include "stringman.h"

// ======================================================================== Nota
double Nota::vNumNotasTipo[] = { -1, 0, 5, 7, 9, 10, 111 };

const std::string Nota::vStrNotasTipo[] = {
	"No presentado",
	"Suspenso",
	"Aprobado",
	"Notable",
	"Sobresaliente",
	"Matrícula de honor",
	"#ERROR"
};

// -------------------------------------------------------- Nota::cnvtNotaTipo()
Nota::NotaConceptual Nota::cnvtNotaTipo(double nota)
{
	unsigned int i = getOrdinal( NoPresentado );
	double limSup = cnvtTipoNota( MatriculaHonor );
	double limInf = cnvtTipoNota( NoPresentado );

	// Comprobar valores
	if ( nota < limInf
	  || nota > limSup )
	{
		throw InconsistenciaError( "Nota es: "
						+ StringMan::toString( nota )
						+ " debiera ser "
						+ StringMan::toString( limInf )
						+ " <= nota <= "
						+ StringMan::toString( limSup )
		);
	}

	// Buscar el valor correcto
	for(; i <= getOrdinal( Error ); ++i) {
		if ( nota < vNumNotasTipo[ i ] )  {
			--i;
			break;
		}
	}

	return getNotaConceptualDeEntero( i );
}

// --------------------------------------------------------- Nota::cnvtNotaStr()
const std::string &Nota::cnvtNotaStr(double nota)
{
	return vStrNotasTipo[ getOrdinal( cnvtNotaTipo( nota ) ) ];
}

// -------------------------------------------------------- Nota::cnvtTipoNota()
double Nota::cnvtTipoNota(Nota::NotaConceptual nota)
{
	return vNumNotasTipo[ getOrdinal( nota ) ];
}

const std::string &Nota::cnvtTipoNotaStr(Nota::NotaConceptual nota)
{
	return vStrNotasTipo[ getOrdinal( nota ) ];
}

// --------------------------------------------------------- Nota::cnvtStrNota()
Nota::NotaConceptual Nota::cnvtStrNotaConceptual(const std::string &nota)
{
	unsigned int i = getOrdinal( NoPresentado );
	std::string n = StringMan::trim( nota );
	StringMan::maysCnvt( n );

	for(; i < getOrdinal( Error ); ++i) {
		if ( StringMan::mays( vStrNotasTipo[ i + 1 ] ) == n ) {
			break;
		}
	}

	return getNotaConceptualDeEntero( i );
}


// --------------------------------------------------------- Nota::cnvtStrNota()
double Nota::cnvtStrNota(const std::string &nota)
{
	return cnvtTipoNota( cnvtStrNotaConceptual( nota ) );
}
