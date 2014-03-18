// camponotaextra.h
/*
 	Campo que guarda una nota a sumar a la nota del alumno.
*/

#ifndef __CAMPONOTAEXTRA__
#define __CAMPONOTAEXTRA__

#include <string>
#include "camponota.h"
#include "stringman.h"

/**
 * Class CampoVerif
 * Una marca de verificación (Sí o No).
 * Si es informativa, no influye en la nota. En caso contrario,
 * influye de manera que el alumno suspende (o no).
 */
class CampoNotaExtra : public CampoNota {
public:
	static const double ValorPorDefecto;
	static const std::string StrDescTipo;

    CampoNotaExtra(DocumentoCalifa *);

	double getValorPorDefecto() const
		{ return CampoNotaExtra::ValorPorDefecto; }

	const std::string &getDescTipo () const
		{ return StrDescTipo; }

    /**
     * @return siempre true
     */
    bool cumple(unsigned int i) const
		{
			return true;
		}

	void putPeso(unsigned int p)
		{ CampoNota::putPeso( MaxPeso ); }

	void putEsNecesarioAprobar(bool ap)
		{ CampoNota::putEsNecesarioAprobar( false ); }

	void putEsPuntuacionSobreDiez(bool sd)
		{ CampoNota::putEsPuntuacionSobreDiez( true ); }

	/// Calcula las estadísticas para campos extra
	std::string getEstadisticas() const;

	CampoNotaExtra * copiar() const;
};

#endif
