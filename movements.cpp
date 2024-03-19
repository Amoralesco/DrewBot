#include <iostream>
#include <vector>
#include <windows.h>
#include "TetrisRepresentation.h"

using namespace std;


#define SALTO VK_SPACE
#define GIROD 'X'
#define GIROI 'Z'
#define MOVERD VK_RIGHT
#define MOVERI VK_LEFT
#define GIROT 'A'




void Tablero::steps(int v1, int v2, int s1, int s2){

  //  Sleep(1000);
    if(v2 == 1){
        movement(GIROI);
        
 //        Sleep(1000);
    }if(v2 == 2){
        movement(GIROT);
  //      Sleep(1000);
    }if(v2 == 3){
        movement(GIROD);
 //       Sleep(1000);
    }
    if(v1<0){
        for(int i = v1 ; i< 0; i++){
     //       Sleep(500);
            movement(MOVERI);
        }
    } if(v1>0){
        for(int i = 0; i <  v1; i++){
       //     Sleep(500);
            movement(MOVERD);
        }
    }
    movement(SALTO);

}


void Tablero::movement(WORD key){
    keybd_event(key, 0, 0, 0); // Simular la pulsación de la tecla
    keybd_event(key, 0, KEYEVENTF_KEYUP, 0); // Simular la liberación de la tecla
}