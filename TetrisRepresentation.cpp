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
    obtenerFiguras();
    ActualTetromino = NextTetromino;
    calculateMinMax();

}


void Tablero::calculateMinMax(){
    int n = ActualTetromino.size();
    int min = 0, max = 0;
    int band = false;
    for (int i = 0; i < n && !band; i++){ //- min seria el minimo de la posicion x
        min = i;
        for (int j = 0; j < n; j++){
            if (ActualTetromino[j][i] != 0){
                band = true;
                break;
            }
        }
    }
    band = false;
    for(int i = 0; i < n && !band; i++){ // 10-tamaño+max seria el maximo de la posicionx
        max = i;
        for (int j = 0; j < n; j++){
            if (ActualTetromino[j][n - i - 1] != 0){
                band = true;
                break;
            }       
        }
    }
    minx = min;
    maxx = max;
}




void Tablero::rotarIzquierda(int num)
{
     std::vector<std::vector<int>> tempShape;
    if(num == 0){
        tempShape = ActualTetromino; // Crear una copia temporal de la forma actual
    }
    if(num == 1){
        tempShape = virtualTetromino; // Crear una copia temporal de la forma actual
    }
   
    int n = tempShape.size();                                  // Obtener el tamaño de la matriz cuadrada
    for (int i = 0; i < n / 2; ++i)
    {
        for (int j = i; j < n - i - 1; ++j)
        {
            int temp = tempShape[i][j];
            tempShape[i][j] = tempShape[j][n - i - 1];
            tempShape[j][n - i - 1] = tempShape[n - i - 1][n - j - 1];
            tempShape[n - i - 1][n - j - 1] = tempShape[n - j - 1][i];
            tempShape[n - j - 1][i] = temp;
        }
    }
     if(num == 0){
        ActualTetromino = tempShape; // Actualizar la forma actual con la forma rotada
    }
    if(num == 1){
        virtualTetromino = tempShape; 
    }
     
}



void Tablero::rotarDerecha(int num)
{
    std::vector<std::vector<int>>& tempShape = (num == 0) ? ActualTetromino : virtualTetromino;
    int n = tempShape.size();
    std::vector<std::vector<int>> rotatedShape(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            rotatedShape[i][j] = tempShape[n - j - 1][i];
        }
    }

    tempShape = rotatedShape; // Actualizar la forma con la forma rotada
    if(num == 0){
        ActualTetromino = tempShape; // Si es la forma actual, actualizar
    }
    else if(num == 1){
        virtualTetromino = tempShape; // Si es la forma virtual, actualizar
    }
}



void Tablero::rotar180(int num)
{
    std::vector<std::vector<int>> tempShape;
    if(num == 0){
        tempShape = ActualTetromino; // Crear una copia temporal de la forma actual
    }
    if(num == 1){
        tempShape = virtualTetromino; // Crear una copia temporal de la forma actual
    }

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

    if(num == 0){
        ActualTetromino = tempShape; // Actualizar la forma actual con la forma rotada
    }
    if(num == 1){
        virtualTetromino = tempShape; 
    }
}




void Tablero::printT(){
    
    int n = virtualTetromino.size();
    for (int i = n - 1; i >= 0; i--){
        for (int j = 0; j < n; j++){
            cout <<virtualTetromino[i][j];
        }
        cout << endl;
    }
}


void Tablero::print()
{
    for (int i = 22; i >= 0; i--)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << TetrisTable[i][j];
        }
        cout << ":" << i << endl;
    }
}


 void Tablero::dropRows(){
    int count = 0;
    bool band;

    
    for(int i = 0; i < 23 ; i++){
        band = true;
       for(int j = 0; j < 10 ; j++ ){
            if(TetrisTable[i][j] == 0){
                band = false;
                break;
            }
        } 
        if (band) {
            for(int j = 0; j < 10 ; j++ ){
                TetrisTable[i][j] = 0;
            }

            for(int k = i; k < 22 ; k++ ){
                for(int j = 0; j < 10 ; j++){
                    TetrisTable[k][j] = TetrisTable[k+1][j];
                }
            }
            for(int j = 0; j < 10 ; j++){
                TetrisTable[22][j] = 0;
                }

            count++;
            i--;
        }
        
    }
 }