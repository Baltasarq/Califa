// generated 2006/9/20 18:31:31 CEST by baltasarq@pcjgarcia.(none)
// using glademm V2.6.0

#include <gtkmmconfig.h>
#include <sigc++/sigc++.h>
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <gtkmm/separator.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/image.h>
#include <gtkmm/table.h>

#include "config.h"
#include "dlgpropiedades_glade.h"

#include <memory>

DlgPropiedades_glade::DlgPropiedades_glade(Gtk::Window &parent)
    : Gtk::Dialog( "Propiedades", parent, true )
{
   // Parte de datos
   tablaDatos = Gtk::manage( new Gtk::Table( 6, 2, true ) );

   Gtk::Label * etqAsg = Gtk::manage( new Gtk::Label( "Asignatura:", Gtk::JUSTIFY_LEFT ) );
   editAsignatura = Gtk::manage( new Gtk::Entry() );

   Gtk::Label * etqConv = Gtk::manage( new Gtk::Label( "Convocatoria:", Gtk::JUSTIFY_LEFT ) );
   editConvocatoria = Gtk::manage( new Gtk::Entry() );

   Gtk::Label * etqProf = Gtk::manage( new Gtk::Label( "Profesores:",Gtk::JUSTIFY_LEFT ) );
   editProfesores = Gtk::manage( new Gtk::Entry() );

   Gtk::Label * etqFecha = Gtk::manage( new Gtk::Label( "Fecha:", Gtk::JUSTIFY_LEFT ) );
   editFecha = Gtk::manage( new Gtk::Entry() );

   Gtk::Label * etqRev = Gtk::manage( new Gtk::Label( "Revision:", Gtk::JUSTIFY_LEFT ) );
   editRevision = Gtk::manage( new Gtk::Entry() );

   Gtk::Label * etqCom = Gtk::manage( new Gtk::Label( "Comentario:", Gtk::JUSTIFY_LEFT ) );
   editComentario = Gtk::manage( new Gtk::Entry() );

   tablaDatos->attach( *editAsignatura, 1, 2, 0, 1 );
   tablaDatos->attach( *etqAsg, 0, 1, 0, 1 );

   tablaDatos->attach( *editConvocatoria, 1, 2, 1, 2 );
   tablaDatos->attach( *etqConv, 0, 1, 1, 2 );

   tablaDatos->attach( *editProfesores, 1, 2, 2, 3 );
   tablaDatos->attach( *etqProf, 0, 1, 2, 3 );

   tablaDatos->attach( *editFecha, 1, 2, 3, 4 );
   tablaDatos->attach( *etqFecha, 0, 1, 3, 4 );

   tablaDatos->attach( *editRevision, 1, 2, 4, 5 );
   tablaDatos->attach( *etqRev, 0, 1, 4, 5 );

   tablaDatos->attach( *editComentario, 1, 2, 5, 6 );
   tablaDatos->attach( *etqCom, 0, 1, 5, 6 );

   // El resto de los componentes del diálogo
   tablaColumnasTipo = Gtk::manage(new  Gtk::TreeView());
   tablaColumnasTipo->set_tooltip_text(Glib::ustring(
        "Tipos de columnas básicas."
   ));

   Gtk::ScrolledWindow *scrlColumnasTipo = Gtk::manage(new  Gtk::ScrolledWindow());
   tablaColumnasPred = Gtk::manage(new  Gtk::TreeView());
   tablaColumnasPred->set_tooltip_text(Glib::ustring(
        "Columnas predefinidas, listas para usar."
   ));

   Gtk::ScrolledWindow *scrlColumnasPred = Gtk::manage(new  Gtk::ScrolledWindow());
   Gtk::VBox *vboxFrmColumnasTipo = Gtk::manage(new  Gtk::VBox(false, 0));

   Gtk::Label *lblColumnasDisponibles = Gtk::manage(new  Gtk::Label("<b>Columnas disponibles</b>"));
   Gtk::Frame *frmColumnasPred = Gtk::manage(new  Gtk::Frame());
   tablaColumnas = Gtk::manage(new  Gtk::TreeView());
   tablaColumnas->set_tooltip_text(Glib::ustring(
        "Columnas ya incorporadas al documento."
   ));

   Gtk::VSeparator *vseparatorArriba = Gtk::manage(new  Gtk::VSeparator());
   Gtk::VSeparator *vseparatorAbajo = Gtk::manage(new  Gtk::VSeparator());
   botMasCols = Gtk::manage(new  Gtk::Button(Gtk::StockID("gtk-add")));
   Gtk::VBox *vBoxBotMasCols = Gtk::manage(new  Gtk::VBox(false, 0));
   vBoxBotMasCols->pack_start( *vseparatorArriba, Gtk::PACK_EXPAND_WIDGET, 0 );
   vBoxBotMasCols->pack_start( *botMasCols, Gtk::PACK_SHRINK, 0 );
   vBoxBotMasCols->pack_start( *vseparatorAbajo, Gtk::PACK_EXPAND_WIDGET, 0 );


   Gtk::ScrolledWindow *scrlColumnas = Gtk::manage(new  Gtk::ScrolledWindow());
   Gtk::Label *lblColumnasIncorporadas = Gtk::manage(new  Gtk::Label("<b>Columnas incorporadas</b>"));
   Gtk::Frame *frmColumnas = Gtk::manage(new  Gtk::Frame());
   Gtk::VSeparator *vseparator4 = Gtk::manage(new  Gtk::VSeparator());
   botEsInformativo = Gtk::manage(new  Gtk::CheckButton("Sólo informativo"));
   botEsInformativo->set_tooltip_text(Glib::ustring(
        "Interviene o no en el cálculo de la nota final."
   ));

   Gtk::HBox *hbox10 = Gtk::manage(new  Gtk::HBox(false, 0));
   botEsNecesarioAprobar = Gtk::manage(new  Gtk::CheckButton("Es necesario aprobar"));
   botEsNecesarioAprobar->set_tooltip_text(Glib::ustring(
        "Es necesario tener un aprobado para que se haga la media con el resto de notas."
   ));
   botPuntuarSobre10 = Gtk::manage(new  Gtk::CheckButton("Ver puntuado sobre diez"));
   botPuntuarSobre10->set_tooltip_text(Glib::ustring(
        "La nota aparece puntuada sobre 10, tenga el peso que tenga."
   ));

   Gtk::VBox * vbox11 = Gtk::manage( new Gtk::VBox( false, 0 ) );
   Gtk::Label *lblPorcentaje = Gtk::manage(new  Gtk::Label("Porcentaje nota: "));
   Gtk::Adjustment * editPorcentaje_adj = Gtk::manage( new Gtk::Adjustment( 1, 1, 100 ) );
   editPorcentaje = Gtk::manage( new Gtk::SpinButton( *editPorcentaje_adj, 1, 0 ) );
   editPorcentaje->set_update_policy( Gtk::UPDATE_ALWAYS );
   editPorcentaje->set_numeric( true );
   editPorcentaje->set_wrap( false );
   editPorcentaje->set_width_chars( 3 );
   editPorcentaje->set_tooltip_text(Glib::ustring(
        "Si no se usan arriba y abajo, pulse ENTER tras introducir el valor."
    ));

   Gtk::HBox *hbox9 = Gtk::manage(new  Gtk::HBox(false, 0));
   Gtk::Label *lblValor = Gtk::manage(new  Gtk::Label(Glib::ustring("Título: ")));
   editValor = Gtk::manage(new  Gtk::Entry());

   Gtk::HBox *hbox8 = Gtk::manage(new  Gtk::HBox(false, 0));
   Gtk::HSeparator *hseparator8 = Gtk::manage(new  Gtk::HSeparator());
   botArriba = Gtk::manage(new  Gtk::Button(Gtk::StockID("gtk-go-up")));
   botAbajo = Gtk::manage(new  Gtk::Button(Gtk::StockID("gtk-go-down")));

   Gtk::Image *imgEdit = Gtk::manage(new  Gtk::Image(Gtk::StockID("gtk-edit"), Gtk::IconSize(4)));
   Gtk::Label *lblNormalizar = Gtk::manage(new  Gtk::Label("_Normalizar notas", true));
   Gtk::HBox *hbox14 = Gtk::manage(new  Gtk::HBox(false, 2));
   Gtk::Alignment *alignment10 = Gtk::manage(new  Gtk::Alignment(0.5, 0.5, 0, 0));
   botNormalizar = Gtk::manage(new  Gtk::Button());
   botNormalizar->set_tooltip_text(Glib::ustring(
        "Todas las notas pasan a tener el mismo peso."
   ));

   Gtk::Image *imgEdit2 = Gtk::manage(new  Gtk::Image(Gtk::StockID("gtk-edit"), Gtk::IconSize(4)));
   etqDetalles = Gtk::manage(new  Gtk::Label("_Ver detalles", true));
   Gtk::HBox *hbox114 = Gtk::manage(new  Gtk::HBox(false, 2));
   Gtk::Alignment *alignment110 = Gtk::manage(new  Gtk::Alignment(0.5, 0.5, 0, 0));
   botDetalles = Gtk::manage(new  Gtk::Button());
   botDetalles->add(*alignment110);
   alignment110->add(*hbox114);
   hbox114->pack_start( *imgEdit2, Gtk::PACK_SHRINK, 0 );
   hbox114->pack_start( *etqDetalles, Gtk::PACK_SHRINK, 0 );

   Gtk::VBox *vbox6 = Gtk::manage(new  Gtk::VBox(false, 0));
   botBorrarCol = Gtk::manage(new  Gtk::Button(Gtk::StockID("gtk-delete")));
   botLimpiar = Gtk::manage(new  Gtk::Button(Gtk::StockID("gtk-clear")));

   Gtk::VBox *vbox3 = Gtk::manage(new  Gtk::VBox(false, 0));
   Gtk::Alignment *alignment7 = Gtk::manage(new  Gtk::Alignment(0.5, 0.5, 1, 1));
   Gtk::Label *label22 = Gtk::manage(new  Gtk::Label("<b>Propiedades</b>"));
   Gtk::Frame *frame3 = Gtk::manage(new  Gtk::Frame());
   Gtk::HBox *hbox7 = Gtk::manage(new  Gtk::HBox(false, 0));
   this->get_action_area()->property_layout_style().set_value(Gtk::BUTTONBOX_END);
   tablaColumnasTipo->set_headers_visible(true);
   tablaColumnasTipo->set_rules_hint(true);
   tablaColumnasTipo->set_reorderable(false);
   tablaColumnasTipo->set_enable_search(true);
   scrlColumnasTipo->set_shadow_type(Gtk::SHADOW_IN);
   scrlColumnasTipo->set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
   scrlColumnasTipo->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   scrlColumnasTipo->add(*tablaColumnasTipo);
   tablaColumnasPred->set_headers_visible(true);
   tablaColumnasPred->set_rules_hint(true);
   tablaColumnasPred->set_reorderable(false);
   tablaColumnasPred->set_enable_search(true);
   scrlColumnasPred->set_shadow_type(Gtk::SHADOW_IN);
   scrlColumnasPred->set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
   scrlColumnasPred->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   scrlColumnasPred->add(*tablaColumnasPred);
   vboxFrmColumnasTipo->pack_start( *scrlColumnasTipo, Gtk::PACK_EXPAND_WIDGET, 0 );
   vboxFrmColumnasTipo->pack_start( *scrlColumnasPred, Gtk::PACK_EXPAND_WIDGET, 0 );
   lblColumnasDisponibles->set_alignment(0.5,0.5);
   lblColumnasDisponibles->set_padding(0,0);
   lblColumnasDisponibles->set_justify(Gtk::JUSTIFY_LEFT);
   lblColumnasDisponibles->set_line_wrap(false);
   lblColumnasDisponibles->set_use_markup(true);
   lblColumnasDisponibles->set_selectable(false);
   frmColumnasPred->set_border_width( 10 );
   frmColumnasPred->set_shadow_type(Gtk::SHADOW_NONE);
   frmColumnasPred->set_label_align(0,0.5);
   frmColumnasPred->add(*vboxFrmColumnasTipo);
   frmColumnasPred->set_label_widget(*lblColumnasDisponibles);
   tablaColumnas->set_headers_visible(true);
   tablaColumnas->set_rules_hint(true);
   tablaColumnas->set_reorderable(false);
   tablaColumnas->set_enable_search(true);
   scrlColumnas->set_shadow_type(Gtk::SHADOW_IN);
   scrlColumnas->set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
   scrlColumnas->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   scrlColumnas->add(*tablaColumnas);
   lblColumnasIncorporadas->set_alignment(0.5,0.5);
   lblColumnasIncorporadas->set_padding(0,0);
   lblColumnasIncorporadas->set_justify(Gtk::JUSTIFY_LEFT);
   lblColumnasIncorporadas->set_line_wrap(false);
   lblColumnasIncorporadas->set_use_markup(true);
   lblColumnasIncorporadas->set_selectable(false);
   frmColumnas->set_border_width( 10 );
   frmColumnas->set_shadow_type(Gtk::SHADOW_NONE);
   frmColumnas->set_label_align(0,0.5);
   frmColumnas->add(*scrlColumnas);
   frmColumnas->set_label_widget(*lblColumnasIncorporadas);
   botEsInformativo->set_relief(Gtk::RELIEF_NORMAL);
   botEsInformativo->set_mode(true);
   botEsInformativo->set_active(false);
   hbox10->pack_start(*botEsInformativo, Gtk::PACK_SHRINK, 0);
   botEsNecesarioAprobar->set_relief(Gtk::RELIEF_NORMAL);
   botEsNecesarioAprobar->set_mode(true);
   botEsNecesarioAprobar->set_active(false);
   botPuntuarSobre10->set_relief(Gtk::RELIEF_NORMAL);
   botPuntuarSobre10->set_mode(true);
   botPuntuarSobre10->set_active(false);
   vbox11->pack_start(*hbox10);
   vbox11->pack_start(*botEsNecesarioAprobar, Gtk::PACK_SHRINK, 0);
   vbox11->pack_start(*botPuntuarSobre10, Gtk::PACK_SHRINK, 0);
   lblPorcentaje->set_alignment(0.5,0.5);
   lblPorcentaje->set_padding(0,0);
   lblPorcentaje->set_justify(Gtk::JUSTIFY_LEFT);
   lblPorcentaje->set_line_wrap(false);
   lblPorcentaje->set_use_markup(false);
   lblPorcentaje->set_selectable(false);
   hbox9->pack_start(*lblPorcentaje, Gtk::PACK_SHRINK, 0);
   hbox9->pack_start(*editPorcentaje);
   lblValor->set_alignment(0.5,0.5);
   lblValor->set_padding(0,0);
   lblValor->set_justify(Gtk::JUSTIFY_LEFT);
   lblValor->set_line_wrap(false);
   lblValor->set_use_markup(false);
   lblValor->set_selectable(false);
   editValor->set_visibility(true);
   editValor->set_editable(true);
   editValor->set_max_length(0);
   editValor->set_text("");
   editValor->set_has_frame(true);
   editValor->set_activates_default(false);
   hbox8->pack_start(*lblValor, Gtk::PACK_SHRINK, 0);
   hbox8->pack_start(*editValor);
   botArriba->set_relief(Gtk::RELIEF_NORMAL);
   botAbajo->set_relief(Gtk::RELIEF_NORMAL);
   imgEdit->set_alignment(0.5,0.5);
   imgEdit->set_padding(0,0);
   lblNormalizar->set_alignment(0.5,0.5);
   lblNormalizar->set_padding(0,0);
   lblNormalizar->set_justify(Gtk::JUSTIFY_LEFT);
   lblNormalizar->set_line_wrap(false);
   lblNormalizar->set_use_markup(false);
   lblNormalizar->set_selectable(false);
   hbox14->pack_start(*imgEdit, Gtk::PACK_SHRINK, 0);
   hbox14->pack_start(*lblNormalizar, Gtk::PACK_SHRINK, 0);
   alignment10->add(*hbox14);
   botNormalizar->set_relief(Gtk::RELIEF_NORMAL);
   botNormalizar->add(*alignment10);
   vbox6->pack_start(*hseparator8);
   vbox6->pack_start(*botArriba, Gtk::PACK_SHRINK, 0);
   vbox6->pack_start(*botAbajo, Gtk::PACK_SHRINK, 0);
   vbox6->pack_start(*botNormalizar, Gtk::PACK_SHRINK, 0);
   vbox6->pack_start(*botDetalles, Gtk::PACK_SHRINK, 0);
   botBorrarCol->set_relief(Gtk::RELIEF_NORMAL);
   botLimpiar->set_relief(Gtk::RELIEF_NORMAL);
   vbox3->pack_start(*vbox11, Gtk::PACK_SHRINK, 0);
   vbox3->pack_start(*hbox9, Gtk::PACK_SHRINK, 0);
   vbox3->pack_start(*hbox8, Gtk::PACK_SHRINK, 0);
   vbox3->pack_start(*vbox6);
   vbox3->pack_start(*botBorrarCol, Gtk::PACK_SHRINK, 0);
   vbox3->pack_start(*botLimpiar, Gtk::PACK_SHRINK, 0);
   alignment7->add(*vbox3);
   label22->set_alignment(0.5,0.5);
   label22->set_padding(0,0);
   label22->set_justify(Gtk::JUSTIFY_LEFT);
   label22->set_line_wrap(false);
   label22->set_use_markup(true);
   label22->set_selectable(false);
   frame3->set_border_width( 10 );
   frame3->set_shadow_type(Gtk::SHADOW_NONE);
   frame3->set_label_align(0,0.5);
   frame3->add(*alignment7);
   frame3->set_label_widget(*label22);
   hbox7->pack_start(*frmColumnasPred);
   hbox7->pack_start(*vBoxBotMasCols);
   hbox7->pack_start(*frmColumnas);
   hbox7->pack_start(*vseparator4);
   hbox7->pack_start(*frame3);

   // Preparar
   this->get_vbox()->set_homogeneous( false );
   this->get_vbox()->set_spacing( 10 );
   this->get_vbox()->set_border_width( 10 );
   this->get_vbox()->pack_start( *hbox7, Gtk::PACK_EXPAND_WIDGET );
   this->get_vbox()->pack_start( *tablaDatos, Gtk::PACK_EXPAND_WIDGET );
   botAyuda = Gtk::manage( new Gtk::Button( Gtk::StockID( "gtk-help" ) ) );
   this->get_action_area()->add( *botAyuda );
   botCerrar = this->add_button( Gtk::StockID( "gtk-close" ), Gtk::RESPONSE_CLOSE );
   botCerrar->set_tooltip_text(Glib::ustring( "Guardar cambios y salir." ));
   this->property_window_position().set_value( Gtk::WIN_POS_CENTER_ON_PARENT );
   this->set_resizable(true);
   this->property_destroy_with_parent().set_value(false);
   this->show_all();
   tablaDatos->hide();
   this->set_default_size( 700, 570 );

   // Conexiones de botones
   botDetalles->signal_clicked().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_botDetalles_clicked), false);
   botAyuda->signal_clicked().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_botAyuda_clicked), false);
   botCerrar->signal_clicked().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_botCerrar_clicked), false);
   tablaColumnasTipo->signal_cursor_changed().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_tablaColumnasTipo_cursor_changed), false);
   tablaColumnasPred->signal_cursor_changed().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_tablaColumnasPred_cursor_changed), false);
   tablaColumnasPred->signal_row_activated().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_row_activated), false);
   tablaColumnasTipo->signal_row_activated().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_row_activated), false);
   botMasCols->signal_clicked().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_botMasCols_clicked), false);
   tablaColumnas->signal_cursor_changed().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_tablaColumnas_cursor_changed), false);
   botEsInformativo->signal_toggled().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_botEsInformativo_toggled), false);
   botEsNecesarioAprobar->signal_toggled().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_botEsNecesarioAprobar_toggled), false);
   botPuntuarSobre10->signal_toggled().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_botPuntuarSobre10_toggled), false);
   editPorcentaje->signal_changed().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_editPorcentaje_changed), false);
   editPorcentaje->signal_value_changed().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_editPorcentaje_changed), false);
   editValor->signal_changed().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_editValor_changed), false);
   botArriba->signal_clicked().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_botArriba_clicked), false);
   botAbajo->signal_clicked().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_botAbajo_clicked), false);
   botNormalizar->signal_clicked().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_botNormalizar_clicked), false);
   botBorrarCol->signal_clicked().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_botBorrarCol_clicked), false);
   botLimpiar->signal_clicked().connect(sigc::mem_fun(*this, &DlgPropiedades_glade::on_botLimpiar_clicked), false);
}

DlgPropiedades_glade::~DlgPropiedades_glade()
{
}
