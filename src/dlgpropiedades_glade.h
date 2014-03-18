// generated 2006/9/20 13:41:26 CEST by baltasarq@pcjgarcia.(none)
// using glademm V2.6.0

#ifndef _DLGPROPIEDADES_GLADE_HH
#define _DLGPROPIEDADES_GLADE_HH

#include <gtkmm/dialog.h>
#include <gtkmm/button.h>
#include <gtkmm/treeview.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/entry.h>
#include <gtkmm/table.h>

class DlgPropiedades_glade : public Gtk::Dialog {
public:
		 Gtk::Table * tablaDatos;
         Gtk::Dialog * DlgPropiedades;
         Gtk::Button * botAyuda;
         Gtk::Button * botCerrar;
         Gtk::TreeView * tablaColumnasTipo;
         Gtk::TreeView * tablaColumnasPred;
         Gtk::Button * botMasCols;
         Gtk::TreeView * tablaColumnas;
         Gtk::CheckButton * botEsInformativo;
         Gtk::CheckButton * botEsNecesarioAprobar;
         Gtk::CheckButton * botPuntuarSobre10;
         Gtk::SpinButton * editPorcentaje;
         Gtk::Entry * editValor;
         Gtk::Button * botArriba;
         Gtk::Button * botAbajo;
         Gtk::Button * botNormalizar;
         Gtk::Button * botBorrarCol;
         Gtk::Button * botLimpiar;
		 Gtk::Entry * editAsignatura;
		 Gtk::Entry * editConvocatoria;
		 Gtk::Entry * editProfesores;
		 Gtk::Entry * editFecha;
		 Gtk::Entry * editRevision;
		 Gtk::Entry * editComentario;
		 Gtk::Label * etqDetalles;
		 Gtk::Button * botDetalles;
protected:
        DlgPropiedades_glade(Gtk::Window &);
        ~DlgPropiedades_glade();
private:
        virtual void on_botDetalles_clicked() = 0;
        virtual void on_botAyuda_clicked() = 0;
        virtual void on_botCerrar_clicked() = 0;
        virtual void on_tablaColumnasTipo_cursor_changed() = 0;
        virtual void on_tablaColumnasPred_cursor_changed() = 0;
        virtual void on_botMasCols_clicked() = 0;
        virtual void on_tablaColumnas_cursor_changed() = 0;
        virtual void on_botEsInformativo_toggled() = 0;
        virtual void on_botEsNecesarioAprobar_toggled() = 0;
        virtual void on_botPuntuarSobre10_toggled() = 0;
        virtual void on_editPorcentaje_changed() = 0;
        virtual void on_editValor_changed() = 0;
        virtual void on_botArriba_clicked() = 0;
        virtual void on_botAbajo_clicked() = 0;
        virtual void on_botNormalizar_clicked() = 0;
        virtual void on_botBorrarCol_clicked() = 0;
        virtual void on_botLimpiar_clicked() = 0;
        virtual void on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) = 0;
};
#endif
