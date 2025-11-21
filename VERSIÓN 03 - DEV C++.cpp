#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <cmath>

using namespace std;

// Estructura del Nodo
struct Nodo {
    int id;
    string nombre;
    int anio;
    char genero;
    string rol;
    Nodo* izq;
    Nodo* der;
    Nodo* padre;
    
    Nodo(int i, string n, int a, char g, string r) {
        id = i;
        nombre = n;
        anio = a;
        genero = g;
        rol = r;
        izq = NULL;
        der = NULL;
        padre = NULL;
    }
};

// Variables globales
Nodo* raiz = NULL;

// Prototipos de funciones
void limpiarPantalla();
void pausar();
void insertar(int id, string nombre, int anio, char genero, string rol);
Nodo* buscar(Nodo* nodo, int id);
bool existeID(Nodo* nodo, int id);
void mostrarMiembros(Nodo* nodo);
void eliminarNodo(int id);
void inorden(Nodo* nodo);
void preorden(Nodo* nodo);
void postorden(Nodo* nodo);
void porNiveles(Nodo* nodo);
int calcularAltura(Nodo* nodo);
void mostrarHojas(Nodo* nodo);
void mostrarInternos(Nodo* nodo, bool esRaiz);
int contarNodos(Nodo* nodo);
void mostrarCamino(Nodo* nodo, int id);
void buscarPorAnio(Nodo* nodo, int anio, vector<Nodo*>& resultados);
void buscarPorNombre(Nodo* nodo, string nombre, vector<Nodo*>& resultados);
void buscarPorGenero(Nodo* nodo, char genero, vector<Nodo*>& resultados);
void mostrarResultados(vector<Nodo*>& resultados, string criterio);
int calcularNivel(Nodo* nodo, int id, int nivel);
int longitudCamino(Nodo* nodo, int id, int nivel);

// Función para limpiar pantalla
void limpiarPantalla() {
    system("cls");
}

// Función para pausar
void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Función para verificar si un ID existe
bool existeID(Nodo* nodo, int id) {
    if (nodo == NULL) return false;
    if (nodo->id == id) return true;
    return existeID(nodo->izq, id) || existeID(nodo->der, id);
}

// Función para insertar un nodo
void insertar(int id, string nombre, int anio, char genero, string rol) {
    Nodo* nuevo = new Nodo(id, nombre, anio, genero, rol);
    
    if (raiz == NULL) {
        raiz = nuevo;
        cout << "\n Miembro insertado como raiz del arbol\n";
    } else {
        Nodo* actual = raiz;
        Nodo* padre = NULL;
        
        while (actual != NULL) {
            padre = actual;
            if (id < actual->id) {
                actual = actual->izq;
            } else {
                actual = actual->der;
            }
        }
        
        nuevo->padre = padre;
        if (id < padre->id) {
            padre->izq = nuevo;
        } else {
            padre->der = nuevo;
        }
        
        cout << "\n Miembro insertado correctamente\n";
    }
}

// Función para buscar un nodo
Nodo* buscar(Nodo* nodo, int id) {
    if (nodo == NULL || nodo->id == id) {
        return nodo;
    }
    if (id < nodo->id) {
        return buscar(nodo->izq, id);
    }
    return buscar(nodo->der, id);
}

// Función para mostrar todos los miembros
void mostrarMiembros(Nodo* nodo) {
    if (nodo != NULL) {
        mostrarMiembros(nodo->izq);
        cout << "ID: " << nodo->id << " - " << nodo->nombre << endl;
        mostrarMiembros(nodo->der);
    }
}

// Función para encontrar el nodo con valor mÃ­nimo
Nodo* encontrarMinimo(Nodo* nodo) {
    while (nodo->izq != NULL) {
        nodo = nodo->izq;
    }
    return nodo;
}

// Función auxiliar para eliminar nodo
Nodo* eliminarNodoAux(Nodo* nodo, int id, bool& eliminado) {
    if (nodo == NULL) return NULL;
    
    if (id < nodo->id) {
        nodo->izq = eliminarNodoAux(nodo->izq, id, eliminado);
        if (nodo->izq != NULL) nodo->izq->padre = nodo;
    } else if (id > nodo->id) {
        nodo->der = eliminarNodoAux(nodo->der, id, eliminado);
        if (nodo->der != NULL) nodo->der->padre = nodo;
    } else {
        eliminado = true;
        
        if (nodo->izq == NULL && nodo->der == NULL) {
            delete nodo;
            return NULL;
        } else if (nodo->izq == NULL) {
            Nodo* temp = nodo->der;
            delete nodo;
            return temp;
        } else if (nodo->der == NULL) {
            Nodo* temp = nodo->izq;
            delete nodo;
            return temp;
        } else {
            Nodo* sucesor = encontrarMinimo(nodo->der);
            nodo->id = sucesor->id;
            nodo->nombre = sucesor->nombre;
            nodo->anio = sucesor->anio;
            nodo->genero = sucesor->genero;
            nodo->rol = sucesor->rol;
            nodo->der = eliminarNodoAux(nodo->der, sucesor->id, eliminado);
            if (nodo->der != NULL) nodo->der->padre = nodo;
        }
    }
    return nodo;
}

// Función para eliminar un nodo
void eliminarNodo(int id) {
    bool eliminado = false;
    raiz = eliminarNodoAux(raiz, id, eliminado);
    
    if (eliminado) {
        cout << "\n Miembro eliminado correctamente\n";
    } else {
        cout << "\n Miembro no encontrado\n";
    }
}

// Recorrido Inorden
void inorden(Nodo* nodo) {
    if (nodo != NULL) {
        inorden(nodo->izq);
        cout << nodo->id << " ";
        inorden(nodo->der);
    }
}

// Recorrido Preorden
void preorden(Nodo* nodo) {
    if (nodo != NULL) {
        cout << nodo->id << " ";
        preorden(nodo->izq);
        preorden(nodo->der);
    }
}

// Recorrido Postorden
void postorden(Nodo* nodo) {
    if (nodo != NULL) {
        postorden(nodo->izq);
        postorden(nodo->der);
        cout << nodo->id << " ";
    }
}

// Recorrido por Niveles
void porNiveles(Nodo* nodo) {
    if (nodo == NULL) return;
    
    queue<Nodo*> cola;
    cola.push(nodo);
    
    while (!cola.empty()) {
        Nodo* actual = cola.front();
        cola.pop();
        cout << actual->id << " ";
        
        if (actual->izq != NULL) cola.push(actual->izq);
        if (actual->der != NULL) cola.push(actual->der);
    }
}

// Calcular altura del Árbol
int calcularAltura(Nodo* nodo) {
    if (nodo == NULL) return -1;
    int alturaIzq = calcularAltura(nodo->izq);
    int alturaDer = calcularAltura(nodo->der);
    return 1 + max(alturaIzq, alturaDer);
}

// Mostrar nodos hoja
void mostrarHojas(Nodo* nodo) {
    if (nodo != NULL) {
        if (nodo->izq == NULL && nodo->der == NULL) {
            cout << nodo->id << " ";
        }
        mostrarHojas(nodo->izq);
        mostrarHojas(nodo->der);
    }
}

// Mostrar nodos internos (sin incluir raíz)
void mostrarInternos(Nodo* nodo, bool esRaiz) {
    if (nodo != NULL) {
        if (!esRaiz && (nodo->izq != NULL || nodo->der != NULL)) {
            cout << nodo->id << " ";
        }
        mostrarInternos(nodo->izq, false);
        mostrarInternos(nodo->der, false);
    }
}

// Contar nodos
int contarNodos(Nodo* nodo) {
    if (nodo == NULL) return 0;
    return 1 + contarNodos(nodo->izq) + contarNodos(nodo->der);
}

// Mostrar camino desde raíz a nodo
void mostrarCamino(Nodo* nodo, int id) {
    Nodo* destino = buscar(nodo, id);
    if (destino == NULL) {
        cout << " Nodo no encontrado\n";
        return;
    }
    
    vector<int> camino;
    Nodo* actual = destino;
    
    while (actual != NULL) {
        camino.push_back(actual->id);
        actual = actual->padre;
    }
    
    cout << "Camino desde raiz hasta " << id << ":\n";
    for (int i = camino.size() - 1; i >= 0; i--) {
        cout << camino[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

// Calcular nivel de un nodo
int calcularNivel(Nodo* nodo, int id, int nivel) {
    if (nodo == NULL) return -1;
    if (nodo->id == id) return nivel;
    
    int nivelIzq = calcularNivel(nodo->izq, id, nivel + 1);
    if (nivelIzq != -1) return nivelIzq;
    
    return calcularNivel(nodo->der, id, nivel + 1);
}

// Calcular longitud del camino
int longitudCamino(Nodo* nodo, int id, int nivel) {
    if (nodo == NULL) return -1;
    if (nodo->id == id) return nivel;
    
    int longitudIzq = longitudCamino(nodo->izq, id, nivel + 1);
    if (longitudIzq != -1) return longitudIzq;
    
    return longitudCamino(nodo->der, id, nivel + 1);
}

// Búsqueda por año de nacimiento
void buscarPorAnio(Nodo* nodo, int anio, vector<Nodo*>& resultados) {
    if (nodo != NULL) {
        buscarPorAnio(nodo->izq, anio, resultados);
        if (nodo->anio == anio) {
            resultados.push_back(nodo);
        }
        buscarPorAnio(nodo->der, anio, resultados);
    }
}

// Búsqueda por nombre (búsqueda parcial, no case-sensitive)
void buscarPorNombre(Nodo* nodo, string nombre, vector<Nodo*>& resultados) {
    if (nodo != NULL) {
        buscarPorNombre(nodo->izq, nombre, resultados);
        
        // Convertir ambos strings a minúsculas para comparación
        string nombreNodo = nodo->nombre;
        string nombreBusqueda = nombre;
        transform(nombreNodo.begin(), nombreNodo.end(), nombreNodo.begin(), ::tolower);
        transform(nombreBusqueda.begin(), nombreBusqueda.end(), nombreBusqueda.begin(), ::tolower);
        
        // Buscar si el nombre ingresado está contenido en el nombre del nodo
        if (nombreNodo.find(nombreBusqueda) != string::npos) {
            resultados.push_back(nodo);
        }
        
        buscarPorNombre(nodo->der, nombre, resultados);
    }
}

// Búsqueda por género
void buscarPorGenero(Nodo* nodo, char genero, vector<Nodo*>& resultados) {
    if (nodo != NULL) {
        buscarPorGenero(nodo->izq, genero, resultados);
        if (nodo->genero == genero) {
            resultados.push_back(nodo);
        }
        buscarPorGenero(nodo->der, genero, resultados);
    }
}

// Mostrar resultados de búsqueda
void mostrarResultados(vector<Nodo*>& resultados, string criterio) {
    if (resultados.empty()) {
        cout << "\n No se encontraron miembros con esa coincidencia\n";
    } else {
        cout << "\n Se encontraron " << resultados.size() << " miembro(s) con esa coincidencia\n";
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
            case 1: { // GESTIÃ“N DE MIEMBROS
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
						                        cout << "\n Genero no valido. Debe ser M o F\n";
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
            
            case 3: { // INFORMACIÃ“N
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
                                    cout << "\n? Nodo no encontrado\n";
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
                                    cout << "\n? Nodo no encontrado\n";
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
                                    cout << "- Estado: ? El arbol esta relativamente balanceado\n";
                                } else {
                                    cout << "- Estado: ? El arbol necesita balanceo\n";
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
                cout << "\n? Opcion no valida. Intente nuevamente.\n";
                pausar();
                break;
        }
        
    } while (opcion != 5);
    
    return 0;
}
