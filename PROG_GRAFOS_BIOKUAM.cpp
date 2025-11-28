/*
	PROGRAMA BIOKUAM - INTEGRACIÓN DE GRAFOS 
	DOCUMENTACIÓN POR: JSNT - JARR
	DESCRIPCIÓN Y REQUISITOS DEL PROGRAMA: 
		I) Grafo ponderado, NO dirigido (El peso es la distancia en CM)
		II) Contiene la lista de adyacencia
		III) Cada nodo (Vértice) almacena la medición del prototipo que contiene: pH, Temperatura, Fecha y Hora. 
		IV) Cada nodo (Vértice) almacena su ID automáticamente (Ej: Nodo 1, Nodo 2, Nodo 3, ...)
		V) Se agregan las aristas (Arcos) NO dirigidas con la distancia entre el NODO en CM.  
		VI) El grafo se imprime y muestra todos los nodos contenidos 
		VII) Se puede registrar o actualizar la medición de un nodo  
		VIII) Función DIJKSTRA 1: Distancia mínima desde un punto A a todos los demás  
		IX) Función DIJKSTRA 2: Distancia desde un punto A hasta un punto B (Muestra la distancia y el camino paso a paso)
	REALIZADO POR: Jhon Alexander Rodriguez Redondo (67001483) y Jader Santiago Nieves Tami (67001539)
	INSTITUCIÓN: Universidad Católica de Colombia
	PROYECTO: Prototipo de Embarcación para la medición y monitoreo del pH del agua orientado al riego en cultivos de Maíz
	LUGAR: Municipio de Simijaca, Cundinamarca 
*/
#include <iostream> //Librería utilizada para el manejo de la entrada y salida de datos (cin, cout)
#include <windows.h> //Librería utilizada en este programa para el manejo de tíldes
#include <vector> //Librería que nos permite utilizar la estructura <vector> que es un arreglo dinámico. Utilizada pra la lista de adyacencia
#include <string> //Librería que permite el manejo de la fecha, hora y otros mensajes dentro de los nodos
#include <queue> //Librería útil porque DIJKSTRA necesita un priority_queue para siempre determinar el nodo con la distancia más pequeña
#include <limits> //Librería utilizada para inicializar distancias infinitas en el algoritmo de DIJKSTRA 
#include <ctime> //Librería utilizada para obtener la FECHA y HORA del sistema
#include <sstream> //Librería utilizada porque permite convertir datos a string (Útil para construir la fecha y hora)
#include <iomanip> //Librería que permite manipular el formato de impresión (Decimales, alineaciones, etc)
using namespace std; 

//STRUCT QUE NOS REPRESENTA LA INFORMACIÓN DE LAS MEDICIONES GUARDADA EN CADA NODO
struct Medicion {
	float pH; 
	float temperatura; 
	string fecha; 
	string hora;
	bool existe; 
	//Inicializador de atributos cuando se crea el objeto (CONSTRUCTOR):
	Medicion() : pH(0.0f), temperatura(0.0f), fecha(""), hora(""), existe(false) {}
};

//STRUCT PARA LA LISTA DE ADYACENCIA (VECINOS, PESO [DISTANCIA EN CM]) REPRESENTACIÓN DE LAS CONEXIONES: 
struct Adyacencia {
	int vecino; //Índice del nodo o vértice
	double peso; //Distancia en centímetros
	Adyacencia(int v, double p) : vecino(v), peso(p) {} //Constructor para la creación del arco
};

//FUNCIONES DE FECHA Y HORA: 
	//A) OBTENER LA FECHA ACTUAL EN STRING (FORMATO ES: DD/MM/AAAA)
string fechaActual(){
	time_t t = time(0); //Obtiene fecha y hora actual del sistema (Segundos desde 1970)
	tm* fecha = localtime(&t); //Convierte tiempo a una estructura tm
	stringstream ss; //Buffer para construir la fecha como texto
	ss 	<< setw(2) << setfill('0') << fecha->tm_mday << "/" //Formato indica que el número debe ocupar dos dígitos, en caso que no lo llena con ceros
		<< setw(2) << setfill('0') << (fecha->tm_mon + 1) << "/" //Obtiene el mes, se suma 1 porque los meses van de 0-11
		<< (fecha->tm_year + 1990); //Obtiene los años contados desde 1990
	return ss.str(); //Devuelve fecha armada en STRING
}
	//B) OBTENER LA HORA ACTUAL EN STRING (FORMATO ES: HH/MM/SS)
string horaActual(){
	time_t t = time(0); //Obtiene fecha y hora actual del sistema (Segundos desde 1970)
	tm* h = localtime(&t); //Convierte el tiempo a una estructura tm
	stringstream ss; //Buffer para construir la fecha como texto
	ss	<< setw(2) << setfill('0') << h->tm_hour << ":" //Formato indica que la hora debe ocupar dos dígitos, en caso que no lo llena con ceros
		<< setw(2) << setfill('0') << h->tm_min << ":" //Formato indica que los minutos deben ocupar dos dígitos, en caso que no lo llena con ceros
		<< setw(2) << setfill('0') << h->tm_sec; //Formato indica que los segundos deben ocupar dos dígitos, en caso que no lo llena con ceros
	return ss.str(); //Devuelve la hora armada en STRING 
}

	//CREACIÓN DEL GRAFO:  
// - Implementación del grafo con la siguiente estructura: 
	// A) nodesNames: Nombres automáticos "Nodo 1", "Nodo 2", ...
	// B) mediciones: vector <Medicion> con la última lectura del nodo  
	// C) adj: vector <vector<Adyacencia>> para la lista de adyacencia

class Grafo{
private: 
	vector<string> nodesNames; //Vector donde cada posición guarda el NOMBRE DEL NODO
	vector<Medicion> mediciones; //Vector donde cada posición guarda la MEDICIÓN MÁS RECIENTE (pH, Temperatura, Fecha, Hora, Existe[Para saber si ya tiene DATOS])
	vector<vector<Adyacencia>> adj;  //Vector para la lista de ADYACENCIA, permite almacenar el GRAFO de forma eficiente y ejecutar DIJKSTRA
public:  
	Grafo() {} //Constructor vacío
	int numNodos() const{
		return (int)nodesNames.size();  //Devuelve el número actual de nodos 
	}
	//Función para poder agregar un nuevo nodo. Retorna el índice (1-ÚLTIMO)
	int agregarNodo(){
		int nuevoIndex = numNodos() + 1; //Determina el número que tendrá el nuevo nodo
		//FUNCIÓN: .push_back sirve para AGREGAR un elemento al final del vector
		nodesNames.push_back("NODO " + to_string (nuevoIndex)); //Agrega el NOMBRE del nuevo nodo al vector NODESNAMES
		mediciones.push_back(Medicion()); //Agrega las MEDICIONES la NODO
		adj.emplace_back(); //Crea un OBJETO directamente dentro del VECTOR 
		//DIFERENCIA ENTRE .push_back Y ENTRE .emplace_back: Una crea el objeto fuera de la función y luego los agrega. La otra los crea dentro de la función y los agrega.
		cout << "OK. NODO AGREGADO: " << nodesNames.back() << " | ÍNDICE " << nuevoIndex << ")" <<endl;
		//FUNCIÓN: .back permite acceder al ÚLTIMO ELMENTO del VECTOR
	}
};

int main(){
	SetConsoleOutputCP(CP_UTF8); // Función para el uso de tildes en C++
	cout<<"Análisis"; 
}