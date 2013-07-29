#include "SDL/SDL.h"
#include "include\world.h"
#include "include\agent.h"

#include <string>
#include <cstdlib>
#include <time.h>

int main( int argc, char* args[] )
{
    srand (time(NULL));
    World world;
    if(world.successful()==false)
        return 1;
    Agent temp(rand()%Screen::SCREEN_WIDTH, rand()%Screen::SCREEN_HEIGHT);
    Agent temp2(rand()%Screen::SCREEN_WIDTH, rand()%Screen::SCREEN_HEIGHT);
    Agent temp3(rand()%Screen::SCREEN_WIDTH, rand()%Screen::SCREEN_HEIGHT);
    world.addObject(&temp);
    world.addObject(&temp2);
    world.addObject(&temp3);
    world.getStart();
    return 0;
}
