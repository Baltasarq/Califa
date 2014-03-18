/************************************************************************
  			documentocalifa.h - baltasarq@yahoo.es

			Implementación del documento que lleva la información de todos
			los campos.


This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#ifndef DOCUMENTOCALIFA_H
#define DOCUMENTOCALIFA_H

#include <cstdio>
#include <string>
#include <vector>

#include "camponotafinal.h"
#include "campodni.h"
#include "opcionescsv.h"
#include "persistente.h"

/**
 * Class DocumentoCalifa
 * El documento que engloba a todas las columnas de datos.
 * Debe permitir el acceso a las columnas, la generación de los datos en
 * formato CSV y HTML, y la creación a partir de un documento CSV.
 */
class DocumentoCalifa : public Persistente {
friend class Campo;
public:
     static const std::string ArchivoSinNombre;
	 static const std::string ExtArchivoDatos;
	 static const std::string NombreDNI;
	 static const std::string NombreNotaFinal;
	 static const std::string NombreInfoTextual;
	 static const std::string NombreNotaParcial;
	 static const std::string NombreVerificacion;
	 static const std::string NombreNotaExtra;
	 static const std::string NombrePredNotaConceptual;
	 static const std::string NombrePredObservaciones;
	 static const std::string NombrePredPractica;
	 static const std::string NombrePredPracticaFinal;
	 static const std::string NombrePredExamen;
	 static const std::string NombrePredNombre;
	 static const std::string NombrePredNotaExtra;
	 static const std::string EtqDocumento;
	 static const std::string EtqCampo;
	 static const std::string EtqPesoCampo;
	 static const std::string EtqNombreCampo;
	 static const std::string EtqTipoCampo;
	 static const std::string EtqEsInformativo;
	 static const std::string EtqEsNecesarioAprobar;
	 static const std::string EtqMostrarPuntuadoSobreDiez;
	 static const std::string EtqNombreAsignatura;
	 static const std::string EtqProfesores;
	 static const std::string EtqConvocatoria;
	 static const std::string EtqFecha;
	 static const std::string EtqComentario;
	 static const std::string EtqRevision;


	 static const char DelimContenidoFilasCampos = '"';
	 static const char SeparadorFilasCampos = ',';

	 static const bool Ascendente = true;
	 static const bool Descendente = false;

	 typedef std::vector<Campo *> ListaCampos;
	 typedef std::pair<std::vector<unsigned int>, std::vector<unsigned int> > ListaDNIs;
private:
	 bool _fueModificado;
	 bool _enCarga;
     CampoNotaFinal * campoNotaFinal;
     CampoDni * campoDNI;
     ListaCampos vCampos;

     std::string convocatoria;
     std::string profesores;
     std::string asignatura;
     std::string revision;
     std::string fecha;
     std::string comentario;

	/// Escribe en el fichero la marca de documento y sus atributos
	void escribeMarcaDocumento(FILE *);

	/// Lee del fichero la marca de documento y sus atributos
	static bool leeMarcaDocumento(FILE *, DocumentoCalifa *);

	void escribeMarcaCampo(FILE *, Campo *);
	static Campo * leeInfoCampo(FILE *, DocumentoCalifa *);
	static void leeFilasCampo(FILE *, Campo *);

	/** Compara dos campos de dos documentos */
	bool comparar(
			Campo * org,
			unsigned int numFilaOrg,
		    Campo * dest,
			unsigned int numFilaDest,
    		bool esAscendente
	);

	/** Inserta ordenadamente una fila de doc en otra de este */
	void insertarOrdenado(
			const DocumentoCalifa &doc,
			unsigned int numCampo,
			unsigned int numFila,
			bool esAscendente
	);
public:
	DocumentoCalifa();
	~DocumentoCalifa();

	/// Eliminar todos los campos del documento, excepto los vitales
	void eliminarCasiTodos();

	/// Eliminar un campo del documento, si no es de los vitales
	bool eliminarCampo(unsigned int);

	/// @return true si el documento fue modificado, false en otro caso
	bool fueModificado() const
		{ return _fueModificado; }
    void forzarFueModificado(bool mdf = true)
        { _fueModificado = mdf; }

    /**
     * Vuelca todo el documento a un fichero en modo de escritura para texto.
     * @param fich
     */
    void  toString(FILE * fich) const;

	/**
	 * Intercambia las posiciones de dos campos en la lista de campos
	*/
	bool intercambiarPosicionesCampos(unsigned int i, unsigned int j)
		{
			if ( i < vCampos.size()
			  && j < vCampos.size() )
			{
				Campo * aux = vCampos[i];
				vCampos[i] = vCampos[j];
				vCampos[j] = aux;

				return true;
			}
			else throw IndiceIncorrectoError( "intercambiando posiciones campos" );

			return false;
		}

	bool mueveCampoAFinal(unsigned int i)
		{
			if ( i < vCampos.size() ) {
				Campo *c = vCampos[ i ];

				vCampos.erase( vCampos.begin() + i );
				vCampos.push_back( c );
			}
			else throw IndiceIncorrectoError( "Moviendo campo al final" );

			return true;
		}

	/// Inserta un campo nuevo antes de "Nota Final"
	void insertaNuevoCampo(Campo *);

	/// Devuelve el número de filas del documento
	unsigned int getNumFilas() const
		{ return ( campoDNI->getNumFilas() ); }

    /**
     * @return una cadena con el contenido de todos los campos en una fila.
     * @param pos La fila concreta.
     */
    std::string toStringFila(unsigned int pos) const;


    /**
     * Obliga a todas las calificaciones para que sean recalculadas.
     */
    void calcula();

	/// Añade una fila a las filas del documento
	void annadeFila();

	/// Insertar una fila
	void insertaFila(unsigned int);

	/// Borra una determinada fila
	/// @param i La fila a borrar
	void borraFila(unsigned int i);

    /**
     * Vuelca en un fichero, en modo de escritura, el documento en formato CSV
     * @param ops Las opciones para generar el formato CSV
     * @param fich
     */
    void toCsv(const OpcionesCsv &ops, FILE * fich) const;


    /**
     * Vuelca toda la información a un archivo en formato HTML
     * @param fich El archivo abierto para escritura.
     */
    void toHtml(FILE *);


    /**
     * Genera un nuevo documento a partir de un archivo CSV
     * @param ops Las opciones que indican cómo fue grabado el CSV
     * @param fich El fichero CSV abierto para lectura de texto
	 * @return Un nuevo DocumentoCalifa con la información del fichero CSV
     */
    static DocumentoCalifa * cnvtDesdeCsv(const OpcionesCsv &ops, FILE * fich);


	/// Devuelve las estadísticas del documento
	std::string getEstadisticas(Campo * = NULL);

    /**
	 * Comprueba que la definición de la estructura de un documento sea
	 * congruente:
	 *		- Debe tener un campo DNI (debe ser el primero) y nota final
	 		- Los pesos de las notas no informativas deben sumar 100%.
     * @return una cadena. Si es vacía, es congruente. En caso contrario,
	 * contiene un mensaje de error explicando el problema
     */
    std::string esCongruente() const;

    /**
     * Devuelve el campo de nota final de este documento
	 * @return el campo de nota final de este documento
     */
	CampoNotaFinal * getCampoNotaFinal() const
		{ return campoNotaFinal; }

    /**
     * @return el campoDNI de este documento.
     */
    CampoDni * getCampoDNI() const
		{ return campoDNI; }

	/**
	 * @return la posición del campo pasado por parámetro
	*/
	unsigned int getPosCampo(Campo *) const;

	/**
		Mueve un campo en una posición a otra
	*/
	void mueveCampo(unsigned int pos1, unsigned int pos2);

	/// @param c El campo a considerar como vital o no para este documento
	/// @return true si es campo vital (DNI o Nota final), false en otro caso
	bool esCampoVital(Campo *c) const
		{ return ( c == getCampoNotaFinal() || c == getCampoDNI() ); }

	/**
     * @return la lista de campos de este documento, no debe modificarse
     */
    const ListaCampos &getListaCampos() const
		{ return vCampos; }

 	/**
     * @return la información sobre la convocatoria
     */
    const std::string &getConvocatoria() const
		{ return convocatoria; }

    /**
		Permite cambiar la información sobre la convocatoria.
     *  @param value La nueva info sobre la convocatoria
     */
    void putConvocatoria(const std::string &value )
		{ convocatoria = value; }

    /**
     * @return La información sobre los profesores
     */
    const std::string &getProfesores () const
		{ return profesores; }

    /**
     * Cambia la información sobre los profesores
     */
    void putProfesores(const std::string &value )
		{ profesores = value; }

    /**
     * @return La información sobre la asignatura
     */
    const std::string &getAsignatura() const
		{ return asignatura; }

    /**
     * Cambia la info sobre la asignatura
		@ param value La nueva info
     */
    void putAsignatura(const std::string &value)
		{ asignatura = value; }

    /**
     * @return la información sobre la revisión
     */
    const std::string &getRevision() const
		{ return revision; }

    /**
     * Cambia la información sobre la revision
     * @param value
     */
    void putRevision(const std::string &value)
		{ revision = value; }

    /**
     * @return la información sobre la fecha de publicación de las notas
     */
    const std::string &getFecha() const
		{ return fecha; }

    /**
     * Cambia la info de la fecha de la publicación.
     */
    void putFecha(const std::string &value)
		{ fecha = value; }

    /**
     *  @return La información de comentarios generales sobre las calificaciones
     */
    const std::string &getComentario() const
		{ return comentario; }

    /**
     * Cambia la info de comentario sobre la convocatoria.
     */
    void putComentario(const std::string &value)
		{ comentario = value; }

	/// Se utiliza para no disparar los cálculos en tiempo de carga
	void ponEnCarga( bool carga = true )
		{ _enCarga = carga; }

    /// Cuando se están introduciendo nuevas columnas no se calculan las notas
	bool enCarga() const
		{ return _enCarga; }

    /// Cargar de un archivo
    /// @see Persistente, DocumentoCalida::recuperar
	static DocumentoCalifa * cargar(const std::string &);

	/// Mezcla dos documentos califa, generando uno nuevo.
	static DocumentoCalifa * mezcla(const DocumentoCalifa &docBase, DocumentoCalifa &docMezcla);

    /// Recuperar y guardar a un archivo en XML
    /// @see Persistente
	DocumentoCalifa * recuperar(std::FILE *);
	void guardar(std::FILE *);

	DocumentoCalifa * copiarEstructura() const
		{ return copiarEstructura( this ); }

    DocumentoCalifa * copiar() const;

    void normalizarNotasParciales()
        { CampoNotaParcial::normalizarNotasParciales( *this ); };

	void copiarFila(
			const DocumentoCalifa &doc,
			unsigned int numFilaOrg,
			unsigned int numFilaDest );

	DocumentoCalifa * ordenar(Campo * campo, bool esAscendente);

	/// Hace que todas las columnas tengan el mismo número de filas
	void normalizarCampos();

	std::auto_ptr<ListaDNIs> chkDNIs();

    /**
        Comprueba si existe el campo (por nombre y tipo) en el documento
        @param nc Nombre del campo
        @return El campo si se encuentra, NULL en caso contrario
    **/
	Campo * existeCampo(const std::string &nc);

	static void convertirCampoNombreApsComaNombre(Campo *);
	static void convertirCampoNombreNombreAps(Campo *);

	static DocumentoCalifa * copiarEstructura(const DocumentoCalifa *);
	static DocumentoCalifa * importarCSV(const std::string &f);

    /**
        Mezcla los campos de dos documentos, generando uno nuevo. Se produce una excepción
        si existen campos con el mismo nombre pero de distinto tipo.
        @param docBase El documento principal
        @param docMezcla El documento a mezclar
        @return El nuevo documento

	**/
	static DocumentoCalifa * mezclar(const DocumentoCalifa &docBase, DocumentoCalifa &docMezcla);


};
#endif //DOCUMENTOCALIFA_H
