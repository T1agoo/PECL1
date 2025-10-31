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
    if (!aux) { cout << "(Vacia)\n"; return; }
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
    cod += to_string(rand() % 900 + 100);
    cod += char('A' + rand() % 26);
    cod += to_string(rand() % 90 + 10);
    return cod;
}

string generarMateria() {
    string materias[] = {"Matematicas","Fisica","Tecnologia","Musica","Historia","Lengua"};
    return materias[rand() % 6];
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

// =================== CATÁLOGO Y STOCK ===================
void inicializarCatalogo(Libro catalogo[]) {
    cout << "\n[INICIANDOSTOCK]\n";
    for (int i = 0; i < MAX_TITULOS; i++) {
        catalogo[i].cod_libro = generarCodLibro();
        catalogo[i].stock = rand() % 11; // 5-20 unidades
        cout << "Libro " << catalogo[i].cod_libro
             << " Stock: " << catalogo[i].stock << " unidades\n";
    }
    cout << endl;
}

void mostrarStock(Libro catalogo[]) {
    cout << "\n[STOCK ACTUAL]\n";
    for (int i = 0; i < MAX_TITULOS; i++) {
        cout << "Libro " << catalogo[i].cod_libro
             << ": " << catalogo[i].stock << " unidades\n";
    }
    cout << endl;
}

// Genera un pedido solo de libros del catálogo
Pedido generarPedidoAleatorio(Libro catalogo[]) {
    Pedido p;
    p.id_editorial = rand() % LIBRERIAS;
    p.id_pedido = generarIdPedido();
    p.cod_libro = catalogo[rand() % MAX_TITULOS].cod_libro;
    p.materia = generarMateria();
    p.unidades = rand() % 5 + 1;
    p.estado = INICIADO;
    return p;
}

// =================== SIMULACIÓN ===================
void ejecutarPaso(Cola &iniciado, Cola &almacen, Cola &imprenta, Cola &listo,
                  Pila cajasLibrerias[], Libro catalogo[], int &fase) {
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
            cout << "\n[FASE 0] " << procesados << " pedidos pasaron a ALMACÉN.\n";
            break;

        case 1: // ALMACEN → IMPRENTA o LISTO
            while (!almacen.vacia() && procesados < N_PEDIDOS_PASO) {
                p = almacen.desencolar();

                // Buscar el libro en el catálogo
                int idLibro = -1;
                for (int i = 0; i < MAX_TITULOS; i++) {
                    if (catalogo[i].cod_libro == p.cod_libro) {
                        idLibro = i;
                        break;
                    }
                }

                if (idLibro != -1) {
                    if (catalogo[idLibro].stock >= p.unidades) {
                        catalogo[idLibro].stock -= p.unidades;
                        p.estado = LISTO;
                        listo.encolar(p);
                        cout << "[ALMACEN] Pedido " << p.id_pedido
                             << " listo (stock suficiente de " << p.cod_libro << ").\n";
                    } else {
                        p.estado = IMPRENTA;
                        imprenta.encolar(p);
                        catalogo[idLibro].stock += TAM_LOTE;
                        cout << "[ALMACEN] Pedido " << p.id_pedido
                             << " enviado a IMPRENTA (+"
                             << TAM_LOTE << " unidades añadidas al stock de "
                             << p.cod_libro << ").\n";
                    }
                }
                procesados++;
            }
            break;

        case 2: // IMPRENTA → LISTO
            while (!imprenta.vacia() && procesados < N_PEDIDOS_PASO) {
                p = imprenta.desencolar();
                p.estado = LISTO;
                listo.encolar(p);
                cout << "[IMPRENTA] Pedido " << p.id_pedido
                     << " impreso, pasa a LISTO.\n";
                procesados++;
            }
            break;

        case 3: // LISTO → CAJA
            while (!listo.vacia() && procesados < N_PEDIDOS_PASO) {
                p = listo.desencolar();
                p.estado = CAJA;
                if (p.id_editorial >= 0 && p.id_editorial < LIBRERIAS)
                    cajasLibrerias[p.id_editorial].apilar(p);
                cout << "[LISTO] Pedido " << p.id_pedido
                     << " enviado a caja de librería "
                     << p.id_editorial << ".\n";
                procesados++;
            }
            break;
    }

    mostrarStock(catalogo);
    fase = (fase + 1) % 4;
}

