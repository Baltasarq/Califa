// generated 2006/1/5 12:54:39 CET by baltasarq@pcjgarcia.(none)
// using glademm V2.6.0

#include <config.h>
#include <gtkmm/main.h>
#include <string>

#include "ventanappal.h"
#include "gtk_uintf.h"
#include "reservadas.h"

VentanaPpal *vPpal = NULL;

int main(int argc, char **argv)
{
    Gtk::Main m( &argc, &argv );

    vPpal = new(std::nothrow) VentanaPpal();

	if ( vPpal != NULL ) {
		try {
		 	if ( argc > 1 ) {
				vPpal->abrir( std::string( argv[ 1 ] ) );
			}

    		m.run( *vPpal );
		} catch(...) {
			ponMsgError( *vPpal, "FATAL: Error inesperado" );
		}

		delete vPpal;
	}
	else ponMsgError( "No hay memoria para ejecutar la aplicación" );

    return 0;
}
