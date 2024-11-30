#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para Producto
struct Producto {
	int id_prod;
	char nom_prod[50];
	float precio_compra_prod;
	int existencia_prod;
	float precio_venta_prod;
	struct Producto *sig;
};
struct Producto *ini_prod = NULL, *fin_prod = NULL, *aux_prod = NULL;

// Estructura para Cliente
struct Cliente {
	int id_cli;
	char nom_cli[50];
	char tel_cli[15];
	struct Cliente *sig;
};
struct Cliente *ini_cli = NULL, *fin_cli = NULL, *aux_cli = NULL;

// Estructura para Venta
struct Venta {
	int num_vta;
	char fecha_vta[20];
	char hora_vta[10];
	int num_cli;
	struct Venta *sig;
};
struct Venta *ini_vta = NULL, *fin_vta = NULL, *aux_vta = NULL;

// Estructura para DetalleVta
struct DetalleVta {
	int num_vta;
	int num_prod;
	int cant_prod;
	struct DetalleVta *sig;
};
struct DetalleVta *ini_det = NULL, *fin_det = NULL, *aux_det = NULL;

void agrega();

int main() {

	return 0;
}
