#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMPIAR_PANTALLA system("cls")
#define PAUSA system("pause")

/*****************************************************************************
 Definicion de estructuras
*****************************************************************************/
typedef struct stc_producto {
    int id_producto;
    char nombre_producto[101];
    float precio_compra;
    int existencia;
    float precio_venta;
    struct stc_producto *siguiente;
} tipo_producto;

typedef struct stc_lista_productos{
    tipo_producto *inicio;
    tipo_producto *fin;
} tipo_lst_productos;

typedef struct stc_cliente {
    int id_cliente;
    char nombre[101];
    char telefono[11];
    struct stc_cliente *siguiente;
} tipo_cliente;

typedef struct stc_lista_clientes{
    tipo_cliente *inicio;
    tipo_cliente *fin;
} tipo_lst_clientes;

typedef struct stc_detalle_venta {
    int num_venta;
    int num_producto;
    int cantidad;
    tipo_producto *producto;
    struct stc_detalle_venta *siguiente;
} tipo_detalle_venta;

typedef struct stc_lista_detalle{
    tipo_detalle_venta *inicio;
    tipo_detalle_venta *fin;
} tipo_lst_detalle;

typedef struct stc_venta {
    int num_venta;
    int fecha;
    int hora;
    int num_cliente;
    tipo_cliente *cliente;
    tipo_lst_detalle detalle;
    struct stc_venta *siguiente;
} tipo_venta;

typedef struct stc_lista_ventas{
    tipo_venta *inicio;
    tipo_venta *fin;
} tipo_lst_ventas;

/*****************************************************************************
 Definicion de prototipos
*****************************************************************************/
tipo_producto *malloc_producto();
tipo_cliente *malloc_cliente();
tipo_detalle_venta *malloc_detalle();
tipo_venta *malloc_venta();
void menu_clientes();
void menu_productos();
void menu_ventas();
void leer_archivo_clientes();
void limpiar_lista_clientes(tipo_lst_clientes*);
void insertar_cliente(tipo_lst_clientes*,tipo_cliente*);
void mostrar_clientes(tipo_lst_clientes);
tipo_cliente *buscar_cliente(int,tipo_lst_clientes);
void solicitar_buscar_cliente();
void no_implementado();

/*****************************************************************************
 Variables globales
*****************************************************************************/
tipo_lst_productos Productos;
tipo_lst_clientes Clientes;
tipo_lst_ventas Ventas;

/*****************************************************************************
 Implementacion de funciones generales o temporales(pruebas)
*****************************************************************************/
void no_implementado(){
    printf("Aun no implementado\n presiona una tecla para continuar");
    PAUSA;
}

/*****************************************************************************
 Implementacion de funciones de asignacion de memoria
*****************************************************************************/
tipo_producto *malloc_producto(){
    tipo_producto *aux=malloc(sizeof(tipo_producto));
    int i;
    if (aux!=NULL){
        aux->id_producto=0;
        for(i=0;i<sizeof(aux->nombre_producto);i++)
            aux->nombre_producto[i]=0;
        aux->precio_compra=0;
        aux->existencia=0;
        aux->precio_venta=0;
        aux->siguiente=NULL;
    }
    return aux;
}

tipo_cliente *malloc_cliente(){
    tipo_cliente *aux=malloc(sizeof(tipo_cliente));
    int i;
    if (aux!=NULL){
        aux->id_cliente=0;
        for(i=0;i<sizeof(aux->nombre);i++)
            aux->nombre[i]=0;
        for(i=0;i<sizeof(aux->telefono);i++)
            aux->telefono[i]=0;
        aux->siguiente=NULL;
    }
    return aux;
}

tipo_detalle_venta *malloc_detalle(){
    tipo_detalle_venta *aux=malloc(sizeof(tipo_detalle_venta));
    if (aux!=NULL){
        aux->num_venta=0;
        aux->num_producto=0;
        aux->cantidad=0;
        aux->producto=NULL;
        aux->siguiente=NULL;
    }
    return aux;
}

tipo_venta *malloc_venta(){
    tipo_venta *aux=malloc(sizeof(tipo_detalle_venta));
    if (aux!=NULL){
        aux->num_venta=0;
        aux->fecha=0;
        aux->hora=0;
        aux->num_cliente=0;
        aux->cliente=NULL;
        aux->detalle.inicio=NULL;
        aux->detalle.fin=NULL;
        aux->siguiente=NULL;
    }
    return aux;
}

/*****************************************************************************
 Implementacion de funciones para cliente
*****************************************************************************/
void menu_clientes(){
    int opcion;
    do{
        LIMPIAR_PANTALLA;
        printf("Menu clientes\n"
               "1. Agregar cliente\n"
               "2. Cargar de archivo\n"
               "3. Guardar en archivo\n"
               "4. Borrar cliente\n"
               "5. Buscar cliente\n"
               "6. Listar clientes\n"
               "7. Regresar a menu principal\n"
               "Ingresa tu opcion: ");
        scanf(" %d",&opcion);
        switch (opcion){
            case 1:
                no_implementado();
                break;
            case 2:
                leer_archivo_clientes();
                break;
            case 3:
                no_implementado();
                break;
            case 4:
                no_implementado();
                break;
            case 5:
                solicitar_buscar_cliente();
                break;
            case 6:
                mostrar_clientes(Clientes);
                break;
            case 7:
                break;
            default:
                printf("Opcion invalida\n presiona una tecla para continuar");
                PAUSA;
                break;
        }
    }while(opcion!=7);
}

void leer_archivo_clientes(){
    FILE *archivo;
    tipo_cliente *cliente=NULL;
    if((archivo=fopen("Clientes.txt","r"))!=NULL){
        limpiar_lista_clientes(&Clientes);//Limpia la lista guardada en ese momento
        cliente=malloc_cliente();
        while(fscanf(archivo,"%d|%[^|]|%[^\n]",&cliente->id_cliente,cliente->nombre,cliente->telefono)!=EOF){
            insertar_cliente(&Clientes,cliente);//Esta funcion guarda la lectura del archivo
                                                   //recibe la lista y al cliente 
            cliente=malloc_cliente();
        }
        free(cliente);
        fclose(archivo);
    }
}

void limpiar_lista_clientes(tipo_lst_clientes *lista){
    tipo_cliente *siguiente;
    while(lista->inicio!=NULL){
        siguiente=lista->inicio->siguiente;
        free(lista->inicio);
        lista->inicio=siguiente;
    }
    lista->fin=NULL;
}

void insertar_cliente(tipo_lst_clientes *lista,tipo_cliente *cliente){
    if(lista->inicio==NULL){
        lista->inicio=cliente;
        lista->fin=cliente;
    }
    else{
        lista->fin->siguiente=cliente;
        lista->fin=cliente;
    }
    cliente->siguiente=NULL;
}

void mostrar_clientes(tipo_lst_clientes clientes){
    tipo_cliente *actual=clientes.inicio;
    while(actual!=NULL){
        printf("%d\t%s\t%s\n",actual->id_cliente, actual->nombre, actual->telefono);
        actual=actual->siguiente;
    }
    PAUSA;
}

tipo_cliente *buscar_cliente(int id_cliente,tipo_lst_clientes clientes){
    tipo_cliente *actual=clientes.inicio;
    while(actual!=NULL){
        if(actual->id_cliente==id_cliente)
            return actual;
        actual=actual->siguiente;
    }
    return NULL;
}

void solicitar_buscar_cliente(){
    int id_cliente;
    tipo_cliente *cliente;
    
    printf("Id del cliente: ");
    scanf("%d",&id_cliente);
    cliente=buscar_cliente(id_cliente,Clientes);
    if(cliente!=NULL){
        printf("%d\t%s\t%s\n",cliente->id_cliente, cliente->nombre, cliente->telefono);
    }
    PAUSA;
}

/*****************************************************************************
 Implementacion de funciones para productos
*****************************************************************************/
void menu_productos(){
    printf("Aun no implementado\n presiona una tecla para continuar");
    PAUSA;
}

/*****************************************************************************
 Implementacion de funciones para ventas
*****************************************************************************/
void menu_ventas(){
    printf("Aun no implementado\n presiona una tecla para continuar");
    PAUSA;
}

/*****************************************************************************
 Main
*****************************************************************************/
int main(){
    int opcion;
    do{
        LIMPIAR_PANTALLA;
        printf("Menu principal\n"
               "1. Clientes\n"
               "2. Productos\n"
               "3. Ventas\n"
               "4. Salir\n"
               "Ingresa tu opcion: ");
        scanf(" %d",&opcion);
        switch (opcion){
            case 1:
                menu_clientes();
                break;
            case 2:
                menu_productos();
                break;
            case 3:
                menu_ventas();
                break;
            case 4:
                break;
            default:
                printf("Opcion invalida\n presiona una tecla para continuar");
                PAUSA;
                break;
        }
    }while(opcion!=4);
}