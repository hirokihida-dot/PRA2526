#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>


class SortingNet {
    
    private:

    std::vector <int> vectorEnteros;
    int tamanyoVector;
    std::vector<std::pair<int, int>> red; // Vector que almacena los pares de índices de los elementos a comparar en la red de ordenamiento;

    public:

    SortingNet (int tamanyoVector) : tamanyoVector(tamanyoVector) {}

    ~SortingNet() {}

    void inputKeyboard () {
        std::cout << "Introduzca los elementos del vector: " << std::endl;
        for (int i = 0; i < tamanyoVector; i++) {
            int elemento;
            std::cin >> elemento;
            vectorEnteros.push_back(elemento); //
        }
    }

    bool inputFile (const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error al abrir el archivo: " << filename << std::endl;
            return false;
        }
        
        int elemento;
        int contador = 0;

        while (file >> elemento) {
            vectorEnteros.push_back(elemento);
            contador++;
        }

        if (contador != tamanyoVector) {
            std::cout << "Error: el fichero debe contener exactamente " << tamanyoVector << " elementos." << std::endl;
            vectorEnteros.clear();
            return false;
        }
        return true;
    }

    void printVector () {
        for (int i = 0; i < tamanyoVector; i++) {
            std::cout << vectorEnteros[i] << " ";
        }
        std::cout << std::endl;
    }

    void swap (int i, int j) {
        int temp = vectorEnteros[i];
        vectorEnteros[i] = vectorEnteros[j];
        vectorEnteros[j] = temp;
    }

    void  cargarNet (const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error al abrir el archivo: " << filename << std::endl;
            return;
        }
        int i, j;                                       // Variables para almacenar temporalmente los índices de los elementos a comparar
        
        while (file >> i >> j) {
            if (i < 0 || i >= tamanyoVector || j < 0 || j >= tamanyoVector) {
                std::cerr << "Índices fuera de rango en el archivo: " << filename << std::endl;
                red.clear();  // Limpiar el vector red si hay un error
                return;
            }

            red.push_back({i, j});                      // Almacena el par de índices en el vector red           

        }
    }

    void sort () {
        for (auto& pair : red) {                        // Bucle que recorre cada par de índices en el vector red
            int i = pair.first;                         // Obtiene el primer índice del par
            int j = pair.second;                        // Obtiene el segundo índice del par
            if (vectorEnteros[i] > vectorEnteros[j]) {  // Compara los elementos en los índices i y j
                swap(i, j);                              // Si el elemento en i es mayor que el elemento en j, se intercambian
            }
        }
    }

};

int main() {

    int tamanyoVector = 6;
    int opcion = 0;

    SortingNet sortingNet(tamanyoVector);   // Crear una instancia de la clase SortingNet con el tamaño del vector

    std::cout << "\n¿Cómo quieres introducir el vector?\n";
    std::cout << "1. Por teclado\n";
    std::cout << "2. Desde fichero\n";
    std::cout << "Opción: ";
    std::cin >> opcion;

    if (opcion == 1) {
        sortingNet.inputKeyboard();  // Llamar al método para introducir el vector por teclado
    }

    else if (opcion == 2) {
        std::string vectorFilename;
        std::cout << "Introduzca el nombre del fichero: " << std::endl;
        std::cin >> vectorFilename;
        if (!sortingNet.inputFile(vectorFilename)){
            return 1;  // Salir del programa con un código de error si no se puede leer el fichero
        };  // Llamar al método para introducir el vector desde un fichero
    }

    else {
        std::cout << "Opción no válida. Saliendo del programa." << std::endl;
        return 1;  // Salir del programa con un código de error
    }

    std::cout << "Vector antes de ser ordenado: " << std::endl;
    sortingNet.printVector();  // Llamar al método para imprimir el vector antes de ordenar
    std::cout << "Introduzca el nombre del fichero que contiene la red de ordenamiento: " << std::endl;
    std::string netFilename;
    std::cin >> netFilename;
    sortingNet.cargarNet(netFilename);  // Llamar al método para cargar la red de ordenamiento desde un fichero
    sortingNet.sort();  // Llamar al método para ordenar el vector utilizando la red de ordenamiento
    std::cout << "Vector después de ser ordenado: " << std::endl;
    sortingNet.printVector();  // Llamar al método para imprimir el vector después de ordenar

    return 0;
}