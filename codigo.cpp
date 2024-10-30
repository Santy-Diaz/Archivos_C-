#include <iostream>
#include <locale>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include "membrete.h"

using namespace std;

void establecerColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void agregarTarea(const string& titulo, const string& descripcion) {
    ofstream archivo("tareas.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "T�tulo: " << titulo << ", Descripci�n: " << descripcion << endl;
        archivo.close();
        cout << "Tarea agregada correctamente." << endl;
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}

void mostrarTareas() {
    ifstream archivo("tareas.txt");
    string linea;
    cout << "Tareas registradas:" << endl;
    while (getline(archivo, linea)) {
        cout << "- " << linea << endl;
    }
    archivo.close();
}

void eliminarTarea(const string& titulo) {
    ifstream archivo("tareas.txt");
    ofstream archivoTemporal("temp.txt");
    string linea;

    bool encontrado = false;
    while (getline(archivo, linea)) {
        // Verificar si la l�nea contiene el t�tulo
        if (linea.find("T�tulo: " + titulo) == string::npos) {
            archivoTemporal << linea << endl; // Mantener la l�nea si no coincide
        } else {
            encontrado = true; // Marca que se encontr� la tarea
        }
    }
    archivo.close();
    archivoTemporal.close();

    remove("tareas.txt");
    rename("temp.txt", "tareas.txt");

    if (encontrado) {
        cout << "Tarea eliminada correctamente." << endl;
    } else {
        cout << "Tarea no encontrada." << endl;
    }
}

void menu() {
	setlocale(LC_ALL, "");

	int opcion;
	string titulo;
    string descripcion;
    membrete();
    
    do {
        establecerColor(11); // Color celeste
        cout << " \n*** Menu Principal *** " << endl;
        establecerColor(7); // Color blanco
        cout << "1. A�adir tarea" << endl;
        cout << "2. Mostrar tareas" << endl;
        cout << "3. Eliminar tarea" << endl;
        cout << "4. Salir" << endl;
        establecerColor(9); // Color azul claro 
        cout << " Elige una opcion: ";
        cin >> opcion;
        cin.ignore();
        establecerColor(7);
        system("cls");

        switch(opcion) {
            case 1: 
				cout << "T�tulo de la tarea: ";
                getline(cin, titulo);
                cout << "Descripci�n de la tarea: ";
                getline(cin, descripcion);
                agregarTarea(titulo, descripcion);
                system("pause");
                establecerColor(7);
                break;
        	case 2: 
				mostrarTareas();
                system("pause");
				establecerColor(7); 
				break;
            case 3: 
				cout << "Ingrese el t�tulo de la tarea a eliminar: ";
                getline(cin, titulo);
                eliminarTarea(titulo);
                system("pause");
                establecerColor(7);
                break;
            case 4:
                cout << "Saliendo del programa." << endl;
                establecerColor(7);
                break;
            default:
                cout << "Opci�n no v�lida. Intenta nuevamente." << endl;
                establecerColor(7);
                system("pause");
        }
        system("cls");
        membrete();
    } while (opcion != 4);
}

int main() {
    menu();
    return 0;
}
