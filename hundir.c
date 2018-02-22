#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define DIM 11

//Declaracion funcion para comprobar la disponibilidad de la posicion elegida para el barco.
int espacioDispo(int posIin, int posIfin, int posJin, int posJfin, char mat[DIM][DIM])
{
    int i, j, aux;
    if(posIin>posIfin)
    {
        aux=posIin;
        posIin=posIfin;
        posIfin=aux;
    }
    if(posJin>posJfin)
    {
        aux=posJin;
        posJin=posJfin;
        posJfin=aux;
    }
    for(i=posIin; i<=posIfin; i++)
    {
        for(j=posJin; j<=posJfin; j++)
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
void agua(int posIin, int posIfin, int posJin, int posJfin, char mat[DIM][DIM])
{
    int i,j;
    for(i=(posIin-1); i<(posIfin+2); i++)
    {
        if(i>0 && i<DIM)
        {
            for(j=(posJin-1); j<(posJfin+2); j++)
            {
                if (j>0 && j<DIM)
                {
                    if(posIin==posIfin)
                    {
                        if(i!=posIin || j<posJin || j>posJfin)
                        {
                            mat[i][j]='~';
                        }
                    }
                    else
                    {
                        if(j!=posJin || i<posIin || i>posIin)
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
        for (j=0; j<DIM; j++)
        {
            printf("%c  ", mat[i][j]);
        }
        printf("\n");
    }
}
void main()
{
    char tableroA1[DIM][DIM], tableroA2[DIM][DIM],tableroB1[DIM][DIM],tableroB2[DIM][DIM];
    int posi1, posi2, posj1, posj2, posOk;
    int x;
    char letra;
    crearTablero(tableroA1);
    crearTablero(tableroA2);
    crearTablero(tableroB1);
    crearTablero(tableroB2);
    posOk=1;

    printf("Inicio primer jugador.\n");

    //scanf("%c", &letra);
    do
    {
        //system("cls");
        printf("Introduce posicion donde empieza el barco.\n");
        scanf("%c%d", &letra, &posj1);
        posi1=letraxnum(letra);
        fflush(stdin);
        printf("Introduce posicion de fin.\n");
        scanf("%c%d", &letra, &posj2);
        posi2=letraxnum(letra);
        posOk=posicionEnTablero(posi1, posi2, posj1, posj2);
        if(posOk==-1)
        {
            printf("El barco no puede estar fuera del tablero.\n");
            system("pause");
        }
        if(posOk==-2)
        {
            printf("No se pueden colocar barcos en diagonal.\n");
            system("pause");
        }
    }
    while(posOk!=1);


    agua(posi1, posi2, posj1, posj2, tableroA1);
    mostrar(tableroA1);
    /*x=letraxnum(letra);*/
    //printf("%d", x);
}

