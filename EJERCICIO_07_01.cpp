// Materia: Programación I, Paralelo 4

// Autor: Valentina Jazmin Angulo Burgoa

// Fecha creación: 20/11/2023

// Fecha modificación: 23/11/2023

// Número de ejericio: 1

// Problema planteado:PRÁCTICA 7
// ARCHIVOS BINARIOS
// Escribe un programa que tenga un menú de tres opciones:

// Ingreso de datos de los equipo de la LPFB.
// Ingreso los resultados de los partidos.
// Reporte de la tabla de posiciones
// Salir
// La primera opción debe ingresar los datos de los nombres de los equipos de la ligade acuerdo con la siguiente estructura y estos sean almacenados en un archivo binario llamado “EquiposLPFB.bin”, se debe considerar en no duplicar los equipos de futbol por el Nombre del Equipo
// struct structEquiposLPFB
// {
//     char nombreEquipo[50];
//     char colorCamiseta[50];
//     char departamento[30];
//     int anioCreacion;
// };
// La segunda opción debe ingresar los resultados de los partidos, que debe almacenarse en el archivo “ResultadosLPFB.bin” de acuerdo a la siguiente estructura, se debe considerer que solo se debe colocar resultados de los equipos ingresados en el archive “EquiposLPFB.bin”:
// struct structResultadosLPFB
// {
//     char nombreEquipoLocal[50];
//     char nombreEquipoVisitante[50];
//     int golesEquipoLocal;
//     Int golesEquipoVisitante;
//     char fechaPartido[10]
// };
// La tercera opción debe dar un reporte de la tabla de posiciones
// Club                   PJ        G      E     P      GF     GC     DG      Puntos
// 1 The Strongest         28       18     5     5      60     30     30        59
// 2 Bolivar               29       15     6     8      72     37     35        51
// 3 Always Ready          28       14     8     6      45     32     13        50
// 4 Nacional Potosi       28       14     6     8      59     38     21        48
// 5 Aurora                29       11     9     9      38     30      8        42
// 6 Real Santa Cruz       28       12     6    10      28     34     -6        42
// 7 Real Tomayapo         28       10     10    8      28     29     -1        40
// 8 Wilsterman            28       11     11    6      37     23     14        38

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct structEquiposLPFB
{
    char nombreEquipo[50];
    char colorCamiseta[50];
    char departamento[30];
    int anioCreacion;
};

struct structResultadosLPFB
{
    char nombreEquipoLocal[50];
    char nombreEquipoVisitante[50];
    int golesEquipoLocal;
    int golesEquipoVisitante;
    char fechaPartido[10];
};

void ingresarEquipos() {
    structEquiposLPFB equipo;
    ofstream archivoEquipos("EquiposLPFB.bin", ios::binary | ios::app);

    cout << "Ingreso de datos de equipos:" << endl;

    cout << "Nombre del equipo: ";
    cin.ignore();
    cin.getline(equipo.nombreEquipo, sizeof(equipo.nombreEquipo));

    // Validar que no se dupliquen los equipos (esto es un ejemplo básico)
    ifstream verificarDuplicado("EquiposLPFB.bin", ios::binary);
    while (verificarDuplicado.read(reinterpret_cast<char*>(&equipo), sizeof(equipo))) {
        if (strcmp(equipo.nombreEquipo, equipo.nombreEquipo) == 0) {
            cout << "Error: Este equipo ya existe." << endl;
            verificarDuplicado.close();
            return;
        }
    }
    verificarDuplicado.close();

    cout << "Color de la camiseta: ";
    cin.getline(equipo.colorCamiseta, sizeof(equipo.colorCamiseta));

    cout << "Departamento: ";
    cin.getline(equipo.departamento, sizeof(equipo.departamento));

    cout << "Año de creación: ";
    cin >> equipo.anioCreacion;

    archivoEquipos.write(reinterpret_cast<char*>(&equipo), sizeof(equipo));
    archivoEquipos.close();
}

void ingresarResultados() {
    structResultadosLPFB resultado;
    ifstream archivoEquipos("EquiposLPFB.bin", ios::binary);
    ofstream archivoResultados("ResultadosLPFB.bin", ios::binary | ios::app);

    cout << "Ingreso de resultados de partidos:" << endl;

    cout << "Nombre del equipo local: ";
    cin.ignore();
    cin.getline(resultado.nombreEquipoLocal, sizeof(resultado.nombreEquipoLocal));

    // Validar que el equipo local exista en el archivo de equipos
    bool equipoLocalValido = false;
    structEquiposLPFB equipo;
    while (archivoEquipos.read(reinterpret_cast<char*>(&equipo), sizeof(equipo))) {
        if (strcmp(equipo.nombreEquipo, resultado.nombreEquipoLocal) == 0) {
            equipoLocalValido = true;
            break;
        }
    }
    archivoEquipos.close();

    if (!equipoLocalValido) {
        cout << "Error: El equipo local no existe." << endl;
        return;
    }

    cout << "Nombre del equipo visitante: ";
    cin.getline(resultado.nombreEquipoVisitante, sizeof(resultado.nombreEquipoVisitante));

    // Validar que el equipo visitante exista en el archivo de equipos
    bool equipoVisitanteValido = false;
    archivoEquipos.open("EquiposLPFB.bin", ios::binary);
    while (archivoEquipos.read(reinterpret_cast<char*>(&equipo), sizeof(equipo))) {
        if (strcmp(equipo.nombreEquipo, resultado.nombreEquipoVisitante) == 0) {
            equipoVisitanteValido = true;
            break;
        }
    }
    archivoEquipos.close();

    if (!equipoVisitanteValido) {
        cout << "Error: El equipo visitante no existe." << endl;
        return;
    }

    cout << "Goles del equipo local: ";
    cin >> resultado.golesEquipoLocal;

    cout << "Goles del equipo visitante: ";
    cin >> resultado.golesEquipoVisitante;

    cout << "Fecha del partido (formato DD/MM/AAAA): ";
    cin.ignore();
    cin.getline(resultado.fechaPartido, sizeof(resultado.fechaPartido));

    archivoResultados.write(reinterpret_cast<char*>(&resultado), sizeof(resultado));
    archivoResultados.close();
}

void generarReporte() {
    structResultadosLPFB resultado;
    structEquiposLPFB equipo;
    ifstream archivoResultados("ResultadosLPFB.bin", ios::binary);
    ifstream archivoEquipos("EquiposLPFB.bin", ios::binary);

    // Lógica para generar el reporte de la tabla de posiciones
    // (implementa según tus necesidades específicas)

    archivoResultados.close();
    archivoEquipos.close();
}

int main() {
    int opcion;

    do {
        cout << "\nMenú de opciones:" << endl;
        cout << "1. Ingreso de datos de los equipos de la LPFB." << endl;
        cout << "2. Ingreso de resultados de los partidos." << endl;
        cout << "3. Reporte de la tabla de posiciones." << endl;
        cout << "4. Salir." << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                ingresarEquipos();
                break;
            case 2:
                ingresarResultados();
                break;
            case 3:
                generarReporte();
                break;
            case 4:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }

    } while (opcion != 4);

    return 0;
}
