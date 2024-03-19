// codigo main


#include <iostream>
#include <windows.h>

#include <stdlib.h>//librerias temporales para generar randoms
#include <time.h>


//#include "ColorDetection.h"
#include "TetrisRepresentation.h"

#define SALTO VK_SPACE
#define GIROD 'X'
#define GIROI 'Z'
#define MOVERD VK_RIGHT
#define MOVERI VK_LEFT
#define GIROT 'A'



using namespace std;



void pruebas();

int main() {

pruebas();

return 0;
}



void pruebas(){
    Tablero tetris;
    int imax = 500;
   // tetris.obtenerFiguras();

    
    while(imax>0){
        tetris.update();
        tetris.betterMove();
        tetris.resetVirtualT();
        tetris.print();
        //tetris.printT();


      //   tetris.calculateMinMax(); // quitar funcion cuando se quite los ifs de las rotaciones // mirar si se puede poner en un lugar mejor
      //  tetris.setTable(movimientos+tetris.initialposition);
      //  tetris.steps(movimientos,rotacion,tetris.minx,tetris.maxx);
      //  tetris.dropRows();
  //       tetris.obtenerFiguras();
      //  tetris.print();
     //   Sleep(1)//este sleep lo ralentiza no permite el calculo debido a que cuando cae ya no detecta la ficha y por ende no acciona;
    imax--;
        }
        
    
    
    
    
  
}