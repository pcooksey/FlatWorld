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
class NeuralNet;

typedef std::vector<Neuron> Layer;
typedef std::vector<double> Weights;

// ************** class Neuron *******************

class Neuron
{
    public:
        Neuron(unsigned numOutputs, unsigned myIndex);
        Neuron(unsigned numOutputs, unsigned myIndex, Weights& weights);
        void setOutputVal(double val) { m_output = val;};
        double getOutputVal() const { return m_output;};
        void feedForward(const Layer &prevLayer);
        void calcOutputGradients(double targetVal);
        void calcHiddenGradients(const Layer &nextLayer);
        void updateInputWeights(Layer &prevLayer);
        Weights getWeights();

    private:
        static const double eta = 0.15; // [0.0..1.0] overall net training rate
        static const double alpha = 0.5; // [0.0..n] multiplier of last weight change
        static double randomWeight() { return (rand()/(double(RAND_MAX)/2))-1; };
        static double transferFunction(double x);
        static double transferFunctionDerivative(double x);
        double sumDOW(const Layer &nextLayer) const;
        double m_output;
        unsigned m_myIndex;
        double m_gradient;
        std::vector<Connection> m_outputWeights;

        friend class NeuralNet;
};

// ************** class NeuralNet ****************

class NeuralNet
{
    public:
        NeuralNet(const std::vector<unsigned> &topology);
        NeuralNet(const std::vector<unsigned> &topology, const std::vector<double> &net);
        virtual ~NeuralNet();

        void feedForward(const std::vector<double> &inputVals);
        void backProp(const std::vector<double> &targetVals);
        void getResults(std::vector<double> &resultVals) const;
        double getRecentAverageError() const { return m_recentAverageError; }
        const std::vector<Layer>& getNet() { return m_layers; }
        std::vector<double> getDNA();

    protected:
    private:
        std::vector<Layer> m_layers; //layer[layerNum][neuronNum]
        double m_error;
        double m_recentAverageError;
        static const double m_recentAverageSmoothingFactor = 100; // Number of training samples to average over
};

#endif // NEURALNET_H
