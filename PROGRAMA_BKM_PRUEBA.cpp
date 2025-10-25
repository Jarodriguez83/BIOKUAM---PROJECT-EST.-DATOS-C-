#include <iostream>
#include <cstdlib>  // Para rand()
#include <ctime>    // Para srand()
using namespace std;

// Definición de la estructura para cada nodo
struct Nodo {
    int idLugar;
    float pH;
    float temperatura;
    Nodo* siguiente; // Puntero al siguiente nodo (lista circular)
};

// Función para crear un nuevo nodo
Nodo* crearNodo(int id) {
    Nodo* nuevo = new Nodo;
    nuevo->idLugar = id;
    // Se generan valores iniciales aleatorios
    nuevo->pH = 6 + rand() % 3;          // valores entre 6 y 8
    nuevo->temperatura = 15 + rand() % 11; // valores entre 15 y 25
    nuevo->siguiente = nullptr;
    return nuevo;
}

// Función para mostrar la lista actual
void mostrarLista(Nodo* inicio) {
    if (inicio == nullptr) return;

    Nodo* temp = inicio;
    cout << "\nLista de lugares y sus valores actuales:\n";
    do {
        cout << "Lugar " << temp->idLugar 
             << " | pH: " << temp->pH 
             << " | Temp: " << temp->temperatura << "°C\n";
        temp = temp->siguiente;
    } while (temp != inicio);
    cout << endl;
}

// Función que simula el recorrido del barco
void recorrerBarco(Nodo* inicio) {
    if (inicio == nullptr) return;

    Nodo* temp = inicio;
    do {
        cout << "\n--- Lugar " << temp->idLugar << " ---\n";
        cout << "Valores anteriores -> pH: " << temp->pH 
             << ", Temp: " << temp->temperatura << "°C\n";

        // Pedir nuevos valores al usuario
        float nuevoPH, nuevaTemp;
        cout << "Ingrese nuevo valor de pH: ";
        cin >> nuevoPH;
        cout << "Ingrese nueva temperatura: ";
        cin >> nuevaTemp;

        // Comparar y mostrar mensaje si hay cambios
        if (nuevoPH != temp->pH) {
            cout << "⚠ Variacion en el pH detectada (antes: " 
                 << temp->pH << ", ahora: " << nuevoPH << ")\n";
        }
        if (nuevaTemp != temp->temperatura) {
            cout << "⚠ Variacion en la temperatura detectada (antes: " 
                 << temp->temperatura << "°C, ahora: " << nuevaTemp << "°C)\n";
        }

        // Sobreescribir con los nuevos valores
        temp->pH = nuevoPH;
        temp->temperatura = nuevaTemp;

        // Pasar al siguiente nodo
        temp = temp->siguiente;

    } while (temp != inicio);

    cout << "\n--- Recorrido finalizado ---\n";
    mostrarLista(inicio);
}

int main() {
    srand(time(0)); // Inicializar generador de números aleatorios

    int n;
    cout << "Ingrese el numero de lugares donde se toman muestras: ";
    cin >> n;

    // Crear lista circular
    Nodo* inicio = nullptr;
    Nodo* ultimo = nullptr;

    for (int i = 1; i <= n; i++) {
        Nodo* nuevo = crearNodo(i);

        if (inicio == nullptr) {
            inicio = nuevo;
            inicio->siguiente = inicio; // Apunta a sí mismo
            ultimo = inicio;
        } else {
            nuevo->siguiente = inicio;
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
    }

    // Mostrar valores iniciales
    mostrarLista(inicio);

    char opcion;
    do {
        recorrerBarco(inicio);
        cout << "\n¿Desea repetir el recorrido? (s/n): ";
        cin >> opcion;
    } while (opcion == 's' || opcion == 'S');

    cout << "\nPrograma finalizado.\n";
    return 0;
}
