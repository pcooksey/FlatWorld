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
    Agent temp;
    world.addObject(&temp);
    world.getStart();
    return 0;
}
