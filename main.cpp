#include "editorial.h"

int main() {
    srand(time(0));
    Cola colaPedidos;
    Pila cajas[LIBRERIAS];
    int opcion, n;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Generar N pedidos aleatorios\n";
        cout << "2. Ejecutar un paso de simulacion\n";
        cout << "3. Mostrar estado del sistema\n";
        cout << "4. Ver contenido de una caja de libreria\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Cuantos pedidos generar? ";
                cin >> n;
                for (int i=0; i<n; i++) {
                    Pedido p = generarPedidoAleatorio();
                    colaPedidos.encolar(p);
                }
                break;
            case 2:
                cout << "Simulando paso (ejemplo simplificado)...\n";
                if (!colaPedidos.vacia()) {
                    Pedido p = colaPedidos.desencolar();
                    p.estado = CAJA;
                    cajas[p.id_editorial].apilar(p);
                }
                break;
            case 3:
                cout << "\nPedidos en cola:\n";
                colaPedidos.mostrar();
                break;
            case 4:
                cout << "Introduce id de libreria (0-" << LIBRERIAS-1 << "): ";
                cin >> n;
                if (n>=0 && n<LIBRERIAS) cajas[n].mostrar();
                else cout << "ID invalido\n";
                break;
        }
    } while(opcion != 0);

    return 0;
}
