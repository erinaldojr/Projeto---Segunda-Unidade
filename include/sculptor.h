#ifndef SCULPTOR_H_INCLUDED
#define SCULPTOR_H_INCLUDED
#include <string>
#include <vector>
#include "voxel.h"


class sculptor{

    private:
        voxel ***vox;
        float lado;
        float r, g, b, a;
        int nx, ny, nz;
        int i, j, k;

    public:
        sculptor(int _nx = 1, int _ny=1, int _nz=1);
        ~sculptor();

        void aloca();
        void libera();

        void setColor(float r, float g, float b, float a);

        void putBox(int x0, int x1, int y0, int y1, int z0, int z1);

        void putEllipsoid (int x0, int y0, int z0, int rx, int ry, int rz);

        void putSphere (int x0, int y0, int z0, int rr);

        void cutSphere(int x0, int y0, int z0, int r);

        void putVoxel (int x0, int y0, int z0);

        void CutVoxel(int x0, int y0, int z0);

        void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);

        void cutEllipsoid (int x0, int y0, int z0, int rx, int ry, int rz);

        void limpaVoxels ();

        void writeOFF (char* f);
};


#endif // SCULPTOR_H_INCLUDED
