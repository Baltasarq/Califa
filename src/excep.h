// excep.h
/*
	Las posibles excepciones que puede generar la aplicación.
*/

#ifndef EXCEP_H__
#define EXCEP_H__

#include <cstring>
#include <string>
#include <stdexcept>

class Error: public std::runtime_error {
public: static const int MaxLonDetalles = 256;
protected:
	char detalles[MaxLonDetalles];

	Error(const char * msg, const char * det)
			: std::runtime_error( msg )
		{ std::strncpy( detalles, det, MaxLonDetalles - 1 ); }

public:
	virtual ~Error() throw()
		{}

	const char * getMsg() const
		{ return what(); }

	const char * getDetalles() const
		{ return detalles; }

	std::string toString() const
		{ return ( std::string( getMsg() )
				  + '(' + std::string( getDetalles() ) + ')' );
		}
};

class FmtError : public Error {
public:
		FmtError(const char * d) : Error( "Formato incorrecto", d )
		{}

		FmtError(const std::string &d) : Error( "Formato incorrecto", d.c_str() )
		{}
};

class IndiceIncorrectoError : public Error {
public:
		IndiceIncorrectoError(const char * d) : Error( "Indice incorrecto", d )
		{}

		IndiceIncorrectoError(const std::string &d) : Error( "Indice incorrecto", d.c_str() )
		{}
};

class InconsistenciaError : public Error {
public:
		InconsistenciaError(const char * d) : Error( "No tiene sentido", d )
		{}

		InconsistenciaError(const std::string &d) : Error( "No tiene sentido", d.c_str() )
		{}
};

class InternoError : public Error {
protected:
	InternoError(const char * m, const char * d) : Error( m, d )
		{}
public:
	InternoError(const char * d) : Error( "Error Interno", d )
		{}

		InternoError(const std::string &d) : Error( "Error Interno", d.c_str() )
		{}
};

class SinMemoriaError : public InternoError {
public:
	SinMemoriaError(const char * d) : InternoError( "Sin memoria", d )
		{}

	SinMemoriaError(const std::string &d) : InternoError( "Sin memoria", d.c_str() )
		{}
};


#endif
