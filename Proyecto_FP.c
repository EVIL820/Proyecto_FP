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
	int fecha_vta;
	int hora_vta;
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
void cargarDatosProductos();
void cargarDatosClientes();
void cargarDatosVentas();
void cargarDatosDetalleVtas();
void guardarDatos();
void guardarDatosProductos();
void guardarDatosClientes();
void guardarDatosVentas();
void guardarDatosDetalleVtas();
void menuProductos();
void menuClientes();
void menuVentas();
void agregarProducto();
void agregarCliente();
void agregarVenta();
void generarDetalleVta();
void borrarProducto();
void borrarCliente();
void borrarVenta();
void listarProductos();
void listarClientes();
void listarVentas();
void buscarCliente();
void editarCliente();
void buscarVenta();
void limpiarPantalla();
void pausar();

// Variables globales
struct Producto *productos = NULL;
struct Cliente *clientes = NULL;
struct Venta *ventas = NULL;
struct DetalleVta *detallesVta = NULL;

// Inicializar archivos si no existen
void inicializarArchivos() {
	const char *archivos[] = {
		"Productos.txt",
		"Clientes.txt",
		"Ventas.txt",
		"Detalle_ventas.txt"
	};

	for (int x = 0; x < 4; x++) {
		FILE *archivo = fopen(archivos[x], "r");
		if (!archivo) {
			archivo = fopen(archivos[x], "w+");
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
	cargarDatosProductos();
	cargarDatosClientes();
	cargarDatosVentas();
	cargarDatosDetalleVtas();
}

void cargarDatosProductos() {
	FILE *Prod = fopen("Productos.txt", "r");

	if (Prod) {
		struct Producto tempProd;
		while (fscanf(Prod, "%d|%[^|]|%f|%d|%f", &tempProd.id_prod, tempProd.nom_prod, &tempProd.precio_compra_prod, &tempProd.existencia_prod, &tempProd.precio_venta_prod) != EOF) {
			struct Producto *nuevo = (struct Producto *)malloc(sizeof(struct Producto));
			*nuevo = tempProd;
			nuevo->sig = NULL;

			if (!productos) {
				productos = nuevo;
			} else {
				struct Producto *actual = productos;
				while (actual->sig) {
					actual = actual->sig;
				}
				actual->sig = nuevo;
			}
		}
		fclose(Prod);
		printf("Productos cargados correctamente.\n");
	} else {
		printf("Error al cargar productos.\n");
	}
}

void cargarDatosClientes() {

	FILE *Cli = fopen("Clientes.txt", "r");
	if (Cli) {
		struct Cliente tempCli;
		while (fscanf(Cli, "%d|%[^|]|%s", &tempCli.id_cli, tempCli.nom_cli, tempCli.tel_cli) != EOF) {
			struct Cliente *nuevo = (struct Cliente *)malloc(sizeof(struct Cliente));
			*nuevo = tempCli;
			nuevo->sig = NULL;

			if (!clientes) {
				clientes = nuevo;
			} else {
				struct Cliente *actual = clientes;
				while (actual->sig) {
					actual = actual->sig;
				}
				actual->sig = nuevo;
			}
		}
		fclose(Cli);
		printf("Clientes cargados correctamente.\n");
	} else {
		printf("Error al cargar clientes.\n");
	}
}

void cargarDatosVentas() {

	FILE *Vta = fopen("Ventas.txt", "r");
	if (Vta) {
		struct Venta tempVta;
		while (fscanf(Vta, "%d|%d|%d|%d|%f", &tempVta.num_vta, tempVta.fecha_vta, tempVta.hora_vta, &tempVta.num_cli, &tempVta.total_vta) != EOF) {
			struct Venta *nuevo = (struct Venta *)malloc(sizeof(struct Venta));
			*nuevo = tempVta;
			nuevo->sig = NULL;

			if (!ventas) {
				ventas = nuevo;
			} else {
				struct Venta *actual = ventas;
				while (actual->sig) {
					actual = actual->sig;
				}
				actual->sig = nuevo;
			}
		}
		fclose(Vta);
		printf("Ventas cargadas correctamente.\n");
	} else {
		printf("Error al cargar ventas.\n");
	}
}

void cargarDatosDetalleVtas() {

	FILE *Det = fopen("Detalle_ventas.txt", "r");

	if (Det) {
		struct DetalleVta tempDet;
		while (fscanf(Det, "%d|%d|%d|%f", &tempDet.num_vta, &tempDet.num_prod, &tempDet.cant_prod, &tempDet.subtotal) != EOF) {
			struct DetalleVta *nuevo = (struct DetalleVta *)malloc(sizeof(struct DetalleVta));
			*nuevo = tempDet;
			nuevo->sig = NULL;

			if (!detallesVta) {
				detallesVta = nuevo;
			} else {
				struct DetalleVta *actual = detallesVta;
				while (actual->sig) {
					actual = actual->sig;
				}
				actual->sig = nuevo;
			}
		}
		fclose(Det);
		printf("Detalles de ventas cargados correctamente.\n");
	} else {
		printf("Error al cargar detalles de ventas.\n");
	}
}

// Guardar datos en archivos
void guardarDatos() {
	guardarDatosProductos();
	guardarDatosClientes();
	guardarDatosVentas();
	guardarDatosDetalleVtas();
}

void guardarDatosProductos() {
	FILE *Prod = fopen("Productos.txt", "w+");

	struct Producto *prod = productos;
	while (prod) {
		fprintf(Prod, "%d|%s|%.2f|%d|%.2f\n", prod->id_prod, prod->nom_prod, prod->precio_compra_prod, prod->existencia_prod, prod->precio_venta_prod);
		prod = prod->sig;
	}
	fclose(Prod);

	printf("Los datos se han guardado con exito.\n");
}
void guardarDatosClientes() {
	FILE *Cli = fopen("Clientes.txt", "w+");

	struct Cliente *cli = clientes;
	while (cli) {
		fprintf(Cli, "%d|%s|%s\n", cli->id_cli, cli->nom_cli, cli->tel_cli);
		cli = cli->sig;
	}
	fclose(Cli);

	printf("Los datos se han guardado con exito.\n");
}
void guardarDatosVentas() {
	FILE *Vta = fopen("Ventas.txt", "w+");

	struct Venta *vta = ventas;
	while (vta) {
		fprintf(Vta, "%d|%d|%d|%d|%.2f\n", vta->num_vta, vta->fecha_vta, vta->hora_vta, vta->num_cli, vta->total_vta);
		vta = vta->sig;
	}
	fclose(Vta);

	printf("Los datos se han guardado con exito.\n");
}
void guardarDatosDetalleVtas() {
	FILE *Det = fopen("Detalle_ventas.txt", "w+");

	struct DetalleVta *det = detallesVta;
	while (det) {
		fprintf(Det, "%d|%d|%d|%.2f\n", det->num_vta, det->num_prod, det->cant_prod, det->subtotal);
		det = det->sig;
	}
	fclose(Det);

	printf("Los datos se han guardado con exito.\n");
}

void menuProductos() {
	int opcion;
	do {
		limpiarPantalla();
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
				agregarProducto();
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				listarProductos();
				break;
			case 5:
				guardarDatosProductos();
				break;
			case 6:
				printf("Volviendo al menu principal");
				break;
			default:
				printf("\nOpcion invalida\n presiona una tecla para continuar");
				break;
		}
		pausar();
	} while (opcion != 6);
}

void menuClientes() {
	int opcion;
	do {
		limpiarPantalla();
		printf("Menu clientes");
		printf("\n1. Agregar cliente");
		printf("\n2. Borrar cliente");
		printf("\n3. Buscar cliente");
		printf("\n4. Editar cliente");
		printf("\n5. Listar clientes");
		printf("\n6. Guardar clientes");
		printf("\n7. Regresar a menu principal");
		printf("\nIngresa tu opcion: ");
		scanf(" %d",&opcion);
		switch (opcion) {
			case 1:
				agregarCliente();
				break;
			case 2:
				break;
			case 3:
				buscarCliente();
				break;
			case 4:
				editarCliente();
				break;
			case 5:
				listarClientes();
				break;
			case 6:
				guardarDatosClientes();
				break;
			case 7:
				printf("Volviendo al menu principal");
				break;
			default:
				printf("\nOpcion invalida\n presiona una tecla para continuar");
				break;
		}
		pausar();
	} while(opcion!=7);
}

void menuVentas() {
	int opcion;
	do {
		limpiarPantalla();
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
				agregarVenta();
				break;
			case 2:
				break;
			case 3:
				buscarVenta();
				break;
			case 4:
				listarVentas();
				break;
			case 5:
				generarDetalleVta();
				break;
			case 6:
				printf("Volviendo al menu principal");
				break;
			default:
				printf("\nOpcion invalida\n presiona una tecla para continuar");
				break;
		}
		pausar();
	} while(opcion!=6);
}

void agregarProducto() {
	struct Producto *nuevoProducto = (struct Producto *)malloc(sizeof(struct Producto));
	if (!nuevoProducto) {
		printf("\nError al agregar datos\n");
		return;
	}

	printf("\nIngrese ID del producto: ");
	scanf("%d", &nuevoProducto->id_prod);
	printf("\nNombre del producto: ");
	scanf(" %49[^\n]", nuevoProducto->nom_prod);
	printf("\nPrecio de compra: ");
	scanf("%f", &nuevoProducto->precio_compra_prod);
	printf("\nExistencias: ");
	scanf("%d", &nuevoProducto->existencia_prod);
	printf("\nPrecio de venta: ");
	scanf("%f", &nuevoProducto->precio_venta_prod);

	nuevoProducto->sig = NULL;

	if (!productos) {
		productos = nuevoProducto;
	} else {
		struct Producto *actual = productos;
		while (actual->sig)
			actual = actual->sig;
		actual->sig = nuevoProducto;
	}

	printf("Producto agregado exitosamente.\n");
}


void agregarCliente() {
	struct Cliente *nuevoCliente = (struct Cliente *)malloc(sizeof(struct Cliente));
	if (!nuevoCliente) {
		printf("\nError al agregar datos\n");
		return;
	}

	printf("\nIngrese ID del cliente: ");
	scanf("%d", &nuevoCliente->id_cli);
	printf("\nNombre del cliente: ");
	scanf(" %49[^\n]", nuevoCliente->nom_cli);
	printf("\nTelefono del cliente: ");
	scanf(" %14[^\n]", &nuevoCliente->tel_cli);

	nuevoCliente->sig = NULL;

	if (!clientes) {
		clientes = nuevoCliente;
	} else {
		struct Cliente *actual = clientes;
		while (actual->sig)
			actual = actual->sig;
		actual->sig = nuevoCliente;
	}

	printf("Cliente agregado exitosamente.\n");
}

void agregarVenta() {
}

void generarDetalleVta() {
}

void borrarProducto() {
}

void borrarCliente() {
}

void borrarVenta() {
}

void listarProductos() {
	if (!productos) {
		printf("No hay productos para mostrar.\n");
		return;
	}
	struct Producto *prod = productos;
	while (prod) {
		printf("ID: %d, Nombre: %s, Precio Compra: %.2f, Precio Venta: %.2f, Existencia: %d",
		       prod->id_prod, prod->nom_prod, prod->precio_compra_prod, prod->precio_venta_prod, prod->existencia_prod);
		prod = prod->sig;
	}
}

void listarClientes() {
	if (!clientes) {
		printf("No hay clientes para mostrar.\n");
		return;
	}

	struct Cliente *cli = clientes;
	while (cli) {
		printf("ID: %d, Nombre: %s, Telefono: %s\n", cli->id_cli, cli->nom_cli, cli->tel_cli);
		cli = cli->sig;
	}
}

void listarVentas() {
}

void buscarCliente() {
	int id_cliente;
	printf("Ingrese el ID del cliente a buscar: ");
	scanf("%d", &id_cliente);

	struct Cliente *actual = clientes;
	while (actual) {
		if (actual->id_cli == id_cliente) {
			printf("\nCliente encontrado:");
			printf("\nID: %d, Nombre: %s, Telefono: %s\n", actual->id_cli, actual->nom_cli, actual->tel_cli);
			return;
		}
		actual = actual->sig;
	}

	printf("Cliente con ID %d no encontrado.\n", id_cliente);
}

void editarCliente() {
	int id_cliente, opc;
	printf("Ingrese el ID del cliente a editar: ");
	scanf("%d", &id_cliente);

	struct Cliente *actual = clientes;
	while (actual) {
		if (actual->id_cli == id_cliente) {
			printf("\nCliente encontrado");
			do {
				limpiarPantalla();
				printf("Seleccione la opcion a editar: ");
				printf("\n1. Nombre del cliente");
				printf("\n2. Telefono del cliente");
				printf("\n3. Volver al menu clientes");
				printf("\nIngresa tu opcion: ");
				scanf("%d", &opc);
				switch (opc) {
					case 1:
						printf("Ingrese el nombre a editar: ");
						scanf(" %49[^\n]", actual->nom_cli);
						printf("\nNombre actualizado correctamente.");
						break;
					case 2:
						printf("Ingrese el telefono a editar: ");
						scanf(" %14[^\n]", actual->tel_cli);
						printf("\nTelefono actualizado correctamente.");
						break;
					case 3:
						printf("Volviendo al menu clientes...\n");
						break;
					default:
						printf("Opcion invalida.\n");
				}
				pausar();
			} while (opc != 3);

			return;
		}
		actual = actual->sig;
	}

	printf("Cliente con ID %d no encontrado.\n", id_cliente);
}

void buscarVenta() {
}

// Función principal
int main() {
	int opcion;
	inicializarArchivos();
	cargarDatos();

	do {
		limpiarPantalla();
		printf("Menu principal");
		printf("\n1. Menu Productos");
		printf("\n2. Menu Clientes");
		printf("\n3. Menu Ventas");
		printf("\n5. Guardar todos los datos");
		printf("\n6. Salir");
		printf("\nOpcion: ");
		scanf("%d", &opcion);

		switch (opcion) {
			case 1:
				menuProductos();
				break;
			case 2:
				menuClientes();
				break;
			case 3:
				menuVentas();
				break;
			case 4:
				generarDetalleVta();
				break;
			case 5:
				guardarDatos();
				break;
			case 6:
				printf("Saliendo del programa. Tenga buen dia.");
				break;
			default:
				printf("Opcion invalida\n");
				pausar();
				break;
		}
		pausar();
	} while (opcion != 6);

	return 0;
}

void limpiarPantalla() {
	if (_WIN32)
		system("cls");
	else
		printf("\033[H\033[J");
}

void pausar() {
	printf("Presiona Enter para continuar...");
	while (getchar() != '\n');
	getchar();
}