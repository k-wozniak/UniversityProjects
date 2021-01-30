import numpy
from ANN import NeuralNetwork
from MINST_data import Mnist, Minst_Loader

def train_data(network, training_data):
    for d in training_data:
        targets = numpy.zeros(network.o_nodes) + 0.01
        targets[d.label] = 0.99
        network.train(d.values, targets)
#net = NeuralNetwork(784, 10000, 10, 0.1)

MNIST = Minst_Loader()

#print("Loading Train Data")
#training_data = MNIST.load_data("Handwriting-Recognition/MINIST/mnist_train.csv")
#print("Loading Test Data")
#test_data = MNIST.load_data("Handwriting-Recognition/MINIST/mnist_test.csv")

training_data = MNIST.load_data("Handwriting-Recognition/fashion_MNIST/fashion_mnist_train.csv")
test_data = MNIST.load_data("Handwriting-Recognition/fashion_MNIST/fashion_mnist_test.csv")

print("Begining Learning")
for nodes in [500]: #, 100, 500, 750
    for learning_rate in [0.05]: #numpy.arange(0.1, 0.4, 0.1):

        net = NeuralNetwork(784, nodes, 10, learning_rate)
        
        for training_iter in range(1, 21):
            train_data(net, training_data)

            scorecard = []
            for record in test_data:
                label = numpy.argmax(net.query(record.values))
                if label == record.label:
                    scorecard.append(1)
                else:
                    scorecard.append(0)

            scorecard_array = numpy.asarray(scorecard)
            performance = (scorecard_array.sum() / scorecard_array.size)*100
            #print("Network n = ", nodes, " LR = ", learning_rate, "Performance = ", (scorecard_array.sum() / scorecard_array.size)*100, '%')
            print(f'n = {nodes}  LR = {learning_rate:.2f},   TI = {training_iter},  Performance = {performance:.2f}')

 