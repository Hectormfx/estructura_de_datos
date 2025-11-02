#include <iostream>   // Biblioteca estándar de C++ que permite usar funciones de entrada y salida como cout y cin
#include <iomanip>    // Biblioteca que permite manipular el formato de salida (por ejemplo setw para alinear texto)
#include <vector>     //Biblioteca para trabar con vectores en lugar del array
#include <random>     // Biblioteca para generar numeros aleatorias
#include <algorithm>  //Biblioteca para usar find por ejemmplo
using namespace std;  // Permite usar cout, cin y endl sin escribir el prefijo std:: antes de cada uno


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
    int posicion = -1;         // Variable para guardar la posición donde se encuentra la clave
    
    // Recorre cada elemento del arreglo
    for (int i = 0; i < arr.size(); i++) {     
        if (arr[i] == clave) {      // Compara el valor actual con la clave buscada
            posicion = i;           // Guarda la posición donde se encontró el valor
            return true;                  // Se encontro
        }
    }

    return false; // No se encontro
    
    // Muestra los resultados de la búsqueda
    cout << "\n--- RESULTADO BUSQUEDA SECUENCIAL ---\n";   // Imprime un encabezado
    if (encontrado) {                                      // Si se encontró la clave
        cout << "Valor encontrado en la posicion: " << posicion << endl; // Muestra la posición encontrada
    } else {                                               // Si no se encontró
        cout << "Valor no encontrado\n";                   // Muestra mensaje de no encontrado
    }
    cout << "-------------------------------------\n\n";   // Línea separadora para estética
}


// Función que realiza la búsqueda binaria

//MODIFICACIONES A LA BUSQUEDA BINARIA

bool busquedaBinaria(const vector<int>& arr, int clave, int &posicion) {   // Función que implementa el algoritmo de búsqueda binaria
    int limiteInferior = 0;        // Primer índice del arreglo (inicio)
    int limiteSuperior = arr.size() - 1;  // Último índice del arreglo (fin)
    int posicion = -1;             // Variable para guardar el índice donde se encontró
    
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


// Función que muestra el menú principal en pantalla

void mostrarMenu() {
    cout << "        MENU \n";                        // Título del menú
    cout << "1. Realizar busqueda secuencial\n";      // Primera opción del menú
    cout << "2. Realizar busqueda binaria\n";         // Segunda opción del menú
    cout << "3. Salir\n";                             // Opción para salir del programa
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
    vector<int> datos(200);
    for (int i = 0; i < 200; i++) {
        datos[i] = universo[i];
    }

    //MOSTRAR EL VECTOR GENERADO ALEATOREAMENTE (200 valores unios entre 0 y 600)

    cout << "VECTOR GENERADO ALEATORIAMENTE (200 valores unicos entre 0 y 600): \n";
    mostrarArray(datos);
    
    
    
    // Se calcula el tamaño del arreglo usando sizeof:
    // sizeof(arr) devuelve el tamaño total del arreglo en bytes
    // sizeof(arr[0]) devuelve el tamaño de un solo elemento
    // Al dividirlos se obtiene el número total de elementos
    int tam = sizeof(arr) / sizeof(arr[0]);
    
    int opcion;  // Variable para guardar la opción seleccionada del menú
    int clave;   // Variable para guardar el número que el usuario quiere buscar
    
    // Ciclo do-while: mantiene el menú activo hasta que el usuario elija salir
    do {
        mostrarArray(arr, tam);    // Llama a la función que muestra el arreglo en pantalla
        mostrarMenu();             // Llama a la función que imprime el menú
        cin >> opcion;             // Lee la opción que el usuario ingresa (usa cin, función de entrada de <iostream>)
        
        // Estructura switch para ejecutar diferentes opciones según la elección del usuario
        switch(opcion) {
            case 1:  // Caso 1: búsqueda secuencial
                cout << "\nIngrese el valor a buscar: ";  // Solicita al usuario la clave
                cin >> clave;                             // Guarda la clave en la variable
                busquedaSecuencial(arr, tam, clave);      // Llama a la función de búsqueda secuencial
                cout << "Presione Enter para continuar...";
                cin.ignore(); // Limpia el búfer de entrada (para eliminar saltos de línea residuales)
                cin.get();    // Espera que el usuario presione Enter (pausa el programa)
                break;
                
            case 2:  // Caso 2: búsqueda binaria
                cout << "\nIngrese el valor a buscar: ";  // Solicita la clave
                cin >> clave;                             // Captura la entrada del usuario
                busquedaBinaria(arr, tam, clave);         // Llama a la función de búsqueda binaria
                cout << "Presione Enter para continuar...";
                cin.ignore(); // Limpia el búfer para evitar errores de lectura
                cin.get();    // Pausa hasta que el usuario presione Enter
                break;
                
            case 3:  // Caso 3: salir del programa
                cout << "\n¡Gracias por usar el programa!\n";  // Mensaje de despedida
                break;
                
            default:  // Si el usuario ingresa una opción inválida
                cout << "\nOpcion invalida. Intente nuevamente.\n";  // Mensaje de error
                cout << "Presione Enter para continuar...";
                cin.ignore(); // Limpia el búfer de entrada
                cin.get();    // Espera Enter antes de continuar
                break;
        }
        
        // system("cls") o system("clear") puede limpiar la pantalla dependiendo del sistema operativo
        // pero están comentadas para evitar errores al compilar en distintos entornos.
        
    } while(opcion != 3);  // El bucle se repite mientras el usuario no elija "3" (salir)
    
    return 0;  // Devuelve 0 al sistema operativo, indicando que el programa terminó correctamente
}