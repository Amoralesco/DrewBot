#include <iostream>


#include "TetrisRepresentation.h"



using namespace std;

Tablero::Tablero() : C({{1, 1}, {1, 1}}), I({{0, 0, 0, 0}, {0, 0, 0, 0}, {2, 2, 2, 2}, {0, 0, 0, 0}}), LD({{0, 0, 0}, {4, 4, 4}, {0, 0, 4}}), LI({{0, 0, 0}, {3, 3, 3}, {3, 0, 0}}), T({{0, 0, 0},{5, 5, 5}, {0, 5, 0}}), ZD({{0, 0, 0}, {0, 7, 7}, {7, 7, 0}}), ZI({{0, 0, 0},{6, 6, 0}, {0, 6, 6}})
{
    for (int i = 0; i < 23; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            TetrisTable[i][j] = 0;
            virtualTable[i][j] = 0;
            alturaColumna[j] = (i == 0) ? 0 : alturaColumna[j];
            virtualColumna[j] = (i == 0) ? 0 : virtualColumna[j];
        }
    }
    initialposition = 0;
}



void Tablero::setTable(int x){ 

    //printT();
    int size = ActualTetromino.size();
    int y,most,aux = 0;

    bool band = false;

    for(int i = 0 ;i < size && !band ;i++){
        most = i;
        for(int j = minx;j<size-maxx;j++){
            if(ActualTetromino[i][j]!= 0){
                band = true;
                break;
            }
        }
    }

    band = false;

    for(int i = 22; i >= 0 && !band; i--){//calcular altura    
        for(int j =x+minx;j <x+size-maxx &&!band; j++){
                if(TetrisTable[i][j]!=0){
                    band = true;
                    break;
                }
            }
        y = i;
        }   

    if(!band) y--;

    band = false;


    while(!band && y >= 0){
        for(int i = minx;i < size-maxx;i++){
            if(ActualTetromino[most+aux][i]!=0 && TetrisTable[y][i+x]!= 0){
                band = true;
                break;

            }
            if(y-aux<0){
                band = true;
                break;
            }
            if(ActualTetromino[most][i]!=0 && TetrisTable[y-aux][i+x]!= 0){
                band = true;
                break;

            }
        }
        if(!band)aux++;
        
    }

    y += size -most - aux;



    for(int i = 0; i < size-most; i++ ){
        for(int j = minx; j < size - maxx;  j++ ){
            TetrisTable[y - i][x + j] = (TetrisTable[y - i][x + j] == 0) ? ActualTetromino[size - i - 1][j] : TetrisTable[y - i][x + j];
        }
    }
  
}





void Tablero::setNext(){
    int Tetr = nextTetros[1];
    NextTetromino = (Tetr == 1) ? C 
                    : (Tetr == 2) ? I
                    : (Tetr == 3)   ? LD
                    : (Tetr == 4)   ? LI
                    : (Tetr == 5)   ? T
                    : (Tetr == 6)   ? ZI
                    : (Tetr == 7)   ? ZD
                                    : NextTetromino;
    virtualTetromino = NextTetromino;
 
    if(Tetr ==1) initialposition = 4; 
    else initialposition = 3;
}


void Tablero::update(){

    ActualTetromino = NextTetromino;
    calculateMinMax();

}


void Tablero::calculateMinMax(){
    int n = ActualTetromino.size();
    int min = 0, max = 0;
    int band = false;
    for (int i = 0; i < n && !band; i++)
    { //- min seria el minimo de la posicion x
        min = i;
        for (int j = 0; j < n; j++)
        {
            if (ActualTetromino[j][i] != 0)
            {
                band = true;
                break;
            }
        }
    }

    band = false;

    for(int i = 0; i < n && !band; i++)
    { // 10-tamaño+max seria el maximo de la posicionx
        max = i;
        for (int j = 0; j < n; j++)
        {
            if (ActualTetromino[j][n - i - 1] != 0)
            {
            
                band = true;
                break;
            }
            
        }
    }
    minx = min;
    maxx = max;
}




void Tablero::rotarIzquierda()
{
    std::vector<std::vector<int>> tempShape = ActualTetromino; // Crear una copia temporal de la forma actual
    int n = tempShape.size();                                 // Obtener el tamaño de la matriz cuadrada
    std::vector<std::vector<int>> rotatedShape(n, std::vector<int>(n, 0)); // Crear una nueva matriz rotada

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            rotatedShape[i][j] = tempShape[j][n - i - 1];
        }
    }

    ActualTetromino = rotatedShape; // Actualizar la forma actual con la forma rotada
}

void Tablero::rotarDerecha()
{
    std::vector<std::vector<int>> tempShape = ActualTetromino; // Crear una copia temporal de la forma actual
    int n = tempShape.size();                                 // Obtener el tamaño de la matriz cuadrada
    std::vector<std::vector<int>> rotatedShape(n, std::vector<int>(n, 0)); // Crear una nueva matriz rotada

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            rotatedShape[i][j] = tempShape[n - j - 1][i];
        }
    }

    ActualTetromino = rotatedShape; // Actualizar la forma actual con la forma rotada
}



void Tablero::rotar180()
{
    std::vector<std::vector<int>> tempShape = ActualTetromino; // Crear una copia temporal de la forma actual
    int n = tempShape.size();                                  // Obtener el tamaño de la matriz cuadrada

    for (int i = 0; i < n / 2; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::swap(tempShape[i][j], tempShape[n - i - 1][n - j - 1]);
        }
    }

    // Si la matriz tiene un número impar de filas, necesitamos intercambiar el elemento central
    if (n % 2 == 1)
    {
        int mid = n / 2;
        for (int j = 0; j < n / 2; j++)
        {
            std::swap(tempShape[mid][j], tempShape[mid][n - j - 1]);
        }
    }

    ActualTetromino = tempShape; // Actualizar la forma actual con la forma rotada
}




void Tablero::printT(){
    
    int n = ActualTetromino.size();
    for (int i = n - 1; i >= 0; i--){
        for (int j = 0; j < n; j++){
            cout <<ActualTetromino[i][j];
        }
        cout << endl;
    }
}


void Tablero::print()
{
    for (int i = 10; i >= 0; i--)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << TetrisTable[i][j];
        }
        cout << ":" << i << endl;
    }
}
