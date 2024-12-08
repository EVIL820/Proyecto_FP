#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMPIAR_PANTALLA system("cls")
#define PAUSA system("pause")

/*****************************************************************************
* Los tipos de datos van en mayusculas 
* Las variables globales la primera letra en mayusculas y el resto en 
* minusculas
* Las variables locales y los parametros en minusculas
* Apuntadores o punteros, funciones y variables van con p_
*****************************************************************************/

/*****************************************************************************
 Definicion de estructuras
*****************************************************************************/
typedef struct struct_producto PRODUCTO; //Definimos el tipo de dato PRODUCTO
struct struct_producto {//Definicion de struct_producto
	int id_producto;
	char nombre_producto[51];
	float precio_compra;
	int existencia;
	float precio_venta;
	PRODUCTO *p_siguiente;
};

typedef struct struct_lst_productos LST_PRODUCTO;//Definimos el tipo de dato LST_PRODUCTO
struct struct_lst_productos {//Definicion de struct_lst_productos
	PRODUCTO *p_inicio;
	PRODUCTO *p_fin;
};

typedef struct struct_producto_venta PRODUCTO_VENTA;//Definimos el tipo de dato PRODUCTO_VENTA
struct struct_producto_venta {//Definicion de struct_producto_venta
	int num_venta;
	int num_producto;
	int cantidad;
	PRODUCTO *p_producto;
	PRODUCTO_VENTA *p_siguiente;
};

typedef struct struct_lst_producto_venta LST_PRODUCTO_VENTA;//Definimos el tipo de dato LST_PRODUCTO_VENTA
struct struct_lst_producto_venta {//Definicion de struct_lst_producto_venta
	PRODUCTO_VENTA *p_inicio;
	PRODUCTO_VENTA *p_fin;
};

typedef struct struct_venta VENTA;//Definimos el tipo de dato VENTA
struct struct_venta {//Definicion de struct_venta
	int num_venta;
	int fecha;
	int hora;
	LST_PRODUCTO_VENTA lista_productos;
	VENTA *p_siguiente;
};

typedef struct struct_lst_venta LST_VENTA;//Definimos el tipo de dato LST_VENTA
struct struct_lst_venta {//Definicion de struct_lst_venta
	VENTA *p_inicio;
	VENTA *p_fin;
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
PRODUCTO *p_nuevo_producto(void);
void agregar_producto(LST_PRODUCTO*,PRODUCTO);
void entrada_producto();

/*** producto venta ***/
PRODUCTO_VENTA *nuevo_producto_venta(void);
void agregar_producto_venta(LST_PRODUCTO_VENTA*,PRODUCTO_VENTA);
LST_PRODUCTO_VENTA entrada_producto_venta(int num_venta);

/*** venta ***/
VENTA *p_nueva_venta(void);
void agregar_venta(LST_VENTA*,VENTA);

/*** menu productos***/
void menu_productos();

/*** menu ventas***/
void menu_ventas();

/*****************************************************************************
Funciones de producto
*****************************************************************************/
PRODUCTO *p_nuevo_producto(void) {
	return (PRODUCTO *) calloc(sizeof(PRODUCTO),1);
}

void agregar_producto(LST_PRODUCTO *p_lista, PRODUCTO producto) {
	PRODUCTO *p_nuevo=p_nuevo_producto();
	*p_nuevo=producto;
	if(p_lista->p_fin!=NULL) {
		p_lista->p_fin->p_siguiente=p_nuevo;
		p_nuevo->p_siguiente=NULL;
		p_lista->p_fin=p_nuevo;
	}
    else{
        p_lista->p_inicio=p_nuevo;
        p_lista->p_fin=p_nuevo;      
    }
}

void entrada_producto(){
    PRODUCTO producto;
    
    printf("ID: ");
    scanf(" %d",&producto.id_producto);
    printf("Nombre del producto: ");
    scanf(" %50[^\n]",producto.nombre_producto);
    printf("Precio de compra: ");
    scanf(" %f",producto.precio_compra);
    printf("Unidades en existencia: ");
    scanf(" %d",producto.existencia);
    printf("Precio de venta: ");
    scanf(" %f",producto.precio_venta);
    
    agregar_producto(&Productos,producto);
}
/*****************************************************************************
 Funciones de producto venta
*****************************************************************************/
PRODUCTO_VENTA *p_nuevo_producto_venta(void){
	return (PRODUCTO_VENTA *) calloc(sizeof(PRODUCTO_VENTA),1);
}

void agregar_producto_venta(LST_PRODUCTO_VENTA *p_lista, PRODUCTO_VENTA producto_venta) {
	PRODUCTO_VENTA *p_nuevo=p_nuevo_producto_venta();
	*p_nuevo=producto_venta;
	if(p_lista->p_fin!=NULL) {
		p_lista->p_fin->p_siguiente=p_nuevo;
		p_nuevo->p_siguiente=NULL;
		p_lista->p_fin=p_nuevo;
	}
    else{
        p_lista->p_inicio=p_nuevo;
        p_lista->p_fin=p_nuevo;      
    }    
}

LST_PRODUCTO_VENTA entrada_producto_venta(int num_venta){
    PRODUCTO_VENTA producto_venta;
    LST_PRODUCTO_VENTA lista_producto_venta;
    char buffer[50];
    
    lista_producto_venta.p_inicio=NULL;
    lista_producto_venta.p_fin=NULL;
    
    producto_venta.num_venta=num_venta;
    do{                    
        printf("Numero de producto: ");
        scanf(" %d",&producto_venta.num_producto);
        printf("Cantidad: ");
        scanf(" %d",&producto_venta.cantidad);
        
        producto_venta.p_producto=NULL;
        producto_venta.p_siguiente=NULL;
        
        agregar_producto_venta(&lista_producto_venta,producto_venta);
        
        printf("Escriba fin para terminar, cualquier otra cosa para agregar un "
                "producto adicional\n");
        scanf(" %s",buffer);
    }while(strcmp("fin",buffer)!=0);
    return lista_producto_venta;
}

/*****************************************************************************
 Funciones de venta
*****************************************************************************/
VENTA *p_nueva_venta(void) {
	return (VENTA *) calloc(sizeof(VENTA),1);
}

void agregar_venta(LST_VENTA *p_lista, VENTA venta) {
	VENTA *p_nuevo=p_nueva_venta();
	*p_nuevo=venta;
	if(p_lista->p_fin!=NULL) {
		p_lista->p_fin->p_siguiente=p_nuevo;
		p_nuevo->p_siguiente=NULL;
		p_lista->p_fin=p_nuevo;
	}
    else{
        p_lista->p_inicio=p_nuevo;
        p_lista->p_fin=p_nuevo;      
    }    
}

void entrada_venta(){
    VENTA venta;
    
    printf("Numero de venta: ");
    scanf(" %d",&venta.num_venta);
    printf("Fecha de venta: ");
    scanf(" %d",&venta.fecha);
    printf("Hora de venta: ");
    scanf(" %d",&venta.hora);
    
    venta.lista_productos=entrada_producto_venta(venta.num_venta);
    agregar_venta(&Ventas,venta);
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
                entrada_venta();
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
		printf("\n2. Menu Ventas");
		printf("\n3. Guardar todos los datos");
		printf("\n4. Salir");
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
