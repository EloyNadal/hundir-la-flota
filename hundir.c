#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//Constante que determina el tamaño del tablero de juego(Matriz DIMxDIM)
#define DIM 11
//Vector que contiene la cantidad de barcos segun su tamaño. El tamaño vendrà dado por la posicion en el vector y la cantidad de
//barcos por el numero que se encuentra en la posicion. P. ej.: barcos[1] --> 4 barcos de 1 casilla.
#define BARCOS {0,4,3,2,1}
//Constante con la cantidad de barcos diferentes que hay mas uno ya que la posicion '0' no se utilizara.
#define DIFBARCOS 5
#define TOTALBARCOS 10


//Declaracion funcion para colocar barcos
void colocarBarcos(int posi1, int posi2, int posj1, int posj2, char mat[DIM][DIM], int vbarcos[])
{
    int i, j, cont;
    cont=0;
    if(posi1==posi2)
    {
        i=posi1;
        for(j=posj1; j<=posj2; j++)
        {
            mat[i][j]='O';
            cont++;
        }
    }
    else
    {
        j=posj1;
        for(i=posi1; i<=posi2; i++)
        {
            mat[i][j]='O';
            cont++;
        }
    }
    vbarcos[cont]=vbarcos[cont]-1;
}
//Declaracion funcion para comprobar la disponibilidad de la posicion elegida para el barco.
int espacioDispo(int posi1, int posi2, int posj1, int posj2, char mat[DIM][DIM])
{
    int i, j;

    for(i=posi1; i<=posi2; i++)
    {
        for(j=posj1; j<=posj2; j++)
        {
            if(mat[i][j]!=' ')
            {
                return -1;
            }
        }
    }
    return 1;
}
//Declaracion funcion para traducir la letra del eje "y" en un numero para movernos por la matriz.
int letraxnum(char letra)
{
    switch (tolower(letra))
    {
    case 'a':
        return 1;
    case 'b':
        return 2;
    case 'c':
        return 3;
    case 'd':
        return 4;
    case 'e':
        return 5;
    case 'f':
        return 6;
    case 'g':
        return 7;
    case 'h':
        return 8;
    case 'i':
        return 9;
    case 'j':
        return 10;
    default:
        return -1;
    }
}

//Declaracion funcion para dejar libres las casillas alrededor del barco. Las rellenaremos con "agua".
//Llamamos a la funcion con la posicion inicial y final del barco junto con la matriz del jugador.
void agua(int posi1, int posi2, int posj1, int posj2, char mat[DIM][DIM])
{
    int i,j;

    for(i=(posi1-1); i<(posi2+2); i++)
    {
        if(i>0 && i<DIM)
        {
            for(j=(posj1-1); j<(posj2+2); j++)
            {
                if (j>0 && j<DIM)
                {
                    if(posi1==posi2)
                    {
                        if(i!=posi1 || j<posj1 || j>posj2)
                        {
                            mat[i][j]='~';
                        }
                    }
                    else
                    {
                        if(j!=posj1 || i<posi1 || i>posi2)
                        {
                            mat[i][j]='~';
                        }
                    }
                }
            }
        }
    }
}

//Declaracion funcion para comprobar que la posicion elegida para el barco esta dentro del tablero.

int posicionEnTablero(int posi1, int posi2, int posj1, int posj2)
{
    if(posi1==-1||posi2==-1)
    {
        return -1;
    }
    if(posi1!=posi2 && posj1!=posj2)
    {
        return -2;
    }
    if(posj1<1||posj1>10||posj2<1||posj2>10)
    {
        return -1;
    }
    return 1;
}


//Declaracion funcion para la creacion de los tableros de juego en blanco.
void crearTablero(char mat[DIM][DIM])
{
    int i,j;
    mat[0][0]=' ';
    mat[0][1]='1';
    mat[0][2]='2';
    mat[0][3]='3';
    mat[0][4]='4';
    mat[0][5]='5';
    mat[0][6]='6';
    mat[0][7]='7';
    mat[0][8]='8';
    mat[0][9]='9';
    mat[0][10]='0';
    mat[1][0]='A';
    mat[2][0]='B';
    mat[3][0]='C';
    mat[4][0]='D';
    mat[5][0]='E';
    mat[6][0]='F';
    mat[7][0]='G';
    mat[8][0]='H';
    mat[9][0]='I';
    mat[10][0]='J';
    for (i=1; i<DIM; i++)
    {
        for (j=1; j<DIM; j++)
        {
            mat[i][j]=' ';
        }
    }
}
void mostrar(char mat[DIM][DIM])
{
    int i, j;
    for (i=0; i<DIM; i++)
    {
        printf("\t\t\t\t");
        for (j=0; j<DIM; j++)
        {
            printf("%c  ", mat[i][j]);
        }
        printf("\n");
    }
}

void rellenarAgua(char mat[DIM][DIM])
{
    int i, j;
    for(i=1; i<DIM; i++)
    {
        for(j=1; j<DIM; j++)
        {
            if(mat[i][j]==' ')
            {
                mat[i][j]='~';
            }
        }
    }
}
int comprobarBarco(int posi1, int posi2, int posj1, int posj2, int barcos[])
{
    int i, j, tamano;
    if (posi1 == posi2)
    {
        tamano = posj2 - posj1 + 1;
    }
    else
    {
        tamano = posi2 - posi1 + 1;
    }
    if (tamano > 5)
    {
        return (-1);
    }
    else
    {
        if (barcos[tamano] != 0)
        {
            return (1);
        }
        else
        {
            return (-2);
        }
    }
}
int tocadoHundido(int posi, int posj, char mat[DIM][DIM])
{
    int i, j;
    i=posi;
    j=posj;
    while(i>0&&mat[i][j]=='X')
    {
        i--;
    }
    if(i>0)
    {
        if(mat[i][j]=='O')
        {
            return 1;
        }
    }
    i=posi;
    while(i<(DIM-1)&&mat[i][j]=='X')
    {
        i++;
    }
    if(i<DIM)
    {
        if(mat[i][j]=='O')
        {
            return 1;
        }
    }
    i=posi;
    while(j>0&&mat[i][j]=='X')
    {
        j--;
    }
    if(j>0)
    {
        if(mat[i][j]=='O')
        {
            return 1;
        }
    }
    j=posj;
    while(j<(DIM-1)&&mat[i][j]=='X')
    {
        i++;
    }
    if(i<DIM)
    {
        if(mat[i][j]=='O')
        {
            return 1;
        }
    }
    return 2;
}
int disparo(int posi, int posj, char mat1[DIM][DIM], char mat2[DIM][DIM])
{
    int x;
    if(mat1[posi][posj]=='O')
    {
        mat1[posi][posj]='X';
        mat2[posi][posj]='X';
        x=tocadoHundido(posi, posj, mat1);
    }
    else
    {
        mat2[posi][posj]='~';
        x=-1;
    }
    return x;
}

void main()
{
    char tablero1A[DIM][DIM], tablero2A[DIM][DIM],tablero1B[DIM][DIM],tablero2B[DIM][DIM];
    int posi1, posi2, posj1, posj2, posOk, barcOk;
    int x, aux, totbarcosj1, totbarcosj2;
    char letra;
    int barcosJugador1[DIFBARCOS]=BARCOS, barcosJugador2[DIFBARCOS]=BARCOS;
    totbarcosj1=0;
    totbarcosj2=0;
    crearTablero(tablero1A);
    crearTablero(tablero2A);
    crearTablero(tablero1B);
    crearTablero(tablero2B);
    printf("Inicio primer jugador.\n");
    while(totbarcosj1!=TOTALBARCOS)
    {
        do
        {
            printf("Quieres ver la disposicion del tablero?(s/n)\n");
            scanf("%c", &letra);
            fflush(stdin);
            if(letra=='s'||letra=='S')
            {
                mostrar(tablero1A);
            }
            printf("Introduce posicion donde empieza el barco.\n");
            scanf("%c%d", &letra, &posj1);
            posi1=letraxnum(letra);
            fflush(stdin);
            printf("Introduce posicion de fin.\n");
            scanf("%c%d", &letra, &posj2);
            posi2=letraxnum(letra);
            fflush(stdin);
            if(posi1>posi2)
            {
                aux=posi1;
                posi1=posi2;
                posi2=aux;
            }
            if(posj1>posj2)
            {
                aux=posj1;
                posj1=posj2;
                posj2=aux;
            }
            posOk=posicionEnTablero(posi1, posi2, posj1, posj2);
            if(posOk==-1)
            {
                printf("El barco no puede estar fuera del tablero.\n");
                system("pause");
            }
            else
            {
                if(posOk==-2)
                {
                    printf("No se pueden colocar barcos en diagonal.\n");
                    system("pause");
                }

                else
                {
                    barcOK=comprobarBarco(posi1, posi2, posj1, posj2,barcosJugador1);
                    if (barcOK==-1)
                    {
                        printf("No existen barcos tan grandes.\n");
                    }
                    else
                    {
                        if(barcOK==-2)
                        {
                            printf("No quedan barcos de ese tamaño a introducir.\n");
                        }
                        else
                        {
                            posOk=espacioDispo(posi1, posi2, posj1, posj2, tablero1);
                            if(posOk==-1)
                            {
                                printf("No se puede colocar el barco en esta posicion. (Recuerda que los barcos no pueden tocarse.)");
                            }
                        }
                    }
                }
            }

        }
        while(posOk!=1 || barcOK!=1);

        colocarBarcos(posi1, posi2, posj1, posj2, tablero1A, barcosJugador1);
        agua(posi1, posi2, posj1, posj2, tablero1A);
        totbarcosj1++;
        printf("Barco colocado!\n");
        system("pause");
        system("cls");
    }
    rellenarAgua(tablero1A);
    mostrar(tablero1A);

    printf("Inicio segundo jugador.\n");
    while(totbarcosj2!=TOTALBARCOS)
    {
        do
        {
            printf("Quieres ver la disposicion del tablero?(s/n)\n");
            scanf("%c", &letra);
            fflush(stdin);
            if(letra=='s'||letra=='S')
            {
                mostrar(tablero2A);
            }
            printf("Introduce posicion donde empieza el barco.\n");
            scanf("%c%d", &letra, &posj1);
            posi1=letraxnum(letra);
            fflush(stdin);
            printf("Introduce posicion de fin.\n");
            scanf("%c%d", &letra, &posj2);
            posi2=letraxnum(letra);
            fflush(stdin);
            if(posi1>posi2)
            {
                aux=posi1;
                posi1=posi2;
                posi2=aux;
            }
            if(posj1>posj2)
            {
                aux=posj1;
                posj1=posj2;
                posj2=aux;
            }
            posOk=posicionEnTablero(posi1, posi2, posj1, posj2);
            if(posOk==-1)
            {
                printf("El barco no puede estar fuera del tablero.\n");
                system("pause");
            }
            else
            {
                if(posOk==-2)
                {
                    printf("No se pueden colocar barcos en diagonal.\n");
                    system("pause");
                }

                else
                {
                    barcOK=comprobarBarco(posi1, posi2, posj1, posj2, barcosJugador2);
                    if (barcOK==-1)
                    {
                        printf("No existen barcos tan grandes.\n");
                    }
                    else
                    {
                        if(barcOK==-2)
                        {
                            printf("No quedan barcos de ese tamaño a introducir.\n");
                        }
                        else
                        {
                            posOk=espacioDispo(posi1, posi2, posj1, posj2, tablero2A);
                            if(posOk==-1)
                            {
                                printf("No se puede colocar el barco en esta posicion. (Recuerda que los barcos no pueden tocarse.)");
                            }
                        }
                    }
                }
            }

        }
        while(posOk!=1 || barcOK!=1);

        colocarBarcos(posi1, posi2, posj1, posj2, tablero2A, barcosJugador2);
        agua(posi1, posi2, posj1, posj2, tablero2A);
        totbarcosj2++;
        printf("Barco colocado!\n");
        system("pause");
        system("cls");
    }
    rellenarAgua(tablero2A);
    mostrar(tablero2A);
    aux=0;
    while(totbarcosj1!=0 && totbarcosj2!=0)
    {
        while(aux%2==0)
        {
            printf("Turno del jugador 1.\n");
            printf("Dispara!\n");
            scanf("%c%d", &letra, &posj1);
            posi1=letraxnum(letra);
            fflush(stdin);
            posOk=posicionEnTablero(posi1, posi1, posj1, posj1);
            if(posOk==1)
            {
                barcOk=disparo(posi1, posj1, tablero2A, tablero1B);
                if(barcOk==-1)
                {
                    printf("Agua!\n");
                }
                else if(barcOk==1)
                {
                    printf("Tocado!\n");
                }
                else
                {
                    printf("Tocado y hundido!\n");
                    totbarcosj2--;
                }
                mostrar(tablero1B);
                aux++;
            }
            else
            {
                printf("Introduce una posicion que se encuentre dentro del tablero.\n");
            }
        }
        while(aux%2==1)
        {
            printf("Turno del jugador 2.\n");
            printf("Dispara!\n");
            scanf("%c%d", &letra, &posj1);
            posi1=letraxnum(letra);
            fflush(stdin);
            posOk=posicionEnTablero(posi1, posi1, posj1, posj1);
            if(posOk==1)
            {
                barcOk=disparo(posi1, posj1, tablero1A, tablero2B);
                if(barcOk==-1)
                {
                    printf("Agua!\n");
                }
                else if(barcOk==1)
                {
                    printf("Tocado!\n");
                }
                else
                {
                    printf("Tocado y hundido!\n");
                    totbarcosj1--;
                }
                mostrar(tablero2B);
                aux++;
            }
            else
            {
                printf("Introduce una posicion que se encuentre dentro del tablero.\n");
            }
        }
    }
    if(totbarcosj2==0)
    {
        printf("\t\t\t\tEl jugador 1 ha ganado!\n");
    }
    else
    {
        printf("\t\t\t\tEl jugador 2 ha ganado! Felicidades!")
    }
}

