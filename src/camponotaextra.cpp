// camponotaextra.cpp
/*
	Campo que guarda una nota a sumar a la nota del alumno.
*/

#include "camponotaextra.h"
#include "ui.h"

const double CampoNotaExtra::ValorPorDefecto = 0;

CampoNotaExtra::CampoNotaExtra(DocumentoCalifa *doc)
	: CampoNota(doc)
{
	putPeso( MaxPeso );
	putEsNecesarioAprobar( false );
	putEsPuntuacionSobreDiez( true );
}

const std::string CampoNotaExtra::StrDescTipo = "CampoNotaExtra";

CampoNotaExtra * CampoNotaExtra::copiar() const
{
	CampoNotaExtra * toret = new CampoNotaExtra( *this );
	toret->eliminarTodosObservadores();

	return toret;
}

// ------------------------------------------- CampoNotaExtra::getEstadisticas()
std::string CampoNotaExtra::getEstadisticas() const
{
	double notaMedia = 0;
	double maximo;
	double minimo;
	int numEncima = 0;
	int numDebajo = 0;
	unsigned int numCalifas = getNumFilas();
	std::string toret;

	if ( numCalifas > 0 ) {
		double nota = maximo = minimo = getValorNumerico( 0 );

		// Media, máximo y mínimo
		for(unsigned int i = 0; i < numCalifas; ++i) {
			nota = getValorNumerico( i );
			notaMedia += nota;

			if ( nota > maximo ) {
					maximo = nota;
			}
			else
			if ( nota < minimo ) {
					minimo = nota;
			}

			ponProgreso( "Calculando estadísticas ...", 0, i, numCalifas * 2);
		}
		notaMedia /= numCalifas;

		// Por encima y por debajo de la media
		for(unsigned int i = 0; i < numCalifas; ++i) {
			nota = getValorNumerico( i );

			if ( nota >= notaMedia )
					++numEncima;
			else	++numDebajo;

			ponProgreso( "Calculando estadísticas ...", numCalifas, numCalifas + i, numCalifas * 2);
		}


		// Visualizar número de califas
		toret +=
			"Número de calificaciones: "
		  + StringMan::toString( numCalifas )
		;

		// Nedia de notas, máximo y mínimo
		toret +=
			"\nMedia: " + StringMan::toString( notaMedia )
		  + "\nMínimo: " + StringMan::toString( minimo )
		  + "\nMáximo: " + StringMan::toString( maximo )
		;


		// Guardar número de aptos
		toret +=
			"\nNúmero de notas por encima de la media: "
		  + StringMan::toString( numEncima )
		  + " ("
		  + StringMan::toString( ( (double) numEncima / numCalifas ) * 100, 5, 2 )
		  + "%)"
		;

		// Guardar número de no aptos
		toret +=
			"\nNúmero de notas por debajo de la media: "
		  + StringMan::toString( numDebajo )
		  + " ("
		  + StringMan::toString( ( (double) numDebajo / numCalifas ) * 100, 5, 2 )
		  + "%)"
		;
	}
	else toret = "\nNo existen calificaciones en " + nombre;

	return toret;
}

