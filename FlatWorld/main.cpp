#include "SDL/SDL.h"
#include "include\world.h"
#include "include\agent.h"
#include <string.h>

int main( int argc, char* args[] )
{
    World world;
    if(world.successful()==false)
        return 1;
    Agent temp;
    world.addObject(&temp);
    world.getStart();
    return 0;
}
