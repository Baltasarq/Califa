/************************************************************************
  			campo.h - Copyright baltasarq@yahoo.es

This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#ifndef CAMPO_H
#define CAMPO_H
#include <string>
#include <vector>
#include "excep.h"
#include "observador.h"
#include "opcionescsv.h"

class DocumentoCalifa;

/**
 * Class Campo
 * Una columna de un DocumentoCalifa. Es la clase base para las columnas
 * con texto, verif. y con notas.
 *
 * Guarda todos los valores de las filas que tiene por debajo.
 */
class Campo : public Observable {
public:
	friend class DocumentoCalifa;
	typedef std::vector<std::string> ListaValores;
private:
    /**
     * El vector de valores
     */
     ListaValores vValores;

     DocumentoCalifa * perteneceA;
     bool _esInformativo;

protected:
	/// La fila que fue cambiada en la última operación de escritura
	unsigned int filaCambiada;
public:
	static const std::string ContenidoPorDefecto;
    std::string nombre;
    bool estaOculta;

    Campo(DocumentoCalifa *doc);
	virtual ~Campo()
		{}

	void normalizarNumFilas();

	void reset(unsigned int numFil)
		{ if ( numFil < getNumFilas() )
			vValores[ numFil ] = "";
		  else throw creaErrorIndiceIncorrecto(
			  					numFil, getNumFilas(),
		  						"reseteando valor del campo"
		  			 );
		}

	DocumentoCalifa * getPerteneceA()
		{ return perteneceA; }

	virtual const std::string getContenidoPorDefecto() const
		{ return Campo::ContenidoPorDefecto; }

	unsigned int getNumFilaCambiada() const
		{ return filaCambiada; }

	/*
	 * Devuelve el contenido de una fila de esta columna
	*/
    bool esFilaCorrecta(unsigned int i) const
		{ return ( i < vValores.size() ); }

    /*
	 * Devuelve el contenido de una fila de esta columna
	*/
    virtual const std::string &toString(unsigned int i)
		{ return getValor( i ); }

	/// Devuelve el número de filas en la columnas
	unsigned int getNumFilas() const
		{ return vValores.size(); }

    /**
     * Impone un valor determinado en una fila
	 * Nótese que este valor no se comprueba
     * @param pos La fila donde guardar la cadena
     * @param str La cadena en sí
     */
    virtual void putValor(unsigned int pos, const std::string &str = "");

    /**
     * Devuelve el valor de una determinada fila
     * @param pos
     */
    virtual const std::string &getValor(unsigned int pos) const;

	/// Inserta una nueva fila al final
	virtual void annade();

	/// Borra una fila
	void borrar(unsigned int i);

	/// Borrar todas las filas
	void borrarTodo()
		{ vValores.clear(); }

	/// Inserta una nueva fila
	virtual void insertar(unsigned int i);

	/// Comprueba si se está en medio de una adición de filas
	bool estaEnMedioAdicionFila();

    /**
     * Determinará si una determinada fila cumple para obtener la nota final
     */
    virtual bool cumple(unsigned int) const = 0;


    /**
     * El documento al que pertenece este campo
     */
    DocumentoCalifa  * getPerteneceA() const
		{ return perteneceA; }


    /**
     * Convierte el valor de una fila a CSV
     * @param ops Las opciones para generar el documento CSV para este campo
     */
    virtual std::string toCsv(unsigned int i, OpcionesCsv ops) const
        {  return toCsv( getValor( i ), ops ); }

    static std::string toCsv(const std::string &, OpcionesCsv ops);

    /**
     * Convierte el valor de una fila a html
     */
    virtual std::string toHtml(unsigned int) const;

    /**
     * @return La lista de valores del campo -- no debería ser modificada
     */
    ListaValores getValores() const
		{ return vValores; }

    /**
     * Devuelve true si es sólo informativo, false en otro caso
	 * @return si es informativo o no
     */
    bool esInformativo () const
		{ return _esInformativo; }

    /**
     * Pone un valor que indica si el campo es sólo informativo
     * @param inf booleano indicando si es sólo informativo o no
     */
    void putEsInformativo(bool value = true)
		{
        	_esInformativo = value;
			filaCambiada = getNumFilas() - 1;
			notificar( Observador::CambioEnElemento );

    	}

	/// Devuelve la descripción textual del *tipo* del campo
	virtual const std::string &getDescTipo() const = 0;

	/// @return si el campo es editable o no
	virtual bool esEditable() const
		{ return true; }

	/// @return una excepción de índice incorrecto
	static IndiceIncorrectoError creaErrorIndiceIncorrecto(
		unsigned int i, unsigned int numFilas, const std::string &);

	/// @return devuelve una copia del campo actual, NULL si no hay memoria
	virtual Campo * copiar() const = 0;
	virtual void rellenar(const std::string &valor = "");

	/**
        @param cadenaBuscar la cadena buscar, como objeto std::string
        @param pos La posc. a buscar 0 >= pos <= getNumFilas()
        @return la fila donde se encuentra, o el número de filas total si no existe
	*/
	virtual unsigned int buscar(const std::string &cadenaBuscar, unsigned int pos = 0) const;
};
#endif //CAMPO_H
