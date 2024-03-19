// ColorDetection.cpp


#include <iostream>

using namespace std;

int Colours[8][3] = {
    {70, 70, 70},   // hold piece
    {206, 197, 82}, // Tetromino C
    {82, 206, 172}, // Tetromino I
    {206, 129, 82}, // Tetromino LD Durazno
    {102,82,206},  // Tetromino  LI morado
    {195, 82, 206}, // tetromino T
    {128, 206, 82}, // Tetromino  ZD rojo
    {206, 82, 89},  // Tetromino ZI lima
};

void printColor(int red, int green, int blue) {
    cout << "Color del píxel en RGB: (" << red << ", " << green << ", " << blue << ")" << endl;
}

int tetrominoS(int red, int green, int blue){
    int  t = 30;
    if(red > Colours[0][0]-t && red < Colours[0][0]+t && green > Colours[0][1]-t  && green < Colours[0][1]+t && blue > Colours[0][2]-t && blue < Colours[0][2]+t ){
    //    cout<< " pieza holding"<<endl;
        return 0;
    }
    if(red > Colours[1][0]-t && red < Colours[1][0]+t && green > Colours[1][1]-t  && green < Colours[1][1]+t && blue > Colours[1][2]-t && blue < Colours[1][2]+t ){
     //   cout<< "1 cuadrado"<<endl;
        return 1;
    }
    if(red > Colours[2][0]-2*t && red < Colours[2][0]+2*t && green > Colours[2][1]-2*t  && green < Colours[2][1]+2*t && blue > Colours[2][2]-2*t && blue < Colours[2][2]+2*t ){
    //    cout<< "2 Linea"<<endl;
         return 2;
    }
    if(red > Colours[3][0]-t && red < Colours[3][0]+t && green > Colours[3][1]-t  && green < Colours[3][1]+t && blue > Colours[3][2]-t && blue < Colours[3][2]+t ){
     //   cout<< "3 L morada"<<endl;
         return 3;
    }
    if(red > Colours[4][0]-t && red < Colours[4][0]+t && green > Colours[4][1]-t  && green < Colours[4][1]+t && blue > Colours[4][2]-t && blue < Colours[4][2]+t ){
    //   cout<< "4 L durazno"<<endl;
         return 4;
    }
    if(red > Colours[5][0]-t && red < Colours[5][0]+t && green > Colours[5][1]-t  && green < Colours[5][1]+t && blue > Colours[5][2]-t && blue < Colours[5][2]+t ){
      //  cout<< "5 Te"<<endl;
         return 5;
    }
    if(red > Colours[6][0]-t && red < Colours[6][0]+t && green > Colours[6][1]-t  && green < Colours[6][1]+t && blue > Colours[6][2]-t && blue < Colours[6][2]+t ){
     //  cout<< "6 Zeta lima"<<endl;
         return 6;
    }
    if(red > Colours[7][0]-t && red < Colours[7][0]+t && green > Colours[7][1]-t  && green < Colours[7][1]+t && blue > Colours[7][2]-t && blue < Colours[7][2]+t ){
       // cout<< "7 zeta rojo"<<endl;
         return 7;
    }
    if(red == 0 && green == 0  && blue == 0){
     //   cout<< "calculating..."<<endl;
         return 8;
    }
    else return 9;
}

bool isHoldLock(int red ,int green ,int blue) {//retorna si esta disponible para usar la ficha holdeada
int t=15;
    if( red > Colours[0][0] -t && red < Colours[0][0] + t &&     green > Colours[0][1] -t && green < Colours[0][1] + t &&  blue > Colours[0][2] -t && blue < Colours[0][2] + t ){
        return true;
    }
    return false;
}
