import numpy
import matplotlib.pyplot as plt
from ANN import NeuralNetwork

def load_data(path):
    training_data_file = open(path, 'r')
    training_data_list = training_data_file.readlines()
    training_data_file.close()

    return training_data_list

def train_data(network, training_data):
    for record in training_data:
        all_values = record.split(',')
        inputs = (numpy.asfarray(all_values[1:])/255.0*0.99) + 0.01
        
        targets = numpy.zeros(network.o_nodes) + 0.01
        targets[int(all_values[0])] = 0.99

        network.train(inputs, targets)
    pass

def show_image(to_display):
    image_array = numpy.asfarray(to_display).reshape((28, 28))
    plt.imshow(image_array, cmap='Greys', interpolation='None')
    plt.show()

net = NeuralNetwork(784, 100, 10, 0.3)
training_data = load_data("Handwriting-Recognition/MINIST/mnist_train_100.csv")
test_data = load_data("Handwriting-Recognition/MINIST/mnist_test_10.csv")
scorecard = []

net.printWeights()

train_data(net, training_data)

for record in test_data:
    all_values = record.split(',')
    correct_label = int(all_values[0])

    inputs = (numpy.asfarray(all_values[1:]) / 255.0 * 0.99) + 0.01
    outputs = net.query(inputs)
    label = numpy.argmax(outputs)

    print(correct_label, "Correct label")
    print(label, "Network label")

    if label == correct_label:
        scorecard.append(1)
    else:
        scorecard.append(0)
        show_image(inputs)
    pass
pass

scorecard_array = numpy.asarray(scorecard)
print("Performance = ", (scorecard_array.sum() / scorecard_array.size)*100, '%')
