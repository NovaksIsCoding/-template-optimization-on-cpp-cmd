#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>

using namespace std;

// Función para simular una pausa aleatoria
void pausaAleatoria() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribucion(500, 2000);
    int tiempo = distribucion(gen);
    cout << "Realizando pausa de " << tiempo << " milisegundos..." << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(tiempo));
}

// Funciones para las tareas
void liberarMemoriaRAM() {
    cout << "Liberando memoria RAM..." << endl;
    pausaAleatoria();
}

void limpiarArchivosTemporales() {
    cout << "Limpiando archivos temporales..." << endl;
    pausaAleatoria();
}

void desfragmentarDiscoDuro() {
    cout << "Desfragmentando el disco duro..." << endl;
    pausaAleatoria();
}

void borrarLogs() {
    cout << "Borrando logs..." << endl;
    pausaAleatoria();
}

// Función para mostrar el menú
void mostrarMenu(const vector<pair<string, function<void()>>>& opciones) {
    cout << "#           MENU DE OPCIONES:                 #" << endl;
    cout << "\033[0m";

    for (int i = 0; i < opciones.size(); i++) {
        cout << "# " << i + 1 << ". " << opciones[i].first;
        cout << string(40 - opciones[i].first.length(), ' ');
        cout << "#" << endl;
    }

    cout << "##############################################" << endl;
    cout << "\033[1;33m#   Seleccione una opción:                   #\n\033[0m";
}

int main() {
    vector<pair<string, function<void()>>> opciones = {
        {"Liberar memoria RAM", liberarMemoriaRAM},
        {"Limpiar archivos temporales", limpiarArchivosTemporales},
        {"Desfragmentar el disco duro", desfragmentarDiscoDuro},
        {"Borrar logs", borrarLogs},
        {"Salir", nullptr}
    };

    while (true) {
        mostrarMenu(opciones);

        int opcionSeleccionada;
        cin >> opcionSeleccionada;

        // Limpiar pantalla antes de la validación de entrada
        //system("clear"); // En Unix/Linux
        system("cls"); // En Windows

        // Validar entrada del usuario
        while (opcionSeleccionada <= 0 || opcionSeleccionada > opciones.size()) {
            cout << "\033[1;31mOpción inválida. Intente de nuevo.\033[0m\n" << endl;
            mostrarMenu(opciones);
            cin >> opcionSeleccionada;
        }

        auto opcion = opciones[opcionSeleccionada - 1];
        if (opcion.second == nullptr) {
            cout << "\033[1;33mSaliendo del programa...\033[0m\n" << endl;
            break;
        }

        cout << "\033[1;36m" << opcion.first << "...\033[0m" << endl;
        opcion.second();
        cout << "\033[1;32m" << opcion.first << " completado exitosamente.\033[0m\n" << endl;

        // Pausa para que el usuario pueda leer el resultado de la tarea
        this_thread::sleep_for(chrono::seconds(2));

        // Borrar pantalla y mostrar menú nuevamente
        //system("clear"); // En Unix/Linux
        system("cls"); // En Windows
    }


    return 0;
}

