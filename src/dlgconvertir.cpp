// generated 2006/9/20 11:25:06 CEST by baltasarq@pcjgarcia.(none)
// using glademm V2.6.0

#include "config.h"
#include "dlgconvertir.h"
#include "gtk_uintf.h"
#include "documentocalifa.h"
#include "fileman.h"
#include "reservadas.h"

const std::string DlgConvertir::CnvtCSV    = "Convertir a CSV";
const std::string DlgConvertir::CnvtHTML   = "Convertir a HTML";
const std::string DlgConvertir::CnvtTXT    = "Convertir a texto plano";
const std::string DlgConvertir::EtqExtCsv  = ".csv";
const std::string DlgConvertir::EtqExtHtml = ".html";
const std::string DlgConvertir::EtqExtTxt  = ".txt";

DlgConvertir::DlgConvertir(Gtk::Window &parent, const std::string &nombreDoc, DocumentoCalifa *doc)
    : DlgConvertir_glade( parent )
{
	Gtk::CheckButton * chk;
	std::string nombre = FileMan::replaceExt( nombreDoc, EtqExtCsv );

	// Inic
	this->set_title( NombreApp );
	this->set_icon( parent.get_icon() );
	ponNombreArchivo( nombre );

	// La lista de conversiones
	listaConversion->append( CnvtCSV );
	listaConversion->append( CnvtHTML );
	listaConversion->append( CnvtTXT );
	listaConversion->set_active( 0 );

	// Los separadores de campos
	listaSepCampos->set_active_text( "," );
	listaSepCampos->append( "," );
	listaSepCampos->append( ";" );
	listaSepCampos->append( "\\b <SPACE>" );
	listaSepCampos->append( "\\t <TAB>" );

	// Los separadores decimales
	listaSepDecimal->set_active_text( "," );
	listaSepDecimal->append( "." );
	listaSepDecimal->append( "," );

	// Poner la lista de chks para los campos
	for(unsigned int i = 0; i < doc->getListaCampos().size(); ++i) {
		chk = Gtk::manage(
				new class Gtk::CheckButton( doc->getListaCampos()[ i ]->nombre )
		);
		cajaListaCampos->pack_start( *chk, Gtk::PACK_SHRINK, 0 );
		chk->set_active();
		chk->show();
	}

	// Recordar el documento
	this->doc = doc;
}

void DlgConvertir::on_listaConversion_changed()
{
	// Si la conversión es a HTML o a TXT, ocultar las opciones de CSV
	// Cambiar la extensión del archivo
	const std::string * currentExt = getCurrentExt();

	if ( currentExt == &EtqExtCsv ) {
		cajaOpsCSV->show();
		separador->show();
	}
	else
	if ( currentExt == &EtqExtHtml ) {
		cajaOpsCSV->hide();
		separador->hide();
	}
	else
	if ( currentExt == &EtqExtTxt ) {
		cajaOpsCSV->hide();
		separador->hide();
	}

	ponNombreArchivo(
			FileMan::replaceExt( edNombreArchivo->get_text(), *currentExt )
    );
}

const std::string * DlgConvertir::getCurrentExt()
{
    const std::string * toret = &EtqExtCsv;

	if ( listaConversion->get_active_text() == CnvtCSV ) {
		toret = &EtqExtCsv;
	}
	else
	if ( listaConversion->get_active_text() == CnvtHTML ) {
		toret = &EtqExtHtml;
	}
	else
	if ( listaConversion->get_active_text() == CnvtTXT ) {
		toret = &EtqExtTxt;
	}

    return toret;
}

void DlgConvertir::ponNombreArchivo(const std::string &nf)
{
    edNombreArchivo->set_text( nf );
    edNombreArchivo->set_position( nf.length() );
}

void DlgConvertir::on_botBuscar_clicked()
{
	std::string path = pideNombreDirectorioAbrir( *this, "Guardar como...",
                        FileMan::getPath( edNombreArchivo->get_text() )
    );

	if ( !path.empty() ) {
	    std::string nomFich = FileMan::getOnlyFileName( edNombreArchivo->get_text() )
                            + FileMan::getExt( edNombreArchivo->get_text() )
        ;
		ponNombreArchivo( path + FileMan::getPathSeparator() + nomFich );
	}
}

void DlgConvertir::on_botSaltoLinDOS_toggled()
{
}

void DlgConvertir::on_botCancelar_clicked()
{
}

void DlgConvertir::on_botAceptar_clicked()
{
    char sepDecimal = getSeparadorDecimal();
    char sepCampos  = getSeparadorCampos();

    if ( sepDecimal == sepCampos ) {
        ponMsgError( *this, "Separador decimal y separador de campos no pueden ser iguales." );
        response( Gtk::RESPONSE_NONE );
    }
}

char DlgConvertir::getSeparadorDecimal() const
{
	char toret;
	Glib::ustring sep = ((Gtk::Entry *)listaSepDecimal->get_child() )->get_text();

	if ( !sep.empty() )
			toret = sep[ 0 ];
	else	toret = '.';

	return toret;
}

char DlgConvertir::getSeparadorCampos() const
{
	char toret;
	Glib::ustring sep = ((Gtk::Entry *)listaSepCampos->get_child() )->get_text();

	if ( !sep.empty() ) {
			if ( sep[0] == '\\'
			  && sep[1] == 't' ) {
				  toret = '\t';
			}
			else
			if ( sep[0] == '\\'
			  && sep[1] == 'b' ) {
				  toret = ' ';
			}
			else toret = sep[0];
	}
	else	toret = ',';

	return toret;
}

void DlgConvertir::pasarSeleccionADoc()
{
	for(unsigned int i = 0; i < doc->getListaCampos().size(); ++i) {
		doc->getListaCampos()[ i ]->estaOculta =
			!( ( (Gtk::CheckButton *)
				( (std::vector<Gtk::Widget *>)
					cajaListaCampos->get_children() )[ i ] )
				->get_active() );
	}
}

void DlgConvertir::on_botEditar_clicked()
{
}
