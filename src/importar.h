// importar.cpp
/*
    Módulo para importar de un archivo de texto o CSV
*/

#ifndef IMPORTAR_H_INCLUDED
#define IMPORTAR_H_INCLUDED

#include <string>

#include "lex.h"
#include "documentocalifa.h"

class Importar {
public:
    Importar(const std::string &n)
        : nombreArchivo( n ), doc( NULL )
    {}

    bool importa();

    DocumentoCalifa * getDocumento()
        { importa(); return doc; }

    bool esSeparador(char c);
    bool esNif(const std::string &, Lexer &);
private:
    std::string nombreArchivo;
    DocumentoCalifa * doc;

    DocumentoCalifa * construir(const std::vector<std::string> &,
                              const std::vector<std::string> &
    );
};

#endif // IMPORTAR_H_INCLUDED
