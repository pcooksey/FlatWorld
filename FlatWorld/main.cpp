#include "SDL/SDL.h"
#include "include\environment.h"

#include <string>
#include <cstdlib>
#include <time.h>

int main( int argc, char* args[] )
{
    srand (time(NULL));
    Environment world;
    if(world.successful()==false)
        return 1;
    world.getStarted();
    return 0;
}
