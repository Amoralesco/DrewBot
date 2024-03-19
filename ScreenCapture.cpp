// ScreenCapture.cpp


#include <iostream>
#include "ColorDetection.h"
#include "TetrisRepresentation.h"
#include <windows.h>



using namespace std;



//int Cords[6][2] = {
   // {727, 324},   // hold position
   // {1204, 334},  // 1 fichas siguientes a salir
   // {1204, 418},  // 2 ficas siguientesa a salir
   // {1204, 512},  // 3 ficas siguientesa a salir
   //{1204, 602},  // 4 ficas siguientesa a salir
    //{1204, 690},  // 5 ficas siguientesa a salir
//};
int Cords[7][2] = {
    {727, 344},   // hold position
    {1226, 348},  // 1 fichas siguientes a salir
    {1226, 445},  // 2 ficas siguientesa a salir
    {1226, 542},  // 3 ficas siguientesa a salir
    {1226, 638},  // 4 ficas siguientesa a salir
    {1226, 735},  // 5 ficas siguientesa a salir
    {940, 235},  // posicion inicial de la figura,esencial para medir el tiempo de espera
};
//Posici├│n del mouse: (957, 240) posicion inicial




void Tablero::obtenerFiguras(){
  // Obtener el dispositivo de pantalla principal
    HDC dc = GetDC(NULL);


  // Bucle para leer continuamente el color del píxel hasta que se haga clic derecho
        int red,green,blue;
        // Obtener el color del píxel en las coordenadas especificadas
        for (int i=1; i<6;i++){
            COLORREF color = GetPixel(dc, Cords[i][0], Cords[i][1]);
                    // Extraer componentes de color RGB
            red = GetRValue(color);
            green = GetGValue(color);
            blue = GetBValue(color);
            nextTetros[i]=tetrominoS(red,green,blue);
            if(i == 0){//imprimir si no se puede desplegar la barra holdeada
                if(isHoldLock(red,green,blue)){
                cout << "la ficha está bloqueada"<<endl;
                 }
            }
        }

        setNext();

   

        COLORREF color = GetPixel(dc, Cords[6][0], Cords[6][1]);//lógica para esperar el siguiente movimiento
        red = GetRValue(color);
        green = GetGValue(color);
        blue = GetBValue(color);

        while(tetrominoS(red,green,blue)==8){
            COLORREF color = GetPixel(dc, Cords[6][0], Cords[6][1]);
            red = GetRValue(color);
            green = GetGValue(color);
            blue = GetBValue(color);
        }


    
    // Liberar el dispositivo de pantalla
    ReleaseDC(NULL, dc);


}
