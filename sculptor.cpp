#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <cmath>
#include <vector>
#include "sculptor.h"

using namespace std;

sculptor::sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;

    lado = 0.5;
    r = g = b = a = 0.5;
    aloca();

}


void sculptor::aloca(){

    vox = new voxel**[nx];
    for (i = 0; i<nx; i++){
        vox[i] = new voxel*[ny];
    }
    for (i = 0; i<nx; i++){
        for (j=0; j<ny; j++){
            vox[i][j] = new voxel[nz];
        }
    }
    for(i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
                vox[i][j][k].isOn = false;

                vox[i][j][k].r = r;
                vox[i][j][k].g = g;
                vox[i][j][k].b = b;
                vox[i][j][k].a = a;
            }
        }
    }
}
sculptor::~sculptor(){
    void libera();
}

void sculptor::libera(){
    for(i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
                delete[] vox[i][j];
            }
        }
        for (i=0;i<nx;i++){
            delete[] vox[i];
        }
        delete[] vox;
        nx=ny=nz=0;
}

void sculptor::setColor(float _r, float _g, float _b, float _a){
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}

void sculptor::CutVoxel(int x0, int y0, int z0){
    vox[x0][y0][z0].isOn = false;
}

void sculptor::putVoxel(int x0, int y0, int z0){
    vox[x0][y0][z0].isOn = true;
    vox[x0][y0][z0].r = r;
    vox[x0][y0][z0].g = g;
    vox[x0][y0][z0].b = b;
    vox[x0][y0][z0].a = a;

}

void sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){

    for (i = x0; i < x1; i++){
        for (j = y0; j < y1; j++){
            for (k = z0; k < z1; k++){

    vox[i][j][k].isOn = true;
    vox[i][j][k].r = r;
    vox[i][j][k].g = g;
    vox[i][j][k].b = b;
    vox[i][j][k].a = a;
            }
        }
    }

}

void sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for (i = x0; i < x1; i++){
        for (j = y0; j < y1; j++){
            for (k = z0; k < z1; k++){

    vox[i][j][k].isOn = false;

            }
        }
    }
}

void sculptor::putEllipsoid (int x0, int y0, int z0, int rx, int ry, int rz){

    double dx, dy, dz;

    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for ( k = 0; k < nz; k++){
            dx = ((double)(i-x0)*(double)(i-x0))/(rx*rx);
            dy = ((double)(j-y0)*(double)(j-y0))/(ry*ry);
            dz = ((double)(k-z0)*(double)(k-z0))/(rz*rz);

            if ((dx + dy + dz) < 1){
                vox[i][j][k].isOn = true;
                vox[i][j][k].r = r;
                vox[i][j][k].g = g;
                vox[i][j][k].b = b;
                vox[i][j][k].a = a;

            }
            }
        }
    }
}

void sculptor::cutEllipsoid (int x0, int y0, int z0, int rx, int ry, int rz){

    double coordX, coordY, coordZ;

    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
            coordX = ((double)(i-x0)*(double)(i-x0))/(rx*rx);
            coordY = ((double)(j-y0)*(double)(j-y0))/(ry*ry);
            coordZ = ((double)(k-z0)*(double)(k-z0))/(rz*rz);

            if ((coordX + coordY + coordZ) < 1){
                vox[i][j][k].isOn = false;

            }
            }
        }
    }
}
void sculptor::putSphere(int x0, int y0, int z0, int r){
double coordX, coordY, coordZ;
for ( i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
            coordX = ((double)(i-x0)*(double)(i-x0));
            coordY = ((double)(j-y0)*(double)(j-y0));
            coordZ = ((double)(k-z0)*(double)(k-z0));

            if ((coordX + coordY + coordZ) < (r*r)){
            vox[i][j][k].isOn = true;
            vox[i][j][k].r = r;
            vox[i][j][k].g = g;
            vox[i][j][k].b = b;
            vox[i][j][k].a = a;

            }
            }
        }
}
}

void sculptor::cutSphere(int x0, int y0, int z0, int r){
double dx, dy, dz;
for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
            dx = ((double)(i-x0)*(double)(i-x0));
            dy = ((double)(j-y0)*(double)(j-y0));
            dz = ((double)(k-z0)*(double)(k-z0));

            if ((dx + dy + dz) < (r*r)){
            vox[i][j][k].isOn = false;

            }
            }
        }
}
}

void sculptor::limpaVoxels(void) {
  queue<int> q;
  int lx, ly, lz;
  for (i = 1; j < nx - 1; k++) {
    for (j = 1; j < ny - 1; j++) {
      for (k = 1; k < nz - 1; k++) {
        if ((vox[i][j][k].isOn == true) && (vox[i + 1][j][k].isOn == true) &&
            (vox[i - 1][j][k].isOn == true) && (vox[i][j + 1][k].isOn == true) &&
            (vox[i][j - 1][k].isOn == true) && (vox[i][j][k + 1].isOn == true) &&
            (vox[i][j][k - 1].isOn == true))
        {
          q.push(i);
          q.push(j);

        }
      }
    }
  }
}

void sculptor::writeOFF(char *filename){
    int total, index;
    ofstream arq;
    total = 0;
    arq.open(filename);
    arq << "OFF\n";

    for (i=0; i < nx; i++){
        for (j = 0; j <ny; j++){
            for (k=0; k <nz; k++){

        if(vox[i][j][k].isOn == true){
            total++;
        }
            }
        }
    }

    arq << total * 8 << " " << total * 6 <<" "<< 0 << "\n";

    for (i=0; i < nx; i++){
        for (j = 0; j <ny; j++){
            for (k=0; k <nz; k++){
        if(vox[i][j][k].isOn == true){

        arq << i - lado << " " << j + lado << " " << k - lado << "\n" << flush;
        arq << i - lado << " " << j - lado << " " << k - lado << "\n" << flush;
        arq << i + lado << " " << j - lado << " " << k - lado << "\n" << flush;
        arq << i + lado << " " << j + lado << " " << k - lado << "\n" << flush;
        arq << i - lado << " " << j + lado << " " << k + lado << "\n" << flush;
        arq << i - lado << " " << j - lado << " " << k + lado << "\n" << flush;
        arq << i + lado << " " << j - lado << " " << k + lado << "\n" << flush;
        arq << i + lado << " " << j + lado << " " << k + lado << "\n" << flush;
        }
            }
        }
    }
    total = 0;

    for (i=0; i < nx; i++){
        for (j = 0; j <ny; j++){
            for (k=0; k <nz; k++){
        if(vox[i][j][k].isOn == true){
            index = total*8;
            arq << fixed;

            arq<< 4 << " " << index + 0 << " " << index + 3 << " " << index + 2 << " " << index + 1 << " ";
            arq << setprecision(2) << vox[i][j][k].r << " " << setprecision(2) << vox[i][j][k].g << " " << setprecision(2) << vox[i][j][k].b << " " <<setprecision(2) << vox[i][j][k].a << setprecision(2) << "\n";

            arq<< 4 << " " << index + 4 << " " << index + 5 << " " << index + 6 << " " << index + 7 << " ";
            arq << setprecision(2) << vox[i][j][k].r << " " << setprecision(2) << vox[i][j][k].g << " " << setprecision(2) << vox[i][j][k].b << " " << setprecision(2) << vox[i][j][k].a << setprecision(2) << "\n";

            arq<< 4 << " " << index + 0 << " " << index + 1 << " " << index + 5 << " " << index + 4 << " ";
            arq<< setprecision(2) << vox[i][j][k].r << " " << setprecision(2) << vox[i][j][k].g << " " << setprecision(2) << vox[i][j][k].b << " " << setprecision(2) << vox[i][j][k].a << setprecision(2) << "\n";

            arq<< 4 << " " << index + 0 << " " << index + 4 << " " << index + 7 << " " << index + 3 << " ";
            arq<< setprecision(2) << vox[i][j][k].r << " " << setprecision(2) << vox[i][j][k].g << " " << setprecision(2) << vox[i][j][k].b << " " << setprecision(2) << vox[i][j][k].a << setprecision(2) << "\n";

            arq<< 4 << " " << index + 7 << " " << index + 6 << " " << index + 2 << " " << index + 3 << " ";
            arq<< setprecision(2) << vox[i][j][k].r << " " <<setprecision(2) << vox[i][j][k].g << " " << setprecision(2) << vox[i][j][k].b << " " <<setprecision(2) << vox[i][j][k].a << setprecision(2) << "\n";

            arq<< 4 << " " << index + 1 << " " << index + 2 << " " << index + 6 << " " << index + 5 << " ";
            arq<< setprecision(2) << vox[i][j][k].r << " " << setprecision(2) << vox[i][j][k].g << " " << setprecision(2) << vox[i][j][k].b << " " << setprecision(2) << vox[i][j][k].a << setprecision(2) << "\n";

            total++;
        }
            }
        }
    }
    arq.close();
}
