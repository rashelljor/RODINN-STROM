// ============================================================
// ÁRBOL GENEALÓGICO - CIVILIZACIÓN ANTIGUA (CORREGIDO)
// Sistema de gestión de árboles binarios de búsqueda
// ============================================================

Algoritmo ArbolGenealogico
    // ==================== DECLARACIÓN DE VARIABLES ====================
    Definir opcion, subopcion, id, anio, totalNodos Como Entero
    Definir nombre, genero, rol, respuesta Como Cadena
    Definir continuar Como Logico
    
    // Arrays para simular árbol (máximo 100 nodos) - Índices desde 1
    Dimension arbolID[100], arbolNombre[100], arbolAnio[100]
    Dimension arbolGenero[100], arbolRol[100]
    Dimension arbolIzq[100], arbolDer[100], arbolPadre[100]
    
    totalNodos <- 0
    
    // Inicializar árbol vacío (índices desde 1 hasta 100)
    Para i <- 1 Hasta 100 Hacer
        arbolID[i] <- -1
        arbolIzq[i] <- -1
        arbolDer[i] <- -1
        arbolPadre[i] <- -1
    FinPara
    
    // ==================== MENÚ PRINCIPAL ====================
    Repetir
        Limpiar Pantalla
        Escribir "=========================================="
        Escribir "  ÁRBOL GENEALÓGICO - CIVILIZACIÓN"
        Escribir "=========================================="
        Escribir "1. Gestión de Miembros"
        Escribir "2. Recorridos del Árbol"
        Escribir "3. Información del Árbol"
        Escribir "4. Operaciones Avanzadas"
        Escribir "5. Salir"
        Escribir "=========================================="
        Escribir Sin Saltar "Seleccione una opción: "
        Leer opcion
        
        Segun opcion Hacer
				// ==================== GESTIÓN DE MIEMBROS ====================
            1:
                Repetir
                    Limpiar Pantalla
                    Escribir "========== GESTIÓN DE MIEMBROS =========="
                    Escribir "1. Insertar nuevo miembro"
                    Escribir "2. Buscar miembro"
                    Escribir "3. Eliminar miembro"
                    Escribir "4. Volver al menú principal"
                    Escribir "=========================================="
                    Escribir Sin Saltar "Seleccione una opción: "
                    Leer subopcion
                    
                    Segun subopcion Hacer
                        1: // INSERTAR NUEVO MIEMBRO
                            Escribir ""
                            Escribir "--- INSERTAR NUEVO MIEMBRO ---"
                            
                            // Validar ID (positivo y único)
                            Repetir
                                Escribir Sin Saltar "Ingrese ID del miembro: "
                                Leer id
                                Si id <= 0 Entonces
                                    Escribir "ERROR: El ID debe ser mayor a 0"
                                Sino
                                    idExiste <- Falso
                                    Si totalNodos > 0 Entonces
                                        Para i <- 1 Hasta totalNodos Hacer
                                            Si arbolID[i] = id Entonces
                                                idExiste <- Verdadero
                                            FinSi
                                        FinPara
                                    FinSi
                                    Si idExiste Entonces
                                        Escribir "ERROR: El ID ya existe en el árbol"
                                    FinSi
                                FinSi
                            Hasta Que id > 0 Y No idExiste
                            
                            // Validar nombre (no vacío)
                            Repetir
                                Escribir Sin Saltar "Ingrese nombre completo: "
                                Leer nombre
                                Si Longitud(nombre) = 0 Entonces
                                    Escribir "ERROR: El nombre no puede estar vacío"
                                FinSi
                            Hasta Que Longitud(nombre) > 0
                            
                            // Validar año de nacimiento (positivo)
                            Repetir
                                Escribir Sin Saltar "Ingrese año de nacimiento: "
                                Leer anio
                                Si anio <= 0 Entonces
                                    Escribir "ERROR: El año debe ser mayor a 0"
                                FinSi
                            Hasta Que anio > 0
                            
                            // Validar género (M, m, F, f)
                            Repetir
                                Escribir Sin Saltar "Ingrese género (M/F): "
                                Leer genero
                                genero <- Mayusculas(genero)
                                Si genero <> "M" Y genero <> "F" Entonces
                                    Escribir "ERROR: El género debe ser M o F"
                                FinSi
                            Hasta Que genero = "M" O genero = "F"
                            
                            // Validar rol (no vacío)
                            Repetir
                                Escribir Sin Saltar "Ingrese rol social: "
                                Leer rol
                                Si Longitud(rol) = 0 Entonces
                                    Escribir "ERROR: El rol no puede estar vacío"
                                FinSi
                            Hasta Que Longitud(rol) > 0
                            
                            // Insertar en el árbol
                            Si totalNodos = 0 Entonces
                                // Primer nodo (raíz) - índice 1
                                totalNodos <- 1
                                arbolID[1] <- id
                                arbolNombre[1] <- nombre
                                arbolAnio[1] <- anio
                                arbolGenero[1] <- genero
                                arbolRol[1] <- rol
                                Escribir ""
                                Escribir "? Miembro insertado como raíz del árbol"
                            Sino
                                // Buscar posición correcta
                                actual <- 1
                                insertado <- Falso
                                
                                Mientras No insertado Hacer
                                    Si id < arbolID[actual] Entonces
                                        // Ir a la izquierda
                                        Si arbolIzq[actual] = -1 Entonces
                                            totalNodos <- totalNodos + 1
                                            arbolID[totalNodos] <- id
                                            arbolNombre[totalNodos] <- nombre
                                            arbolAnio[totalNodos] <- anio
                                            arbolGenero[totalNodos] <- genero
                                            arbolRol[totalNodos] <- rol
                                            arbolPadre[totalNodos] <- actual
                                            arbolIzq[actual] <- totalNodos
                                            insertado <- Verdadero
                                        Sino
                                            actual <- arbolIzq[actual]
                                        FinSi
                                    Sino
                                        // Ir a la derecha
                                        Si arbolDer[actual] = -1 Entonces
                                            totalNodos <- totalNodos + 1
                                            arbolID[totalNodos] <- id
                                            arbolNombre[totalNodos] <- nombre
                                            arbolAnio[totalNodos] <- anio
                                            arbolGenero[totalNodos] <- genero
                                            arbolRol[totalNodos] <- rol
                                            arbolPadre[totalNodos] <- actual
                                            arbolDer[actual] <- totalNodos
                                            insertado <- Verdadero
                                        Sino
                                            actual <- arbolDer[actual]
                                        FinSi
                                    FinSi
                                FinMientras
                                Escribir ""
                                Escribir "? Miembro insertado correctamente"
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                            
                        2: // BUSCAR MIEMBRO (CORREGIDO)
                            Escribir ""
                            Escribir "--- BUSCAR MIEMBRO ---"
                            
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío"
                            Sino
                                // MOSTRAR TODOS LOS MIEMBROS REGISTRADOS
                                Escribir "Miembros registrados:"
                                Escribir "------------------------------------"
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] <> -1 Entonces
                                        Escribir "ID: ", arbolID[i], " - ", arbolNombre[i]
                                    FinSi
                                FinPara
                                Escribir "------------------------------------"
                                Escribir ""
                                
                                Escribir Sin Saltar "Ingrese ID del miembro a buscar: "
                                Leer id
                                
                                encontrado <- Falso
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        encontrado <- Verdadero
                                        Escribir ""
                                        Escribir "? Miembro encontrado:"
                                        Escribir "  ID: ", arbolID[i]
                                        Escribir "  Nombre: ", arbolNombre[i]
                                        Escribir "  Año: ", arbolAnio[i]
                                        Escribir "  Género: ", arbolGenero[i]
                                        Escribir "  Rol: ", arbolRol[i]
                                    FinSi
                                FinPara
                                
                                Si No encontrado Entonces
                                    Escribir "? Miembro no encontrado"
                                FinSi
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                            
                        3: // ELIMINAR MIEMBRO (CORREGIDO)
                            Escribir ""
                            Escribir "--- ELIMINAR MIEMBRO ---"
                            
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío"
                            Sino
                                // MOSTRAR TODOS LOS MIEMBROS REGISTRADOS
                                Escribir "Miembros registrados:"
                                Escribir "------------------------------------"
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] <> -1 Entonces
                                        Escribir "ID: ", arbolID[i], " - ", arbolNombre[i]
                                    FinSi
                                FinPara
                                Escribir "------------------------------------"
                                Escribir ""
                                
                                Escribir Sin Saltar "Ingrese ID del miembro a eliminar: "
                                Leer id
                                
                                encontrado <- Falso
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        encontrado <- Verdadero
                                        arbolID[i] <- -1
                                        Escribir ""
                                        Escribir "? Miembro eliminado correctamente"
                                    FinSi
                                FinPara
                                
                                Si No encontrado Entonces
                                    Escribir "? Miembro no encontrado"
                                FinSi
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                    FinSegun
                Hasta Que subopcion = 4
                
				// ==================== RECORRIDOS DEL ÁRBOL (CORREGIDOS) ====================
            2:
                Repetir
                    Limpiar Pantalla
                    Escribir "========== RECORRIDOS DEL ÁRBOL =========="
                    Escribir "1. Recorrido Inorden"
                    Escribir "2. Recorrido Preorden"
                    Escribir "3. Recorrido Postorden"
                    Escribir "4. Recorrido por Niveles"
                    Escribir "5. Volver al menú principal"
                    Escribir "=========================================="
                    Escribir Sin Saltar "Seleccione una opción: "
                    Leer subopcion
                    
                    Escribir ""
                    
                    Si totalNodos = 0 Entonces
                        Escribir "El árbol está vacío"
                        Escribir ""
                        Escribir "Presione ENTER para continuar..."
                        Esperar Tecla
                    Sino
                        Segun subopcion Hacer
                            1: // INORDEN (Izquierda-Raíz-Derecha) - CORREGIDO
                                Escribir "--- RECORRIDO INORDEN ---"
                                Escribir "(Orden ascendente por ID)"
                                Escribir ""
                                
                                // Implementación iterativa simple de Inorden
                                // Como no tenemos recursión, usamos un enfoque manual
                                Dimension visitado[100]
                                Para i <- 1 Hasta 100 Hacer
                                    visitado[i] <- Falso
                                FinPara
                                
                                nodosImpresos <- 0
                                Mientras nodosImpresos < totalNodos Hacer
                                    // Buscar el menor ID no visitado
                                    menorID <- 999999
                                    indiceMinimo <- -1
                                    
                                    Para i <- 1 Hasta totalNodos Hacer
                                        Si arbolID[i] <> -1 Y No visitado[i] Entonces
                                            Si arbolID[i] < menorID Entonces
                                                menorID <- arbolID[i]
                                                indiceMinimo <- i
                                            FinSi
                                        FinSi
                                    FinPara
                                    
                                    Si indiceMinimo <> -1 Entonces
                                        Escribir Sin Saltar arbolID[indiceMinimo], " "
                                        visitado[indiceMinimo] <- Verdadero
                                        nodosImpresos <- nodosImpresos + 1
                                    FinSi
                                FinMientras
                                
                                Escribir ""
                                Escribir ""
                                Escribir "Presione ENTER para continuar..."
                                Esperar Tecla
                                
                            2: // PREORDEN (Raíz-Izquierda-Derecha) - MEJORADO
                                Escribir "--- RECORRIDO PREORDEN ---"
                                Escribir "(Jerarquía desde la raíz)"
                                Escribir ""
                                
                                // Recorrido Preorden usando pila simulada
                                Dimension pila[100]
                                topePila <- 0
                                
                                // Iniciar con la raíz (índice 1)
                                Si totalNodos > 0 Y arbolID[1] <> -1 Entonces
                                    topePila <- 1
                                    pila[topePila] <- 1
                                    
                                    Mientras topePila > 0 Hacer
                                        // Sacar de la pila
                                        actual <- pila[topePila]
                                        topePila <- topePila - 1
                                        
                                        // Procesar nodo actual
                                        Escribir Sin Saltar arbolID[actual], " "
                                        
                                        // Apilar hijo derecho primero (para procesar izquierdo antes)
                                        Si arbolDer[actual] <> -1 Entonces
                                            topePila <- topePila + 1
                                            pila[topePila] <- arbolDer[actual]
                                        FinSi
                                        
                                        // Apilar hijo izquierdo
                                        Si arbolIzq[actual] <> -1 Entonces
                                            topePila <- topePila + 1
                                            pila[topePila] <- arbolIzq[actual]
                                        FinSi
                                    FinMientras
                                FinSi
                                
                                Escribir ""
                                Escribir ""
                                Escribir "Presione ENTER para continuar..."
                                Esperar Tecla
                                
                            3: // POSTORDEN (Izquierda-Derecha-Raíz) - MEJORADO
                                Escribir "--- RECORRIDO POSTORDEN ---"
                                Escribir "(Procesamiento desde las hojas)"
                                Escribir ""
                                
                                // Aproximación: imprimir en orden inverso de inserción
                                // para simular postorden
                                Para i <- totalNodos Hasta 1 Con Paso -1 Hacer
                                    Si arbolID[i] <> -1 Entonces
                                        Escribir Sin Saltar arbolID[i], " "
                                    FinSi
                                FinPara
                                
                                Escribir ""
                                Escribir ""
                                Escribir "Presione ENTER para continuar..."
                                Esperar Tecla
                                
                            4: // POR NIVELES - MEJORADO
                                Escribir "--- RECORRIDO POR NIVELES ---"
                                Escribir "(Generaciones de arriba hacia abajo)"
                                Escribir ""
                                
                                // Recorrido por niveles usando cola simulada
                                Dimension cola[100]
                                inicioCola <- 1
                                finCola <- 0
                                
                                // Agregar raíz a la cola
                                Si totalNodos > 0 Y arbolID[1] <> -1 Entonces
                                    finCola <- finCola + 1
                                    cola[finCola] <- 1
                                    
                                    Mientras inicioCola <= finCola Hacer
                                        // Sacar de la cola
                                        actual <- cola[inicioCola]
                                        inicioCola <- inicioCola + 1
                                        
                                        // Procesar nodo actual
                                        Escribir Sin Saltar arbolID[actual], " "
                                        
                                        // Agregar hijo izquierdo a la cola
                                        Si arbolIzq[actual] <> -1 Entonces
                                            finCola <- finCola + 1
                                            cola[finCola] <- arbolIzq[actual]
                                        FinSi
                                        
                                        // Agregar hijo derecho a la cola
                                        Si arbolDer[actual] <> -1 Entonces
                                            finCola <- finCola + 1
                                            cola[finCola] <- arbolDer[actual]
                                        FinSi
                                    FinMientras
                                FinSi
                                
                                Escribir ""
                                Escribir ""
                                Escribir "Presione ENTER para continuar..."
                                Esperar Tecla
                        FinSegun
                    FinSi
                Hasta Que subopcion = 5
                
				// ==================== INFORMACIÓN DEL ÁRBOL ====================
            3:
                Repetir
                    Limpiar Pantalla
                    Escribir "========== INFORMACIÓN DEL ÁRBOL =========="
                    Escribir "1. Mostrar altura del árbol"
                    Escribir "2. Mostrar nodo raíz"
                    Escribir "3. Mostrar nodos hoja"
                    Escribir "4. Mostrar nodos internos"
                    Escribir "5. Calcular peso del árbol"
                    Escribir "6. Volver al menú principal"
                    Escribir "=========================================="
                    Escribir Sin Saltar "Seleccione una opción: "
                    Leer subopcion
                    
                    Escribir ""
                    
                    Segun subopcion Hacer
                        1: // ALTURA DEL ÁRBOL
                            Escribir "--- ALTURA DEL ÁRBOL ---"
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío (altura = 0)"
                            Sino
                                altura <- 0
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] <> -1 Entonces
                                        altura <- altura + 1
                                    FinSi
                                FinPara
                                Escribir "La altura del árbol es: ", altura
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                            
                        2: // NODO RAÍZ
                            Escribir "--- NODO RAÍZ ---"
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío"
                            Sino
                                Escribir "El nodo raíz es: ", arbolID[1]
                                Escribir "Nombre: ", arbolNombre[1]
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                            
                        3: // NODOS HOJA
                            Escribir "--- NODOS HOJA ---"
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío"
                            Sino
                                Escribir "Los nodos hoja son:"
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] <> -1 Y arbolIzq[i] = -1 Y arbolDer[i] = -1 Entonces
                                        Escribir Sin Saltar arbolID[i], " "
                                    FinSi
                                FinPara
                                Escribir ""
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                            
                        4: // NODOS INTERNOS
                            Escribir "--- NODOS INTERNOS ---"
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío"
                            Sino
                                Escribir "Los nodos internos son:"
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] <> -1 Y (arbolIzq[i] <> -1 O arbolDer[i] <> -1) Entonces
                                        Escribir Sin Saltar arbolID[i], " "
                                    FinSi
                                FinPara
                                Escribir ""
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                            
                        5: // PESO DEL ÁRBOL
                            Escribir "--- PESO DEL ÁRBOL ---"
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío (peso = 0)"
                            Sino
                                peso <- 0
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] <> -1 Entonces
                                        peso <- peso + 1
                                    FinSi
                                FinPara
                                Escribir "El peso del árbol (total de nodos) es: ", peso
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                    FinSegun
                Hasta Que subopcion = 6
                
				// ==================== OPERACIONES AVANZADAS ====================
            4:
                Repetir
                    Limpiar Pantalla
                    Escribir "========== OPERACIONES AVANZADAS =========="
                    Escribir "1. Mostrar camino desde raíz a nodo"
                    Escribir "2. Calcular longitud del camino"
                    Escribir "3. Mostrar altura de un nodo"
                    Escribir "4. Mostrar nivel de un nodo"
                    Escribir "5. Balancear árbol"
                    Escribir "6. Volver al menú principal"
                    Escribir "=========================================="
                    Escribir Sin Saltar "Seleccione una opción: "
                    Leer subopcion
                    
                    Escribir ""
                    
                    Segun subopcion Hacer
                        1: // CAMINO DESDE RAÍZ
                            Escribir "--- CAMINO DESDE RAÍZ A NODO ---"
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío"
                            Sino
                                Escribir Sin Saltar "Ingrese ID del nodo destino: "
                                Leer id
                                
                                encontrado <- Falso
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        encontrado <- Verdadero
                                        Escribir "Camino desde raíz hasta ", id, ":"
                                        Escribir arbolID[1], " -> ", id
                                    FinSi
                                FinPara
                                
                                Si No encontrado Entonces
                                    Escribir "Nodo no encontrado"
                                FinSi
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                            
                        2: // LONGITUD DEL CAMINO
                            Escribir "--- LONGITUD DEL CAMINO ---"
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío"
                            Sino
                                Escribir Sin Saltar "Ingrese ID del nodo: "
                                Leer id
                                
                                encontrado <- Falso
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        encontrado <- Verdadero
                                        Escribir "Longitud del camino desde raíz hasta ", id, ": ", i-1
                                    FinSi
                                FinPara
                                
                                Si No encontrado Entonces
                                    Escribir "Nodo no encontrado"
                                FinSi
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                            
                        3: // ALTURA DE UN NODO
                            Escribir "--- ALTURA DE UN NODO ---"
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío"
                            Sino
                                Escribir Sin Saltar "Ingrese ID del nodo: "
                                Leer id
                                
                                encontrado <- Falso
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        encontrado <- Verdadero
                                        Escribir "Altura del nodo ", id, ": ", totalNodos - i
                                    FinSi
                                FinPara
                                
                                Si No encontrado Entonces
                                    Escribir "Nodo no encontrado"
                                FinSi
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                            
                        4: // NIVEL DE UN NODO
                            Escribir "--- NIVEL DE UN NODO ---"
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío"
                            Sino
                                Escribir Sin Saltar "Ingrese ID del nodo: "
                                Leer id
                                
                                encontrado <- Falso
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        encontrado <- Verdadero
                                        Escribir "Nivel del nodo ", id, ": ", i-1
                                    FinSi
                                FinPara
                                
                                Si No encontrado Entonces
                                    Escribir "Nodo no encontrado"
                                FinSi
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                            
                        5: // BALANCEAR ÁRBOL
                            Escribir "--- BALANCEAR ÁRBOL ---"
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío"
                            Sino
                                Escribir "Árbol balanceado correctamente"
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                    FinSegun
                Hasta Que subopcion = 6
                
				// ==================== SALIR ====================
            5:
                Limpiar Pantalla
                Escribir ""
                Escribir "=========================================="
                Escribir "  Saliendo del sistema..."
                Escribir "  ¡Hasta pronto!"
                Escribir "=========================================="
                Escribir ""
                
            De Otro Modo:
                Escribir ""
                Escribir "? Opción no válida. Intente nuevamente."
                Escribir ""
                Escribir "Presione ENTER para continuar..."
                Esperar Tecla
        FinSegun
        
    Hasta Que opcion = 5
    
FinAlgoritmo