#ifndef __MONSTRE_H__
#define __MONSTRE_H__

#include <vector>
#include <string>

using namespace std;

struct pos
        {
            float x,y;
        };

class Monstre
{
    private:
    
        vector<float> direction;
        float vitesse; 
        float taille;
        int TypeM;
        int resistance;
    
    public:
        Monstre(); /*! \brief */
        ~Monstre(); /*! \brief */
        pos getPos() const; /*! \brief renvoie la position du monstre en x et y*/
        void setPos(pos p); /*! \brief */
        int getTypeM(); /*! \brief */
        void setgetTypeM(); /*! \brief */
        vector<float> getDirM() const; /*! \brief */
        void setDir(vector<float> d); /*! \brief */
        float getVit() const; /*! \brief */
        float setVit(float v); /*! \brief */
        float getTailleM() const;  /*! \brief */
        float setTailleM(float t); /*! \brief */
        int getResistance(); /*! \brief */
        void setResistance(); /*! \brief */
        

};


#endif