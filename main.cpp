#include "editorial.h"   // Incluye las definiciones de estructuras, clases y funciones del sistema

int main() {
    srand(time(0));  // Inicializa la semilla aleatoria para generar datos aleatorios diferentes cada ejecución


    // DECLARACIÓN DE ESTRUCTURAS PRINCIPALES DEL SISTEMA

    Cola iniciado, almacen, imprenta, listo;     // Colas que representan las fases del flujo de pedidos
    Pila cajasLibrerias[LIBRERIAS];              // Arreglo de pilas: una por cada librería
    Libro catalogo[MAX_TITULOS];                 // Catálogo de libros con su stock
    int fase = 0;                                // Indica la fase actual de la simulación (0→1→2→3→0)

    // Inicializa el catálogo de libros con códigos y stock aleatorios
    inicializarCatalogo(catalogo);

    int opcion, N;   // Variables para el menú y número de pedidos a generar


    // MENÚ PRINCIPAL DE INTERACCIÓN CON EL USUARIO

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Generar N pedidos aleatorios\n";
        cout << "2. Ejecutar un paso de simulacion\n";
        cout << "3. Mostrar estado general del sistema\n";
        cout << "4. Ver contenido de una caja de una libreria\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;


        // SELECCIÓN DE OPCIÓN DEL MENÚ

        switch(opcion) {

            // --------------------------------------------------
            // OPCIÓN 1: Generar N pedidos aleatorios
            // --------------------------------------------------
            // Crea N pedidos aleatorios y los encola en la cola "iniciado"
            case 1: {
                cout << "Cuantos pedidos generar?: ";
                cin >> N;
                for (int i = 0; i < N; i++) {
                    Pedido p = generarPedidoAleatorio(catalogo); // Pedido aleatorio válido
                    iniciado.encolar(p);                          // Se añade a la cola inicial
                }
                cout << N << " pedidos generados.\n";
                break;
            }


            // OPCIÓN 2: Ejecutar un paso de simulación

            // Llama a la función ejecutarPaso(), que mueve los pedidos
            // entre colas según su estado (INICIADO→ALMACEN→IMPRENTA→LISTO→CAJA)
            case 2: {
                ejecutarPaso(iniciado, almacen, imprenta, listo, cajasLibrerias, catalogo, fase);
                break;
            }


            // OPCIÓN 3: Mostrar estado general del sistema

            // Muestra todas las colas (iniciado, almacen, imprenta, listo)
            // y también las cajas (pilas) que contienen pedidos
            case 3: {
                cout << "\n--- INICIADO ---\n"; iniciado.mostrar();
                cout << "\n--- ALMACEN ---\n"; almacen.mostrar();
                cout << "\n--- IMPRENTA ---\n"; imprenta.mostrar();
                cout << "\n--- LISTO ---\n"; listo.mostrar();

                cout << "\n--- CAJAS (solo librerias con pedidos) ---\n";
                bool hayPedidos = false;  // Bandera para comprobar si hay alguna caja con pedidos

                // Recorre todas las librerías
                for (int i = 0; i < LIBRERIAS; i++) {
                    // Solo muestra las cajas que tienen pedidos
                    if (!cajasLibrerias[i].vacia()) {
                        cout << "Libreria " << i << ":\n";
                        cajasLibrerias[i].mostrar();
                        hayPedidos = true;
                    }
                }

                // Si no hay cajas con pedidos, se informa al usuario
                if (!hayPedidos)
                    cout << "(No hay cajas con pedidos por ahora)\n";

                // También se muestra el stock actual de los libros
                mostrarStock(catalogo);
                break;
            }


            // OPCIÓN 4: Ver contenido de una caja de librería específica

            // Permite consultar los pedidos apilados (listos) de una librería concreta
            case 4: {
                int id;
                cout << "Introduce el ID de la libreria (0-" << LIBRERIAS-1 << "): ";
                cin >> id;

                // Comprobación de rango válido
                if (id < 0 || id >= LIBRERIAS) {
                    cout << "ID de libreria invalido.\n";
                    break;
                }

                cout << "\nContenido de la caja de la libreria " << id << ":\n";
                cajasLibrerias[id].mostrar();  // Muestra el contenido de la pila correspondiente
                break;
            }


            // OPCIÓN 0: Salir del programa

            case 0:
                cout << "Saliendo del programa...\n";
                break;


            // OPCIÓN NO VÁLIDA

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 0);  // El programa se repite hasta que el usuario elija salir

    return 0;
}


