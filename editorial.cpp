#include "editorial.h"

// =================== COLA ===================
Cola::Cola() { frente = fin = nullptr; }
Cola::~Cola() { while (!vacia()) desencolar(); }
bool Cola::vacia() { return frente == nullptr; }

void Cola::encolar(Pedido p) {
    NodoCola* nuevo = new NodoCola{p, nullptr};
    if (fin == nullptr) frente = fin = nuevo;
    else { fin->sig = nuevo; fin = nuevo; }
}

Pedido Cola::desencolar() {
    if (vacia()) { cout << "Cola vacia\n"; exit(1); }
    NodoCola* aux = frente;
    Pedido p = aux->pedido;
    frente = frente->sig;
    if (frente == nullptr) fin = nullptr;
    delete aux;
    return p;
}

void Cola::mostrar() {
    NodoCola* aux = frente;
    while (aux != nullptr) {
        mostrarPedido(aux->pedido);
        aux = aux->sig;
    }
}

// =================== PILA ===================
Pila::Pila() { tope = nullptr; }
Pila::~Pila() { while (!vacia()) desapilar(); }
bool Pila::vacia() { return tope == nullptr; }

void Pila::apilar(Pedido p) {
    NodoPila* nuevo = new NodoPila{p, tope};
    tope = nuevo;
}

Pedido Pila::desapilar() {
    if (vacia()) { cout << "Pila vacia\n"; exit(1); }
    NodoPila* aux = tope;
    Pedido p = aux->pedido;
    tope = tope->sig;
    delete aux;
    return p;
}

void Pila::mostrar() {
    if (vacia()) {
        cout << "(Caja vacía)\n";
        return;
    }
    NodoPila* aux = tope;
    while (aux != nullptr) {
        mostrarPedido(aux->pedido);
        aux = aux->sig;
    }
}

// =================== FUNCIONES AUXILIARES ===================
string generarIdPedido() {
    string id = "P";
    for (int i = 0; i < 5; i++) id += to_string(rand() % 10);
    return id;
}

string generarCodLibro() {
    string cod = "";
    cod += to_string(rand() % 900 + 100); // 3 cifras
    cod += char('A' + rand() % 26);       // una letra
    cod += to_string(rand() % 90 + 10);   // 2 cifras
    return cod;
}

string generarMateria() {
    string materias[] = {"Matematicas","Fisica","Tecnologia","Musica","Historia","Lengua"};
    return materias[rand() % 6];
}

Pedido generarPedidoAleatorio() {
    Pedido p;
    p.id_editorial = rand() % LIBRERIAS;
    p.id_pedido = generarIdPedido();
    p.cod_libro = generarCodLibro();
    p.materia = generarMateria();
    p.unidades = rand() % 5 + 1; // entre 1 y 5 ejemplares
    p.estado = INICIADO;
    return p;
}

void mostrarPedido(Pedido p) {
    cout << "[Pedido " << p.id_pedido << "] Libreria " << p.id_editorial
         << " | Libro: " << p.cod_libro << " (" << p.materia << ")"
         << " | Unidades: " << p.unidades
         << " | Estado: ";
    switch (p.estado) {
        case INICIADO: cout << "Iniciado"; break;
        case ALMACEN:  cout << "Almacen"; break;
        case IMPRENTA: cout << "Imprenta"; break;
        case LISTO:    cout << "Listo"; break;
        case CAJA:     cout << "Caja"; break;
    }
    cout << endl;
}

// =================== SIMULACIÓN ===================
void ejecutarPaso(Cola &iniciado, Cola &almacen, Cola &imprenta, Cola &listo,
                  Pila cajasLibrerias[], int stock[], int &fase) {
    Pedido p;
    int procesados = 0;

    switch(fase) {
        case 0: // INICIADO → ALMACEN
            while (!iniciado.vacia() && procesados < N_PEDIDOS_PASO) {
                p = iniciado.desencolar();
                p.estado = ALMACEN;
                almacen.encolar(p);
                procesados++;
            }
            break;

        case 1: // ALMACEN → IMPRENTA o LISTO
            while (!almacen.vacia() && procesados < N_PEDIDOS_PASO) {
                p = almacen.desencolar();
                int idLibro = rand() % MAX_TITULOS;
                if (stock[idLibro] >= p.unidades) {
                    stock[idLibro] -= p.unidades;
                    p.estado = LISTO;
                    listo.encolar(p);
                } else {
                    stock[idLibro] += TAM_LOTE;
                    p.estado = IMPRENTA;
                    imprenta.encolar(p);
                }
                procesados++;
            }
            break;

        case 2: // IMPRENTA → LISTO
            while (!imprenta.vacia() && procesados < N_PEDIDOS_PASO) {
                p = imprenta.desencolar();
                p.estado = LISTO;
                listo.encolar(p);
                procesados++;
            }
            break;

        case 3: // LISTO → CAJA (y colocamos el pedido en la pila de su librería)
            while (!listo.vacia() && procesados < N_PEDIDOS_PASO) {
                p = listo.desencolar();
                p.estado = CAJA;
                cajasLibrerias[p.id_editorial].apilar(p);
                procesados++;
            }
            break;
    }

    // Avanzamos la fase de forma cíclica (0→1→2→3→0)
    fase = (fase + 1) % 4;
}




