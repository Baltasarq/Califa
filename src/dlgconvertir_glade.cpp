// generated 2006/9/20 18:44:57 CEST by baltasarq@pcjgarcia
// using glademm V2.6.0

#include <gtkmmconfig.h>
#include <sigc++/sigc++.h>
#include <gtkmm/box.h>
#include <gtkmm/separator.h>
#include <gtkmm/scrolledwindow.h>

#include "config.h"
#include "dlgconvertir_glade.h"

DlgConvertir_glade::DlgConvertir_glade(Gtk::Window &parent)
    : Gtk::Dialog( "Convert", parent, true )
{
   Gtk::HBox * master = Gtk::manage( new Gtk::HBox(false, 0) );
   listaConversion = Gtk::manage( new Gtk::ComboBoxText( true ) );

   Gtk::HBox *regletaGuardarComo = Gtk::manage(new Gtk::HBox(true, 0));
   edNombreArchivo = Gtk::manage( new Gtk::Entry() );
   edNombreArchivo->set_visibility(true);
   edNombreArchivo->set_editable(true);
   edNombreArchivo->set_text("");
   edNombreArchivo->set_has_frame(true);
   edNombreArchivo->set_activates_default( true );
   edNombreArchivo->set_width_chars( 32 );
   botGuardarComo = Gtk::manage( new Gtk::Button( Gtk::StockID( "gtk-save-as") ) );
   botGuardarComo->set_relief(Gtk::RELIEF_NORMAL);
   regletaGuardarComo->pack_start( *edNombreArchivo );
   regletaGuardarComo->pack_start( *botGuardarComo, Gtk::PACK_SHRINK, 0 );
   regletaGuardarComo->set_homogeneous( false );

   Gtk::ScrolledWindow * scroll = Gtk::manage( new Gtk::ScrolledWindow() );
   cajaListaCampos = Gtk::manage(new Gtk::VBox(false, 0));
   cajaListaCampos->set_border_width( 10 );
   scroll->add( *cajaListaCampos );
   scroll->show();

   Gtk::VBox *vBoxDocumento = Gtk::manage( new Gtk::VBox( false, 0 ) );
   vBoxDocumento->set_border_width( 10 );
   vBoxDocumento->pack_start( *listaConversion, Gtk::PACK_SHRINK, 0 );
   vBoxDocumento->pack_start( *regletaGuardarComo, Gtk::PACK_SHRINK, 0 );
   vBoxDocumento->pack_start( *scroll, Gtk::PACK_EXPAND_WIDGET, 0 );
   separador = Gtk::manage( new Gtk::VSeparator()) ;
   botDNISinLetra = Gtk::manage( new Gtk::CheckButton( "DNI (NIF sin letra)" ) );
   botSaltoLinDOS = Gtk::manage( new Gtk::CheckButton( "Cambio de línea DOS" ) );
   botSaltarNoPresentados = Gtk::manage( new Gtk::CheckButton( "Excluir no presentados" ) );
   botDNISinLetra->set_relief( Gtk::RELIEF_NORMAL);
   botDNISinLetra->set_mode( true );
   botDNISinLetra->set_active( false );
   botSaltarNoPresentados->set_relief( Gtk::RELIEF_NORMAL);
   botSaltarNoPresentados->set_mode( true );
   botSaltarNoPresentados->set_active( false );
   botSaltarNoPresentados->activate();
   botSaltoLinDOS->set_relief( Gtk::RELIEF_NORMAL );
   botSaltoLinDOS->set_mode( true );
   botSaltoLinDOS->set_active( false );

   Gtk::HBox *regletaSeparadorCampos = Gtk::manage(new Gtk::HBox(false, 0));
   Gtk::Label *lblCaracterSeparador = Gtk::manage(new Gtk::Label("Carácter separador: "));
   listaSepCampos = Gtk::manage( new class Gtk::ComboBoxText( true ) );
   lblCaracterSeparador->set_alignment(0.5,0.5);
   lblCaracterSeparador->set_padding(0,0);
   lblCaracterSeparador->set_justify(Gtk::JUSTIFY_LEFT);
   lblCaracterSeparador->set_line_wrap(false);
   lblCaracterSeparador->set_use_markup(false);
   lblCaracterSeparador->set_selectable(false);
   regletaSeparadorCampos->pack_start(*lblCaracterSeparador, Gtk::PACK_SHRINK, 0);
   regletaSeparadorCampos->pack_start(*listaSepCampos);

   Gtk::HBox *regletaSeparadorDecimal = Gtk::manage(new Gtk::HBox(false, 0));
   Gtk::Label *lblSeparadorDecimal = Gtk::manage(new Gtk::Label("Carácter decimal:"));
   listaSepDecimal = Gtk::manage(new Gtk::ComboBoxText());
   lblSeparadorDecimal->set_alignment(0.5,0.5);
   lblSeparadorDecimal->set_padding(0,0);
   lblSeparadorDecimal->set_justify(Gtk::JUSTIFY_LEFT);
   lblSeparadorDecimal->set_line_wrap(false);
   lblSeparadorDecimal->set_use_markup(false);
   lblSeparadorDecimal->set_selectable(false);
   regletaSeparadorDecimal->pack_start(*lblSeparadorDecimal, Gtk::PACK_SHRINK, 0);
   regletaSeparadorDecimal->pack_start(*listaSepDecimal, Gtk::PACK_SHRINK, 0);

   cajaOpsCSV = Gtk::manage( new Gtk::VBox( true, 0 ) );
   cajaOpsCSV->set_border_width( 10 );
   cajaOpsCSV->pack_start( *botDNISinLetra, Gtk::PACK_SHRINK, 0 );
   cajaOpsCSV->pack_start( *botSaltarNoPresentados, Gtk::PACK_SHRINK, 0 );
   cajaOpsCSV->pack_start( *botSaltoLinDOS, Gtk::PACK_SHRINK, 0 );
   cajaOpsCSV->pack_start( *regletaSeparadorCampos, Gtk::PACK_SHRINK, 0 );
   cajaOpsCSV->pack_start( *regletaSeparadorDecimal, Gtk::PACK_SHRINK, 0 );

   master->pack_start( *vBoxDocumento );
   master->pack_start( *separador );
   master->pack_start( *cajaOpsCSV );
   master->set_homogeneous( false );
   vBoxDocumento->set_homogeneous( false );

   // toques finales
   this->get_vbox()->add( *master );
   this->set_modal( true );
   this->property_window_position().set_value( Gtk::WIN_POS_CENTER );
   this->set_resizable( true );
   this->property_destroy_with_parent().set_value(false);
   this->set_default_size( 320, 320 );

   // botones
   this->add_button( Gtk::StockID("gtk-close"), Gtk::RESPONSE_CLOSE );
   botConvertir = this->add_button( Gtk::StockID("gtk-convert"), Gtk::RESPONSE_OK );
   this->show_all();

   // enlaces con botones
   listaConversion->signal_changed().connect(sigc::mem_fun(*this, &DlgConvertir_glade::on_listaConversion_changed), false);
   botGuardarComo->signal_clicked().connect(sigc::mem_fun(*this, &DlgConvertir_glade::on_botBuscar_clicked), false);
   botSaltoLinDOS->signal_toggled().connect(sigc::mem_fun(*this, &DlgConvertir_glade::on_botSaltoLinDOS_toggled), false);
   botConvertir->signal_clicked().connect(sigc::mem_fun(*this, &DlgConvertir_glade::on_botAceptar_clicked), false);
}

