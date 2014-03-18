// generated 2006/1/9 12:38:31 CET by baltasarq@pcjgarcia.
// using glademm V2.6.0

#ifndef _VENTANAPPAL_HH
#define _VENTANAPPAL_HH

#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/progressbar.h>
#include <memory>

#include "ventanappal_glade.h"
#include "documentocalifa.h"
#include "dlgconvertir.h"


class ColumnasDocumento : public Gtk::TreeModel::ColumnRecord {
public:
	typedef Gtk::TreeModelColumn<unsigned int> ColumnaIndice;
	typedef Gtk::TreeModelColumn<Glib::ustring> * ListaColumnasTipo;
private:
	ColumnaIndice indx;
	ListaColumnasTipo cols;
	unsigned int numCols;
public:
	const ListaColumnasTipo getListaColumnasTexto() const
		{ return cols; }

	const ColumnaIndice &getColumnaIndice() const
		{ return indx; }

	ColumnasDocumento(unsigned int);
	~ColumnasDocumento();
};

class VentanaPpal : public VentanaPpal_glade {
public:
		static const std::string MsgPreparado;
		static const std::string MsgOcupado;
		static const std::string NoHayDoc;
		static const unsigned int NumColumnasFijas = 2;
		static const std::string TitulosColumnasFijas[];

		class PosicionCelda {
		private:
			const Campo *campo;
			unsigned int numFila;
		public:
			PosicionCelda(const Campo *c, unsigned int n)
				{ campo = c; numFila = n; }

			unsigned int getNumFila() const
				{ return numFila ; }

			const Campo *getCampo() const
				{ return campo; }
		};

private:
		Glib::ustring ultimaBusqueda;
		int linUltimaBusqueda;
		const Campo * campoUltimaBusqueda;
		Gtk::Menu *cntxt;
		Gtk::Label *msgEstado;
		Gtk::Label *msgPorcentaje;
		Gtk::ProgressBar *barraProgreso;
		ColumnasDocumento *colsDoc;
		Glib::RefPtr<Gtk::ListStore> refModeloCamposDoc;

		std::string nombreDocumentoActual;
		DocumentoCalifa * documentoActual;

        void on_nuevo1_activate();
		void on_opCerrar_activate();
        void on_abrir1_activate();
        void on_opGuardar_activate();
        void on_opMezclar_activate();
        void on_opGuardarComo_activate();
        void on_importar1_activate();
        void on_opConvertir_activate();
        void on_salir1_activate();
        void on_borrar1_activate();
        void on_a__adir1_activate();
        void on_ascendente1_activate();
        void on_descendente1_activate();
		void on_convertirNombreDeParComa_activate();
		void on_convertirNombreAParComa_activate();
        void on_buscar1_activate();
        void on_buscar_de_nuevo1_activate();
        void on_propiedades1_activate();
        void on_informaci__n1_activate();
		void on_stats_activate();
		void on_rellenar_activate();
        void on_acerca_de1_activate();
		void on_insertar_en_medio_activate();
		void on_verificar_dnis_activate();
		void onColEdited(const Glib::ustring&, const Glib::ustring&, unsigned int);
		void onKeyPressedInCell();
		void on_botMouse(GdkEventButton*);
		bool on_delete_event(GdkEventAny *);

		void uiActiva();
		void uiDesactiva();

		void convertirHTML(const DlgConvertir &dlg, FILE *f);
		void convertirTXT(const DlgConvertir &dlg, FILE *f);
		void convertirCSV(const DlgConvertir &dlg, FILE *f);

		void cambiarNombreDocumentoActual(const std::string & = "");
		void prepararVistaColumnasDocumento();
public:
		static const bool RequierePreguntar = true;
	    static const bool NoRequierePreguntar = false;

		VentanaPpal();
		~VentanaPpal();

		void abrir(const std::string &);

		std::auto_ptr<PosicionCelda> getCeldaActual() const;
		void putCeldaActual(const PosicionCelda &);

		DocumentoCalifa * getDocumentoActual()
			{ return documentoActual; }

		const std::string &getNombreDocumentoActual() const
			{ return nombreDocumentoActual; }

		void guardarDocumentoActual(bool preguntar = RequierePreguntar);

		void refrescaTabla();
		void refrescaTabla(unsigned int);
		void refrescaFila(unsigned int);

		void ponEstado(const std::string &msgEstado);
		void preparaBarraEstado();
		void ponInicioProgreso();
		void ponFinalProgreso();
		void ponProgreso(const std::string &, int, int, int);
};
#endif
