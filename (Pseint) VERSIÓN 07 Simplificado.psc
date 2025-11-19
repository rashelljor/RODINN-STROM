// ============================================================
// ÁRBOL GENEALÓGICO - CIVILIZACIÓN ANTIGUA
// Sistema de gestión de árboles binarios de búsqueda
// ============================================================

Algoritmo ArbolGenealogico
    // Variables principales
    Definir opcion, subopcion, id, anio, totalNodos Como Entero
    Definir nombre, genero, rol Como Cadena
    Definir idExiste, encontrado, insertado Como Logico
    Definir actual, i Como Entero
    
    // Arrays para el árbol (máximo 100 nodos)
    Dimension arbolID[100], arbolNombre[100], arbolAnio[100]
    Dimension arbolGenero[100], arbolRol[100]
    Dimension arbolIzq[100], arbolDer[100], arbolPadre[100]
    
    totalNodos <- 0
    
    // Inicializar árbol vacío
    Para i <- 1 Hasta 100 Hacer
        arbolID[i] <- -1
        arbolIzq[i] <- -1
        arbolDer[i] <- -1
        arbolPadre[i] <- -1
    FinPara
    
    // MENÚ PRINCIPAL
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
            1:
                // GESTIÓN DE MIEMBROS
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
                        1:
                            // INSERTAR NUEVO MIEMBRO
                            Escribir ""
                            Escribir "--- INSERTAR NUEVO MIEMBRO ---"
                            
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
                                        Escribir "ERROR: El ID ya existe"
                                    FinSi
                                FinSi
                            Hasta Que id > 0 Y No idExiste
                            
                            Repetir
                                Escribir Sin Saltar "Ingrese nombre completo: "
                                Leer nombre
                                Si Longitud(nombre) = 0 Entonces
                                    Escribir "ERROR: El nombre no puede estar vacío"
                                FinSi
                            Hasta Que Longitud(nombre) > 0
                            
                            Repetir
                                Escribir Sin Saltar "Ingrese año de nacimiento: "
                                Leer anio
                                Si anio <= 0 Entonces
                                    Escribir "ERROR: El año debe ser mayor a 0"
                                FinSi
                            Hasta Que anio > 0
                            
                            Repetir
                                Escribir Sin Saltar "Ingrese género (M/F): "
                                Leer genero
                                genero <- Mayusculas(genero)
                                Si genero <> "M" Y genero <> "F" Entonces
                                    Escribir "ERROR: El género debe ser M o F"
                                FinSi
                            Hasta Que genero = "M" O genero = "F"
                            
                            Repetir
                                Escribir Sin Saltar "Ingrese rol social: "
                                Leer rol
                                Si Longitud(rol) = 0 Entonces
                                    Escribir "ERROR: El rol no puede estar vacío"
                                FinSi
                            Hasta Que Longitud(rol) > 0
                            
                            Si totalNodos = 0 Entonces
                                totalNodos <- 1
                                arbolID[1] <- id
                                arbolNombre[1] <- nombre
                                arbolAnio[1] <- anio
                                arbolGenero[1] <- genero
                                arbolRol[1] <- rol
                                arbolPadre[1] <- 0
                                Escribir ""
                                Escribir "Miembro insertado como raíz"
                            Sino
                                actual <- 1
                                insertado <- Falso
                                
                                Mientras No insertado Hacer
                                    Si id < arbolID[actual] Entonces
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
                                Escribir "Miembro insertado correctamente"
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                            
                        2:
                            // BUSCAR MIEMBRO
                            Escribir ""
                            Escribir "--- BUSCAR MIEMBRO ---"
                            
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío"
                            Sino
                                Escribir "Miembros registrados:"
                                Escribir "------------------------------------"
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] <> -1 Entonces
                                        Escribir "ID: ", arbolID[i], " - ", arbolNombre[i]
                                    FinSi
                                FinPara
                                Escribir "------------------------------------"
                                Escribir ""
                                
                                Escribir Sin Saltar "Ingrese ID a buscar: "
                                Leer id
                                
                                encontrado <- Falso
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        encontrado <- Verdadero
                                        Escribir ""
                                        Escribir "Miembro encontrado:"
                                        Escribir "  ID: ", arbolID[i]
                                        Escribir "  Nombre: ", arbolNombre[i]
                                        Escribir "  Año: ", arbolAnio[i]
                                        Escribir "  Género: ", arbolGenero[i]
                                        Escribir "  Rol: ", arbolRol[i]
                                    FinSi
                                FinPara
                                
                                Si No encontrado Entonces
                                    Escribir "Miembro no encontrado"
                                FinSi
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                            
                        3:
                            // ELIMINAR MIEMBRO
                            Escribir ""
                            Escribir "--- ELIMINAR MIEMBRO ---"
                            
                            Si totalNodos = 0 Entonces
                                Escribir "El árbol está vacío"
                            Sino
                                Escribir "Miembros registrados:"
                                Escribir "------------------------------------"
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] <> -1 Entonces
                                        Escribir "ID: ", arbolID[i], " - ", arbolNombre[i]
                                    FinSi
                                FinPara
                                Escribir "------------------------------------"
                                Escribir ""
                                
                                Escribir Sin Saltar "Ingrese ID a eliminar: "
                                Leer id
                                
                                encontrado <- Falso
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        encontrado <- Verdadero
                                        arbolID[i] <- -1
                                        Escribir ""
                                        Escribir "Miembro eliminado"
                                    FinSi
                                FinPara
                                
                                Si No encontrado Entonces
                                    Escribir "Miembro no encontrado"
                                FinSi
                            FinSi
                            Escribir ""
                            Escribir "Presione ENTER para continuar..."
                            Esperar Tecla
                    FinSegun
                Hasta Que subopcion = 4
                
            2:
                // RECORRIDOS DEL ÁRBOL
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
                    
                    Si subopcion <> 5 Entonces
                        Escribir ""
                        Si totalNodos = 0 Entonces
                            Escribir "El árbol está vacío"
                        Sino
                            Escribir "Función en desarrollo"
                        FinSi
                        Escribir ""
                        Escribir "Presione ENTER para continuar..."
                        Esperar Tecla
                    FinSi
                Hasta Que subopcion = 5
                
            3:
                // INFORMACIÓN DEL ÁRBOL
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
                    
                    Si subopcion <> 6 Entonces
                        Escribir ""
                        Escribir "Función en desarrollo"
                        Escribir ""
                        Escribir "Presione ENTER para continuar..."
                        Esperar Tecla
                    FinSi
                Hasta Que subopcion = 6
                
            4:
                // OPERACIONES AVANZADAS
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
                    
                    Si subopcion <> 6 Entonces
                        Escribir ""
                        Escribir "Función en desarrollo"
                        Escribir ""
                        Escribir "Presione ENTER para continuar..."
                        Esperar Tecla
                    FinSi
                Hasta Que subopcion = 6
                
            5:
                // SALIR
                Limpiar Pantalla
                Escribir ""
                Escribir "=========================================="
                Escribir "  Saliendo del sistema..."
                Escribir "  Hasta pronto!"
                Escribir "=========================================="
                Escribir ""
                
            De Otro Modo:
                Escribir ""
                Escribir "Opción no válida"
                Escribir ""
                Escribir "Presione ENTER para continuar..."
                Esperar Tecla
        FinSegun
        
    Hasta Que opcion = 5
    
FinAlgoritmo