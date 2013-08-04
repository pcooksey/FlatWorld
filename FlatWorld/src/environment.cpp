#include "../include/environment.h"

Environment::Environment()
:World(), geneticAlg(10, .05 , .7)
{
    init();
}

Environment::~Environment()
{
    //dtor
}

void Environment::init()
{
    for(int i=0; i<10; ++i)
    {
        Agent* temp = new Agent(rand()%Screen::SCREEN_WIDTH, rand()%Screen::SCREEN_HEIGHT);
        agents.push_back(temp);
        addObject(temp);
    }
    for(int i=0; i<30; ++i)
    {
        Plant* plant = new Plant(rand()%Screen::SCREEN_WIDTH, rand()%Screen::SCREEN_HEIGHT);
        addObject(plant);
    }
}

void Environment::getStarted()
{
    startTime = SDL_GetTicks();
    World::getStarted();
}

void Environment::addObjects(const Object_list& objects)
{
    int time = SDL_GetTicks() - startTime;

    if(time>=600)
    {
        population.clear();
        std::list<Agent*>::iterator it;
        for(it=agents.begin(); it!=agents.end(); ++it)
        {
            (*it)->getDNA();
            population.push_back(SGenome((*it)->getDNA(), (*it)->getFitness()));
        }
        population = geneticAlg.Epoch(population);
        initNewPopulation();
        startTime = SDL_GetTicks();
    }
    else if(objects.size()<40)
    {
        for(int i = objects.size(); i<=40; ++i)
        {
            Plant* plant = new Plant(rand()%Screen::SCREEN_WIDTH, rand()%Screen::SCREEN_HEIGHT);
            addObject(plant);
        }
    }
}

void Environment::initNewPopulation()
{
    World::clearObjects();
    agents.clear();
    for(int i=0; i<10; ++i)
    {
        Agent* temp = new Agent(rand()%Screen::SCREEN_WIDTH, rand()%Screen::SCREEN_HEIGHT, population[i].vecWeights);
        agents.push_back(temp);
        addObject(temp);
    }
    for(int i=0; i<30; ++i)
    {
        Plant* plant = new Plant(rand()%Screen::SCREEN_WIDTH, rand()%Screen::SCREEN_HEIGHT);
        addObject(plant);
    }
}
