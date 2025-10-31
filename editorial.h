#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// =================== CONFIGURACI�N ===================
#define MAX_TITULOS 10
#define N_PEDIDOS_PASO 12
#define TAM_LOTE 10
#define LIBRERIAS 6
#define CAP_CAJA 5

// =================== ENUMERADOS ===================
enum Estado { INICIADO, ALMACEN, IMPRENTA, LISTO, CAJA };

// =================== STRUCTS ===================
struct Pedido {
    int id_editorial;      // ID de la librer�a que realiza el pedido
    string id_pedido;      // C�digo identificador del pedido (Pxxxxx)
    string cod_libro;      // C�digo del libro solicitado (formato 963K76)
    string materia;        // Materia del libro solicitado
    int unidades;          // N�mero de ejemplares solicitados
    Estado estado;         // Estado actual del pedido
};

struct Libro {
    string cod_libro;      // C�digo identificador del libro
    int stock;             // Unidades disponibles en almac�n
};

// =================== NODOS ===================
struct NodoCola {
    Pedido pedido;         // Pedido almacenado
    NodoCola* sig;         // Puntero al siguiente nodo
};

struct NodoPila {
    Pedido pedido;         // Pedido almacenado
    NodoPila* sig;         // Puntero al siguiente nodo
};

// =================== CLASE COLA ===================

// Se usa para modelar las distintas fases del flujo editorial:
// INICIADO, ALMACEN, IMPRENTA y LISTO.
// Los pedidos entran por el final (encolar) y salen por el frente (desencolar).

class Cola {
private:
    NodoCola* frente;   //Puntero al primer nodo de la cola
    NodoCola* fin;      //Puntero al �ltimo nodo de la cola
public:
    Cola();                // Constructor: inicializa punteros a NULL
    ~Cola();               // Destructor: libera la memoria din�mica usada
    bool vacia();          // Devuelve true si la cola est� vac�a
    void encolar(Pedido p);// Inserta un pedido al final de la cola
    Pedido desencolar();   // Extrae un pedido del inicio de la cola
    void mostrar();        // Muestra por pantalla los pedidos de la cola
};

// =================== CLASE PILA ===================

// Se usa para representar las cajas de las librer�as.
// Cada caja es una pila donde los pedidos se apilan uno sobre otro.

class Pila {
private:
    NodoPila* tope;        // Puntero al �ltimo pedido insertado (parte superior)

public:
    Pila();                // Constructor
    ~Pila();               // Destructor
    bool vacia();          // Devuelve true si la pila est� vac�a
    void apilar(Pedido p); // A�ade un pedido al tope de la pila
    Pedido desapilar();    // Extrae el pedido del tope de la pila
    void mostrar();        // Muestra por pantalla los pedidos de la pila
};

// =================== FUNCIONES ===================
// Estas funciones gestionan el flujo general del programa.
// Incluyen generaci�n de datos, inicializaci�n y simulaci�n.
// ------------------------------------------------------

// Genera un identificador aleatorio para el pedido (ej: "P12345")
string generarIdPedido();

// Genera un c�digo de libro aleatorio (ej: "963K76")
string generarCodLibro();

// Devuelve una materia aleatoria (ej: "Historia", "Lengua", etc.)
string generarMateria();

// Crea un pedido aleatorio usando los datos del cat�logo
Pedido generarPedidoAleatorio(Libro catalogo[]);

// Muestra por pantalla los datos de un pedido concreto
void mostrarPedido(Pedido p);

// Inicializa el cat�logo de libros con c�digos y stock aleatorios
void inicializarCatalogo(Libro catalogo[]);

// Muestra el stock actual de todos los libros del cat�logo
void mostrarStock(Libro catalogo[]);

// Ejecuta un paso de la simulaci�n, moviendo pedidos entre fases
void ejecutarPaso(Cola &iniciado, Cola &almacen, Cola &imprenta, Cola &listo,
                  Pila cajasLibrerias[], Libro catalogo[], int &fase);

#endif

