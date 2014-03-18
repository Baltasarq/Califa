// campodni.cpp
/*
	Implementación del campo DNI, que incluye comprobación especial
	y capacidad de búsqueda también especial.
*/

#include "campodni.h"
#include "stringman.h"
#include <cctype>

const std::string CampoDni::ContenidoPorDefecto = "00000000X";
std::string CampoDni::msgErrorValidacion;

// -------------------------------------------------------- CampoDni::CampoDni()
CampoDni::CampoDni(DocumentoCalifa *doc) : Campo( doc )
{
}

// ----------------------------------------------------- CampoDni::getDescTipo()
const std::string CampoDni::StrDescTipo = "CampoDni";
const std::string &CampoDni::getDescTipo() const
{
	return StrDescTipo;
}

// ---------------------------------------------------------- CampoDni::cumple()
bool CampoDni::cumple(unsigned int i) const
{
	return esFmtCorrecto( getValor( i ) );
}

// -------------------------------------------------------- CampoDni::putValor()
void CampoDni::putValor(unsigned int pos, const std::string &strDni)
{
	std::string dni = StringMan::trim( strDni );
	StringMan::maysCnvt( dni );

	if ( esFmtCorrecto( dni ) ) {
        // Comprobar la letra del NIF
        const char LetraNif = getLetra( dni );
        const char LetraNifCalculada = calcularLetraNif( dni );

        if ( LetraNif != LetraNifProhibida ) {
          if ( LetraNif != LetraNifCalculada )
          {
            // Borrar la letra si existe y es incorrecta
            if ( LetraNif != 0 ) {
                dni.erase( dni.length() - 1 );
            }

            // Añadir la letra
            dni += LetraNifCalculada;
          }
        } else {
             // Borrar la marca de no modificar
            if ( LetraNif != 0 ) {
                dni.erase( dni.length() - 1 );
            }
        }

	    // Poner
		Campo::putValor( pos, dni );
	}
	else throw creaErrorFmt( strDni );
}

// ---------------------------------------------------- CampoDni::creaErrorFmt()
FmtError CampoDni::creaErrorFmt(const std::string &strNoDni)
{
	return FmtError( "El DNI/Nif debe ser un número entero terminado en letra"
	                 ", no '"
				+ strNoDni
				+ '\''
	);
}

// --------------------------------------------------- CampoDni::esFmtCorrecto()
bool CampoDni::esFmtCorrecto(const std::string &strDni)
{
	bool toret = true;
	unsigned int i = 0;

	// Es obligatorio que haya algo
	if ( strDni.empty() ) {
		toret = false;
		goto FIN;
	}

	// Lo primero puede ser un número o una letra, si es DNI extranjero
	if ( !std::isdigit( strDni[ i ] )
	  && !std::isalpha( strDni[ i ] ) )
	{
		toret = false;
	}

	// Comprobar que sólo hay números
	for(++i; i < strDni.size() - 1; ++i) {
		if ( !std::isdigit( strDni[ i ] ) ) {
			toret = false;
			goto FIN;
		}
	}

	// Lo último puede ser un número o una letra (si es un Nif)
    i = strDni.size() - 1;
	if ( !std::isdigit( strDni[ i ] )
	  && !std::isalpha( strDni[ i ] ) )
	{
		toret = false;
	}

	FIN:
	return toret;
}

char CampoDni::getLetra(const std::string &d)
{
    char toret = 0;
    const unsigned int UltimoCaracter = d.length() - 1;

    if ( UltimoCaracter < d.length() ) {
        toret = d[ UltimoCaracter ];

        if ( !std::isalpha( toret ) ) {
            toret = 0;
        }
    }

    return toret;
}

char CampoDni::calcularLetraNif(std::string nif)
{
    const char LetraNIF = getLetra( StringMan::trimCnvt( nif ) );
    static char LetrasNIF[] = "TRWAGMYFPDXBNJZSQVHLCKE";

    // Comprobar si hay letra al final
    if ( LetraNIF != 0 ) {
        nif.erase( nif.length() - 1 );
    }

    // Calcular letra
    if ( std::isalpha( nif[ 0 ] ) ) {
        // Eliminar el caracter inicial, si existe.
        nif.erase( 0, 1 );
    }

    return LetrasNIF[ StringMan::toIntNum( nif ) % strlen( LetrasNIF ) ];
}

std::string CampoDni::validarDNI(const std::string &nif)
{
    std::string &toret = msgErrorValidacion;
    const char LetraNIF = getLetra( StringMan::trim( nif ) );
    char letraCalculada;

    toret = "";

    // Comprobar que tiene un formato correcto
    if ( !esFmtCorrecto( nif ) ) {
        toret = "Formato de DNI/NIF incorrecto.";
    }
    else {
        letraCalculada = calcularLetraNif( StringMan::trim( nif ) );

        // resultado
        if ( LetraNIF != letraCalculada ) {
                toret = "Letra del NIF calculada '";
                toret += letraCalculada;
                toret += "' y no '";
                toret += LetraNIF == 0 ? ' ' : LetraNIF;
                toret += '\'';
        }
    }

    return toret;
}

// ----------------------------------------------------------- CampoDNI::toCsv()
std::string CampoDni::toCsv(unsigned int i, OpcionesCsv ops) const
{
	std::string toret = StringMan::trim( getValor( i ) );
	const char LetraNIF = getLetra( i );

	if ( ops.esDNISinLetra ) {
	    // NIF letter ?
		if ( LetraNIF != 0 ) {
			toret.erase( toret.length() - 1 );
		}

		// First letter?
		if ( std::isalpha( toret[ 0 ] ) ) {
		    toret.erase( 0, 1 );
		}
	}
	else toret = Campo::toCsv( toret, ops );

	return toret;
}

// ---------------------------------------------------------- CampoDni::copiar()
CampoDni * CampoDni::copiar() const
{
	CampoDni * toret = new CampoDni( *this );
    toret->eliminarTodosObservadores();

	return toret;
}
