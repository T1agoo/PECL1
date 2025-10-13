#include "editorial.h"

// --- COLA ---
Cola::Cola() { frente = fin = nullptr; }
Cola::~Cola() { while (!vacia()) desencolar(); }
bool Cola::vacia() { return frente == nullptr; }

void Cola::encolar(Pedido p) {
    NodoCola* nuevo = new NodoCola{p, nullptr};
    if (vacia()) frente = fin = nuevo;
    else { fin->sig = nuevo; fin = nuevo; }
}

Pedido Cola::desencolar() {
    if (vacia()) { cout << "Cola vacía\n"; exit(1); }
    NodoCola* aux = frente;
    Pedido p = aux->pedido;
    frente = frente->sig;
    if (!frente) fin = nullptr;
    delete aux;
    return p;
}

void Cola::mostrar() {
    NodoCola* aux = frente;
    while (aux) {
        mostrarPedido(aux->pedido);
        aux = aux->sig;
    }
}

// --- PILA ---
Pila::Pila() { tope = nullptr; }
Pila::~Pila() { while (!vacia()) desapilar(); }
bool Pila::vacia() { return tope == nullptr; }

void Pila::apilar(Pedido p) {
    NodoPila* nuevo = new NodoPila{p, tope};
    tope = nuevo;
}

Pedido Pila::desapilar() {
    if (vacia()) { cout << "Pila vacía\n"; exit(1); }
    NodoPila* aux = tope;
    Pedido p = aux->pedido;
    tope = tope->sig;
    delete aux;
    return p;
}

void Pila::mostrar() {
    NodoPila* aux = tope;
    while (aux) {
        mostrarPedido(aux->pedido);
        aux = aux->sig;
    }
}

// --- Generación de pedidos aleatorios ---
string generarIdPedido() {
    string id = "P";
    for (int i=0; i<5; i++) id += to_string(rand()%10);
    return id;
}

string generarCodLibro() {
    string cod = "";
    cod += to_string(rand()%900+100);     // 3 dígitos
    cod += char('A' + rand()%26);         // letra
    cod += to_string(rand()%90+10);       // 2 dígitos
    return cod;
}

string generarMateria() {
    string materias[] = {"Matematicas","Fisica","Tecnologia","Musica","Historia","Lengua"};
    return materias[rand()%6];
}

Pedido generarPedidoAleatorio() {
    Pedido p;
    p.id_editorial = rand() % LIBRERIAS;
    p.id_pedido = generarIdPedido();
    p.cod_libro = generarCodLibro();
    p.materia = generarMateria();
    p.unidades = rand()%5 + 1;
    p.estado = INICIADO;
    return p;
}

void mostrarPedido(Pedido p) {
    cout << "Pedido " << p.id_pedido
         << " | Libreria: " << p.id_editorial
         << " | Libro: " << p.cod_libro
         << " | Materia: " << p.materia
         << " | Unidades: " << p.unidades
         << " | Estado: " << p.estado
         << endl;
}
