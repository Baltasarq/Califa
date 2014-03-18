/************************************************************************
  			documentocalifa.cpp - baltasarq@yahoo.es

	Esta clase representa a un documento de calificaciones por entero, por lo
que forzosamente mantiene una colección de campos.


This file was generated on mar ene 10 2006 at 20:43:09
**************************************************************************/

#include "stringman.h"
#include "nombreman.h"
#include "documentocalifa.h"
#include "camponotaconceptual.h"
#include "campodni.h"
#include "campoinfo.h"
#include "camponota.h"
#include "camponotaextra.h"
#include "campoinfo.h"
#include "campoverif.h"
#include "reservadas.h"
#include "ui.h"

#include <iostream>
#include <fstream>
#include <set>

const std::string DocumentoCalifa::ExtArchivoDatos = ".clf";
const std::string DocumentoCalifa::ArchivoSinNombre = "sin_nombre" + ExtArchivoDatos;
const std::string DocumentoCalifa::NombreDNI = "DNI";
const std::string DocumentoCalifa::NombreNotaFinal = "Nota final";
const std::string DocumentoCalifa::NombreInfoTextual = "Información textual";
const std::string DocumentoCalifa::NombreNotaParcial = "Nota parcial";
const std::string DocumentoCalifa::NombreVerificacion = "Verificación";
const std::string DocumentoCalifa::NombreNotaExtra = "Pts. Extra";
const std::string DocumentoCalifa::NombrePredNotaConceptual = "Nota conceptual";
const std::string DocumentoCalifa::NombrePredObservaciones = "Observaciones";
const std::string DocumentoCalifa::NombrePredPractica = "Práctica";
const std::string DocumentoCalifa::NombrePredPracticaFinal = "Práctica final";
const std::string DocumentoCalifa::NombrePredExamen = "Examen teoría";
const std::string DocumentoCalifa::NombrePredNombre = "Nombre completo";
const std::string DocumentoCalifa::NombrePredNotaExtra = "Participa";

const std::string DocumentoCalifa::EtqDocumento = "DocumentoCalifa";
const std::string DocumentoCalifa::EtqCampo = "Campo";
const std::string DocumentoCalifa::EtqPesoCampo = "Peso";
const std::string DocumentoCalifa::EtqNombreCampo = "NombreCampo";
const std::string DocumentoCalifa::EtqTipoCampo = "TipoCampo";
const std::string DocumentoCalifa::EtqEsInformativo = "EsInformativo";
const std::string DocumentoCalifa::EtqEsNecesarioAprobar = "EsNecesarioAprobar";
const std::string DocumentoCalifa::EtqMostrarPuntuadoSobreDiez="MostrarPuntuacionSobreDiez";
const std::string DocumentoCalifa::EtqNombreAsignatura = "Asignatura";
const std::string DocumentoCalifa::EtqProfesores = "Profesores";
const std::string DocumentoCalifa::EtqConvocatoria = "Convocatoria";
const std::string DocumentoCalifa::EtqFecha = "Fecha";
const std::string DocumentoCalifa::EtqComentario = "Comentario";
const std::string DocumentoCalifa::EtqRevision = "Revision";

// ------------------------------------------ DocumentoCalifa::DocumentoCalifa()
DocumentoCalifa::DocumentoCalifa()
{
	_enCarga = false;
	_fueModificado = false;
	campoNotaFinal = new(std::nothrow) CampoNotaFinal( this );
	campoDNI = new(std::nothrow) CampoDni( this );

	if ( campoDNI != NULL
 	  && campoNotaFinal != NULL )
	{
	    campoDNI->nombre = NombreDNI;
        campoNotaFinal->nombre = NombreNotaFinal;
		vCampos.push_back( campoDNI );
		vCampos.push_back( campoNotaFinal );
	}
	else throw SinMemoriaError( "Creando documento de calificaciones" );
}

void DocumentoCalifa::insertaNuevoCampo(Campo *c)
{
	c->perteneceA = this;

	if ( dynamic_cast<CampoDni *>( c ) != NULL ) {
		throw InconsistenciaError( "No puede haber más de un DNI" );
	}

	if ( dynamic_cast<CampoNotaFinal *>( c ) != NULL ) {
		throw InconsistenciaError( "No puede haber más de una nota final" );
	}

	// ¿Es observable?
	if ( ( dynamic_cast<CampoNota *>( c ) != NULL
		|| dynamic_cast<CampoVerif *>( c ) != NULL )
	  && !( c->esInformativo() ) )
	{
		campoNotaFinal->observar( c );
	}

	// ¿Es el de nota conceptual?
	if ( dynamic_cast<CampoNotaConceptual *>( c ) != NULL ) {
		(( CampoNotaConceptual *) c)->observar( campoNotaFinal );
	}

	// Meterlo
	vCampos.insert( vCampos.end(), c );
	_fueModificado = true;
}

DocumentoCalifa::~DocumentoCalifa()
{
	// Liberar los campos del documento
	for(unsigned int i = 0; i < vCampos.size(); ++i) {
		delete vCampos[ i ];
	}
}

unsigned int DocumentoCalifa::getPosCampo(Campo *c) const
/**
	Devuelve la posición de un campo pasado por parámetro,
	o el número de campos +1 si no lo encuentra.
*/
{
	unsigned int i = 0;

	for(; i < vCampos.size(); ++i) {
		if ( vCampos[ i ] == c ) {
			break;
		}
	}

	return i;
}

void DocumentoCalifa::eliminarCasiTodos()
{
	// Liberar los campos del documento que no son vitales
	for(unsigned int i = 0; i < vCampos.size(); ++i) {
		if ( !esCampoVital( vCampos[ i ] ) ) {
			delete vCampos[ i ];
		}
	}

	// Meter los vitales de nuevo
	vCampos.clear();
	vCampos.push_back( getCampoDNI() );
	vCampos.push_back( getCampoNotaFinal() );
	_fueModificado = true;
}

bool DocumentoCalifa::eliminarCampo(unsigned int i)
{
	bool toret = false;

	if ( i < vCampos.size() ) {
	    Campo * c = vCampos[ i ];
		if ( !esCampoVital( c ) ) {
		    // Eliminar observaciones
            if ( ( dynamic_cast<CampoNota *>( c ) != NULL
                || dynamic_cast<CampoVerif *>( c ) != NULL )
            && !( c->esInformativo() ) )
            {
                campoNotaFinal->dejarDeObservar( c );
            }

		    // Eliminar
		    vCampos.erase( vCampos.begin() + i );
		    delete c;
			toret = true;
			_fueModificado = true;
		}
	}

	return toret;
}

// -------------------------------------------------- DocumentoCalifa::calcula()
void DocumentoCalifa::calcula()
/*
	Se recalcula el documento. El campo de nota final hace que se recalculen
	las notas conceptuales, al ser su observador.
*/
{
	unsigned int num = campoNotaFinal->getValores().size();

	for(unsigned int i = 0; i < num; ++i) {
		campoNotaFinal->calcula( i );
	}
}

// ------------------------------------------------- DocumentoCalifa::toString()
std::string DocumentoCalifa::toStringFila(unsigned int pos) const
{
	std::string toret;
	unsigned int num = vCampos.size();

	for(unsigned int j = 0; j < num; ++j) {
		if ( !( vCampos[j]->estaOculta ) ) {
			toret += vCampos[j]->toString( pos ) + '\t';
		}
	}

	return toret;
}

// ------------------------------------------------- DocumentoCalifa::toString()
void DocumentoCalifa::toString(FILE * f) const
{

	if ( f != NULL ) {
		ponInicioProgreso();

		// Poner la cabecera
		for(unsigned int i = 0; i < getListaCampos().size(); ++i) {

			if ( !( getListaCampos()[ i ]->estaOculta ) ) {
				fprintf( f, "%s\t", getListaCampos()[ i ]->nombre.c_str() );
			}
		}
		fprintf( f, "\n\n" );

		// Poner los datos
		for(unsigned int i = 0; i < getNumFilas(); ++i) {
			fprintf( f, "%s\n", toStringFila( i ).c_str() );

			ponProgreso( "Convirtiendo a texto ...", 0, i, getNumFilas() );
		}

		ponFinalProgreso();
	}
	else throw InconsistenciaError( "fichero inválido" );
}

// --------------------------------------------------- DocumentoCalifa::toHtml()
void DocumentoCalifa::toHtml(FILE *f)
{
	if ( f == NULL ) {
		throw InconsistenciaError( "fichero no válido" );
	}

	ponInicioProgreso();

	// Preámbulos
	fprintf( f, "<html>"
				"<meta http-equiv=\"Content-Type\" content=\"text/html; "
				"charset=utf-8\" />"
				"<head><title>%s (%s)</title></head>\n<body>\n",
			    asignatura.c_str(),
				convocatoria.c_str()
	);

	fprintf( f, "\n<!-- Generado por %s (%s) -->\n\n",
			    NombreApp.c_str(),
				VersionApp.c_str()
	);

	// Escribir la cabecera
	fprintf(f, "<div align=\"center\"><p><center>\n<h1>%s</h1>\n</center>\n",
			    asignatura.c_str()
	);
	fprintf(f, "<br><center>\n<h2>%s</h2>\n</center></div>\n",
				convocatoria.c_str()
	);

	// Escribir el documento en sí
	fputs( "<p><table width=100%>", f );

	// Escribir la cabecera de la tabla
	fputs( "<tr bgcolor=\"#BFBFBF\"><td><small>N&uacute;m.</small></td>", f );
	for(unsigned int j = 0; j < vCampos.size(); ++j) {
			if ( !( vCampos[ j ]->estaOculta ) ) {
			 fprintf( f, "<td><b><center>%s</center></b></td>",
						vCampos[ j ]->nombre.c_str()
			 );
			}
		}
	fputs( "</tr>\n", f );

	// Escribir los datos
	for(unsigned int i = 0; i < getNumFilas(); ++i) {

		// Fondo de la línea
		if ( ( i % 2 ) == 0 )
				fputs( "<tr bgcolor=\"#DFDFDF\">", f );
		else 	fputs( "<tr>", f );

		// Número de línea
		fprintf( f, "<td><center><small>%d</small></center></td>\n", i + 1 );

		// Datos
		for(unsigned int j = 0; j < vCampos.size(); ++j) {
			if ( !( vCampos[ j ]->estaOculta ) ) {
				fprintf( f, "%s", ( vCampos[ j ]->toHtml( i ) + '\n' ).c_str() );
			}
		}
		fputs( "</tr>", f );

		ponProgreso( "Convirtiendo a HTML ...", 0, i, getNumFilas() );
	}

	fputs( "</table>", f );

	// Pie de informaciones
	fprintf(f, "<p><b>Profesor(es)</b>: %s\n", profesores.c_str() );
	fprintf(f, "<br><b>Revisi&oacute;n</b>: %s\n", revision.c_str() );
	fprintf(f, "<br><b>Fecha</b>: %s\n", fecha.c_str() );
	fprintf(f, "<br><b>Observaciones</b>: %s\n", comentario.c_str() );

	// Epílogo
	fputs( "\n</body>\n</html>\n", f );

	ponFinalProgreso();
}

// ---------------------------------------------------- DocumentoCalifa::toCsv()
void DocumentoCalifa::toCsv(const OpcionesCsv &ops, FILE *f) const
{
	std::string lineaCsv;
	std::string fmt = "\"%s\"";

	if ( f != NULL ) {
		ponInicioProgreso();

		// Volcar la cabecera
		for(unsigned int j = 0; j < vCampos.size(); ++j) {
			if ( !( vCampos[ j ]->estaOculta ) ) {
				fprintf( f, fmt.c_str(), vCampos[ j ]->nombre.c_str() );

				if ( j < vCampos.size() -1 ) {
					fprintf( f, "%c", ops.chSeparador );
				}
			}
		}
		fprintf( f, "%s", ops.chCambioLinea );

		// Volcar los datos
		for(unsigned int i = 0; i < getNumFilas(); ++i) {

		    lineaCsv.clear();
		    lineaCsv.reserve( vCampos.size() * 4 );
			for(unsigned int j = 0; j < vCampos.size(); ++j) {
				// Escribir
				if ( !( vCampos[ j ]->estaOculta ) ) {
				    // Saltarse los no presentados
				    if ( dynamic_cast<CampoNota *>( vCampos[ j ] ) != NULL ) {
				        double nota = ((CampoNota *) vCampos[ j ])->getValorNumerico( i );

				        if ( ops.excluirNoPresentados
                          && nota < 0 )
                        {
                            lineaCsv.clear();
                            break;
                        }
				    }

					// Obtener la versión CSV del campo
					lineaCsv += vCampos[ j ]->toCsv( i, ops );

					// Ahora el separador
					if ( j < vCampos.size() -1 ) {
						lineaCsv += ops.chSeparador;
					}
				}
			}

            // Escribir lin.
            if ( !lineaCsv.empty() ) {
                fprintf( f, "%s%s", lineaCsv.c_str(), ops.chCambioLinea );
            }

			ponProgreso( "Convirtiendo a CSV ...", 0, i, getNumFilas() );
		}

		ponFinalProgreso();
	} else throw InconsistenciaError( "fichero no válido" );
}

// --------------------------------------------- DocumentoCalifa::esCongruente()
std::string DocumentoCalifa::esCongruente() const
{
	std::string toret;
	unsigned int pesosTotal = 0;
	unsigned int numParciales = 0;

	// ¿Tiene un campo DNI?
	if ( getCampoDNI() == NULL ) {
		toret += "No existe el campo \"DNI\".\n";
	}

	// ¿Es el campo DNI el primero?
	if ( getCampoDNI() != vCampos[0] ) {
		toret += "El campo \"DNI\" no es el primero de todos.\n";
	}

	// ¿Tiene un campo Nota final?
	if ( getCampoNotaFinal() == NULL ) {
		toret += "No existe el campo \"Nota final\".\n";
	}

	// Pesos de las notas
	for(unsigned int i = 0; i < vCampos.size(); ++i) {
		if ( !( vCampos[ i ]->esInformativo() )
		  && dynamic_cast<CampoNotaParcial *>( vCampos[i] ) != NULL )
		{
			pesosTotal += ( (CampoNota *) vCampos[ i ] )->getPeso();
			++numParciales;

			if ( ( (CampoNota *) vCampos[ i ] )->getPeso() == 0 ) {
				toret += '\'' + ( (CampoNota *) vCampos[ i ] )->nombre + '\''
					   + " no puede tener peso cero.\n";
			}
		}
	}

	if ( pesosTotal != CampoNota::MaxPeso
	  && numParciales > 0 )
	{
		toret += "La suma de los pesos de los campos de notas no es "
				+ StringMan::toString( (int) CampoNota::MaxPeso )
				+ "% como debería, sino "
				+ StringMan::toString( (int) pesosTotal )
				+ "%.\n"
		;
	}

	// Todas las columnas tienen el mismo número de filas
	for(unsigned int i = 1; i < vCampos.size(); ++i) {
		if ( vCampos[ i ]->getNumFilas() != getNumFilas() ) {
			toret += "La columna '";
			toret += vCampos[ i ]->nombre;
			toret += "' tiene " + StringMan::toString( vCampos[ i ]->getNumFilas() );
			toret += " filas, y el documento declara " + StringMan::toString( getNumFilas() );
			toret += ".\n";
		}
	}

	return toret;
}

// ----------------------------------------------- DocumentoCalifa::annadeFila()
void DocumentoCalifa::annadeFila()
{
	unsigned int numUltFila;

	// Añadir la fila extra en todos ellos
	for(unsigned int i = 0; i < vCampos.size(); ++i ) {
		vCampos[ i ]->annade();
	}

	// Avisar al observador
	numUltFila = getNumFilas() -1;
	campoNotaFinal->calcula( numUltFila );

	// El DNI en ppio es el nº de fila
	getCampoDNI()->putValor( numUltFila, StringMan::toString( numUltFila ) + "X" );

	// Asegurarse
	_fueModificado = true;
}


// ---------------------------------------------- DocumentoCalifa::insertaFila()
void DocumentoCalifa::insertaFila(unsigned int numFila)
{
	if ( !getCampoDNI()->esFilaCorrecta( numFila ) ) {
		throw IndiceIncorrectoError( "tratando de insertar nueva fila" );
	}

	// Insertar una fila nueva en todos los campos
	for(unsigned int i = 0; i < getListaCampos().size(); ++i) {
		getListaCampos()[ i ]->insertar( numFila );
	}

	// Poner el DNI preseleccionado
	getCampoDNI()->putValor( numFila, StringMan::toString( getNumFilas() +1 ) );
}

// ------------------------------------------------ DocumentoCalifa::borraFila()
void DocumentoCalifa::borraFila(unsigned int numFila)
{
	if ( !getCampoDNI()->esFilaCorrecta( numFila ) ) {
		throw IndiceIncorrectoError( "tratando de borrar fila incorrecta" );
	}

	for(unsigned int i = 0; i < getListaCampos().size(); ++i) {
		getListaCampos()[ i ]->borrar( numFila );
	}
}

Campo * DocumentoCalifa::leeInfoCampo(FILE *f, DocumentoCalifa *doc)
{
	const AtributoXML * atr;
	ListaAtributosXML * lAtrs;
	bool esInformativo      = false;
	bool esNecesarioAprobar = false;
	bool verPuntuadoSobre10 = false;
	unsigned int peso = 0;
	std::string nombreCampo;
	Campo * toret = NULL;

	if ( !leeAperturaMarca( f, EtqCampo ) ) {
		throw InconsistenciaError( "recuperando, se esperaba marca: " + EtqCampo );
	}

	// Repasar los atributos
	lAtrs = &getAtributos();
	for(unsigned int i = 0; i < lAtrs->getNumero(); ++i) {
		atr = &lAtrs->getElemento( i );

		// Tipo del campo
		std::string etq = StringMan::mays( atr->getEtq() );

		if ( etq == StringMan::mays( EtqTipoCampo ) )
		{
			std::string valor = StringMan::mays( atr->getValor() );

			// Tipo de campo CampoNotaConceptual
			if ( valor == StringMan::mays( CampoNotaConceptual::StrDescTipo ) )
			{
				toret = new(std::nothrow) CampoNotaConceptual( doc );

				if ( toret == NULL ) {
					throw SinMemoriaError( "recuperando, sin memoria con: "
										    + atr->getValor()
					);
				} else doc->insertaNuevoCampo( toret );
			}
			else
			// Tipo de campo CampoDni
			if ( valor == StringMan::mays( CampoDni::StrDescTipo ) )
			{
				toret = doc->getCampoDNI();
			}
			else
			// Tipo de campo CampoNotaFinal
			if ( valor == StringMan::mays( CampoNotaFinal::StrDescTipo ) )
			{
				toret = doc->getCampoNotaFinal();
				doc->mueveCampoAFinal(
					doc->getPosCampo( doc->getCampoNotaFinal() )
				);
			}
			else
			// Tipo de campo CampoNotaParcial
			if ( valor == StringMan::mays( CampoNotaParcial::StrDescTipo ) )
			{
				toret = new(std::nothrow) CampoNotaParcial( doc );

				if ( toret == NULL ) {
					throw SinMemoriaError(
							"recuperando, sin memoria con: "
						+ atr->getValor()
					);
				} else doc->insertaNuevoCampo( toret );
			}
			else
			// Tipo de campo CampoInfo
			if ( valor == StringMan::mays( CampoInfo::StrDescTipo ) )
			{
				toret = new(std::nothrow) CampoInfo( doc );

				if ( toret == NULL ) {
					throw SinMemoriaError(
							"recuperando, sin memoria con: " + atr->getValor()
					);
				} else doc->insertaNuevoCampo( toret );
			}
			else
			// Tipo de campo CampoVerif
			if ( valor == StringMan::mays( CampoVerif::StrDescTipo ) )
			{
				toret = new(std::nothrow) CampoVerif( doc );

				if ( toret == NULL ) {
					throw SinMemoriaError(
							"recuperando, sin memoria con: " + atr->getValor()
					);
				} else doc->insertaNuevoCampo( toret );
			}
			else
			// Tipo de campo CampoNotaExtra
			if ( valor == StringMan::mays( CampoNotaExtra::StrDescTipo ) )
			{
				toret = new(std::nothrow) CampoNotaExtra( doc );

				if ( toret == NULL ) {
					throw SinMemoriaError(
							"recuperando, sin memoria con: "
						+ atr->getValor()
					);
				} else doc->insertaNuevoCampo( toret );
			}
		}

		// Nombre del campo
		if ( etq == StringMan::mays( EtqNombreCampo ) ) {
			nombreCampo = atr->getValor();
		}

		// Peso del campo
		if ( etq == StringMan::mays( EtqPesoCampo ) ) {
			peso = StringMan::toIntNum( atr->getValor() );
		}

		// ¿Es informativo?
		if ( etq == StringMan::mays( EtqEsInformativo ) ) {
			esInformativo = StringMan::toIntNum( atr->getValor() );
		}

		// ¿Es necesario aprobar?
		if ( etq == StringMan::mays( EtqEsNecesarioAprobar ) ) {
			esNecesarioAprobar =
							StringMan::toIntNum( atr->getValor() );
		}

		// ¿Puntuación sobre 10?
		if ( etq == StringMan::mays( EtqMostrarPuntuadoSobreDiez ) ) {
			verPuntuadoSobre10 = StringMan::toIntNum( atr->getValor() );
		}
	}

	// Opciones del campo
	if ( toret != NULL ) {
		toret->nombre = nombreCampo;
		toret->putEsInformativo( esInformativo );
		CampoNotaParcial * notaParcial;

		if ( ( notaParcial = dynamic_cast<CampoNotaParcial*>( toret ) ) != NULL ) {
			notaParcial->putEsNecesarioAprobar( esNecesarioAprobar );
			notaParcial->putEsPuntuacionSobreDiez( verPuntuadoSobre10 );
			notaParcial->putPeso( peso );
		}
	}
	else throw InconsistenciaError( "recuperando, se esperaba: " + EtqTipoCampo );

	return toret;
}

// -------------------------------------------- DocumentoCalifa::leeFilasCampo()
void DocumentoCalifa::leeFilasCampo(FILE * f, Campo *c)
{
	int ch;
	std::string fila;

	// Leer todas las filas del campo
	do {
		// Leer el contenido de la fila
		pasaEsp( f );
		ch = std::fgetc( f );
		fila.clear();

		if ( ch == DelimContenidoFilasCampos ) {
			fila = leeLiteral( f, DelimContenidoFilasCampos );
		} else throw InconsistenciaError( "se esperaba fila de '"
										+ c->nombre
										+ "' con " + DelimContenidoFilasCampos
			   );

		// Pasar las comillas de cierre
		pasaEsp( f );
		ch = std::fgetc( f );
		if ( ch != DelimContenidoFilasCampos ) {
				throw InconsistenciaError( "se esperaba fila de '"
										+ c->nombre
										+ "' con " + DelimContenidoFilasCampos
			   );
		}

		// Guardar
		c->annade();
		c->putValor( c->getNumFilas() - 1, fila );

		// Pasar la coma (si existe, si no, salir)
		pasaEsp( f );
		ch = std::fgetc( f );
		if ( ch != SeparadorFilasCampos ) {
			fseek( f, -1, SEEK_CUR );
			break;
		}
	} while ( true );

	return;
}

// ---------------------------------------- DocumentoCalifa::normalizarCampos()
void DocumentoCalifa::normalizarCampos()
{
    for(unsigned int i = 0; i < this->getListaCampos().size(); ++i) {
		this->getListaCampos()[ i ]->normalizarNumFilas();
	}
}

// ------------------------------------------------ DocumentoCalifa::recuperar()
DocumentoCalifa * DocumentoCalifa::recuperar(FILE *f)
{
	std::string sigMarca;
	std::string errores;
	DocumentoCalifa *doc = NULL;
	Campo * c;
	long int pos;
	long int tamArchivo;

	// Buscar el tamaño del archivo
	pos = ftell( f );
	fseek( f, 0, SEEK_END );
	tamArchivo = ftell( f );
	fseek( f, pos, SEEK_END );

	// Leer la cabecera
	if ( leerCabecera( f ) ) {
		if ( leeMarcaDocumento( f, this ) ) {
			// Crear el documento
			doc = new(std::nothrow) DocumentoCalifa();

			if ( doc == NULL ) {
				throw SinMemoriaError( "recuperando, creando documento" );
			}

			doc->ponEnCarga();

			// Cargar los campos
			sigMarca = getSigMarca( f );
			StringMan::maysCnvt( StringMan::trimCnvt( sigMarca ) );

			ponInicioProgreso();

			while( sigMarca != StringMan::mays( EtqDocumento ) ) {
				ponProgreso( "Recuperando ...", 0, ftell( f ), tamArchivo );

				if ( sigMarca == StringMan::mays( EtqCampo ) ) {
					c = leeInfoCampo( f, doc );

					// Leer la info del campo, si no es especial
					if ( dynamic_cast<CampoNotaFinal *>( c ) == NULL
					  && dynamic_cast<CampoNotaConceptual *>( c ) == NULL )
					{
						// Leer la info del campo
						if ( getSigMarca( f ).empty() ) {
							leeFilasCampo( f, c );
						}
					}

					if ( !leeCierreMarca( f, EtqCampo ) ) {
						throw InconsistenciaError(
								"recuperando, se esperaba: /" + EtqCampo
						);
					}
				}
				else throw InconsistenciaError(
								"marca no reconocida: " + sigMarca
						);

				// Leer la sig. marca
				sigMarca = getSigMarca( f );
				StringMan::maysCnvt( StringMan::trimCnvt( sigMarca ) );
			}

			if ( !leeCierreMarca( f, EtqDocumento ) ) {
				throw InconsistenciaError(
							"recuperando, se esperaba: /" + EtqDocumento
				);
			}
		} else throw InconsistenciaError(
						"recuperando, se esperaba: " + EtqDocumento
			   );
	} else throw InconsistenciaError( "recuperando: se esperaba cab. XML" );

	// Normalizar los campos
	doc->normalizarCampos();

	// Comprobar la congruencia
	errores = doc->esCongruente();
	if ( !errores.empty() ) {
		delete doc;
		doc = NULL;
		throw InconsistenciaError( "En documento cargado:\n" + errores );
	}

	// Cargar los datos
	doc->putAsignatura( asignatura );
	doc->putProfesores( profesores );
	doc->putRevision( revision );
	doc->putConvocatoria( convocatoria );
	doc->putFecha( fecha );
	doc->putComentario( comentario );

	doc->ponEnCarga( false );
	ponFinalProgreso();
	doc->_fueModificado = false;
	return doc;
}

// ------------------------------------ DocumentoCalifa::escribeMarcaDocumento()
void DocumentoCalifa::escribeMarcaDocumento(FILE *f)
{
	getAtributos().reset();

	// Llenar los atributos de la marca de documento
	if ( !asignatura.empty() ) {
		getAtributos().carga( AtributoXML( EtqNombreAsignatura, asignatura ) );
	}

	if ( !profesores.empty() ) {
		getAtributos().carga( AtributoXML( EtqProfesores, profesores ) );
	}

	if ( !convocatoria.empty() ) {
		getAtributos().carga( AtributoXML( EtqConvocatoria, convocatoria ) );
	}

	if ( !fecha.empty() ) {
		getAtributos().carga( AtributoXML( EtqFecha, fecha ) );
	}

	if ( !comentario.empty() ) {
		getAtributos().carga( AtributoXML( EtqComentario, comentario ) );
	}

	if ( !revision.empty() ) {
		getAtributos().carga( AtributoXML( EtqRevision, revision ) );
	}

	// Escribir la marca de apertura, finalmente
	escribeAperturaMarca( f, EtqDocumento );
}

// ---------------------------------------- DocumentoCalifa::leeMarcaDocumento()
bool DocumentoCalifa::leeMarcaDocumento(FILE *f, DocumentoCalifa * doc)
{
	std::string etq;
	bool toret = true;

	// Leer la marca
	if ( leeAperturaMarca( f, EtqDocumento ) ) {

		// Desgranar los atributos
		for(unsigned int i = 0; i < getAtributos().getNumero(); ++i) {
			etq = StringMan::mays( getAtributos().getElemento( i ).getEtq() );

			if ( etq == StringMan::mays( EtqNombreAsignatura ) )
			{
				doc->asignatura = getAtributos().getElemento( i ).getValor();
			}
			else
			if ( etq == StringMan::mays( EtqProfesores ) )
			{
				doc->profesores = getAtributos().getElemento( i ).getValor();
			}
			else
			if ( etq == StringMan::mays( EtqConvocatoria ) )
			{
				doc->convocatoria = getAtributos().getElemento( i ).getValor();
			}
			else
			if ( etq == StringMan::mays( EtqComentario ) )
			{
				doc->comentario = getAtributos().getElemento( i ).getValor();
			}
			else
			if ( etq == StringMan::mays( EtqFecha ) )
			{
				doc->fecha = getAtributos().getElemento( i ).getValor();
			}
			else
			if ( etq == StringMan::mays( EtqRevision ) )
			{
				doc->revision = getAtributos().getElemento( i ).getValor();
			}
		}
	} else toret = false;

	return toret;
}

void DocumentoCalifa::escribeMarcaCampo(FILE *f, Campo *c)
/**
	Escribe toda la info del campo en marca de apertura
*/
{
	if ( c != NULL ) {
		// Meter el atributo del nombre
		getAtributos().carga(
			AtributoXML( EtqNombreCampo, c->nombre )
		);

		// Meter el atributo del tipo del campo
		getAtributos().carga(
			AtributoXML( EtqTipoCampo, c->getDescTipo() )
		);

		// ¿Es informativo?
		getAtributos().carga(
			AtributoXML( EtqEsInformativo, c->esInformativo() ? "1" : "0" )
		);

		if ( dynamic_cast<CampoNotaParcial*>( c ) != NULL ) {
			// ¿Es necesario aprobar?
			getAtributos().carga(
				AtributoXML( EtqEsNecesarioAprobar,
					( (CampoNotaParcial*) c)->esNecesarioAprobar() ? "1" : "0" )
			);

			// ¿El peso de la nota?
			getAtributos().carga(
				AtributoXML( EtqPesoCampo,
					StringMan::toString( ( (CampoNotaParcial*) c)->getPeso() ) )
			);

			// ¿Puntuado sobre 10?
			getAtributos().carga(
				AtributoXML( EtqMostrarPuntuadoSobreDiez,
				 ( (CampoNotaParcial*) c)->esPuntuacionSobreDiez() ? "1" : "0" )
			);
		}

		// Guardar la marca
		escribeAperturaMarca( f, EtqCampo );
	}

}

// -------------------------------------------------- DocumentoCalifa::guardar()
void DocumentoCalifa::guardar(FILE *f)
/**
	Crea un archivo XML que permite persistencia
*/
{
	Campo *c;

	if ( f == NULL ) {
		throw InconsistenciaError( "archivo no abierto" );
	}

	escribirCabecera( f );
	escribeMarcaDocumento( f );

	ponInicioProgreso();

	for(unsigned int numCampo = 0; numCampo < getListaCampos().size(); ++numCampo )
	{
		ponProgreso( "Guardando ...", 0, numCampo, getListaCampos().size() );

		c = getListaCampos()[ numCampo ];

		// ¿Es uno de los campos especiales?
		if ( dynamic_cast<CampoNotaFinal *>( c ) != NULL
		  || dynamic_cast<CampoNotaConceptual *>( c ) != NULL )
		{
			getAtributos().carga( AtributoXML( EtqNombreCampo, c->nombre ) );
			getAtributos().carga( AtributoXML( EtqTipoCampo, c->getDescTipo() ) );
			escribeAperturaMarca( f, EtqCampo );
			escribeCierreMarca( f, EtqCampo );
			continue;
		}

		// Marca de campo con toda la info
		escribeMarcaCampo( f, c );

		for(unsigned int numFila = 0; numFila < getNumFilas(); ++numFila ) {
			// Escribir el contenido del campo
			fprintf( f, "%c", DelimContenidoFilasCampos );
			fputs( getListaCampos()[numCampo]->getValor( numFila ).c_str(), f );
			fprintf( f, "%c", DelimContenidoFilasCampos );

			// Poner la coma final (o no)
			if ( numFila < ( getNumFilas() -1 ) )
					fprintf( f, "%c\n", SeparadorFilasCampos );
			else 	fputs( "\n", f );
		}

		escribeCierreMarca( f, EtqCampo );
	}

	escribeCierreMarca( f, EtqDocumento );
	ponFinalProgreso();
	_fueModificado = false;

	return;
}

// --------------------------------------------------- DocumentoCalifa::cargar()
DocumentoCalifa * DocumentoCalifa::cargar(const std::string &nomArchivo)
{
	DocumentoCalifa * toret = NULL;
	DocumentoCalifa proxy;
	FILE * f = fopen( nomArchivo.c_str(), "rt" );

	if ( f != NULL )
			toret = proxy.recuperar( f );
	else 	throw InconsistenciaError( "archivo no abierto" );

	return toret;
}

// ------------------------------------------ DocumentoCalifa::getEstadisticas()
std::string DocumentoCalifa::getEstadisticas(Campo *cmp)
/// Calcular estadísticas
/// @param cmp El campo del que calcular las estadísticas (debe ser estudiable)
/// @return Una cadena con información textual de las estadístias
{
	Estudiable *cmpEstudiable;
	std::string toret;

	ponInicioProgreso();

	if ( ( cmpEstudiable = dynamic_cast<Estudiable *>( cmp ) ) == NULL ) {
		cmpEstudiable = getCampoNotaFinal();
	}

	toret = "\nAsignatura: " + getAsignatura();
	toret += "\nConvocatoria: " + getConvocatoria();
	toret += "\nFecha: " + getFecha();
	toret += "\nNotas: " + cmp->nombre;
	toret += "\n\n\n" ;

	toret += cmpEstudiable->getEstadisticas();

	ponFinalProgreso();

	return toret;
}

// --------------------------------------------------- DocumentoCalifa::copiar()
DocumentoCalifa * DocumentoCalifa::copiarEstructura(const DocumentoCalifa *doc)
{
	DocumentoCalifa * toret = NULL;
	Campo * campo = NULL;

	try {
		toret = new DocumentoCalifa();

		// Pasar los datos
		toret->putAsignatura( doc->getAsignatura() );
		toret->putProfesores( doc->getProfesores() );
		toret->putRevision( doc->getRevision() );
		toret->putConvocatoria( doc->getConvocatoria() );
		toret->putFecha( doc->getFecha() );
		toret->putComentario( doc->getComentario() );

        // Pasar las filas
		for(unsigned int i = 0; i < doc->getListaCampos().size(); ++i) {
			campo = doc->getListaCampos()[ i ];

			if ( !doc->esCampoVital( campo ) ) {
				campo = campo->copiar();
				campo->borrarTodo();

				if ( campo != NULL )
						toret->insertaNuevoCampo( campo );
				else 	throw SinMemoriaError( "copiando campo para documento copia" );
			}
		}

		// Colocar el campo de la nota en la posición adecuada
		toret->mueveCampo(
			toret->getPosCampo( toret->getCampoNotaFinal() ),
			doc->getPosCampo( doc->getCampoNotaFinal() )
		);
	}
	catch(const Error &)
	{
		throw;
	}


	catch(const std::bad_alloc &) {
		throw SinMemoriaError( "creando copia de documento" );
	}
	catch(...) {
		throw InternoError( "FATAL: creando copia de documento" );
	}

	return toret;
}

// ----------------------------------------------- DocumentoCalifa::mueveCampo()
void DocumentoCalifa::mueveCampo(unsigned int pos1, unsigned int pos2)
{
	if ( pos1 < vCampos.size()
	  && pos2 < vCampos.size() )
	{
		Campo * cmp = vCampos[ pos1 ];
		vCampos.erase( vCampos.begin() + pos1 );

		if ( pos2 < getListaCampos().size() )
				vCampos.insert( vCampos.begin() + pos2, cmp );
		else 	vCampos.push_back( cmp );
	}
	else throw IndiceIncorrectoError( "indexando en campos al mover" );
}

// ----------------------------------------- DocumentoCalifa::insertarOrdenado()
void DocumentoCalifa::insertarOrdenado(
							const DocumentoCalifa &doc,
							unsigned int numCampo,
							unsigned int numFila,
							bool esAscendente)
{
	unsigned int i = 0;
	Campo *cmpOrg;
	Campo *cmpDest;

	// Buscar el campo destino
	if ( numCampo < vCampos.size() )
			cmpDest = vCampos[ numCampo ];
	else	throw IndiceIncorrectoError( "indexando en campos al insertar" );


	// Buscar el campo origen
	if ( numCampo < doc.getListaCampos().size() )
			cmpOrg = doc.getListaCampos()[ numCampo ];
	else	throw IndiceIncorrectoError( "indexando en campos al insertar" );

	// Buscar la fila de destino correcta
	for(; i < getNumFilas(); ++i) {
		if ( comparar( cmpOrg, numFila, cmpDest, i, esAscendente ) ) {
			break;
		}
	}

	copiarFila( doc, numFila, i );
}

// ------------------------------------------------- DocumentoCalifa::comparar()
bool DocumentoCalifa::comparar(
	Campo * org,
	unsigned int numFilaOrg,
    Campo * dest,
	unsigned int numFilaDest,
    bool esAscendente)
{
	bool toret = false;

	// Comprobar
	if ( org->getDescTipo() != dest->getDescTipo() ) {
		throw InconsistenciaError( "al comparar '"
		                         + org->nombre
		                         + "' y '"
		                         + dest->nombre + '\'' );
	}

	// Comparar en caso de ser notas
	if ( dynamic_cast<CampoNota *>( org ) != NULL ) {
		double nota1 = ((CampoNota *) org)->getValorNumerico( numFilaOrg );
		double nota2 = ((CampoNota *) dest)->getValorNumerico( numFilaDest );

		if ( esAscendente )
				toret = ( nota1 < nota2 );
		else	toret = ( nota1 > nota2 );
	}
	else {
		// Comparar en caso de ser cadenas
		std::string str1 = StringMan::mays( org->getValor( numFilaOrg ) );
		std::string str2 = StringMan::mays( dest->getValor( numFilaDest ) );

		if ( esAscendente )
				toret = ( str1.compare( str2 ) < 0 );
		else	toret = ( str1.compare( str2 ) >= 0 );
	}

	return toret;
}

// -------------------------------------------------- DocumentoCalifa::ordenar()
DocumentoCalifa * DocumentoCalifa::ordenar(Campo * campo, bool esAscendente)
{
	DocumentoCalifa * toret = copiarEstructura();
	unsigned int numCampo = getPosCampo( campo );

	toret->ponEnCarga();

	for(unsigned int i = 0; i < getNumFilas(); ++i) {
			toret->insertarOrdenado( *this, numCampo, i, esAscendente );
	}

	toret->ponEnCarga( false );

	// Comprobar la congruencia
	std::string errores = toret->esCongruente();
	if ( !errores.empty() ) {
		delete toret;
		toret = NULL;
		throw InconsistenciaError( "En documento ordenado:\n" + errores );
	}

	return toret;
}

// ----------------------------------------------- DocumentoCalifa::copiarFila()
void DocumentoCalifa::copiarFila(
			const DocumentoCalifa &doc,
			unsigned int numFilaOrg,
			unsigned int numFilaDest )
/**
	Copia la fila numFilaOrg del documento doc en la fila numFilaDest,
	que se inserta previamente.
*/
{
	// Comprobar
	if ( getNumFilas() > 0
	  && numFilaDest > getNumFilas() )
	{
		throw IndiceIncorrectoError( "indice demasiado grande ("
					+ StringMan::toString( numFilaDest ) + "/"
					+ StringMan::toString( getNumFilas() )
					+ "), copiando nueva fila"
		);
	}

	// Crear primero el "hueco"
	if ( numFilaDest >= getNumFilas() )
			annadeFila();
	else 	insertaFila( numFilaDest );

	// Ahora sí, copiar
	for(unsigned int i = 0; i < vCampos.size(); ++i) {
		vCampos[ i ]->putValor(
						numFilaDest,
						doc.getListaCampos()[ i ]->getValor( numFilaOrg )
		);
	}
}

// ---------------------------------------------- DocumentoCalifa::importarCSV()
DocumentoCalifa * DocumentoCalifa::importarCSV(const std::string &nomArchivo)
{
	std::string lin;
	DocumentoCalifa * toret = NULL;
	std::ifstream f( nomArchivo.c_str() );

	if ( f.is_open() ) {
/*		try {
			// Preparar el nuevo documento
			toret = new DocumentoCalifa();
			CampoInfo * nombre = new CampoInfo( toret );
			nombre->nombre = "nombre";
			toret->insertarNuevoCampo( nombre );

			// Leer el archivo CSV
			std::getline( f, lin );
			while( !f.eof() ) {
				StringMan::trimCnvt( lin );
				procesarLineaCSV( toret, lin );

				std::getline( f, lin );
			}

			fclose( f );
		} catch(...) {
			fclose( f );
			delete toret;
			toret = NULL;
		}
		 */
	}

	return toret;
}

// ----------------------------------------- convertirCampoNombreApsComaNombre()
void DocumentoCalifa::convertirCampoNombreApsComaNombre(Campo *c)
{
	std::string partes[3];

	if ( dynamic_cast<CampoInfo *>( c ) == NULL ) {
		throw InternoError( c->nombre + " no es textual" );
	}

	ponInicioProgreso();
	for(unsigned int i = 0; i < c->getNumFilas(); ++i) {
		ponProgreso( "Convirtiendo ...", 0, i, c->getNumFilas() );
		std::string nombre = c->getValor( i );

		// Si hay una coma, ya fue cambiado
		if ( nombre.rfind( ',' ) != std::string::npos ) {
			continue;
		}

		NombreMan::descomponerNombre( nombre, partes );
		nombre = partes[ 1 ] + ' ' + partes[ 0 ] + ',' + ' ' + partes[ 2 ];
		c->putValor( i, nombre );
	}

	ponFinalProgreso();
}

// --------------------------------------------- convertirCampoNombreNombreAps()
void DocumentoCalifa::convertirCampoNombreNombreAps(Campo *c)
{
	unsigned int posComa;

	if ( dynamic_cast<CampoInfo *>( c ) == NULL ) {
		throw InternoError( c->nombre + " no es textual" );
	}

	ponInicioProgreso();
	for(unsigned int i = 0; i < c->getNumFilas(); ++i) {
		ponProgreso( "Convirtiendo ...", 0, i, c->getNumFilas() );
		std::string nombre = c->getValor( i );
		posComa = nombre.rfind( ',' );

		// Si no hay una coma, ya fue cambiado
		if ( posComa == std::string::npos ) {
			continue;
		}

		nombre = nombre.substr( posComa + 1 ) + ' ' + nombre.substr( 0, posComa );
		c->putValor( i, StringMan::trimCnvt( nombre ) );
	}

	ponFinalProgreso();
}

// ------------------------------------------------------------------ chkDNIs()
std::auto_ptr<DocumentoCalifa::ListaDNIs> DocumentoCalifa::chkDNIs()
{
    const unsigned int NumFilas = getNumFilas();
    std::auto_ptr<ListaDNIs> toret( new ListaDNIs );

    for(unsigned int i = 0; i < NumFilas; ++i) {
        unsigned int j = getCampoDNI()->buscar(
                                getCampoDNI()->getValor( i ),
                                i + 1
        );

        if ( j < NumFilas
          && i != j)
        {
            toret->first.push_back( i );
            toret->second.push_back( j );
        }
    }

    return toret;
}

// ------------------------------------------------------------------ mezclar()
Campo * DocumentoCalifa::existeCampo(const std::string &nc)
{
    Campo * toret = NULL;
    std::string nombreCampo = StringMan::trim( nc );
    StringMan::minsCnvt( nombreCampo );

    for(unsigned int i = 0; i < this->vCampos.size(); ++i) {
        Campo * c = vCampos[ i ];
        if ( nombreCampo ==  StringMan::mins( StringMan::trimCnvt( c->nombre ) ) ) {
            toret = c;
        }
    }

    return toret;
}

// ------------------------------------------------------------------- copiar()
DocumentoCalifa * DocumentoCalifa::copiar() const
{
    DocumentoCalifa * toret = this->copiarEstructura();

    ponInicioProgreso();
    for(unsigned int i = 0; i < this->getNumFilas(); ++i) {
        ponProgreso( "Copiando filas...", 0, i, this->getNumFilas() );
        toret->copiarFila( *this, i, i );
    }
    ponFinalProgreso();

    return toret;
}

// ------------------------------------------------------------------ mezclar()
DocumentoCalifa * DocumentoCalifa::mezclar(const DocumentoCalifa &docBase, DocumentoCalifa &docMezcla)
{
    DocumentoCalifa * toret = NULL;

    try {
    // Conjunto para marcar campos nuevos
    std::set<Campo *> camposNuevos;

    // Crear el nuevo documento
    toret = docBase.copiar();
    toret->ponEnCarga();
    const DocumentoCalifa::ListaCampos &camposDocMezcla = docMezcla.getListaCampos();
    unsigned int posDest = toret->getPosCampo( toret->getCampoNotaFinal() );

    // Revisar los campos del otro
    ponInicioProgreso();
    for(unsigned int i = 0; i < camposDocMezcla.size(); ++i) {
        ponProgreso( "Revisando campos", 0, i, camposDocMezcla.size() );
        Campo * c = camposDocMezcla[ i ];

        if ( !docMezcla.esCampoVital( c ) ) {
            Campo * nuevoCampo = NULL;
            Campo * campoBase = toret->existeCampo( c->nombre );

            if ( campoBase == NULL ) {
                // Crear y preparar
                toret->insertaNuevoCampo( nuevoCampo = c->copiar() );
                toret->mueveCampo( toret->getPosCampo( nuevoCampo ), posDest );
                nuevoCampo->borrarTodo();
                nuevoCampo->normalizarNumFilas();
                camposNuevos.insert( nuevoCampo );
            } else {
                if ( campoBase->getDescTipo() != c->getDescTipo() ) {
                    throw InconsistenciaError(
                            "Existen dos campos con mismo nombre y distinto tipo: "
                            + campoBase->nombre
                    );
                }
            }
        }
    }
    ponFinalProgreso();

    // Copiar las filas del docMezclar
    CampoDni * campoDniToret = toret->getCampoDNI();
    CampoDni * campoDniMezcla = docMezcla.getCampoDNI();
    unsigned int numFilasTotal = docMezcla.getNumFilas();
    bool esNuevaFila;
    ponInicioProgreso();
    for(unsigned int numFila = 0; numFila < numFilasTotal; ++numFila) {
        ponProgreso( "Mezclando...", 0, numFila, numFilasTotal );

        // Buscar la fila en el documento final
        unsigned int filaDest = campoDniToret->buscar( campoDniMezcla->getValor( numFila ) );
        esNuevaFila = false;

        if ( filaDest >= toret->getNumFilas() ) {
            filaDest = toret->getNumFilas();
            toret->annadeFila();
            esNuevaFila = true;
        }

        // Copiar cada columna
        for(unsigned int numCampo = 0; numCampo < camposDocMezcla.size(); ++numCampo) {
            Campo * c = camposDocMezcla[ numCampo ];
            Campo * campoBase = toret->existeCampo( c->nombre );

            if ( campoBase == NULL ) {
                throw InternoError( "campo no encontrado copiando filas" );
            }

            // Si es un campo nuevo, copiar el contenido
            if ( esNuevaFila
              || ( !esNuevaFila
                && camposNuevos.find( campoBase ) != camposNuevos.end() ) )
            {
                campoBase->putValor( filaDest, c->getValor( numFila ) );
            }
        }

        toret->normalizarCampos();
        toret->normalizarNotasParciales();
        toret->ponEnCarga( false );
        ponFinalProgreso();
    }
    }
    catch(const std::bad_alloc &e)
    {
        throw SinMemoriaError( "mezclando documentos" );
    }
    catch(const Error &e) {
        throw;
    }
    catch(const std::exception &e)
    {
        throw InternoError( e.what() );
    }
    catch(...)
    {
        throw InternoError( "ERROR inesperado mezclando documentos" );
    }

    return toret;
}
