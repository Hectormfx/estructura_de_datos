#include <iostream>
using namespace std;

// ===============================
// Estructura del nodo del ABB
// ===============================
struct Nodo {
    int dato;        // Valor almacenado en el nodo
    Nodo* izq;       // Puntero al hijo izquierdo
    Nodo* der;       // Puntero al hijo derecho
};

// ===============================
// Prototipos de funciones
// ===============================
Nodo* crearNodo(int valor);
void insertarNodo(Nodo* &raiz, int valor, bool &insertado);
bool buscarNodo(Nodo* raiz, int valor);
bool eliminarNodo(Nodo* &raiz, int valor);
Nodo* minimoNodo(Nodo* raiz);

void preorden(Nodo* raiz);
void inorden(Nodo* raiz);
void postorden(Nodo* raiz);

void mostrarArbolPreorden(Nodo* raiz);
void mostrarRecorridos(Nodo* raiz);

int altura(Nodo* raiz);
int contarNodos(Nodo* raiz);

void mostrarMenu();
void liberarArbol(Nodo* &raiz);

// ===============================
// Implementaciones
// ===============================

Nodo* crearNodo(int valor) {
    Nodo* nuevo = new Nodo;
    nuevo->dato = valor;
    nuevo->izq = nullptr;
    nuevo->der = nullptr;
    return nuevo;
}

// Inserta un nodo en el ABB (sin duplicados)
void insertarNodo(Nodo* &raiz, int valor, bool &insertado) {
    if (raiz == nullptr) {
        raiz = crearNodo(valor);
        insertado = true;
    } else if (valor < raiz->dato) {
        insertarNodo(raiz->izq, valor, insertado);
    } else if (valor > raiz->dato) {
        insertarNodo(raiz->der, valor, insertado);
    } else {
        // valor == raiz->dato -> duplicado
        insertado = false;
    }
}

// Busca un valor en el ABB
bool buscarNodo(Nodo* raiz, int valor) {
    if (raiz == nullptr) return false;
    if (valor == raiz->dato) return true;
    if (valor < raiz->dato)
        return buscarNodo(raiz->izq, valor);
    else
        return buscarNodo(raiz->der, valor);
}

// Devuelve el nodo con el valor mínimo del subárbol
Nodo* minimoNodo(Nodo* raiz) {
    if (raiz == nullptr) return nullptr;
    while (raiz->izq != nullptr) {
        raiz = raiz->izq;
    }
    return raiz;
}

// Elimina un valor del ABB, devuelve true si se eliminó
bool eliminarNodo(Nodo* &raiz, int valor) {
    if (raiz == nullptr) {
        return false;  // no encontrado
    }

    if (valor < raiz->dato) {
        return eliminarNodo(raiz->izq, valor);
    } else if (valor > raiz->dato) {
        return eliminarNodo(raiz->der, valor);
    } else {
        // Encontramos el nodo a eliminar
        if (raiz->izq == nullptr && raiz->der == nullptr) {
            // Caso 1: sin hijos
            delete raiz;
            raiz = nullptr;
        } else if (raiz->izq == nullptr) {
            // Caso 2: solo hijo derecho
            Nodo* temp = raiz;
            raiz = raiz->der;
            delete temp;
        } else if (raiz->der == nullptr) {
            // Caso 2: solo hijo izquierdo
            Nodo* temp = raiz;
            raiz = raiz->izq;
            delete temp;
        } else {
            // Caso 3: dos hijos
            Nodo* sucesor = minimoNodo(raiz->der);
            raiz->dato = sucesor->dato;
            // Eliminamos el sucesor (que ahora está duplicado en el subárbol derecho)
            eliminarNodo(raiz->der, sucesor->dato);
        }
        return true;
    }
}

// ===============================
// Recorridos
// ===============================
void preorden(Nodo* raiz) {
    if (raiz == nullptr) return;
    cout << raiz->dato << " ";
    preorden(raiz->izq);
    preorden(raiz->der);
}

void inorden(Nodo* raiz) {
    if (raiz == nullptr) return;
    inorden(raiz->izq);
    cout << raiz->dato << " ";
    inorden(raiz->der);
}

void postorden(Nodo* raiz) {
    if (raiz == nullptr) return;
    postorden(raiz->izq);
    postorden(raiz->der);
    cout << raiz->dato << " ";
}

// Muestra el árbol en preorden o avisa si está vacío
void mostrarArbolPreorden(Nodo* raiz) {
    if (raiz == nullptr) {
        cout << "El arbol esta vacio (sin elementos).\n";
    } else {
        cout << "Recorrido en preorden: ";
        preorden(raiz);
        cout << "\n";
    }
}

// Menú para recorridos inorden/postorden
void mostrarRecorridos(Nodo* raiz) {
    if (raiz == nullptr) {
        cout << "El arbol esta vacio, no hay recorridos que mostrar.\n";
        return;
    }

    int opcionRec;
    cout << "Recorridos del arbol:\n";
    cout << "1. Inorden (izquierda, raiz, derecha)\n";
    cout << "2. Postorden (izquierda, derecha, raiz)\n";
    cout << "Elija una opcion: ";
    cin >> opcionRec;

    switch (opcionRec) {
        case 1:
            cout << "Recorrido en inorden: ";
            inorden(raiz);
            cout << "\n";
            break;
        case 2:
            cout << "Recorrido en postorden: ";
            postorden(raiz);
            cout << "\n";
            break;
        default:
            cout << "Opcion no valida.\n";
            break;
    }
}

// ===============================
// Altura y número de elementos
// ===============================
int altura(Nodo* raiz) {
    if (raiz == nullptr) return 0;
    int altIzq = altura(raiz->izq);
    int altDer = altura(raiz->der);
    return 1 + (altIzq > altDer ? altIzq : altDer);
}

int contarNodos(Nodo* raiz) {
    if (raiz == nullptr) return 0;
    return 1 + contarNodos(raiz->izq) + contarNodos(raiz->der);
}

// ===============================
// Utilidades
// ===============================
void mostrarMenu() {
    cout << "\n========= MENU ARBOL BINARIO DE BUSQUEDA =========\n";
    cout << "1. Mostrar arbol binario en preorden\n";
    cout << "2. Insertar elemento (de forma ordenada)\n";
    cout << "3. Buscar elemento\n";
    cout << "4. Eliminar elemento\n";
    cout << "5. Recorridos (a) inorden o (b) postorden\n";
    cout << "6. Altura del arbol\n";
    cout << "7. Numero de elementos\n";
    cout << "8. Salir de ejecucion\n";
}

void liberarArbol(Nodo* &raiz) {
    if (raiz == nullptr) return;
    liberarArbol(raiz->izq);
    liberarArbol(raiz->der);
    delete raiz;
    raiz = nullptr;
}

// ==============================
// Programa principal
// ===============================
int main() {
    Nodo* raiz = nullptr;
    int opcion;

    do {
        // Mostrar siempre el contenido actual del árbol en preorden
        cout << "\n----------------------------------------\n";
        cout << "CONTENIDO ACTUAL DEL ARBOL (PREORDEN):\n";
        if (raiz != nullptr) {
            preorden(raiz);
            cout << "\n";
        } else {
            cout << "[Arbol vacio]\n";
        }

        mostrarMenu();
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "\n--- MOSTRAR ARBOL EN PREORDEN ---\n";
                mostrarArbolPreorden(raiz);
                break;
            }
            case 2: {
                cout << "\n--- INSERTAR ELEMENTO ---\n";
                int valor;
                cout << "Ingrese el valor a insertar: ";
                cin >> valor;
                bool insertado = false;
                insertarNodo(raiz, valor, insertado);
                if (insertado) {
                    cout << "Valor " << valor << " insertado con exito.\n";
                } else {
                    cout << "El valor " << valor 
                         << " ya existe en el arbol. No se inserto.\n";
                }
                break;
            }
            case 3: {
                cout << "\n--- BUSCAR ELEMENTO ---\n";
                int valor;
                cout << "Ingrese el valor a buscar: ";
                cin >> valor;
                if (buscarNodo(raiz, valor)) {
                    cout << "El valor " << valor 
                         << " SI se encuentra en el arbol.\n";
                } else {
                    cout << "El valor " << valor 
                         << " NO se encuentra en el arbol.\n";
                }
                break;
            }
            case 4: {
                cout << "\n--- ELIMINAR ELEMENTO ---\n";
                int valor;
                cout << "Ingrese el valor a eliminar: ";
                cin >> valor;
                bool eliminado = eliminarNodo(raiz, valor);
                if (eliminado) {
                    cout << "Valor " << valor 
                         << " eliminado con exito.\n";
                } else {
                    cout << "El valor " << valor 
                         << " no se encontro en el arbol.\n";
                }
                break;
            }
            case 5: {
                cout << "\n--- RECORRIDOS ---\n";
                mostrarRecorridos(raiz);
                break;
            }
            case 6: {
                cout << "\n--- ALTURA DEL ARBOL ---\n";
                int h = altura(raiz);
                cout << "La altura del arbol es: " << h << "\n";
                break;
            }
            case 7: {
                cout << "\n--- NUMERO DE ELEMENTOS ---\n";
                int n = contarNodos(raiz);
                cout << "Numero de elementos en el arbol: " << n << "\n";
                break;
            }
            case 8: {
                cout << "\nSaliendo de la ejecucion del programa...\n";
                break;
            }
            default: {
                cout << "Opcion invalida, intente de nuevo.\n";
                break;
            }
        }

    } while (opcion != 8);

    liberarArbol(raiz); // Liberar memoria antes de terminar
    return 0;
}
