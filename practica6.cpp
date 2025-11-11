#include <iostream>   // Biblioteca estándar de C++ que permite usar entrada/salida (cin, cout)
#include <iomanip>    // Biblioteca que permite manipular el formato de salida (por ejemplo setw)
#include <limits>     // Biblioteca usada para obtener límites de tipos numéricos y limpiar el buffer de entrada
using namespace std;  // Permite usar cin, cout, endl sin escribir std:: antes de cada uno

// =================== Configuración de la COLA ===================
const int CAP = 5;                  // Tamaño máximo de la cola (número de elementos que puede almacenar)
int q[CAP];                         // Arreglo que almacenará los elementos de la cola
bool ocupado[CAP] = {false,false,false,false,false}; // Arreglo booleano para marcar qué posiciones tienen datos válidos

int frente = 0;                     // Índice del primer elemento (frente de la cola)
int elementos = 0;                  // Contador de elementos actuales en la cola

// =================== Funciones auxiliares ===================

// Devuelve true si la cola está vacía (cuando no hay elementos)
inline bool estaVacia() { return elementos == 0; }

// Devuelve true si la cola está llena (cuando ya se alcanzó la capacidad máxima)
inline bool estaLlena() { return elementos == CAP; }

// Devuelve el índice donde está el último elemento (la "cola" propiamente)
inline int idxCola() { return (frente + elementos - 1 + CAP) % CAP; } 
// El +CAP es para evitar números negativos en el módulo

// =================== Funciones de entrada/salida ===================

// Función que pide un número entero al usuario con validación de errores
int leerEntero(const char* prompt) {
    int x;                    // Variable donde se guardará el número ingresado
    cout << prompt;           // Muestra el mensaje en pantalla
    while (!(cin >> x)) {     // Mientras el usuario no ingrese un número válido...
        cin.clear();          // Limpia el estado de error de cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Elimina caracteres inválidos del buffer
        cout << "Entrada invalida, intente de nuevo: ";       // Muestra un aviso de error
    }
    return x;                 // Retorna el número ingresado correctamente
}

// Función para pausar la ejecución hasta que el usuario presione Enter
void pausa() {
    cout << "\nPresione Enter para continuar...";   // Muestra mensaje
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia buffer
    cin.get();                                      // Espera que el usuario presione Enter
}

// =================== Impresión horizontal de la cola ===================

// Determina si una posición i está dentro del rango circular válido de la cola
bool estaEnRangoCircular(int i) {
    if (estaVacia()) return false; // Si la cola está vacía, ninguna posición está ocupada
    int cnt = 0, p = frente;       // Contador de pasos y posición actual (empezamos en frente)
    while (cnt < elementos) {      // Recorremos todos los elementos válidos
        if (p == i) return true;   // Si encontramos el índice buscado, devolvemos true
        p = (p + 1) % CAP;         // Avanzamos al siguiente elemento (modo circular)
        cnt++;                     // Incrementamos el contador
    }
    return false;                  // Si no se encuentra, devolvemos false
}

// Muestra el contenido de la cola en forma horizontal, con sus posiciones
void imprimirTabla() {
    cout << "\n-------- COLA (vista horizontal) --------\n"; // Encabezado de tabla
    
    // Fila de posiciones
    cout << setw(10) << "Posicion" << " | ";
    for (int i = 0; i < CAP; ++i) cout << setw(5) << i;   // Muestra las posiciones 0 a 4
    cout << "\n";

    // Fila de indicadores: muestra cuál es el frente (F) y la cola (C)
    cout << setw(10) << "" << " | ";
    for (int i = 0; i < CAP; ++i) {
        if (!estaVacia() && i == frente)            cout << setw(5) << "F"; // Marca frente
        else if (!estaVacia() && i == idxCola())    cout << setw(5) << "C"; // Marca cola
        else                                        cout << setw(5) << "";   // Celda vacía
    }
    cout << "\n";

    // Fila de valores: muestra los números almacenados en cada posición
    cout << setw(10) << "Valores" << " | ";
    for (int i = 0; i < CAP; ++i) {
        if (ocupado[i] && estaEnRangoCircular(i))   cout << setw(5) << q[i]; // Muestra el valor si está ocupado
        else                                        cout << setw(5) << "";   // Si está vacío, deja en blanco
    }
    cout << "\n=====================================\n"; // Línea final de la tabla
}

// =================== Operaciones principales de la cola ===================

// Inserta un nuevo elemento al final de la cola (operación ENCOLAR)
void encolar() {
    if (estaLlena()) {   // Verifica si la cola ya está llena
        cout << "[Error] Cola llena (overflow). No se puede insertar.\n";
        return;          // Si está llena, termina la función
    }
    int v = leerEntero("Valor entero a insertar: ");     // Pide un número al usuario
    int pos = (frente + elementos) % CAP;                // Calcula la posición de inserción (circular)
    q[pos] = v;                                          // Guarda el número en esa posición
    ocupado[pos] = true;                                 // Marca la celda como ocupada
    elementos++;                                         // Aumenta el contador de elementos
    cout << "[OK] Insertado " << v << " en posicion " << pos << ".\n"; // Confirma la operación
    imprimirTabla();                                     // Muestra el estado actual de la cola
}

// Quita el elemento del frente de la cola (operación DESENCOLAR)
void desencolar() {
    if (estaVacia()) {   // Verifica si la cola está vacía
        cout << "[Error] Cola vacia (underflow). No hay elementos para quitar.\n";
        return;          // Si está vacía, no hace nada
    }
    int quitado = q[frente];       // Guarda el valor que se va a eliminar
    ocupado[frente] = false;       // Marca la celda como vacía
    frente = (frente + 1) % CAP;   // Avanza el índice del frente (modo circular)
    elementos--;                   // Disminuye el contador de elementos
    cout << "[OK] Quitado " << quitado << " desde el frente.\n"; // Mensaje de confirmación
    imprimirTabla();               // Muestra el estado actualizado de la cola
}

// Vacía completamente la cola (reinicia todos los valores)
void limpiarCola() {
    if (estaVacia()) {  // Si ya está vacía, avisamos al usuario
        cout << "[Aviso] La cola ya esta vacia.\n";
        return;
    }
    for (int i = 0; i < CAP; ++i) ocupado[i] = false; // Marca todas las posiciones como vacías
    frente = 0;             // Reinicia el índice del frente
    elementos = 0;          // Reinicia el contador de elementos
    cout << "[OK] Cola limpiada.\n"; // Mensaje de éxito
    imprimirTabla();         // Muestra la cola vacía
}

// Muestra el estado general de la cola (vacía, llena o con espacio)
void estadoCola() {
    if (estaVacia()) { // Si no hay elementos
        cout << "COLA VACIA. Capacidad: " << CAP << "\n";
    } else if (estaLlena()) { // Si está al máximo
        cout << "COLA LLENA. Elementos: " << CAP << "\n";
    } else { // Si aún hay espacio
        cout << "COLA CON ESPACIO. Elementos: " << elementos
             << " / " << CAP << "  |  Huecos: " << (CAP - elementos) << "\n";
    }
    imprimirTabla(); // Muestra la cola con los datos actuales
}

// =================== Menú principal ===================

// Muestra el menú de opciones al usuario y devuelve su elección
int menu() {
    cout << "\n*** MENU DE OPERACIONES (COLA) ***\n"   // Encabezado
         << "1) Insertar (encolar)\n"                  // Opción 1: Insertar
         << "2) Quitar (desencolar)\n"                // Opción 2: Quitar
         << "3) Limpiar cola\n"                       // Opción 3: Vaciar completamente
         << "4) Mostrar estado\n"                     // Opción 4: Ver estado actual
         << "5) Salir\n";                             // Opción 5: Salir del programa
    return leerEntero("Elige una opcion: ");          // Pide al usuario una opción
}

// =================== Función principal ===================

// Punto de entrada del programa
int main() {
    for (;;) {              // Bucle infinito hasta que el usuario decida salir
        int op = menu();    // Muestra el menú y guarda la opción elegida
        cout << "\n";       // Salto de línea estético

        // Ejecuta la opción seleccionada
        switch (op) {
            case 1: encolar();      break;  // Insertar un elemento
            case 2: desencolar();   break;  // Quitar un elemento
            case 3: limpiarCola();  break;  // Vaciar toda la cola
            case 4: estadoCola();   break;  // Mostrar el estado actual
            case 5:
                cout << "Fin del programa.\n"; // Mensaje de salida
                return 0;                      // Termina la ejecución
            default:
                cout << "[Error] Opcion invalida.\n"; // Si la opción no existe
        }

        pausa(); // Pausa antes de volver a mostrar el menú
    }
}