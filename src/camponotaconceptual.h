/************************************************************************
  			camponotaconceptual.h - baltasarq@yahoo.es

	La nota otorgada según un determinado valor numérico

This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#ifndef CAMPONOTACONCEPTUAL_H
#define CAMPONOTACONCEPTUAL_H
#include <string>
#include "campo.h"
#include "camponotafinal.h"

/**
 * Clase CampoNotaConceptual
 * Columna que a partir de la nota final, genera las notas conceptuales.
 */
class CampoNotaConceptual : public Campo, public Observador {
public:
	static const std::string StrDescTipo;

    CampoNotaConceptual(DocumentoCalifa *);

	const std::string &getDescTipo() const;

   /**
	* Calcula la nota conceptual de cada fila y las almacena
	*/
	void calcula();

	/**
	  Comprueba que el campo cumpla y contenga uno de los valores
	  predeterminados.
	*/
	bool cumple(unsigned int) const;

	/// Avisa CampoNotaFinal cuando ha cambiado
	void actualizar(Observable *rmt, TipoCambio t);

	/**
	* Calcula la nota conceptual de una fila y la almacena y devuelve
	*/
	void calcula(unsigned int i);

	bool esEditable() const
		{ return false; }

	CampoNotaConceptual * copiar() const;
};

#endif //CAMPONOTACONCEPTUAL_H
