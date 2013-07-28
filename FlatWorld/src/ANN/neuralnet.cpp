#include "../../include/ANN/neuralnet.h"

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
    for(unsigned c = 0; c < numOutputs; ++c)
    {
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = randomWeight();
    }

    m_myIndex = myIndex;
}

void Neuron::feedForward(const Layer &prevLayer)
{
    double sum = 0;

    for(unsigned n=0; n < prevLayer.size(); ++n)
    {
        sum += prevLayer[n].getOutputVal() *
                prevLayer[n].m_outputWeights[m_myIndex].weight;
    }

    m_output = Neuron::transferFunction(sum);
}

void Neuron::calcOutputGradients(double targetVal)
{
    double delta = targetVal - m_output;
    m_gradient = delta * Neuron::transferFunctionDerivative(m_output);
}

void Neuron::calcHiddenGradients(const Layer &nextLayer)
{
    double dow = sumDOW(nextLayer);
    m_gradient = dow * Neuron::transferFunctionDerivative(m_output);
}

void Neuron::updateInputWeights(Layer &prevLayer)
{
    for(unsigned n = 0; n <prevLayer.size(); ++n)
    {
        Neuron &neuron = prevLayer[n];
        double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

        double newDeltaWeight =
            // Individual input, magnified by the gradient and train rate;
            eta
            * neuron.getOutputVal()
            * m_gradient
            // Also add momentum = a fraction of the previous delta weight
            * alpha
            * oldDeltaWeight;

        neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
        neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
    }
}

double Neuron::sumDOW(const Layer &nextLayer) const
{
    double sum = 0;

    for(unsigned n = 0; n < nextLayer.size()-1; ++n)
    {
        sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
    }

    return sum;
}

double Neuron::transferFunction(double x)
{
    // tanh - output range [-1.0..1.0]
    return tanh(x);
}

double Neuron::transferFunctionDerivative(double x)
{
    // tanh derivative
    return 1.0 - x * x;
}

NeuralNet::NeuralNet(const std::vector<unsigned> &topology)
{
    // The size of the neural network
    unsigned numLayers = topology.size();
    for(unsigned layerNum = 0; layerNum<numLayers; ++layerNum)
    {
        // Create a new layer and then fill it with neurons and bias
        m_layers.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size() -1 ? 0 : topology[layerNum + 1];

        for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
        {
            m_layers.back().push_back(Neuron(numOutputs, neuronNum));
        }

        // Force the bias node's output value to 1
        m_layers.back().back().setOutputVal(1.0);
    }
}

NeuralNet::~NeuralNet()
{
    //dtor
}

void NeuralNet::feedForward(const std::vector<double> &inputVals)
{
    assert(inputVals.size() == m_layers[0].size()-1);

    // Assign the input values to the input neurons
    for(unsigned i = 0; i<inputVals.size(); ++i)
    {
        m_layers[0][i].setOutputVal(inputVals[i]);
    }

    // Forward propagate
    for(unsigned layerNum = 1; layerNum < m_layers.size(); ++ layerNum)
    {
        Layer &prevLayer = m_layers[layerNum -1];
        for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n)
        {
            m_layers[layerNum][n].feedForward(prevLayer);
        }
    }
}

void NeuralNet::backProp(const std::vector<double> &targetVals)
{
    // Calculate overall net error (RMS of output neruon errors)

    Layer &outputLayer = m_layers.back();
    m_error = 0;

    for(unsigned n = 0; n < outputLayer.size() -1; ++n)
    {
        double delta = targetVals[n] - outputLayer[n].getOutputVal();
        m_error += delta * delta;
    }
    m_error /= outputLayer.size() - 1; // Get average error squared
    m_error = sqrt(m_error); // RMS

    m_recentAverageError =
            (m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
            / (m_recentAverageSmoothingFactor + 1.0);

    // Calculate output layer gradients

    for(unsigned n=0; n < outputLayer.size() -1; ++n)
    {
        outputLayer[n].calcOutputGradients(targetVals[n]);
    }

    // Calculate gradients on hidden layers

    for(unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum)
    {
        Layer &hiddenLayer = m_layers[layerNum];
        Layer &nextLayer = m_layers[layerNum +1];

        for(unsigned n = 0; n < hiddenLayer.size(); ++n)
        {
            hiddenLayer[n].calcHiddenGradients(nextLayer);
        }
    }

    // For all layers from outputs to first hidden layer
    // update connection weights

    for(unsigned layerNum = m_layers.size() -1; layerNum > 0; --layerNum)
    {
        Layer &layer = m_layers[layerNum];
        Layer &prevLayer = m_layers[layerNum -1];

        for(unsigned n = 0; n <layer.size()-1; ++n)
        {
            layer[n].updateInputWeights(prevLayer);
        }
    }

}

void NeuralNet::getResults(std::vector<double> &resultVals) const
{
    resultVals.clear();

    for(unsigned n = 0; n < m_layers.back().size() -1; ++n)
    {
        resultVals.push_back(m_layers.back()[n].getOutputVal());
    }
}
