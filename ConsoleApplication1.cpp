//Aplicación creada por Alejandro Bedoya Taborda y Cristian Camilo Henao Rojas
//Calculará la tangente x divido entra con una serie de Taylor

#include <iostream>
using namespace std;

int main()
{
    int dos = 2;
    int x;
    int m;
    int a;
    double resultado;

    cout << "Ingrese un numero x positivo menor a 100000: \n(Si ingresa un numero fuera del rango o un string el numero y el crapulo seran 0)" << endl;
    cin >> x;
    cout << "Ingrese un numero a positivo menor a 100000: \n(Si ingresa un numero fuera del rango o un string el numero y el crapulo seran 0)" << endl;
    cin >> a;
    cout << "Ingrese un numero m positivo menor a 100000: \n(Si ingresa un numero fuera del rango o un string el numero y el crapulo seran 0)" << endl;
    cin >> m;
    _asm {
        mov esi,0                       ;Se inicializa el registro para poder usar la pila de la FPU
        finit
        fild dos                        ;Se apila el numero dos para determinar si m es par
        fild m 
        fprem1                          ;Aqui se calcula m%2 y se apila
        fstp resultado                  ;Se desapila el residuo de m/2
        cmp resultado,0
        jnz par
        impar:                          ;Desde aqui empieza la ejecucion de la suma cuando m es impar
            mov cx,m                    ;Usaremos el for loop
            xor resultado,resultado     ;Se convierte el resultado en 0 para poder sumar sin ningun valor extra
        jmp fuera                       ;Se termina la ejecucion
        par:                            ;Se comienza la ejecucion de la suma si m es par
            mov cx, m                   ;Usaremos el for loop
        fuera:
        fwait
    }
    if (resultado==0)
    {
        cout << "el numero m es par "<<a;
    }
    else {
        cout << "el numero m es impar"<<a;
    }
    
    getchar();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
