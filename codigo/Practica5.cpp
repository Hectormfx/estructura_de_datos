#include <iostream>   // Incluye la biblioteca estándar para E/S en consola: usamos cout/cin
#include <iomanip>    // Incluye manipuladores de formato como setw, fixed, setprecision
#include <vector>     // Incluye el contenedor std::vector para manejar arreglos dinámicos
#include <random>     // Incluye utilidades de números aleatorios (random_device, mt19937)
#include <algorithm>  // Incluye algoritmos genéricos como std::shuffle
#include <chrono>     // Incluye utilidades para medir tiempo (high_resolution_clock, duration)
using namespace std;               // Evita escribir std:: antes de cout, vector, etc.
using namespace std::chrono;       // Evita std::chrono:: antes de high_resolution_clock, duration

// ===============================
// Función para mostrar el contenido del vector
// ===============================
void mostrarArray(const vector<int>& arr) {            // Recibe el vector por referencia constante (no copia ni modifica)
    cout << "CONTENIDO DEL VECTOR:\n\n";               // Imprime encabezado

    for (int i = 0; i < arr.size(); i++) {             // Recorre todos los elementos del vector
        cout << setw(6) << arr[i];                     // setw(6) (de <iomanip>) alinea el número ocupando 6 espacios
        if ((i + 1) % 10 == 0) cout << "\n";           // Cada 10 elementos, salta de línea (mejora legibilidad)
        else if (i < arr.size() - 1) cout << ", ";     // Si no es el último, imprime coma y espacio
    }
    cout << "\n\n";                                    // Dos saltos de línea al final para separar visualmente
}

// ===============================
// Ordenamiento tipo burbuja (versión optimizada con límite n - i - 1)
// ===============================
void ordenarBurbuja(vector<int>& arr) {                // Recibe el vector por referencia (sí lo modifica)
    int n = arr.size();                                // Guardamos tamaño para no llamar size() en cada iteración
    for (int i = 0; i < n - 1; i++) {                  // i controla las pasadas; tras cada pasada, el mayor queda al final
        for (int j = 0; j < n - i - 1; j++) {          // j recorre hasta el elemento no ordenado más lejano
            if (arr[j] > arr[j + 1]) {                 // Si el elemento actual es mayor que el siguiente, intercambia
                // Intercambio manual (swap clásico sin std::swap)
                int temp = arr[j];                     // Guarda temporalmente arr[j]
                arr[j] = arr[j + 1];                   // Mueve el menor hacia la izquierda
                arr[j + 1] = temp;                     // Completa el intercambio
            }
        }
    }
}

// ===============================
// Quicksort: función auxiliar de partición (esquema Lomuto)
// ===============================
int particion(vector<int>& arr, int bajo, int alto) {  // Particiona el subarreglo [bajo, alto] alrededor de un pivote
    int pivote = arr[alto];                            // Elegimos como pivote el último elemento (estrategia simple)
    int i = bajo - 1;                                  // i marcará la posición del último elemento < pivote

    for (int j = bajo; j < alto; j++) {                // j recorre los elementos excepto el pivote
        if (arr[j] < pivote) {                         // Si el elemento es menor al pivote…
            i++;                                       // Avanza el marcador de elementos "menores"
            // Intercambio arr[i] con arr[j] para colocar el menor en el bloque izquierdo
            int temp = arr[i];                         // Intercambio manual (sin std::swap)
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Coloca el pivote en su posición final (entre los menores y los mayores)
    int temp = arr[i + 1];                             // Intercambia arr[i+1] con el pivote arr[alto]
    arr[i + 1] = arr[alto];
    arr[alto] = temp;

    return i + 1;                                      // Devuelve la posición final del pivote
}

// ===============================
// Quicksort: función recursiva
// ===============================
void quicksortRecursivo(vector<int>& arr, int bajo, int alto) { // Ordena recursivamente el subarreglo [bajo, alto]
    if (bajo < alto) {                                // Caso base: si el subarreglo tiene 0 o 1 elemento, ya está ordenado
        int pi = particion(arr, bajo, alto);          // Obtiene la posición del pivote tras particionar
        quicksortRecursivo(arr, bajo, pi - 1);        // Ordena recursivamente la parte izquierda del pivote
        quicksortRecursivo(arr, pi + 1, alto);        // Ordena recursivamente la parte derecha del pivote
    }
}

// ===============================
// Quicksort: función principal (wrapper)
// ===============================
void ordenarQuicksort(vector<int>& arr) {             // Recibe el vector y llama a la versión recursiva si procede
    if (arr.size() > 0) {                             // Evita llamar con rangos inválidos cuando el vector está vacío
        quicksortRecursivo(arr, 0, arr.size() - 1);   // Ordena el rango completo [0, n-1]
    }
}

// ===============================
// Menú principal
// ===============================
void mostrarMenu() {                                  // Imprime el menú con las opciones pedidas
    cout << "===================================\n";   // Líneas de adorno
    cout << "              MENU\n";
    cout << "===================================\n";
    cout << "1. Generar valores aleatorios\n";        // Opción para crear V_desordenado con 15,000 únicos en [0, 35000]
    cout << "2. Mostrar vector desordenado V_desordenado[]\n"; // Muestra V_desordenado (no se modifica al ordenar)
    cout << "3. Ordenar y mostrar V_ordenado[] con Burbuja + tiempo\n"; // Ordena copia con burbuja y cronometra
    cout << "4. Ordenar y mostrar V_ordenado[] con Quicksort + tiempo\n"; // Ordena copia con quicksort y cronometra
    cout << "5. Salir\n";                              // Termina el programa
    cout << "===================================\n";
    cout << "Seleccione una opcion: ";                 // Prompt de entrada para el usuario
}

// ===============================
// Función principal
// ===============================
int main() {
    vector<int> V_desordenado;                         // Vector fuente desordenado (NO debe modificarse al ordenar)
    vector<int> V_ordenado;                            // Vector destino: aquí se guarda la copia ordenada
    bool datosGenerados = false;                       // Bandera para validar que se generaron datos antes de ordenar

    int opcion;                                        // Variable donde se almacenará la opción de menú elegida

    do {                                               // Bucle principal del menú
        mostrarMenu();                                 // Muestra el menú en cada iteración
        cin >> opcion;                                 // Lee la opción (usa std::cin de <iostream>)
        cout << "\n";                                  // Salto de línea después de leer

        if (opcion == 1) {                             // Opción 1: generar datos únicos
            // Generar 15,000 valores únicos aleatorios entre 0 y 35,000
            cout << "Generando 15,000 valores aleatorios unicos (rango 0-35000)...\n";

            // Crear vector con todos los valores posibles [0, 35000]
            vector<int> universo;                      // Contendrá 35001 elementos únicos
            for (int x = 0; x <= 35000; x++) {         // Recorremos el rango completo (incluye 35000)
                universo.push_back(x);                 // push_back inserta al final del vector
            }

            // Mezclar el vector para aleatorizar el orden de 'universo'
            random_device rd;                          // random_device obtiene entropía del sistema (semilla no determinista)
            mt19937 gen(rd());                         // mt19937 es el motor Mersenne Twister (rápido y de buena calidad)
            // ¿Por qué usar shuffle? std::shuffle (de <algorithm>) reordena aleatoriamente un rango usando un generador
            shuffle(universo.begin(), universo.end(), gen); // Mezclamos todo 'universo' con el motor 'gen'

            // Tomar los primeros 15,000 valores ya mezclados (garantiza unicidad y rango)
            V_desordenado.clear();                     // Aseguramos que esté vacío antes de llenarlo
            V_desordenado.resize(15000);               // Redimensionamos a 15,000 posiciones
            for (int i = 0; i < 15000; i++) {          // Copiamos los 15,000 primeros elementos del universo barajado
                V_desordenado[i] = universo[i];        // Unicidad garantizada por construcción (no hay repeticiones)
            }

            datosGenerados = true;                     // Ya hay datos para ordenar y mostrar
            cout << "Valores generados exitosamente!\n\n"; // Mensaje de éxito
        }
        else if (opcion == 2) {                        // Opción 2: mostrar el vector desordenado
            if (!datosGenerados) {                     // Si no hemos generado datos aún…
                cout << "ERROR: Primero debe generar los valores (opcion 1)\n\n";
            } else {
                cout << "VECTOR DESORDENADO (15,000 valores):\n";
                mostrarArray(V_desordenado);           // Llamada a la función de impresión
                cout << "----------------------------------------\n\n";
            }
        }
        else if (opcion == 3) {                        // Opción 3: ordenar con burbuja (y medir tiempo)
            if (!datosGenerados) {                     // Validación: no se puede ordenar sin datos
                cout << "ERROR: Primero debe generar los valores (opcion 1)\n\n";
            } else {
                // Copiar el vector desordenado al ordenado (requisito: NO modificar V_desordenado)
                V_ordenado = V_desordenado;            // Asignación copia los 15,000 elementos al nuevo vector

                // Medir tiempo SOLO del ordenamiento (no incluye impresión)
                auto inicio = high_resolution_clock::now(); // Marca de tiempo antes (reloj de alta resolución)
                ordenarBurbuja(V_ordenado);                 // Algoritmo de ordenamiento burbuja
                auto fin = high_resolution_clock::now();    // Marca de tiempo después

                // Calcular duración en milisegundos
                // duration<double, milli>(fin - inicio).count() convierte el intervalo a milisegundos tipo double
                auto duracion = duration<double, milli>(fin - inicio).count();

                // Mostrar vector ordenado (puede ser lento imprimir 15,000 valores)
                cout << "VECTOR ORDENADO CON BURBUJA (15,000 valores):\n";
                mostrarArray(V_ordenado);                   // Imprime elementos ordenados

                // Mostrar tiempo con formato 0.000 ms
                cout << "Tiempo de ordenamiento: "
                     << fixed << setprecision(3)           // fixed = notación fija; setprecision(3) = 3 decimales
                     << duracion << " ms.\n";              // Imprime la duración con 3 decimales y sufijo "ms."
                cout << "----------------------------------------\n\n";
            }
        }
        else if (opcion == 4) {                        // Opción 4: ordenar con Quicksort (y medir tiempo)
            if (!datosGenerados) {                     // Validación de datos generados
                cout << "ERROR: Primero debe generar los valores (opcion 1)\n\n";
            } else {
                // Copiar el vector desordenado al ordenado (no tocar V_desordenado)
                V_ordenado = V_desordenado;

                // Medir tiempo SOLO del ordenamiento quicksort
                auto inicio = high_resolution_clock::now(); // Marca antes
                ordenarQuicksort(V_ordenado);               // Quicksort (O(n log n) promedio)
                auto fin = high_resolution_clock::now();    // Marca después

                // Convertir a milisegundos con double
                auto duracion = duration<double, milli>(fin - inicio).count();

                // Mostrar vector ordenado
                cout << "VECTOR ORDENADO CON QUICKSORT (15,000 valores):\n";
                mostrarArray(V_ordenado);

                // Mostrar tiempo en ms con 3 decimales
                cout << "Tiempo de ordenamiento: "
                     << fixed << setprecision(3)
                     << duracion << " ms.\n";
                cout << "----------------------------------------\n\n";
            }
        }
        else if (opcion == 5) {                        // Opción 5: salir del programa
            cout << "Saliendo del programa...\n";      // Mensaje de salida
        }
        else {                                         // Cualquier otra opción es inválida
            cout << "Opcion invalida. Intente nuevamente.\n\n";
        }

    } while (opcion != 5);                             // Repite hasta que el usuario elija 5 (salir)

    return 0;                                          // Retorno exitoso del programa
}
