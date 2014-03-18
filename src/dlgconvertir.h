// generated 2006/9/20 11:25:06 CEST by baltasarq@pcjgarcia.(none)
// using glademm V2.6.0

#ifndef _DLGCONVERTIR_HH
#define _DLGCONVERTIR_HH

#include <gtkmm/checkbutton.h>
#include <string>

#include "dlgconvertir_glade.h"

class DocumentoCalifa;

class DlgConvertir : public DlgConvertir_glade {
public:
    typedef std::vector<Gtk::CheckButton *> ListaBotonesChk;

    static const std::string CnvtCSV;
    static const std::string CnvtHTML;
    static const std::string CnvtTXT;

    static const std::string EtqExtCsv;
    static const std::string EtqExtTxt;
    static const std::string EtqExtHtml;

    DlgConvertir(Gtk::Window &parent, const std::string &nombreDoc, DocumentoCalifa *);

    void on_listaConversion_editing_done();
    void on_listaConversion_changed();
    void on_botBuscar_clicked();
    void on_botAceptar_clicked();
    void on_botEditar_clicked();
    void on_botCancelar_clicked();
    void on_botSaltoLinDOS_toggled();

    char getSeparadorDecimal() const;
    char getSeparadorCampos() const;
    const ListaBotonesChk &getListaBotonesChk() const
        { return listaBotonesChk; }
    void pasarSeleccionADoc();

    const std::string * getCurrentExt();
    void ponNombreArchivo(const std::string &nf);
private:
    ListaBotonesChk listaBotonesChk;
    DocumentoCalifa *doc;
};
#endif
