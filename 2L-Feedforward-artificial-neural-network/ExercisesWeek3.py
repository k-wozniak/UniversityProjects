from ANN import NeuralNetwork
'''
1.  Create a neural network instance with two inputs, two hidden neurons and one output neuron.
    Create some tests inputs and query the network (without and training), how do you explain the networks outputs?
'''
network = NeuralNetwork(2, 6, 1, 2)
simpleQuery = [[0,0], [0,1], [1,0], [1,1]]

#for x in simpleQuery:
#    print(x, network.query(x))

'''
2.  Create a set of training vectors for all possible inputs and target vector for one of the logical functions such as AND.
'''
training_AND = [[[0, 0], [0]], [[0, 1], [0]], [[1, 0], [0]], [[1, 1], [1]]]
training_XOR = [[[0, 0], [0]], [[0, 1], [1]], [[1, 0], [1]], [[1, 1], [0]]]

'''
3.  Train the network once for each target, then query the network for all possible inputs. Has your
    successfully learned the AND function? If not, then why not?

for data in training_AND:
    network.train(data[0], data[1])

for x in simpleQuery:
    print(x, network.query(x))

'''
'''
4. Extend your training routine to repeat the training process more than once for each target,
    how many iterrations does it take for the network to learn the AND function with two inputs?
'''
for a in range(1000):
    for data in training_XOR:
        network.train(data[0], data[1])

for x in simpleQuery:
    print(x, network.query(x))
'''
5.  Experiment with the number of neurons in the hidden layer, and the learning rate, what effect do these
    have on training the AND function?
'''

'''
6.  If you have time, try other functions, such as XOR. What effect do the number of neurons in the hidden layer have and why?
'''

'''
7.  How do these effects scale if you create, for example, a 4 input logical function?
'''