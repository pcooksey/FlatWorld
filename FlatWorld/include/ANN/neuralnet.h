#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>

struct Connection
{
    double weight;
    double deltaWeight;
};

class Neuron;

typedef std::vector<Neuron> Layer;

// ************** class Neuron *******************

class Neuron
{
    public:
        Neuron(unsigned numOutputs, unsigned myIndex);
        void setOutputVal(double val) { m_output = val;};
        double getOutputVal() const { return m_output;};
        void feedForward(const Layer &prevLayer);
        void calcOutputGradients(double targetVal);
        void calcHiddenGradients(const Layer &nextLayer);
        void updateInputWeights(Layer &prevLayer);

    private:
        static double eta; // [0.0..1.0] overall net training rate
        static double alpha; // [0.0..n] multiplier of last weight change
        static double randomWeight() { return rand()/double(RAND_MAX); };
        static double transferFunction(double x);
        static double transferFunctionDerivative(double x);
        double sumDOW(const Layer &nextLayer) const;
        double m_output;
        unsigned m_myIndex;
        double m_gradient;
        std::vector<Connection> m_outputWeights;
};

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

// ************** class NeuralNet ****************

class NeuralNet
{
    public:
        NeuralNet(const std::vector<unsigned> &topology);
        virtual ~NeuralNet();

        void feedForward(const std::vector<double> &inputVals);
        void backProp(const std::vector<double> &targetVals);
        void getResults(std::vector<double> &resultVals) const;
    protected:
    private:
        std::vector<Layer> m_layers; //layer[layerNum][neuronNum]
        double m_error;
        double m_recentAverageError;
        double m_recentAverageSmoothingFactor;
};

#endif // NEURALNET_H
