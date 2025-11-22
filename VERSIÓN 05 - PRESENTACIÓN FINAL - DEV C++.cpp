/*============================================================================
LIBRERÍAS INCLUIDAS - HERRAMIENTAS QUE NECESITA EL PROGRAMA
============================================================================*/

#include <iostream> 	// Para entrada/salida (cout, cin)
#include <string>       // Para manejar cadenas de texto (nombres, roles)
#include <queue>        // Para implementar cola (usado en recorrido por niveles)
#include <vector>       // Para almacenar listas dinámicas de resultados de búsqueda
#include <algorithm>    // Para funciones como transform() usado en búsqueda de nombres
#include <cstdlib>      // Para funciones del sistema como system("cls")
#include <limits>       // Para límites numéricos (usado en pausar())
#include <cmath>        // Para funciones matemáticas como log2() en balanceo

using namespace std;


/*============================================================================
ESTRUCTURA DE DATOS - DEFINICIÓN DEL NODO DEL ÁRBOL
============================================================================
Esta es la PIEZA FUNDAMENTAL del árbol genealógico
Cada nodo representa un miembro de la civilización*/

// Estructura del Nodo
struct Nodo {
	// DATOS DEL MIEMBRO (información que se almacena)
    int id; // Identificador único (clave para ordenar en el árbol)
    string nombre;
    int anio;
    char genero;
    string rol; // Rol social (agricultor, guerrero, etc.)
    
    // PUNTEROS - CONEXIONES CON OTROS NODOS DEL ÁRBOL
    Nodo* izq;        // Apunta al hijo IZQUIERDO (IDs menores)
    Nodo* der;        // Apunta al hijo DERECHO (IDs mayores)
    Nodo* padre;      // Apunta al nodo PADRE (para navegar hacia arriba)
    
    // CONSTRUCTOR - Inicializa un nuevo nodo con valores
    
    Nodo(int i, string n, int a, char g, string r) {
        id = i;
        nombre = n;
        anio = a;
        genero = g;
        rol = r;
        izq = NULL;      // Inicia sin hijo izquierdo
        der = NULL;      // Inicia sin hijo derecho
        padre = NULL;    // Inicia sin padre
    }
};



/*============================================================================
VARIABLE GLOBAL - RAÍZ DEL ÁRBOL
============================================================================
Esta es la ENTRADA al árbol, el primer nodo desde donde comienza todo
Si raiz == NULL, el árbol está vacío*/
Nodo* raiz = NULL;



/*============================================================================
PROTOTIPOS DE FUNCIONES - DECLARACIONES ANTICIPADAS
============================================================================
Esto le dice al compilador qué funciones existen antes de definirlas*/

// --- FUNCIONES AUXILIARES DE INTERFAZ ---
void limpiarPantalla();                                    // Limpia la pantalla
void pausar();                                             // Espera ENTER del usuario

// --- OPERACIONES BÁSICAS DEL ÁRBOL ---
void insertar(int id, string nombre, int anio, char genero, string rol); // Agrega un miembro
Nodo* buscar(Nodo* nodo, int id);                         // Busca por ID
bool existeID(Nodo* nodo, int id);                        // Verifica si un ID existe
void mostrarMiembros(Nodo* nodo);                         // Lista todos los miembros
void eliminarNodo(int id);                                // Elimina un miembro

// --- RECORRIDOS DEL ÁRBOL ---
void inorden(Nodo* nodo);                                 // Recorrido: Izq -> Raíz -> Der
void preorden(Nodo* nodo);                                // Recorrido: Raíz -> Izq -> Der
void postorden(Nodo* nodo);                               // Recorrido: Izq -> Der -> Raíz
void porNiveles(Nodo* nodo);                              // Recorrido por generaciones

// --- INFORMACIÓN DEL ÁRBOL ---
int calcularAltura(Nodo* nodo);                           // Altura del árbol
void mostrarHojas(Nodo* nodo);                            // Nodos sin hijos
void mostrarInternos(Nodo* nodo, bool esRaiz);           // Nodos con hijos
int contarNodos(Nodo* nodo);                              // Total de nodos

// --- OPERACIONES AVANZADAS ---
void mostrarCamino(Nodo* nodo, int id);                   // Camino desde raíz a nodo
int calcularNivel(Nodo* nodo, int id, int nivel);        // Nivel de un nodo
int longitudCamino(Nodo* nodo, int id, int nivel);       // Distancia desde raíz

// --- BÚSQUEDAS AVANZADAS ---
void buscarPorAnio(Nodo* nodo, int anio, vector<Nodo*>& resultados);
void buscarPorNombre(Nodo* nodo, string nombre, vector<Nodo*>& resultados);
void buscarPorGenero(Nodo* nodo, char genero, vector<Nodo*>& resultados);
void mostrarResultados(vector<Nodo*>& resultados, string criterio);



/*============================================================================
FUNCIÓN: limpiarPantalla()
PROPÓSITO: Limpia la consola para mejorar la presentación visual
UBICACIÓN: Función auxiliar de interfaz
============================================================================*/
void limpiarPantalla() {
    system("cls");  // Comando de Windows para limpiar pantalla
                    // En Linux/Mac sería system("clear")
}



/*============================================================================
FUNCIÓN: pausar()
PROPÓSITO: Detiene la ejecución hasta que el usuario presione ENTER
UBICACIÓN: Función auxiliar de interfaz
LÓGICA: 
  1. Limpia el buffer de entrada (descarta caracteres residuales)
  2. Espera a que el usuario presione ENTER
============================================================================*/
void pausar() {
    cout << "\nPresione ENTER para continuar...";
    // cin.ignore() descarta caracteres residuales del buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}




/*============================================================================
FUNCIÓN: existeID()
PARÁMETROS:
  - nodo: Nodo actual a verificar (comienza desde raíz)
  - id: ID que queremos verificar
RETORNA: true si existe, false si no existe
LÓGICA DE BÚSQUEDA RECURSIVA:
  1. Si el nodo es NULL (llegamos al final), el ID NO existe ? return false
  2. Si el ID del nodo actual coincide -> return true
  3. Si no, buscar recursivamente en subárbol IZQUIERDO O DERECHO
============================================================================*/
bool existeID(Nodo* nodo, int id) {
    if (nodo == NULL) return false; // Caso base: fin del árbol
    if (nodo->id == id) return true; // Encontrado
    // Busca en AMBOS subárboles (OR lógico)
    return existeID(nodo->izq, id) || existeID(nodo->der, id);
}



/* ============================================================================
FUNCIÓN: insertar()
PARÁMETROS: Todos los datos del miembro a insertar

LÓGICA DE INSERCIÓN EN ÁRBOL BINARIO DE BÚSQUEDA (BST):
Un BST mantiene la propiedad: 
  - Todos los nodos del subárbol IZQUIERDO tienen IDs MENORES
  - Todos los nodos del subárbol DERECHO tienen IDs MAYORES

PROCESO DE INSERCIÓN:
1. Crear nuevo nodo con los datos proporcionados
2. Si el árbol está vacío (raiz == NULL):
   -> El nuevo nodo se convierte en la raíz
3. Si el árbol tiene nodos:
   -> Buscar la posición correcta:
     a) Empezar desde la raíz
     b) Si ID < nodo actual -> ir a la IZQUIERDA
     c) Si ID >= nodo actual -> ir a la DERECHA
     d) Repetir hasta encontrar un espacio vacío (NULL)
   -> Insertar el nuevo nodo en ese espacio
   -> Actualizar el puntero 'padre' del nuevo nodo
============================================================================*/
void insertar(int id, string nombre, int anio, char genero, string rol) {
	// PASO 1: Crear el nuevo nodo con los datos
    Nodo* nuevo = new Nodo(id, nombre, anio, genero, rol);
    
    // PASO 2: Verificar si el árbol está vacío
    if (raiz == NULL) {
        raiz = nuevo;
        cout << "\n Miembro insertado como raiz del arbol\n";
    } else {
        // PASO 3: Buscar la posición correcta para insertar
        Nodo* actual = raiz;     // Comienza desde la raíz
        Nodo* padre = NULL;      // Guardará el padre del nuevo nodo
        
        // BUCLE: Navegar por el árbol hasta encontrar espacio vacío
        while (actual != NULL) {
            padre = actual;      // Guardar el nodo actual como padre potencial
            
            // DECISIÓN: ¿Ir a la izquierda o derecha?
            if (id < actual->id) {
                actual = actual->izq;  // ID menor -> ir IZQUIERDA
            } else {
                actual = actual->der;  // ID mayor -> ir DERECHA
            }
        }
        // Al salir del bucle: actual == NULL (encontramos el lugar)
        
        // PASO 4: Conectar el nuevo nodo con su padre
        nuevo->padre = padre;
        
        // Determinar si va como hijo izquierdo o derecho
        if (id < padre->id) {
            padre->izq = nuevo;  // Insertar a la IZQUIERDA
        } else {
            padre->der = nuevo;  // Insertar a la DERECHA
        }
        
        cout << "\n Miembro insertado correctamente\n";
    }
}

/*============================================================================
FUNCIÓN: buscar()
PROPÓSITO: Busca un nodo por su ID en el árbol
UBICACIÓN: Operación básica de búsqueda
PARÁMETROS:
  - nodo: Nodo actual (comienza desde raíz)
  - id: ID a buscar
RETORNA: Puntero al nodo encontrado, o NULL si no existe

LÓGICA DE BÚSQUEDA EN BST (Binaria eficiente):
La búsqueda aprovecha la propiedad del BST para ser MÁS RÁPIDA que una
búsqueda lineal. En cada paso descarta la mitad del árbol.

PROCESO:
1. Si el nodo es NULL -> no encontrado -> return NULL
2. Si el ID coincide -> encontrado -> return nodo
3. Si ID buscado < ID actual -> buscar en subárbol IZQUIERDO (recursión)
4. Si ID buscado > ID actual -> buscar en subárbol DERECHO (recursión)
============================================================================*/
Nodo* buscar(Nodo* nodo, int id) {
    // CASO BASE 1: Nodo vacío (no encontrado)
    // CASO BASE 2: ID encontrado
    if (nodo == NULL || nodo->id == id) {
        return nodo;
    }
    
    // CASO RECURSIVO: Decidir hacia dónde buscar
    if (id < nodo->id) {
        return buscar(nodo->izq, id);  // Buscar en IZQUIERDA
    }
    return buscar(nodo->der, id);      // Buscar en DERECHA
}

/* Función para mostrar todos los miembros
PROPÓSITO: Muestra todos los miembros del árbol en orden ascendente por ID
LÓGICA: Usa recorrido INORDEN*/
void mostrarMiembros(Nodo* nodo) {
    if (nodo != NULL) {
        mostrarMiembros(nodo->izq);                          // Procesar IZQUIERDA
        cout << "ID: " << nodo->id << " - " << nodo->nombre << endl;  // Procesar RAÍZ
        mostrarMiembros(nodo->der);                          // Procesar DERECHA
    }
}

/*============================================================================
FUNCIÓN: encontrarMinimo()
PROPÓSITO: Encuentra el nodo con el ID MÁS PEQUEÑO en un subárbol
UBICACIÓN: Función auxiliar para eliminación
USO: Necesaria para eliminar nodos con DOS hijos
LÓGICA: En un BST, el mínimo siempre está en el EXTREMO IZQUIERDO
============================================================================*/
Nodo* encontrarMinimo(Nodo* nodo) {
    // Ir siempre a la IZQUIERDA hasta que no haya más nodos
    while (nodo->izq != NULL) {
        nodo = nodo->izq;
    }
    return nodo;  // Este es el nodo con ID mínimo
}



/*============================================================================
FUNCIÓN: eliminarNodoAux()
PROPÓSITO: Función auxiliar recursiva para eliminar un nodo del árbol
UBICACIÓN: Operación compleja del árbol
PARÁMETROS:
  - nodo: Nodo actual en la recursión
  - id: ID del nodo a eliminar
  - eliminado: Bandera para saber si se eliminó exitosamente
RETORNA: Nuevo subárbol después de la eliminación

LÓGICA DE ELIMINACIÓN EN BST (3 CASOS POSIBLES):
============================================================================
CASO 1: NODO HOJA (sin hijos)
   Simplemente eliminar el nodo
   Retornar NULL

CASO 2: NODO CON UN HIJO (izquierdo O derecho)
   Eliminar el nodo
   Conectar su hijo directamente con su padre
   Retornar el hijo

CASO 3: NODO CON DOS HIJOS (más complejo)
   NO se puede simplemente eliminar
   ESTRATEGIA: Reemplazar con el SUCESOR INORDEN
   El sucesor es el nodo más pequeño del subárbol DERECHO
   Copiar datos del sucesor al nodo actual
   Eliminar el sucesor (que tendrá 0 o 1 hijo)
============================================================================*/
Nodo* eliminarNodoAux(Nodo* nodo, int id, bool& eliminado) {
    // CASO BASE: Nodo no encontrado
    if (nodo == NULL) return NULL;
    
    // PASO 1: Buscar el nodo a eliminar
    if (id < nodo->id) {
        // Buscar en subárbol IZQUIERDO
        nodo->izq = eliminarNodoAux(nodo->izq, id, eliminado);
        if (nodo->izq != NULL) nodo->izq->padre = nodo;  // Actualizar padre
    } else if (id > nodo->id) {
        // Buscar en subárbol DERECHO
        nodo->der = eliminarNodoAux(nodo->der, id, eliminado);
        if (nodo->der != NULL) nodo->der->padre = nodo;  // Actualizar padre
    } else {
        // NODO ENCONTRADO - Proceder a eliminar
        eliminado = true;
        
        // CASO 1: NODO HOJA (sin hijos)
        if (nodo->izq == NULL && nodo->der == NULL) {
            delete nodo;
            return NULL;
        } 
        // CASO 2A: Solo tiene hijo DERECHO
        else if (nodo->izq == NULL) {
            Nodo* temp = nodo->der;
            delete nodo;
            return temp;
        } 
        // CASO 2B: Solo tiene hijo IZQUIERDO
        else if (nodo->der == NULL) {
            Nodo* temp = nodo->izq;
            delete nodo;
            return temp;
        } 
        // CASO 3: TIENE DOS HIJOS
        else {
            // Encontrar el SUCESOR (mínimo del subárbol derecho)
            Nodo* sucesor = encontrarMinimo(nodo->der);
            
            // COPIAR los datos del sucesor al nodo actual
            nodo->id = sucesor->id;
            nodo->nombre = sucesor->nombre;
            nodo->anio = sucesor->anio;
            nodo->genero = sucesor->genero;
            nodo->rol = sucesor->rol;
            
            // ELIMINAR el sucesor del subárbol derecho
            nodo->der = eliminarNodoAux(nodo->der, sucesor->id, eliminado);
            if (nodo->der != NULL) nodo->der->padre = nodo;
        }
    }
    return nodo;
}



/*============================================================================
FUNCIÓN: eliminarNodo()
PROPÓSITO: Interfaz pública para eliminar un nodo por ID
UBICACIÓN: Operación pública del árbol
LÓGICA: Llama a eliminarNodoAux() que hace el trabajo real
============================================================================*/
void eliminarNodo(int id) {
    bool eliminado = false;
    raiz = eliminarNodoAux(raiz, id, eliminado);
    
    if (eliminado) {
        cout << "\n Miembro eliminado correctamente\n";
    } else {
        cout << "\n Miembro no encontrado\n";
    }
}



/* Recorrido Inorden
Es una forma de visitar TODOS los nodos del árbol en un orden específico:
  ORDEN: Izquierda -> Raíz -> Derecha
CARACTERÍSTICAS:
  - En un BST, el recorrido INORDEN visita los nodos en ORDEN ASCENDENTE
  - Es útil para listar elementos ordenados*/
void inorden(Nodo* nodo) {
    if (nodo != NULL) {
        inorden(nodo->izq);          // PASO 1: Procesar IZQUIERDA
        cout << nodo->id << " ";     // PASO 2: Procesar RAÍZ
        inorden(nodo->der);          // PASO 3: Procesar DERECHA
    }
}



/*Recorrido Preorden
Forma de visitar nodos donde procesamos el nodo ANTES de sus hijos:
  ORDEN: Raíz -> Izquierda -> Derecha

CARACTERÍSTICAS:
  - Útil para COPIAR árboles
  - Útil para obtener EXPRESIONES PREFIJAS
  - Muestra la jerarquía desde arriba*/
void preorden(Nodo* nodo) {
    if (nodo != NULL) {
        cout << nodo->id << " ";     // PASO 1: Procesar RAÍZ primero
        preorden(nodo->izq);         // PASO 2: Procesar IZQUIERDA
        preorden(nodo->der);         // PASO 3: Procesar DERECHA
    }
}



/*Recorrido Postorden
Forma de visitar nodos donde procesamos el nodo DESPUÉS de sus hijos:
  ORDEN: Izquierda -> Derecha -> Raíz

CARACTERÍSTICAS:
  - Útil para ELIMINAR árboles (eliminas hijos antes que padres)
  - Útil para EVALUAR expresiones postfijas
  - Procesa las hojas primero*/
void postorden(Nodo* nodo) {
    if (nodo != NULL) {
        postorden(nodo->izq);        // PASO 1: Procesar IZQUIERDA
        postorden(nodo->der);        // PASO 2: Procesar DERECHA
        cout << nodo->id << " ";     // PASO 3: Procesar RAÍZ al final
    }
}



/*Recorrido por Niveles
También llamado "recorrido en anchura", visita los nodos nivel por nivel:
  - Primero la raíz (nivel 0)
  - Luego todos los nodos del nivel 1
  - Luego todos los nodos del nivel 2
  - Y así sucesivamente

CARACTERÍSTICAS:
  - NO usa recursión, usa una COLA (queue)
  - Útil para buscar nodos por cercanía a la raíz
  - Representa "generaciones" en un árbol genealógico*/
void porNiveles(Nodo* nodo) {
    if (nodo == NULL) return;
    
    // Crear una COLA para almacenar nodos por procesar
    queue<Nodo*> cola;
    cola.push(nodo);  // Empezar con la raíz
    
    // BUCLE: Mientras haya nodos en la cola
    while (!cola.empty()) {
        // PASO 1: Sacar el primer nodo de la cola
        Nodo* actual = cola.front();
        cola.pop();
        
        // PASO 2: Procesar el nodo actual
        cout << actual->id << " ";
        
        // PASO 3: Agregar hijos a la cola (si existen)
        if (actual->izq != NULL) cola.push(actual->izq);
        if (actual->der != NULL) cola.push(actual->der);
    }
    // Al terminar, habremos visitado todos los nodos nivel por nivel
} 



/*============================================================================
FUNCIÓN: calcularAltura()
PROPÓSITO: Calcula la ALTURA de un árbol o subárbol
UBICACIÓN: Información del árbol
 
¿QUÉ ES LA ALTURA?
============================================================================
La altura es la DISTANCIA MÁXIMA desde un nodo hasta una hoja
(el camino más largo hacia abajo)

DEFINICIONES:
  - Altura de NULL = -1 (por convención)
  - Altura de una hoja = 0
  - Altura de un nodo = 1 + max(altura_izq, altura_der)

EJEMPLO:
       50       <- altura = 2
      /  \
     30  70     <- altura = 1
    /
   20           <- altura = 0 (es hoja)

PROCESO RECURSIVO:
1. Si nodo es NULL -> retornar -1
2. Calcular altura del subárbol IZQUIERDO (recursión)
3. Calcular altura del subárbol DERECHO (recursión)
4. La altura del nodo = 1 + máximo de ambas alturas
============================================================================*/
int calcularAltura(Nodo* nodo) {
    if (nodo == NULL) return -1;  // Caso base
    
    // Calcular alturas de subárboles
    int alturaIzq = calcularAltura(nodo->izq);
    int alturaDer = calcularAltura(nodo->der);
    
    // Altura = 1 + la mayor de las dos alturas
    return 1 + max(alturaIzq, alturaDer);
}



/*============================================================================
FUNCIÓN: mostrarHojas()
PROPÓSITO: Muestra todos los nodos HOJA del árbol
UBICACIÓN: Información del árbol
 
¿QUÉ ES UN NODO HOJA?
============================================================================
Un nodo HOJA es un nodo que NO tiene hijos (ni izquierdo ni derecho)
Son los nodos en los "extremos" del árbol

CONDICIÓN: nodo->izq == NULL && nodo->der == NULL

EJEMPLO:
       50
      /  \
     30  70
    /    / \
   20   60 80

HOJAS: 20, 60, 80 (no tienen hijos)
============================================================================*/
void mostrarHojas(Nodo* nodo) {
    if (nodo != NULL) {
        // Si es hoja, imprimirla
        if (nodo->izq == NULL && nodo->der == NULL) {
            cout << nodo->id << " ";
        }
        // Continuar búsqueda en subárboles
        mostrarHojas(nodo->izq);
        mostrarHojas(nodo->der);
    }
}



/*============================================================================
FUNCIÓN: mostrarInternos()
PROPÓSITO: Muestra todos los nodos INTERNOS (excepto la raíz)
UBICACIÓN: Información del árbol
PARÁMETROS:
  - nodo: Nodo actual
  - esRaiz: Flag para identificar la raíz

¿QUÉ ES UN NODO INTERNO?
============================================================================
Un nodo INTERNO es un nodo que SÍ tiene al menos un hijo
Esta función excluye la raíz de los resultados

CONDICIÓN: (nodo->izq != NULL || nodo->der != NULL) && !esRaiz
 
EJEMPLO:
       50      <- Raíz (no se muestra)
      /  \
     30  70    <- Internos (tienen hijos)
    /    / \
   20   60 80  <- Hojas (no se muestran)

INTERNOS (sin raíz): 30, 70
===========================================================================*/
void mostrarInternos(Nodo* nodo, bool esRaiz) {
    if (nodo != NULL) {
        // Si NO es raíz Y tiene al menos un hijo ? es nodo interno
        if (!esRaiz && (nodo->izq != NULL || nodo->der != NULL)) {
            cout << nodo->id << " ";
        }
        // Continuar recursión (ahora ya no es raíz)
        mostrarInternos(nodo->izq, false);
        mostrarInternos(nodo->der, false);
    }
}



/*============================================================================
FUNCIÓN: contarNodos()
PROPÓSITO: Cuenta el TOTAL de nodos en el árbol (peso del árbol)
UBICACIÓN: Información del árbol

LÓGICA RECURSIVA:
============================================================================
Para contar nodos:
  - Si el nodo es NULL ? hay 0 nodos
  - Si el nodo existe ? hay 1 nodo (el actual) + 
                        nodos del subárbol izquierdo +
                        nodos del subárbol derecho

EJEMPLO:
       50          Total = 7 nodos
      /  \
     30  70       = 1 (raíz) + 3 (izq) + 3 (der)
    /    / \
   20   60 80
============================================================================*/
int contarNodos(Nodo* nodo) {
    if (nodo == NULL) return 0;  // Caso base
    
    // 1 nodo actual + nodos izquierda + nodos derecha
    return 1 + contarNodos(nodo->izq) + contarNodos(nodo->der);
}

// Mostrar camino desde raíz a nodo
void mostrarCamino(Nodo* nodo, int id) {
    // PASO 1: Buscar el nodo destino
    Nodo* destino = buscar(nodo, id);
    if (destino == NULL) {
        cout << " Nodo no encontrado\n";
        return;
    }
    
    // PASO 2: Construir el camino usando punteros 'padre'
    vector<int> camino;  // Vector para almacenar IDs del camino
    Nodo* actual = destino;
    
    // RETROCEDER desde destino hasta raíz
    while (actual != NULL) {
        camino.push_back(actual->id);  // Guardar ID
        actual = actual->padre;         // Subir al padre
    }
    
    // PASO 3: Mostrar el camino (invertido, de raíz a destino)
    cout << "Camino desde raiz hasta " << id << ":\n";
    for (int i = camino.size() - 1; i >= 0; i--) {
        cout << camino[i];
        if (i > 0) cout << " -> ";  // Flechas entre nodos
    }
    cout << endl;
}



/*FUNCIÓN: calcularNivel()
PARÁMETROS:
  - nodo: Nodo actual en la búsqueda
  - id: ID del nodo cuyo nivel queremos calcular
  - nivel: Nivel actual (0 para la raíz)
RETORNA: El nivel del nodo, o -1 si no existe

¿QUÉ ES EL NIVEL?
============================================================================
El NIVEL de un nodo es su DISTANCIA desde la RAÍZ
- Raíz está en nivel 0
- Hijos de la raíz están en nivel 1
- Nietos de la raíz están en nivel 2
- etc.*/
int calcularNivel(Nodo* nodo, int id, int nivel) {
    if (nodo == NULL) return -1;          // Caso base: no encontrado
    if (nodo->id == id) return nivel;     // Caso base: encontrado
    
    // Buscar en subárbol IZQUIERDO
    int nivelIzq = calcularNivel(nodo->izq, id, nivel + 1);
    if (nivelIzq != -1) return nivelIzq;  // Si se encontró, retornar
    
    // Si no se encontró en izquierda, buscar en DERECHA
    return calcularNivel(nodo->der, id, nivel + 1);
}



/*============================================================================
FUNCIÓN: longitudCamino()
LONGITUD = Número de ARISTAS (conexiones) desde raíz
Esta función es IDÉNTICA a calcularNivel() en su implementación*/
int longitudCamino(Nodo* nodo, int id, int nivel) {
    if (nodo == NULL) return -1;
    if (nodo->id == id) return nivel;
    
    int longitudIzq = longitudCamino(nodo->izq, id, nivel + 1);
    if (longitudIzq != -1) return longitudIzq;
    
    return longitudCamino(nodo->der, id, nivel + 1);
}



/*============================================================================
FUNCIÓN: buscarPorAnio()
PROPÓSITO: Busca TODOS los miembros nacidos en un año específico
UBICACIÓN: Búsquedas avanzadas
PARÁMETROS:
  - nodo: Nodo actual en el recorrido
  - anio: Año de nacimiento a buscar
  - resultados: Vector (por referencia) donde se almacenan los resultados

LÓGICA DE BÚSQUEDA POR CRITERIO:
============================================================================
A diferencia de buscar por ID (que usa las propiedades del BST para ser
eficiente), buscar por OTROS CAMPOS requiere revisar TODOS los nodos.
 
ESTRATEGIA:
1. Hacer un recorrido INORDEN (izquierda-raíz-derecha)
2. En cada nodo, verificar si el año coincide
3. Si coincide, agregar el nodo al vector de resultados
4. Continuar el recorrido completo
 
COMPLEJIDAD: O(n) - debe revisar todos los nodos
 
NOTA: Se usa un VECTOR (paso por referencia con &) para acumular
múltiples resultados a través de la recursión
============================================================================*/
void buscarPorAnio(Nodo* nodo, int anio, vector<Nodo*>& resultados) {
    if (nodo != NULL) {
        buscarPorAnio(nodo->izq, anio, resultados);  // IZQUIERDA
        
        // VERIFICAR si el año coincide
        if (nodo->anio == anio) {
            resultados.push_back(nodo);  // Agregar a resultados
        }
        
        buscarPorAnio(nodo->der, anio, resultados);  // DERECHA
    }
}



/*============================================================================
FUNCIÓN: buscarPorNombre()
PROPÓSITO: Busca miembros por nombre (búsqueda PARCIAL y case-insensitive)
UBICACIÓN: Búsquedas avanzadas
PARÁMETROS:
  - nodo: Nodo actual en el recorrido
  - nombre: Texto a buscar (puede ser parcial)
  - resultados: Vector donde se almacenan coincidencias
 
CARACTERÍSTICAS ESPECIALES:
============================================================================
Esta búsqueda es MÁS FLEXIBLE que una búsqueda exacta:
 
1. BÚSQUEDA PARCIAL:
   - Si buscas "Juan", encontrará "Juan Pérez", "María Juan", etc.
   - Usa find() para ver si el texto está CONTENIDO en el nombre
 
2. CASE-INSENSITIVE (no distingue mayúsculas/minúsculas):
   - Convierte ambos strings a minúsculas antes de comparar
   - "PEDRO", "Pedro" y "pedro" se consideran iguales

PROCESO:
1. Recorrer todos los nodos (INORDEN)
2. Para cada nodo:
   a) Convertir el nombre del nodo a minúsculas
   b) Convertir el texto buscado a minúsculas
   c) Verificar si el texto está contenido en el nombre (find())
   d) Si coincide, agregar a resultados
 
EJEMPLO:
Árbol con nombres: "Ana López", "JUAN PEREZ", "María Juan"
Búsqueda: "juan"
Resultados: "JUAN PEREZ" y "María Juan" (ambos contienen "juan")
============================================================================*/
void buscarPorNombre(Nodo* nodo, string nombre, vector<Nodo*>& resultados) {
    if (nodo != NULL) {
        buscarPorNombre(nodo->izq, nombre, resultados);  // IZQUIERDA
        
        // CONVERTIR a minúsculas para comparación case-insensitive
        string nombreNodo = nodo->nombre;
        string nombreBusqueda = nombre;
        
        // transform() convierte cada carácter a minúscula
        transform(nombreNodo.begin(), nombreNodo.end(), nombreNodo.begin(), ::tolower);
        transform(nombreBusqueda.begin(), nombreBusqueda.end(), nombreBusqueda.begin(), ::tolower);
        
        // BUSCAR si el nombre ingresado está CONTENIDO en el nombre del nodo
        // find() retorna string::npos si NO se encuentra
        if (nombreNodo.find(nombreBusqueda) != string::npos) {
            resultados.push_back(nodo);  // Coincidencia encontrada
        }
        
        buscarPorNombre(nodo->der, nombre, resultados);  // DERECHA
    }
}

/*============================================================================
FUNCIÓN: buscarPorGenero()
PROPÓSITO: Busca todos los miembros de un género específico (M o F)
UBICACIÓN: Búsquedas avanzadas
 
LÓGICA:
============================================================================
Similar a buscarPorAnio(), pero comparando el campo 'genero'
Recorre todo el árbol y acumula nodos donde genero == genero_buscado
============================================================================*/
void buscarPorGenero(Nodo* nodo, char genero, vector<Nodo*>& resultados) {
    if (nodo != NULL) {
        buscarPorGenero(nodo->izq, genero, resultados);  // IZQUIERDA
        
        if (nodo->genero == genero) {
            resultados.push_back(nodo);
        }
        
        buscarPorGenero(nodo->der, genero, resultados);  // DERECHA
    }
}



// Mostrar resultados de búsqueda
void mostrarResultados(vector<Nodo*>& resultados, string criterio) {
    if (resultados.empty()) {
        cout << "\n No se encontraron miembros con esa coincidencia\n";
    } else {
        cout << "\n Se encontraron " << resultados.size() << " miembro(s) con ese criterio\n";
        cout << "============================================================\n";
        for (size_t i = 0; i < resultados.size(); i++) {
            cout << "\nMiembro #" << (i + 1) << ":\n";
            cout << "  ID: " << resultados[i]->id << endl;
            cout << "  Nombre: " << resultados[i]->nombre << endl;
            cout << "  Anio: " << resultados[i]->anio << endl;
            cout << "  Genero: " << resultados[i]->genero << endl;
            cout << "  Rol: " << resultados[i]->rol << endl;
        }
        cout << "============================================================\n";
    }
}

// MENÚ PRINCIPAL
int main() {
    int opcion, subopcion;
    
    do {
        limpiarPantalla();
        cout << "==========================================\n";
        cout << "  ARBOL GENEALOGICO - CIVILIZACION\n";
        cout << "==========================================\n";
        cout << "1. Gestion de Miembros\n";
        cout << "2. Recorridos del arbol\n";
        cout << "3. Informacion del arbol\n";
        cout << "4. Operaciones Avanzadas\n";
        cout << "5. Salir\n";
        cout << "==========================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: { // GESTIÓN DE MIEMBROS
                do {
                    limpiarPantalla();
                    cout << "========== GESTION DE MIEMBROS ==========\n";
                    cout << "1. Insertar nuevo miembro\n";
                    cout << "2. Buscar miembro\n";
                    cout << "3. Eliminar miembro\n";
                    cout << "4. Volver al menu principal\n";
                    cout << "==========================================\n";
                    cout << "Seleccione una opcion: ";
                    cin >> subopcion;
                    
                    switch (subopcion) {
                        case 1: { // INSERTAR
                            cout << "\n--- INSERTAR NUEVO MIEMBRO ---\n";
                            int id, anio;
                            string nombre, rol;
                            char genero;
                            
                            // Validar ID
                            do {
                                cout << "Ingrese ID del miembro: ";
                                cin >> id;
                                if (id <= 0) {
                                    cout << "ERROR: El ID debe ser mayor a 0\n";
                                } else if (existeID(raiz, id)) {
                                    cout << "ERROR: El ID ya existe en el arbol\n";
                                    id = 0;
                                }
                            } while (id <= 0);
                            
                            cin.ignore();
                            
                            // Validar nombre
                            do {
                                cout << "Ingrese nombre completo: ";
                                getline(cin, nombre);
                                if (nombre.empty()) {
                                    cout << "ERROR: El nombre no puede estar vacio\n";
                                }
                            } while (nombre.empty());
                            
                            // Validar año
                            do {
                                cout << "Ingrese anio de nacimiento: ";
                                cin >> anio;
                                if (anio <= 0) {
                                    cout << "ERROR: El anio debe ser mayor a 0\n";
                                }
                            } while (anio <= 0);
                            
                            // Validar género
                            do {
                                cout << "Ingrese genero (M/F): ";
                                cin >> genero;
                                genero = toupper(genero);
                                if (genero != 'M' && genero != 'F') {
                                    cout << "ERROR: El genero debe ser M o F\n";
                                }
                            } while (genero != 'M' && genero != 'F');
                            
                            cin.ignore();
                            
                            // Validar rol
                            do {
                                cout << "Ingrese rol social: ";
                                getline(cin, rol);
                                if (rol.empty()) {
                                    cout << "ERROR: El rol no puede estar vacio\n";
                                }
                            } while (rol.empty());
                            
                            insertar(id, nombre, anio, genero, rol);
                            pausar();
                            break;
                        }
                        
                        case 2: { // BUSCAR
						    int opcionBusqueda;
						    do {
						        limpiarPantalla();
						        cout << "========== BUSCAR MIEMBRO ==========\n";
						        cout << "1. Buscar por ID\n";
						        cout << "2. Buscar por Anio de Nacimiento\n";
						        cout << "3. Buscar por Nombre\n";
						        cout << "4. Buscar por Genero\n";
						        cout << "5. Volver al menu anterior\n";
						        cout << "====================================\n";
						        cout << "Seleccione una opcion: ";
						        cin >> opcionBusqueda;
						        
						        switch (opcionBusqueda) {
						            case 1: { // Búsqueda por ID (original)
						                cout << "\n--- BUSCAR POR ID ---\n";
						                if (raiz == NULL) {
						                    cout << "El arbol esta vacio\n";
						                } else {
						                    cout << "Miembros registrados:\n";
						                    cout << "------------------------------------\n";
						                    mostrarMiembros(raiz);
						                    cout << "------------------------------------\n\n";
						                    
						                    int id;
						                    cout << "Ingrese ID del miembro a buscar: ";
						                    cin >> id;
						                    
						                    Nodo* encontrado = buscar(raiz, id);
						                    if (encontrado != NULL) {
						                        cout << "\n Miembro encontrado:\n";
						                        cout << "  ID: " << encontrado->id << endl;
						                        cout << "  Nombre: " << encontrado->nombre << endl;
						                        cout << "  Anio: " << encontrado->anio << endl;
						                        cout << "  Genero: " << encontrado->genero << endl;
						                        cout << "  Rol: " << encontrado->rol << endl;
						                    } else {
						                        cout << "\n Miembro no encontrado\n";
						                    }
						                }
						                pausar();
						                break;
						            }
						            
						            case 2: { // Búsqueda por Año
						                cout << "\n--- BUSCAR POR AÑO DE NACIMIENTO ---\n";
						                if (raiz == NULL) {
						                    cout << "El arbol esta vacio\n";
						                } else {
						                    int anio;
						                    cout << "Ingrese el anio de nacimiento: ";
						                    cin >> anio;
						                    
						                    vector<Nodo*> resultados;
						                    buscarPorAnio(raiz, anio, resultados);
						                    mostrarResultados(resultados, "el año " + anio);
						                }
						                pausar();
						                break;
						            }
						            
						            case 3: { // Búsqueda por Nombre
						                cout << "\n--- BUSCAR POR NOMBRE ---\n";
						                if (raiz == NULL) {
						                    cout << "El arbol esta vacio\n";
						                } else {
						                    string nombre;
						                    cin.ignore();
						                    cout << "Ingrese el nombre (o parte del nombre) a buscar: ";
						                    getline(cin, nombre);
						                    
						                    vector<Nodo*> resultados;
						                    buscarPorNombre(raiz, nombre, resultados);
						                    mostrarResultados(resultados, "el nombre '" + nombre + "'");
						                }
						                pausar();
						                break;
						            }
						            
						            case 4: { // Búsqueda por Género
						                cout << "\n--- BUSCAR POR GENERO ---\n";
						                if (raiz == NULL) {
						                    cout << "El arbol esta vacio\n";
						                } else {
						                    char genero;
						                    cout << "Ingrese el genero (M/F): ";
						                    cin >> genero;
						                    genero = toupper(genero);
						                    
						                    if (genero != 'M' && genero != 'F') {
						                        cout << "\nGenero no valido. Debe ser M o F\n";
						                    } else {
						                        vector<Nodo*> resultados;
						                        buscarPorGenero(raiz, genero, resultados);
						                        string generoTexto = (genero == 'M') ? "Masculino" : "Femenino";
						                        mostrarResultados(resultados, "el genero " + generoTexto);
						                    }
						                }
						                pausar();
						                break;
						            }
						            
						            case 5:
						                // Volver al menú anterior
						                break;
						                
						            default:
						                cout << "\n Opcion no valida. Intente nuevamente.\n";
						                pausar();
						                break;
						        }
						    } while (opcionBusqueda != 5);
						    break;
						}
                        
                        case 3: { // ELIMINAR
                            cout << "\n--- ELIMINAR MIEMBRO ---\n";
                            if (raiz == NULL) {
                                cout << "El arbol esta vacio\n";
                            } else {
                                cout << "Miembros registrados:\n";
                                cout << "------------------------------------\n";
                                mostrarMiembros(raiz);
                                cout << "------------------------------------\n\n";
                                
                                int id;
                                cout << "Ingrese ID del miembro a eliminar: ";
                                cin >> id;
                                
                                eliminarNodo(id);
                            }
                            pausar();
                            break;
                        }
                    }
                } while (subopcion != 4);
                break;
            }
            
            case 2: { // RECORRIDOS
                do {
                    limpiarPantalla();
                    cout << "========== RECORRIDOS DEL ARBOL ==========\n";
                    cout << "1. Recorrido Inorden\n";
                    cout << "2. Recorrido Preorden\n";
                    cout << "3. Recorrido Postorden\n";
                    cout << "4. Recorrido por Niveles\n";
                    cout << "5. Volver al menu principal\n";
                    cout << "==========================================\n";
                    cout << "Seleccione una opcion: ";
                    cin >> subopcion;
                    
                    if (subopcion >= 1 && subopcion <= 4) {
                        cout << "\n";
                        if (raiz == NULL) {
                            cout << "El arbol esta vacio\n";
                        } else {
                            switch (subopcion) {
                                case 1:
                                    cout << "--- RECORRIDO INORDEN ---\n";
                                    cout << "(Orden ascendente por ID)\n\n";
                                    inorden(raiz);
                                    cout << endl;
                                    break;
                                case 2:
                                    cout << "--- RECORRIDO PREORDEN ---\n";
                                    cout << "(Jerarquia desde la raiz)\n\n";
                                    preorden(raiz);
                                    cout << endl;
                                    break;
                                case 3:
                                    cout << "--- RECORRIDO POSTORDEN ---\n";
                                    cout << "(Procesamiento desde las hojas)\n\n";
                                    postorden(raiz);
                                    cout << endl;
                                    break;
                                case 4:
                                    cout << "--- RECORRIDO POR NIVELES ---\n";
                                    cout << "(Generaciones de arriba hacia abajo)\n\n";
                                    porNiveles(raiz);
                                    cout << endl;
                                    break;
                            }
                        }
                        pausar();
                    }
                } while (subopcion != 5);
                break;
            }
            
            case 3: { // INFORMACIÃN
                do {
                    limpiarPantalla();
                    cout << "========== INFORMACION DEL ARBOL ==========\n";
                    cout << "1. Mostrar altura del arbol\n";
                    cout << "2. Mostrar nodo raiz\n";
                    cout << "3. Mostrar nodos hoja\n";
                    cout << "4. Mostrar nodos internos\n";
                    cout << "5. Calcular peso del arbol\n";
                    cout << "6. Volver al menu principal\n";
                    cout << "==========================================\n";
                    cout << "Seleccione una opcion: ";
                    cin >> subopcion;
                    
                    cout << "\n";
                    
                    switch (subopcion) {
                        case 1:
                            cout << "--- ALTURA DEL ARBOL ---\n";
                            if (raiz == NULL) {
                                cout << "El arbol esta vacio (altura = 0)\n";
                            } else {
                                cout << "La altura del arbol es: " << calcularAltura(raiz) << endl;
                            }
                            pausar();
                            break;
                            
                        case 2:
                            cout << "--- NODO RAIZ ---\n";
                            if (raiz == NULL) {
                                cout << "El arbol esta vacio\n";
                            } else {
                                cout << "El nodo raiz es: " << raiz->id << endl;
                                cout << "Nombre: " << raiz->nombre << endl;
                            }
                            pausar();
                            break;
                            
                        case 3:
                            cout << "--- NODOS HOJA ---\n";
                            if (raiz == NULL) {
                                cout << "El arbol esta vacio\n";
                            } else {
                                cout << "Los nodos hoja son:\n";
                                mostrarHojas(raiz);
                                cout << endl;
                            }
                            pausar();
                            break;
                            
                        case 4:
                            cout << "--- NODOS INTERNOS ---\n";
                            if (raiz == NULL) {
                                cout << "El arbol esta vacio\n";
                            } else if (contarNodos(raiz) == 1) {
                                cout << "No hay nodos internos (solo existe la raiz)\n";
                            } else {
                                cout << "Los nodos internos (sin incluir raiz) son:\n";
                                mostrarInternos(raiz, true);
                                cout << endl;
                            }
                            pausar();
                            break;
                            
                        case 5:
                            cout << "--- PESO DEL ARBOL ---\n";
                            if (raiz == NULL) {
                                cout << "El arbol esta vacio (peso = 0)\n";
                            } else {
                                cout << "El peso del arbol (total de nodos) es: " << contarNodos(raiz) << endl;
                            }
                            pausar();
                            break;
                    }
                } while (subopcion != 6);
                break;
            }
            
            case 4: { // OPERACIONES AVANZADAS
                do {
                    limpiarPantalla();
                    cout << "========== OPERACIONES AVANZADAS ==========\n";
                    cout << "1. Mostrar camino desde raiz a nodo\n";
                    cout << "2. Calcular longitud del camino\n";
                    cout << "3. Mostrar altura de un nodo\n";
                    cout << "4. Mostrar nivel de un nodo\n";
                    cout << "5. Balancear arbol\n";
                    cout << "6. Volver al menu principal\n";
                    cout << "==========================================\n";
                    cout << "Seleccione una opcion: ";
                    cin >> subopcion;
                    
                    cout << "\n";
                    
                    switch (subopcion) {
                        case 1: {
                            cout << "--- CAMINO DESDE RAIZ A NODO ---\n";
                            if (raiz == NULL) {
                                cout << "El arbol esta vacio\n";
                            } else {
                                cout << "IDs disponibles en el arbol:\n";
                                cout << "------------------------------------\n";
                                mostrarMiembros(raiz);
                                cout << "------------------------------------\n\n";
                                
                                int id;
                                cout << "Ingrese ID del nodo destino: ";
                                cin >> id;
                                cout << "\n";
                                
                                mostrarCamino(raiz, id);
                            }
                            pausar();
                            break;
                        }
                        
                        case 2: {
                            cout << "--- LONGITUD DEL CAMINO ---\n";
                            if (raiz == NULL) {
                                cout << "El arbol esta vacio\n";
                            } else {
                                cout << "IDs disponibles en el arbol:\n";
                                cout << "------------------------------------\n";
                                mostrarMiembros(raiz);
                                cout << "------------------------------------\n\n";
                                
                                int id;
                                cout << "Ingrese ID del nodo: ";
                                cin >> id;
                                
                                int longitud = longitudCamino(raiz, id, 0);
                                if (longitud == -1) {
                                    cout << "\nNodo no encontrado\n";
                                } else {
                                    cout << "\nLongitud del camino desde raiz hasta " << id << ": " << longitud << " arista(s)\n";
                                }
                            }
                            pausar();
                            break;
                        }
                        
                        case 3: {
                            cout << "--- ALTURA DE UN NODO ---\n";
                            if (raiz == NULL) {
                                cout << "El arbol esta vacio\n";
                            } else {
                                cout << "IDs disponibles en el arbol:\n";
                                cout << "------------------------------------\n";
                                mostrarMiembros(raiz);
                                cout << "------------------------------------\n\n";
                                
                                int id;
                                cout << "Ingrese ID del nodo: ";
                                cin >> id;
                                
                                Nodo* nodo = buscar(raiz, id);
                                if (nodo == NULL) {
                                    cout << "\n? Nodo no encontrado\n";
                                } else {
                                    int altura = calcularAltura(nodo);
                                    cout << "\nAltura del nodo " << id << ": " << altura << endl;
                                    cout << "(Distancia maxima desde " << id << " hasta una hoja)\n";
                                }
                            }
                            pausar();
                            break;
                        }
                        
                        case 4: {
                            cout << "--- NIVEL DE UN NODO ---\n";
                            if (raiz == NULL) {
                                cout << "El arbol esta vacio\n";
                            } else {
                                cout << "IDs disponibles en el arbol:\n";
                                cout << "------------------------------------\n";
                                mostrarMiembros(raiz);
                                cout << "------------------------------------\n\n";
                                
                                int id;
                                cout << "Ingrese ID del nodo: ";
                                cin >> id;
                                
                                int nivel = calcularNivel(raiz, id, 0);
                                if (nivel == -1) {
                                    cout << "\nNodo no encontrado\n";
                                } else {
                                    cout << "\nNivel del nodo " << id << ": " << nivel << endl;
                                    cout << "(La raiz esta en nivel 0)\n";
                                }
                            }
                            pausar();
                            break;
                        }
                        
                        case 5: {
                            cout << "--- BALANCEAR ARBOL ---\n\n";
                            cout << "=== PROPUESTA DE MEJORA ===\n\n";
                            cout << "Para balancear correctamente un arbol binario de busqueda\n";
                            cout << "se requiere implementar algoritmos complejos como:\n\n";
                            cout << "1. Algoritmo AVL (rotaciones simples y dobles)\n";
                            cout << "2. Algoritmo Rojo-Negro\n";
                            cout << "3. Reconstruccion completa del arbol\n\n";
                            cout << "ESTO SE IMPLEMENTARA EN EL ARCHIVO PYTHON DONDE TAMBIEN SE VISUALIZARA EL ARBOL";
                            
                            if (raiz != NULL) {
                                cout << "Analisis basico del arbol actual:\n";
                                cout << "- Total de nodos: " << contarNodos(raiz) << endl;
                                int altura = calcularAltura(raiz);
                                cout << "- Altura actual: " << altura << endl;
                                
                                int alturaIdeal = (int)log2(contarNodos(raiz));
                                cout << "- Altura ideal (balanceado): " << alturaIdeal << endl;
                                
                                if (altura <= alturaIdeal + 1) {
                                    cout << "- Estado: El arbol esta relativamente balanceado\n";
                                } else {
                                    cout << "- Estado: El arbol necesita balanceo\n";
                                }
                            }
                            pausar();
                            break;
                        }
                    }
                } while (subopcion != 6);
                break;
            }
            
            case 5:
                limpiarPantalla();
                cout << "\n==========================================\n";
                cout << "  Saliendo del sistema...\n";
                cout << "  Hasta pronto!\n";
                cout << "==========================================\n\n";
                break;
                
            default:
                cout << "\n Opcion no valida. Intente nuevamente.\n";
                pausar();
                break;
        }
        
    } while (opcion != 5);
    
    return 0;
}

