#ifndef __BONUS_H__
#define __BONUS_H__

#include <string>

using namespace std;

struct pos 
{
    float x,y; 
};


class bonus
{
private:
    pos p;
    string nomBonus;
    float vitesse;
    float duree;
public:
    bonus();/*! \brief */
    ~bonus();
};




#endif