#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//Constante que determina el tamaño del tablero de juego(Matriz DIMxDIM)
#define DIM 11
//Vector que contiene la cantidad de barcos segun su tamaño. El tamaño vendrà dado por la posicion en el vector y la cantidad de
//barcos por el numero que se encuentra en la posicion. P. ej.: barcos[1] --> 4 barcos de 1 casilla.
#define BARCOS {0,4,3,2,1,1}
//Constante con la cantidad de barcos diferentes que hay mas uno ya que la posicion '0' no se utilizara.
#define DIFBARCOS 6
#define TOTALBARCOS 11


//Declaracion funcion para colocar barcos
void colocarBarcos(int posi1, int posi2, int posj1, int posj2, char mat[DIM][DIM])
{
    int i, j;
    if(posi1==posi2)
    {
        i=posi1;
        for(j=posj1; j<=posj2; j++){
            mat[i][j]='O';
        }
    }
    else
    {
        j=posj1;
        for(i=posi1; i<=posi2; i++)
        {
            mat[i][j]='O';
        }
    }
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

int comprobarBarco(int posi1, int posi2, int posj1, int posj2, int barcos1[])
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
        if (barcos1[tamano] != 0)
        {
            return (1);
        }
        else
        {
            return (-2);
        }
    }
}

void main()
{
    char tableroA1[DIM][DIM], tableroA2[DIM][DIM],tableroB1[DIM][DIM],tableroB2[DIM][DIM];
    int posi1, posi2, posj1, posj2, posOk, barcOK;
    int x, aux;
    char letra;
    int barcosJugador1[DIFBARCOS]=BARCOS, barcosJugador2[DIFBARCOS]=BARCOS;

    crearTablero(tableroA1);
    crearTablero(tableroA2);
    crearTablero(tableroB1);
    crearTablero(tableroB2);

    printf("Inicio primer jugador.\n");
    do
    {

        printf("Introduce posicion donde empieza el barco.\n");
        scanf("%c%d", &letra, &posj1);
        posi1=letraxnum(letra);
        fflush(stdin);
        printf("Introduce posicion de fin.\n");
        scanf("%c%d", &letra, &posj2);
        posi2=letraxnum(letra);
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
        else if(posOk==-2)
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
            else if(barcOK==-2)
            {
                printf("No quedan barcos de ese tamaño a introducir.\n");
            }
            else
            {
                posOk=espacioDispo(posi1, posi2, posj1, posj2, tableroA1);
                if(posOk==-1)
                {
                    printf("No se puede colocar el barco en esta posicion. (Recuerda que los barcos no pueden tocarse.)");
                }
            }
        }
    }
    while(posOk!=1);
    colocarBarcos(posi1, posi2, posj1, posj2, tableroA1);
    agua(posi1, posi2, posj1, posj2, tableroA1);
    mostrar(tableroA1);
    mostrar(tableroA2);
    mostrar(tableroB1);
    mostrar(tableroB2);
}
