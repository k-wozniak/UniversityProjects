''' model_KNN module

Provides class for k nearest neighbor classification of spikes.
'''

import os
import numpy as np
import matplotlib.pyplot as plt

import sklearn
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report, confusion_matrix

import performance_metrics as PM
import data_loading as DL
import signal_processing as SP
from data_loading import load_dataset
from feature_extraction_KNN import FeatureExtraction

''' Class which include the k nearest neighbor logic '''
class KNN:
    ''' During the model initialisation data are loaded from a file. 
        Then they are divided into train and test data.
        Consequenlty, features are extracted and scaled.
    '''
    def __init__(self, train_x, train_y, test_x, test_y):
        self.train_x = train_x
        self.train_y = train_y
        self.test_x = test_x
        self.test_y = test_y
        
        fe = FeatureExtraction()
        self.train_x = fe.extract_features_from_dataset(self.train_x)
        self.test_x = fe.extract_features_from_dataset(self.test_x)
        self.scale_features()

        '''
        The following line of code can replace the custom FeatureExtraction()
        It is part of the sklearn.metric module and computes the features
        based on the principle component analysis

        self.test_x, self.train_x = principal_component_analysis(self.test_x, self.train_x)
        '''

    ''' Generates a windows from the signal and the index positions '''
    def spectra_window(self, d, Index, Class):
        dataX = []
        dataY = Class

        for x in range(0, len(Index)):
            pos = Index[x]
            dataX.append(d[(pos - 5):(pos + 45)])

        return dataX, dataY

    ''' Using sklearn functoins normalises the features around the mean '''
    def scale_features(self):
        scaler = StandardScaler()
        scaler.fit(self.train_x)

        self.train_x = scaler.transform(self.train_x)
        self.test_x = scaler.transform(self.test_x)

    ''' Trains the model using known values '''
    def train(self, n_neighbors = 5):
        self.classifier = KNeighborsClassifier(n_neighbors)
        self.classifier.fit(self.train_x, self.train_y)

    ''' Uses the model to predict test data '''
    def predict(self):
        self.predicted_y = self.classifier.predict(self.test_x)


# Applies principal component analysis to remove any redundant features
def principal_component_analysis(train_x, test_x):
    pca = sklearn.decomposition.PCA()
    pca = pca.fit(train_x)

    train_x = pca.transform(train_x)
    test_x = pca.transform(test_x)

    return train_x, test_x

def plot_scatter(model):
    colours = ['red','green','blue','orange']
    labelled_colours = [colours[i-1] for i in model.train_y]

    plt.scatter(model.train_x[:,0], model.train_x[:,1],s=0.5,color=(labelled_colours))
    plt.show()

def plot_maen_diagram(max_k):
    error = []

    for i in range(1, max_k):
        model.train(i)
        model.predict()
        error.append(np.mean((model.predicted_y != model.test_y)))

    plt.figure(figsize=(12, 6))
    plt.plot(range(1, max_k), error, color='red', linestyle='dashed', marker='o',
            markerfacecolor='blue', markersize=10)
    plt.title('Error Rate K Value')
    plt.xlabel('K Value')
    plt.ylabel('Mean Error')
    plt.show()


''' 
    Code for running the KNN training and testing
'''

# Get data set
data_x, data_y, test_data_x, test_data_y = DL.loda_and_split_data('data/training.mat')
data_y = [i[0] for i in data_y]
skipped = np.sum([len(i)-1 for i in test_data_y])
test_data_y = [i[0] for i in test_data_y]

# Train the model and predict data for chart generation
model = KNN(data_x, data_y, test_data_x, test_data_y)
model.train(6)
model.predict()

# Plot predicted data from the chart
PM.plot_confusion_matrix(model.test_y, model.predicted_y)
print(PM.calculate_metrics(model.test_y, model.predicted_y))
plot_scatter(model)

# Generates models with multiple k parameters and plots the accuracy
plot_maen_diagram(50)