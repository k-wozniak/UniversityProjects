import scipy.special
import numpy as np
import mxnet as mx

# Neural network class definition
class NeuralNetwork:
    def __init__(self, input_nodes, hidden_nodes, output_nodes, learning_rate):
        # Set the number of nodes in each input, hidden and output layer
        self.i_nodes = input_nodes
        self.h_nodes = hidden_nodes
        self.o_nodes = output_nodes

        # Weight matrices, wih (inpput -> hidden) and who (hidden -> output)
        self.wih = np.random.normal(0.0, pow(self.h_nodes, -0.5), (self.h_nodes, self.i_nodes))
        self.who = np.random.normal(0.0, pow(self.o_nodes, -0.5), (self.o_nodes, self.h_nodes))

        # Set the learning rate
        self.lr = learning_rate
        self.activation_function = lambda x: mx.gluon.nn.Swish(x)
        #self.activation_function = lambda x: scipy.special.expit(x)

    # Train the network using back-propagation of errors
    def train(self, inputs_list, target_list):
        # Convert inputs into 2D arrays
        input_array = np.array(inputs_list, ndmin=2).T
        targets_array = np.array(target_list, ndmin=2).T

        # Calculate singals into and out of the hidden layer 
        hidden_inputs = np.dot(self.wih, input_array)
        hidden_outputs = self.activation_function(hidden_inputs)

        # Calculate signals into and out of the final layer
        final_inputs = np.dot(self.who, hidden_outputs)
        final_outputs = self.activation_function(final_inputs)

        # Calculate last and hidden layer errors
        output_errors = targets_array - final_outputs
        hidden_errors = np.dot(self.who.T, output_errors)

        # Update the weights for the links between the hidden and output layers
        self.who += self.lr * np.dot((output_errors * final_outputs * (1.0 - final_outputs)), np.transpose(hidden_outputs))
        self.wih += self.lr * np.dot((hidden_errors * hidden_outputs * (1.0 - hidden_outputs)), np.transpose(input_array))

    # Wuery the network
    def query(self, inputs_list):
        inputs_array = np.array(inputs_list, ndmin=2).T
        
        # Hidden layer calculations
        hidden_inputs = np.dot(self.wih, inputs_array)
        hidden_outputs = self.activation_function(hidden_inputs)

        # Final layer calculations
        final_inputs = np.dot(self.who, hidden_outputs)
        final_outputs = self.activation_function(final_inputs)

        return final_outputs

    def printWeights(self):
        print(self.wih)
        print(self.who)

# Neural network class definition
class MultiLayerNeuralNetwork:
    # layers inputs as array [input, ..., output]
    def __init__(self, nodes, learning_rate):
        # Set the number of nodes in each input, hidden and output layer
        self.nodes = nodes
        self.weightsLayers = (len(nodes) - 1)

        self.lr = learning_rate
        self.activation_function = lambda x: scipy.special.expit(x)

        self.WLayers = []
        for layer in range(0, (len(nodes) - 1)):
            self.WLayers.append(np.random.normal(0.0, pow(nodes[layer], -0.5), (nodes[layer], nodes[layer+1]))) 

    # Train the network using back-propagation of errors
    #def train(self, inputs_list, target_list):
        # Convert inputs into 2D arrays
        #input_array = np.array(inputs_list, ndmin=2).T
        #targets_array = np.array(target_list, ndmin=2).T

        # Calculate singals into and out of each layer
        #for layer in self.WLayers:
            
        # Calculate singals into and out of the hidden layer 
        #hidden_inputs = np.dot(self.wih, input_array)
        #hidden_outputs = self.activation_function(hidden_inputs)

        # Calculate signals into and out of the final layer
        #final_inputs = np.dot(self.who, hidden_outputs)
        #final_outputs = self.activation_function(final_inputs)

        # Calculate last and hidden layer errors
        #output_errors = targets_array - final_outputs
        #hidden_errors = np.dot(self.who.T, output_errors)

        # Update the weights for the links between the hidden and output layers
        #self.who += self.lr * np.dot((output_errors * final_outputs * (1.0 - final_outputs)), np.transpose(hidden_outputs))
        #self.wih += self.lr * np.dot((hidden_errors * hidden_outputs * (1.0 - hidden_outputs)), np.transpose(input_array))

    # Wuery the network
    def query(self, inputs_list):
        inputs_array = np.array(inputs_list, ndmin=2).T
        
        # Hidden layer calculations
        hidden_inputs = np.dot(self.wih, inputs_array)
        hidden_outputs = self.activation_function(hidden_inputs)

        # Final layer calculations
        final_inputs = np.dot(self.who, hidden_outputs)
        final_outputs = self.activation_function(final_inputs)

        return final_outputs