// Pila LIFO con arreglo fijo (sin POO, sin <stack>)
// Fecha: 09/nov/2025
// Nota: implementación manual con validaciones básicas de overflow/underflow.

#include <iostream>  // Biblioteca estándar para entrada y salida (cin, cout)
#include <limits>    // Biblioteca que permite acceder a límites de tipos de datos (para limpiar buffer)
using namespace std; // Usamos el espacio de nombres estándar para evitar escribir std::

// ===== Config =====
const int CAP = 5;            // Tamaño máximo de la pila (solo puede tener 5 elementos)
int datos[CAP];               // Arreglo estático donde se almacenan los datos de la pila
int topIdx = -1;              // Índice de la cima de la pila (-1 indica que está vacía)

// ===== Prototipos =====
void menu();         // Muestra el menú principal con las opciones
void pintarPila();   // Imprime visualmente el contenido de la pila (de arriba hacia abajo)
void insertar();     // Inserta un nuevo elemento en la pila (operación push)
void quitar();       // Quita el elemento superior de la pila (operación pop)
void vaciar();       // Elimina todos los elementos (reinicia la pila)
void estado();       // Muestra información sobre el estado actual de la pila
void pausa();        // Detiene la ejecución hasta que el usuario presione Enter

// ===== Helpers =====
inline bool estaVacia() { return topIdx == -1; }     // Devuelve true si la pila está vacía
inline bool estaLlena() { return topIdx == CAP - 1; } // Devuelve true si la pila está llena

// ===== Programa principal =====
int main() {
    int op;  // Variable para guardar la opción del usuario

    // Bucle infinito para mantener el programa ejecutándose hasta que el usuario decida salir
    for (;;) {
        menu();                   // Mostramos las opciones del menú
        cout << "Opcion: ";       // Solicitamos al usuario que elija una opción

        // Validamos que la entrada sea numérica
        if (!(cin >> op)) { // Si la entrada no es un número válido
            cin.clear(); // Limpia el estado de error del flujo de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Borra la entrada incorrecta del buffer
            cout << "[Aviso] Entrada invalida.\n"; // Mensaje de error
            pausa(); // Esperamos al usuario antes de continuar
            continue; // Saltamos a la siguiente iteración del bucle
        }

        // Ejecutamos la opción seleccionada
        switch (op) {
            case 1: insertar(); break;  // Opción 1: Insertar un nuevo elemento
            case 2: quitar();   break;  // Opción 2: Quitar un elemento
            case 3: vaciar();   break;  // Opción 3: Vaciar la pila
            case 4: estado();   break;  // Opción 4: Mostrar estado actual
            case 5: // Opción 5: Salir del programa
                cout << "\nSaliendo... Gracias.\n"; // Mensaje de despedida
                return 0; // Terminamos la ejecución
            default:
                cout << "[Error] Opcion fuera de rango.\n"; // Mensaje si el número no corresponde a una opción válida
        }

        pausa(); // Esperamos al usuario antes de mostrar el menú nuevamente
    }

    return 0; // Fin del programa principal
}

// ===== Implementacion =====

// Muestra el menú principal con las opciones disponibles
void menu() {
    cout << "\n----------------------------\n";          // Línea decorativa
    cout << "        PILA (ARREGLO)        \n";         // Título del programa
    cout << "----------------------------\n";          // Línea decorativa
    cout << "1) Insertar un elemento (push)\n";        // Opción para insertar un valor
    cout << "2) Quitar un elemento (pop)\n";           // Opción para quitar un valor
    cout << "3) Limpiar pila\n";                       // Opción para vaciar la pila
    cout << "4) Mostrar estado de pila:\n";            // Opción para mostrar el estado
    cout << "5) Salir\n";                              // Opción para salir del programa
}

// Muestra visualmente el contenido de la pila de arriba hacia abajo
void pintarPila() {
    cout << "\n--- Pila (vista vertical) ---\n";       // Encabezado
    cout << "Posicion\tValor\n";                      // Etiquetas de columnas

    // Recorremos el arreglo desde la cima (índice 4) hasta el fondo (índice 0)
    for (int i = CAP - 1; i >= 0; --i) {
        cout << i << "\t\t";                          // Mostramos el índice actual

        if (i <= topIdx) {                            // Si hay un elemento almacenado en esa posición
            cout << datos[i];                         // Mostramos el valor
            if (i == topIdx) cout << "  <- CIMA";     // Indicamos cuál es la cima
        } else {
            cout << "---";                            // Espacio vacío en la pila
        }

        if (i == 0) cout << "  <- FONDO";             // Marcamos la base de la pila
        cout << "\n";                                 // Salto de línea
    }
}

// Inserta un nuevo elemento en la pila
void insertar() {
    // Comprobamos si la pila ya está llena
    if (estaLlena()) {
        cout << "\n[Pila llena] No es posible insertar (overflow).\n"; // Mensaje de error
        return; // No insertamos nada
    }

    int v; // Variable para almacenar el valor ingresado
    cout << "\nValor entero a agregar: "; // Solicitamos el valor al usuario
    cin >> v; // Leemos el valor ingresado

    datos[++topIdx] = v; // Incrementamos la cima y colocamos el nuevo valor en esa posición

    cout << "[OK] Insertado " << v << " en posicion " << topIdx << ".\n"; // Confirmamos la inserción
    pintarPila(); // Mostramos el estado actual de la pila
}

// Elimina el elemento superior de la pila
void quitar() {
    // Comprobamos si la pila está vacía
    if (estaVacia()) {
        cout << "\n[Pila vacia] No hay elementos para quitar (underflow).\n"; // Mensaje de error
        return; // No se puede eliminar nada
    }

    int quitado = datos[topIdx--]; // Guardamos el valor de la cima y reducimos el índice
    cout << "[OK] Quitado " << quitado << " de la cima.\n"; // Mostramos qué valor se quitó
    pintarPila(); // Mostramos cómo quedó la pila
}

// Vacía completamente la pila (reinicia la cima)
void vaciar() {
    // Si la pila ya está vacía, avisamos
    if (estaVacia()) {
        cout << "\n[Aviso] La pila ya estaba vacia.\n"; // No hay nada que limpiar
        return;
    }

    topIdx = -1; // Restablecemos la cima (indicando que está vacía)
    cout << "\n[OK] Pila limpiada.\n"; // Confirmamos la acción
    pintarPila(); // Mostramos la pila vacía
}

// Muestra el estado general de la pila
void estado() {
    cout << "\n*** Estado de la pila ***\n"; // Título

    // Verificamos cada posible estado de la pila
    if (estaVacia()) {
        cout << "PILA VACIA. Capacidad: " << CAP << "\n"; // Si no hay elementos
    } else if (estaLlena()) {
        cout << "PILA LLENA. Elementos: " << CAP << "\n"; // Si está al máximo
    } else {
        // Si tiene algunos elementos
        cout << "PILA CON ESPACIO. Elementos: " << (topIdx + 1)
             << " / " << CAP << "\n"; // Mostramos cuántos hay
        cout << "Huecos disponibles: " << (CAP - topIdx - 1) << "\n"; // Cuántos faltan para llenarse
    }

    pintarPila(); // Mostramos el contenido actual
}

// Detiene el programa hasta que el usuario presione Enter
void pausa() {
    cout << "\nPresione Enter para continuar..."; // Indicamos que espere
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiamos el buffer de entrada
    cin.get(); // Esperamos que el usuario presione Enter
}
