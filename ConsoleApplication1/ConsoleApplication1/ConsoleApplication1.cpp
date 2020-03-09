//Aplicación creada por Alejandro Bedoya Taborda y Cristian Camilo Henao Rojas
//Calculará la tangente x divido entra con una serie de Taylor

#include <iostream>

using namespace std;

int main()
{
    int dos;
    int uno;
    int x;
    int n=0;
    int a;
    double resultado=0;
    int result;
    double atan=0;
    cout << "Ingrese un numero x positivo menor a 100000: " << endl;
    cin >> x;
    cout << "Ingrese un numero a positivo menor a 100000: " << endl;
    cin >> a;
    cout << "Ingrese un numero n positivo menor a 147: " << endl;
    cin >> n;


    _asm {
        mov uno,1                  ;Variable uno tiene el valor de 1, lo usaremos más tarde
        mov dos,2                  ;Varibale dos tiene el valor de 2, lo usaremos más tarde

        taylor:                    ;Aqui comienza la serie para calcular el atan(x/a)
            mov esi,0                  ;Inicializamos el registro de apuntadores                                
            finit                      ;Iniciamos el coprocesador
            cmp n,0                ;Se separa en cuando n>0 y n=0 que seria la ultima iteracion
            jnz suma               ;si n>0 se va a calcular la suma, sino a la sumatoria se le agregra a/x
            fld x                  ;Se apila x para dividir por a
            fld a                  ;Se apila a
            fdiv                   ;Se calcula x/a y se guarda en st(0)
            fld atan               ;Apilamos atan, que es el valor de la serie de 1 a n
            fadd                   ;Sumamos x/a a el valor de la serie que llevamos
            fstp atan              ;Se recupera el resultado listo para imprimir
            jmp fin                ;Se termina la serie, ya que en n=0, la expresion toma el valor de a/x

        suma:                      ;Sumatoria desde 1 hasta n
                mov eax, n         ;Iniciamos el calculo de 1 / (n*2 + 1)
                mov ebx, 2         ;Número que usaremos para multiplicar a n
                mul ebx            ;Multiplicamos n por 2
                inc eax            ;Le sumamos 1 a n*2
                mov result, eax    ;Guardamos el resultado de n*2+1 en result
                fld uno            ;Apilamos el número uno, el cual dividiremos n*2 + 1
                fld result         ;Apilamos n*2+1
                fdiv               ;Dividimos 1 sobre 2*n+1
                fstp resultado     ;Desapilamos el resultado de 1/(2*n+1).
                fstp st(0)         ;Desapilamos el tope de la pila, así preparamos la pila para la siguiente operación.
                mov ecx,result     ;Usaremos el ciclo for para hallar x^(2*n+1), hará 2*n+2 repeticiones

        powx:                      ;Aqui inicia el calculo de x^(2*n+1)
                    mov eax,x      ;Movemos al registro eax el valor de x para poder multiplicarlo despues
                    mul uno        ;Multiplicamos x por lo que hay en la variable uno, el resultado se guarda en eax
                    mov uno,eax    ;Movemos el resultado de uno*x a la variable uno.
                loop powx          ;Fin del calculo de x^(2*n+1)
                mov eax,uno        ;Sacamos el resultado de la variable uno para guardarlo en el registro eax
                mov ebx, x         ;Guardamos una copia en ebx del valor x para recupearlo después
                mov x,eax          ;x^(2*n+1) queda en x para usarlo despues en la division
                mov uno,1          ;La variable vuelve a su valor original
                mov ecx, result    ;Usaremos el ciclo for para hallar a^(2*n+1), hará 2*n+2 repeticiones

        powa:                      ;Es exactamente igual que powx, solo que esta vez se usara el valor de a
                    mov eax,a
                    mul uno                 
                    mov uno,eax
                loop powa          ;Aqui se acaba el calculo de a^(2*n+1)
                mov eax, uno       ;Sacamos el resultado de la variable uno para guardarlo en el registro eax
                mov edx, a         ;Guardamos una copia en edx del valor a para recupearlo después
                mov a, eax         ;a^(2*n+1) se guarda en la variable a para usarse en la division
                mov uno, 1         ;La variable uno toma su valor original (1)
                fld x              ;Añadimos x (x^(2*n+1)) a la pila 
                fld a              ;Añadimos a (a^(2*n+1)) a la pila
                fdiv               ;Dividimos x/a y el resultado queda en st(0)
                fld resultado      ;Apilamos resultado(1/(2*n+1))
                fmul               ;Multiplicamos st(0)*st(1)=(1/(2*n+1))*((x/a)^(2*n+1))
                fchs               ;Cambio el signo de la multiplicacion anteior, ahora queda negativa      
                fstp resultado     ;Guardo la -(1/(2*n+1))*((x/a)^(2*n+1)) en la variable resultado
                fild dos           ;Apilo el numero 2 para verificar si n es par o no
                fild n             ;Apilo n para sacarle el modulo con 2
                fprem1             ;Calculo m%2
                fstp result        ;Guardo el modulo en la variable result
                cmp result,0       ;Comparo el m%2 con 0
                jz par             ;Si el m%2 es 0, entonces es par
                fld resultado      ;Apilo el valor negativo que tengo en resultado
                fld atan           ;Apilo el valor que llevo de la serie de Taylor
                fadd               ;Resto (resultado es negativo) lo que llevo de la serie con el valor de resultado 
                fstp atan          ;Guardo el resultado en la variable atan
                jmp seguir         ;Aqui termina la iteracion y salta a reajustar algunos valores

        par:                       ;Instrucciones cuando n es par
                    fld atan       ;Apilo el valor de serie que se lleva hasta ahora
                    fld resultado  ;Apilo -(1/(2*n+1))*((x/a)^(2*n+1))
                    fabs           ;Le saco valor absoluto a -(1/(2*n+1))*((x/a)^(2*n+1))
                    fadd           ;Sumo lo que se lleva de la serie con (1/(2*n+1))*((x/a)^(2*n+1))
                    fstp atan      ;Se guarda el resultado de la suma en atan

        seguir:                    ;Aqui se termino de calcular el valor de enesima serie de Taylor
                    mov eax,n      ;Se empieza ajustando el valor n
                    dec eax        ;Se resta 1 al valor de n que esta guardado en eax
                    mov n,eax      ;Se guarda n-1 en n
                    mov x,ebx      ;Se recupera el valor x inicial
                    mov a,edx      ;Se recupera el valor a inicial
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
