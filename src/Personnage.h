#ifndef __PERSONNAGE_H__
#define __PERSONNAGE_H__

#include <vector>
#include <string>

using namespace std;

class Personnage
{
    private:
        struct pos
        {
            float x,y;
        };
        vector<float> * projectile;
        vector<float> direction;
        float vitesse;
        float score;
        string nom;

};


#endif