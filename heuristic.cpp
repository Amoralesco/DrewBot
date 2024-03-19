#include <iostream>
#include <vector>
#include "TetrisRepresentation.h"

#include <windows.h>

using namespace std;


void Tablero:: virtualsetTable(int x){ 
    int size = virtualTetromino.size();
    int y,most,aux = 0;
    bool band = false;
    for(int i = 0 ;i < size && !band ;i++){
        most = i;
        for(int j = vminx;j<size-vmaxx;j++){
            if(virtualTetromino[i][j]!= 0){
                band = true;
                break;
            }
        }
    }
    band = false;
    for(int i = 22; i >= 0 && !band; i--){//calcular altura    
        for(int j =x+vminx;j <x+size-vmaxx &&!band; j++){
                if(virtualTable[i][j]!=0){
                    band = true;
                    break;
                }
            }
        y = i;
        }   
    if(!band) y--;
    band = false;
    while(!band && y >= 0){
        for(int i = vminx;i < size-vmaxx;i++){
            if(virtualTetromino[most+aux][i]!=0 && virtualTable[y][i+x]!= 0){
                band = true;
                break;
            }
            if(y-aux<0){
                band = true;
                break;
            }
            if(virtualTetromino[most][i]!=0 && virtualTable[y-aux][i+x]!= 0){
                band = true;
                break;
            }
        }
        if(!band)aux++;     
    }
    y += size -most - aux;
    for(int i = 0; i < size-most; i++ ){
        for(int j = vminx; j < size - vmaxx;  j++ ){
            virtualTable[y - i][x + j] = (virtualTable[y - i][x + j] == 0) ? virtualTetromino[size - i - 1][j] : virtualTable[y - i][x + j];
        }
    }
  
}

void Tablero::virtualcalculateMinMax()
{
    int n = virtualTetromino.size();
    int min = 0, max = 0;
    int band = false;
    for (int i = 0; i < n && !band; i++){ //- min seria el minimo de la posicion x
        min = i;
        for (int j = 0; j < n; j++){
            if (virtualTetromino[j][i] != 0){
                band = true;
                break;
            }
        }
    }
    band = false;
    for (int i = 0; i < n && !band; i++){ // 10-tamaño+max seria el maximo de la posicionx
        max = i;
        for (int j = 0; j < n; j++){
            if (virtualTetromino[j][n - i - 1] != 0){
                band = true;
                break;
            }
        }
    }
    vminx = min;
    vmaxx = max;
}





void Tablero::resetVirtualT(){
     for (int i = 0; i < 23; i++) {
        for (int j = 0; j < 10; j++) {
           virtualTable[i][j] = TetrisTable[i][j];
        }

    }
}


void Tablero::columnHeight(){
    for (int j =0; j < 10; j++){          
        virtualColumna[j] = 0;
    }for (int i = 0; i < 23; i++){
        for (int j =0; j < 10; j++){          
            virtualColumna[j] = (virtualTable[i][j] != 0) ? i + 1 : virtualColumna[j];
        }     
    }
}


int  Tablero::alturaAgregada(){
    int sum = 0;
    for(int i = 0; i<10; i++){
        sum +=virtualColumna[i];
    }
    return sum;
}


int  Tablero::lineasCompletas(){
    int count = 0;
    bool band;
    for(int i = 0; i< 23; i++){
        band = true;
       for(int j = 0; j<10; j++){
            band = (virtualTable[i][j] == 0) ? false : band;
            }
            if(band) count++;
        } 
    return count;
    }

int  Tablero::totalAgujeros(){
    int holes = 0;
    for(int i = 0; i<10; i++){
       for(int j = 0; j<virtualColumna[i]-1; j++){
            holes += (virtualTable[j][i] == 0) ? 1 : 0;
        } 
    }
    return holes;
}


int Tablero::totalIrregularidades(){
    int bump = 0;
    int temp = 0;

    for(int i = 0; i < 9; i++){
        temp=(virtualColumna[i]-virtualColumna[i+1]);
        temp = (temp < 0) ? -temp : temp;
        bump+=temp;

    }
    return bump;
}


float Tablero::positionValue(){
    float score = 0;
    columnHeight();
    int a = alturaAgregada();
    int b = lineasCompletas();
    int c = totalAgujeros();
    int d = totalIrregularidades();
    float values[4]= {-0.510066,0.760666,-0.35663,-0.184483};
    score = a*values[0]+b*values[1]+c*values[2]+d*values[3];
    cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<endl;
    cout<<score<<" value score"<<endl;
    Sleep(10);
    return score;
}




void Tablero::betterMove(){
    virtualcalculateMinMax();
    float better=-1000;
    float value = 0;
    int xpos = 0;
    int rot = 0;
    for(int j=0;j<4; j++){
        for(int i=-vminx;i<= 10-virtualTetromino.size()+vmaxx;i++){

            /**/
            resetVirtualT();
            virtualsetTable(i);
            value = positionValue();
            cout<<" rot: "<<j<<" pos: "<<i<<" value: "<<value<<endl;
            if(value > better){
                better = value;
                xpos = i;
                rot = j;
            }
        }
        rotarDerecha(1);
    }
    cout<<xpos<<" posicion del tetromino"<<endl;
    cout<<rot<<" en la rotacion "<<endl;
    cout <<better<<" valor de la mejor posicion"<< endl;

    
    if(rot == 1){  // implementar logica con la heuristica
        rotarDerecha(0);
    }else if(rot == 2 ){
        rotar180(0);
    }else if(rot == 3){
        rotarIzquierda(0);             
    }
    setTable(xpos);
    dropRows();
    resetVirtualT();
    virtualcalculateMinMax();
    steps(xpos-initialposition,rot,vminx,vmaxx);
}