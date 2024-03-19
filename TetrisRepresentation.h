#ifndef TETRIS_REPRESENTATION_H
#define TETRIS_REPRESENTATION_H

#include <iostream>
#include <vector>
#include <windows.h>

class Tablero {
public:


    void dropRows();
    int retmin();//metodo temporal que devuelve la minima
    int retmax();
    Tablero();
    void setTable(int x);
    void setNext();
    int tetrominoheight(int x);
    void columnHeight();
    int highestC(int x);
    void calculateMinMax();
    void rotarIzquierda(int num);
    void rotarDerecha(int num);
    void rotar180(int num);
    void update();
    void print();   
     void printT();

     void printH();





    //metodos de la heuristica 

    //metodos para poner el tablero virtual

    void virtualsetTable(int x);
    void virtualcolumnHeight();
    int virtualtetrominoheight(int x);
    void virtualcalculateMinMax();
    int virtualretmin();
    int virtualretmax();

    int virtualhighestC(int x);





     //evaluar el tablero
     int alturaAgregada();
     int lineasCompletas();
     int totalAgujeros();
     int totalIrregularidades();
     float positionValue();
     void resetVirtualT();
     void betterMove();



     //metodos del captura de pantalla

     void obtenerFiguras();

     void movement(WORD key);
     void steps(int v1,int v2, int s1, int s2);


     //metodo de accciones

    int nextTetros[6]; 
    int TetrisTable[23][10];
    int virtualTable[23][10];
    int alturaColumna[10];
    int virtualColumna[10];
    int minx, maxx;
    int vminx, vmaxx;
    int initialposition;
    std::vector<std::vector<int>> NextTetromino;
    std::vector<std::vector<int>> ActualTetromino;
    std::vector<std::vector<int>> virtualTetromino;
    std::vector<std::vector<int>> C;
    std::vector<std::vector<int>> I;
    std::vector<std::vector<int>> LD;
    std::vector<std::vector<int>> LI;
    std::vector<std::vector<int>> T;
    std::vector<std::vector<int>> ZD;
    std::vector<std::vector<int>> ZI;


private:
    
    
};

#endif // TETRIS_REPRESENTATION_H