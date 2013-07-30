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
    for(int i=0; i<10; ++i)
    {
        Agent* temp = new Agent(rand()%Screen::SCREEN_WIDTH, rand()%Screen::SCREEN_HEIGHT);
        world.addObject(temp);
    }
    world.getStarted();
    return 0;
}
