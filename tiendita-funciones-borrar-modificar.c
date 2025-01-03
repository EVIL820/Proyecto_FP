#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMPIAR_PANTALLA system("cls")
#define PAUSA system("pause")
#define F_NOM_PRODUCTOS "Productos.txt"
#define F_NOM_VENTAS "Ventas.txt"
#define F_NOM_DETALLE_VENTAS "Detalle-ventas.txt"

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
	char nombre_producto[101];
	float precio_compra;
	int existencia;
	float precio_venta;
	PRODUCTO *p_siguiente;
	PRODUCTO *p_anterior;
};

typedef struct struct_lst_productos LST_PRODUCTO;//Definimos el tipo de dato LST_PRODUCTO
struct struct_lst_productos {//Definicion de struct_lst_productos
	PRODUCTO *p_inicio;
	PRODUCTO *p_fin;
};

typedef struct struct_detalle_venta DETALLE_VENTA;//Definimos el tipo de dato DETALLE_VENTA
struct struct_detalle_venta {//Definicion de struct_detalle_venta
	int num_venta;
	int num_producto;
	int cantidad;
	PRODUCTO *p_producto;
	DETALLE_VENTA *p_siguiente;
};

typedef struct struct_lst_detalle_venta LST_DETALLE_VENTA;//Definimos el tipo de dato LST_DETALLE_VENTA
struct struct_lst_detalle_venta {//Definicion de struct_lst_detalle_venta
	DETALLE_VENTA *p_inicio;
	DETALLE_VENTA *p_fin;
};

typedef struct struct_venta VENTA;//Definimos el tipo de dato VENTA
struct struct_venta {//Definicion de struct_venta
	int num_venta;
	int fecha;
	int hora;
	//LST_DETALLE_VENTA lista_productos;
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
LST_DETALLE_VENTA Detalles;

/*****************************************************************************
 Funciones prototipo
*****************************************************************************/

/*** producto ***/
PRODUCTO *p_nuevo_producto(void);
void agregar_producto(LST_PRODUCTO*,PRODUCTO);
void entrada_producto(void);
void mostrar_producto(PRODUCTO);
void mostrar_lista_producto(LST_PRODUCTO);
PRODUCTO *buscar_producto(LST_PRODUCTO lista,int id_producto, PRODUCTO **p_anterior);
void mostrar_busqueda_producto();
void leer_archivo_producto(void);
void guardar_archivo_producto(void);
void limpiar_lista_producto(LST_PRODUCTO*);
void borrar_producto();
void modificar_producto();

/*** detalle venta ***/
DETALLE_VENTA *p_nuevo_detalle_venta(void);
void agregar_detalle_venta(LST_DETALLE_VENTA*,DETALLE_VENTA);
void entrada_detalle_venta(int num_venta);
void mostrar_detalle_venta(DETALLE_VENTA);
void mostrar_lista_detalle_venta(LST_DETALLE_VENTA);
void mostrar_lista_detalle_venta_por_num(LST_DETALLE_VENTA,int);
void leer_archivo_detalle_venta(void);
void limpiar_lista_detalle_venta(LST_DETALLE_VENTA*);
void guardar_archivo_detalle_venta();

/*** venta ***/
VENTA *p_nueva_venta(void);
void agregar_venta(LST_VENTA*,VENTA);
void entrada_venta();
void mostrar_venta(VENTA);
void mostrar_lista_venta(LST_VENTA);
void leer_archivo_venta(void);
void guardar_archivo_venta(void);
void limpiar_lista_venta(LST_VENTA*);


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
	p_nuevo->p_siguiente=NULL;

	if(p_lista->p_fin!=NULL) {
		p_lista->p_fin->p_siguiente=p_nuevo;
		p_nuevo->p_siguiente=NULL;
		p_lista->p_fin=p_nuevo;
	} else {
		p_lista->p_inicio=p_nuevo;
		p_lista->p_fin=p_nuevo;
	}
}

void entrada_producto() {
	PRODUCTO producto;

	printf("ID: ");
	scanf(" %d",&producto.id_producto);
	printf("Nombre del producto: ");
	scanf(" %100[^\n]",producto.nombre_producto);
	printf("Precio de compra: ");
	scanf(" %f",&producto.precio_compra);
	printf("Unidades en existencia: ");
	scanf(" %d",&producto.existencia);
	printf("Precio de venta: ");
	scanf(" %f",&producto.precio_venta);

	agregar_producto(&Productos,producto);
}

void mostrar_producto(PRODUCTO producto) {
	printf("%d\t%s\t%.2f\t%d\t%.2f\n", producto.id_producto, producto.nombre_producto, producto.precio_compra,
	       producto.existencia, producto.precio_venta);
}

PRODUCTO *buscar_producto(LST_PRODUCTO lista,int id_producto, PRODUCTO **p_anterior) {
	PRODUCTO *p_actual=lista.p_inicio;

	if (p_anterior != NULL)
		*p_anterior = NULL;

	while(p_actual!=NULL) {
		if(p_actual->id_producto==id_producto)
			return (PRODUCTO *)p_actual;

		if (p_anterior != NULL)
			*p_anterior = p_actual;

		p_actual=p_actual->p_siguiente;
	}
	return NULL;
}

void mostrar_lista_producto(LST_PRODUCTO lista) {
	PRODUCTO *p_actual=lista.p_inicio;

	while(p_actual!=NULL) {
		mostrar_producto(*p_actual);
		p_actual=p_actual->p_siguiente;
	}
}

void mostrar_busqueda_producto() {
	PRODUCTO *p_actual=NULL;
	int id_producto;
	printf("Ingrese el ID del producto: ");
	scanf("%d",&id_producto);
	p_actual=buscar_producto(Productos,id_producto, NULL);
	if(p_actual!=NULL)
		mostrar_producto(*p_actual);
}

void borrar_producto() {
	PRODUCTO *p_actual = NULL, *p_anterior = NULL;
	int id_producto;

	printf("Ingrese el ID del producto a eliminar: ");
	scanf("%d", &id_producto);

	p_actual = buscar_producto(Productos, id_producto, &p_anterior);

	if (p_actual == NULL) {
		printf("Producto no encontrado.\n");
		return;
	}

	if (p_anterior == NULL) {
		Productos.p_inicio = p_actual->p_siguiente;
	} else {
		p_anterior->p_siguiente = p_actual->p_siguiente;
	}

	free(p_actual);
	printf("Producto borrado con exito.\n");
}

void modificar_producto() {
	PRODUCTO *p_actual = NULL;
	int id_producto;
	int opcion;

	printf("Ingrese el ID del producto a modificar: ");
	scanf("%d", &id_producto);

	p_actual = buscar_producto(Productos, id_producto, NULL);

	if (p_actual != NULL) {
		do {
			LIMPIAR_PANTALLA;
			printf("Seleccione que desea modificar:\n");
			printf("1. Nombre del producto\n");
			printf("2. Precio de compra\n");
			printf("3. Existencia\n");
			printf("4. Precio de venta\n");
			printf("5. Volver al menu productos\n");
			printf("Opcion: ");
			scanf("%d", &opcion);

			switch (opcion) {
				case 1:
					printf("Ingrese el nuevo nombre del producto: ");
					scanf(" %[^\n]", p_actual->nombre_producto);
					break;
				case 2:
					printf("Ingrese el nuevo precio de compra del producto: ");
					scanf(" %f", &p_actual->precio_compra);
					break;
				case 3:
					printf("Ingrese la nueva existencia del producto: ");
					scanf(" %d", &p_actual->existencia);
					break;
				case 4:
					printf("Ingrese el nuevo precio de venta del producto: ");
					scanf(" %f", &p_actual->precio_venta);
					break;
				case 5:
					printf("Volviendo al menu productos\n");
					break;
				default:
					printf("Opcion no valida.\n");
					return;
			}
			if (opcion >= 1 && opcion <= 4) {
				printf("Producto modificado con exito.\n");
				PAUSA;
			}
		} while(opcion!=5);
	} else {
		printf("Producto no encontrado.\n");
	}
}

void leer_archivo_producto(void) {
	FILE *p_archivo;
	PRODUCTO producto;
	p_archivo=fopen(F_NOM_PRODUCTOS,"r");

	limpiar_lista_producto(&Productos);

	while(fscanf(p_archivo,"%d|%[^|]|%f|%d|%f",&producto.id_producto,producto.nombre_producto,&producto.precio_compra,
	             &producto.existencia,&producto.precio_venta)!=EOF) {
		agregar_producto(&Productos,producto);
	}

	fclose(p_archivo);
}

void guardar_archivo_producto(void) {
	FILE *p_archivo;
	PRODUCTO *p_actual=Productos.p_inicio;
	p_archivo=fopen(F_NOM_PRODUCTOS,"w+");
	while(p_actual !=NULL) {
		fprintf(p_archivo,"%d|%s|%.2f|%d|%.2f\n",p_actual->id_producto,p_actual->nombre_producto,p_actual->precio_compra,
		        p_actual->existencia,p_actual->precio_venta);
		p_actual=p_actual->p_siguiente;
	}
	fclose(p_archivo);
}

void limpiar_lista_producto(LST_PRODUCTO *p_lista) {
	PRODUCTO *p_actual=p_lista->p_inicio;

	while(p_actual!=NULL) {
		p_lista->p_inicio=p_actual->p_siguiente;
		free(p_actual);
		p_actual=p_lista->p_inicio;
	}
	p_lista->p_fin=NULL;
}

/*****************************************************************************
 Funciones de detalle venta
*****************************************************************************/
DETALLE_VENTA *p_nuevo_detalle_venta(void) {
	return (DETALLE_VENTA *) calloc(sizeof(DETALLE_VENTA),1);
}

void agregar_detalle_venta(LST_DETALLE_VENTA *p_lista, DETALLE_VENTA detalle_venta) {
	DETALLE_VENTA *p_nuevo=p_nuevo_detalle_venta();
	*p_nuevo=detalle_venta;
	p_nuevo->p_siguiente=NULL;

	if(p_lista->p_fin!=NULL) {
		p_lista->p_fin->p_siguiente=p_nuevo;
		p_nuevo->p_siguiente=NULL;
		p_lista->p_fin=p_nuevo;
	} else {
		p_lista->p_inicio=p_nuevo;
		p_lista->p_fin=p_nuevo;
	}
}

void entrada_detalle_venta(int num_venta) {
	DETALLE_VENTA detalle_venta;
	//LST_DETALLE_VENTA lista_detalle_venta;
	char buffer[50];

	//lista_detalle_venta.p_inicio=NULL;
	//lista_detalle_venta.p_fin=NULL;

	detalle_venta.num_venta=num_venta;
	do {
		printf("Numero de producto: ");
		scanf(" %d",&detalle_venta.num_producto);
		printf("Cantidad: ");
		scanf(" %d",&detalle_venta.cantidad);

		detalle_venta.p_producto=buscar_producto(Productos,detalle_venta.num_producto, NULL);
		detalle_venta.p_siguiente=NULL;

		agregar_detalle_venta(&Detalles,detalle_venta);

		printf("Escriba fin para terminar, cualquier otra cosa para agregar un "
		       "producto adicional\n");
		scanf(" %s",buffer);
	} while(strcmp("fin",buffer)!=0);
	//return lista_detalle_venta;
}

void mostrar_detalle_venta(DETALLE_VENTA detalle_venta) {
	printf(" %d\t%d\t%d\n", detalle_venta.num_venta, detalle_venta.num_producto,
	       detalle_venta.cantidad);
}

void mostrar_lista_detalle_venta(LST_DETALLE_VENTA lista) {
	DETALLE_VENTA *p_actual=lista.p_inicio;

	while(p_actual!=NULL) {
		mostrar_detalle_venta(*p_actual);
		p_actual=p_actual->p_siguiente;
	}
}

void mostrar_lista_detalle_venta_por_num(LST_DETALLE_VENTA lista,int num_venta) {
	DETALLE_VENTA *p_actual=lista.p_inicio;

	while(p_actual!=NULL) {
		if (p_actual->num_venta==num_venta)
			mostrar_detalle_venta(*p_actual);
		p_actual=p_actual->p_siguiente;
	}
}

void limpiar_lista_detalle_venta(LST_DETALLE_VENTA *p_lista) {
	DETALLE_VENTA *p_actual=p_lista->p_inicio;

	while(p_actual!=NULL) {
		p_lista->p_inicio=p_actual->p_siguiente;
		free(p_actual);
		p_actual=p_lista->p_inicio;
	}
	p_lista->p_fin=NULL;

}

void leer_archivo_detalle_venta() {
	FILE *p_archivo;
	DETALLE_VENTA detalle;
	p_archivo=fopen(F_NOM_DETALLE_VENTAS,"r");

	limpiar_lista_detalle_venta(&Detalles);

	while(fscanf(p_archivo,"%d|%d|%d\n",&detalle.num_venta,&detalle.num_producto,&detalle.cantidad)!=EOF) {
		agregar_detalle_venta(&Detalles,detalle);
	}
	fclose(p_archivo);
}

void guardar_archivo_detalle_venta() {
	FILE *p_archivo;
	DETALLE_VENTA *p_actual=Detalles.p_inicio;
	p_archivo=fopen(F_NOM_DETALLE_VENTAS,"w+");
	while(p_actual !=NULL) {
		fprintf(p_archivo,"%d|%d|%d\n",p_actual->num_venta,p_actual->num_producto,p_actual->cantidad);
		p_actual=p_actual->p_siguiente;
	}
	fclose(p_archivo);

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
	p_nuevo->p_siguiente=NULL;

	if(p_lista->p_fin!=NULL) {
		p_lista->p_fin->p_siguiente=p_nuevo;
		p_nuevo->p_siguiente=NULL;
		p_lista->p_fin=p_nuevo;
	} else {
		p_lista->p_inicio=p_nuevo;
		p_lista->p_fin=p_nuevo;
	}
}

void entrada_venta() {
	VENTA venta;

	printf("Numero de venta: ");
	scanf(" %d",&venta.num_venta);
	printf("Fecha de venta: ");
	scanf(" %d",&venta.fecha);
	printf("Hora de venta: ");
	scanf(" %d",&venta.hora);

	entrada_detalle_venta(venta.num_venta);
	agregar_venta(&Ventas,venta);
}

void mostrar_venta(VENTA venta) {
	printf("%d\t%d\t%d\n", venta.num_venta, venta.fecha, venta.hora);
	mostrar_lista_detalle_venta_por_num(Detalles,venta.num_venta);
}

void mostrar_lista_venta(LST_VENTA lista) {
	VENTA *p_actual=lista.p_inicio;

	while(p_actual!=NULL) {
		mostrar_venta(*p_actual);
		p_actual=p_actual->p_siguiente;
	}
}

void leer_archivo_venta() {

	FILE *p_archivo;
	VENTA venta;
	p_archivo=fopen(F_NOM_VENTAS,"r");

	limpiar_lista_venta(&Ventas);

	while(fscanf(p_archivo,"%d|%d|%d\n",&venta.num_venta,&venta.fecha,&venta.hora)!=EOF) {
		agregar_venta(&Ventas,venta);
	}

	fclose(p_archivo);

}
void guardar_archivo_venta() {
	FILE *p_archivo;
	VENTA *p_actual=Ventas.p_inicio;
	p_archivo=fopen(F_NOM_VENTAS,"w+");
	while(p_actual !=NULL) {
		fprintf(p_archivo,"%d|%d|%d\n",p_actual->num_venta,p_actual->fecha,p_actual->hora);
		p_actual=p_actual->p_siguiente;
	}
	fclose(p_archivo);

}

void limpiar_lista_venta(LST_VENTA *p_lista) {
	VENTA *p_actual=p_lista->p_inicio;

	while(p_actual!=NULL) {
		p_lista->p_inicio=p_actual->p_siguiente;
		free(p_actual);
		p_actual=p_lista->p_inicio;
	}
	p_lista->p_fin=NULL;

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
		printf("\n3. Editar producto");
		printf("\n4. Buscar producto");
		printf("\n5. Listar productos");
		printf("\n6. Guardar productos");
		printf("\n7. Regresar a menu principal");
		printf("\nIngresa tu opcion: ");
		scanf(" %d", &opcion);
		switch (opcion) {
			case 1:
				entrada_producto();
				break;
			case 2:
				borrar_producto();
				break;
			case 3:
				modificar_producto();
				break;
			case 4:
				mostrar_busqueda_producto();
				break;
			case 5:
				mostrar_lista_producto(Productos);
				break;
			case 6:
				guardar_archivo_producto();
				break;
			case 7:
				printf("Volviendo al menu principal\n");
				break;
			default:
				printf("Opcion invalida\n");
				break;
		}
		PAUSA;
	} while (opcion != 7);
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
				mostrar_lista_venta(Ventas);
				break;
			case 5:
				break;
			case 6:
				printf("Volviendo al menu principal\n");
				break;
			default:
				printf("Opcion invalida\n");
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

	leer_archivo_producto();
	leer_archivo_venta();
	leer_archivo_detalle_venta();

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
				printf("Saliendo del programa. Tenga buen dia.\n");
				PAUSA;
				break;
			default:
				printf("Opcion invalida\n");
				PAUSA;
				break;
		}
	} while (opcion != 4);

	guardar_archivo_producto();
	guardar_archivo_venta();
	guardar_archivo_detalle_venta();

	return 0;
}
