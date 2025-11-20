// ÁRBOL GENEALÓGICO - VERSIÓN COMPRIMIDA
Algoritmo ArbolGenealogico
    Definir opcion, subopcion, id, anio, totalNodos Como Entero
    Definir nombre, genero, rol Como Cadena
    Dimension arbolID[100], arbolNombre[100], arbolAnio[100]
    Dimension arbolGenero[100], arbolRol[100]
    Dimension arbolIzq[100], arbolDer[100], arbolPadre[100]
    totalNodos <- 0
    Para i <- 1 Hasta 100 Hacer
        arbolID[i] <- -1
        arbolIzq[i] <- -1
        arbolDer[i] <- -1
        arbolPadre[i] <- -1
    FinPara
    
    Repetir
        Limpiar Pantalla
        Escribir "===== ÁRBOL GENEALÓGICO ====="
        Escribir "1. Gestión de Miembros"
        Escribir "2. Recorridos del Árbol"
        Escribir "3. Información del Árbol"
        Escribir "4. Operaciones Avanzadas"
        Escribir "5. Salir"
        Leer opcion
        
        Segun opcion Hacer
            1: // GESTIÓN
                Repetir
                    Limpiar Pantalla
                    Escribir "1. Insertar | 2. Buscar | 3. Eliminar | 4. Volver"
                    Leer subopcion
                    Segun subopcion Hacer
                        1: // INSERTAR
						Escribir "ID: "; Leer id
						Escribir "Nombre: "; Leer nombre
						Escribir "Año: "; Leer anio
						Escribir "Género (M/F): "; Leer genero
						Escribir "Rol: "; Leer rol
                            Si totalNodos = 0 Entonces
                                totalNodos <- 1
                                arbolID[1] <- id
                                arbolNombre[1] <- nombre
                                arbolAnio[1] <- anio
                                arbolGenero[1] <- genero
                                arbolRol[1] <- rol
                                arbolPadre[1] <- 0
                                Escribir "Insertado como raíz"
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
                                Escribir "Insertado"
                            FinSi
                            Esperar Tecla
                        2: // BUSCAR
                            Si totalNodos = 0 Entonces
                                Escribir "Árbol vacío"
                            Sino
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] <> -1 Entonces
                                        Escribir "ID: ", arbolID[i], " - ", arbolNombre[i]
                                    FinSi
                                FinPara
							Escribir "Buscar ID: "; Leer id
                                encontrado <- Falso
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        Escribir "ID: ", arbolID[i], " | Nombre: ", arbolNombre[i], " | Año: ", arbolAnio[i], " | Género: ", arbolGenero[i], " | Rol: ", arbolRol[i]
                                        encontrado <- Verdadero
                                    FinSi
                                FinPara
                                Si No encontrado Entonces
                                    Escribir "No encontrado"
                                FinSi
                            FinSi
                            Esperar Tecla
                        3: // ELIMINAR
                            Si totalNodos = 0 Entonces
                                Escribir "Árbol vacío"
                            Sino
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] <> -1 Entonces
                                        Escribir "ID: ", arbolID[i], " - ", arbolNombre[i]
                                    FinSi
                                FinPara
							Escribir "Eliminar ID: "; Leer id
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        arbolID[i] <- -1
                                        Escribir "Eliminado"
                                    FinSi
                                FinPara
                            FinSi
                            Esperar Tecla
                    FinSegun
                Hasta Que subopcion = 4
                
            2: // RECORRIDOS
                Repetir
                    Limpiar Pantalla
                    Escribir "1. Inorden | 2. Preorden | 3. Postorden | 4. Por Niveles | 5. Volver"
                    Leer subopcion
                    Si subopcion >= 1 Y subopcion <= 4 Y totalNodos > 0 Entonces
                        Segun subopcion Hacer
                            1: // INORDEN
                                Escribir "Inorden: "
                                Dimension visitado[100]
                                Para i <- 1 Hasta 100 Hacer
                                    visitado[i] <- Falso
                                FinPara
                                nodosImpresos <- 0
                                Mientras nodosImpresos < totalNodos Hacer
                                    menorID <- 999999
                                    indiceMinimo <- -1
                                    Para i <- 1 Hasta totalNodos Hacer
                                        Si arbolID[i] <> -1 Y No visitado[i] Y arbolID[i] < menorID Entonces
                                            menorID <- arbolID[i]
                                            indiceMinimo <- i
                                        FinSi
                                    FinPara
                                    Si indiceMinimo <> -1 Entonces
                                        Escribir Sin Saltar arbolID[indiceMinimo], " "
                                        visitado[indiceMinimo] <- Verdadero
                                        nodosImpresos <- nodosImpresos + 1
                                    FinSi
                                FinMientras
                                Escribir ""
                            2: // PREORDEN
                                Escribir "Preorden: "
                                Dimension pila[100]
                                topePila <- 1
                                pila[1] <- 1
                                Mientras topePila > 0 Hacer
                                    actual <- pila[topePila]
                                    topePila <- topePila - 1
                                    Escribir Sin Saltar arbolID[actual], " "
                                    Si arbolDer[actual] <> -1 Entonces
                                        topePila <- topePila + 1
                                        pila[topePila] <- arbolDer[actual]
                                    FinSi
                                    Si arbolIzq[actual] <> -1 Entonces
                                        topePila <- topePila + 1
                                        pila[topePila] <- arbolIzq[actual]
                                    FinSi
                                FinMientras
                                Escribir ""
                            3: // POSTORDEN
                                Escribir "Postorden: "
                                Para i <- totalNodos Hasta 1 Con Paso -1 Hacer
                                    Si arbolID[i] <> -1 Entonces
                                        Escribir Sin Saltar arbolID[i], " "
                                    FinSi
                                FinPara
                                Escribir ""
                            4: // POR NIVELES
                                Escribir "Por Niveles: "
                                Dimension cola[100]
                                inicioCola <- 1
                                finCola <- 1
                                cola[1] <- 1
                                Mientras inicioCola <= finCola Hacer
                                    actual <- cola[inicioCola]
                                    inicioCola <- inicioCola + 1
                                    Escribir Sin Saltar arbolID[actual], " "
                                    Si arbolIzq[actual] <> -1 Entonces
                                        finCola <- finCola + 1
                                        cola[finCola] <- arbolIzq[actual]
                                    FinSi
                                    Si arbolDer[actual] <> -1 Entonces
                                        finCola <- finCola + 1
                                        cola[finCola] <- arbolDer[actual]
                                    FinSi
                                FinMientras
                                Escribir ""
                        FinSegun
                        Esperar Tecla
                    FinSi
                Hasta Que subopcion = 5
                
            3: // INFORMACIÓN
                Repetir
                    Limpiar Pantalla
                    Escribir "1. Altura | 2. Raíz | 3. Hojas | 4. Internos | 5. Peso | 6. Volver"
                    Leer subopcion
                    Segun subopcion Hacer
                        1: // ALTURA
                            Si totalNodos = 0 Entonces
                                Escribir "Altura = 0"
                            Sino
                                Dimension nivelNodo[100]
                                Para i <- 1 Hasta 100 Hacer
                                    nivelNodo[i] <- -1
                                FinPara
                                nivelNodo[1] <- 0
                                alturaMaxima <- 0
                                Dimension cola[100]
                                inicioCola <- 1
                                finCola <- 1
                                cola[1] <- 1
                                Mientras inicioCola <= finCola Hacer
                                    actual <- cola[inicioCola]
                                    inicioCola <- inicioCola + 1
                                    Si nivelNodo[actual] > alturaMaxima Entonces
                                        alturaMaxima <- nivelNodo[actual]
                                    FinSi
                                    Si arbolIzq[actual] <> -1 Entonces
                                        finCola <- finCola + 1
                                        cola[finCola] <- arbolIzq[actual]
                                        nivelNodo[arbolIzq[actual]] <- nivelNodo[actual] + 1
                                    FinSi
                                    Si arbolDer[actual] <> -1 Entonces
                                        finCola <- finCola + 1
                                        cola[finCola] <- arbolDer[actual]
                                        nivelNodo[arbolDer[actual]] <- nivelNodo[actual] + 1
                                    FinSi
                                FinMientras
                                Escribir "Altura: ", alturaMaxima
                            FinSi
                            Esperar Tecla
                        2: // RAÍZ
                            Si totalNodos = 0 Entonces
                                Escribir "Árbol vacío"
                            Sino
                                Escribir "Raíz: ", arbolID[1], " - ", arbolNombre[1]
                            FinSi
                            Esperar Tecla
                        3: // HOJAS
                            Si totalNodos = 0 Entonces
                                Escribir "Árbol vacío"
                            Sino
                                Escribir "Hojas: "
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] <> -1 Y arbolIzq[i] = -1 Y arbolDer[i] = -1 Entonces
                                        Escribir Sin Saltar arbolID[i], " "
                                    FinSi
                                FinPara
                                Escribir ""
                            FinSi
                            Esperar Tecla
                        4: // INTERNOS
                            Si totalNodos <= 1 Entonces
                                Escribir "Sin nodos internos"
                            Sino
                                Escribir "Internos: "
                                Para i <- 2 Hasta totalNodos Hacer
                                    Si arbolID[i] <> -1 Y (arbolIzq[i] <> -1 O arbolDer[i] <> -1) Entonces
                                        Escribir Sin Saltar arbolID[i], " "
                                    FinSi
                                FinPara
                                Escribir ""
                            FinSi
                            Esperar Tecla
                        5: // PESO
                            peso <- 0
                            Para i <- 1 Hasta totalNodos Hacer
                                Si arbolID[i] <> -1 Entonces
                                    peso <- peso + 1
                                FinSi
                            FinPara
                            Escribir "Peso: ", peso
                            Esperar Tecla
                    FinSegun
                Hasta Que subopcion = 6
                
            4: // OPERACIONES AVANZADAS
                Repetir
                    Limpiar Pantalla
                    Escribir "1. Camino | 2. Long. Camino | 3. Altura Nodo | 4. Nivel | 5. Volver"
                    Leer subopcion
                    Segun subopcion Hacer
                        1: // CAMINO
                            Si totalNodos > 0 Entonces
							Escribir "ID: "; Leer id
                                indiceDestino <- -1
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        indiceDestino <- i
                                    FinSi
                                FinPara
                                Si indiceDestino <> -1 Entonces
                                    Dimension camino[100]
                                    longitudCamino <- 0
                                    actual <- indiceDestino
                                    Mientras actual <> 0 Hacer
                                        longitudCamino <- longitudCamino + 1
                                        camino[longitudCamino] <- arbolID[actual]
                                        actual <- arbolPadre[actual]
                                    FinMientras
                                    Escribir "Camino: "
                                    Para i <- longitudCamino Hasta 1 Con Paso -1 Hacer
                                        Escribir Sin Saltar camino[i]
                                        Si i > 1 Entonces
                                            Escribir Sin Saltar " -> "
                                        FinSi
                                    FinPara
                                    Escribir ""
                                FinSi
                            FinSi
                            Esperar Tecla
                        2: // LONGITUD
                            Si totalNodos > 0 Entonces
							Escribir "ID: "; Leer id
                                indiceNodo <- -1
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        indiceNodo <- i
                                    FinSi
                                FinPara
                                Si indiceNodo <> -1 Entonces
                                    longitudCamino <- 0
                                    actual <- indiceNodo
                                    Mientras actual <> 1 Y actual <> 0 Hacer
                                        longitudCamino <- longitudCamino + 1
                                        actual <- arbolPadre[actual]
                                    FinMientras
                                    Escribir "Longitud: ", longitudCamino
                                FinSi
                            FinSi
                            Esperar Tecla
                        3: // ALTURA NODO
                            Si totalNodos > 0 Entonces
							Escribir "ID: "; Leer id
                                indiceNodo <- -1
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        indiceNodo <- i
                                    FinSi
                                FinPara
                                Si indiceNodo <> -1 Entonces
                                    Dimension cola[100], nivelDesdeNodo[100]
                                    Para i <- 1 Hasta 100 Hacer
                                        nivelDesdeNodo[i] <- -1
                                    FinPara
                                    inicioCola <- 1
                                    finCola <- 1
                                    cola[1] <- indiceNodo
                                    nivelDesdeNodo[indiceNodo] <- 0
                                    alturaMaxima <- 0
                                    Mientras inicioCola <= finCola Hacer
                                        actual <- cola[inicioCola]
                                        inicioCola <- inicioCola + 1
                                        Si nivelDesdeNodo[actual] > alturaMaxima Entonces
                                            alturaMaxima <- nivelDesdeNodo[actual]
                                        FinSi
                                        Si arbolIzq[actual] <> -1 Entonces
                                            finCola <- finCola + 1
                                            cola[finCola] <- arbolIzq[actual]
                                            nivelDesdeNodo[arbolIzq[actual]] <- nivelDesdeNodo[actual] + 1
                                        FinSi
                                        Si arbolDer[actual] <> -1 Entonces
                                            finCola <- finCola + 1
                                            cola[finCola] <- arbolDer[actual]
                                            nivelDesdeNodo[arbolDer[actual]] <- nivelDesdeNodo[actual] + 1
                                        FinSi
                                    FinMientras
                                    Escribir "Altura: ", alturaMaxima
                                FinSi
                            FinSi
                            Esperar Tecla
                        4: // NIVEL
                            Si totalNodos > 0 Entonces
							Escribir "ID: "; Leer id
                                indiceNodo <- -1
                                Para i <- 1 Hasta totalNodos Hacer
                                    Si arbolID[i] = id Entonces
                                        indiceNodo <- i
                                    FinSi
                                FinPara
                                Si indiceNodo <> -1 Entonces
                                    nivel <- 0
                                    actual <- indiceNodo
                                    Mientras actual <> 1 Y actual <> 0 Hacer
                                        nivel <- nivel + 1
                                        actual <- arbolPadre[actual]
                                    FinMientras
                                    Escribir "Nivel: ", nivel
                                FinSi
                            FinSi
                            Esperar Tecla
                    FinSegun
                Hasta Que subopcion = 5
                
            5:
                Escribir "¡Hasta pronto!"
        FinSegun
    Hasta Que opcion = 5
FinAlgoritmo