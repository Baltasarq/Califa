// generated 2006/9/20 18:44:57 CEST by baltasarq@pcjgarcia.(none)
// using glademm V2.6.0

#ifndef _DLGCONVERTIR_GLADE_HH
#define _DLGCONVERTIR_GLADE_HH

#include <gtkmm/window.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm.h>

class DlgConvertir_glade : public Gtk::Dialog {
public:
        Gtk::ComboBoxText * listaConversion;
        Gtk::Entry * edNombreArchivo;
        Gtk::Button * botGuardarComo;
        Gtk::VBox * cajaListaCampos;
        Gtk::CheckButton * botDNISinLetra;
        Gtk::CheckButton * botSaltoLinDOS;
        Gtk::CheckButton * botSaltarNoPresentados;
        Gtk::ComboBoxText * listaSepCampos;
        Gtk::ComboBoxText * listaSepDecimal;
        Gtk::VBox * cajaOpsCSV;
		Gtk::Button * botConvertir;
		Gtk::VSeparator *separador;

        virtual void on_listaConversion_changed() = 0;
        virtual void on_botBuscar_clicked() = 0;
		virtual void on_botCancelar_clicked() = 0;
		virtual void on_botEditar_clicked() = 0;
		virtual void on_botAceptar_clicked() = 0;
        virtual void on_botSaltoLinDOS_toggled() = 0;
protected:
        DlgConvertir_glade(Gtk::Window &parent);
        virtual ~DlgConvertir_glade() {};
};
#endif
