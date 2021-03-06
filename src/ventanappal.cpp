// generated 2006/1/9 12:38:31 CET by baltasarq@pcjgarcia
// using glademm V2.6.0

#include <gtkmm/main.h>
#include <gtkmm/treeviewcolumn.h>
#include <gtkmm/cellrenderertext.h>
#include <sigc++/sigc++.h>
#include "config.h"

#include "ventanappal.h"
#include "dlgpropiedades.h"
#include "reservadas.h"
#include "gtk_uintf.h"
#include "stringman.h"
#include "fileman.h"
#include "ui.h"
#include "gtk_visor.h"
#include "gtk_uintf.h"
#include "camponotaconceptual.h"
#include "importar.h"
#include "califaicon.h"

// =========================================================== ColumnasDocumento
// ------------------------------------- ColumnasDocumento::~ColumnasDocumento()
ColumnasDocumento::~ColumnasDocumento()
{
	delete[] cols;
}


// ------------------------------------------ ColumnasDocumento::crearColumnas()
ColumnasDocumento::ColumnasDocumento(unsigned int nc) : numCols( nc )
/// Crea el número de columnas especificado, tipo std::string
/// @param el número de columnas necesarias
{
	// Crear las columnas
	cols = new(std::nothrow) Gtk::TreeModelColumn<Glib::ustring>[ numCols ];

	// Añadirlas
	if ( cols != NULL ) {
	    add( indx );
		for(unsigned int i = 0; i < numCols; ++i) {
			add( cols[ i ] );
		}
	} else throw SinMemoriaError( "creando columnas de vista" );
}

// ================================================================= VentanaPpal
const std::string VentanaPpal::MsgPreparado = "Preparado ...";
const std::string VentanaPpal::MsgOcupado = "Trabajando ...";
const std::string VentanaPpal::NoHayDoc = "No existe un documento abierto";
const std::string VentanaPpal::TitulosColumnasFijas[] = { "Ord.", "Prom." };

// -------------------------------------------------- VentanaPpal::VentanaPpal()
VentanaPpal::VentanaPpal() : colsDoc( NULL ), documentoActual( NULL )
{
	Gtk::MenuItem *add;
	Gtk::MenuItem *ins;
	Gtk::MenuItem *del;
	Gtk::MenuItem *fill;
	Gtk::MenuItem *search;
	Gtk::MenuItem *prefs;
	Gtk::Image *imageIns
		= Gtk::manage(new class Gtk::Image(
				Gtk::StockID("gtk-jump-to"),
				Gtk::IconSize( Gtk::ICON_SIZE_MENU ))
	);
	Gtk::Image *imageFill
		= Gtk::manage(new class Gtk::Image(
				Gtk::StockID("gtk-edit"),
				Gtk::IconSize( Gtk::ICON_SIZE_MENU ))
	);

    // Icono
    Glib::RefPtr<Gdk::Pixbuf> iconoCalifa = Gdk::Pixbuf::create_from_xpm_data( califa_icon );
    this->set_icon( iconoCalifa );

	// Inicializar
	campoUltimaBusqueda = NULL;
	ultimaBusqueda = Glib::ustring();
	linUltimaBusqueda = -1;
	uiDesactiva();
	preparaBarraEstado();

	// Prepara el menú contextual
	// Opciones
	cntxt = Gtk::manage( new Gtk::Menu() );
	cntxt->items().push_back( Gtk::Menu_Helpers::StockMenuElem( Gtk::StockID( "gtk-add" ) ) );
    add = (Gtk::ImageMenuItem *)&cntxt->items().back();

	imageIns->show();
    cntxt->items().push_back( Gtk::Menu_Helpers::ImageMenuElem("Insertar", *imageIns));
    ins = (Gtk::ImageMenuItem *)&cntxt->items().back();

	cntxt->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-delete")));
    del = (Gtk::ImageMenuItem *)&cntxt->items().back();

	cntxt->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-find")));
    search = (Gtk::ImageMenuItem *)&cntxt->items().back();

	imageFill->show();
 	cntxt->items().push_back(Gtk::Menu_Helpers::ImageMenuElem("Rellenar ...", *imageFill));
	fill = (Gtk::ImageMenuItem *)&cntxt->items().back();

	cntxt->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-properties")));
    prefs = (Gtk::ImageMenuItem *)&cntxt->items().back();

	// Enlazar con las señales a los métodos ya existentes
    add->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal::on_a__adir1_activate), false);
	ins->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal::on_insertar_en_medio_activate), false);
	del->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal::on_borrar1_activate), false);
	search->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal::on_buscar1_activate), false);
	fill->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal::on_rellenar_activate), false);
	prefs->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal::on_propiedades1_activate), false);

	// Prepararse para lanzarlo cuando se pulse el mouse
	tablaCalifas->signal_button_press_event().connect_notify(
		sigc::mem_fun(*this, &VentanaPpal::on_botMouse), false
	);
}

VentanaPpal::~VentanaPpal()
{
	tablaCalifas->remove_all_columns();
	delete colsDoc;
}

// -------------------------------------------------- VentanaPpal::on_botMouse()
void VentanaPpal::on_botMouse(GdkEventButton* event)
/**
   Está enlazado con el TreeView.
   Comprobar si es el bot derecho, para visualizar el menú contextual.
*/
{
	if ( event->type == GDK_BUTTON_PRESS
	  && event->button == 3
	  && documentoActual != NULL )
	{
		cntxt->popup( event->button, event->time );
	}
}

// ----------------------------------------------------- VentanaPpal::uiActiva()
void VentanaPpal::uiActiva()
/// Activa todos los menúes y botones excepto "nuevo" y "abrir"
{
	tablaCalifas->set_sensitive( true );

	botBarraGuardar->set_sensitive( true );
	botBarraBuscar->set_sensitive( true );
	botBarraAscendente->set_sensitive( true );
	botBarraDescendente->set_sensitive( true );
	botBarraInsertar->set_sensitive( true );
	botBarraInsertarEnMedio->set_sensitive( true );
	botBarraBorrar->set_sensitive( true );
	botBarraPropiedades->set_sensitive( true );
	botBarraConvertir->set_sensitive( true );

	opGuardar->set_sensitive( true );
	opGuardarComo->set_sensitive( true );
	opConvertir->set_sensitive( true );
	opCerrar->set_sensitive( true );
	opMezclar->set_sensitive( true );
	menuHerramientas->set_sensitive( true );

	// Habilitar los miembros del menú Editar
	Glib::ListHandle<Widget *> subMenus = menuEditar->get_children();
	Glib::ListHandle<Widget *>::const_iterator it = subMenus.begin();

	while( it != subMenus.end() ) {
		(*it)->set_sensitive( true );

		++it;
	}

	// Habilitar los miembros del menú Herramientas
	Glib::ListHandle<Widget *> subMenusH = menuHerramientas->get_children();
	Glib::ListHandle<Widget *>::const_iterator itH = subMenusH.begin();

	while( itH != subMenusH.end() ) {
		(*itH)->set_sensitive( true );

		++itH;
	}
}

// -------------------------------------------------- VentanaPpal::uiDesactiva()
void VentanaPpal::uiDesactiva()
/// Desactiva todos los menús y botones
/*
Botones
=======
botBarraGuardar
botBarraBuscar
botBarraAscendente
botBarraDescendente
botBarraInsertar
botBarraBorrar
botBarraPropiedades

Menús
======
opGuardar
opGuardarComo
opConvertir
opCerrar
opMezclar
menuEditar
menuHerramientaserramientas
*/
{
	tablaCalifas->set_sensitive( false );

	botBarraGuardar->set_sensitive( false );
	botBarraBuscar->set_sensitive( false );
	botBarraAscendente->set_sensitive( false );
	botBarraDescendente->set_sensitive( false );
	botBarraInsertar->set_sensitive( false );
	botBarraInsertarEnMedio->set_sensitive( false );
	botBarraBorrar->set_sensitive( false );
	botBarraPropiedades->set_sensitive( false );
	botBarraConvertir->set_sensitive( false );

	opGuardar->set_sensitive( false );
	opGuardarComo->set_sensitive( false );
	opConvertir->set_sensitive( false );
	opCerrar->set_sensitive( false );
	opMezclar->set_sensitive( false );

	// Deshabilitar los miembros del menú Editar
	Glib::ListHandle<Widget *> subMenusEd = menuEditar->get_children();
	Glib::ListHandle<Widget *>::const_iterator itEd = subMenusEd.begin();

	while( itEd != subMenusEd.end() ) {
		(*itEd)->set_sensitive( false );

		++itEd;
	}

	// Habilitar los miembros del menú Herramientas
	Glib::ListHandle<Widget *> subMenusH = menuHerramientas->get_children();
	Glib::ListHandle<Widget *>::const_iterator itH = subMenusH.begin();

	while( itH != subMenusH.end() ) {
		(*itH)->set_sensitive( false );

		++itH;
	}
}

// --------------------------------- VentanaPpal::cambiarNombreDocumentoActual()
void VentanaPpal::cambiarNombreDocumentoActual(const std::string &nuevoNombre)
{
	std::string nombreTitulo;

    // Recordar el nombre del documento actual con extensión .clf
    nombreDocumentoActual =
        FileMan::replaceExt( nuevoNombre, DocumentoCalifa::ExtArchivoDatos )
    ;

	// Preparar el título de la aplicación
	if ( documentoActual != NULL ) {
		nombreTitulo += ' ';
		nombreTitulo += '[';
		nombreTitulo += ' ';

		if ( nuevoNombre.empty() )
		{
			nombreTitulo += DocumentoCalifa::ArchivoSinNombre;
			nombreDocumentoActual = DocumentoCalifa::ArchivoSinNombre;
		}
		else {
			if ( nombreDocumentoActual.size() < 30 ) {
					nombreTitulo += nombreDocumentoActual;
			}
			else {
				nombreTitulo += "...";
				nombreTitulo += nombreDocumentoActual.substr(
									nombreDocumentoActual.size() - 30,
									30
				);
			}
		}

		nombreTitulo += ' ';
		nombreTitulo += ']';
	}

	set_title( NombreApp + nombreTitulo );
}

// --------------------------------------- VentanaPpal::guardarDocumentoActual()
void VentanaPpal::guardarDocumentoActual(bool preguntar)
{
	FILE *f;

	if ( documentoActual != NULL ) {
	 if ( documentoActual->fueModificado() ) {
		// Preguntar si quiere guardar el archivo
		if ( preguntar ) {
			if ( !preguntaSiNo( *this, "Guardar ",
						       "¿Guardar el documento actual?",
							   "guardar: '" + nombreDocumentoActual + '\'')
			   )
			{
				goto end;
			}
		}

		// Preguntar el nombre del documento si no existe
		if ( nombreDocumentoActual.empty()
		  || nombreDocumentoActual == DocumentoCalifa::ArchivoSinNombre )
		{
			std::string nombreArchivo;

			do {
				nombreArchivo = pideNombreArchivoGuardar( *this,
										"Guardar documento de calificaciones",
										"",
									    DocumentoCalifa::ArchivoSinNombre,
										"*" + DocumentoCalifa::ExtArchivoDatos
				);

				if ( nombreArchivo.empty() ) {
					goto end;
				}

				f = fopen( nombreArchivo.c_str(), "r" );
				if ( f != NULL ) {
					if ( !preguntaSiNo( *this, "El archivo ya existe",
								   "¿Desea sobreescribir el archivo?",
								   "guardar: '" + nombreArchivo + '\'' ) )
					{
						nombreArchivo.clear();
					}

					fclose( f );
				}
			} while( nombreArchivo.empty() );

			cambiarNombreDocumentoActual( nombreArchivo );
		}

		// Guardarlo
		FILE * f = fopen( nombreDocumentoActual.c_str(), "wt" );

		if ( f != NULL ) {
			try {
				documentoActual->guardar( f );
			}
			catch(const Error &e) {
				ponMsgError( *this, e.toString() );
			}
			catch(...) {
				ponMsgError( *this, "ERROR inesperado al guardar" );
			}

			fclose( f );
		}
		else {
			ponMsgError( *this, "No fue posible crear: " + nombreDocumentoActual );
			cambiarNombreDocumentoActual( DocumentoCalifa::ArchivoSinNombre );
		}
	 }
	} else ponMsgError( *this, NoHayDoc );

	end:
	return;
}

// ------------------------------------------- VentanaPpal::on_nuevo1_activate()
void VentanaPpal::on_nuevo1_activate()
/// Crear un nuevo documento
{
	// Guardar el documento actual
	if ( documentoActual != NULL ) {

		if ( !preguntaSiNo( *this,
			"¿Está seguro de querer crear un nuevo documento?",
			"¿Desea cerrar el documento actual y crear uno nuevo?",
			"Si elige \"Sí\", y no ha guardado el documento actual, tendrá"
		    " oportunidad de hacerlo antes de que éste sea cerrado."
			) )
		{
			goto end;
		}

		guardarDocumentoActual( NoRequierePreguntar );
		delete documentoActual;
		documentoActual = NULL;
	}

	// Crear el nuevo
	documentoActual = new(std::nothrow) DocumentoCalifa();
	cambiarNombreDocumentoActual();

	// Abrir sus propiedades
	if ( documentoActual != NULL ) {
		uiActiva();
		on_propiedades1_activate();
		documentoActual->forzarFueModificado();
	}
	else {
		ponMsgError( *this, "Sin memoria creando nuevo documento" );
	}

	end:
	return;
}

// ------------------------------------------- VentanaPpal::on_abrir1_activate()
void VentanaPpal::on_abrir1_activate()
/// Abrir un nuevo documento
{
	std::string nuevoArchivo;

	// Guardar el documento actual
	if ( documentoActual != NULL ) {

		if ( !preguntaSiNo( *this,
			"¿Está seguro de querer abrir un documento?",
			"¿Desea cerrar el documento actual y abrir uno nuevo?",
			"Si elige \"Sí\", y no ha guardado el documento actual, tendrá"
		    " oportunidad de hacerlo antes de que éste sea cerrado."
			) )
		{
			goto end;
		}

		guardarDocumentoActual( RequierePreguntar );
	}

	// Crear el nuevo
	nuevoArchivo = pideNombreArchivoAbrir( *this,
							"Abrir documento de calificaciones ...",
							"",
							getNombreDocumentoActual(),
							"*" + DocumentoCalifa::ExtArchivoDatos
	);

	if ( !( nuevoArchivo.empty() ) ) {
		abrir( nuevoArchivo );
	}

	end:
	return;
}

void VentanaPpal::abrir(const string &nuevoArchivo)
{
	try {
		try {
			documentoActual = DocumentoCalifa::cargar( nuevoArchivo );
			prepararVistaColumnasDocumento();
			uiActiva();
		}
		catch(const Error &e) {
			ponMsgError( *this, e.toString() );
			throw;
		}

		cambiarNombreDocumentoActual( nuevoArchivo );

		if ( documentoActual == NULL ) {
			ponMsgError( *this,  "Abriendo documento '" + nuevoArchivo + '\'' );
		}
	} catch(...) {
		ponFinalProgreso();
		uiDesactiva();
	}
}

// ----------------------------------------- VentanaPpal::on_opGuardar_activate()
void VentanaPpal::on_opGuardar_activate()
/// Guardar el documento
{
	if ( documentoActual != NULL ) {
		guardarDocumentoActual( NoRequierePreguntar );
	}
	else ponMsgError( *this, NoHayDoc );
}

// ------------------------------------ VentanaPpal::on_opGuardarComo_activate()
void VentanaPpal::on_opGuardarComo_activate()
/// Guardar el documento existente con otro nombre
{
	if ( documentoActual != NULL ) {
		// Pedir el nuevo nombre
		std::string nuevoNombre = pideNombreArchivoGuardar( *this,
								"Guardar documento de calificaciones como ...",
								"",
								nombreDocumentoActual,
								"*" + DocumentoCalifa::ExtArchivoDatos
		);

		if ( !nuevoNombre.empty() ) {
			// Cambiarlo
			cambiarNombreDocumentoActual( nuevoNombre );

			// Guardarlo
			documentoActual->forzarFueModificado();
			guardarDocumentoActual( NoRequierePreguntar );
		}
	}
	else ponMsgError( *this, NoHayDoc );
}

// ---------------------------------------- VentanaPpal::on_importar1_activate()
void VentanaPpal::on_importar1_activate()
/// Convertir desde CSV(DNI, nombre)
{
    // Obtener un nombre de archivo
    std::string nombreArchivo = pideNombreArchivoAbrir(
                                    *this,
                                    "Abrir archivo para importar",
                                    "",
                                    "",
                                    "*.txt"
    );

    // Importar el archivo y prepararlo como nuevo
    if ( !nombreArchivo.empty() ) {
        Importar importador( nombreArchivo );

        // Guardar lo que haya hecho ahora
        if ( documentoActual != NULL ) {
            on_opCerrar_activate();
        }

        if ( importador.importa() ) {
            documentoActual = importador.getDocumento();
            prepararVistaColumnasDocumento();
            cambiarNombreDocumentoActual();
            uiActiva();
        } else ponMsgError( *this, "No pudo importarse el archivo" );
    }
}

// --------------------------------------- VentanaPpal::on_opConvertir_activate()
void VentanaPpal::on_opConvertir_activate()
{
	Gtk::ResponseType resp;
	std::string nomFich;

	if ( documentoActual != NULL ) {
	    this->set_sensitive( false );

		// Dar las opciones de conversión posibles
		DlgConvertir dlgCnvt( *this, nombreDocumentoActual, documentoActual );

        do {
            resp = (Gtk::ResponseType) dlgCnvt.run();

            dlgCnvt.hide();
            actualizaIntf();

            // Ahora sí, convertir
            if ( resp == Gtk::RESPONSE_OK ) {
                nomFich = dlgCnvt.edNombreArchivo->get_text();
                dlgCnvt.pasarSeleccionADoc();

                if ( !nomFich.empty() ) {
                    FILE * f = fopen( nomFich.c_str(), "wt" );

                    if ( f != NULL ) {
                        if ( dlgCnvt.listaConversion->get_active_text()
                                                          == DlgConvertir::CnvtCSV )
                        {
                            convertirCSV( dlgCnvt, f);
                        }
                        else
                        if ( dlgCnvt.listaConversion->get_active_text()
                                                          == DlgConvertir::CnvtHTML )
                        {
                            convertirHTML( dlgCnvt, f);
                        }
                        else
                        if ( dlgCnvt.listaConversion->get_active_text()
                                                          == DlgConvertir::CnvtTXT )
                        {
                            convertirTXT( dlgCnvt, f);
                        }
                        else ponMsgError( *this, "ERROR interno: conversión no soportada" );

                        fclose( f );
                        ponMsgInfo( *this, "Archivo generado: '" + nomFich + "'" );
                    } else ponMsgError( *this, "No se pudo crear: " + nomFich );
                } else ponMsgError( *this, "No se puede crear un archivo sin nombre" );
            }
        } while( resp == Gtk::RESPONSE_OK
              || resp == Gtk::RESPONSE_NONE );

        this->set_sensitive( true );
	} else ponMsgError( *this, NoHayDoc );

	return;
}

// ------------------------------------------------- VentanaPpal::convertirCSV()
void VentanaPpal::convertirCSV(const DlgConvertir &dlg, FILE *f)
{
	OpcionesCsv ops;

	ops.chSeparador = dlg.getSeparadorCampos();
	ops.chDecimal = dlg.getSeparadorDecimal();
	ops.esDNISinLetra = dlg.botDNISinLetra->get_active();
	ops.excluirNoPresentados = dlg.botSaltarNoPresentados->get_active();

	documentoActual->toCsv( ops, f );
}

// ------------------------------------------------ VentanaPpal::convertirHTML()
void VentanaPpal::convertirHTML(const DlgConvertir &dlg, FILE *f)
{
	documentoActual->toHtml( f );
}

// ------------------------------------------------- VentanaPpal::convertirTXT()
void VentanaPpal::convertirTXT(const DlgConvertir &dlg, FILE *f)
{
	documentoActual->toString( f );
}

// -------------------------------------------- VentanaPpal::delete_event_impl()
bool VentanaPpal::on_delete_event(GdkEventAny *)
/// Es llamado cuando se cierra la ventana
/// @return true si se mantiene la ventana, false si se cierra
{
	bool toret = preguntaSiNo( *this,
			"Salir de la aplicación",
			"¿Está seguro de que desea salir?",
			getDocumentoActual() != NULL ?
				"Tendrá oportunidad de guardar el documento si no lo ha hecho ya"
				: "Abandonar " + NombreApp
	);

	if ( toret ) {
		if ( getDocumentoActual() != NULL ) {
			guardarDocumentoActual( RequierePreguntar );

			delete documentoActual;
		}

		Gtk::Main::quit();
	}


	return !toret;
}

// ------------------------------------------- VentanaPpal::on_salir1_activate()
void VentanaPpal::on_salir1_activate()
{
	on_delete_event( NULL );
}

// ------------------------------------------ VentanaPpal::on_borrar1_activate()
void VentanaPpal::on_borrar1_activate()
{
	unsigned int numFila;

	try {
		if ( documentoActual != NULL ) {
            if ( askYesNo( *this,
                       "Borrar fila",
                       Glib::ustring( "¿Esta seguro?" ),
                       "Todo el contenido (columnas) de la fila va a ser eliminado" ) )
            {
                // Interfaz y averiguar la línea
                botBarraInsertarEnMedio->set_sensitive( false );
                std::auto_ptr<PosicionCelda> pos = getCeldaActual();

                // ¿Qué fila es?
                if ( pos.get() != NULL )
                        numFila = pos->getNumFila();
                else	numFila = documentoActual->getNumFilas() -1;

                // Borra la línea "real"
                documentoActual->borraFila( numFila );

                // Borra la última línea de la interfaz
                refModeloCamposDoc->erase(
                            refModeloCamposDoc->children()[
                                refModeloCamposDoc->children().size() -1
                            ]
                );

                // Prepara la interfaz
                refrescaTabla( numFila );
                botBarraInsertarEnMedio->set_sensitive( true );
            }
		} else ponMsgError( *this, NoHayDoc );
	}
	catch(const Error &e) {
		ponMsgError( *this, e.toString() );
	}
	catch(...) {
		ponMsgError( *this, "FATAL: Error inesperado." );
	}
}

// ----------------------------------------- VentanaPpal::on_a__adir1_activate()
void VentanaPpal::on_a__adir1_activate()
/// Añadir una nueva fila
{
	std::string strPos = StringMan::toString( documentoActual->getNumFilas() );
	Glib::ustring ustrPos = strPos;
	Gtk::TreePath fila( ustrPos );

	if ( documentoActual != NULL ) {
	  try {
		botBarraInsertar->set_sensitive( false );
		tablaCalifas->scroll_to_row( fila );

		documentoActual->annadeFila();

		refrescaFila( documentoActual->getNumFilas() -1 );
		botBarraInsertar->set_sensitive();
	  }
	  catch(const Error &e) {
		  ponMsgError( *this, e.toString() );
	  }
	  catch(...) {
		  ponMsgError( *this, "Sin memoria creando nueva fila" );
	  }
	}
	else ponMsgError( *this, NoHayDoc );
}

// -------------------------------------- VentanaPpal::on_ascendente1_activate()
void VentanaPpal::on_ascendente1_activate()
{
	DocumentoCalifa * doc;

	if ( documentoActual != NULL ) {
		// Obtener columna
		std::auto_ptr<VentanaPpal::PosicionCelda> pos = getCeldaActual();

		if ( pos.get() != NULL ) {
			// Ordenar
			try {
				doc = documentoActual->ordenar(
										const_cast<Campo *>( pos->getCampo() ),
										DocumentoCalifa::Ascendente
				);
				delete documentoActual;

				documentoActual = doc;
				refrescaTabla();
			} catch(Error &e) {
				ponMsgError( *this, e.toString() );
			}
			catch(...) {
				ponMsgError( *this, "Error indefinido" );
			}
		}
		else ponMsgError( *this, "Debe seleccionar una columna a ordenar ascendentemente" );
	} else ponMsgError( *this, NoHayDoc );
}

// ------------------------------------- VentanaPpal::on_descendente1_activate()
void VentanaPpal::on_descendente1_activate()
{
	DocumentoCalifa * doc;

	if ( documentoActual != NULL ) {
		// Obtener columna
		std::auto_ptr<VentanaPpal::PosicionCelda> pos = getCeldaActual();

		if ( pos.get() != NULL ) {
			// Ordenar
			try {
				doc = documentoActual->ordenar(
											const_cast<Campo *>( pos->getCampo() ),
											DocumentoCalifa::Descendente
				);
				delete documentoActual;
				documentoActual = doc;
				refrescaTabla();
			} catch(Error &e) {
				ponMsgError( *this, e.toString() );
			}
			catch(...) {
				ponMsgError( *this, "Error indefinido" );
			}
		}
		else ponMsgError( *this, "Debe seleccionar una columna a ordenar descendentemente" );
	} else ponMsgError( *this, NoHayDoc );
}

// ------------------------------------------ VentanaPpal::on_opCerrar_activate()
void VentanaPpal::on_opCerrar_activate()
{
	if ( documentoActual != NULL ) {
		guardarDocumentoActual();

		tablaCalifas->remove_all_columns();
		delete documentoActual;
		documentoActual = NULL;
		nombreDocumentoActual.erase();

		uiDesactiva();
	} else ponMsgError( *this, NoHayDoc );
}

// ----------------------------------------------- VentanaPpal::getCampoActual()
std::auto_ptr<VentanaPpal::PosicionCelda> VentanaPpal::getCeldaActual() const
{
	int numFila = 0;
	Gtk::TreeViewColumn *col;
	Gtk::TreeModel::Path fila;
	std::auto_ptr<PosicionCelda> toret( NULL );
	Glib::ListHandle<Gtk::TreeViewColumn *> listaColumnas
												= tablaCalifas->get_columns();
	Glib::ListHandle<Gtk::TreeViewColumn *>::const_iterator it
												= listaColumnas.begin();

	if ( documentoActual != NULL ) {
		// Obtener la fila/columna actual
		tablaCalifas->get_cursor( fila, col );

		// Tomar el número de fila
		if ( !fila.empty()
		  && fila.begin() != NULL )
		{
			numFila = *( fila.begin() );
		}

		// Tomar el número de columna
		for(unsigned int i = 0; it != listaColumnas.end(); ++it, ++i) {
			if ( i >= 1
			  && *it == col )
			{
				toret.reset( new PosicionCelda(
								documentoActual->getListaCampos()[ i - NumColumnasFijas ],
								numFila )
				);
				break;
			}
		}
	} else ponMsgError(  *( ( VentanaPpal *) this ), NoHayDoc );

	return toret;
}

// ----------------------------------------------- VentanaPpal::ponCeldaActual()
void VentanaPpal::putCeldaActual(const VentanaPpal::PosicionCelda &pos)
{
	// Poner el número de fila como TreeModel::Path
	Gtk::TreeModel::Path lPos;
	lPos.push_back( pos.getNumFila() );

	// Poner la columna como TreeViewColumn
	unsigned int i;
	Gtk::TreeViewColumn * col;

	// Buscar el campo actual en la lista de campos del documento
	for(i = 0; i < documentoActual->getListaCampos().size(); ++i) {
		if ( pos.getCampo() == documentoActual->getListaCampos()[ i ] ) {
			break;
		}
	}

	if ( i < documentoActual->getListaCampos().size() ) {
		col = ( (std::vector<Gtk::TreeViewColumn *>)
										tablaCalifas->get_columns() )[ i + NumColumnasFijas ]
		;
		// Poner la posición
		tablaCalifas->scroll_to_row( lPos );
		tablaCalifas->set_cursor( lPos, *col );
	} else ponMsgError( *this, "ERROR interno: Campo no encontrado" );
}

// ------------------------------------------ VentanaPpal::on_buscar1_activate()
void VentanaPpal::on_buscar1_activate()
{
	std::auto_ptr<PosicionCelda> pos = getCeldaActual();

	if ( pos.get() != NULL ) {
		unsigned int i;
		const Campo *campo = pos->getCampo();
		std::string cadenaBuscar = pideInfo( *this,
							"Buscar",
							"Introduzca la cadena a buscar:",
							"Buscar en la columna: " + campo->nombre
		);

		if ( !cadenaBuscar.empty() ) {
		    // Buscar
			StringMan::normCnvt( cadenaBuscar );
			ultimaBusqueda = cadenaBuscar;
			campoUltimaBusqueda = campo;

			i = campo->buscar( cadenaBuscar, 0 );
			linUltimaBusqueda = i;

			// Si fallo
			if ( i < documentoActual->getNumFilas() ) {
                PosicionCelda nuevaPos( campo, i );
                putCeldaActual( nuevaPos );
			} else {
				ponMsgInfo( *this, "No encontrado. Buscando '"
								+ cadenaBuscar
								+ "' en <i>"
								+ campo->nombre + "</i>.");
			}
		}
	}
	else ponMsgError( *this, "Debe seleccionar una columna en la que buscar" );

	return;
}

// --------------------------------- VentanaPpal::on_buscar_de_nuevo1_activate()
void VentanaPpal::on_buscar_de_nuevo1_activate()
{
    if ( campoUltimaBusqueda != NULL ) {
        const Campo *campo = campoUltimaBusqueda;

        unsigned int i = campo->buscar( ultimaBusqueda, linUltimaBusqueda + 1 );
        linUltimaBusqueda = i;

        // Si Fallo
        if ( i < documentoActual->getNumFilas() ) {
            PosicionCelda pos( campo, i );
            putCeldaActual( pos );
        } else {
            ponMsgInfo( *this, "No encontrado. Buscando '"
                            + ultimaBusqueda
                            + "' en <i>"
                            + campo->nombre + "</i>.");
        }
    }
}

// ------------------------------------- VentanaPpal::on_propiedades1_activate()
void VentanaPpal::on_propiedades1_activate()
{
	if ( documentoActual != NULL ) {
		DlgPropiedades props( *this, documentoActual );

		this->set_sensitive( false );
		documentoActual->ponEnCarga();


		props.run();
		props.hide();

        this->set_sensitive( true );
		documentoActual->ponEnCarga( false );
		prepararVistaColumnasDocumento();
	}
	else ponMsgError( *this, NoHayDoc );
}

// ----------------------------------------- VentanaPpal::on_rellenar_activate()
void VentanaPpal::on_rellenar_activate()
/// Rellenar una columna
{
	std::string valor;
	Campo * campo = NULL;
	std::auto_ptr<VentanaPpal::PosicionCelda> celda;

	if ( documentoActual == NULL ) {
		ponMsgError( *this, "No existe documento" );
		goto END;
	}

	celda = getCeldaActual();

	if ( celda.get() != NULL ) {
		campo = const_cast<Campo *>( celda->getCampo() );

		if ( campo == NULL
		  || !( campo->esEditable() ) )
		{
			ponMsgError( *this, "No es posible rellenar esa columna" );
			goto END;
		}

		valor = pideInfo(
							*this,
							"Rellenar ...",
							"¿Con qué valor desea rellenar?",
							"El campo a rellenar es '" + campo->nombre
							+ "'. Su contenido será reemplazado por el nuevo valor"
							+ " para todas sus filas. Pulse <b>Cancelar</b> si no"
							+ " es este el efecto deseado."
		);

		if ( !valor.empty() ) {
		    campo->rellenar( valor );
		    refrescaTabla();
		}
	}
	else ponMsgError( *this, "Debe seleccionar una columna a rellenar" );

	END:
	return;
}

// -------------------------------------------- VentanaPpal::on_stats_activate()
void VentanaPpal::on_stats_activate()
/// Mostrar estadísticas
{
	if ( documentoActual != NULL ) {
		std::auto_ptr<VentanaPpal::PosicionCelda> celda;
		celda = getCeldaActual();
		Campo * campo = documentoActual->getCampoNotaFinal();

		if ( celda.get() != NULL ) {
			Campo * campoPulsado = const_cast<Campo *>( celda->getCampo() );

			if ( campoPulsado != NULL ) {
				campo = campoPulsado;
			}
		}

		Visor * visor = new Visor( "Estadísticas", *this );

		visor->append_text( "\nEstadísticas de '" + getNombreDocumentoActual() + '\'' );
		visor->append_text( "\n**\n\n" );
		visor->append_text( documentoActual->getEstadisticas( campo ) );

		visor->show();
	} else ponMsgError( *this, "No existe documento" );

	return;
}

// ------------------------------- VentanaPpal::prepararVistaColumnasDocumento()
void VentanaPpal::prepararVistaColumnasDocumento()
/// Según los campos en el documento, crea la vista en columnas más adecuada
{
	Gtk::TreeViewColumn * col;

	// Recrear las columnas
	delete colsDoc;
	colsDoc = new(std::nothrow) ColumnasDocumento(
					NumColumnasFijas + documentoActual->getListaCampos().size()
	);

	if ( colsDoc != NULL ) {
		// Crear el nuevo modelo
		refModeloCamposDoc = Gtk::ListStore::create( *colsDoc );
		tablaCalifas->set_model( refModeloCamposDoc );
		ponInicioProgreso();

		// Crear las columnas fijas
		tablaCalifas->remove_all_columns();
		for( unsigned int i = 0; i < NumColumnasFijas; ++i) {
			if ( i == 0 )
					tablaCalifas->append_column(
						Glib::ustring( TitulosColumnasFijas[ i ] ),
						colsDoc->getColumnaIndice()
					);
			else	tablaCalifas->append_column(
						Glib::ustring( TitulosColumnasFijas[ i ] ),
						colsDoc->getListaColumnasTexto()[ i - 1 ]
					);
		}

		// Crear las columnas reales
		for(unsigned int i = 0; i < documentoActual->getListaCampos().size(); ++i) {
			ponProgreso( "creando columnas ...", 0, i, documentoActual->getListaCampos().size() );

			if ( !( documentoActual->getListaCampos()[ i ]->esEditable() ) )
			{
				// No es editable
				tablaCalifas->append_column(
					Glib::ustring( documentoActual->getListaCampos()[ i ]->nombre ),
						( colsDoc->getListaColumnasTexto() )[ i + NumColumnasFijas - 1 ]
				);
			} else {
				// Es editable
				tablaCalifas->append_column_editable(
					Glib::ustring( documentoActual->getListaCampos()[ i ]->nombre ),
							   colsDoc->getListaColumnasTexto()[ NumColumnasFijas + i - 1 ]
				);

				// Conectar con el método de edición
				col = tablaCalifas->get_column( tablaCalifas->get_columns().size() - 1 );
				( (Gtk::CellRendererText *) col->get_first_cell_renderer() )
					->signal_edited().connect(
					  sigc::bind<int>(
						sigc::mem_fun( *this, &VentanaPpal::onColEdited ),
						NumColumnasFijas + i - 1 )
				);

				// Conectar con el mth de atender a teclas
/*				( (Gtk::CellRendererText *) col->get_first_cell_renderer() )
					->signal_key_released().connect(
					  sigc::bind<int>(
						sigc::mem_fun( *this, &VentanaPpal::onKeyPressedInCell ),
						NumColumnasFijas + i - 1 )
				);*/
			}
		}

		// Se puede buscar por DNI
		tablaCalifas->set_search_column( NumColumnasFijas );
		tablaCalifas->set_enable_search();

		// Preparar
		tablaCalifas->columns_autosize();
		tablaCalifas->set_headers_clickable();
		tablaCalifas->set_reorderable( false );

		// Rellenar con los datos
		ponFinalProgreso();
		refrescaTabla();
	}
	else ponMsgError( *this, "sin memoria, creando columnas del documento" );
}

// -------------------------------------------------- VentanaPpal::onColEdited()
void VentanaPpal::onColEdited(const Glib::ustring& path_string,
	const Glib::ustring& valor, unsigned int numCol)
/**
	Se pasa el número de fila y el número de columna,
	contando con las columnas fijas.
*/
{
	unsigned int numFil = atoi( path_string.c_str() );

	// Comprobar que esté dentro de los límites
	numCol -= NumColumnasFijas - 1;
	if ( numCol >= 0
	  && numCol < documentoActual->getListaCampos().size()
	  && numFil >= 0
	  && numFil < documentoActual->getNumFilas() )
	{
		try {
			documentoActual->getListaCampos()[ numCol ]->putValor( numFil, valor );
			refrescaFila( numFil );
		} catch(const Error &e)
		{
		    // Informar
			ponMsgError( *this, e.toString() );

			try {
			    // Resetear campo
				documentoActual->getListaCampos()[ numCol ]->reset( numFil );

				// Poner campo a error en interfaz
				refrescaFila( numFil );
			} catch(...)
			{
				ponMsgError( *this, "ERROR interno: doble excepción al editar" );
			}
		}
	}
	else ponMsgError( *this, "ERROR interno: celda editada ("
						+ path_string
						+ ',' + ' '
						+ StringMan::toString( numCol )
						+ ") no válida"
		);
}

// -------------------------------------------------- VentanaPpal::onColEdited()
void VentanaPpal::onKeyPressedInCell()
{

}


// ------------------------------------------------ VentanaPpal::refrescaTabla()
void VentanaPpal::refrescaTabla(unsigned int numFila)
{
	// Poner las filas
	tablaCalifas->hide();
	ponInicioProgreso();

	for(unsigned int i = numFila; i < documentoActual->getNumFilas(); ++i) {
		refrescaFila( i );

		ponProgreso( "Refrescando tabla", numFila, i, documentoActual->getNumFilas() );
	}

	tablaCalifas->show();
	ponFinalProgreso();
}

// ------------------------------------------------ VentanaPpal::refrescaTabla()
void VentanaPpal::refrescaTabla()
/**
	El código aquí está duplicado para evitar tener que hacer dos bucles,
 	llamando después a refrescaTabla() con número de filas igual a 0
*/
{
	// Identificar el número de filas necesarias
	tablaCalifas->hide();
	refModeloCamposDoc->clear();

	// Reponerlas ahora
	for(unsigned int i = 0; i < documentoActual->getNumFilas(); ++i) {
		refModeloCamposDoc->append();
		refrescaFila( i );
		ponProgreso( "Refrescando tabla", 0, i, documentoActual->getNumFilas() );
	}

	tablaCalifas->show();
	ponFinalProgreso();
}

// ------------------------------------------------- VentanaPpal::refrescaFila()
void VentanaPpal::refrescaFila(unsigned int i)
{
	Gtk::TreeModel::Row fila = refModeloCamposDoc->children()[ i ];

	// Refrescar una fila determinada en la interfaz
	fila->set_value( 0, i + 1 );

	// Ahora mostrar los campos propios
	try {
	  // Calcular la nota final
	  documentoActual->getCampoNotaFinal()->calcula( i );
	  fila->set_value( 1, documentoActual->getCampoNotaFinal()->getPromocion( i ) );

	  for(unsigned int j = 0; j < documentoActual->getListaCampos().size(); ++j)
	  {
		// Mostrar
		fila->set_value( j + NumColumnasFijas,
						 documentoActual->getListaCampos()[ j ]->getValor( i )
		);
	  }
	}
	catch(const Error &e) {
		ponMsgError( *this, e.toString() );
	}
}

// ------------------------------------ VentanaPpal::on_informaci__n1_activate()
void VentanaPpal::on_informaci__n1_activate()
{
	on_acerca_de1_activate();
}

// --------------------------------------- VentanaPpal::on_acerca_de1_activate()
void VentanaPpal::on_acerca_de1_activate()
{
    Gtk::AboutDialog about;
    about.set_icon( this->get_icon() );

    about.set_name( NombreApp );
    about.set_version( VersionApp );
    about.set_copyright( AutorApp );
    about.set_comments( ExplicaApp );
    about.set_logo( this->get_icon() );

    about.run();
}

// --------------------------- VentanaPpal::on_insertar_en_medio_activate()
void VentanaPpal::on_insertar_en_medio_activate()
{
	try {
		if ( documentoActual != NULL ) {
			botBarraInsertarEnMedio->set_sensitive( false );
			std::auto_ptr<PosicionCelda> pos = getCeldaActual();

			if ( pos.get() != NULL ) {
					documentoActual->insertaFila( pos->getNumFila() );
					refModeloCamposDoc->append();
					refrescaTabla( pos->getNumFila() );
			}
			else	on_a__adir1_activate();

			botBarraInsertarEnMedio->set_sensitive( true );
		} else ponMsgError( *this, NoHayDoc );
	}
	catch(const Error &e) {
		ponMsgError( e.toString() );
	}
	catch(...) {
		ponMsgError( *this, "FATAL: Error inesperado." );
	}
}

// ---------------------------------- VentanaPpal::on_verificar_dnis_activate()
void VentanaPpal::on_verificar_dnis_activate()
{
    if ( documentoActual != NULL ) {
        std::auto_ptr<DocumentoCalifa::ListaDNIs> lpos = documentoActual->chkDNIs();
        unsigned int num = lpos->first.size();
        Visor * visor = new Visor( "Verificación DNI's", *this );
        bool algo = false;

        // Verificar letras
        for(unsigned int i = 0; i < documentoActual->getNumFilas(); ++i) {
            CampoDni::validarDNI( documentoActual->getCampoDNI()->getValor( i ) );
            if ( !CampoDni::getMsgErrorValidacion().empty() )
            {
                algo = true;

                visor->append_text( "DNI inválido en " + StringMan::toString( i + 1 ) + ": \"" );
                visor->append_text( documentoActual->toStringFila( i ) + "\"" );
                visor->append_text( "\n\t" + CampoDni::getMsgErrorValidacion() + "\n" );
            }
        }

        // Verificar duplicados
        if ( num > 0 ) {
            algo = true;
            visor->append_text( "\nDNI's duplicados en '" + getNombreDocumentoActual() + '\'' );
            visor->append_text( "\n**\n\n" );

            for(unsigned int i = 0; i < num; ++i) {
                unsigned int pos1 = lpos->first[ i ];
                unsigned int pos2 = lpos->second[ i ];

                visor->append_text( "\nCoincidencia en filas " + StringMan::toString( pos1 + 1 ) );
                visor->append_text( " y " + StringMan::toString( pos2 + 1 ) );
                visor->append_text( "\n" + documentoActual->toStringFila( pos1 ) );
                visor->append_text( "\n" + documentoActual->toStringFila( pos2 ) );
                visor->append_text( "\n--\n" );
            }
        }

        if ( !algo ) {
            delete visor;
            ponMsgInfo( *this, "No se aprecia ningún problema." );
        } else visor->show();

    } else ponMsgError( *this, NoHayDoc );
}

// ------------------------------------------- VentanaPpal::preparaBarraEstado()
void VentanaPpal::preparaBarraEstado()
{
	// Crear los componentes de la barra
	msgEstado = Gtk::manage( new Gtk::Label( Glib::ustring() ) );
	msgPorcentaje = Gtk::manage( new Gtk::Label( Glib::ustring() ) );
	barraProgreso = Gtk::manage( new Gtk::ProgressBar() );

	// Título de la barra de estado y de la aplicación
	barraEstado->push( Glib::ustring( NombreApp ) );

	// Visualizar
	barraEstado->pack_start( *msgEstado );
	barraEstado->pack_start( *msgPorcentaje );
	barraEstado->pack_start( *barraProgreso );
	msgEstado->show();
	msgPorcentaje->show();
	barraProgreso->hide();

	ponEstado( MsgPreparado );
}

// ---------------------------------------------------- VentanaPpal::ponEstado()
void VentanaPpal::ponEstado(const std::string &msg)
{
	std::string mensaje = '|' + ( ' ' + msg );

	msgEstado->set_text( Glib::ustring( mensaje ) );
	msgEstado->show();

	actualizaIntf();
}

// -------------------------------------------- VentanaPpal::ponInicioProgreso()
void VentanaPpal::ponInicioProgreso()
{
		// Comenzar
		msgPorcentaje->set_text( "| 0%" );
		barraProgreso->set_fraction( 0.0 );
	    barraProgreso->show();
		ponEstado( MsgOcupado );
}

// --------------------------------------------- VentanaPpal::ponFinalProgreso()
void VentanaPpal::ponFinalProgreso()
{
		// Terminar
		msgPorcentaje->set_text( Glib::ustring() );
	    barraProgreso->hide();
		ponEstado( MsgPreparado );
}

// -------------------------------------------------- VentanaPpal::ponProgreso()
void VentanaPpal::ponProgreso(const std::string &tarea, int inic, int prg, int fin)
{
	static char bufferProgreso[16];

	// ¿Cuál es el porcentaje?
	double porcentaje = ( ( (double) prg - inic ) / ( (double) fin - inic ) ) * 100;

	// Construir la cadena de procentaje y mostrar
	sprintf( bufferProgreso, "| %d%%", (int) porcentaje );
	msgPorcentaje->set_text( Glib::ustring( bufferProgreso ) );
	msgPorcentaje->show();

	// Ahora el progreso
	porcentaje /= 100;
	barraProgreso->set_fraction( porcentaje );
	barraProgreso->show();

	// Cambiar estado a la tarea concreta
	ponEstado( tarea );
}

// -------------------------- VentanaPpal::on_convertirNombreAParComa_activate()
void VentanaPpal::on_convertirNombreAParComa_activate()
{
	if ( documentoActual != NULL ) {
		// Obtener columna
		std::auto_ptr<VentanaPpal::PosicionCelda> pos = getCeldaActual();

		if ( pos.get() != NULL ) {
			// Convertir
			try {
				documentoActual->convertirCampoNombreApsComaNombre( (Campo *) pos->getCampo() );
				refrescaTabla();
			} catch(Error &e) {
				ponMsgError( *this, e.toString() );
			}
			catch(...) {
				ponMsgError( *this, "Error indefinido" );
			}
		}
		else ponMsgError( *this, "Debe seleccionar una columna de nombre completo" );
	} else ponMsgError( *this, NoHayDoc );
}

// ------------------------- VentanaPpal::on_convertirNombreDeParComa_activate()
void VentanaPpal::on_convertirNombreDeParComa_activate()
{
	if ( documentoActual != NULL ) {
		// Obtener columna
		std::auto_ptr<VentanaPpal::PosicionCelda> pos = getCeldaActual();

		if ( pos.get() != NULL ) {
			// Convertir
			try {
				documentoActual->convertirCampoNombreNombreAps( (Campo *) pos->getCampo() );
				refrescaTabla();
			} catch(Error &e) {
				ponMsgError( *this, e.toString() );
			}
			catch(...) {
				ponMsgError( *this, "Error indefinido" );
			}
		}
		else ponMsgError( *this, "Debe seleccionar una columna de nombre completo" );
	} else ponMsgError( *this, NoHayDoc );
}


// ------------------------------------------ VentanaPpal::on_opMezclar_activate()
void VentanaPpal::on_opMezclar_activate()
{
    const std::string * nuevoNombre = &DocumentoCalifa::ArchivoSinNombre;
    DocumentoCalifa * docBase = documentoActual;

    // Guardar el archivo de calificaciones actual
    try {
        if ( documentoActual == NULL ) {
            throw InconsistenciaError( "necesita un archivo cargado" );
        }

        this->guardarDocumentoActual( NoRequierePreguntar );

        // Cargar el archivo nuevo de calificaciones
        std::string nuevoArchivo = pideNombreArchivoAbrir( *this,
                                "Documento para mezclar...",
                                "",
                                nombreDocumentoActual,
                                "*" + DocumentoCalifa::ExtArchivoDatos
        );

        if ( !( nuevoArchivo.empty() ) ) {
            std::auto_ptr<DocumentoCalifa> docMezcla( DocumentoCalifa::cargar( nuevoArchivo ) );
            documentoActual = NULL;

            documentoActual = DocumentoCalifa::mezclar( *docBase, *docMezcla );
            delete docBase;
            docBase = NULL;
        }
    }
    catch(const Error &e) {
        ponMsgError( *this, e.toString() );
    }
    catch(const std::runtime_error &e) {
        ponMsgError( *this, std::string( e.what() ) );
    }
    catch(...) {
        ponMsgError( *this, "ERROR inesperado" );
    }

    // Poner la interfaz a tono
    this->ponFinalProgreso();
    if ( documentoActual == NULL ) {
        documentoActual = docBase;
        nuevoNombre = &( this->getNombreDocumentoActual() );
    }

    if ( documentoActual == NULL ) {
        this->uiDesactiva();
    } else {
        if ( documentoActual != docBase ) {
            this->prepararVistaColumnasDocumento();
        }
        this->uiActiva();
    }

    if ( nuevoNombre != &( this->getNombreDocumentoActual() ) )  {
        this->cambiarNombreDocumentoActual( *nuevoNombre );
    }
}

// -------------------------------------------------------------------------- ui
void ponInicioProgreso()
{
	vPpal->ponInicioProgreso();
}

void ponFinalProgreso()
{
	vPpal->ponFinalProgreso();
}

void ponProgreso(const std::string &tarea, int inic, int prg, int fin)
{
	vPpal->ponProgreso( tarea, inic, prg, fin );
}
