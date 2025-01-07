#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

//Definiciones
#define Limpiar_Pantalla system("cls")
#define Pausar_Pantalla system("pause")
#define File_Nombre_Productos "Productos.txt"
#define File_Nombre_Ventas "Ventas.txt"
#define File_Nombre_Detalle_Ventas "Detalle-ventas.txt"

//Estructuras
typedef struct struct_producto PRODUCTO;
struct struct_producto {
	int id_producto;
	char nombre_producto[101];
	float precio_compra;
	float precio_venta;
	int existencia;
	PRODUCTO *puntero_siguiente;
};
typedef struct struct_venta VENTA;
struct struct_venta {
	int numero_venta;
	int fecha;
	int hora;
	VENTA *puntero_siguiente;
};
typedef struct struct_detalle_venta DETALLE_VENTA;
struct struct_detalle_venta {
	int numero_venta;
	int numero_producto;
	int cantidad;
	PRODUCTO *puntero_producto;
	DETALLE_VENTA *puntero_siguiente;
};
typedef struct struct_lista_productos LISTA_PRODUCTO;
struct struct_lista_productos {
	PRODUCTO *puntero_inicio;
	PRODUCTO *puntero_fin;
};
typedef struct struct_lista_venta LISTA_VENTA;
struct struct_lista_venta {
	VENTA *puntero_inicio;
	VENTA *puntero_fin;
};
typedef struct struct_lista_detalle_venta LISTA_DETALLE_VENTA;
struct struct_lista_detalle_venta {
	DETALLE_VENTA *puntero_inicio;
	DETALLE_VENTA *puntero_fin;
};

//Variables Globales
LISTA_PRODUCTO Productos;
LISTA_VENTA Ventas;
LISTA_DETALLE_VENTA Detalles;

//Funciones Prototipo
/* PRODUCTO */
PRODUCTO *puntero_nuevo_producto();
void leer_archivo_producto();
void guardar_archivo_producto();
void agregar_producto(LISTA_PRODUCTO*,PRODUCTO);
void entrada_producto();
void mostrar_producto(PRODUCTO);
void mostrar_lista_producto(LISTA_PRODUCTO);
PRODUCTO *puntero_buscar_producto(LISTA_PRODUCTO,int);
void mostrar_busqueda_producto();
void modificar_producto();
int remover_producto(LISTA_PRODUCTO*,int);
void eliminar_producto();
void mostrar_producto_existencia_5();

/* VENTA */
VENTA *puntero_nueva_venta();
void leer_archivo_venta();
void guardar_archivo_venta();
void agregar_venta(LISTA_VENTA*,VENTA);
void entrada_venta();
void mostrar_venta(VENTA);
void mostrar_lista_venta(LISTA_VENTA);
VENTA *puntero_buscar_venta(LISTA_VENTA,int);
void mostrar_busqueda_nota_venta();
void reporte_venta_dia_intervalo_nota();
void total_general_venta(LISTA_VENTA);

/* DETALLE_VENTA */
DETALLE_VENTA *puntero_nuevo_detalle_venta();
void leer_archivo_detalle_venta();
void guardar_archivo_detalle_venta();
void agregar_detalle_venta(LISTA_DETALLE_VENTA*,DETALLE_VENTA);
void entrada_detalle_venta(int);
void mostrar_detalle_venta(DETALLE_VENTA);
void mostrar_lista_detalle_venta(LISTA_DETALLE_VENTA);
void mostrar_lista_detalle_venta_por_numero(LISTA_DETALLE_VENTA,int);
float calcular_total_detalle_venta(LISTA_PRODUCTO,LISTA_DETALLE_VENTA,int);

/* FECHA Y HORA */
int pedir_fecha(const char *impresion_usuario);
int pedir_hora(const char *impresion_usuario);
int es_fecha_valida(int year,int mon,int mday);
int es_hora_valida(int hora,int min);
char *formatear_fecha(int fecha,char buffer[],int tam_buffer);
char *formatear_hora(int hora,char buffer[],int tam_buffer);
int siguiente_dia(int dia);

/* MENU PRODUCTOS */
void menu_productos();

/* MENU VENTAS */
void menu_ventas();

//Funciones de Producto
PRODUCTO *puntero_nuevo_producto() {
	return (PRODUCTO*) calloc(sizeof(PRODUCTO),1);
}
void leer_archivo_producto() {
	FILE *puntero_archivo;
	PRODUCTO producto;
	puntero_archivo=fopen(File_Nombre_Productos,"r");

	while(fscanf(puntero_archivo,"%d|%[^|]|%f|%f|%d",
	             &producto.id_producto,
	             producto.nombre_producto,
	             &producto.precio_compra,
	             &producto.precio_venta,
	             &producto.existencia)!=EOF) {
		agregar_producto(&Productos,producto);
	}
	fclose(puntero_archivo);
}
void guardar_archivo_producto() {
	FILE *puntero_archivo;
	PRODUCTO *puntero_actual=Productos.puntero_inicio;
	puntero_archivo=fopen(File_Nombre_Productos,"w+");

	while(puntero_actual!=NULL) {
		fprintf(puntero_archivo, "%d|%s|%.2f|%.2f|%d\n",
		        puntero_actual->id_producto,
		        puntero_actual->nombre_producto,
		        puntero_actual->precio_compra,
		        puntero_actual->precio_venta,
		        puntero_actual->existencia);
		puntero_actual=puntero_actual->puntero_siguiente;
	}
	fclose(puntero_archivo);
}
void agregar_producto(LISTA_PRODUCTO *puntero_lista,PRODUCTO producto) {
	PRODUCTO *puntero_nuevo=puntero_nuevo_producto();
	*puntero_nuevo=producto;
	puntero_nuevo->puntero_siguiente=NULL;

	if(puntero_lista->puntero_fin!=NULL) {
		puntero_lista->puntero_fin->puntero_siguiente=puntero_nuevo;
		puntero_lista->puntero_fin=puntero_nuevo;
	} else {
		puntero_lista->puntero_inicio=puntero_nuevo;
		puntero_lista->puntero_fin=puntero_nuevo;
	}
}
void entrada_producto() {
	PRODUCTO producto;
	PRODUCTO *puntero_producto_existente;

	do {
		printf("ID: ");
		scanf(" %d",&producto.id_producto);
		puntero_producto_existente=puntero_buscar_producto(Productos,producto.id_producto);
		if(puntero_producto_existente!=NULL)
			printf("ERROR: El ID %d ya existe. Por favor, ingrese un ID diferente.\n",producto.id_producto);
	} while(puntero_producto_existente!=NULL);

	printf("Nombre del producto: ");
	scanf(" %100[^\n]",producto.nombre_producto);
	printf("Precio de compra: ");
	scanf(" %f",&producto.precio_compra);
	printf("Precio de venta: ");
	scanf(" %f",&producto.precio_venta);
	printf("Existencias: ");
	scanf(" %d",&producto.existencia);

	agregar_producto(&Productos,producto);
	printf("Producto agregado con exito.\n");
}
void mostrar_producto(PRODUCTO producto) {
	printf(" ------------------------------------------------------------------------------------------------------------------\n");
	printf(" %-8s %-60s %-15s %-15s %s\n",
	       "ID",
	       "Nombre del producto",
	       "Precio de compra",
	       "Precio de venta",
	       "Existencias");
	printf(" %-8d %-60s %-16.2f %-15.2f %d\n",
	       producto.id_producto,
	       producto.nombre_producto,
	       producto.precio_compra,
	       producto.precio_venta,
	       producto.existencia);
	printf(" ------------------------------------------------------------------------------------------------------------------\n");
}
PRODUCTO *puntero_buscar_producto(LISTA_PRODUCTO lista, int id_producto) {
	PRODUCTO *puntero_actual=lista.puntero_inicio;

	while(puntero_actual!=NULL) {
		if(puntero_actual->id_producto==id_producto)
			return (PRODUCTO *)puntero_actual;
		puntero_actual=puntero_actual->puntero_siguiente;
	}
	return NULL;
}
void mostrar_lista_producto(LISTA_PRODUCTO lista) {
	PRODUCTO *puntero_actual=lista.puntero_inicio;

	while(puntero_actual!=NULL) {
		mostrar_producto(*puntero_actual);
		puntero_actual=puntero_actual->puntero_siguiente;
	}
}
void mostrar_busqueda_producto() {
	PRODUCTO *puntero_actual=NULL;
	int id_producto;
	printf("Ingrese el ID del producto: ");
	scanf(" %d",&id_producto);
	puntero_actual=puntero_buscar_producto(Productos,id_producto);
	mostrar_producto(*puntero_actual);
}
void mostrar_producto_existencia_5() {
	PRODUCTO *puntero_actual=Productos.puntero_inicio;
	int productos_5=0;
	while(puntero_actual!=NULL) {
		if(puntero_actual->existencia<=5) {
			mostrar_producto(*puntero_actual);
			productos_5++;
		}
		puntero_actual=puntero_actual->puntero_siguiente;
	}
	printf("Se mostraron %d productos con existencia menor o igual a cinco\n",productos_5);
}
void modificar_producto() {
	PRODUCTO *puntero_producto;
	int id_producto;
	char opcion;

	printf("Ingrese el ID del producto a modificar: ");
	scanf(" %d", &id_producto);
	puntero_producto = puntero_buscar_producto(Productos, id_producto);

	if (puntero_producto != NULL) {
		do {
			Limpiar_Pantalla;
			printf("Producto encontrado:\n");
			mostrar_producto(*puntero_producto);
			printf("Seleccione que desea modificar:\n");
			printf("1. Nombre del producto\n");
			printf("2. Precio de compra\n");
			printf("3. Precio de venta\n");
			printf("4. Existencia\n");
			printf("5. Volver al menu productos\n");
			printf("Opcion: \n");
			opcion = getch();

			switch (opcion) {
				case '1':
					printf("Ingrese el nuevo nombre del producto: ");
					scanf(" %[^\n]", puntero_producto->nombre_producto);
					break;
				case '2':
					printf("Ingrese el nuevo precio de compra del producto: ");
					scanf(" %f", &puntero_producto->precio_compra);
					break;
				case '3':
					printf("Ingrese el nuevo precio de venta del producto: ");
					scanf(" %f", &puntero_producto->precio_venta);
					break;
				case '4':
					printf("Ingrese la nueva existencia del producto: ");
					scanf(" %d", &puntero_producto->existencia);
					break;
				case '5':
					printf("Volviendo al menu productos.\n");
					break;
				default:
					printf("Opción no válida.\n");
					break;
			}

			if (opcion >= '1' && opcion <= '4') {
				printf("Producto modificado con exito:\n");
				Pausar_Pantalla;
			}
		} while (opcion != '5');
	} else {
		printf("Producto no encontrado.\n");
	}
}
int remover_producto(LISTA_PRODUCTO *puntero_lista,int id_producto) {
	PRODUCTO *puntero_actual=puntero_lista->puntero_inicio,*puntero_anterior=NULL;

	while (puntero_actual!=NULL) {
		if (puntero_actual->id_producto==id_producto) {
			if (puntero_anterior==NULL) {
				puntero_lista->puntero_inicio=puntero_actual->puntero_siguiente;
			} else {
				puntero_anterior->puntero_siguiente=puntero_actual->puntero_siguiente;
			}
			if (puntero_actual==puntero_lista->puntero_fin) {
				puntero_lista->puntero_fin=puntero_anterior;
			}
			free(puntero_actual);
			return 1;
		}
		puntero_anterior = puntero_actual;
		puntero_actual = puntero_actual->puntero_siguiente;
	}
	return 0;
}
void eliminar_producto() {
	int id_producto;

	mostrar_lista_producto(Productos);
	printf("Ingrese el ID del producto a eliminar: ");
	scanf("%d",&id_producto);
	Pausar_Pantalla;
	Limpiar_Pantalla;

	if (remover_producto(&Productos,id_producto)) {
		printf("Producto eliminado con exito.\n");
	} else {
		printf("Producto no encontrado.\n");
	}

	mostrar_lista_producto(Productos);
}

//Funciones de Venta
VENTA *puntero_nueva_venta() {
	return (VENTA *) calloc(sizeof(VENTA),1);
}
void leer_archivo_venta() {
	FILE *puntero_archivo;
	VENTA venta;
	puntero_archivo=fopen(File_Nombre_Ventas,"r");

	while(fscanf(puntero_archivo,"%d|%d|%d\n",
	             &venta.numero_venta,
	             &venta.fecha,
	             &venta.hora)!=EOF) {
		agregar_venta(&Ventas,venta);
	}
	fclose(puntero_archivo);
}
void guardar_archivo_venta() {
	FILE *puntero_archivo;
	VENTA *puntero_actual=Ventas.puntero_inicio;
	puntero_archivo=fopen(File_Nombre_Ventas,"w+");

	while(puntero_actual!=NULL) {
		fprintf(puntero_archivo, "%d|%d|%d\n",
		        puntero_actual->numero_venta,
		        puntero_actual->fecha,
		        puntero_actual->hora);
		puntero_actual=puntero_actual->puntero_siguiente;
	}
	fclose(puntero_archivo);
}
void agregar_venta(LISTA_VENTA *puntero_lista,VENTA venta) {
	VENTA *puntero_nuevo=puntero_nueva_venta();
	*puntero_nuevo=venta;
	puntero_nuevo->puntero_siguiente=NULL;

	if(puntero_lista->puntero_fin!=NULL) {
		puntero_lista->puntero_fin->puntero_siguiente=puntero_nuevo;
		puntero_lista->puntero_fin=puntero_nuevo;
	} else {
		puntero_lista->puntero_inicio=puntero_nuevo;
		puntero_lista->puntero_fin=puntero_nuevo;
	}
}
void entrada_venta() {
	VENTA venta;
	VENTA *puntero_venta_existente;

	do {
		printf("Numero de venta: ");
		scanf(" %d",&venta.numero_venta);
		puntero_venta_existente=puntero_buscar_venta(Ventas,venta.numero_venta);
		if(puntero_venta_existente!=NULL)
			printf("Error: El numero de venta %d ya existe. Por favor, ingrese un numero diferente.\n",venta.numero_venta);
	} while(puntero_venta_existente!=NULL);

	venta.fecha=pedir_fecha("Fecha de venta: ");
	venta.hora=pedir_hora("Hora de venta: ");

	entrada_detalle_venta(venta.numero_venta);
	agregar_venta(&Ventas,venta);
	printf("Venta agregada con exito.\n");
}
void mostrar_venta(VENTA venta) {
	char cadena_fecha[20];
	char cadena_hora[20];
	float subtotal=calcular_total_detalle_venta(Productos,Detalles,venta.numero_venta);

	printf(" ------------------------------------------------------------------------------------------------------\n");
	printf("  NUMERO DE NOTA: %4d                                                FECHA:  %s  HORA: %s  \n",
	       venta.numero_venta,formatear_fecha(venta.fecha,cadena_fecha,sizeof(cadena_fecha)),
	       formatear_hora(venta.hora,cadena_hora,sizeof(cadena_hora)));
	printf(" ------------------------------------------------------------------------------------------------------\n");
	mostrar_lista_detalle_venta_por_numero(Detalles,venta.numero_venta);
	printf(" ------------------------------------------------------------------------------------------------------\n");
	printf("                                                                              SUBTOTAL:  $%9.2f\n",
	       subtotal);
	printf(" ------------------------------------------------------------------------------------------------------\n");
}
void mostrar_lista_venta(LISTA_VENTA lista) {
	VENTA *puntero_actual=lista.puntero_inicio;
	float gran_total=0.0;

	while(puntero_actual!=NULL) {
		float subtotal=calcular_total_detalle_venta(Productos,Detalles,puntero_actual->numero_venta);
		mostrar_venta(*puntero_actual);
		gran_total+=subtotal;
		puntero_actual=puntero_actual->puntero_siguiente;
	}

	printf(" ------------------------------------------------------------------------------------------------------\n");
	printf("                                                                            GRAN TOTAL:  $%12.2f\n",
	       gran_total);
	printf(" ------------------------------------------------------------------------------------------------------\n");
}
VENTA *puntero_buscar_venta(LISTA_VENTA lista,int numero_venta) {
	VENTA *puntero_actual=lista.puntero_inicio;

	while(puntero_actual!=NULL) {
		if(puntero_actual->numero_venta==numero_venta)
			return puntero_actual;
		puntero_actual=puntero_actual->puntero_siguiente;
	}
	return NULL;
}
void mostrar_busqueda_nota_venta() {
	int numero_venta;

	printf("Ingrese el numero de nota de la venta que va a buscar: ");
	scanf("%d",&numero_venta);
	VENTA *puntero_venta=puntero_buscar_venta(Ventas,numero_venta);
	if(puntero_venta!=NULL)
		mostrar_venta(*puntero_venta);
	else
		printf("No se encontro la nota\n");
}
void reporte_venta_dia_intervalo_nota(void) {
	int fecha_inicio, fecha_fin;
	float total_total = 0.0;
	char cadena_fecha[20], cadena_hora[20];
	VENTA *puntero_actual;

	fecha_inicio=pedir_fecha("Ingrese la fecha de inicio: ");
	fecha_fin=pedir_fecha("Ingrese la fecha de fin: ");

	printf(" ------------------------------- \n");

	for (int fecha=fecha_inicio; fecha<=fecha_fin; fecha=siguiente_dia(fecha)) {
		float total_dia=0.0;
		int ventas_encontradas=0;

		puntero_actual=Ventas.puntero_inicio;
		while (puntero_actual!=NULL) {
			if (puntero_actual->fecha==fecha) {
				if (!ventas_encontradas) {
					printf(" FECHA: %s\n",formatear_fecha(fecha,cadena_fecha,sizeof(cadena_fecha)));
					printf(" ------------------------------- \n");
					printf("  No.Nota  Hora   Total de nota\n");
					ventas_encontradas=1;
				}

				float total_nota=calcular_total_detalle_venta(Productos,Detalles,puntero_actual->numero_venta);
				total_dia+=total_nota;
				total_total+=total_nota;

				printf("  %3d      %s  $%9.2f\n",
				       puntero_actual->numero_venta,
				       formatear_hora(puntero_actual->hora,
				                      cadena_hora,sizeof(cadena_hora)),
				       total_nota);
			}
			puntero_actual=puntero_actual->puntero_siguiente;
		}

		if (ventas_encontradas) {
			printf(" TOTAL DEL DIA: $%11.2f\n",total_dia);
			printf(" ------------------------------- \n");
		}
	}

	printf(" TOTAL RANGO:   $%11.2f\n",total_total);
	printf(" ------------------------------- \n");
}

void total_general_venta(LISTA_VENTA lista) {
	VENTA *puntero_actual=lista.puntero_inicio;
	int fecha_anterior=0;
	float total, total_total=0.0;
	char cadena_fecha[20];
	char cadena_hora[20];

	printf(" ------------------------------- \n");
	printf(" TOTAL DE VENTAS: ");

	while (puntero_actual!=NULL) {
		if (puntero_actual->fecha!=fecha_anterior) {
			fecha_anterior=puntero_actual->fecha;
			printf("\n ------------------------------- \n");
			printf(" FECHA: %s",formatear_fecha(puntero_actual->fecha,cadena_fecha,sizeof(cadena_fecha)));
		}

		total=calcular_total_detalle_venta(Productos,Detalles,puntero_actual->numero_venta);
		total_total+=total;
		printf("\n ------------------------------- \n");
		printf("  No.Nota  Hora   Total de nota \n"
		       "  %3d      %s  $%9.2f ",
		       puntero_actual->numero_venta,
		       formatear_hora(puntero_actual->hora,
		                      cadena_hora,
		                      sizeof(cadena_hora)),total);

		puntero_actual=puntero_actual->puntero_siguiente;
	}

	printf("\n ------------------------------- \n");
	printf(" GRAN TOTAL:   $%12.2f",total_total);
	printf(" \n ------------------------------- \n");
}

//Funciones de Detalle venta
DETALLE_VENTA *puntero_nuevo_detalle_venta() {
	return (DETALLE_VENTA *) calloc(sizeof(DETALLE_VENTA),1);
}
void leer_archivo_detalle_venta() {
	FILE *puntero_archivo;
	DETALLE_VENTA detalle;
	puntero_archivo=fopen(File_Nombre_Detalle_Ventas,"r");

	while(fscanf(puntero_archivo,"%d|%d|%d\n",&detalle.numero_venta,&detalle.numero_producto,&detalle.cantidad)!=EOF) {
		detalle.puntero_producto=puntero_buscar_producto(Productos,detalle.numero_producto);
		agregar_detalle_venta(&Detalles,detalle);
	}
	fclose(puntero_archivo);
}
void guardar_archivo_detalle_venta() {
	FILE *puntero_archivo;
	DETALLE_VENTA *puntero_actual=Detalles.puntero_inicio;
	puntero_archivo=fopen(File_Nombre_Detalle_Ventas,"w+");

	while(puntero_actual!=NULL) {
		fprintf(puntero_archivo,"%d|%d|%d\n",puntero_actual->numero_venta,puntero_actual->numero_producto,puntero_actual->cantidad);
		puntero_actual=puntero_actual->puntero_siguiente;
	}
	fclose(puntero_archivo);
}
void agregar_detalle_venta(LISTA_DETALLE_VENTA *puntero_lista,DETALLE_VENTA detalle_venta) {
	DETALLE_VENTA *puntero_nuevo=puntero_nuevo_detalle_venta();
	*puntero_nuevo=detalle_venta;
	puntero_nuevo->puntero_siguiente=NULL;

	if(puntero_lista->puntero_fin!=NULL) {
		puntero_lista->puntero_fin->puntero_siguiente=puntero_nuevo;
		puntero_lista->puntero_fin=puntero_nuevo;
	} else {
		puntero_lista->puntero_inicio=puntero_nuevo;
		puntero_lista->puntero_fin=puntero_nuevo;
	}
}
void entrada_detalle_venta(int numero_venta) {
    DETALLE_VENTA detalle_venta;
    PRODUCTO *producto;
    char tecla;

    detalle_venta.numero_venta = numero_venta;

    do {
        do {
            printf("Numero de producto: ");
            scanf(" %d", &detalle_venta.numero_producto);

            producto = puntero_buscar_producto(Productos, detalle_venta.numero_producto);
            if (producto == NULL) {
                printf("Error: El producto con ID %d no existe. Intente con otro ID.\n", detalle_venta.numero_producto);
                continue;
            }
			do {
				printf("Cantidad: ");
				scanf(" %d", &detalle_venta.cantidad);

				if (detalle_venta.cantidad > producto->existencia) {
					printf("Solo hay %d existencias para el producto. Por favor intente de nuevo.\n", producto->existencia);
				}
			}while (detalle_venta.cantidad > producto->existencia);
        } while (producto == NULL);

        producto->existencia -= detalle_venta.cantidad;
        detalle_venta.puntero_producto = producto;
        detalle_venta.puntero_siguiente = NULL;
        agregar_detalle_venta(&Detalles, detalle_venta);

        printf("Presione [Enter] para agregar otro producto o [ESC] para terminar...\n");

        do {
            tecla = getch();
        } while (tecla != 13 && tecla != 27);

    } while (tecla != 27);
}
void mostrar_detalle_venta(DETALLE_VENTA detalle_venta) {
	printf("  %3d  %8d  %-60s  $%6.2f  $%9.2f \n",
	       detalle_venta.numero_producto,detalle_venta.cantidad,detalle_venta.puntero_producto->nombre_producto,
	       detalle_venta.puntero_producto->precio_venta,
	       detalle_venta.cantidad*detalle_venta.puntero_producto->precio_venta);
}
void mostrar_lista_detalle_venta(LISTA_DETALLE_VENTA lista) {
	DETALLE_VENTA *puntero_actual=lista.puntero_inicio;

	while(puntero_actual!=NULL) {
		mostrar_detalle_venta(*puntero_actual);
		puntero_actual=puntero_actual->puntero_siguiente;
	}
}
void mostrar_lista_detalle_venta_por_numero(LISTA_DETALLE_VENTA lista,int numero_venta) {
	DETALLE_VENTA *puntero_actual=lista.puntero_inicio;

	printf("   ID  CANTIDAD  NOMBRE                                        "
	       "                PRECIO      TOTAL \n");

	while(puntero_actual!=NULL) {
		if(puntero_actual->numero_venta==numero_venta)
			mostrar_detalle_venta(*puntero_actual);
		puntero_actual=puntero_actual->puntero_siguiente;
	}
}
float calcular_total_detalle_venta(LISTA_PRODUCTO lista_productos,LISTA_DETALLE_VENTA lista_ventas,int numero_venta) {
	DETALLE_VENTA *puntero_actual=lista_ventas.puntero_inicio;
	float total=0.0;

	while(puntero_actual!=NULL) {
		if(puntero_actual->numero_venta==numero_venta) {
			if(puntero_actual->puntero_producto!=NULL)
				total=total+puntero_actual->cantidad*(puntero_actual->puntero_producto->precio_venta);
		}
		puntero_actual=puntero_actual->puntero_siguiente;
	}
	return total;
}

//Funciones de FECHA y HORA
int pedir_fecha(const char *impresion_usuario) {
	char fecha[11]= {"YYYY-MM-DD"};
	int pos=0,tecla,year,mon,mday;

	printf("%s",impresion_usuario);
	printf(" %s\b\b\b\b\b\b\b\b\b\b",fecha);

	while (pos<10||tecla!=13) {
		tecla=getch();

		if (tecla>='0'&&tecla<='9'&&pos<10) {
			putchar(tecla);
			fecha[pos++]=tecla;
			if (pos==4||pos==7) {
				fecha[pos++]='-';
				putchar('-');
			}
		} else if (tecla=='\b'&&pos>0) {
			switch (pos) {
				case 1:
				case 2:
				case 3:
					printf("\bY\b");
					pos--;
					break;
				case 5:
					printf("\b\bY\b");
					pos-=2;
					break;
				case 6:
					printf("\bM\b");
					pos--;
					break;
				case 8:
					printf("\b\bM\b");
					pos-=2;
					break;
				case 9:
				case 10:
					printf("\bD\b");
					pos--;
					break;
			}
		} else if (tecla==13) {
			if (pos<10) {
				printf("\a");
			} else {
				fecha[pos]='\0';
				sscanf(fecha,"%4d-%2d-%2d",&year,&mon,&mday);
				if (!es_fecha_valida(year,mon,mday)) {
					printf("\a");
					printf("\nFecha invalida. Intente de nuevo.\n");
					return pedir_fecha(impresion_usuario);
				}
				break;
			}
		} else {
			printf("\a");
		}
	}

	printf("\n");
	return year*10000+mon*100+mday;
}

int pedir_hora(const char *impresion_usuario) {
	char hora[6]= {"HH:MM"};
	int pos=0,tecla,horas,minutos;

	printf("%s", impresion_usuario);
	printf(" %s\b\b\b\b\b", hora);

	while (pos<5||tecla!=13) {
		tecla=getch();

		if (tecla>='0'&&tecla<='9'&&pos<5) {
			putchar(tecla);
			hora[pos++]=tecla;
			if (pos==2) {
				hora[pos++]=':';
				putchar(':');
			}
		} else if (tecla=='\b'&&pos>0) {
			switch (pos) {
				case 1:
					printf("\bH\b");
					pos--;
					break;
				case 3:
					printf("\b\bH\b");
					pos-=2;
					break;
				case 4:
				case 5:
					printf("\bM\b");
					pos--;
					break;
			}
		} else if (tecla==13) {
			if (pos<5) {
				printf("\a");
			} else {
				hora[pos]='\0';
				sscanf(hora,"%2d:%2d",&horas,&minutos);
				if (!es_hora_valida(horas,minutos)) {
					printf("\a");
					printf("\nHora invalida. Intente de nuevo.\n");
					return pedir_hora(impresion_usuario);
				}
				break;
			}
		} else {
			printf("\a");
		}
	}

	printf("\n");
	return horas*100+minutos;
}
int es_fecha_valida(int year,int mon,int mday) {
	if (year<1900||mon<1||mon>12||mday<1)
		return 0;
	struct tm fecha= {.tm_year=year-1900,.tm_mon=mon-1,.tm_mday=mday};
	time_t t=mktime(&fecha);
	return t!=-1&&fecha.tm_mday==mday;
}
int es_hora_valida(int hora,int min) {
	return hora>=0&&hora<24&&min>=0&&min<60;
}
char *formatear_fecha(int fecha,char buffer[],int tam_buffer) {
	struct tm tm_fecha= {
		.tm_sec=0,
		.tm_min=0,
		.tm_hour=0,
		.tm_year=(fecha/10000)-1900,
		.tm_mon=((fecha%10000)/100)-1,
		.tm_mday=fecha%100,
		.tm_yday=0,
		.tm_isdst=0
	};
	strftime(buffer,tam_buffer,"%Y-%m-%d",&tm_fecha);
	return buffer;
}

char *formatear_hora(int hora,char buffer[],int tam_buffer) {
	int horas=hora/100,minutos=hora%100;
	snprintf(buffer,tam_buffer,"%02d:%02d",horas,minutos);
	return buffer;
}
int siguiente_dia(int dia) {
	struct tm fecha= {
		.tm_sec=0,
		.tm_min=0,
		.tm_hour=0,
		.tm_year=(dia/10000)-1900,
		.tm_mon=((dia%10000)/100)-1,
		.tm_mday=dia%100,
		.tm_yday=0,
		.tm_isdst=0
	};
	time_t tiempo=mktime(&fecha);
	tiempo+=24*60*60;
	struct tm*nueva_fecha=localtime(&tiempo);

	return (nueva_fecha->tm_year+1900)*10000+(nueva_fecha->tm_mon+1)*100+nueva_fecha->tm_mday;
}

//Menu productos
void menu_productos() {
	char opcion;
	do {
		Limpiar_Pantalla;
		printf("Menu productos\n");
		printf("1. Agregar producto.\n");
		printf("2. Buscar producto por id.\n");
		printf("3. Eliminar producto.\n");
		printf("4. Listar productos\n");
		printf("5. Modificar productos\n");
		printf("6. Listar productos con existencia menor o igual a cinco\n");
		printf("7. Regresar a menu principal\n");
		printf("Ingresa tu opcion: \n");

		opcion=getch();
		switch (opcion) {
			case '1':
				entrada_producto();
				break;
			case '2':
				mostrar_busqueda_producto();
				break;
			case '3':
				eliminar_producto();
				break;
			case '4':
				mostrar_lista_producto(Productos);
				break;
			case '5':
				modificar_producto();
				break;
			case '6':
				mostrar_producto_existencia_5();
				break;
			case '7':
				printf("Volviendo al menu principal\n");
				break;
			default:
				printf("Opcion invalida\n");
				break;
		}
		Pausar_Pantalla;
	} while (opcion != '7');
}

//Menu ventas
void menu_ventas() {
	char opcion;
	do {
		Limpiar_Pantalla;
		printf("Menu ventas\n");
		printf("1. Agregar venta\n");
		printf("2. Buscar venta por numero de nota\n");
		printf("3. Listar ventas\n");
		printf("4. Total de ventas por dia, por intervalo de fechas y con numero de nota\n");
		printf("5. Total de ventas general\n");
		printf("6. Regresar a menu principal\n");
		printf("Ingresa tu opcion: \n");

		opcion=getch();
		switch (opcion) {
			case '1':
				entrada_venta();
				break;
			case '2':
				mostrar_busqueda_nota_venta();
				break;
			case '3':
				mostrar_lista_venta(Ventas);
				break;
			case '4':
				reporte_venta_dia_intervalo_nota();
				break;
			case '5':
				total_general_venta(Ventas);
				break;
			case '6':
				printf("Volviendo al menu principal\n");
				break;
			default:
				printf("Opcion invalida\n");
				break;
		}
		Pausar_Pantalla;
	} while(opcion!='6');
}

//Funcion Main
int main() {
	char opcion;

	leer_archivo_producto();
	leer_archivo_venta();
	leer_archivo_detalle_venta();

	do {
		Limpiar_Pantalla;
		printf("Menu principal\n");
		printf("1. Menu Productos\n");
		printf("2. Menu Ventas\n");
		printf("3. Salir\n");
		printf("Opcion: ");

		opcion = getch();
		switch (opcion) {
			case '1':
				menu_productos();
				break;
			case '2':
				menu_ventas();
				break;
			case '3':
				printf("Saliendo del programa. Tenga buen dia.\n");
				Pausar_Pantalla;
				break;
			default:
				printf("Opcion invalida\n");
				Pausar_Pantalla;
				break;
		}
	} while (opcion!='3');

	guardar_archivo_producto();
	guardar_archivo_venta();
	guardar_archivo_detalle_venta();

	return 0;
}