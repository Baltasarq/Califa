// campodni.h
/*
	Esta clase representa a los campos (columnas) que guardan un DNI.
*/

#ifndef _CAMPO_DNI_H_
#define _CAMPO_DNI_H_

#include <map>
#include <string>
#include "campo.h"

class CampoDni : public Campo {
	public:
		static const std::string StrDescTipo;
		static const std::string ContenidoPorDefecto;
		static const char LetraNifProhibida = 'O';

		CampoDni(DocumentoCalifa *doc);

		void putValor(unsigned int pos, const std::string &strDni);
		bool cumple(unsigned int) const;

		const std::string getContenidoPorDefecto() const
			{ return CampoDni::ContenidoPorDefecto; }

		const std::string &getDescTipo() const;

	    /**
    	 * Convierte el valor de una fila de un campo DNI a CSV
	     * Es necesario debido a creaweb, no soporta la letra del NIF al final
     	 * @param ops Las opciones para generar el documento CSV para este campo
     	*/
    	virtual std::string toCsv(unsigned int i, OpcionesCsv ops) const;

		static bool esFmtCorrecto(const std::string &);
		static FmtError creaErrorFmt(const std::string &);

		CampoDni * copiar() const;

		char getLetra(unsigned int i) const
            { return getLetra( getValor( i ) ); }

        static const std::string &getMsgErrorValidacion()
            { return msgErrorValidacion; }

		static char getLetra(const std::string &);
		static std::string validarDNI(const std::string &);
		static char calcularLetraNif(std::string nif);
	private:
		using Campo::putEsInformativo;
		static std::string msgErrorValidacion;
};

#endif
