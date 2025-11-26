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
#include <iostream>
#include <windows.h> //LIBRERÍA UTILIZADA PARA LAS TILDES
using namespace std; 

int main(){
	SetConsoleOutputCP(CP_UTF8); // Función para el uso de tildes en C++
	cout<<"Análisis"; 
}