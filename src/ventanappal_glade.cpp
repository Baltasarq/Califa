// generated 2006/9/20 11:25:06 CEST by baltasarq@pcjgarcia.(none)
// using glademm V2.6.0

#include <gtkmmconfig.h>
#include <sigc++/sigc++.h>
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtk/gtkimagemenuitem.h>
#include <gtkmm/image.h>
#include <gtkmm/stockid.h>
#include <gtkmm/separatortoolitem.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>

#include "config.h"
#include "ventanappal_glade.h"

VentanaPpal_glade::VentanaPpal_glade()
    : Gtk::Window( Gtk::WINDOW_TOPLEVEL )
{
   Gtk::ImageMenuItem *nuevo1 = NULL;
   Gtk::ImageMenuItem *abrir1 = NULL;
   opGuardar = NULL;
   opGuardarComo = NULL;
   opInsertarEnMedio = NULL;
   opMezclar = NULL;
   Gtk::Image *image10 = Gtk::manage(new  Gtk::Image(Gtk::StockID("gtk-convert"), Gtk::IconSize( Gtk::ICON_SIZE_MENU )));
   Gtk::ImageMenuItem *importar1 = NULL;
   opConvertir = NULL;
   Gtk::ImageMenuItem *salir1 = NULL;
   Gtk::Menu *menuitem1_menu = Gtk::manage(new  Gtk::Menu());
   Gtk::ImageMenuItem *stats = NULL;
   Gtk::ImageMenuItem *fill = NULL;
   Gtk::ImageMenuItem *borrar1 = NULL;
   Gtk::ImageMenuItem *a__adir1 = NULL;
   Gtk::ImageMenuItem *ascendente1 = NULL;
   Gtk::ImageMenuItem *descendente1 = NULL;
   Gtk::ImageMenuItem *buscar1 = NULL;
   Gtk::ImageMenuItem *buscarNuevo1 = NULL;
   Gtk::ImageMenuItem *propiedades1 = NULL;
   Gtk::Menu *menuitem2_menu = menuEditar = Gtk::manage(new  Gtk::Menu());
   Gtk::ImageMenuItem *informaci__n1 = NULL;
   Gtk::Image *image21 = Gtk::manage(new  Gtk::Image(Gtk::StockID("gtk-jump-to"), Gtk::IconSize( Gtk::ICON_SIZE_LARGE_TOOLBAR )));
   Gtk::Image *image22 = Gtk::manage(new  Gtk::Image(Gtk::StockID("gtk-jump-to"), Gtk::IconSize( Gtk::ICON_SIZE_MENU )));
   Gtk::Image *image23 = Gtk::manage(new  Gtk::Image(Gtk::StockID("gtk-find"), Gtk::IconSize( Gtk::ICON_SIZE_MENU )));
   Gtk::Image *imageStats = Gtk::manage(new  Gtk::Image(Gtk::StockID("gtk-index"), Gtk::IconSize( Gtk::ICON_SIZE_MENU )));
   Gtk::Image *imageFill = Gtk::manage(new  Gtk::Image(Gtk::StockID("gtk-edit"), Gtk::IconSize( Gtk::ICON_SIZE_MENU )));
   Gtk::Image *imgMezclar = Gtk::manage(new  Gtk::Image(Gtk::StockID("gtk-refresh"), Gtk::IconSize( Gtk::ICON_SIZE_MENU )));
   Gtk::ImageMenuItem *acerca_de1 = NULL;
   Gtk::Menu *menuitem4_menu = Gtk::manage(new  Gtk::Menu());
   menuHerramientas = Gtk::manage(new  Gtk::Menu());
   opConvertirParComa = NULL;
   opConvertirDeParComa = NULL;
   opVerificarDNIs = NULL;

   // Ppal menu
   menubar1 = Gtk::manage(new  Gtk::MenuBar());
   menuitem1_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-new")));
   nuevo1 = (Gtk::ImageMenuItem *)&menuitem1_menu->items().back();

   menuitem1_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-open")));
   abrir1 = (Gtk::ImageMenuItem *)&menuitem1_menu->items().back();

   menuitem1_menu->items().push_back(Gtk::Menu_Helpers::ImageMenuElem("_Mezclar con...", *imgMezclar));
   opMezclar = (Gtk::ImageMenuItem *)&menuitem1_menu->items().back();

   menuitem1_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-save")));
   opGuardar = (Gtk::ImageMenuItem *)&menuitem1_menu->items().back();

   menuitem1_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-save-as")));
   opGuardarComo = (Gtk::ImageMenuItem *)&menuitem1_menu->items().back();

   menuitem1_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-close")));
   opCerrar = (Gtk::ImageMenuItem *)&menuitem1_menu->items().back();

   menuitem1_menu->items().push_back(Gtk::Menu_Helpers::SeparatorElem());

   menuitem1_menu->items().push_back(Gtk::Menu_Helpers::ImageMenuElem("_Importar de...", *image10));
   importar1 = (Gtk::ImageMenuItem *)&menuitem1_menu->items().back();

   menuitem1_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-convert")));
   opConvertir = (Gtk::ImageMenuItem *)&menuitem1_menu->items().back();

   menuitem1_menu->items().push_back(Gtk::Menu_Helpers::SeparatorElem());

   menuitem1_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-quit")));
   salir1 = (Gtk::ImageMenuItem *)&menuitem1_menu->items().back();

   menuitem2_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-delete")));
   borrar1 = (Gtk::ImageMenuItem *)&menuitem2_menu->items().back();

   menuitem2_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-add")));
   a__adir1 = (Gtk::ImageMenuItem *)&menuitem2_menu->items().back();

   menuitem2_menu->items().push_back(Gtk::Menu_Helpers::ImageMenuElem("Insertar", *image22));
   opInsertarEnMedio = (Gtk::ImageMenuItem *)&menuitem2_menu->items().back();

   menuitem2_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-find")));
   buscar1 = (Gtk::ImageMenuItem *)&menuitem2_menu->items().back();

   menuitem2_menu->items().push_back(Gtk::Menu_Helpers::ImageMenuElem("Buscar de _nuevo...", *image23));
   buscarNuevo1 = (Gtk::ImageMenuItem *)&menuitem2_menu->items().back();

   menuitem2_menu->items().push_back(Gtk::Menu_Helpers::SeparatorElem());

   menuitem2_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-properties")));
   propiedades1 = (Gtk::ImageMenuItem *)&menuitem2_menu->items().back();

   menuitem4_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-dialog-info")));
   informaci__n1 = (Gtk::ImageMenuItem *)&menuitem4_menu->items().back();

   menuitem4_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-about")));
   acerca_de1 = (Gtk::ImageMenuItem *)&menuitem4_menu->items().back();

   menuHerramientas->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-sort-ascending")));
   ascendente1 = (Gtk::ImageMenuItem *)&menuHerramientas->items().back();

   menuHerramientas->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::StockID("gtk-sort-descending")));
   descendente1 = (Gtk::ImageMenuItem *)&menuHerramientas->items().back();

   menuHerramientas->items().push_back( Gtk::Menu_Helpers::MenuElem( "Convertir _nombre a par apellidos - nombre" ) );
   opConvertirParComa = (Gtk::MenuItem *)&menuHerramientas->items().back();

   menuHerramientas->items().push_back( Gtk::Menu_Helpers::MenuElem( "Convertir nombre de _par apellidos - nombre" ) );
   opConvertirDeParComa = (Gtk::MenuItem *)&menuHerramientas->items().back();

   menuHerramientas->items().push_back( Gtk::Menu_Helpers::MenuElem( "_Verificar DNI's" ) );
   opVerificarDNIs = (Gtk::MenuItem *)&menuHerramientas->items().back();

   menuHerramientas->items().push_back(Gtk::Menu_Helpers::ImageMenuElem("_Estadísticas", *imageStats));
   stats = (Gtk::ImageMenuItem *)&menuHerramientas->items().back();

   menuHerramientas->items().push_back(Gtk::Menu_Helpers::ImageMenuElem("_Rellenar ...", *imageFill));
   fill = (Gtk::ImageMenuItem *)&menuHerramientas->items().back();

   menubar1->items().push_back(Gtk::Menu_Helpers::MenuElem("_Archivo", *menuitem1_menu));

   menubar1->items().push_back(Gtk::Menu_Helpers::MenuElem("_Editar", *menuitem2_menu));

   menubar1->items().push_back(Gtk::Menu_Helpers::MenuElem("_Herramientas", *menuHerramientas));

   menubar1->items().push_back(Gtk::Menu_Helpers::MenuElem("A_yuda", *menuitem4_menu));

   // Barra de herramientas
   Gtk::Toolbar * toolbar = Gtk::manage( new Gtk::Toolbar );
   toolbar->set_tooltips(true);
   toolbar->set_toolbar_style(Gtk::TOOLBAR_BOTH);
   toolbar->set_orientation(Gtk::ORIENTATION_HORIZONTAL);
   toolbar->set_show_arrow(true);
   botBarraGuardar = Gtk::manage(new  Gtk::ToolButton(Gtk::StockID("gtk-save")));
   Gtk::SeparatorToolItem *toolBarSeparator1 = Gtk::manage(new  Gtk::SeparatorToolItem());
   Gtk::SeparatorToolItem *toolBarSeparator2 = Gtk::manage(new  Gtk::SeparatorToolItem());
   Gtk::SeparatorToolItem *toolBarSeparator3 = Gtk::manage(new  Gtk::SeparatorToolItem());
   botBarraBuscar = Gtk::manage(new  Gtk::ToolButton(Gtk::StockID("gtk-find")));
   botBarraAscendente = Gtk::manage(new  Gtk::ToolButton(Gtk::StockID("gtk-sort-ascending")));
   botBarraDescendente = Gtk::manage(new  Gtk::ToolButton(Gtk::StockID("gtk-sort-descending")));
   botBarraInsertar = Gtk::manage(new  Gtk::ToolButton(Gtk::StockID("gtk-add")));
   botBarraInsertarEnMedio = Gtk::manage(new  Gtk::ToolButton(*image21, "Insertar"));
   botBarraBorrar = Gtk::manage(new  Gtk::ToolButton(Gtk::StockID("gtk-delete")));
   botBarraPropiedades = Gtk::manage(new  Gtk::ToolButton(Gtk::StockID("gtk-properties")));
   botBarraConvertir = Gtk::manage(new  Gtk::ToolButton(Gtk::StockID("gtk-convert")));
   toolbar->append(*botBarraGuardar);
   toolbar->append(*toolBarSeparator1);
   toolbar->append(*botBarraInsertar);
   toolbar->append(*botBarraInsertarEnMedio);
   toolbar->append(*botBarraBorrar);
   toolbar->append(*toolBarSeparator2);
   toolbar->append(*botBarraBuscar);
   toolbar->append(*botBarraAscendente);
   toolbar->append(*botBarraDescendente);
   toolbar->append(*toolBarSeparator3);
   toolbar->append(*botBarraPropiedades);
   toolbar->append(*botBarraConvertir);
   image10->set_alignment(0.5,0.5);
   image10->set_padding(0,0);
   image21->set_alignment(0.5,0.5);
   image21->set_padding(0,0);
   image22->set_alignment(0.5,0.5);
   image22->set_padding(0,0);

   // Tabla de calificaciones
   Gtk::VBox *vMainBox = Gtk::manage(new  Gtk::VBox(false, 0));
   tablaCalifas = Gtk::manage(new  Gtk::TreeView());
   Gtk::ScrolledWindow *scrlWinTablaCalifas = Gtk::manage(new  Gtk::ScrolledWindow());
   tablaCalifas->set_flags(Gtk::CAN_FOCUS);
   tablaCalifas->set_headers_visible(true);
   tablaCalifas->set_rules_hint(true);
   tablaCalifas->set_reorderable(true);
   tablaCalifas->set_enable_search(true);
   tablaCalifas->set_border_width( 10 );
   scrlWinTablaCalifas->set_flags(Gtk::CAN_FOCUS);
   scrlWinTablaCalifas->set_shadow_type(Gtk::SHADOW_IN);
   scrlWinTablaCalifas->set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
   scrlWinTablaCalifas->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   scrlWinTablaCalifas->add(*tablaCalifas);

   // Toques finales
   barraEstado = Gtk::manage(new Gtk::Statusbar());
   vMainBox->pack_start(*menubar1, Gtk::PACK_SHRINK, 0);
   vMainBox->pack_start(*toolbar, Gtk::PACK_SHRINK, 0);
   vMainBox->pack_start(*scrlWinTablaCalifas);
   vMainBox->pack_start(*barraEstado, Gtk::PACK_SHRINK, 0);
   this->add(*vMainBox);
   this->set_title( "Califa" );
   this->set_modal( false );
   this->property_window_position().set_value(Gtk::WIN_POS_CENTER);
   this->set_resizable( true );
   this->property_destroy_with_parent().set_value(false);
   Gdk::Geometry geometry;
   geometry.min_height = 400;
   geometry.min_width = 500;
   this->set_geometry_hints( *this, geometry, Gdk::HINT_MIN_SIZE );
   this->show_all();

   // Enlaces de botones
   fill->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_rellenar_activate), false);
   stats->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_stats_activate), false);
   nuevo1->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_nuevo1_activate), false);
   opCerrar->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_opCerrar_activate), false);
   abrir1->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_abrir1_activate), false);
   opGuardar->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_opGuardar_activate), false);
   opGuardarComo->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_opGuardarComo_activate), false);
   importar1->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_importar1_activate), false);
   opMezclar->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_opMezclar_activate), false);
   opConvertir->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_opConvertir_activate), false);
   salir1->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_salir1_activate), false);
   borrar1->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_borrar1_activate), false);
   a__adir1->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_a__adir1_activate), false);
   opInsertarEnMedio->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_insertar_en_medio_activate), false);
   ascendente1->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_ascendente1_activate), false);
   descendente1->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_descendente1_activate), false);
   buscar1->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_buscar1_activate), false);
   buscarNuevo1->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_buscar_de_nuevo1_activate), false);
   propiedades1->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_propiedades1_activate), false);
   informaci__n1->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_informaci__n1_activate), false);
   acerca_de1->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_acerca_de1_activate), false);
   opConvertirParComa->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_convertirNombreAParComa_activate), false);
   opConvertirDeParComa->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_convertirNombreDeParComa_activate), false);
   opVerificarDNIs->signal_activate().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_verificar_dnis_activate), false);
   botBarraGuardar->signal_clicked().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_opGuardar_activate), false);
   botBarraBuscar->signal_clicked().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_buscar1_activate), false);
   botBarraAscendente->signal_clicked().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_ascendente1_activate), false);
   botBarraDescendente->signal_clicked().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_descendente1_activate), false);
   botBarraInsertar->signal_clicked().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_a__adir1_activate), false);
   botBarraInsertarEnMedio->signal_clicked().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_insertar_en_medio_activate), false);
   botBarraBorrar->signal_clicked().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_borrar1_activate), false);
   botBarraPropiedades->signal_clicked().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_propiedades1_activate), false);
   botBarraConvertir->signal_clicked().connect(sigc::mem_fun(*this, &VentanaPpal_glade::on_opConvertir_activate), false);
}

VentanaPpal_glade::~VentanaPpal_glade()
{
}
