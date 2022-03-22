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
        pos position; /*! \brief structure contenant la position en coordonnées x,y*/
        vector<float> direction;
        float vitesse; 
        float taille;
        int TypeM;
        
    
    public:
        int resistance;
        Monstre(); /*! \brief */
        ~Monstre(); /*! \brief */
        pos getPos() const; /*! \brief renvoie la position du monstre en x et y*/
        void setPos(pos p); /*! \brief */
        int getTypeM(); /*! \brief */
        void setTypeM(); /*! \brief */
        vector<float> getDirM() const; /*! \brief */
        float getVitM() const; /*! \brief */
        void setVitM(float v); /*! \brief */
        float getTailleM() const;  /*! \brief */
        void setTailleM(float t); /*! \brief */
        int getResistance(); /*! \brief */
        void setResistance(int r); /*! \brief */
        

};


#endif