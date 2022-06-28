#include <iostream>
#include "voxel.h"
#include "sculptor.h"

using namespace std;

int main(void) {
   sculptor porco(100, 100, 100);

   // corpo
   porco.setColor(1, 0.76, 0.82, 1.0);
   porco.putBox(0, 12, 1, 20, 10, 18);

   // cabeça
   porco.setColor(1, 0.76, 0.82, 1.0);;
   porco.putBox(2, 10, 20, 28, 13, 20);

   // pernas
   porco.setColor(1, 0.76, 0.82, 1.0);
   porco.putBox(8, 12, 0, 5, 3, 10);    // traseiras
   porco.putBox(0, 4, 0, 5, 3, 10);     // traseiras
   porco.putBox(8, 12, 14, 19, 3, 10);  // dianteiras
   porco.putBox(0, 4, 14, 19, 3, 10);   // dianteiras

   // focinho
   porco.setColor(1, 1, 1, 1.0);
   porco.putBox(4, 8, 28, 29, 16, 17);
   porco.setColor(1, 0.76, 0.82, 1.0);
   porco.putBox(4, 8, 28, 29, 15, 16);
   porco.setColor(1, 1, 1, 1.0);
   porco.putBox(4, 8, 28, 29, 14, 15);

   // olhos
   porco.setColor(1, 1, 1, 1.0);
   porco.putVoxel(3, 27, 17);  // olho branco
   porco.putVoxel(8, 27, 17);  // olho branco

   porco.setColor(0, 0, 0, 1.0);
   porco.putVoxel(2, 27, 17);  // olho preto
   porco.putVoxel(9, 27, 17);  // olho preto

   porco.writeOFF("../output/porco.off");

   return 0;
}