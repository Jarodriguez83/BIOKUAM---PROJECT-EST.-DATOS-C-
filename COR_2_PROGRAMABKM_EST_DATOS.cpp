/* =======================
   PROGRAMA: BIOKUAM - MULTILISTA (FINCAS Y MUESTRAS)
   FECHA: 18-10-2025
   DOCUMENTACIÓN: (JSNT (JADER SANTIAGO NIEVES TAMI Y JARR (JHON ALEXANDER RODRIGUEZ REDONDO)))
   DESCRIPCIÓN:
   - Lista principal: Fincas (lista lineal simple)
   - Sublistas por finca: Muestras (lista lineal simple)
   - Historiales: Listas lineales simples (PH y Temperatura)
   - Validación: folio de matrícula inmobiliaria único
   - Simulación: recorrido del barco por finca seleccionada
   NOTA: Para revisar el manual de usuario y saber las funcionalidades del programa entrar al siguiente LINK:  
   https://drive.google.com/drive/folders/1iRpriOaJ_pYzcx1y9u0acqGkJTdmqSyq?usp=sharing
   ======================= */

#include <iostream> //Librería para el manejo de la entrada y salida de datos  
#include <cstdlib> //Para el uso de funciones con números aleatorios
#include <ctime> //Para obtener fecha y hora del sistema 
#include <sstream> //Para la conversión de datos (Para la fecha y hora a una cadena de texto (string))
#include <cmath> //Para usos matemáticos
#include <windows.h> //Interactuar directamente con el sistema operativo (Usado en este caso para el uso de tildes)
using namespace std;

/* =========================
   ESTRUCTURAS
   ========================= */

// [JSN] Nodo de la sublista: Muestras tomadas por el prototipo en una finca
struct Muestra {
    int idMuestra; 
    float pH;
    float temperatura;
    string fecha;
    string hora;
    Muestra* sig;
};

// [JSN] Nodo de la lista principal: Finca
struct Finca {
    string nombre;
    string folio;
    Finca* sig;
    Muestra* sub;
};

// [JARR] Nodo para historial de variaciones
struct Variacion {
    string fechaDeteccion;
    string finca;
    float valorVariacion;
    string tipo;
    Variacion* sig;
};

/* =========================
   FUNCIONES AUXILIARES FECHA/HORA
   ========================= */

string fecha() {
    time_t t = time(0); //Obtiene la fecha del sistema númerico (En segundos desde 1970)
    tm* fecha = localtime(&t); //Crea la estructura (DD/MM/AAAA)
    stringstream ss; //Se van guardando los valores, cumple con la función de concatenador de texto
    ss 	<< (fecha->tm_mday) << "/" //Día
		<< (fecha->tm_mon + 1) << "/" //Mes (Se suma 1 porque empieza desde 0)
		<< (fecha->tm_year + 1900); //Año y suma 1900 porque es la fecha desde que se empieza a contar
    return ss.str(); //Pasa a string y lo retorna
}

string horaActual() {
    time_t t = time(0); //Obtiene la fecha del sistema numérico (En segundos desde 1970)
    tm* h = localtime(&t); //Crea la estructura (HH/MM/SS)
    stringstream ss; //Se van guardando los valores, cumple con la función de concatenador de texto
    ss 	<< (h->tm_hour) << ":" //Hora
		<< (h->tm_min) << ":" //Minutos
		<< (h->tm_sec); //Segundos
    return ss.str(); //Pasa a string y lo retorna
}

/* =========================
   CREACIÓN DE NODOS
   ========================= */
//Crear NODO para la sublista de MUESTRAS
Muestra* crearNuevoMuestra(int id) {
    Muestra* nuevo = new Muestra; 
    nuevo->idMuestra = id;
    nuevo->pH = 6 + rand() % 3; //(Genera números entre 0 y 2) El rango de valores sería entre 6 - 8
    nuevo->temperatura = 15 + rand() % 18; //(Genera números entre 0 y 17) El rango de valores sería entre 15 - 32
    nuevo->fecha = fecha(); //Inicializa con la fecha del sistema
    nuevo->hora = horaActual(); //Inicializa con la hora del sistema
    nuevo->sig = NULL; //Siguiente NODO apunta a NULL
    return nuevo; //Retorna el puntero
}

Finca* crearFinca(string nombre, string folio) {
    Finca* nueva = new Finca;
    nueva->nombre = nombre;
    nueva->folio = folio;
    nueva->sig = NULL;
    nueva->sub = NULL;
    return nueva;
}

Variacion* crearVariacion(string finca, float valor, string tipo) {
    Variacion* v = new Variacion;
    v->fechaDeteccion = fecha();
    v->finca = finca;
    v->valorVariacion = valor;
    v->tipo = tipo;
    v->sig = NULL;
    return v;
}

/* =========================
   INSERCIONES
   ========================= */

void insertarFinca(Finca*& cab, Finca* nuevo) {
    if (cab == NULL) //Si 'cab' llega ser igual a NULL en la lista principal
        cab = nuevo; //Se asigna 'cab' al puntero 'nuevo'
    else {
        Finca* aux = cab; //Crea un puntero determinado como 'aux' para recorrer la lista principal
        while (aux->sig != NULL) //Mientras 'aux' sea diferente de NULL
            aux = aux->sig; //Auxiliar recorre las 'FINCAS'
        aux->sig = nuevo; //Se reacomoda el puntero 'nuevo'
    }
}

void insertarMuestra(Muestra*& cab, Muestra* nuevo) {
    if (cab == NULL) //Si 'cab' llega ser igual a NULL en la lista secundaria
        cab = nuevo; //Se asigna 'cab' al puntero 'nuevo'
    else {
        Muestra* aux = cab; //Crea el puntero 'aux' para recorrer la sublista
        while (aux->sig != NULL) //Mientras 'aux' sea diferente de NULL
            aux = aux->sig; //Auxiliar recorre las 'MUESTRAS'
        aux->sig = nuevo; //Se reacomoda el puntero 'nuevo'
    }
}

void insertarVariacion(Variacion*& cab, Variacion* nuevo) {
    if (cab == NULL) //Si 'cab' llega ser igual a NULL
        cab = nuevo; //Se asigna 'cab' al puntero 'nuevo'
    else {
        Variacion* aux = cab; //Se crea el puntero 'aux' para recorrer la lista
        while (aux->sig != NULL) //Mientras el 'aux' sea diferente de NULL
            aux = aux->sig; //Auxiliar recorre las 'VARIACIONES'
        aux->sig = nuevo; //Se reacomoda el puntero 'nuevo'
    }
}

/* =========================
   BÚSQUEDAS Y VALIDACIONES
   ========================= */
//Función para determinar que el FOLIO de cada una de las FINCAS es ÚNICO 
bool existeFolio(Finca* cab, const string& folio) {
	//CONST: Implica que no se puede modificar el valor dentro de la función
    Finca* aux = cab; //Se crea el puntero 'aux'
    while (aux != NULL) { //Mientras el 'aux' sea diferente de NULL
        if (aux->folio == folio) return true; //Si el FOLIO ingresado es TRUE al que se encuentra 
        aux = aux->sig; //Pasa a la siguiente 'FINCA'
    }
    return false;
}
//Función para buscar FINCA dependiendo del FOLIO de MATRICULA
Finca* buscarFinca(Finca* cab, const string& folio) {
    Finca* aux = cab; //Crea el puntero 'aux'
    while (aux != NULL) { //Mientras 'aux' sea diferente de NULL
        if (aux->folio == folio) return aux; //Si encuentra el FOLIO entonces retorna el NODO
        aux = aux->sig; //Pasa a la siguiente FINCA
    }
    return NULL;
}

/* =========================
   IMPRESIÓN / MOSTRAR ESTRUCTURAS
   ========================= */

void mostrarMultilista(Finca* cab) {
    cout << "\n--------------------- MULTILISTA: FINCAS Y MUESTRAS ---------------------\n";
    if (cab == NULL) { //Si 'cab' es igual a NULL
        cout << "No hay fincas registradas.\n"; //Multilista se encuentra vacía
        return;
    }

    Finca* f = cab; //Se crea el puntero 'f'
    while (f != NULL) { //Mientras 'f' sea diferente de NULL
        cout << "\nFinca: " << f->nombre << "  |  Folio: " << f->folio << "\n"; //Imprime NOMBRE y FOLIO de la finca
        if (f->sub == NULL) { //Condición para saber si la sublista se encuentra vacía
            cout << "   (Sin muestras registradas)\n"; //Avisa al usuario que la sublista esta vacía
        } else {
            Muestra* m = f->sub; //Crea el puntero 'm' para que recorra la sublista
            while (m != NULL) { //Mientras 'm' sea diferente de NULL
                cout << "   MUESTRA " << m->idMuestra << "  - PH: " << m->pH
                     << "  | TEMP: " << m->temperatura
                     << "  | FECHA: " << m->fecha << "  | HORA: " << m->hora << "\n";
                m = m->sig; //Pasa a la siguiente MUESTRA
            }
        }
        f = f->sig; //Pasa a la siguiente FINCA
    }
    cout << "-----------------------------------------------------------------------\n";
}
//Función de LISTA para saber el HISTORIAL de VARIACIONES
void mostrarHistorial(Variacion* cab, const string& titulo) {
    cout << "\n===== HISTORIAL: " << titulo << " =====\n";
    if (cab == NULL) { //Condicional para saber si la lista esta vaçía
        cout << "No hay variaciones registradas.\n";
        return;
    }
    Variacion* aux = cab; //Se crea el puntero 'aux'
    int i = 1; //Inicializar variable 'i' en 1
    while (aux != NULL) { //Mientras el 'aux' sea diferente de NULL
        cout << i << ". Fecha: " << aux->fechaDeteccion 
             << " | Finca: " << aux->finca
             << " | Valor variación: " << aux->valorVariacion
             << " | Tipo: " << aux->tipo << "\n";
        aux = aux->sig; //Pasa a la siguiente VARIACIÓN
        i++; //Incrementa de 1 en 1, la variable 'i'
    }
}

/* =========================
   LÓGICA DE SIMULACIÓN AJUSTADA
   ========================= */

void simularRecorridoPorFinca(Finca* cab, Variacion*& histPH, Variacion*& histTemp) {
    if (cab == NULL) { //Condicional para saber si hay FINCAS registradas
        cout << "\nNo hay fincas registradas. Registre una finca primero.\n";
        return;
    }

    cout << "\n--- FINCAS DISPONIBLES ---\n";
    Finca* temp = cab; //Se crea el puntero 'temp'
    while (temp != NULL) { //Mientras 'temp' sea diferente de NULL
        cout << "Finca: " << temp->nombre << " | Folio: " << temp->folio << endl;
        temp = temp->sig; //Avanza a la siguiente FINCA
    }

    string folioSel; //Inicializar variable de 'folioSel' como string
    cout << "\nIngrese el folio de la finca para simular el recorrido: ";
    cin >> folioSel; //Entrada por teclado de 'folioSel'

    Finca* fincaSel = buscarFinca(cab, folioSel); //Se crea el puntero fincaSel
    if (fincaSel == NULL) {
        cout << "\n[ERROR] Finca no encontrada.\n";
        return;
    }

    int cantidad; //Inicializar variable para determinar la cantidad de muestras para esa finca
    cout << "¿Cuántas muestras desea registrar para esta finca? ";
    cin >> cantidad; //Entrada por teclado de la cantidad de muestras 

    // Registrar las muestras nuevas antes de simular
    int siguienteId = 1;
    if (fincaSel->sub != NULL) {
        Muestra* aux = fincaSel->sub;
        while (aux->sig != NULL) aux = aux->sig;
        siguienteId = aux->idMuestra + 1;
    }

    for (int i = 0; i < cantidad; i++) {
        Muestra* nueva = crearNuevoMuestra(siguienteId + i);
        insertarMuestra(fincaSel->sub, nueva);
    }

    cout << "\n✅ " << cantidad << " muestras registradas. Iniciando recorrido...\n";

    // Simulación del recorrido SOLO para la finca seleccionada
    Muestra* m = fincaSel->sub;
    while (m != NULL) {
        cout << "\nMUESTRA " << m->idMuestra << " - Valores anteriores -> PH: " << m->pH
             << " | TEMP: " << m->temperatura
             << " | FECHA: " << m->fecha << " | HORA: " << m->hora << "\n";

        float nuevoPH, nuevaTemp;
        string nuevaFecha, nuevaHora;

        cout << "  - INGRESE EL NUEVO VALOR DEL PH: ";
        cin >> nuevoPH;
        cout << "  - INGRESE EL NUEVO VALOR DE LA TEMPERATURA: ";
        cin >> nuevaTemp;
        cin.ignore();
        cout << "  - INGRESE LA FECHA (DD/MM/AAAA) O ENTER PARA USAR ACTUAL: ";
        getline(cin, nuevaFecha);
        if (nuevaFecha.empty()) nuevaFecha = fecha();
        cout << "  - INGRESE LA HORA (HH:MM:SS) O ENTER PARA USAR ACTUAL: ";
        getline(cin, nuevaHora);
        if (nuevaHora.empty()) nuevaHora = horaActual();

        float diffPH = fabs(nuevoPH - m->pH); //FABS para valor absoluto
        float diffTemp = fabs(nuevaTemp - m->temperatura); //FABS para valor absoluto

        if (diffPH > 0.4f) {
            string tipo = (nuevoPH > m->pH) ? "MAYOR" : "MENOR";
            cout << " ⚠️ VARIACIÓN EN PH detectada.\n";
            insertarVariacion(histPH, crearVariacion(fincaSel->nombre + " (" + fincaSel->folio + ")", diffPH, tipo));
        }
        if (diffTemp > 1.8f) {
            string tipo = (nuevaTemp > m->temperatura) ? "MAYOR" : "MENOR";
            cout << " ⚠️ VARIACIÓN EN TEMPERATURA detectada.\n";
            insertarVariacion(histTemp, crearVariacion(fincaSel->nombre + " (" + fincaSel->folio + ")", diffTemp, tipo));
        }

        m->pH = nuevoPH;
        m->temperatura = nuevaTemp;
        m->fecha = nuevaFecha;
        m->hora = nuevaHora;

        m = m->sig;
    }

    cout << "\n--- RECORRIDO FINALIZADO ---\n";
}

/* =========================
   MENÚ PRINCIPAL
   ========================= */

int main() {
	SetConsoleOutputCP(CP_UTF8); // Función para el uso de tildes en C++
    srand(time(0));
    Finca* cabFincas = NULL;
    Variacion* historialPH = NULL;
    Variacion* historialTemp = NULL;
    int opcion = -1;
	
	cout << " ==========================================\n";
    cout << "|                 BIOKUAM                  |\n";
    cout << " ==========================================\n";
    cout << "|  CREADO POR:                             |\n";
    cout << "|    - Jhon Alexander Rodriguez Redondo    |\n";
    cout << "|    - Jader Santiago Nieves Tami          |\n";
    cout << " ------------------------------------------\n";
	
    do {
        cout << "\n========= MENU PRINCIPAL BIOKUAM =========" << endl;
        cout << " 1| Registrar nueva finca" << endl;
        cout << " 2| Mostrar multilista (Fincas y Muestras)" << endl;
        cout << " 3| Simular recorrido del barco (Por finca)" << endl;
        cout << " 4| Mostrar historial de variaciones (PH)" << endl;
        cout << " 5| Mostrar historial de variaciones (Temperatura)" << endl;
        cout << " 0| Salir" << endl;
        cout << "==========================================" << endl;
        cout << "	Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                string nombreFinca, folio;
                cout << "\nNombre de la finca: ";
                getline(cin, nombreFinca);
                cout << "Folio de matrícula (único): ";
                getline(cin, folio);

                if (existeFolio(cabFincas, folio))
                    cout << "\n[ERROR] Ya existe una finca con ese folio.\n";
                else {
                    insertarFinca(cabFincas, crearFinca(nombreFinca, folio));
                    cout << "\n✅ Finca registrada correctamente.\n";
                }
                break;
            }

            case 2: mostrarMultilista(cabFincas); break;
            case 3: simularRecorridoPorFinca(cabFincas, historialPH, historialTemp); break;
            case 4: mostrarHistorial(historialPH, "PH"); break;
            case 5: mostrarHistorial(historialTemp, "TEMPERATURA"); break;
            case 0: cout << "\nSaliendo del programa...\n"; break;
            default: cout << "\n[Opción inválida, intente de nuevo.]\n";
        }

    } while (opcion != 0);

    return 0;
}
