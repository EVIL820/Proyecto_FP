#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Estructuras
struct Producto {
	int id_prod;
	char nom_prod[50];
	float precio_compra_prod;
	int existencia_prod;
	float precio_venta_prod;
	struct Producto *sig;
};

struct Cliente {
	int id_cli;
	char nom_cli[50];
	char tel_cli[15];
	struct Cliente *sig;
};

struct Venta {
	int num_vta;
	char fecha_vta[20];
	char hora_vta[10];
	int num_cli;
	float total_vta;
	struct Venta *sig;
};

struct DetalleVta {
	int num_vta;
	int num_prod;
	int cant_prod;
	float subtotal;
	struct DetalleVta *sig;
};

// Prototipos
void inicializarArchivos();
void cargarDatos();
void guardarDatos();
void agregarProducto();
void agregarCliente();
void agregarVenta();
void generarDetalleVta();
void listarProductos();
void listarClientes();
void listarVentas();

// Variables globales
struct Producto *productos = NULL;
struct Cliente *clientes = NULL;
struct Venta *ventas = NULL;
struct DetalleVta *detallesVta = NULL;

// Función principal
int main() {
	int opcion;
	inicializarArchivos();
	cargarDatos();

	do {
		printf("Menu");
		printf("\n1. Agregar Producto");
		printf("\n2. Agregar Cliente");
		printf("\n3. Agregar Venta");
		printf("\n4. Generar Detalle Venta");
		printf("\n5. Listar Productos");
		printf("\n6. Listar Clientes");
		printf("\n7. Listar Ventas");
		printf("\n8. Guardar y Salir");
		printf("\nOpcion: ");
		scanf("%d", &opcion);

		switch (opcion) {
			case 1:
				agregarProducto();
				break;
			case 2:
				agregarCliente();
				break;
			case 3:
				agregarVenta();
				break;
			case 4:
				generarDetalleVta();
				break;
			case 5:
				listarProductos();
				break;
			case 6:
				listarClientes();
				break;
			case 7:
				listarVentas();
				break;
			case 8:
				guardarDatos();
				break;
			default:
				printf("Opcion invalida\n");
		}
		system("pause");
		system("cls");
	} while (opcion != 8);

	return 0;
}