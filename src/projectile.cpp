#include "projectile.h"

projectile::projectile(float x, float y){
    p.x=x;
    p.y=y;
    direction.x=0;
    direction.y=10;
}

projectile::~projectile(){

}

void projectile::Update(){
    p.x+=direction.x;
    p.y+=direction.y;
}