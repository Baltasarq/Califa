// ui.h
/*
	Las funciones de progreso del proceso para la interfaz
*/

#include <string>

void ponInicioProgreso();
void ponFinalProgreso();
void ponProgreso(const std::string &tarea, int inic, int prg, int fin);

class VentanaPpal;
extern VentanaPpal *vPpal;
