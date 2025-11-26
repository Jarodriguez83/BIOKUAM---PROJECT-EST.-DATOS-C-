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

int main(){
	SetConsoleOutputCP(CP_UTF8); // Función para el uso de tildes en C++
	cout<<"Análisis"; 
}