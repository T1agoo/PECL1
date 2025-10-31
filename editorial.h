#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// =================== CONFIGURACIÓN ===================
#define MAX_TITULOS 10
#define N_PEDIDOS_PASO 12
#define TAM_LOTE 10
#define LIBRERIAS 6
#define CAP_CAJA 5

// =================== ENUMERADOS ===================
enum Estado { INICIADO, ALMACEN, IMPRENTA, LISTO, CAJA };

// =================== STRUCTS ===================
struct Pedido {
    int id_editorial;
    string id_pedido;
    string cod_libro;
    string materia;
    int unidades;
    Estado estado;
};

struct Libro {
    string cod_libro;
    int stock;
};

// =================== NODOS ===================
struct NodoCola {
    Pedido pedido;
    NodoCola* sig;
};

struct NodoPila {
    Pedido pedido;
    NodoPila* sig;
};

// =================== CLASE COLA ===================
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

// =================== CLASE PILA ===================
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

// =================== FUNCIONES ===================
string generarIdPedido();
string generarCodLibro();
string generarMateria();
Pedido generarPedidoAleatorio(Libro catalogo[]);
void mostrarPedido(Pedido p);
void inicializarCatalogo(Libro catalogo[]);
void mostrarStock(Libro catalogo[]);
void ejecutarPaso(Cola &iniciado, Cola &almacen, Cola &imprenta, Cola &listo,
                  Pila cajasLibrerias[], Libro catalogo[], int &fase);

#endif

