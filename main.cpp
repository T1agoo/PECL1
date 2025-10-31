#include "editorial.h"

int main() {
    srand(time(0));

    Cola iniciado, almacen, imprenta, listo;
    Pila cajasLibrerias[LIBRERIAS];
    Libro catalogo[MAX_TITULOS];
    int fase = 0;

    inicializarCatalogo(catalogo);

    int opcion, N;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Generar N pedidos aleatorios\n";
        cout << "2. Ejecutar un paso de simulacion\n";
        cout << "3. Mostrar estado general del sistema\n";
        cout << "4. Ver contenido de una caja de una libreria\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                cout << "Cuantos pedidos generar?: ";
                cin >> N;
                for (int i = 0; i < N; i++) {
                    Pedido p = generarPedidoAleatorio(catalogo);
                    iniciado.encolar(p);
                }
                cout << N << " pedidos generados.\n";
                break;
            }

            case 2: {
                ejecutarPaso(iniciado, almacen, imprenta, listo, cajasLibrerias, catalogo, fase);
                break;
            }

            case 3: {
                cout << "\n--- INICIADO ---\n"; iniciado.mostrar();
                cout << "\n--- ALMACEN ---\n"; almacen.mostrar();
                cout << "\n--- IMPRENTA ---\n"; imprenta.mostrar();
                cout << "\n--- LISTO ---\n"; listo.mostrar();

                cout << "\n--- CAJAS (solo librerías con pedidos) ---\n";
                bool hayPedidos = false;
                for (int i = 0; i < LIBRERIAS; i++) {
                    if (!cajasLibrerias[i].vacia()) {
                        cout << "Libreria " << i << ":\n";
                        cajasLibrerias[i].mostrar();
                        hayPedidos = true;
                    }
                }
                if (!hayPedidos)
                    cout << "(No hay cajas con pedidos por ahora)\n";

                mostrarStock(catalogo);
                break;
            }

            case 4: {
                int id;
                cout << "Introduce el ID de la libreria (0-" << LIBRERIAS-1 << "): ";
                cin >> id;
                if (id < 0 || id >= LIBRERIAS) {
                    cout << "ID de libreria invalido.\n";
                    break;
                }
                cout << "\nContenido de la caja de la libreria " << id << ":\n";
                cajasLibrerias[id].mostrar();
                break;
            }

            case 0:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 0);

    return 0;
}


