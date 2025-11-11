#include <iostream> // Librer\'eda para entrada/salida de datos (cin, cout)\
using namespace std; // Espacio de nombres est\'e1ndar para no escribir std:: antes de cout, cin, etc.\

// ==================== VARIABLES GLOBALES ====================\
// Definimos el tama\'f1o m\'e1ximo de la pila como constante para evitar cambios accidentales\
const int TAMANO_MAXIMO = 5; // Capacidad m\'e1xima de la pila (5 elementos)\

// Vector est\'e1tico que almacenar\'e1 los elementos de la pila\
int pila[TAMANO_MAXIMO]; // Array de enteros con 5 posiciones (\'edndices 0 a 4)\

// Variable que indica la posici\'f3n del elemento en la cima de la pila\
// -1 significa que la pila est\'e1 vac\'eda (no hay elementos)\
int cima = -1; // Inicializamos en -1 porque a\'fan no hay elementos\

// ==================== DECLARACI\'d3N DE FUNCIONES ====================\
void mostrarPila(); // Funci\'f3n para mostrar el contenido actual de la pila\
void push(); // Funci\'f3n para insertar un elemento en la cima\
void pop(); // Funci\'f3n para eliminar el elemento de la cima\
void limpiarPila(); // Funci\'f3n para vaciar toda la pila\
void mostrarEstado(); // Funci\'f3n para mostrar el estado actual de la pila\
void mostrarMenu(); // Funci\'f3n para mostrar el men\'fa de opciones\

// ==================== FUNCI\'d3N PRINCIPAL ====================\
int main() \{\
    // Variable para almacenar la opci\'f3n seleccionada por el usuario\
    int opcion; // Tipo entero para las opciones del men\'fa (1-5)\
    \
    // Ciclo infinito que mantiene el programa ejecut\'e1ndose hasta que el usuario elija salir\
    while(true) \{ // true siempre es verdadero, el ciclo se rompe con break en la opci\'f3n 5\
        \
        // Llamada a la funci\'f3n que muestra el men\'fa de opciones\
        mostrarMenu(); // Imprime las 5 opciones disponibles\
        \
        // Solicitar al usuario que ingrese su opci\'f3n\
        cout << "Ingrese su opcion: "; // Mensaje de solicitud de entrada\
        cin >> opcion; // Lee la opci\'f3n ingresada por el usuario y la almacena en la variable opcion\
        \
        // Estructura de control switch para ejecutar la acci\'f3n seg\'fan la opci\'f3n elegida\
        switch(opcion) \{ // Eval\'faa el valor de opcion\
            case 1: // Si el usuario eligi\'f3 1\
                push(); // Llamar a la funci\'f3n para insertar un elemento\
                break; // Salir del switch para no ejecutar los dem\'e1s casos\
                \
            case 2: // Si el usuario eligi\'f3 2\
                pop(); // Llamar a la funci\'f3n para quitar un elemento\
                break; // Salir del switch\
                \
            case 3: // Si el usuario eligi\'f3 3\
                limpiarPila(); // Llamar a la funci\'f3n para limpiar la pila\
                break; // Salir del switch\
                \
            case 4: // Si el usuario eligi\'f3 4\
                mostrarEstado(); // Llamar a la funci\'f3n para mostrar el estado de la pila\
                break; // Salir del switch\
                \
            case 5: // Si el usuario eligi\'f3 5\
                cout << "\\n=== Saliendo del programa... ===" << endl; // Mensaje de despedida\
                return 0; // Terminar la ejecuci\'f3n del programa (salir de main)\
                \
            default: // Si el usuario ingres\'f3 cualquier otro valor\
                cout << "\\n[ERROR] Opcion invalida. Intente nuevamente." << endl; // Mensaje de error\
                // No se usa break aqu\'ed porque despu\'e9s del default el switch termina autom\'e1ticamente\
        \}\
        \
        // Pausa para que el usuario pueda ver los resultados antes de mostrar el men\'fa nuevamente\
        cout << "\\nPresione Enter para continuar..."; // Mensaje para el usuario\
        cin.ignore(); // Limpiar el buffer de entrada (elimina el salto de l\'ednea pendiente del cin anterior)\
        cin.get(); // Esperar a que el usuario presione Enter\
        \
    \} // Fin del while - vuelve a mostrar el men\'fa\
    \
    return 0; // Esta l\'ednea nunca se ejecuta porque salimos con return 0 en el case 5\
\} // Fin de la funci\'f3n main\
\
// ==================== IMPLEMENTACI\'d3N DE FUNCIONES ====================\
\
// Funci\'f3n para mostrar el men\'fa de opciones al usuario\
void mostrarMenu() \{\
    // Usamos \\n para saltos de l\'ednea y endl para limpiar el buffer\
    cout << "\\n========================================" << endl;\
    cout << "        MENU DE OPERACIONES PILA       " << endl;\
    cout << "========================================" << endl;\
    cout << "1. Insertar un elemento (PUSH)" << endl; // Agregar elemento a la cima\
    cout << "2. Quitar un elemento (POP)" << endl; // Eliminar elemento de la cima\
    cout << "3. Limpiar pila" << endl; // Vaciar todos los elementos\
    cout << "4. Mostrar estado de la pila" << endl; // Ver si est\'e1 vac\'eda, llena o con espacio\
    cout << "5. Salir" << endl; // Terminar el programa\
    cout << "========================================" << endl;\
\}\
\
// Funci\'f3n para mostrar el contenido de la pila de forma VERTICAL\
void mostrarPila() \{\
    cout << "\\n--- CONTENIDO DE LA PILA ---" << endl;\
    cout << "Posicion\\tValores" << endl; // \\t es tabulaci\'f3n para alinear columnas\
    \
    // Recorremos la pila desde la posici\'f3n 4 (arriba) hasta la 0 (abajo)\
    // Usamos for con decremento para mostrar de arriba hacia abajo\
    for(int i = TAMANO_MAXIMO - 1; i >= 0; i--) \{ // i inicia en 4 y termina en 0\
        cout << i << "\\t\\t"; // Imprimir el \'edndice de la posici\'f3n\
        \
        // Verificamos si esta posici\'f3n tiene un elemento o est\'e1 vac\'eda\
        if(i <= cima) \{ // Si el \'edndice i es menor o igual a cima, hay un elemento\
            cout << pila[i]; // Mostrar el valor almacenado en esa posici\'f3n\
            if(i == cima) \{ // Si es la posici\'f3n de la cima (el \'faltimo elemento agregado)\
                cout << " <- CIMA"; // Indicar que es la cima\
            \}\
        \} else \{ // Si el \'edndice i es mayor que cima, la posici\'f3n est\'e1 vac\'eda\
            cout << "---"; // Mostrar guiones para indicar que est\'e1 vac\'eda\
        \}\
        cout << endl; // Salto de l\'ednea para la siguiente posici\'f3n\
    \}\
    \
    // Indicar cu\'e1l es el fondo de la pila\
    cout << "\\t\\t   FONDO" << endl;\
    cout << "----------------------------" << endl;\
\}\
\
// Funci\'f3n para insertar (push) un elemento en la cima de la pila\
void push() \{\
    // VALIDACI\'d3N: Verificar si la pila est\'e1 llena (overflow)\
    if(cima == TAMANO_MAXIMO - 1) \{ // Si cima es 4, la pila est\'e1 llena (\'edndices 0-4)\
        cout << "\\n[ERROR] PILA LLENA - No se puede agregar mas elementos (OVERFLOW)" << endl;\
        cout << "Debe quitar elementos antes de agregar nuevos." << endl;\
        return; // Salir de la funci\'f3n sin hacer nada m\'e1s\
    \}\
    \
    // Si llegamos aqu\'ed, hay espacio disponible\
    int valor; // Variable para almacenar el valor que ingresar\'e1 el usuario\
    cout << "\\nIngrese el valor entero a insertar: "; // Solicitar el valor\
    cin >> valor; // Leer el valor ingresado por el usuario\
    \
    // Incrementar la cima para apuntar a la siguiente posici\'f3n disponible\
    cima++; // Si cima era -1, ahora ser\'e1 0; si era 0, ahora ser\'e1 1, etc.\
    \
    // Almacenar el valor en la posici\'f3n de la cima\
    pila[cima] = valor; // Asignar el valor al array en la posici\'f3n cima\
    \
    cout << "\\n[EXITO] Elemento " << valor << " insertado correctamente en la posicion " << cima << endl;\
    \
    // Mostrar la pila despu\'e9s de la operaci\'f3n push\
    mostrarPila(); // Llamar a la funci\'f3n para visualizar la pila actualizada\
\}\
\
// Funci\'f3n para quitar (pop) el elemento de la cima de la pila\
void pop() \{\
    // VALIDACI\'d3N: Verificar si la pila est\'e1 vac\'eda (underflow)\
    if(cima == -1) \{ // Si cima es -1, no hay elementos\
        cout << "\\n[ERROR] PILA VACIA - No se puede eliminar elementos (UNDERFLOW)" << endl;\
        cout << "La pila esta vacia, puede agregar un valor primero." << endl;\
        return; // Salir de la funci\'f3n sin hacer nada m\'e1s\
    \}\
    \
    // Si llegamos aqu\'ed, hay al menos un elemento\
    // Guardar el valor que vamos a eliminar para mostrarlo al usuario\
    int valorEliminado = pila[cima]; // Obtener el valor actual de la cima\
    \
    // Decrementar la cima para "eliminar" el elemento\
    // No es necesario borrar f\'edsicamente el valor del array, solo mover el \'edndice cima\
    cima--; // Si cima era 2, ahora ser\'e1 1; si era 0, ahora ser\'e1 -1 (vac\'eda)\
    \
    cout << "\\n[EXITO] Elemento " << valorEliminado << " eliminado correctamente de la cima" << endl;\
    \
    // Mostrar la pila despu\'e9s de la operaci\'f3n pop\
    mostrarPila(); // Llamar a la funci\'f3n para visualizar la pila actualizada\
\}\
\
// Funci\'f3n para limpiar completamente la pila\
void limpiarPila() \{\
    // VALIDACI\'d3N: Verificar si la pila ya est\'e1 vac\'eda\
    if(cima == -1) \{ // Si cima es -1, no hay elementos para limpiar\
        cout << "\\n[AVISO] La pila ya esta vacia, puede agregar un valor" << endl;\
        return; // Salir de la funci\'f3n sin hacer nada\
    \}\
    \
    // Si llegamos aqu\'ed, hay al menos un elemento\
    // Para limpiar la pila, simplemente reiniciamos cima a -1\
    cima = -1; // Resetear cima a su valor inicial (pila vac\'eda)\
    \
    // No es necesario borrar f\'edsicamente los valores del array\
    // Al poner cima = -1, los valores quedan inaccesibles y se sobrescribir\'e1n al agregar nuevos\
    \
    cout << "\\n[EXITO] Pila limpiada correctamente. Todos los elementos han sido eliminados." << endl;\
    \
    // Mostrar la pila vac\'eda\
    mostrarPila(); // Visualizar que la pila est\'e1 completamente vac\'eda\
\}\
\
// Funci\'f3n para mostrar el estado actual de la pila\
void mostrarEstado() \{\
    cout << "\\n=== ESTADO DE LA PILA ===" << endl;\
    \
    // Verificar el estado seg\'fan el valor de cima\
    if(cima == -1) \{ // Si cima es -1, no hay elementos\
        cout << "Estado: PILA VACIA" << endl;\
        cout << "Descripcion: No hay elementos en la pila. Puede agregar hasta " << TAMANO_MAXIMO << " elementos." << endl;\
    \} \
    else if(cima == TAMANO_MAXIMO - 1) \{ // Si cima es 4 (\'faltima posici\'f3n disponible)\
        cout << "Estado: PILA LLENA YA NO SE PUEDE CAPTURAR\'94 << endl;\
        cout << "Descripcion: La pila ha alcanzado su capacidad maxima (" << TAMANO_MAXIMO << " elementos)." << endl;\
        cout << "Debe eliminar elementos antes de agregar nuevos." << endl;\
    \} \
    else \{ // Si cima est\'e1 entre 0 y 3, hay espacio disponible\
        cout << "Estado: PILA CON ESPACIO" << endl;\
        cout << "Descripcion: La pila tiene " << (cima + 1) << " elemento(s)." << endl;\
        // cima + 1 porque si cima es 0, hay 1 elemento; si cima es 2, hay 3 elementos\
        cout << "Espacios disponibles: " << (TAMANO_MAXIMO - cima - 1) << endl;\
        // Espacios libres = 5 - (cima + 1) = 5 - cima - 1 = 4 - cima\
    \}\
    \
    cout << "=========================" << endl;\
    \
    // Mostrar el contenido actual de la pila\
    mostrarPila(); // Visualizar la pila junto con su estado\
\}\cf3 \
}