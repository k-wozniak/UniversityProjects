import numpy
import matplotlib.pyplot as plt
from scipy import ndimage, misc

class Mnist:
    def __init__(self, record):
        values = record.split(',')

        self.label = int(values[0])
        self.values = (numpy.asfarray(values[1:])/255.0*0.99) + 0.01

    def show(self):
        image_array = numpy.asfarray(self.values).reshape((28, 28))
        plt.imshow(image_array, cmap='Greys', interpolation='None')
        plt.show()

class Minst2:
    def __init__(self, record):
        values = record.split(',')

        self.label = int(values[0])
        self.values = (numpy.asfarray(values[1:])/255.0*0.99) + 0.01

    def show(self):
        image_array = numpy.asfarray(self.values).reshape((28, 28))
        plt.imshow(image_array, cmap='Greys', interpolation='None')
        plt.show()

class Minst_Loader:
    def load_data(self, path):
        training_data_file = open(path, 'r')
        training_data_list = training_data_file.readlines()
        training_data_file.close()

        output = [Mnist(r) for r in training_data_list]
        return output

    def load_train_data(self, path):
        training_data_file = open(path, 'r')
        training_data_list = training_data_file.readlines()
        training_data_file.close()

        output = []
        for d in training_data_list:
            output.append(Mnist(d))
            
            '''
            for angle in [-15, 15]:
                m = Mnist(d)
                squre_array = numpy.asfarray(m.values).reshape((28, 28))
                rotated_squre_array = ndimage.rotate(squre_array, angle, reshape=False, cval=0.01)
                m.values = numpy.ravel(rotated_squre_array)

                output.append(m)'''

        return output