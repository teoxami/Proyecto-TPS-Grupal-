//Buenaño Melanie, Teo Maita

#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_PRODUCTOS 100
#define MAX_ITEMS 30
#define STOCK_BAJO 5

/* ============ ESTRUCTURAS ============ */

typedef struct {
    int id;
    char nombre[40];
    float precio;
    int stock;
} Producto;

typedef struct {
    int id;
    char nombre[40];
    float precio;
    int cantidad;
    float ivaPorc;
    float subtotal;
    float ivaValor;
    float total;
} ItemTicket;

/* ============ VARIABLES GLOBALES ============ */

Producto productos[MAX_PRODUCTOS];
int totalProductos = 0;

int cajaAbierta = 0;
float totalCaja = 0;
int totalVentas = 0;

/* ============ PROTOTIPOS ============ */

void cargarProductos();
void menuPrincipal();

/* Productos */
void menuProductos();
void listarProductos();
void registrarProducto();
void eliminarProducto();
void modificarPrecio();
void ordenarProductos();

/* Inventario */
void menuInventario();
void ajustarStock();

/* Ventas */
void menuVentas();
void realizarVenta();
float seleccionarIVA();
void mostrarTicket(ItemTicket ticket[], int n, float sub, float iva, float total);
void advertenciaStock();

/* Caja */
void menuCaja();
void abrirCaja();
void cerrarCaja();

/* Reportes */
void menuReportes();
void reporteGeneral();
void reporteStockBajo();

/* Utilidades */
int buscarProductoID(int id);

/* ============ CARGA PRECARGADA (PANADERÍA) ============ */

void cargarProductos() {
    // Definimos un inventario base de 50 productos
    Producto inventarioBase[] = {
        {1, "Pan Batido", 0.15, 100}, {2, "Pan de Molde", 2.50, 20}, {3, "Baguette", 1.20, 30},
        {4, "Pan de Dulce", 0.25, 50}, {5, "Croissant", 0.85, 40}, {6, "Pan de Queso", 0.50, 60},
        {7, "Donas Chocolate", 1.00, 25}, {8, "Dona Glaseada", 0.80, 25}, {9, "Pastel de Manzana", 12.00, 5},
        {10, "Pastel de Chocolate", 15.00, 4}, {11, "Galletas de Avena", 0.40, 80}, {12, "Galletas Chispas", 0.50, 80},
        {13, "Empanada de Carne", 1.50, 15}, {14, "Empanada de Pollo", 1.50, 15}, {15, "Empanada Queso", 1.25, 20},
        {16, "Muffin Vainilla", 1.20, 18}, {17, "Muffin Arandanos", 1.40, 12}, {18, "Cachitos", 0.30, 45},
        {19, "Pan Integral", 1.80, 15}, {20, "Pan con Nueces", 3.00, 10}, {21, "Alfajor Maicena", 0.75, 30},
        {22, "Alfajor Chocolate", 1.10, 25}, {23, "Oreja (Hojaldre)", 0.60, 20}, {24, "Milhojas", 1.50, 12},
        {25, "Relampago", 1.30, 15}, {26, "Brazo Gitano", 8.50, 6}, {27, "Cheesecake", 2.50, 10},
        {28, "Tarta de Limon", 2.00, 10}, {29, "Pan de Ajo", 0.90, 15}, {30, "Pan de Maiz", 0.60, 20},
        {31, "Cafe Americano", 1.50, 50}, {32, "Cafe con Leche", 1.80, 50}, {33, "Capuccino", 2.25, 40},
        {34, "Chocolate Caliente", 2.00, 30}, {35, "Te Variados", 1.00, 100}, {36, "Jugo de Naranja", 2.50, 20},
        {37, "Agua Mineral", 1.00, 30}, {38, "Gaseosa 500ml", 1.25, 24}, {39, "Leche Entera 1L", 1.10, 12},
        {40, "Yogurt Natural", 1.50, 10}, {41, "Mermelada Fresa", 3.50, 8}, {42, "Mantequilla 200g", 2.20, 15},
        {43, "Huevo (unidad)", 0.15, 120}, {44, "Queso Fresco", 3.00, 8}, {45, "Jamón Cocido", 4.00, 10},
        {46, "Brownie", 1.50, 20}, {47, "Suspiros", 0.10, 200}, {48, "Pan de Yuca", 0.60, 40},
        {49, "Rosca de Reyes", 10.00, 3}, {50, "Piruletas", 0.50, 50}
    };

    totalProductos = 50;
    for(int i = 0; i < totalProductos; i++) {
        productos[i] = inventarioBase[i];
    }
}

/* ================= MENÚ PRINCIPAL ================= */

void menuPrincipal() {
    int op;
    do {
        printf("\n====== SISTEMA PANADERIA: LA ESPIGA DE ORO ======\n");
        printf("1. Productos\n2. Inventario\n3. Ventas\n4. Caja\n5. Reportes\n0. Salir\nOpcion: ");
        if (scanf("%d", &op) != 1) { while(getchar() != '\n'); continue; }

        switch(op) {
            case 1: menuProductos(); break;
            case 2: menuInventario(); break;
            case 3: menuVentas(); break;
            case 4: menuCaja(); break;
            case 5: menuReportes(); break;
        }
    } while(op != 0);
}

/* ================= PRODUCTOS ================= */

void menuProductos() {
    int op;
    do {
        printf("\n--- PRODUCTOS ---\n");
        printf("1. Listar\n2. Agregar nuevo\n3. Eliminar\n4. Modificar precio\n5. Ordenar Alfabeticamente\n0. Volver\n");
        scanf("%d",&op);

        switch(op) {
            case 1: listarProductos(); break;
            case 2: registrarProducto(); break;
            case 3: eliminarProducto(); break;
            case 4: modificarPrecio(); break;
            case 5: ordenarProductos(); break;
        }
    } while(op != 0);
}

void listarProductos() {
    printf("\nID\t%-25s\tPrecio\tStock\n", "Producto");
    printf("------------------------------------------------------------\n");
    for(int i=0; i<totalProductos; i++)
        printf("%d\t%-25s\t$%.2f\t%d\n",
               productos[i].id, productos[i].nombre,
               productos[i].precio, productos[i].stock);
}

void registrarProducto() {
    if(totalProductos >= MAX_PRODUCTOS) {
        printf("Error: Capacidad maxima alcanzada.\n");
        return;
    }
    Producto p;
    printf("Nuevo ID: "); scanf("%d",&p.id);
    printf("Nombre: "); getchar(); fgets(p.nombre, 40, stdin);
    p.nombre[strcspn(p.nombre, "\n")] = 0;
    printf("Precio: "); scanf("%f",&p.precio);
    printf("Stock Inicial: "); scanf("%d",&p.stock);
    productos[totalProductos++] = p;
    printf("Producto agregado con exito.\n");
}

void eliminarProducto() {
    int id;
    printf("ID a eliminar: "); scanf("%d",&id);
    int pos = buscarProductoID(id);
    if(pos == -1) { printf("No encontrado.\n"); return; }
    for(int i=pos; i<totalProductos-1; i++) productos[i] = productos[i+1];
    totalProductos--;
    printf("Producto eliminado.\n");
}

void modificarPrecio() {
    int id;
    printf("ID producto: "); scanf("%d",&id);
    int pos = buscarProductoID(id);
    if(pos == -1) { printf("No encontrado.\n"); return; }
    printf("Precio actual: %.2f. Nuevo precio: ", productos[pos].precio);
    scanf("%f",&productos[pos].precio);
}

void ordenarProductos() {
    Producto aux;
    for(int i=0; i<totalProductos-1; i++)
        for(int j=0; j<totalProductos-1-i; j++)
            if(strcmp(productos[j].nombre, productos[j+1].nombre) > 0) {
                aux = productos[j];
                productos[j] = productos[j+1];
                productos[j+1] = aux;
            }
    printf("Productos ordenados por nombre.\n");
}

/* ================= INVENTARIO ================= */

void menuInventario() {
    int op;
    do {
        printf("\n--- INVENTARIO ---\n1. Ver Stock\n2. Ajustar stock (+/-)\n0. Volver\n");
        scanf("%d",&op);
        if(op==1) listarProductos();
        if(op==2) ajustarStock();
    } while(op!=0);
}

void ajustarStock() {
    int id, cant;
    printf("ID producto: "); scanf("%d",&id);
    int pos = buscarProductoID(id);
    if(pos == -1) { printf("No encontrado.\n"); return; }
    printf("Cantidad a sumar (positivo) o restar (negativo): ");
    scanf("%d",&cant);
    productos[pos].stock += cant;
    printf("Stock actualizado: %d\n", productos[pos].stock);
}

int buscarProductoID(int id) {
    for(int i=0; i<totalProductos; i++)
        if(productos[i].id == id) return i;
    return -1;
}

/* ================= CAJA ================= */

void menuCaja() {
    int op;
    do {
        printf("\n--- GESTION DE CAJA ---\n1. Abrir caja\n2. Cerrar caja / Ver Total\n0. Volver\n");
        scanf("%d",&op);
        if(op==1) abrirCaja();
        if(op==2) cerrarCaja();
    } while(op!=0);
}

void abrirCaja() {
    cajaAbierta = 1;
    totalCaja = 0;
    totalVentas = 0;
    printf("Caja abierta. Lista para vender.\n");
}

void cerrarCaja() {
    printf("\n====== CIERRE DE CAJA ======\n");
    printf("Ventas realizadas: %d\n", totalVentas);
    printf("Monto acumulado: $%.2f\n", totalCaja);
    cajaAbierta = 0;
    printf("Caja cerrada.\n");
}

/* ================= VENTAS ================= */

void menuVentas() {
    if(!cajaAbierta){
        printf("\n[!] ERROR: Debe abrir caja antes de vender.\n");
        return;
    }
    realizarVenta();
}

float seleccionarIVA() {
    int op;
    printf("Tipo IVA (1=0%%  2=12%%  3=15%%): ");
    scanf("%d",&op);
    if(op==1) return 0.0;
    if(op==3) return 0.15;
    return 0.12;
}

void realizarVenta() {
    ItemTicket ticket[MAX_ITEMS];
    int totalItems = 0;
    float subtotalGeneral = 0, ivaGeneral = 0;

    printf("\n--- NUEVA VENTA ---\n");
    while(totalItems < MAX_ITEMS) {
        int id, cant;
        printf("ID producto (0 para cobrar): ");
        scanf("%d",&id);
        if(id == 0) break;

        int pos = buscarProductoID(id);
        if(pos == -1) { printf("ID no existe.\n"); continue; }

        printf("Cantidad: ");
        scanf("%d",&cant);
        if(productos[pos].stock < cant) {
            printf("Solo hay %d en stock.\n", productos[pos].stock);
            continue;
        }

        float ivaP = seleccionarIVA();
        float sub = cant * productos[pos].precio;
        float iva = sub * ivaP;

        productos[pos].stock -= cant;

        ticket[totalItems] = (ItemTicket){productos[pos].id, "", productos[pos].precio, cant, ivaP, sub, iva, sub+iva};
        strcpy(ticket[totalItems].nombre, productos[pos].nombre);

        subtotalGeneral += sub;
        ivaGeneral += iva;
        totalItems++;
    }

    if(totalItems == 0) return;

    float total = subtotalGeneral + ivaGeneral;
    totalCaja += total;
    totalVentas++;

    mostrarTicket(ticket, totalItems, subtotalGeneral, ivaGeneral, total);
    advertenciaStock();
}

void mostrarTicket(ItemTicket t[], int n, float sub, float iva, float total) {
    printf("\n============================\n");
    printf("       TICKET DE VENTA      \n");
    printf("============================\n");
    for(int i=0; i<n; i++) {
        printf("%-20s x%-2d  $%.2f\n", t[i].nombre, t[i].cantidad, t[i].total);
    }
    printf("----------------------------\n");
    printf("Subtotal:       $%.2f\n", sub);
    printf("IVA:            $%.2f\n", iva);
    printf("TOTAL A PAGAR:  $%.2f\n", total);
    printf("============================\n");
}

void advertenciaStock() {
    for(int i=0; i<totalProductos; i++)
        if(productos[i].stock <= STOCK_BAJO)
            printf("\n[!] ALERTA: Stock critico de %s (%d unidades)\n", productos[i].nombre, productos[i].stock);
}

/* ================= REPORTES ================= */

void menuReportes() {
    int op;
    do {
        printf("\n--- REPORTES ---\n1. Resumen General\n2. Ver Stock Bajo\n0. Volver\n");
        scanf("%d",&op);
        if(op==1) reporteGeneral();
        if(op==2) reporteStockBajo();
    } while(op!=0);
}

void reporteGeneral() {
    printf("\n--- ESTADO DEL NEGOCIO ---\n");
    printf("Productos en catálogo: %d\n", totalProductos);
    printf("Ventas en este turno: %d\n", totalVentas);
    printf("Dinero en caja:       $%.2f\n", totalCaja);
}

void reporteStockBajo() {
    printf("\n--- PRODUCTOS POR AGOTARSE ---\n");
    int cont = 0;
    for(int i=0; i<totalProductos; i++) {
        if(productos[i].stock <= STOCK_BAJO) {
            printf("- %s: %d unidades\n", productos[i].nombre, productos[i].stock);
            cont++;
        }
    }
    if(cont == 0) printf("Todo el stock esta en niveles normales.\n");
}

/* ================= MAIN ================= */

int main() {
    // Configura la consola para mostrar tildes y caracteres especiales correctamente
    SetConsoleOutputCP(65001);
    
    cargarProductos();
    menuPrincipal();
    
    return 0;
} 