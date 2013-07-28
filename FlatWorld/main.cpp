#include "SDL/SDL.h"
#include "include\world.h"
#include "include\agent.h"
#include "include\ANN\neuralnet.h"

#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>

//int nums[] = {2,3,1};
//std::vector<unsigned> topology2 (nums, nums + sizeof(nums) / sizeof(int) );

int main( int argc, char* args[] )
{
    srand (time(NULL));
    /* // Test the ANN with a simple xOr
    NeuralNet network(topology2);
    std::vector<double> input, target, result;
    int a,b,c;

    for(int i=0; i<2000; ++i)
    {
        a=rand()%2;
        b=rand()%2;
        c=a^b;
        input.clear();
        input.push_back(a);
        input.push_back(b);
        network.feedForward(input);
        std::cout<<"Input: "<<a<<" "<<b<<std::endl;
        network.getResults(result);
        std::cout<<"Target: "<<c<<std::endl;
        std::cout<<"Result: "<<result[0]<<std::endl;
        target.clear();
        target.push_back(c);
        network.backProp(target);
        std::cout <<"Average error: "<< network.getRecentAverageError() <<std::endl<<std::endl;

    }
    */
    World world;
    if(world.successful()==false)
        return 1;
    Agent temp;
    world.addObject(&temp);
    world.getStart();
    return 0;
}
