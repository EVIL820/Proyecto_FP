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
	PRODUCTO *siguiente;
};

typedef struct struct_lst_productos LST_PRODUCTO;
struct struct_lst_productos{
	PRODUCTO *inicio;
	PRODUCTO *fin;
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

/*****************************************************************************
Funciones de producto
*****************************************************************************/
PRODUCTO *nuevo_producto(void){
    return (PRODUCTO *) calloc(sizeof(PRODUCTO),1);
}

void agregar_producto(LST_PRODUCTO *lista, PRODUCTO producto){
    PRODUCTO *nuevo=nuevo_producto();
    *nuevo=*producto;
    if(lista->fin!=NULL){
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

void agregar_producto_venta(LST_PRODUCTO_VENTA *lista, PRODUCTO_VENTA producto_venta){
    PRODUCTO_VENTA *nuevo=nuevo_producto_venta();
    *nuevo=*producto_venta;
    if(lista->fin!=NULL){
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

void agregar_venta(LST_VENTA *lista, VENTA venta){
    VENTA *nuevo=nuevo_venta();
    *nuevo=*venta;
    if(lista->fin!=NULL){
        lista->fin->siguiente=nuevo;
        nuevo->siguiente=NULL;
        lista->fin=nuevo;
    }
}