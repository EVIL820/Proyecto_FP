#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
//in master
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
/*****************************************************************************
 Manejo de fechas y horas
*****************************************************************************/
int siguiente_dia(int dia);

int pedir_fecha(char*);

int pedir_hora(char*);

int reestructura_fecha (int);

int validar_fecha(int,int,int);

char *formatear_fecha(int,char[],int);

char *formatear_hora(int,char[],int);

/*** producto ***/
/*
  Asigna memoria y lo castea como puntero
*/
PRODUCTO *p_nuevo_producto(void);//Back
  
/*
  Agrega producto, recibe la lista
  y el producto, despues lo agrega
  Devuelve la lista con el producto
*/ 
void agregar_producto(LST_PRODUCTO*,PRODUCTO);//Back
                                              
/*
  Pide al usuario el producto a agregar
*/                                              
void entrada_producto(void);//Front

/*
  Recibe el producto y muestra en pantalla
*/
void mostrar_producto(PRODUCTO);//Front

/*
  Recibe la lista y muestra en pantalla usando mostrar_producto
*/
void mostrar_lista_producto(LST_PRODUCTO);//Front

/*
  Recibe la lista y busca por el ID y regresa NULL si no encuentra, regresa el 
  producto si lo encuentra
*/
PRODUCTO *p_buscar_producto(LST_PRODUCTO,int);//Back

/*
  Muestra en pantalla el producto buscado en la lista 
*/
void mostrar_busqueda_producto();//Front

/*
  Borra los archivos por el inicio para que se vacie
*/ 
void limpiar_lista_producto(LST_PRODUCTO*);//Back

/*
  Abre el archivo F_NOM_PRODUCTOS "Productos.txt" y lo carga en la lista
  Primero limpia la lista existente (usa limpiar_lista_producto) y reemplaza 
  (usando agregar_producto)
  Cierra el archivo
*/                                 
void leer_archivo_producto(void);//Back

/*
  Carga el archivo F_NOM_PRODUCTOS "Productos.txt", lo crea si no existe y lo
  sobreescribe si existe. Copia los elementos de la lista y los almacena en
  el archivo
  Cierra el archivo
*/ 
void guardar_archivo_producto(void);//Back

/*
  Modificar
*/ 
void modificar_producto(void);//Front

/*
  Eliminar producto
*/ 
void eliminar_producto(void);//Front

/*
  Remover producto
*/
int remover_producto(LST_PRODUCTO*,int);

/*
  Lista los productos cuya existencia en tienda sea menor o igual a 5 piezas.
*/
void mostrar_producto_existencia_5(void);

/*****************************************************************************

    detalle venta 
*****************************************************************************/
/*
    Asigna memoria y lo castea como puntero
*/ 
DETALLE_VENTA *p_nuevo_detalle_venta(void);//Back

/*
    Agrega detalle de la venta, recibe la lista del detalle de la venta
    devuelve la lista del detalle de la venta
*/ 
void agregar_detalle_venta(LST_DETALLE_VENTA*,DETALLE_VENTA);//Back

/*
    Pide al usuario que producto agregar
*/ 
void entrada_detalle_venta(int num_venta);//Front

/*
    Recibe el producto y muestra en pantalla
*/ 
void mostrar_detalle_venta(DETALLE_VENTA);//Back

/*
    Recibe la lista y muestra en pantalla usando mostrar_venta
*/ 
void mostrar_lista_detalle_venta(LST_DETALLE_VENTA);//Front
/*
    Recibe la lista y busca por el ID y regresa NULL si no encuentra, regresa el 
    producto si lo encuentra
*/ 
void mostrar_lista_detalle_venta_por_num(LST_DETALLE_VENTA,int);//Back

/*
    Abre el archivo F_NOM_DETALLE_VENTAS "Detalles.txt" y lo carga en la lista
  Primero limpia la lista existente (usa limpiar_lista_detalle_venta) y reemplaza 
  (usando agregar_detalle_venta)
  Cierra el archivo
*/ 
void leer_archivo_detalle_venta(void);//Back

/*
    Borra los archivos por el inicio para que se vacie
*/ 
void limpiar_lista_detalle_venta(LST_DETALLE_VENTA*);//

/*
    Carga el archivo F_NOM_DETALLE_VENTAS "Detalles.txt", lo crea si no existe y lo
  sobreescribe si existe. Copia los elementos de la lista y los almacena en
  el archivo
  Cierra el archivo
*/ 
void guardar_archivo_detalle_venta();//Back

float calcular_total_detalle_venta(LST_PRODUCTO,LST_DETALLE_VENTA,int);//Back

/******************************************************************************
****venta**** 
******************************************************************************/
/*
    Asigna memoria y lo castea como puntero
*/ 
VENTA *p_nueva_venta(void);//

/*
    Agrega la venta, recibe la lista de la venta
    devuelve la lista de la venta
*/ 
void agregar_venta(LST_VENTA*,VENTA);//

/*
    
*/ 
void entrada_venta();//

/*
    
*/ 
void mostrar_venta(VENTA);//

/*
    
*/ 
void mostrar_lista_venta(LST_VENTA);//

/*
    
*/ 
void leer_archivo_venta(void);//

/*
    
*/ 
void guardar_archivo_venta(void);//

/*
    
*/ 
void limpiar_lista_venta(LST_VENTA*);//


/*
  Recibe la lista y busca por el ID (num de nota) y regresa NULL si no 
  encuentra, regresa el apuntador a la venta si la encuentra
*/
VENTA *p_buscar_venta(LST_VENTA,int);//Back

/*
  Solicita el ID de venta (num de nota) y si la encuentra la muestra en pantalla
  con su detalle
*/
void mostrar_busqueda_nota_venta();//Front



/*** menu productos***/
void menu_productos();

/*** menu ventas***/
void menu_ventas();

void reporte_venta_dia_intervalo_nota(void);//Front

void total_general_venta(LST_VENTA);//Front

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
	}
    else{
        p_lista->p_inicio=p_nuevo;
        p_lista->p_fin=p_nuevo;      
    }
}

void entrada_producto(){
    PRODUCTO producto;
    PRODUCTO *p_producto_existente;
	
	do{
	printf("ID: ");
	scanf(" %d",&producto.id_producto);
	
	p_producto_existente = p_buscar_producto(Productos, producto.id_producto);
	if(p_producto_existente != NULL)
		 printf("Error: El ID %d ya existe. Por favor, ingrese un ID diferente.\n", producto.id_producto);
	}while(p_producto_existente != NULL);
		
	printf("Nombre del producto: ");
	scanf(" %100[^\n]",producto.nombre_producto);
	printf("Precio de compra: ");
	scanf(" %f",&producto.precio_compra);
	printf("Unidades en existencia: ");
	scanf(" %d",&producto.existencia);
	printf("Precio de venta: ");
	scanf(" %f",&producto.precio_venta);

	agregar_producto(&Productos,producto);
	printf("Producto agregado con exito.\n");
}

void mostrar_producto(PRODUCTO producto){
    printf("%-8d %-60s %-15.2f %-15d %.2f\n", 
           producto.id_producto, 
           producto.nombre_producto, 
           producto.precio_compra, 
           producto.existencia, 
           producto.precio_venta);
}

PRODUCTO *p_buscar_producto(LST_PRODUCTO lista,int id_producto){
    PRODUCTO *p_actual=lista.p_inicio;
    
    while(p_actual!=NULL){
        if(p_actual->id_producto==id_producto)
            return (PRODUCTO *)p_actual;
        p_actual=p_actual->p_siguiente;
    }
    return NULL;
}

void mostrar_lista_producto(LST_PRODUCTO lista){
    PRODUCTO *p_actual=lista.p_inicio;
	
	printf("%-8s %-60s %-15s %-15s %s\n", 
           "ID", 
           "Nombre del producto", 
           "Precio compra", 
           "Existencia", 
           "Precio venta");
    
    while(p_actual!=NULL) {
        mostrar_producto(*p_actual);
        p_actual=p_actual->p_siguiente;
    }
}

void mostrar_busqueda_producto(){
    PRODUCTO *p_actual=NULL;
    int id_producto;
    printf("Ingrese el ID del producto: ");
    scanf("%d",&id_producto);
    p_actual=p_buscar_producto(Productos,id_producto);
    if(p_actual!=NULL)  
        mostrar_producto(*p_actual);
}

void mostrar_producto_existencia_5(){
    PRODUCTO *p_actual=Productos.p_inicio;
    printf("La lista de productos con existencia menor o igual a cinco:\n");
    while(p_actual!=NULL){
        if(p_actual->existencia<=5)
            mostrar_producto(*p_actual);
        p_actual=p_actual->p_siguiente;
    }
}

void leer_archivo_producto(void){
    FILE *p_archivo;
    PRODUCTO producto;
    p_archivo=fopen(F_NOM_PRODUCTOS,"r");
    
    limpiar_lista_producto(&Productos);
    
    while(fscanf(p_archivo,"%d|%[^|]|%f|%d|%f",&producto.id_producto,producto.nombre_producto,&producto.precio_compra,
                &producto.existencia,&producto.precio_venta)!=EOF){
          agregar_producto(&Productos,producto);
    }
    
    fclose(p_archivo);    
}

void guardar_archivo_producto(void){
    FILE *p_archivo;
    PRODUCTO *p_actual=Productos.p_inicio;
    p_archivo=fopen(F_NOM_PRODUCTOS,"w+");
    while(p_actual !=NULL){
        fprintf(p_archivo,"%d|%s|%.2f|%d|%.2f\n",p_actual->id_producto,p_actual->nombre_producto,p_actual->precio_compra,
                p_actual->existencia,p_actual->precio_venta);
        p_actual=p_actual->p_siguiente;
    }
    fclose(p_archivo);    
}

void limpiar_lista_producto(LST_PRODUCTO *p_lista){
     PRODUCTO *p_actual=p_lista->p_inicio;
     
    while(p_actual!=NULL){
         p_lista->p_inicio=p_actual->p_siguiente;
         free(p_actual);
         p_actual=p_lista->p_inicio;
    }
    p_lista->p_fin=NULL;
}

void modificar_producto(void){
    int id_producto;
	int opcion;
    PRODUCTO *p_producto;
    
    printf("Ingrese el id del producto a modificar: ");
    scanf("%d",&id_producto);
    p_producto=p_buscar_producto(Productos,id_producto);
	if (p_producto != NULL) {
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
					scanf(" %[^\n]", p_producto->nombre_producto);
					break;
				case 2:
					printf("Ingrese el nuevo precio de compra del producto: ");
					scanf(" %f", &p_producto->precio_compra);
					break;
				case 3:
					printf("Ingrese la nueva existencia del producto: ");
					scanf(" %d", &p_producto->existencia);
					break;
				case 4:
					printf("Ingrese el nuevo precio de venta del producto: ");
					scanf(" %f", &p_producto->precio_venta);
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

void eliminar_producto(void){
    int id_producto;
    
    mostrar_lista_producto(Productos);
    printf("Ingrese el id del producto a eliminar: ");
    scanf("%d",&id_producto);
    
    if(remover_producto(&Productos,id_producto)==1){
        printf("Producto eliminado exitosamente\n");
        mostrar_lista_producto(Productos);
    }
    else 
        printf("Producto no encontrado\n");
}

int remover_producto(LST_PRODUCTO *p_lista,int id_producto){
    PRODUCTO *p_actual=p_lista->p_inicio,*p_anterior=NULL;
    while(p_actual!=NULL){
        if(id_producto==p_actual->id_producto){
            if(p_anterior==NULL)
                p_lista->p_inicio=p_actual->p_siguiente;
            else{
                p_anterior->p_siguiente=p_actual->p_siguiente;
            }    
            free(p_actual);
            return 1;
        }
    p_anterior=p_actual;
    p_actual=p_actual->p_siguiente;
    }
    return 0;
}

/*****************************************************************************
 Funciones de detalle venta
*****************************************************************************/
DETALLE_VENTA *p_nuevo_detalle_venta(void){
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
	}
    else{
        p_lista->p_inicio=p_nuevo;
        p_lista->p_fin=p_nuevo;      
    }    
}

void entrada_detalle_venta(int num_venta) {
    DETALLE_VENTA detalle_venta;
    int existencia_ok;
    char tecla;
    
    detalle_venta.num_venta = num_venta;

    do {                    
        do {
            existencia_ok = 0;
            printf("Numero de producto: ");
            scanf(" %d", &detalle_venta.num_producto);
            printf("Cantidad: ");
            scanf(" %d", &detalle_venta.cantidad);
            
            detalle_venta.p_producto = p_buscar_producto(Productos, detalle_venta.num_producto);
            if (detalle_venta.cantidad <= detalle_venta.p_producto->existencia) {
                detalle_venta.p_producto->existencia -= detalle_venta.cantidad;
                existencia_ok = 1;
            } else {
                printf("Solo hay %d existencias para el producto\nPor favor intente de nuevo\n",
                       detalle_venta.p_producto->existencia);
            }
        } while (existencia_ok == 0);

        detalle_venta.p_siguiente = NULL;
        agregar_detalle_venta(&Detalles, detalle_venta);
        
        printf("Presione [Enter] para agregar otro producto o [ESC] para terminar...\n");
        
        do {
            tecla = getch();
        } while (tecla != 13 && tecla != 27);
        
    } while (tecla != 27);
}

void mostrar_detalle_venta(DETALLE_VENTA detalle_venta){
    printf(" %-20d\t%-2d:%-60s\t%-20d\n", detalle_venta.num_venta,
            detalle_venta.num_producto,detalle_venta.p_producto->nombre_producto,detalle_venta.cantidad);
}

void mostrar_lista_detalle_venta(LST_DETALLE_VENTA lista){
    DETALLE_VENTA *p_actual=lista.p_inicio;
    
    while(p_actual!=NULL) {
        mostrar_detalle_venta(*p_actual);
        p_actual=p_actual->p_siguiente;
    }
}

void mostrar_lista_detalle_venta_por_num(LST_DETALLE_VENTA lista,int num_venta){
    DETALLE_VENTA *p_actual=lista.p_inicio;
    
	printf("Numero de venta:\tNumero y nombre de producto:\t\t\t\t\tCantidad:\n");
	
    while(p_actual!=NULL) {
        if (p_actual->num_venta==num_venta)
            mostrar_detalle_venta(*p_actual);
        p_actual=p_actual->p_siguiente;
    }
}

void limpiar_lista_detalle_venta(LST_DETALLE_VENTA *p_lista){
     DETALLE_VENTA *p_actual=p_lista->p_inicio;
     
    while(p_actual!=NULL){
         p_lista->p_inicio=p_actual->p_siguiente;
         free(p_actual);
         p_actual=p_lista->p_inicio;
    }
    p_lista->p_fin=NULL;

}

void leer_archivo_detalle_venta(){
    FILE *p_archivo;
    DETALLE_VENTA detalle;
    p_archivo=fopen(F_NOM_DETALLE_VENTAS,"r");
    
    limpiar_lista_detalle_venta(&Detalles);
    
    while(fscanf(p_archivo,"%d|%d|%d\n",&detalle.num_venta,&detalle.num_producto,&detalle.cantidad)!=EOF){
        detalle.p_producto=p_buscar_producto(Productos,detalle.num_producto);
          agregar_detalle_venta(&Detalles,detalle);
    }
    fclose(p_archivo); 
}

void guardar_archivo_detalle_venta(){
    FILE *p_archivo;
    DETALLE_VENTA *p_actual=Detalles.p_inicio;
    p_archivo=fopen(F_NOM_DETALLE_VENTAS,"w+");
    while(p_actual !=NULL){
        fprintf(p_archivo,"%d|%d|%d\n",p_actual->num_venta,p_actual->num_producto,p_actual->cantidad);
        p_actual=p_actual->p_siguiente;
    }
    fclose(p_archivo);   

}

float calcular_total_detalle_venta(LST_PRODUCTO lista_productos,LST_DETALLE_VENTA lista_ventas,int num_venta){
    DETALLE_VENTA *p_actual=lista_ventas.p_inicio;
    PRODUCTO *p_producto;
    float total=0.0;
    
    while(p_actual!=NULL){
        if(p_actual->num_venta==num_venta){
            p_producto=p_buscar_producto(lista_productos,p_actual->num_producto);
            if(p_actual->p_producto!=NULL)
                total=total+p_actual->cantidad*(p_producto->precio_venta);
        }
        
        p_actual=p_actual->p_siguiente;
    }
    return total;
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
	}
    else{
        p_lista->p_inicio=p_nuevo;
        p_lista->p_fin=p_nuevo;      
    }    
}

void entrada_venta(){
    VENTA venta;
    VENTA *p_venta_existente;

    do {
        printf("Numero de venta: ");
        scanf(" %d", &venta.num_venta);

        p_venta_existente = p_buscar_venta(Ventas, venta.num_venta);
        if (p_venta_existente != NULL)
            printf("Error: El numero de venta %d ya existe. Por favor, ingrese un numero diferente.\n", venta.num_venta);
    } while (p_venta_existente != NULL);

    venta.fecha = pedir_fecha("Fecha de venta en formato (yyyy-mm-dd): ");
    venta.hora = pedir_hora("Hora de venta en formato (hh:mm): ");

    entrada_detalle_venta(venta.num_venta);
    agregar_venta(&Ventas, venta);

    printf("Venta agregada con exito.\n");
}


void mostrar_venta(VENTA venta){
    char buffer[20];
    char buffer2[20];
    printf("Numero de venta:\tFecha:\t\t\t\t\t\t\t\tHora:\n");
printf(" %-20d\t%-60s\t%-20s\n", venta.num_venta, formatear_fecha(venta.fecha,buffer,20), formatear_hora(venta.hora,buffer2,sizeof(buffer2)));
    mostrar_lista_detalle_venta_por_num(Detalles,venta.num_venta);
}

void mostrar_lista_venta(LST_VENTA lista){
    VENTA *p_actual=lista.p_inicio;
   
   //printf("Numero de venta:\tFecha:\t\t\tHora:\n");

    while(p_actual!=NULL) {
        mostrar_venta(*p_actual);
        p_actual=p_actual->p_siguiente;
    }
}

void leer_archivo_venta(){
    
    FILE *p_archivo;
    VENTA venta;
    p_archivo=fopen(F_NOM_VENTAS,"r");
    
    limpiar_lista_venta(&Ventas);
    
    while(fscanf(p_archivo,"%d|%d|%d\n",&venta.num_venta,&venta.fecha,&venta.hora)!=EOF){
          agregar_venta(&Ventas,venta);
    }
    
    fclose(p_archivo); 

}
void guardar_archivo_venta(){
    FILE *p_archivo;
    VENTA *p_actual=Ventas.p_inicio;
    p_archivo=fopen(F_NOM_VENTAS,"w+");
    while(p_actual !=NULL){
        fprintf(p_archivo,"%d|%d|%d\n",p_actual->num_venta,p_actual->fecha,p_actual->hora);
        p_actual=p_actual->p_siguiente;
    }
    fclose(p_archivo);   

}

void limpiar_lista_venta(LST_VENTA *p_lista){
    VENTA *p_actual=p_lista->p_inicio;
     
    while(p_actual!=NULL){
         p_lista->p_inicio=p_actual->p_siguiente;
         free(p_actual);
         p_actual=p_lista->p_inicio;
    }
    p_lista->p_fin=NULL;    

}

VENTA *p_buscar_venta(LST_VENTA lista,int num_venta){
    VENTA *p_actual=lista.p_inicio;
    
    while(p_actual!=NULL){
        if(p_actual->num_venta==num_venta)
            return p_actual;
        p_actual=p_actual->p_siguiente;
    }
    return NULL;
}

void mostrar_busqueda_nota_venta(){
    int num_venta;
    
    printf("Ingrese el numero de nota de la venta que va a buscar: ");
    scanf("%d",&num_venta);
    VENTA *p_venta=p_buscar_venta(Ventas,num_venta);
    if(p_venta!=NULL)
       mostrar_venta(*p_venta); 
    else
        printf("No se encontro la nota\n");
}

void reporte_venta_dia_intervalo_nota(void){
    int fecha_inicio,fecha_fin,bandera_encabezado;
    float total;
    char buffer[20];
    VENTA *p_actual;

	fecha_inicio=pedir_fecha("Ingrese la fecha de inicio en formato (yyyy-mm-dd): ");
	fecha_fin=pedir_fecha("Ingrese la fecha de fin en formato (yyyy-mm-dd): ");
    
    for(int fecha=fecha_inicio;fecha<=fecha_fin;fecha=siguiente_dia(fecha)){
        bandera_encabezado=1; //Hay que mostrar el encabezado
        p_actual=Ventas.p_inicio;
        while(p_actual!=NULL){
            if(p_actual->fecha==fecha){
                if(bandera_encabezado==1){
                    printf("FECHA:\t%s\n",formatear_fecha(fecha,buffer,20));
                    bandera_encabezado=0;
                }
                total=calcular_total_detalle_venta(Productos,Detalles,p_actual->num_venta);
                printf("%3d\t$%.2f\n",p_actual->num_venta,total);
            }
            
            p_actual=p_actual->p_siguiente;
        }
    }    
}

void total_general_venta(LST_VENTA lista) {
    VENTA *p_actual = lista.p_inicio;
    int fecha_anterior = 0;
    float total, total_total = 0.0;
    char buffer[20];

    printf("TOTAL de ventas \n");

    while (p_actual != NULL) {
        if (p_actual->fecha != fecha_anterior) {
            fecha_anterior = p_actual->fecha;
            printf("FECHA:\t%s\n", formatear_fecha(p_actual->fecha, buffer, 20));
        }
		
		total = calcular_total_detalle_venta(Productos, Detalles, p_actual->num_venta);
        printf("%3d\t$%.2f\n", p_actual->num_venta, total);
        total_total += total;

        p_actual = p_actual->p_siguiente;
    }

    printf("TOTAL: \n$%.2lf\n", total_total);
}

/*****************************************************************************
 Menu productos
*****************************************************************************/
void menu_productos() {
	char opcion;
	do {
		LIMPIAR_PANTALLA;
		printf("Menu productos\n");
		printf("1. Agregar producto.\n");
		printf("2. Buscar producto por id.\n");
		printf("3. Eliminar producto.\n");
		printf("4. Listar productos\n");
		printf("5. Modificar productos\n");
		printf("6. Listar productos con existencia menor o igual a cinco\n");
		printf("7. Regresar a menu principal\n");
		printf("Ingresa tu opcion: \n");
		//scanf(" %d", &opcion);
		
		opcion = getch();
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
		PAUSA;
	} while (opcion != '7');
}

/*****************************************************************************
 Menu ventas
*****************************************************************************/
void menu_ventas() {
	char opcion;
	do {
		LIMPIAR_PANTALLA;
		printf("Menu ventas\n");
		printf("1. Agregar venta\n");
		printf("2. Buscar venta por numero de nota\n");
		printf("3. Listar ventas\n");
		printf("4. Total de ventas por dia, por intervalo de fechas y con numero de nota\n");
		printf("5. Total de ventas general\n");
		printf("6. Regresar a menu principal\n");
		printf("Ingresa tu opcion: ");
		//scanf(" %d",&opcion);
		
		opcion = getch();
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
		PAUSA;
	} while(opcion!='6');
}

/*****************************************************************************
 Manejo de fechas y horas
*****************************************************************************/
int siguiente_dia(int dia){
    int aux=0;
    struct tm fecha={
        .tm_sec=0,
        .tm_min=0,
        .tm_hour=0,
        .tm_year=dia/10000-1900,
        .tm_mon=((dia%10000)/100)-1,
        .tm_mday=dia%100,
        .tm_yday=0,
        .tm_isdst=0
    };
    time_t segundos_fecha=mktime(&fecha);
    
    segundos_fecha+=24*60*60;
    fecha=*localtime(&segundos_fecha);
    aux+=(fecha.tm_year+1900)*10000;
    aux+=(fecha.tm_mon+1)*100;
    aux+=fecha.tm_mday;
    return aux;
}

int pedir_hora(char *p_impresion_usuario){
    int horas,minutos,valido;
    do{
        printf(p_impresion_usuario);
        scanf("%d:%d",&horas,&minutos);
        //validar horas y minutos
        if(horas>=0 && horas<60 && minutos>=0 && minutos<60)
            valido=1;
        else{
            valido=0;
            printf("El rango de horas es de 0 a 23 y el de minutos de 0 a 59\n");
        }
    }while(valido==0);
    return horas*100+minutos;
}

int pedir_fecha(char *p_impresion_usuario){
    int year, mon, mday,aux;
    do{
        printf(p_impresion_usuario);
        scanf("%d-%d-%d", &year,&mon,&mday);
        aux=validar_fecha(year, mon, mday);
        if(aux==0)
           printf("La fecha es invalida, vuelva a intentar\n"); 
    }while(aux==0);   
    return (year*10000)+(mon*100)+mday;
}

int validar_fecha(int year, int mon, int mday){
    int fecha;
    if(year<=0)
        return 0;
    if(mon<1 || mon>12)
        return 0;
    if(mday<1 || mday>31)
        return 0;
    fecha=(year*10000)+(mon*100)+mday;
    
    if(fecha == reestructura_fecha(fecha))
        return 1;
    return 0;
}


int reestructura_fecha (int fecha){
    int year, mon, mday;
    struct tm aux={
        .tm_sec=0,
        .tm_min=0,
        .tm_hour=0,
        .tm_mday=0,
        .tm_mon=0,
        .tm_year=0,
        .tm_yday=0,
        .tm_isdst=0
    };
    time_t segundos_fecha;
    year = (fecha/10000)-1900;
    mon = ((fecha%10000)/100)-1;
    mday = fecha%100;
    
    aux.tm_year = year;
    aux.tm_mon = mon;
    aux.tm_mday = mday;
    
    segundos_fecha=mktime(&aux);
    aux=*localtime(&segundos_fecha);
    year=aux.tm_year+1900;
    mon=aux.tm_mon+1;
    mday=aux.tm_mday;
    fecha=(year*10000)+(mon*100)+mday;
    
    return fecha;   
}

char *formatear_hora(int hora,char buffer[],int tam_buffer){
    int horas, minutos; 
    horas=hora/100;
    minutos=hora%100;
    sprintf(buffer,"%02d:%02d",horas,minutos);
    return buffer;
}

char *formatear_fecha(int fecha,char buffer[],int tam_buffer){
    struct tm tm_fecha={
        .tm_sec=0,
        .tm_min=0,
        .tm_hour=0,
        .tm_mday=fecha%100,
        .tm_mon=((fecha%10000)/100)-1,
        .tm_year=(fecha/10000)-1900,
        .tm_yday=0,
        .tm_isdst=0        
    };
    strftime(buffer,tam_buffer,"%Y-%m-%d",&tm_fecha);
    return buffer;
}

/*****************************************************************************
 Funcion principal
*****************************************************************************/
int main() {
	char opcion;
    
    leer_archivo_producto();
    leer_archivo_venta();
    leer_archivo_detalle_venta();
    
	do {
		LIMPIAR_PANTALLA;
		printf("Menu principal");
		printf("\n1. Menu Productos");
		printf("\n2. Menu Ventas");
		printf("\n3. Salir");
		printf("\nOpcion: ");
		//scanf("%d", &opcion);
		
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
				PAUSA;
				break;
			default:
				printf("Opcion invalida\n");
				PAUSA;
				break;
		}
	} while (opcion != '3');
    
    guardar_archivo_producto();
    guardar_archivo_venta();
    guardar_archivo_detalle_venta();
    
	return 0;
}
