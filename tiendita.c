#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMPIAR_PANTALLA system("cls")
#define PAUSA system("pause")

/*****************************************************************************
 Definicion de estructuras
*****************************************************************************/
typedef struct struct_producto PRODUCTO;
struct struct_producto{
	int id_producto;
	char nombre_producto[51];
	float precio_compra;
	int existencia;
	float precio_venta;
	tipo_st_producto *siguiente;
};

typedef struct struct_lst_productos LST_PRODUCTO;
struct struct_lst_productos{
	tipo_st_producto *inicio;
	tipo_st_producto *fin;
};

typedef struct struct_producto_venta PRODUCTO_VENTA;
struct struct_producto_venta{
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
struct struct_venta{
	int num_venta;
	int fecha;
	int hora;
	LST_PRODUCTO_VENTA lista_productos;
	VENTA *siguiente;
};

typedef struct struct_lst_venta LST_VENTA;
struct struct_lst_venta{
	VENTA *inicio;
	VENTA *fin;
};

/*****************************************************************************
 Variables globales
*****************************************************************************/
LST_PRODUCTO Productos;
LST_VENTA Ventas;


