#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// =================== CONFIGURACIÓN ===================
#define MAX_TITULOS 10      // nº de títulos en catálogo
#define N_PEDIDOS_PASO 12   // nº de pedidos procesados por fase
#define TAM_LOTE 10         // incremento de stock desde imprenta
#define LIBRERIAS 6         // ids 0..LIBRERIAS-1
#define CAP_CAJA 5          // nº de pedidos por caja antes de enviar

// =================== ENUMS Y STRUCTS ===================
enum Estado { INICIADO, ALMACEN, IMPRENTA, LISTO, CAJA };

struct Pedido {
    int id_editorial;
    string id_pedido;
    string cod_libro;
    string materia;
    int unidades;
    Estado estado;
};

// Nodos dinámicos
struct NodoCola { Pedido pedido; NodoCola* sig; };
struct NodoPila { Pedido pedido; NodoPila* sig; };

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

// =================== FUNCIONES AUXILIARES ===================
Pedido generarPedidoAleatorio();
string generarIdPedido();
string generarCodLibro();
string generarMateria();
void mostrarPedido(Pedido p);

// =================== SIMULACIÓN ===================
// Avanza una fase por llamada, y añade pedidos a la pila de su librería
void ejecutarPaso(Cola &iniciado, Cola &almacen, Cola &imprenta, Cola &listo,
                  Pila cajasLibrerias[], int stock[], int &fase);

#endif


