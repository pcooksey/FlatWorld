#include "..\include\world.h"

World::World()
 : success(false), objects()
{
    screen = NULL;
    success = init();
}

World::~World()
{
    for(std::list<Object*>::iterator it=objects.begin(); it!=objects.end(); ++it)
    {
        delete (*it);
    }

    SDL_DestroySemaphore( runLock ); //Destroy semaphore
    SDL_Quit(); //Quit SDL
}

bool World::init()
{
    // Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return false;

    // Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    // If there was an error in setting up the screen
    if( screen == NULL )
        return false;

    // Create the semaphore
    runLock = SDL_CreateSemaphore( 1 );

    // Set the window caption
    SDL_WM_SetCaption( "Flat World", NULL );

    // If everything initialized fine
    return true;
}

void World::getStarted()
{
    bool quit = false;
    running = true;
    SDL_Thread *thread = SDL_CreateThread( starter, this );
    SDL_Event event;
    while(!quit)
    {
        // Check if user wants to quit
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
                setRunning(false); // Stop the thread
                SDL_WaitThread( thread, NULL ); //Waits for thread to end
            }
        }
    }
}

int World::starter(void *data)
{
    return ((World*)data)->start();
}

int World::start()
{
    // The frame rate regulator
    int delta = SDL_GetTicks(), time;
    // Object iterator
    std::list<Object*>::iterator obj;

    while(getRunning())
    {
        // Check for future collisions of objects
        collisionDetection(time);

        // Removes all objects that died in the collision phase
        objects.remove_if(died);

        // Time (dt) between frames **No need for fps**
        time = (SDL_GetTicks() - delta);

        // Move all objects in the world using their velocities
        for(obj = objects.begin(); obj!=objects.end(); ++obj)
        {
            // Objects will be able to look around the world during @move()
            (*obj)->move(screen, time);
        }

        // Start clock over for time (dt)
        delta = SDL_GetTicks();

        // Clean the screen to black
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) );

        addObjects(objects);

        // Place all the objects into the world
        for(obj = objects.begin(); obj!=objects.end(); ++obj)
        {
            (*obj)->show(screen);
        }

        // Update Screen
        if(SDL_Flip( screen ) == -1)
            return 1;
    }

    return 0;
}

void World::setRunning(bool run)
{
    SDL_SemWait( runLock ); //Lock
    running = run;
    SDL_SemPost( runLock ); //unlock
}

bool World::getRunning()
{
    SDL_SemWait( runLock ); //Lock
    bool run = running;
    SDL_SemPost( runLock ); //unlock
    return run;
}

void World::clearObjects()
{
    Object_list::iterator it;
    for(it=objects.begin(); it!=objects.end(); ++it)
    {
        delete (*it);
    }
    objects.clear();
}

void World::addObject(Object* temp)
{
    objects.push_back(temp);
}

void World::collisionDetection(int time)
{
    // Object iterator
    std::list<Object*>::iterator obj, check;
    int objx, objy, checkx, checky;
    for(obj = objects.begin(); obj!=objects.end(); ++obj)
    {
        objx = (*obj)->Getx() + (*obj)->GetxVel() * (time / 100.f);
        objy = (*obj)->Gety() + (*obj)->GetyVel() * (time / 100.f);
        for(check = --objects.end(); check!=obj; --check)
        {
            checkx = (*check)->Getx() + (*check)->GetxVel() * (time / 100.f);
            checky = (*check)->Gety() + (*check)->GetyVel() * (time / 100.f);

            if( objy + (*obj)->Object_HEIGHT() <= checky
                || objy >= checky + (*check)->Object_HEIGHT()
                || objx + (*obj)->Object_WIDTH() <= checkx
                || objx >= checkx + (*check)->Object_WIDTH() )
            {} else {
                // Set the velocity of the object to zero
                /*float velxObj = (*obj)->GetxVel();
                float velyObj = (*obj)->GetyVel();
                (*obj)->SetxVel((*check)->GetxVel());
                (*obj)->SetyVel((*check)->GetyVel());
                (*check)->SetxVel(velxObj);
                (*check)->SetyVel(velyObj); */

                // Only make object collide with check
                (*obj)->collision(*check);
            }
        }
    }
}
