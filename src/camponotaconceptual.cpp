/************************************************************************
  			camponotaconceptual.cpp - baltasarq@yahoo.es

	Implementación de la nota conceptual

This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#include "stringman.h"
#include "documentocalifa.h"
#include "camponotaconceptual.h"
#include "nota.h"
#include "ui.h"

// ========================================================= CampoNotaConceptual
// ---------------------------------- CampoNotaConceptual::CampoNotaConceptual()
CampoNotaConceptual::CampoNotaConceptual(DocumentoCalifa *doc) : Campo( doc )
{
}

// ---------------------------------------------- CampoNotaConceptual::calcula()
void CampoNotaConceptual::calcula()
{
	ponInicioProgreso();

	for(unsigned int i = 0; i < getNumFilas(); ++i) {
		calcula( i );

		ponProgreso( "Calculando ...", 0, i, getNumFilas() );
	}

	ponFinalProgreso();
}

// ------------------------------------------- CampoNotaConceptual::actualizar()
void CampoNotaConceptual::actualizar(Observable *rmt, TipoCambio t)
{
	calcula( ( (Campo *) rmt )->getNumFilaCambiada() );
}

// ---------------------------------------------- CampoNotaConceptual::calcula()
void CampoNotaConceptual::calcula(unsigned int i)
{
	CampoNotaFinal * campoNotaFinal = getPerteneceA()->getCampoNotaFinal();

	if ( campoNotaFinal != NULL ) {

		if ( esFilaCorrecta( i ) ) {
			putValor( i, Nota::cnvtNotaStr( campoNotaFinal->getValorNumerico( i ) ) );
		}
		else throw creaErrorIndiceIncorrecto(
						i, getNumFilas(), "calculando nota conceptual"
			 );

	}
	else throw InconsistenciaError( "No existe nota final" );
}

// ----------------------------------------------- CampoNotaConceptual::cumple()
bool CampoNotaConceptual::cumple(unsigned int i) const
{
	if ( !esFilaCorrecta( i ) ) {
		throw creaErrorIndiceIncorrecto( i, getNumFilas(), "cumple nota conceptual" );
	}

	double notaGuardada = Nota::cnvtStrNota( getValor( i ) );

	return ( notaGuardada != Nota::vNumNotasTipo[ Nota::Error ] );
}

// ------------------------------------------ CampoNotaConceptual::getDescTipo()
const std::string CampoNotaConceptual::StrDescTipo = "CampoNotaConceptual";
const std::string &CampoNotaConceptual::getDescTipo() const
{
	return StrDescTipo;
}

// ----------------------------------------------- CampoNotaConceptual::copiar()
CampoNotaConceptual * CampoNotaConceptual::copiar() const
{
	CampoNotaConceptual * toret = new CampoNotaConceptual( *this );
	toret->eliminarTodosObservadores();
	toret->dejarDeObservarTodos();

	return toret;
}
