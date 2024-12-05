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

// Inicializar archivos si no existen
void inicializarArchivos() {
	const char *archivos[] = {
		"productos.txt",
		"clientes.txt",
		"ventas.txt",
		"detalle_ventas.txt"
	};

	for (int x = 0; x < 4; x++) {
		FILE *archivo = fopen(archivos[x], "r");
		if (!archivo) {
			archivo = fopen(archivos[x], "w");
			if(archivo) {
				printf("Archivo '%s' creado correctamente.\n", archivos[x]);
			} else {
				printf("Error al crear el archivo '%s'.\n", archivos[x]);
			}
			fclose(archivo);
		}
	}
}

// Cargar datos desde archivos
void cargarDatos() {
	FILE *Prod = fopen("productos.txt", "r");
	FILE *Cli = fopen("Clientes.txt", "r");
	FILE *Vta = fopen("ventas.txt", "r");
	FILE *Det = fopen("detalle_ventas.txt", "r");

	if (Prod) {
		struct Producto tempProd;
		while (fscanf(Prod, "%d %49s %f %d %f", &tempProd.id_prod, tempProd.nom_prod, &tempProd.precio_compra_prod, &tempProd.existencia_prod, &tempProd.precio_venta_prod) != EOF) {
			struct Producto *nuevo = (struct Producto *)malloc(sizeof(struct Producto));
			*nuevo = tempProd;
			nuevo->sig = productos;
			productos = nuevo;
		}
		fclose(Prod);
		printf("Productos cargados correctamente.\n");
	} else {
		printf("Error al cargar productos.\n");
	}

	if (Cli) {
		struct Cliente tempCli;
		while (fscanf(Cli, "%d %49s %14s", &tempCli.id_cli, tempCli.nom_cli, tempCli.tel_cli) != EOF) {
			struct Cliente *nuevo = (struct Cliente *)malloc(sizeof(struct Cliente));
			*nuevo = tempCli;
			nuevo->sig = clientes;
			clientes = nuevo;
		}
		fclose(Cli);
		printf("Clientes cargados correctamente.\n");
	} else {
		printf("Error al cargar clientes.\n");
	}

	if (Vta) {
		struct Venta tempVta;
		while (fscanf(Vta, "%d %19s %9s %d %f", &tempVta.num_vta, tempVta.fecha_vta,
		              tempVta.hora_vta, &tempVta.num_cli, &tempVta.total_vta) != EOF) {
			struct Venta *nuevo = (struct Venta *)malloc(sizeof(struct Venta));
			*nuevo = tempVta;
			nuevo->sig = ventas;
			ventas = nuevo;
		}
		fclose(Vta);
		printf("Ventas cargadas correctamente.\n");
	} else {
		printf("Error al cargar ventas.\n");
	}

	if (Det) {
		struct DetalleVta tempDet;
		while (fscanf(Det, "%d %d %d %f", &tempDet.num_vta, &tempDet.num_prod, &tempDet.cant_prod, &tempDet.subtotal) != EOF) {
			struct DetalleVta *nuevo = (struct DetalleVta *)malloc(sizeof(struct DetalleVta));
			*nuevo = tempDet;
			nuevo->sig = detallesVta;
			detallesVta = nuevo;
		}
		fclose(Det);
		printf("Detalles de ventas cargados correctamente.\n");
	} else {
		printf("Error al cargar detalles de ventas.\n");
	}
}

// Guardar datos en archivos
void guardarDatos() {
	FILE *Prod = fopen("productos.txt", "w+");
	FILE *Cli = fopen("clientes.txt", "w+");
	FILE *Vta = fopen("ventas.txt", "w+");
	FILE *Det = fopen("detalle_ventas.txt", "w+");

	struct Producto *prod = productos;
	while (prod) {
		fprintf(Prod, "%d %s %.2f %d %.2f\n", prod->id_prod, prod->nom_prod, prod->precio_compra_prod, prod->existencia_prod, prod->precio_venta_prod);
		prod = prod->sig;
	}
	fclose(Prod);

	struct Cliente *cli = clientes;
	while (cli) {
		fprintf(Cli, "%d %s %s\n", cli->id_cli, cli->nom_cli, cli->tel_cli);
		cli = cli->sig;
	}
	fclose(Cli);

	struct Venta *vta = ventas;
	while (vta) {
		fprintf(Vta, "%d %s %s %d %.2f\n", vta->num_vta, vta->fecha_vta, vta->hora_vta, vta->num_cli, vta->total_vta);
		vta = vta->sig;
	}
	fclose(Vta);

	struct DetalleVta *det = detallesVta;
	while (det) {
		fprintf(Det, "%d %d %d %.2f\n", det->num_vta, det->num_prod, det->cant_prod, det->subtotal);
		det = det->sig;
	}
	fclose(Det);
	
	// Imprimir mensaje de éxito
	printf("Los datos se han guardado con exito en los archivos.\n");
}

void agregarProducto(){
}

void agregarCliente(){
}

void agregarVenta(){
}

void generarDetalleVta(){
}

void listarProductos(){
}

void listarClientes(){
}

void listarVentas(){
}

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
				break;
		}
		system("pause");
		system("cls");
	} while (opcion != 8);

	return 0;
}