/************************************************************************
  			camponota.h - baltasarq@yahoo.es


	Esta clase representa a todos los campos de notas del documento

This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#ifndef CAMPONOTA_H
#define CAMPONOTA_H
#include <string>
#include "campo.h"
#include "estudiable.h"
#include "stringman.h"

/**
 * Class CampoNota
 * Una columna que guarda notas numéricas como valores para sus filas.
 */
class CampoNota : public Campo, public Estudiable {
public:
	static const double NotasPromociones[];
	static const std::string MarcasPromociones[];
	static const unsigned int NumPromociones = 4;
	static const double LimiteSuperior;
	static const double LimiteInferior;
	static const double ValorPorDefecto;
protected:

	/// Para convertir formatos de campo sin problema
	std::string buffer;

    /**
     * Un número de 0 a 100 que indica el peso de esta nota sobre el global
     */
     unsigned int peso;

     /**
     * Indica si es necesario tener más de un cinco o no para calcular el resto.
     */
     bool _esNecesarioAprobar;

  	 /// Indica si la puntuación es sobre 10 o sobre el peso
	 bool _esPuntuacionSobreDiez;

public:
	static const unsigned int MinPeso = 0;
	static const unsigned int MaxPeso = 100;
	static const double RazonAprobado;
	static const unsigned int NoTenerEnCuentaPeso = false;
	static const unsigned int TenerEnCuentaPeso = true;

    CampoNota(DocumentoCalifa *);

	/// @return true si la puntuacion es sobre diez
	bool esPuntuacionSobreDiez() const
		{ return _esPuntuacionSobreDiez; }

	virtual double getValorPorDefecto() const
		{ return CampoNota::ValorPorDefecto; }

	const std::string getContenidoPorDefecto() const
		{ return StringMan::toString( getValorPorDefecto() ); }

	std::string getEstadisticas() const;

    /**
     * @return true si es necesario tener más de un cinco en esta nota
     */
    bool esNecesarioAprobar() const
		{ return _esNecesarioAprobar; }

	/// Pone la puntuación sobre 10 o no
	void putEsPuntuacionSobreDiez(bool sobreDiez = true)
		{
			if ( sobreDiez != _esPuntuacionSobreDiez ) {
				_esPuntuacionSobreDiez = sobreDiez;
				normalizarNotasSobreDiez();
			}
		}

	void normalizarNotasSobreDiez();

    /**
     * Cambia el valor de si es necesario aprobar. Recalcula si es true
     */
    void putEsNecesarioAprobar(bool esNecesario = true)
		{
			if ( esNecesario ) {
				calcula();
			}

        	_esNecesarioAprobar = esNecesario;
    	}

    /**
	 * Muestra el contenido según el tipo de puntuación
     * @return una cadena conteniendo la descripción como texto de una fila
     */
    const std::string &toString(unsigned int i);

    /**
     * @return true si la nota > 5 y es necesario aprobar
	 * o no es necesario aprobar
     */
    bool estaAprobada(unsigned int i) const
		{
			return ( !esNecesarioAprobar()
			      || ( esNecesarioAprobar()
				    && ( getValorNumerico( i ) >= ( getLimiteSuperior() * RazonAprobado ) ))
			);
		}

	/// Devuelve la promoc. (si procede) de una nota
	const std::string &getPromocion(unsigned int i);



    /**
     * @return true si la nota se puede sumar para obtener la nota final
     */
    bool cumple(unsigned int i) const
		{
			return ( esInformativo() || estaAprobada( i ) );
		}


	/// Cambia el valor de una fila de esta columna
	/// @param pos La posición en la columna (fila)
	/// @param str El nuevo valor
	void putValor(unsigned int pos, const std::string &str = "");

    /**
     * Cambia el valor de una fila de esta columna
     * @param pos El número de fila
     * @param nota La nueva nota (como número)
     */
    void putValor(unsigned int pos, double nota);


    /**
     * Devuelve el valor de una fila de esta columna
     * @param pos
     */
    double getValorNumerico(unsigned int pos) const;


    /**
     * Calcula la nota para cada fila y la almacena
     */
    void calcula();


    /**
     * Calcula la nota para una fila concreta y la almacena y devuelve
     * @param pos La fila
     */
    double calcula(unsigned int pos);

	/// Calcula la nota aproximada de la fila pos
	/// @param pos La fila de la que calcular la nota aproximada.
	virtual double calculaAproximado(unsigned int pos);

    /**
     * Devuelve el peso de esta nota en el global
	 * @return el peso
     */
    int getPeso() const
		{ return peso; }

    /**
     * Cambia el peso de las notas de esta columna sobre el global
     */
    void putPeso(unsigned int peso )
		{
			if ( peso >= MinPeso
			  && peso <= MaxPeso )
			{
        		this->peso = peso;
			}
			else throw InconsistenciaError( "Peso fuera de margen en " + nombre );
    	}

	/// Devuelve el límite superior de la nota (10 o menos, según peso)
	/// @see LimiteSuperior
	double getLimiteSuperior() const;

	/// Devuelve el límite inferior de la nota (-1, no presentado)
	/// @see LimiteInferior
	double getLimiteInferior() const;

	/** Comprobar que es un formato correcto
	  * @param v el valor a comprobar
	  * @param tenerEnCuentaPeso Por defecto es false. Si es true, se tiene en
		       cuenta que si se ha elegido que no se puntúe sobre diez, entonces
			   el límite superior lo marca el peso.
	*/
	bool esFmtCorrecto(const std::string &v, bool tenerEnCuentaPeso = NoTenerEnCuentaPeso);

	/**
	  * Crea una excepción de formato para las notas (nota no es número
	  *	o está fuera de márgenes).
	  * @param v El valor de la nota.
	  * @return Un objeto adecuado del tipo FmtError
	*/
	static FmtError creaErrorFmt(const std::string &v, double limSup);

	// Pasar a CSV
	std::string toCsv(unsigned int i, OpcionesCsv ops) const;
};

/// Las notas normales que no son finales
class CampoNotaParcial : public CampoNota {
public:
	static const std::string StrDescTipo;
	CampoNotaParcial(DocumentoCalifa *doc);

	static void normalizarNotasParciales(DocumentoCalifa &);

	const std::string &getDescTipo() const;

	CampoNotaParcial * copiar() const;
};

#endif //CAMPONOTA_H
