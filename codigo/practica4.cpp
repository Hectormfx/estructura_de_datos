#include <iostream>   // Biblioteca estándar de C++ que permite usar funciones de entrada y salida como cout y cin
#include <iomanip>    // Biblioteca que permite manipular el formato de salida (por ejemplo setw para alinear texto)
#include <vector>     //Biblioteca para trabar con vectores en lugar del array
#include <random>     // Biblioteca para generar numeros aleatorias
#include <algorithm>  //Biblioteca para usar find por ejemmplo
#include <chrono>     //Biblioteca para el temporizador
using namespace std;  // Permite usar cout, cin y endl sin escribir el prefijo std:: antes de cada uno
using namespace std::chrono; // Para usar high_resolution_clock sin std::chrono::

// Función para mostrar el contenido del array

//CAMBIO A LA FUNCIÓN mostrarArray: pasamos el vector por referencia constante  (no se copia y no lo modificamos), tambien ya no usamos tam, porque ahora usamos arr.size() esto nos da el tamaño de array

void mostrarArray(const vector<int>& arr) {   // Función que recibe un arreglo y su tamaño como parámetros
    cout << "CONTENIDO DEL ARRAY (VECTOR):\n";     // Imprime un encabezado para identificar el arreglo
    cout << "\n";                         // Imprime una línea vacía para separar visualmente
    
    for (int i = 0; i < arr.size(); i++) {       // Ciclo for para recorrer todos los elementos del arreglo
        cout << setw(3) << arr[i];        // Muestra cada elemento con un ancho fijo de 3 caracteres (setw viene de <iomanip>)
        if (i < arr.size() - 1) cout << ", ";    // Si no es el último elemento, imprime una coma como separador
    }
    cout << "\n\n";                       // Imprime dos saltos de línea para dejar espacio después del arreglo
}


// Función que realiza la búsqueda secuencial

//CAMBIO A LA FUNCIÓN busquedaSecuencial

bool busquedaSecuencial(const vector<int>& arr, int clave, int &posicion) {  // Función que busca un valor dentro del arreglo
    posicion = -1;         // Variable para guardar la posición donde se encuentra la clave
    
    // Recorre cada elemento del arreglo
    for (int i = 0; i < arr.size(); i++) {     
        if (arr[i] == clave) {      // Compara el valor actual con la clave buscada
            posicion = i;           // Guarda la posición donde se encontró el valor
            return true;                  // Se encontro
        }
    }

    return false; // No se encontro
}


// Función que realiza la búsqueda binaria

//MODIFICACIONES A LA BUSQUEDA BINARIA

bool busquedaBinaria(const vector<int>& arr, int clave, int &posicion) {   // Función que implementa el algoritmo de búsqueda binaria
    int limiteInferior = 0;        // Primer índice del arreglo (inicio)
    int limiteSuperior = arr.size() - 1;  // Último índice del arreglo (fin)
    posicion = -1;             // Variable para guardar el índice donde se encontró
    
    //cout << "\n--- PROCESO DE BUSQUEDA BINARIA ---\n";  // Imprime encabezado explicativo
    
    // Mientras los límites sean válidos y no se haya encontrado el elemento
    while (limiteInferior <= limiteSuperior) {
        int mitad = (limiteInferior + limiteSuperior) / 2;   // Calcula la posición media (mitad del rango actual)
        
        if (arr[mitad] == clave) {
            posicion = mitad;
            return true; //encontrado
        }
        else if (clave < arr[mitad]) {
            limiteSuperior = mitad - 1;

        }
        else {
            limiteInferior = mitad + 1;
        }
        
       //LA VERSIÓN CON MENSAJES DE SALIDA LA VAMOS A OMITIR POR LA CUESTION DE VELOCIDAD, PERO LA DEJAREMOS GUARDADA AQUI EN FORMA DE COMENTARIO
       
        // Muestra los valores de los límites y el elemento central
       // cout << "Limite Inferior: " << limiteInferior 
       //      << " | Limite Superior: " << limiteSuperior 
       //      << " | Mitad: " << mitad 
       //      << " | Valor en mitad: " << arr[mitad] << endl;
        
        // Compara la clave buscada con el elemento central
       // if (arr[mitad] == clave) {             // Si el elemento central es igual a la clave
       //     encontrado = true;                 // Marca que se encontró
       //     posicion = mitad;                  // Guarda la posición
       //} else if (clave < arr[mitad]) {       // Si la clave es menor que el valor central
       //     limiteSuperior = mitad - 1;        // Ajusta el límite superior (busca en la mitad izquierda)
       // } else {                               // Si la clave es mayor que el valor central
       //     limiteInferior = mitad + 1;        // Ajusta el límite inferior (busca en la mitad derecha)
       // }
    }
    
    return false; //no encontrado
    // Muestra los resultados finales de la búsqueda
   // cout << "\n--- RESULTADO BUSQUEDA BINARIA ---\n";  // Encabezado de resultado
    //if (encontrado) {                                  // Si se encontró el valor
   //     cout << "Se encontro el valor buscado en la posicion: " << posicion << endl;
   //     cout << "El limite inferior es: " << limiteInferior << endl;
   //     cout << "El limite superior es: " << limiteSuperior << endl;
   // } else {                                           // Si no se encontró
   //     cout << "No se encontro el valor buscado\n";
   //     cout << "Ultimo limite inferior: " << limiteInferior << endl;
   //     cout << "Ultimo limite superior: " << limiteSuperior << endl;
   // }
   //cout << "-----------------------------------\n\n"; // Línea separadora
}

//Ordenamiento tipo burbuja
void bubblesort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                //intercambio manual
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            
        }
        
    }
    
}


// Función que muestra el menú principal en pantalla

void mostrarMenu() {
    cout << "        MENU \n";                        // Título del menú
    cout << "1. Mostrar el vector ordenado\n";      // Primera opción del menú
    cout << "2. Realizar busqueda secuencial (con tiempo)\n";         // Segunda opción del menú
    cout << "3. Realizar busqueda binaria (con tiempo)\n";                             // Tercera opción del menu
    cout << "4. Salir\n";                                   //cuarta opcion del menu
    cout << "\n";                                     // Línea vacía
    cout << "Seleccione una opcion: ";                // Mensaje para solicitar al usuario su elección
}


// Función principal del programa (punto de inicio)

int main() {
    // Crear todos los posibles valores de 0 a 600
    vector<int> universo;
    for (int x = 0; x <= 600; x++) {
        universo.push_back(x);
    }

    //resolver el vector universo con suffle
    random_device rd; //semilla del hardware
    mt19937 gen(rd()); //motor aleatorio mersenne twister
    shuffle(universo.begin(), universo.end(), gen);

    //tomar los primeros 200 datos ya mezclados
    vector<int> datos(200);    //Este es el vector base desordenado
    for (int i = 0; i < 200; i++) {
        datos[i] = universo[i];
    }

    //Hacemos una copia para ordenarla con bubblesort
    vector<int> ordenado = datos; //copiamos el contenido

    //usamos la copia para ordenarlos con bubblesort
    bubblesort(ordenado);

    //MOSTRAR EL VECTOR GENERADO ALEATOREAMENTE (200 valores unios entre 0 y 600)

    cout << "VECTOR GENERADO ALEATORIAMENTE (200 valores unicos entre 0 y 600): \n";
    mostrarArray(datos);
    
    
    
    int opcion;
    
    do {
        mostrarMenu();             // Llama a la función que imprime el menú
        cin >> opcion;             // Lee la opción que el usuario ingresa (usa cin, función de entrada de <iostream>)

        if (opcion == 1) {
            cout << "\nVECTOR ORDENADO (200 valores unicos entre 0 y 600):\n";
            mostrarArray(ordenado);
            cout << "----------------------------------------\n\n";
        }
        else if (opcion == 2) {
            int clave;
            cout << "\nIngrese el valor a buscar (busqueda secuencial): ";
            cin >> clave;

            int posicion;
            // Tomamos tiempo ANTES de buscar
            auto inicio = high_resolution_clock::now();
            bool encontrado = busquedaSecuencial(datos, clave, posicion);
            auto fin = high_resolution_clock::now();
            // Calculamos duración en milisegundos
            auto duracion = duration<double, milli>(fin - inicio).count();

            // Mostramos resultados
            cout << "\n--- RESULTADO BUSQUEDA SECUENCIAL ---\n";
            if (encontrado) {
                cout << "Valor encontrado en la posicion (del vector DESORDENADO): " 
                     << posicion << endl;
            } else {
                cout << "Valor NO encontrado\n";
            }
            cout << "Tiempo: " 
                 << fixed << setprecision(3) 
                 << duracion << " ms.\n";
            cout << "-------------------------------------\n\n";
        }
        else if (opcion == 3) {
            int clave;
            cout << "\nIngrese el valor a buscar (busqueda binaria): ";
            cin >> clave;

            int posicion;
            // Tomamos tiempo ANTES de buscar
            auto inicio = high_resolution_clock::now();
            bool encontrado = busquedaBinaria(ordenado, clave, posicion);
            auto fin = high_resolution_clock::now();
            // Calculamos duración en milisegundos
            auto duracion = duration<double, milli>(fin - inicio).count();

            // Mostramos resultados
            cout << "\n--- RESULTADO BUSQUEDA BINARIA ---\n";
            if (encontrado) {
                cout << "Valor encontrado en la posicion (del vector ORDENADO): " 
                     << posicion << endl;
            } else {
                cout << "Valor NO encontrado\n";
            }
            cout << "Tiempo: " 
                 << fixed << setprecision(3) 
                 << duracion << " ms.\n";
            cout << "-----------------------------------\n\n";
        }
        else if (opcion == 4) {
            cout << "\nSaliendo del programa...\n";
        }
        else {
            cout << "\nOpcion invalida. Intente nuevamente.\n\n";
        }

    } while (opcion != 4);

    return 0;
}