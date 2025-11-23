class Nodo:
    """Cada nodo tiene un valor y dos hijos: izquierdo y derecho."""

    def __init__(self, valor):
        self.valor = valor
        self.izquierda = None
        self.derecha = None


class ArbolBinario:
    """Árbol de búsqueda binaria: menores a la izquierda, mayores a la derecha."""

    def __init__(self):
        self.raiz = None

    def insertar(self, valor):
        """Inserta un nuevo valor en el árbol."""
        if self.raiz is None:
            self.raiz = Nodo(valor)
        else:
            self._insertar_en(self.raiz, valor)

    def _insertar_en(self, nodo, valor):
        """Busca la posición correcta e inserta el valor."""
        if valor < nodo.valor:
            if nodo.izquierda is None:
                nodo.izquierda = Nodo(valor)
            else:
                self._insertar_en(nodo.izquierda, valor)
        elif valor > nodo.valor:
            if nodo.derecha is None:
                nodo.derecha = Nodo(valor)
            else:
                self._insertar_en(nodo.derecha, valor)

    def preorden(self, nodo, resultado):
        """Raíz -> Izquierda -> Derecha"""
        if nodo:
            resultado.append(nodo.valor)
            self.preorden(nodo.izquierda, resultado)
            self.preorden(nodo.derecha, resultado)

    def inorden(self, nodo, resultado):
        """Izquierda -> Raíz -> Derecha (orden ascendente)"""
        if nodo:
            self.inorden(nodo.izquierda, resultado)
            resultado.append(nodo.valor)
            self.inorden(nodo.derecha, resultado)

    def postorden(self, nodo, resultado):
        """Izquierda -> Derecha -> Raíz"""
        if nodo:
            self.postorden(nodo.izquierda, resultado)
            self.postorden(nodo.derecha, resultado)
            resultado.append(nodo.valor)

    def por_niveles(self):
        """Recorre el árbol nivel por nivel (de arriba hacia abajo)."""
        if not self.raiz:
            return []

        resultado = []
        cola = [self.raiz]

        while cola:
            nodo = cola.pop(0)
            resultado.append(nodo.valor)

            if nodo.izquierda:
                cola.append(nodo.izquierda)
            if nodo.derecha:
                cola.append(nodo.derecha)

        return resultado

    def dibujar(self):
        """Dibuja el árbol de forma visual usando matplotlib."""
        if not self.raiz:
            print("El árbol está vacío")
            return

        import matplotlib.pyplot as plt
        import matplotlib.patches as mpatches

        fig, ax = plt.subplots(figsize=(12, 8))
        ax.set_xlim(-1, 1)
        ax.set_ylim(-1, 0.1)
        ax.axis('off')

        def obtener_posiciones(nodo, x=0, y=0, nivel=1, pos_dict=None, ancho=1.0):
            """Calcula las posiciones de cada nodo en el árbol."""
            if pos_dict is None:
                pos_dict = {}

            if nodo is not None:
                pos_dict[id(nodo)] = (x, y)

                # Calcular el espaciado horizontal basado en el nivel
                dx = ancho / (2 ** nivel)

                # Procesar hijo izquierdo
                if nodo.izquierda:
                    obtener_posiciones(nodo.izquierda, x - dx, y - 0.15, nivel + 1, pos_dict, ancho)

                # Procesar hijo derecho
                if nodo.derecha:
                    obtener_posiciones(nodo.derecha, x + dx, y - 0.15, nivel + 1, pos_dict, ancho)

            return pos_dict

        def dibujar_nodo(nodo, posiciones):
            """Dibuja recursivamente los nodos y sus conexiones."""
            if nodo is None:
                return

            x, y = posiciones[id(nodo)]

            # Dibujar conexiones con los hijos
            if nodo.izquierda:
                x_izq, y_izq = posiciones[id(nodo.izquierda)]
                ax.plot([x, x_izq], [y, y_izq], 'k-', linewidth=2, zorder=1)
                dibujar_nodo(nodo.izquierda, posiciones)

            if nodo.derecha:
                x_der, y_der = posiciones[id(nodo.derecha)]
                ax.plot([x, x_der], [y, y_der], 'k-', linewidth=2, zorder=1)
                dibujar_nodo(nodo.derecha, posiciones)

            # Dibujar el nodo (círculo)
            circulo = mpatches.Circle((x, y), 0.04, color='lightblue',
                                      ec='darkblue', linewidth=2, zorder=2)
            ax.add_patch(circulo)

            # Dibujar el valor del nodo
            ax.text(x, y, str(nodo.valor), ha='center', va='center',
                    fontsize=12, fontweight='bold', zorder=3)

        # Obtener posiciones y dibujar
        posiciones = obtener_posiciones(self.raiz)
        dibujar_nodo(self.raiz, posiciones)

        plt.title('Visualización del Árbol Binario de Búsqueda',
                  fontsize=16, fontweight='bold', pad=20)
        plt.tight_layout()
        plt.show()
        print("✓ Árbol visualizado en ventana gráfica")


def main():
    arbol = ArbolBinario()

    while True:
        print("\n========== MENÚ ==========")
        print("1. Ingresar números")
        print("2. Dibujar árbol")
        print("3. Mostrar recorridos")
        print("4. Salir")
        print("==========================")

        opcion = input("Elige una opción: ").strip()

        if opcion == "1":
            numeros = input("Ingresa números separados por espacio: ").split()
            for num in numeros:
                try:
                    arbol.insertar(int(num))
                except ValueError:
                    print(f"'{num}' no es un número válido, se omite.")
            print(f"✓ Números insertados correctamente")

        elif opcion == "2":
            arbol.dibujar()

        elif opcion == "3":
            print("\n--- RECORRIDOS DEL ÁRBOL ---")

            resultado = []
            arbol.preorden(arbol.raiz, resultado)
            print(f"Preorden:     {resultado}")

            resultado = []
            arbol.inorden(arbol.raiz, resultado)
            print(f"Inorden:      {resultado}")

            resultado = []
            arbol.postorden(arbol.raiz, resultado)
            print(f"Postorden:    {resultado}")

            print(f"Por niveles:  {arbol.por_niveles()}")

        elif opcion == "4":
            print("¡Hasta luego!")
            break

        else:
            print("Opción no válida, intenta de nuevo.")


if __name__ == "__main__":
    main()