// nota.h
/*
    Conversiones de notas tipo, cadena a nums. y viceversa.
*/


#ifndef NOTA_H_INCLUDED
#define NOTA_H_INCLUDED

#include <string>

/** Clase Nota
 *  Lleva todos los posibles valores de notas y conversiones
 */
class Nota {
public:
	enum NotaConceptual {
		NoPresentado, Suspenso, Aprobado, Notable, Sobresaliente,
		MatriculaHonor, Error
	};

	/// Notas tipo equivalentes a las anteriores, en num.
	/// @see NotaConceptual
	static double vNumNotasTipo[];

	/// Notas tipo equivalentes a la nota conceptual, como cadena
	/// @see NotaConceptual
	static const std::string vStrNotasTipo[];

	/// Pasa de nota tipo a num. ordinal
	/// @see NotaConceptual
	static unsigned int getOrdinal(NotaConceptual n)
		{ return (unsigned int) n; }

	/// Pasa de ordinal a nota tipo
	/// @see NotaConceptual
	static NotaConceptual getNotaConceptualDeEntero( unsigned int i )
		{ return (NotaConceptual) i; }

	/// Pasa de nota numérica a nota tipo
	/// @see NotaConceptual
	static NotaConceptual cnvtNotaTipo(double nota);

	/// Pasa de nota tipo a cadena
	/// @see NotaConceptual
	static const std::string &cnvtTipoNotaStr(NotaConceptual);

	/// Pasa de nota numérica a conceptual (cadena de vStrNotasTipo)
	/// @see vStrNotasTipo
	static const std::string &cnvtNotaStr(double nota);

	/// Pasa de nota conceptual (cadena) a numérica
	/// @see NotaConceptual, vStrNotasTipo
	static double cnvtStrNota(const std::string &nota);

	/// Pasa de nota tipo a numérica
	/// @see NotaConceptual
	static double cnvtTipoNota(NotaConceptual nota);

	/// Pasa de nota conceptual (cadena) a nota tipo
	/// @see NotaConceptual, vStrNotasTipo
	static NotaConceptual cnvtStrNotaConceptual(const std::string &nota);
};


#endif // NOTA_H_INCLUDED
