// importar.cpp
/*
    Módulo para importar de un archivo de texto o CSV
*/

#include <cctype>
#include <vector>

#include "importar.h"
#include "fileio.h"
#include "campoinfo.h"

bool Importar::importa()
{
    std::vector<std::string> dnis;
    std::vector<std::string> nombres;

    std::string lin;
    std::auto_ptr<StringLexer> lex;
    bool toret = false;
    InputFile f( nombreArchivo );

    if ( f.isOpen() ) {
        f.readLn( lin );
        while ( !f.isEof() ) {
            lex.reset( new StringLexer( &lin ) );

            // Leer el DNI
            std::string dni = lex->getNumber();
            std::string nombre;

            if ( !dni.empty() ) {
                // Pasar la letra del NIF, si está presente
                if ( esNif( lin, *lex ) ) {
                    dni += lex->getCurrentChar();
                    lex->advance();
                }

                // Pasar la coma o punto y coma, si existen
                lex->skipDelim();
                if ( esSeparador( lex->getCurrentChar() ) ) {
                    lex->advance();
                    lex->skipDelim();
                }

                // Tomar el nombre
                if ( lex->getCurrentChar() == '"' ) {
                    lex->advance();
                    nombre = lex->getLiteral( "\"" );
                } else {
                    nombre = lin.erase( 0, lex->getCurrentPos() );
                }
            }
            else break;

            // Guardar y avanzar
            dnis.push_back( dni );
            nombres.push_back( nombre );
            f.readLn( lin );
        }

        toret = ( construir( dnis, nombres ) != NULL );
    }

    return toret;
}

bool Importar::esNif(const std::string &lin, Lexer &lex)
{
    bool toret = false;
    unsigned int pos = lex.getCurrentPos();

    if ( std::isalpha( lex.getCurrentChar() ) ) {
        lex.advance();

        if ( Lexer::StandardDelimiters.find( lex.getCurrentChar() ) != std::string::npos
          || this->esSeparador( lex.getCurrentChar() ) )
        {
            toret = true;
        }
    }

    lex.reset( pos );
    return toret;
}

bool Importar::esSeparador(char c)
{
    return ( c == ';' || c == ',' );
}

DocumentoCalifa * Importar::construir(const std::vector<std::string> & dnis,
                            const std::vector<std::string> & nombres)
{
    try {
        doc = new DocumentoCalifa();

        // Preparar el campo DNI
        doc->ponEnCarga();
        CampoDni * cDni = doc->getCampoDNI();

        // Preparar el campo nombre
        Campo * cNom = new CampoInfo( doc );
        cNom->nombre = DocumentoCalifa::NombrePredNombre;
        doc->insertaNuevoCampo( cNom );
        doc->intercambiarPosicionesCampos(
                doc->getListaCampos().size() - 1,
                doc->getListaCampos().size() - 2
        );

        // Introducir todos los dni's
        for(unsigned int i = 0; i < dnis.size(); ++i) {
            cDni->annade();
            cDni->putValor( i, dnis[ i ] );

            cNom->annade();
            cNom->putValor( i, nombres[ i ] );
        }

        cDni->normalizarNumFilas();
        cNom->normalizarNumFilas();
        doc->getCampoNotaFinal()->normalizarNumFilas();
        doc->ponEnCarga( false );
    } catch(...) {
        doc = NULL;
    }

    return doc;
}
