/************************************************************************
  			campoverif.h - baltasarq@yahoo.es

	Campos de verificación, pueden valer sí o no

This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#ifndef CAMPOVERIF_H
#define CAMPOVERIF_H
#include <string>
#include "campo.h"
#include "excep.h"
#include "estudiable.h"

/**
 * Class CampoVerif
 * Una marca de verificación (Sí o No).
 * Si es informativa, no influye en la nota. En caso contrario,
 * influye de manera que el alumno suspende (o no).
 */
class CampoVerif : public Campo, public Estudiable {
public:
	static const std::string Si;
	static const std::string No;
	static const std::string StrDescTipo;
	static const std::string Sies;
	static const std::string Noes;

    CampoVerif(DocumentoCalifa *);

	const std::string &getDescTipo() const;

	static FmtError creaErrorFmt(const std::string &);

	const std::string getContenidoPorDefecto() const
		{ return CampoVerif::No; }

    /**
     * @return true si es informativo o no es informativo y vale sí,
	 *         falso en otro caso
     */
    bool  cumple(unsigned int i) const
		{
			return ( esInformativo() || ( !esInformativo() && getValorBooleano( i ) ) );
		}

    /**
     * Devuelve el valor de una determinada fila
     * @param pos La fila de la que obtener el valor
	 * @return El valor de esa fila, como booleano.
     */
    bool getValorBooleano(unsigned int pos) const;

    /// @brief Devuelve las estadísticas del campo
	std::string getEstadisticas() const;

    /**
     * Cambia el valor de una fila
     * @param pos La fila a cambiar
     * @param verif El booleano que indica sí o no
     */
    void putValor(unsigned int pos, bool verif)
		{ Campo::putValor( pos, ( verif ? Si : No ) ); }

	static bool esFmtCorrecto(const std::string &);

	CampoVerif * copiar() const;
};
#endif //CAMPOVERIF_H
