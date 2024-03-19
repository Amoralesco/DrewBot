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
    int movimientos = 2;
    int rotacion = 3;
    Tablero tetris;

    tetris.obtenerFiguras();
    for(int i = 1 ;i < 6; i++){
        cout<<tetris.nextTetros[i]<<" tetro "<<endl;
    }
    
    while(true){
       
        tetris.update();
        if(rotacion == 1){
                tetris.rotarDerecha();
        }
        if(rotacion == 2 ){
            tetris.rotar180();
        }
        if(rotacion == 3){
            
            tetris.rotarIzquierda();  
            
            
        }
        tetris.printT();
        tetris.setTable(movimientos+tetris.initialposition);
        tetris.calculateMinMax();
        tetris. steps(movimientos,rotacion,tetris.minx,tetris.maxx);
         tetris.obtenerFiguras();
        tetris.print();
        Sleep(10);

        }
        
    
    
    
    
  
}