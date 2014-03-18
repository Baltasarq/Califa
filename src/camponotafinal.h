/************************************************************************
  			camponotafinal.h - baltasarq@yahoo.es

	El campo de nota final, es pelín especial.

This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#ifndef CAMPONOTAFINAL_H
#define CAMPONOTAFINAL_H
#include <string>
#include "camponota.h"
#include "observador.h"

/**
 * Class CampoNotaFinal
 * La nota final, realizando la suma ponderada de aquellos campos de nota que
 * no son informativos.
 */
class CampoNotaFinal : public CampoNota, public Observador {
public:
	static const std::string StrDescTipo;

    CampoNotaFinal(DocumentoCalifa *);

	const std::string &getDescTipo() const;

	/**
     * Obliga a recalcular la nota final, y las guarda cada una en su fila.
     */
    void  calcula();
        
    
    /**
     * 
     * @param pos Obliga a calcular la nota final de una fila, y la guarda
     */
    double  calcula(unsigned int pos);
	
	/// Calcula la nota aproximada de la fila pos
	/// @param pos La fila de la que calcular la nota aproximada.
	double calculaAproximado(unsigned int pos);

	/**
	  * Actualizar cuando una columna notifique un cambio
	*/
	void actualizar(Observable *, TipoCambio);

	bool esEditable() const
		{ return false; }
		
	CampoNotaFinal * copiar() const;
};
#endif //CAMPONOTAFINAL_H
