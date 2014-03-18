// generated 2006/1/9 13:12:41 CET by baltasarq@pcjgarcia.(none)
// using glademm V2.6.0
// Propiedades del documento (gui)

#ifndef _DLGPROPIEDADES_HH
#define _DLGPROPIEDADES_HH

#include <gtkmm/liststore.h>
#include <string>

#include "dlgpropiedades_glade.h"
#include "documentocalifa.h"

class ColumnaSimple : public Gtk::TreeModel::ColumnRecord {
public:
	Gtk::TreeModelColumn<std::string> datos;

	ColumnaSimple()
		{ add( datos ); }
};

class DlgPropiedades : public DlgPropiedades_glade {
public:
		DlgPropiedades(Gtk::Window &parent, DocumentoCalifa *);

		const DocumentoCalifa * getDocumentoCalifa() const
			{ return documento; }

		ColumnaSimple modeloColumnaSimple;

		void actualizaListadoCampos();
		void insertarColumnaPred();
		void insertarColumnaTipo();
		void activarPropiedades();
		void desactivarPropiedades();

		Gtk::ResponseType run();
		Gtk::ResponseType get_response()
            { return _response; }
        void on_response(int resp)
            { _response = (Gtk::ResponseType) resp; }
private:
        Gtk::ResponseType _response;
		int ancho;
		int alto;
		Glib::RefPtr<Gtk::ListStore> refModeloCampos;
		Gtk::TreeView * tablaSeleccionada;
		DocumentoCalifa * documento;

		static int getOpcion(Gtk::TreeView *);
		static void setOpcion(Gtk::TreeView *tr, unsigned int numOpcion);

        void on_botAyuda_clicked();
        void on_botDetalles_clicked();
        void on_botCerrar_clicked();
        void on_botMasCols_clicked();
        void on_tablaColumnas_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
        void on_tablaColumnasTipo_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
        void on_tablaColumnasPred_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
		void on_tablaColumnasPred_cursor_changed();
		void on_tablaColumnasTipo_cursor_changed();
		void on_tablaColumnas_cursor_changed();
        void on_botEsInformativo_toggled();
        void on_botPuntuarSobre10_toggled();
		void on_botEsNecesarioAprobar_toggled();
        void on_editPorcentaje_changed();
        void on_editValor_changed();
        void on_botNormalizar_clicked();
        void on_botBorrarCol_clicked();
        void on_botLimpiar_clicked();
		void on_botArriba_clicked();
		void on_botAbajo_clicked();
		void on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
};
#endif
