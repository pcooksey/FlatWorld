#include "../include/environment.h"

Environment::Environment()
:World()
{
    for(int i=0; i<10; ++i)
    {
        Agent* temp = new Agent(rand()%Screen::SCREEN_WIDTH, rand()%Screen::SCREEN_HEIGHT);
        addObject(temp);
    }
    for(int i=0; i<30; ++i)
    {
        Plant* plant = new Plant(rand()%Screen::SCREEN_WIDTH, rand()%Screen::SCREEN_HEIGHT);
        addObject(plant);
    }
}

Environment::~Environment()
{
    //dtor
}
