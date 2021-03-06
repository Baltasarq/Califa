/************************************************************************
  			campo.cpp - baltasarq@yahoo.es

			Implementación de un campo del documento

This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#include <cstdlib>
#include <stdexcept>

#include "stringman.h"
#include "campo.h"
#include "documentocalifa.h"
#include "ui.h"
#include "excep.h"

const std::string Campo::ContenidoPorDefecto = "";

// -------------------------------------------------------------- Campo::Campo()
Campo::Campo(DocumentoCalifa *doc)
	: perteneceA( doc ), _esInformativo( false ), estaOculta( false )
{
	if ( doc == NULL ) {
		throw InconsistenciaError( "Campo debe pertenecer a un documento" );
	}
}

// ----------------------------------------------------------- Campo::putValor()
void Campo::putValor(unsigned int pos, const std::string &str)
/**
	Se notifica al observador sólo si se trata de una modificación, no de una
	adición, lo que sería un error al no haber fila correspondiente en
	CampoNotaFinal.
	Será notificado al final de DocumentoCalifa::annade().
*/
{
	if ( pos < getNumFilas() )
	{
		vValores[ pos ] = StringMan::trim( str );
		filaCambiada = pos;

		if ( esEditable() ) {
			getPerteneceA()->_fueModificado = true;
		}

		// Notificar del cambio sólo si es una modificación
		if ( !esInformativo()
		  && !estaEnMedioAdicionFila()
		  && !getPerteneceA()->enCarga() )
		{
			notificar( Observador::CambioEnElemento );
		}
	}
	else throw creaErrorIndiceIncorrecto( pos, getNumFilas(),
					"putValor(): buscando valor " + StringMan::toString( pos )
		 );
}

// --------------------------------------------- Campo::estaEnMedioAdicionFila()
bool Campo::estaEnMedioAdicionFila()
{
	bool toret = false;

	for( getPrimerObservador(); !esUltimoObservador(); ++itObsd ) {
		if ( ( (Campo *) *itObsd )->getNumFilas() != getPerteneceA()->getNumFilas() )
		{
			toret = true;
			break;
		}
	}

	return toret;
}

// ----------------------------------------------------------- Campo::getValor()
const std::string &Campo::getValor(unsigned int pos) const
{
	if ( pos < getNumFilas() )
			return vValores[ pos ];
	else 	throw creaErrorIndiceIncorrecto( pos, getNumFilas(),
					"getValor(): buscando valor " + StringMan::toString( pos )
		    );
}

// ------------------------------------------------------------- Campo::annade()
void Campo::annade()
/**
	Aquí no se notifica al observador (nota final), pq no habrá fila en él
	hasta que sea insertada toda la fila.
	Se hace en DocumentoCalifa::annade()
*/
{
	vValores.push_back( getContenidoPorDefecto() );
	filaCambiada = getNumFilas() - 1;
}


// ----------------------------------------------------------- Campo::insertar()
void Campo::insertar(unsigned int i)
{
	if ( !esFilaCorrecta( i ) ) {
		throw creaErrorIndiceIncorrecto( i, getNumFilas(), "insertando" );
	}

	vValores.insert( vValores.begin() + i, getContenidoPorDefecto() );
	filaCambiada = i;
}

// ------------------------------------------------------------- Campo::borrar()
void Campo::borrar(unsigned int i)
{
	if ( !esFilaCorrecta( i ) ) {
		throw creaErrorIndiceIncorrecto( i, getNumFilas(), "borrando" );
	}

	vValores.erase( vValores.begin() + i );
}

// --------------------------------------------------------- Campo::normalizar()
void Campo::normalizarNumFilas()
/**
	Añade las filas necesarias o incluso elimina las sobrantes.
*/
{
	if ( getPerteneceA() != NULL ) {
		int numFilas = getPerteneceA()->getCampoDNI()->getNumFilas() - getNumFilas();

		if ( numFilas > 0 ) {
			ponInicioProgreso();
			for(int i = 0; i < numFilas; ++i) {
				annade();
				ponProgreso( "Añadiendo filas", 0, i, numFilas );
			}
			ponFinalProgreso();
		}
		else
		if ( numFilas < 0 ) {
			numFilas = std::abs( numFilas );
			vValores.erase( vValores.end() - numFilas, vValores.end() );
		}
	}
}

// ------------------------------------------ Campo::creaErrorIndiceIncorrecto()
IndiceIncorrectoError Campo::creaErrorIndiceIncorrecto(
	unsigned int i,
	unsigned int numFilas,
	const std::string &msg)
{
	std::string error = "Indice incorrecto: " + StringMan::toString( i + 1 ) + " de "
	 				+ StringMan::toString( numFilas )
					+ '(' + msg + ')'
	;

	return IndiceIncorrectoError( error );
}

// -------------------------------------------------------------- Campo::toCsv()
std::string Campo::toCsv(const std::string &x, OpcionesCsv ops)
{
    return '"' + StringMan::trim( x ) + '"';
}

// ------------------------------------------------------------- Campo::toHtml()
std::string Campo::toHtml(unsigned int pos) const
{
	return "<td><center><small>" + getValor( pos ) + "</small></center></td>";
}

// ------------------------------------------------------------ Campo::buscar()
unsigned int Campo::buscar(const std::string &cadenaBuscar, unsigned int pos) const
{
    unsigned int i;
    const unsigned int NumFilas = getNumFilas();

    // Acotar pos
    if (pos >= NumFilas ) {
        pos = 0;
    }

    // Buscar secuencialmente
    for(i = pos; i < NumFilas; ++i) {
        if ( StringMan::norm( getValor( i ) ).find( cadenaBuscar )
                            != std::string::npos)
        {
            break;
        }
    }

    return i;
}

void Campo::rellenar(const std::string &valor)
{
    std::string v = valor;

    if ( valor.empty() ) {
        v = this->getContenidoPorDefecto();
    }

    unsigned int numFilas = getPerteneceA()->getNumFilas();
    ponInicioProgreso();

    try {
        for(unsigned int i = 0; i < numFilas; ++i) {
            ponProgreso( "Rellenando ...", 0, i, numFilas );

            this->putValor( i, v );
        }
    }
    catch(const Error &e) {
        throw;
    }
    catch(const std::exception &e) {
        throw InternoError( e.what() );
    }
    catch(...) {
        throw InternoError( "ERROR inesperado: rellenando" );
    }

    ponFinalProgreso();
}
