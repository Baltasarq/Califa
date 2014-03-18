/************************************************************************
  			campoinfo.h - Copyright baltasarq

	Campos de información textual que no intervienen en la evaluación


This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#ifndef CAMPOINFO_H
#define CAMPOINFO_H
#include <string>
#include "campo.h"

/**
 * Class CampoInfo
 * Columna de información textual.
 */
class CampoInfo : public Campo {
private:
	using Campo::putEsInformativo;
public:
	static const std::string StrDescTipo;	

	CampoInfo(DocumentoCalifa *);	

	/// Devolver el tipo del campo
	const std::string &getDescTipo() const;

    /**
     * @return Siempre devuelve true, siempre cumple las especificaciones
     */
    bool cumple()
		{
			return true;
		}
        		
	/// Estos campos lo cumplen todo siempre
	bool cumple(unsigned int) const
		{ return true; }
		
	CampoInfo * copiar() const;
		
    /**
     * Como el contenido es texto, hay que pasar los acentos a código HTML
     */
    std::string toHtml(unsigned int) const;
};
#endif //CAMPOINFO_H
