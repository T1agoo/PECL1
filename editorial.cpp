#include "editorial.h"

// =================== COLA ===================
// Constructor: inicializa los punteros a null
Cola::Cola() { frente = fin = nullptr; }

// Destructor: elimina todos los elementos de la cola
Cola::~Cola() { while (!vacia()) desencolar(); }

// Comprueba si la cola está vacía
bool Cola::vacia() { return frente == nullptr; }

// Inserta un nuevo pedido al final de la cola
void Cola::encolar(Pedido p) {
    NodoCola* nuevo = new NodoCola{p, nullptr};
    if (fin == nullptr) frente = fin = nuevo; // si la cola estaba vacía
    else { fin->sig = nuevo; fin = nuevo; }   // si ya tiene elementos
}

// Elimina y devuelve el pedido al frente de la cola
Pedido Cola::desencolar() {
    if (vacia()) { cout << "Cola vacia\n"; exit(1); }
    NodoCola* aux = frente;       // nodo temporal al frente
    Pedido p = aux->pedido;       // copia del pedido
    frente = frente->sig;         // avanzar el frente
    if (frente == nullptr) fin = nullptr; // si se vacía la cola
    delete aux;                   // liberar memoria
    return p;                     // devolver el pedido
}

// Muestra todos los pedidos de la cola (del frente al final)
void Cola::mostrar() {
    NodoCola* aux = frente;
    if (!aux) { cout << "(Vacia)\n"; return; }
    while (aux != nullptr) {
        mostrarPedido(aux->pedido);
        aux = aux->sig;
    }
}

// =================== PILA ===================
// Constructor: inicializa el tope a null
Pila::Pila() { tope = nullptr; }

// Destructor: vacía la pila eliminando todos los nodos
Pila::~Pila() { while (!vacia()) desapilar(); }

// Comprueba si la pila está vacía
bool Pila::vacia() { return tope == nullptr; }

// Apila un pedido en la parte superior
void Pila::apilar(Pedido p) {
    NodoPila* nuevo = new NodoPila{p, tope};
    tope = nuevo;
}

// Desapila (extrae) el pedido del tope
Pedido Pila::desapilar() {
    if (vacia()) { cout << "Pila vacia\n"; exit(1); }
    NodoPila* aux = tope;
    Pedido p = aux->pedido;
    tope = tope->sig; // mover el tope
    delete aux;
    return p;
}

// Muestra los pedidos en la pila (de arriba hacia abajo)
void Pila::mostrar() {
    if (vacia()) {
        cout << "Caja vacia, tiene que haber pedidos en Caja\n";
        return;
    }
    NodoPila* aux = tope;
    while (aux != nullptr) {
        mostrarPedido(aux->pedido);
        aux = aux->sig;
    }
}

// =================== FUNCIONES AUXILIARES ===================
// Genera un identificador único de pedido (ej: "P12345")
string generarIdPedido() {
    string id = "P";
    for (int i = 0; i < 5; i++) id += to_string(rand() % 10);
    return id;
}

// Genera un código de libro aleatorio (ej: "963K76")
string generarCodLibro() {
    string cod = "";
    cod += to_string(rand() % 900 + 100);  // tres dígitos
    cod += char('A' + rand() % 26);        // una letra mayúscula
    cod += to_string(rand() % 90 + 10);    // dos dígitos
    return cod;
}

// Devuelve una materia aleatoria de entre las posibles
string generarMateria() {
    string materias[] = {"Matematicas","Fisica","Tecnologia","Musica","Historia","Lengua"};
    return materias[rand() % 6];
}

// Muestra en consola la información completa de un pedido
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

// ======================================================
// CATÁLOGO Y CONTROL DE STOCK
// ======================================================

// Inicializa el catálogo con libros aleatorios y stock entre 0–10 unidades
void inicializarCatalogo(Libro catalogo[]) {
    cout << "\n[INICIANDO STOCK]\n";
    for (int i = 0; i < MAX_TITULOS; i++) {
        catalogo[i].cod_libro = generarCodLibro(); // código único
        catalogo[i].stock = rand() % 11;           // stock aleatorio 0–10
        cout << "Libro " << catalogo[i].cod_libro
             << " Stock: " << catalogo[i].stock << " unidades\n";
    }
    cout << endl;
}

// Muestra el stock actual del catálogo de libros
void mostrarStock(Libro catalogo[]) {
    cout << "\n[STOCK ACTUAL]\n";
    for (int i = 0; i < MAX_TITULOS; i++) {
        cout << "Libro " << catalogo[i].cod_libro
             << ": " << catalogo[i].stock << " unidades\n";
    }
    cout << endl;
}

// Genera un pedido aleatorio que pertenece a un libro existente en el catálogo
Pedido generarPedidoAleatorio(Libro catalogo[]) {
    Pedido p;
    p.id_editorial = rand() % LIBRERIAS;                 // ID de librería 0–5
    p.id_pedido = generarIdPedido();                     // ID del pedido
    p.cod_libro = catalogo[rand() % MAX_TITULOS].cod_libro; // libro existente
    p.materia = generarMateria();                        // materia aleatoria
    p.unidades = rand() % 5 + 1;                         // unidades entre 1–5
    p.estado = INICIADO;                                 // estado inicial
    return p;
}

// ======================================================
// SIMULACIÓN DE FASES DE PROCESAMIENTO
// ======================================================
// Ejecuta un paso de la simulación moviendo pedidos entre
// colas según su estado y el stock disponible.
// El parámetro 'fase' indica qué transición ejecutar.
// ------------------------------------------------------

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
                             << " enviado a IMPRENTA (+" << TAM_LOTE
                             << " unidades nuevas al stock de "
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
                     << " enviado a caja de libreria "
                     << p.id_editorial << ".\n";
                procesados++;
            }
            break;

        case 4: // CAJA → ENTREGA FINAL
            cout << "\n[FASE 4] Entregando pedidos y actualizando stock...\n";

            // Vaciar las cajas de librerías y restar del stock
            for (int i = 0; i < LIBRERIAS; i++) {
                while (!cajasLibrerias[i].vacia()) {
                    p = cajasLibrerias[i].desapilar();

                    // Buscar libro y restar unidades
                    for (int j = 0; j < MAX_TITULOS; j++) {
                        if (catalogo[j].cod_libro == p.cod_libro) {
                            catalogo[j].stock = max(0, catalogo[j].stock - p.unidades);
                            break;
                        }
                    }

                    cout << "[CAJA] Pedido " << p.id_pedido
                         << " entregado a libreria " << p.id_editorial
                         << " (libro " << p.cod_libro << ", "
                         << p.unidades << " unidades).\n";
                }
            }

            // 2️⃣ Vaciar todas las colas del sistema para reiniciar
            while (!iniciado.vacia()) iniciado.desencolar();
            while (!almacen.vacia()) almacen.desencolar();
            while (!imprenta.vacia()) imprenta.desencolar();
            while (!listo.vacia()) listo.desencolar();

            cout << "\nTodos los pedidos han sido entregados.\n";
            cout << "Cajas vaciadas.\n";
            cout << "Stock actualizado. Listo para nuevos pedidos.\n";

            break;
    }

    mostrarStock(catalogo);

    // Incrementar fase: ahora hay 5 fases (0→1→2→3→4→0)
    fase = (fase + 1) % 5;
}
