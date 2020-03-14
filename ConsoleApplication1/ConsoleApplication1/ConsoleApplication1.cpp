//Aplicación creada por Alejandro Bedoya Taborda y Cristian Camilo Henao Rojas
//Calculará la tangente x divido entra con una serie de Taylor

#include <iostream>

using namespace std;

int main()
{
    double auxi = 0.0;
    double dos=2.0;
    double uno=1.0;
    double x=0.0;
    int n=0;
    double a=0.0;
    double resultado=0.0;
    int result=0;
    double atan=0.0;
    cout << "Ingrese un numero x positivo menor a 100000: " << endl;
    cin >> x;
    cout << "Ingrese un numero a positivo menor a 100000: " << endl;
    cin >> a;
    cout << "Ingrese un numero n positivo menor a 147: " << endl;
    cin >> n;


    _asm {
        taylor:                    ;Aqui comienza la serie para calcular el atan(x/a)
            mov esi,0                  
            cmp n,0                ;Se separa en cuando n>0 y n=0 que seria la ultima iteracion
            jnz suma               ;si n>0 se va a calcular la suma, sino a la sumatoria se le agrega a/x
            fld x                 
            fld a                  
            fdiv                   ;Se calcula x/a y se guarda en st(0)
            fld atan               ;Apilamos atan, que es el valor de la serie de 1 a n
            fadd                   
            fstp atan              ;Se recupera el resultado listo para imprimir
            jmp fin                ;Se termina la serie, ya que en n=0, la expresion toma el valor de a/x

        suma:                      ;Sumatoria desde 1 hasta n
                mov eax, n         ;Iniciamos el calculo de 1 / (n*2 + 1)
                mov ebx, 2         ;Número que usaremos para multiplicar a n
                mul ebx                
                mov result, eax    ;Guardamos el resultado de n*2 en result
                fild n
                fmul dos
                fstp auxi          
                fld auxi
                fld uno
                fadd
                fstp resultado     ;En resultado esta guardado 2*n+1               
                fstp st(0)         ;Desapilamos el tope de la pila, así preparamos la pila para la siguiente operación.
                fld x              ;Se apila x para dividir por a
                fld a              ;Se apila a
                fdiv               
                fstp auxi          ;Se guarda x/a en auxi
                mov ecx,result     ;Usaremos un ciclo para hallar (x/a)^(2*n+1), hará 2*n+1 repeticiones
                fld auxi           ;Apilamos x/a para hallar la potencia

        powax:                      ;Aqui inicia el calculo de la potencia              
                    jecxz finpowax
                    fmul auxi           
                    dec ecx
                    jmp powax
        finpowax:

                fstp auxi          ;En auxi queda guardado(x / a) ^ (2 * n + 1)
                fld auxi
                fld resultado      ;Apilamos resultado (2*n+1) 
                fdiv                    
                fstp resultado     ;Guardo (1/(2*n+1))*((x/a)^(2*n+1)) en la variable resultado
                fld dos            ;Apilo el numero 2 para verificar si n es par o no
                fild n             
                fprem1             
                fstp result        ;Guardo el modulo en la variable result
                cmp result,0       
                jz par             
                fld atan           ;Apilo el valor que llevo de la serie de Taylor
                fld resultado                     
                fsub                
                fstp atan          ;Guardo el resultado en la variable atan
                jmp seguir         ;Aqui termina la iteracion y salta a reajustar algunos valores

        par:                       ;Instrucciones cuando n es par
                    fld atan       ;Apilo el valor de serie que se lleva hasta ahora
                    fld resultado  
                    fadd           
                    fstp atan      ;Guardo el resultado en la variable atan

        seguir:                    ;Aqui se termina de calcular el valor de enesima serie de Taylor
                    
                    sub n, 1
                    jmp taylor     ;Si n>=0, salta a hacer otra enesima serie de Taylor

        fin:                       ;Se acaba el calculo y el valor queda guardado en atan
        fwait
    }

    cout << "El valor de atan(x/a) es: " << atan << endl;
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
