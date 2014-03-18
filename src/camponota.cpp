/************************************************************************
  			camponota.cpp - baltasarq@yahoo.es

This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#include "camponota.h"
#include "nota.h"
#include "documentocalifa.h"
#include "gtk_uintf.h"
#include "ui.h"
#include <clocale>
#include <cctype>
#include <cmath>

const double CampoNota::NotasPromociones[]        = { 9, 8.70, 6.70, 4.70 };
const std::string CampoNota::MarcasPromociones[]  = { "mh", "sb", "n", "a" };
const double CampoNota::LimiteSuperior = 10;
const double CampoNota::LimiteInferior = -1;
const double CampoNota::ValorPorDefecto = -1;
const double CampoNota::RazonAprobado = 0.5;

// ------------------------------------------------------ CampoNota::CampoNota()
CampoNota::CampoNota(DocumentoCalifa * doc)
	: Campo( doc ), peso( 0 ), _esNecesarioAprobar( true ),
	  _esPuntuacionSobreDiez( false )
{
}

// -------------------------------------------------------- CampoNota::calcula()
void CampoNota::calcula()
{
	ponInicioProgreso();

	for(unsigned int i = 0; i < getNumFilas(); ++i) {
		calcula( i );

		ponProgreso( "Calculando ...", 0, i, getNumFilas() );
	}

	ponFinalProgreso();
}

// -------------------------------- CampoNotaParcial::normalizarNotasSobreDiez()
void CampoNota::normalizarNotasSobreDiez()
/**
	Cambiar todas las notas para que estén puntuadas sobre 10 o no
	Toma el valor actual de esPuntuacionSobreDiez(), para actualizarlo a lo
	que devuelva.
*/
{
	double valor;

	ponInicioProgreso();

	for(unsigned int i = 0; i < getNumFilas(); ++i) {
		valor = getValorNumerico( i );

		if ( valor > 0 ) {
			if ( esPuntuacionSobreDiez() )
					putValor( i, ( valor * MaxPeso ) / getPeso() );
			else	putValor( i, ( valor * getPeso() ) / MaxPeso );
		}

		ponProgreso( "Normalizando sobre 10...", 0, i, getNumFilas() );
	}

	ponFinalProgreso();
}

// -------------------------------------------------------- CampoNota::calcula()
/**
	Devuelve la nota total con el peso aplicado y todo.
	Normalmente aparece la puntuación según el peso, pero se puede indicar
 	que aparezca sobre 10.
*/
double CampoNota::calcula(unsigned int pos)
{
	double toret = 0;

	if ( esFilaCorrecta( pos ) ) {
		toret = getValorNumerico( pos );

		// Si es no presentado ...
		if (  toret >= 0 ) {
			if ( cumple( pos ) ) {
				if ( esFmtCorrecto( getValor( pos ) ) ) {
					if ( esPuntuacionSobreDiez() ) {
							toret = toret * ( ( (double) getPeso() ) / 100 );
					}
				}
				else throw creaErrorFmt( getValor( pos ), getLimiteSuperior() );
			}
		}
	}
	else throw creaErrorIndiceIncorrecto( pos, getNumFilas(), "calculando campo nota" );

	return toret;
}

// --------------------------------------------------- CampoNotaFinal::calcula()
double CampoNota::calculaAproximado(unsigned int pos)
{
	double toret = 0;

	if ( esFilaCorrecta( pos ) ) {
		if ( esFmtCorrecto( getValor( pos ) ) ) {
			if ( esPuntuacionSobreDiez() )
					toret = getValorNumerico( pos )
							* ( ( (double) getPeso() ) / 100 );
			else 	toret = getValorNumerico( pos );
		}
		else throw creaErrorFmt( getValor( pos ), getLimiteSuperior() );
	}
	else throw creaErrorIndiceIncorrecto( pos, getNumFilas(), "calculando campo nota" );

	return toret;
}

// ------------------------------------------------------- CampoNota::putValor()
void CampoNota::putValor(unsigned int pos, double nota)
{
	setlocale( LC_ALL, "C" );
	std::string strNota = StringMan::toString( nota, 4, 2 );
	setlocale( LC_ALL, "" );

	putValor( pos, strNota );
}

void CampoNota::putValor(unsigned int pos, const std::string &nota)
{
	std::string laNota =
		nota.empty() ? StringMan::toString( LimiteInferior ) : nota
	;

	if ( esFmtCorrecto( laNota, TenerEnCuentaPeso ) )
			Campo::putValor( pos, laNota );
	else 	throw creaErrorFmt( laNota, getLimiteSuperior() );
}

// ------------------------------------------------------- CampoNota::getValor()
double CampoNota::getValorNumerico(unsigned int pos) const
{
	double toret;

	setlocale( LC_ALL, "C" );
	toret = StringMan::toFltNum( Campo::getValor( pos ) );
	setlocale( LC_ALL, "" );

	return toret;
}

// ------------------------------------------------ CampoNota::getEstadisticas()
std::string CampoNota::getEstadisticas() const
{
	int numAptos = 0;
	int nums[Nota::Error];
	unsigned int numCalifas = getNumFilas();
	double nota = 0;
	Nota::NotaConceptual tipoNota;
	std::string toret;

	memset( &nums, 0, sizeof( int ) * ( ( int ) Nota::Error ) );

	if ( numCalifas > 0 ) {
		for(unsigned int i = 0; i < numCalifas; ++i) {
			nota = getValorNumerico( i );
			tipoNota = Nota::cnvtNotaTipo( nota );

			ponProgreso( "Calculando estadísticas ...", 0, i, numCalifas );

			// Número de aptos
			if ( estaAprobada( i ) ) {
				++numAptos;
			}

			// Número de aprobados, suspensos ... etc
			if ( tipoNota == Nota::NoPresentado ) {
				++nums[ Nota::getOrdinal( Nota::NoPresentado ) ];
			}
			else
			if ( tipoNota == Nota::Aprobado ) {
				++nums[ Nota::getOrdinal( Nota::Aprobado ) ];
			}
			else
			if ( tipoNota == Nota::Suspenso ) {
				++nums[ Nota::getOrdinal( Nota::Suspenso ) ];
			}
			else
			if ( tipoNota == Nota::Notable ) {
				++nums[ Nota::getOrdinal( Nota::Notable ) ];
			}
			else
			if ( tipoNota == Nota::Sobresaliente ) {
				++nums[ Nota::getOrdinal( Nota::Sobresaliente ) ];
			}
			else
			if ( tipoNota == Nota::MatriculaHonor ) {
				++nums[ Nota::getOrdinal( Nota::MatriculaHonor ) ];
			}
		}

		// Visualizar número de califas
		toret +=
			"Número de calificaciones: "
		  + StringMan::toString( numCalifas )
		;

		// Guardar número de aptos
		toret +=
			"\nNúmero de aptos: "
		  + StringMan::toString( numAptos )
		  + " ("
		  + StringMan::toString( ( (double) numAptos / numCalifas ) * 100, 5, 2 )
		  + "%)"
		;

		// Visualizar el resto de notas
		unsigned int i = Nota::getOrdinal( Nota::NoPresentado );
		for(; i < Nota::getOrdinal( Nota::Error ); ++i ) {
			toret +=
				"\nNúmero de alumnos con nota "
			  + Nota::cnvtTipoNotaStr( (Nota::NotaConceptual) i )
			  + ": "
			  + StringMan::toString( nums[ i ] )
			  + " ("
			  + StringMan::toString( ( (double) nums[ i ] / numCalifas ) * 100, 5, 2 )
			  + "% sobre el total, "
			  + ( numAptos > 0 ?
			  	StringMan::toString( ( (double) nums[ i ] / numAptos ) * 100, 5, 2 )
				: "0" )
			  + "% sobre aptos)"
			;
		}
	}
	else toret = "\nNo existen calificaciones en " + nombre;

	return toret;
}

// --------------------------------------------------- CampoNota::getPromocion()
const std::string &CampoNota::getPromocion(unsigned int i)
/**
	Devuelve una letra (o dos) según promocione la nota
*/
{
	double nota = getValorNumerico( i );
	double notaOrg = nota;
	double limiteSuperior;
	buffer.clear();
	buffer.push_back( ' ' );

	if ( nota == 0.0 ) {
		nota = calculaAproximado( i );
	}

	for(unsigned int i = 0;  i < NumPromociones; ++i)  {
		limiteSuperior = std::ceil( NotasPromociones[ i ] );

		// Para el sobresaliente y la MH
		if ( limiteSuperior == NotasPromociones[ i ] ) {
			limiteSuperior += 1.0;
		}

		// Para el aprobado
		if ( limiteSuperior == ( getLimiteSuperior() / 2 ) ) {
			limiteSuperior = NotasPromociones[ i - 1 ];

			// Ya tiene el aprobado, no continuar
			if ( notaOrg > 0.0 ) {
				continue;
			}
		}

		if ( nota > NotasPromociones[ i ]
		  && nota < limiteSuperior )
		{
			buffer = MarcasPromociones[ i ];
			break;
		}
	}

	return buffer;
}

// -------------------------------------------------- CampoNota::esFmtCorrecto()
bool CampoNota::esFmtCorrecto(const std::string &strNum, bool tenerEnCuentaPeso)
{
	bool toret = false;

	// Convertir el numerajo que nos pasan
	setlocale( LC_ALL, "C" );
	double nota = StringMan::toFltNum( strNum );
	setlocale( LC_ALL, "" );

	// Revisión lims. (si hay un error es 0 al convertir)
	if ( nota >= getLimiteInferior()
	  && nota <= getLimiteSuperior() )
	{
		toret = StringMan::esNumeroDecimal( strNum );
	}

	return toret;
}

double CampoNota::getLimiteSuperior() const
{
	// Poner el límite superior adecuado
	if ( esPuntuacionSobreDiez() )
	{
		return LimiteSuperior;
	}
	else return ( peso / LimiteSuperior );
}

double CampoNota::getLimiteInferior() const
{
	return LimiteInferior;
}

// --------------------------------------------------- CampoNota::creaErrorFmt()
FmtError CampoNota::creaErrorFmt(const std::string &strNoNota, double limSup)
{
	return FmtError( "Nota debe ser un número flotante entre "
				+ StringMan::toString( CampoNota::LimiteInferior )
				+ " y "
			    + StringMan::toString( limSup )
			    + ", no '"
				+ strNoNota
				+ '\''
	);
}

// ---------------------------------------------------------- CampoNota::toCsv()
std::string CampoNota::toCsv(unsigned int i, OpcionesCsv ops) const
{
	std::string toret;

	if ( esFilaCorrecta( i ) ) {
		toret = getValor( i );

		if ( ops.chDecimal != '.' ) {
			unsigned int pos = toret.find( '.' );

			if ( pos != std::string::npos ) {
				toret[ pos ] = ops.chDecimal;
			}
		}
	}
	else throw creaErrorIndiceIncorrecto( i, getNumFilas(), "toCsv() en: " + nombre );

	return toret;
}

// ------------------------------------------------------- CampoNota::toString()
const std::string &CampoNota::toString(unsigned int i)
{
	const std::string *toret;
	double valor;

	if ( !esPuntuacionSobreDiez() ) {
		toret = &buffer;
		valor = getValorNumerico( i );

		valor *= peso / 100;

		buffer = StringMan::toString( valor );
	}
	else toret = &( getValor( i ) );

	return *toret;
}

// ============================================================ CampoNotaParcial
// ---------------------------------------- CampoNotaParcial::CampoNotaParcial()
CampoNotaParcial::CampoNotaParcial(DocumentoCalifa *doc) : CampoNota( doc )
{
}

// --------------------------------------------- CampoNotaParcial::getDescTipo()
const std::string CampoNotaParcial::StrDescTipo = "CampoNotaParcial";
const std::string &CampoNotaParcial::getDescTipo() const
{
	return StrDescTipo;
}

// -------------------------------- CampoNotaParcial::normalizarNotasParciales()
void CampoNotaParcial::normalizarNotasParciales(DocumentoCalifa &d)
{
	std::vector<CampoNotaParcial *> vcnp;
	const DocumentoCalifa::ListaCampos &l = d.getListaCampos();

	// Recolectar aquellos campos que son notas parciales
	for(unsigned int i = 0; i < l.size(); ++i) {
		if ( dynamic_cast<CampoNotaParcial *>( l[ i ] ) != NULL ) {
			vcnp.push_back( (CampoNotaParcial *) l[ i ] );
		}
	}

	// ¿A cuánto tocan?
	unsigned int peso = ( (unsigned int) ( ( (double) MaxPeso ) / vcnp.size() ) );

	// Poner los porcentajes
	for(unsigned int i = 0; i < vcnp.size(); ++i) {
        vcnp[ i ]->putEsPuntuacionSobreDiez( true );
		vcnp[ i ]->putPeso( peso );
	}
}

// -------------------------------------------------- CampoNotaParcial::copiar()
CampoNotaParcial * CampoNotaParcial::copiar() const
{
	CampoNotaParcial * toret = new CampoNotaParcial( *this );
	toret->eliminarTodosObservadores();

	return toret;
}
