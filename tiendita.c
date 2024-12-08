#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMPIAR_PANTALLA system("cls")
#define PAUSA system("pause")

/*****************************************************************************
 Definicion de estructuras
*****************************************************************************/
typedef struct struct_producto PRODUCTO;
struct struct_producto {
	int id_producto;
	char nombre_producto[51];
	float precio_compra;
	int existencia;
	float precio_venta;
	PRODUCTO *siguiente;
};

typedef struct struct_lst_productos LST_PRODUCTO;
struct struct_lst_productos {
	PRODUCTO *inicio;
	PRODUCTO *fin;
};

typedef struct struct_producto_venta PRODUCTO_VENTA;
struct struct_producto_venta {
	int num_venta;
	int num_producto;
	int cantidad;
	PRODUCTO *producto;
	PRODUCTO_VENTA *siguiente;
};

typedef struct struct_lst_producto_venta LST_PRODUCTO_VENTA;
struct struct_lst_producto_venta {
	PRODUCTO_VENTA *inicio;
	PRODUCTO_VENTA *fin;
};

typedef struct struct_venta VENTA;
struct struct_venta {
	int num_venta;
	int fecha;
	int hora;
	LST_PRODUCTO_VENTA lista_productos;
	VENTA *siguiente;
};

typedef struct struct_lst_venta LST_VENTA;
struct struct_lst_venta {
	VENTA *inicio;
	VENTA *fin;
};

/*****************************************************************************
 Variables globales
*****************************************************************************/

LST_PRODUCTO Productos;
LST_VENTA Ventas;

/*****************************************************************************
 Funciones prototipo
*****************************************************************************/

/*** producto ***/
PRODUCTO *nuevo_producto(void);
void agregar_producto(LST_PRODUCTO*,PRODUCTO);

/*** producto venta ***/
PRODUCTO_VENTA *nuevo_producto_venta(void);
void agregar_producto_venta(LST_PRODUCTO_VENTA*,PRODUCTO_VENTA);

/*** venta ***/
VENTA *nueva_venta(void);
void agregar_venta(LST_VENTA*,VENTA);

/*** menu productos***/
void menu_productos();

/*** menu ventas***/
void menu_ventas();

/*****************************************************************************
Funciones de producto
*****************************************************************************/
PRODUCTO *nuevo_producto(void) {
	return (PRODUCTO *) calloc(sizeof(PRODUCTO),1);
}

void agregar_producto(LST_PRODUCTO *lista, PRODUCTO producto) {
	PRODUCTO *nuevo=nuevo_producto();
	*nuevo=producto;
	if(lista->fin!=NULL) {
		lista->fin->siguiente=nuevo;
		nuevo->siguiente=NULL;
		lista->fin=nuevo;
	}
}

/*****************************************************************************
 Funciones de producto venta
*****************************************************************************/
PRODUCTO_VENTA *nuevo_producto_venta(void) {
	return (PRODUCTO_VENTA *) calloc(sizeof(PRODUCTO_VENTA),1);
}

void agregar_producto_venta(LST_PRODUCTO_VENTA *lista, PRODUCTO_VENTA producto_venta) {
	PRODUCTO_VENTA *nuevo=nuevo_producto_venta();
	*nuevo=producto_venta;
	if(lista->fin!=NULL) {
		lista->fin->siguiente=nuevo;
		nuevo->siguiente=NULL;
		lista->fin=nuevo;
	}
}

/*****************************************************************************
 Funciones de venta
*****************************************************************************/
VENTA *nuevo_venta(void) {
	return (VENTA *) calloc(sizeof(VENTA),1);
}

void agregar_venta(LST_VENTA *lista, VENTA venta) {
	VENTA *nuevo=nuevo_venta();
	*nuevo=venta;
	if(lista->fin!=NULL) {
		lista->fin->siguiente=nuevo;
		nuevo->siguiente=NULL;
		lista->fin=nuevo;
	}
}

/*****************************************************************************
 Menu productos
*****************************************************************************/
void menu_productos() {
	int opcion;
	do {
		LIMPIAR_PANTALLA;
		printf("Menu productos");
		printf("\n1. Agregar producto");
		printf("\n2. Borrar producto");
		printf("\n3. Buscar producto");
		printf("\n4. Listar productos");
		printf("\n5. Guardar productos");
		printf("\n6. Regresar a menu principal");
		printf("\nIngresa tu opcion: ");
		scanf(" %d", &opcion);
		switch (opcion) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				printf("Volviendo al menu principal");
				break;
			default:
				printf("\nOpcion invalida\n presiona una tecla para continuar");
				break;
		}
		PAUSA;
	} while (opcion != 6);
}

/*****************************************************************************
 Menu productos_venta
*****************************************************************************/
void menu_ventas() {
	int opcion;
	do {
		LIMPIAR_PANTALLA;
		printf("Menu ventas");
		printf("\n1. Agregar venta");
		printf("\n2. Borrar venta");
		printf("\n3. Buscar venta");
		printf("\n4. Listar ventas");
		printf("\n5. Generar Detalle Venta");
		printf("\n6. Regresar a menu principal");
		printf("\nIngresa tu opcion: ");
		scanf(" %d",&opcion);
		switch (opcion) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				printf("Volviendo al menu principal");
				break;
			default:
				printf("\nOpcion invalida\n presiona una tecla para continuar");
				break;
		}
		PAUSA;
	} while(opcion!=6);
}

/*****************************************************************************
 Funcion principal
*****************************************************************************/
int main() {
	int opcion;

	do {
		LIMPIAR_PANTALLA;
		printf("Menu principal");
		printf("\n1. Menu Productos");
		printf("\n2. Menu Clientes");
		printf("\n3. Menu Ventas");
		printf("\n4. Guardar todos los datos");
		printf("\n5. Salir");
		printf("\nOpcion: ");
		scanf("%d", &opcion);

		switch (opcion) {
			case 1:
				menu_productos();
				break;
			case 2:
				menu_ventas();
				break;
			case 3:
				//guardarDatos();
				break;
			case 4:
				printf("Saliendo del programa. Tenga buen dia.");
				break;
			default:
				printf("Opcion invalida\n");
				PAUSA;
				break;
		}
		PAUSA;
	} while (opcion != 4);

	return 0;
}
