#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// --- Configuraci�n de la simulaci�n ---
#define MAX_TITULOS 10
#define N_PEDIDOS_PASO 12
#define TAM_LOTE 10
#define LIBRERIAS 6
#define CAP_CAJA 5

// --- Estados posibles de los pedidos ---
enum Estado { INICIADO, ALMACEN, IMPRENTA, LISTO, CAJA };

// --- Estructura de pedido ---
struct Pedido {
    int id_editorial;     // librer�a (0..LIBRERIAS-1)
    string id_pedido;     // ej: P21508
    string cod_libro;     // ej: 963K76
    string materia;       // Matem�ticas, F�sica, etc.
    int unidades;         // n� ejemplares
    Estado estado;        // estado actual
};

// --- Nodo para colas ---
struct NodoCola {
    Pedido pedido;
    NodoCola* sig;
};

// --- Nodo para pilas ---
struct NodoPila {
    Pedido pedido;
    NodoPila* sig;
};

// --- Clase Cola din�mica ---
class Cola {
private:
    NodoCola* frente;
    NodoCola* fin;
public:
    Cola();
    ~Cola();
    bool vacia();
    void encolar(Pedido p);
    Pedido desencolar();
    void mostrar();
};

// --- Clase Pila din�mica ---
class Pila {
private:
    NodoPila* tope;
public:
    Pila();
    ~Pila();
    bool vacia();
    void apilar(Pedido p);
    Pedido desapilar();
    void mostrar();
};

// --- Funciones auxiliares ---
Pedido generarPedidoAleatorio();
string generarIdPedido();
string generarCodLibro();
string generarMateria();
void mostrarPedido(Pedido p);

#endif
