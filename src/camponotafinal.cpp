/************************************************************************
  			camponotafinal.cpp - baltasarq@yahoo.es

	La nota final es la que guarda la nota del alumno

This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#include <algorithm>

#include "gtk_uintf.h"
#include "camponotafinal.h"
#include "documentocalifa.h"
#include "ui.h"
#include "nota.h"

// ----------------------------------------------- CampoNotaFinal::getDescTipo()
const std::string CampoNotaFinal::StrDescTipo = "CampoNotaFinal";
const std::string &CampoNotaFinal::getDescTipo() const
{
	return StrDescTipo;
}

// -------------------------------------------- CampoNotaFinal::CampoNotaFinal()
CampoNotaFinal::CampoNotaFinal(DocumentoCalifa *doc) : CampoNota( doc )
{
	peso = MaxPeso;
	_esPuntuacionSobreDiez = true;
}

// ------------------------------------------------ CampoNotaFinal::actualizar()
void CampoNotaFinal::actualizar(Observable *obs, TipoCambio t)
{
	if ( t != BorradoElemento ) {
		calcula( ( (Campo *) obs )->getNumFilaCambiada() );
	}
}

// --------------------------------------------------- CampoNotaFinal::calcula()
void CampoNotaFinal::calcula()
{
	ponInicioProgreso();

	if ( !getPerteneceA()->enCarga() ) {
		for(unsigned int i = 0; i < getNumFilas(); ++i) {
			calcula( i );

			ponProgreso( "Calculando ...", 0, i, getNumFilas() );
		}
	}

	ponFinalProgreso();
}

// --------------------------------------------------- CampoNotaFinal::calcula()
double CampoNotaFinal::calculaAproximado(unsigned int pos)
{
	double toret = 0;

	if ( getPerteneceA()->enCarga() ) {
		goto FIN;
	}

	if ( esFilaCorrecta( pos ) ) {
		// Calcular el valor de esta columna
    	for( getPrimerObservable(); !( esUltimoObservable() ); ++itObsv) {
			// Si es una nota, sumarla
			if ( dynamic_cast<CampoNota *>( *itObsv ) ) {
				toret += ( (CampoNota *) *itObsv )->calculaAproximado( pos );
			}

		}
	}
	else throw creaErrorIndiceIncorrecto( pos, getNumFilas(),
										  "calculando nota final" );

	FIN:
	return toret;
}

// --------------------------------------------------- CampoNotaFinal::calcula()
double CampoNotaFinal::calcula(unsigned int pos)
{
	double toret = 0;
	double nota;
	CampoNota * cmpNota;
	const double CasiAprobado = Nota::cnvtTipoNota( Nota::Aprobado ) - 1;

	if ( getPerteneceA()->enCarga() ) {
		goto FIN;
	}

	if ( esFilaCorrecta( pos ) ) {
		// Calcular el valor de esta columna
    	for( getPrimerObservable(); !( esUltimoObservable() ); ++itObsv) {
			// A lo mejor es una nota, pero es no presentado
			if ( ( cmpNota = dynamic_cast<CampoNota *>( *itObsv ) ) != NULL ) {
				// Es un no presentado?
				if ( ( nota = cmpNota->calcula( pos ) ) < 0 ) {
					toret = -1;
					break;
				} else toret += nota;
			}

			// ¿Cumple el valor del campo?
			if ( !( ( (Campo *) *itObsv )->cumple( pos ) ) ) {
				toret = std::min( calculaAproximado( pos ), CasiAprobado );
				break;
			}

		}

		// Poner valor en la fila correspondiente
		if ( toret > getLimiteSuperior() ) {
			toret = getLimiteSuperior();
		}

		filaCambiada = pos;
		putValor( pos, toret );
		notificar( Observador::CambioEnElemento );
	}
	else throw creaErrorIndiceIncorrecto( pos, getNumFilas(),
										  "calculando nota final" );

	FIN:
	return toret;
}

// ---------------------------------------------------- CampoNotaFinal::copiar()
CampoNotaFinal * CampoNotaFinal::copiar() const
{
	CampoNotaFinal * toret = new CampoNotaFinal( *this );
	toret->dejarDeObservarTodos();
	toret->eliminarTodosObservadores();

	return toret;
}
