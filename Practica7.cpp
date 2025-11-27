#include <iostream>           // Incluye la librería estándar para entrada y salida (cout, cin).
using namespace std;          // Permite usar cout y cin sin escribir std:: antes.

// Estructura básica de un nodo de lista simplemente enlazada
struct Nodo {                 // Define una estructura llamada Nodo.
    int dato;                 // Campo donde se almacena el valor del nodo.
    Nodo* siguiente;          // Puntero que apunta al siguiente nodo de la lista.
};

// Prototipos de funciones
void insertarInicio(Nodo* &cabeza, int valor);     // Prototipo de la función que inserta al inicio.
bool buscarElemento(Nodo* cabeza, int valor);      // Prototipo de la función que busca un elemento.
bool eliminarElemento(Nodo* &cabeza, int valor);   // Prototipo de la función que elimina un nodo.
void recorridoDirecto(Nodo* cabeza);               // Prototipo del recorrido de cabeza a cola.
void mostrarListaActual(Nodo* cabeza);             // Prototipo para mostrar la lista actual.
void mostrarMenu();                                // Prototipo para mostrar el menú principal.
void liberarLista(Nodo* &cabeza);                  // Prototipo para liberar la memoria de la lista.

// Muestra el menú principal
void mostrarMenu() {                               // Función que imprime el menú de opciones.
    cout << "========== MENU ==========\n";         // Línea superior del menú.
    cout << "1. Insertar elemento en la lista\n";   // Opción 1: insertar.
    cout << "2. Buscar elemento de la lista\n";     // Opción 2: buscar.
    cout << "3. Eliminar elemento de la lista\n";   // Opción 3: eliminar.
    cout << "4. Recorrido directo (cabeza -> cola)\n"; // Opción 4: mostrar lista.
    cout << "5. Salir\n";                           // Opción 5: salir.
    cout << "==========================\n";          // Línea inferior del menú.
}

// Muestra la lista actual (solo si tiene elementos)
void mostrarListaActual(Nodo* cabeza) {             // Función para mostrar la lista sin mensajes extra.
    if (cabeza == nullptr) {                        // Si la cabeza es NULL, la lista está vacía.
        return;                                     // No mostrar nada aquí, solo salir.
    }

    cout << "\nLista actual (cabeza -> cola): ";    // Mensaje de encabezado.
    Nodo* actual = cabeza;                          // Puntero auxiliar para recorrer la lista.

    while (actual != nullptr) {                     // Bucle mientras existan nodos.
        cout << actual->dato;                       // Imprimir el valor del nodo.
        if (actual->siguiente != nullptr) {         // Si existe un siguiente nodo...
            cout << " -> ";                         // Imprime una flecha para representación.
        }
        actual = actual->siguiente;                 // Avanza al siguiente nodo.
    }
    cout << "\n\n";                                 // Salto de línea extra al finalizar.
}

// Inserta un nuevo elemento al inicio de la lista
void insertarInicio(Nodo* &cabeza, int valor) {     // Función que inserta al inicio.
    Nodo* nuevo = new Nodo;                         // Reserva memoria para un nuevo nodo.
    nuevo->dato = valor;                            // Asigna el dato al nodo.
    nuevo->siguiente = cabeza;                      // El nuevo nodo apunta al antiguo primer nodo.
    cabeza = nuevo;                                 // La cabeza ahora es el nuevo nodo.
}

// Busca un elemento en la lista (true si lo encuentra)
bool buscarElemento(Nodo* cabeza, int valor) {      // Función que busca un valor.
    Nodo* actual = cabeza;                          // Comienza a buscar desde la cabeza.

    while (actual != nullptr) {                     // Recorre la lista mientras existan nodos.
        if (actual->dato == valor) {                // Si encuentra el valor...
            return true;                            // Devuelve true indicando éxito.
        }
        actual = actual->siguiente;                 // Avanza al siguiente nodo.
    }

    return false;                                   // Si termina el bucle, el valor no está.
}

// Elimina la primera ocurrencia de un valor en la lista
bool eliminarElemento(Nodo* &cabeza, int valor) {   // Función para eliminar un nodo.
    if (cabeza == nullptr) {                        // Si la lista está vacía...
        return false;                               // No se puede eliminar nada.
    }

    // Caso 1: el elemento está en la cabeza
    if (cabeza->dato == valor) {                    // Si el primer nodo contiene el valor...
        Nodo* aux = cabeza;                         // Guardamos el nodo a eliminar.
        cabeza = cabeza->siguiente;                 // Movemos la cabeza al siguiente nodo.
        delete aux;                                 // Liberamos memoria del nodo eliminado.
        return true;                                // Devolvemos éxito.
    }

    // Caso 2: el elemento está en medio o al final
    Nodo* anterior = cabeza;                        // Puntero al nodo anterior.
    Nodo* actual = cabeza->siguiente;               // Puntero al nodo actual.

    while (actual != nullptr && actual->dato != valor) {  // Buscar el valor.
        anterior = actual;                          // Avanza el puntero anterior.
        actual = actual->siguiente;                 // Avanza actual.
    }

    if (actual == nullptr) {                        // Si el valor no se encontró...
        return false;                               // No se elimina nada.
    }

    // Saltamos el nodo actual para eliminarlo.
    anterior->siguiente = actual->siguiente;        // Enlazamos el anterior con el siguiente del actual.
    delete actual;                                  // Liberamos memoria del nodo eliminado.
    return true;                                    // Eliminación exitosa.
}

// Recorre la lista de cabeza a cola
void recorridoDirecto(Nodo* cabeza) {               // Función que recorre e imprime la lista.
    if (cabeza == nullptr) {                        // Si la lista está vacía...
        cout << "La lista no tiene elementos. (Lista vacia)\n"; // Mensaje de lista vacía.
        return;                                     // Salir de la función.
    }

    cout << "Recorrido directo (cabeza -> cola): "; // Mensaje de encabezado.
    Nodo* actual = cabeza;                          // Puntero para recorrer la lista.

    while (actual != nullptr) {                     // Recorremos la lista completa.
        cout << actual->dato;                       // Imprimir el dato actual.
        if (actual->siguiente != nullptr) {         // Si no es el último nodo...
            cout << " -> ";                         // Imprimimos flecha.
        }
        actual = actual->siguiente;                 // Avanzamos al siguiente.
    }
    cout << "\n";                                   // Nueva línea después del recorrido.
}

// Libera toda la memoria de la lista
void liberarLista(Nodo* &cabeza) {                  // Función que libera todos los nodos.
    while (cabeza != nullptr) {                     // Mientras existan nodos...
        Nodo* aux = cabeza;                         // Guardamos la cabeza para eliminarla.
        cabeza = cabeza->siguiente;                 // Avanzamos la cabeza al siguiente nodo.
        delete aux;                                 // Eliminamos el nodo guardado.
    }
}

int main() {                                        // Función principal del programa.
    Nodo* cabeza = nullptr;                         // Inicializamos la lista como vacía.
    int opcion;                                     // Variable para almacenar la opción del menú.
    int valor;                                      // Variable para almacenar valores ingresados.

    // El programa se mantiene en ejecución mostrando el menú
    // hasta que el usuario elige la opción 5 (Salir).
    do {                                            // Inicio del bucle principal.
        cout << "============================\n";     // Línea decorativa.
        mostrarListaActual(cabeza);                 // Muestra la lista actual (si hay elementos).
        mostrarMenu();                              // Muestra el menú al usuario.

        cout << "Elija una opcion: ";               // Solicita una opción al usuario.
        cin >> opcion;                              // Guarda la opción ingresada.

        switch (opcion) {                           // Selección basada en la opción.
        case 1:                                     // Caso insertar.
            cout << "Ingrese el valor a insertar: ";
            cin >> valor;
            insertarInicio(cabeza, valor);          // Insertar valor en la lista.
            cout << "Valor " << valor << " agregado con exito!\n";
            break;

        case 2:                                     // Caso buscar.
            cout << "Ingrese el valor a buscar: ";
            cin >> valor;
            if (buscarElemento(cabeza, valor)) {    // Llamada a función buscar.
                cout << "El valor " << valor << " SI fue encontrado en la lista.\n";
            } else {
                cout << "El valor " << valor << " NO fue encontrado.\n";
            }
            break;

        case 3:                                     // Caso eliminar.
            cout << "Ingrese el valor a eliminar: ";
            cin >> valor;
            if (eliminarElemento(cabeza, valor)) {  // Intentar eliminar valor.
                cout << "Valor " << valor << " eliminado con exito!\n";
            } else {
                cout << "El valor " << valor << " no se encuentra en la lista. No se elimino nada.\n";
            }
            break;

        case 4:                                     // Caso recorrido.
            recorridoDirecto(cabeza);               // Mostrar recorrido.
            break;

        case 5:                                     // Caso salir.
            cout << "Saliendo de la ejecucion...\n";
            break;

        default:                                    // Opción inválida.
            cout << "Opcion no valida. Intente de nuevo.\n";
            break;
        }

        cout << "\n";                               // Salto de línea después de cada operación.

    } while (opcion != 5);                          // El ciclo continúa hasta elegir 5.

    liberarLista(cabeza);                           // Liberar memoria antes de cerrar el programa.
    return 0;                                       // Fin del programa.
}
