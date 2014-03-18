// generated 2006/1/9 13:12:41 CET by baltasarq
// using glademm V2.6.0
//
// Dlg de propiedades de un proyecto califa

#include "config.h"
#include "dlgpropiedades.h"
#include "gtk_uintf.h"
#include "campoinfo.h"
#include "camponota.h"
#include "campoverif.h"
#include "camponotaconceptual.h"
#include "camponotaextra.h"

#include <vector>

DlgPropiedades::DlgPropiedades(Gtk::Window &parent, DocumentoCalifa *doc)
	: DlgPropiedades_glade( parent ), tablaSeleccionada( NULL ), documento( doc )
{
	Gtk::TreeModel::Row filaColumnas;

    this->get_default_size( ancho, alto );
	this->set_size_request( ancho, alto );

	// Llenar la lista de campos-tipo
	Glib::RefPtr<Gtk::ListStore> refModeloCamposTipo =
								Gtk::ListStore::create( modeloColumnaSimple )
	;

	tablaColumnasTipo->set_model( refModeloCamposTipo );
	tablaColumnasTipo->append_column( "Columnas tipo", modeloColumnaSimple.datos );

	filaColumnas = *( refModeloCamposTipo->append() );
	filaColumnas[ modeloColumnaSimple.datos ] = DocumentoCalifa::NombreInfoTextual;
	filaColumnas = *( refModeloCamposTipo->append() );
	filaColumnas[ modeloColumnaSimple.datos ] = DocumentoCalifa::NombreNotaParcial;
	filaColumnas = *( refModeloCamposTipo->append() );
	filaColumnas[ modeloColumnaSimple.datos ] = DocumentoCalifa::NombreVerificacion;
	filaColumnas = *( refModeloCamposTipo->append() );
	filaColumnas[ modeloColumnaSimple.datos ] = DocumentoCalifa::NombreNotaExtra;

	tablaColumnas->scroll_to_point( 0, 0 );

	// Llenar la lista de campos predefinidos
	Glib::RefPtr<Gtk::ListStore> refModeloCamposPred =
								Gtk::ListStore::create( modeloColumnaSimple )
	;
	tablaColumnasPred->set_model( refModeloCamposPred );
	tablaColumnasPred->append_column( "Columnas predefinidas",
									  modeloColumnaSimple.datos )
	;

	filaColumnas = *( refModeloCamposPred->append() );
	filaColumnas[ modeloColumnaSimple.datos ] = DocumentoCalifa::NombrePredNotaConceptual;
	filaColumnas = *( refModeloCamposPred->append() );
	filaColumnas[ modeloColumnaSimple.datos ] = DocumentoCalifa::NombrePredObservaciones;
	filaColumnas = *( refModeloCamposPred->append() );
	filaColumnas[ modeloColumnaSimple.datos ] = DocumentoCalifa::NombrePredPractica;
	filaColumnas = *( refModeloCamposPred->append() );
	filaColumnas[ modeloColumnaSimple.datos ] = DocumentoCalifa::NombrePredPracticaFinal;
	filaColumnas = *( refModeloCamposPred->append() );
	filaColumnas[ modeloColumnaSimple.datos ] = DocumentoCalifa::NombrePredExamen;
	filaColumnas = *( refModeloCamposPred->append() );
	filaColumnas[ modeloColumnaSimple.datos ] = DocumentoCalifa::NombrePredNombre;
	filaColumnas = *( refModeloCamposPred->append() );
	filaColumnas[ modeloColumnaSimple.datos ] = DocumentoCalifa::NombrePredNotaExtra;

	// La lista de campos reales que tendrá el documento
	refModeloCampos = Gtk::ListStore::create( modeloColumnaSimple );
	tablaColumnas->set_model( refModeloCampos );
	tablaColumnas->remove_all_columns();
	tablaColumnas->append_column( "Columnas existentes", modeloColumnaSimple.datos );

	// Finalmente, cargar la info complementaria
	editAsignatura->set_text( doc->getAsignatura() );
	editProfesores->set_text( doc->getProfesores() );
	editFecha->set_text( doc->getFecha() );
	editConvocatoria->set_text( doc->getConvocatoria() );
	editComentario->set_text( doc->getComentario() );
	editRevision->set_text( doc->getRevision() );

	actualizaListadoCampos();
}

void DlgPropiedades::actualizaListadoCampos()
{
	Gtk::TreeModel::Row filaColumnas;

	// Llenar la lista de campos existentes
	refModeloCampos->clear();
	for(unsigned int i = 0; i < documento->getListaCampos().size(); ++i) {
		filaColumnas = *( refModeloCampos->append() );
		filaColumnas[ modeloColumnaSimple.datos ] =
				documento->getListaCampos()[ i ]->nombre
		;
	}

	tablaColumnas->scroll_to_point( 0, 0 );
	desactivarPropiedades();
}

void DlgPropiedades::on_botAyuda_clicked()
{
	ponMsgInfo( *this, "Introduzca las columnas" );
}

void DlgPropiedades::on_botCerrar_clicked()
{
    // Pasar los datos
    documento->putAsignatura( editAsignatura->get_text() );
    documento->putProfesores( editProfesores->get_text() );
    documento->putRevision( editRevision->get_text() );
    documento->putConvocatoria( editConvocatoria->get_text() );
    documento->putFecha( editFecha->get_text() );
    documento->putComentario( editComentario->get_text() );

	// Comprobar si hay errores
	std::string errores = documento->esCongruente();

	if ( !errores.empty() ) {
		ponMsgError( *this,
					"<b>Errores en formato de documento:</b>\n\n"
					+ errores
					+ "\n\n<i>Deberá solucionar estos problemas antes de poder "
					"proceder a editar el documento</i>."

		);

		response( Gtk::RESPONSE_NONE );
	}

	return;
}

int DlgPropiedades::getOpcion(Gtk::TreeView * tr)
/* Pasándole un treeView, devuelve la opción seleccionada si la hay, o
   un -1 en otro caso */
{
	int toret = -1;

	if ( tr != NULL ) {
		Glib::RefPtr<Gtk::TreeSelection> selected = tr->get_selection();
		std::vector<Gtk::TreeModel::Path> selectedRows =
												selected->get_selected_rows();

		if ( selected->count_selected_rows() > 0 ) {
			std::vector<Gtk::TreeModel::Path>::const_iterator it =
				selectedRows.begin()
			;
			toret = *( (*it).begin() );
		}
	}

	return toret;
}

void DlgPropiedades::setOpcion(Gtk::TreeView *tr, unsigned int numOpcion)
{
    Gtk::TreeModel::Row row = tr->get_model()->children()[ numOpcion ];
    Glib::RefPtr<Gtk::TreeSelection> selected = tr->get_selection();

    if( row ) {
      selected->select( row );
    }
}

void DlgPropiedades::insertarColumnaPred()
{
	Campo *c = NULL;
	CampoNotaParcial * n;

	// Obtener la fila seleccionada
	int op = getOpcion( tablaSeleccionada );

	if ( op >= 0 ) {
	    // Crear el campo adecuado
		if ( op == 0 ) {
			c = new(std::nothrow) CampoNotaConceptual( documento );
			c->nombre = DocumentoCalifa::NombrePredNotaConceptual;
		}
		else
		if ( op == 1 ) {
			c = new(std::nothrow) CampoInfo( documento );
			c->nombre = DocumentoCalifa::NombrePredObservaciones;
		}
		else
		if ( op == 2 ) {
			c = new(std::nothrow) CampoNotaParcial( documento );
			c->nombre = DocumentoCalifa::NombrePredPractica;
		}
		else
		if ( op == 3 ) {
			c = new(std::nothrow) CampoNotaParcial( documento );
			c->nombre = DocumentoCalifa::NombrePredPracticaFinal;
		}
		else
		if ( op == 4 ) {
			c = new(std::nothrow) CampoNotaParcial( documento );
			c->nombre = DocumentoCalifa::NombrePredExamen;
		}
		else
		if ( op == 5 ) {
			c = new(std::nothrow) CampoInfo( documento );
			c->nombre = DocumentoCalifa::NombrePredNombre;
		}
		else
		if ( op == 6 ) {
			c = new(std::nothrow) CampoNotaExtra( documento );
			c->nombre = DocumentoCalifa::NombrePredNotaExtra;
		}
		else {
			ponMsgError( *this, "ERROR Interno, opción no existente" );
			goto FIN;
		}

		if ( c != NULL ) {
			documento->insertaNuevoCampo( c );
			c->normalizarNumFilas();

			if ( ( n = dynamic_cast<CampoNotaParcial *>( c ) ) != NULL )
            {
                n->putEsPuntuacionSobreDiez();
                documento->normalizarNotasParciales();
            }
		}
		else ponMsgError( *this, "Sin memoria, creando campos" );

	} else ponMsgError( *this, "Debe seleccionar una opción de alguna lista" );

	FIN:
	return;
}

void DlgPropiedades::insertarColumnaTipo()
{
	Campo *c = NULL;
	CampoNotaParcial * n;

	// Obtener la fila seleccionada
	int op = getOpcion( tablaSeleccionada );

	if ( op >= 0 ) {
	    // Crear el campo adecuado
		if ( op == 0 ) {
			c = new(std::nothrow) CampoInfo( documento );
			c->nombre = "Info";
		}
		else
		if ( op == 1 ) {
			c = new(std::nothrow) CampoNotaParcial( documento );
			c->nombre = "Nota";
		}
		else
		if ( op == 2 ) {
			c = new(std::nothrow) CampoVerif( documento );
			c->nombre = "Comprobar";
		}
		else
		if ( op == 3 ) {
			c = new(std::nothrow) CampoNotaExtra( documento );
			c->nombre = "Nota extra";
		}
		else {
			ponMsgError( "ERROR Interno: opción no existente" );
			goto FIN;
		}

		if ( c != NULL ) {
			documento->insertaNuevoCampo( c );
			c->normalizarNumFilas();

			if ( ( n = dynamic_cast<CampoNotaParcial *>( c ) ) != NULL )
            {
                n->putEsPuntuacionSobreDiez();
                documento->normalizarNotasParciales();
            }
		}
		else ponMsgError( *this, "Sin memoria, creando campos" );
	} else ponMsgError( *this, "Debe seleccionar una opción de alguna lista" );

	FIN:
	return;
}

void DlgPropiedades::on_botMasCols_clicked()
// Gestor del evento que se dispara cuando se pulsa el botón del +
{
	if ( tablaSeleccionada == tablaColumnasTipo ) {
		insertarColumnaTipo();
		actualizaListadoCampos();
	}
	else
	if ( tablaSeleccionada == tablaColumnasPred ) {
		insertarColumnaPred();
		actualizaListadoCampos();
	}
	else ponMsgError( *this, "Debe seleccionar una opción de alguna lista" );
}

void DlgPropiedades::on_tablaColumnasPred_cursor_changed()
// Al seleccionar uno de los elementos, indicar la última tabla
{
	tablaSeleccionada = tablaColumnasPred;
}

void DlgPropiedades::on_tablaColumnasTipo_cursor_changed()
// Al seleccionar uno de los elementos, indicar la última tabla
{
	tablaSeleccionada = tablaColumnasTipo;
}

void DlgPropiedades::on_tablaColumnas_cursor_changed()
// Al seleccionar uno de los elementos, indicar la última tabla
{
	activarPropiedades();
}

void DlgPropiedades::on_botEsInformativo_toggled()
{
	int numCampo = getOpcion( tablaColumnas );

	if ( numCampo >= 0 ) {
		Campo * c = documento->getListaCampos()[ numCampo ];

		c->putEsInformativo( botEsInformativo->get_active() );
	}
	else {
		botEsInformativo->set_sensitive( false );
		botEsInformativo->set_active( false );
	}
}

void DlgPropiedades::on_botPuntuarSobre10_toggled()
{
	int numCampo = getOpcion( tablaColumnas );
	CampoNotaParcial * campo;

	if ( numCampo >= 0 ) {
		Campo * c = documento->getListaCampos()[ numCampo ];

		if ( dynamic_cast<CampoNotaParcial *>( c ) != NULL ) {
			campo = (CampoNotaParcial *) c;

			campo->putEsPuntuacionSobreDiez( botPuntuarSobre10->get_active() );
		}
		else {
			botPuntuarSobre10->set_sensitive( false );
			botPuntuarSobre10->set_active( false );
		}

	} else {
		botPuntuarSobre10->set_sensitive( false );
		botPuntuarSobre10->set_active( false );
	}
}

void DlgPropiedades::on_botEsNecesarioAprobar_toggled()
{
	int numCampo = getOpcion( tablaColumnas );

	if ( numCampo >= 0 ) {
		Campo * c = documento->getListaCampos()[ numCampo ];

		if ( dynamic_cast<CampoNotaParcial *>( c ) != NULL ) {
			( (CampoNotaParcial *) c )->putEsNecesarioAprobar(
					botEsNecesarioAprobar->get_active() )
			;
		}
		else {
			botEsNecesarioAprobar->set_sensitive( false );
			botEsNecesarioAprobar->set_active( false );
		}

	} else {
		botEsNecesarioAprobar->set_sensitive( false );
		botEsNecesarioAprobar->set_active( false );
	}
}

void DlgPropiedades::on_editPorcentaje_changed()
// Se activa cuando el porcentaje del campo cambia
{
    try {
		unsigned int peso = (unsigned int) editPorcentaje->get_value();
		int numCampo = getOpcion( tablaColumnas );

		if ( numCampo >= 0
		  && ( (unsigned int) numCampo ) < documento->getListaCampos().size() )
		{
			Campo * cmp = documento->getListaCampos()[ numCampo ];
            CampoNotaParcial * c;

			if ( ( c = dynamic_cast<CampoNotaParcial *>( cmp ) ) != NULL ) {
			    c->putEsPuntuacionSobreDiez();
                botPuntuarSobre10->set_active( true );
				c->putPeso( peso );

				if ( !editPorcentaje->is_sensitive() ) {
					activarPropiedades();
				}
			}
		}
		else desactivarPropiedades();
    }
    catch(...) {
        showError( *this, "Error inesperado. Tratando de normalizar..." );
        on_botNormalizar_clicked();
    }
}

void DlgPropiedades::activarPropiedades()
{
	botEsInformativo->set_sensitive();
	editValor->set_sensitive();
	botBorrarCol->set_sensitive();
	botArriba->set_sensitive();
	botAbajo->set_sensitive();

	// Meter la info
	int numCampo = getOpcion( tablaColumnas );
	if ( numCampo >= 0 ) {
		Campo * c = documento->getListaCampos()[ numCampo ];

		botEsInformativo->set_active( c->esInformativo() );
		editValor->set_text( c->nombre );

		if ( dynamic_cast<CampoNotaParcial *>( c ) ) {
			editPorcentaje->set_sensitive();
			editPorcentaje->set_value( ( (CampoNotaParcial *) c)->getPeso() );
			botPuntuarSobre10->set_sensitive();
			botPuntuarSobre10->set_active(
						( (CampoNotaParcial *) c )->esPuntuacionSobreDiez()
			);
			botEsNecesarioAprobar->set_sensitive();
			botEsNecesarioAprobar->set_active(
						( (CampoNotaParcial *) c )->esNecesarioAprobar()
			);
		}
		else {
			editPorcentaje->set_sensitive( false );
			editPorcentaje->set_value( 0 );
			botPuntuarSobre10->set_sensitive( false );
			botPuntuarSobre10->set_active( false );
			botEsNecesarioAprobar->set_active( false );
			botEsNecesarioAprobar->set_sensitive( false );
		}
	}
}

void DlgPropiedades::desactivarPropiedades()
{
	editPorcentaje->set_sensitive( false );
	botEsInformativo->set_sensitive( false );
	editValor->set_sensitive( false );
	botPuntuarSobre10->set_sensitive( false );
	botEsNecesarioAprobar->set_sensitive( false );

	botEsInformativo->set_active( false );
	editValor->set_text( "" );
	botPuntuarSobre10->set_active( false );
	botEsNecesarioAprobar->set_active( false );

	botBorrarCol->set_sensitive( false );
	botArriba->set_sensitive( false );
	botAbajo->set_sensitive( false );
}

void DlgPropiedades::on_editValor_changed()
// Cambiar este campo supone cambiar el nombre de la columna
{
	int numCampo = getOpcion( tablaColumnas );

	if ( numCampo >= 0 ) {
		Campo * c = documento->getListaCampos()[ numCampo ];

		// Meterlo
		c->nombre = editValor->get_text();

		// Actualizar la fila en cuestión
		Gtk::TreeIter it = refModeloCampos->children()[ numCampo ];
  		( *it )->set_value( 0, editValor->get_text() );
	}
}

void DlgPropiedades::on_botDetalles_clicked()
{
	if ( !( tablaDatos->get_visible() ) ) {
		ancho = this->get_width();
		alto = this->get_height();
		etqDetalles->set_text( "Ocultar detalles" );
		tablaDatos->show_all();
	} else {
		etqDetalles->set_text( "Ver detalles" );
		this->resize( ancho, alto );
		tablaDatos->hide();
	}
}

void DlgPropiedades::on_botNormalizar_clicked()
/// Encontrar todas las notas parciales, y normalizarlas
{
	documento->normalizarNotasParciales();
	actualizaListadoCampos();
	desactivarPropiedades();
}

void DlgPropiedades::on_botBorrarCol_clicked()
/// El gestor del botón borrar, para eliminar un campo
{
	int numCampo = getOpcion( tablaColumnas );

	if ( numCampo >= 0 ) {
        if ( askYesNo( *this,
               "Borrar columna",
               Glib::ustring( "¿Esta seguro?" ),
               "Todo el contenido (filas) de la columna va a ser eliminado" ) )
        {
            if ( documento->eliminarCampo( numCampo ) ) {
                actualizaListadoCampos();
                desactivarPropiedades();
            }
            else ponMsgError( *this, "Lo siento, se trata de un campo vital" );
        }
	}
	else ponMsgError( *this, "Debe seleccionar un campo primero" );
}

void DlgPropiedades::on_botLimpiar_clicked()
/// El gestor del botón limpiar, para eliminar casi todos los campos
{
	if ( preguntaSiNo( *this,
			"Eliminar todos los campos",
			"¿Desea eliminar todos los campos?",
			"Todos los campos del documento serán eliminados, a excepción de "
		    "los mínimos. La información guardada en las filas de esos campos no "
	        "podrá ser recuperada."
	   ) )
	{
		documento->eliminarCasiTodos();
		actualizaListadoCampos();
	}
}

void DlgPropiedades::on_botArriba_clicked()
/// Gestor para el botón abajo (pasar un campo a la pos. superior)
{
	int numCampo = getOpcion( tablaColumnas );

	if ( numCampo >= 0 ) {
		if ( numCampo >= 1 ) {
			documento->intercambiarPosicionesCampos( numCampo, numCampo - 1 );
			actualizaListadoCampos();
			setOpcion( tablaColumnas, numCampo - 1 );
			activarPropiedades();
		}
	}
	else ponMsgError( *this, "Debe seleccionar un campo primero" );
}

void DlgPropiedades::on_botAbajo_clicked()
/// Gestor para el botón abajo (pasar un campo a la pos. inferior)
{
	int numCampo = getOpcion( tablaColumnas );

	if ( numCampo >= 0 ) {
		if ( ((unsigned int) numCampo)  < documento->getListaCampos().size() - 1 ) {
			documento->intercambiarPosicionesCampos( numCampo, numCampo + 1 );
			actualizaListadoCampos();
            setOpcion( tablaColumnas, numCampo + 1 );
			activarPropiedades();
		}
	}
	else ponMsgError( *this, "Debe seleccionar un campo primero" );
}

Gtk::ResponseType DlgPropiedades::run()
{
    Gtk::ResponseType toret;

    do {
        toret = (Gtk::ResponseType) Dialog::run();

        if ( toret == Gtk::RESPONSE_DELETE_EVENT ) {
            response( toret = Gtk::RESPONSE_CLOSE );
            on_botCerrar_clicked();
            toret = this->get_response();
        }
    }
    while( toret != Gtk::RESPONSE_CLOSE );

    return toret;
}

void DlgPropiedades::on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
{
    on_botMasCols_clicked();
}
