''' model_CNN module

Provides the class for CNN classification of spikes.
'''
import keras
from keras.models import Sequential, load_model
from keras.layers import Dense, Dropout, Reshape, GlobalAveragePooling1D
from keras.layers import Conv1D, MaxPooling1D

from matplotlib import pyplot as plt
import os
import numpy as np

import performance_metrics as PM
import data_loading as DL
import signal_processing as SP

from sklearn import metrics
import tensorflow as tf

from bayes_opt import BayesianOptimization

''' Class which include the CNN logic '''
class CNN:
    ''' Performs a training of the CNN model'''
    def train(self, data_x, data_y, batch_size = 50, epochs = 80, val_split = 0.01):
        number_of_classes = 4
        data_y = DL.convert_to_one_hot(data_y, number_of_classes)
        
        # Convert to floats as reqired by the model
        data_x = np.asarray(data_x).astype(np.float32)
        data_y = np.asarray(data_y).astype(np.float32)

        self.model = self.generate_model(data_x.shape[1], 1, number_of_classes)

        callbacks_list = [
            keras.callbacks.EarlyStopping(monitor='accuracy', patience=5)
        ]

        self.history = self.model.fit(data_x, data_y, batch_size, epochs,
                                    callbacks=callbacks_list,
                                    validation_split=0.05,
                                    verbose=2)

        p = self.test_trained_model(data_x, data_y)
        self.thresholds = PM.calculate_optimal_thresholds(data_y, p)

    def test_trained_model(self, test_x, test_y):
        self.test_x = np.asarray(test_x).astype(np.float32)
        self.test_y = np.asarray(test_y).astype(np.float32)
        self.test_y_predict = self.model.predict(self.test_x)
        return self.test_y_predict

    ''' Generates a model to the input specifications '''
    def generate_model(self, window_width, window_height = 1, num_classes = 4):
        input_shape = (window_width*window_height)

        model_m = Sequential()
        model_m.add(Reshape((window_width, window_height), input_shape=(input_shape,))) # 100
        model_m.add(Conv1D(120, 10, activation='swish', input_shape=(window_width, window_height))) # 100
        model_m.add(Conv1D(120, 10, activation='swish'))
        model_m.add(MaxPooling1D(3))
        model_m.add(Conv1D(180, 10, activation='swish')) # 160
        model_m.add(Conv1D(180, 5, activation='swish')) # 160
        model_m.add(GlobalAveragePooling1D())
        model_m.add(Dropout(0.5))
        model_m.add(Dense(num_classes, activation='sigmoid'))
        print(model_m.summary())
        
        model_m.compile(loss='binary_crossentropy',
                        optimizer='RMSprop',
                        metrics=['accuracy',])

        return model_m

    def calculate_metrics(self):
        # Change one hot encoding to numbers
        true_y = np.argmax(self.test_y, axis=1)
        predicted_y = np.argmax(self.test_y_predict, axis=1)

        return PM.calculate_metrics(true_y, predicted_y)

    ''' Provides the information about the model'''
    def plot_metrics(self):
        self.summarize_history()

        # Change one hot encoding to numbers
        true_y = np.argmax(self.test_y, axis=1)
        predicted_y = np.argmax(self.test_y_predict, axis=1)

        PM.plot_confusion_matrix(true_y, predicted_y)
        PM.plot_roc_curve(self.test_y, self.test_y_predict)

        print(self.calculate_metrics())

    ''' Takes the metrics and plots the learning curve of the CNN '''
    def summarize_history(self):
        history = self.history
        print("\n--- Learning curve of model training ---\n")

        # summarize history for accuracy and loss
        acc = history.history['accuracy']
        val_acc = history.history['val_accuracy']
        loss = history.history['loss']
        val_loss = history.history['val_loss']
        #auc = history.history['auc']

        plt.figure(figsize=(6, 4))
        plt.plot(acc, "g--", label="Accuracy of training data")
        plt.plot(val_acc, "g", label="Accuracy of validation data")
        plt.plot(loss, "r--", label="Loss of training data")
        plt.plot(val_loss, "r", label="Loss of validation data")
        plt.title('Model Accuracy and Loss')
        plt.ylabel('Accuracy and Loss')
        plt.xlabel('Training Epoch')
        plt.ylim(0)
        plt.legend()
        plt.show()

    ''' Funciton called to predict values using the model '''
    def predict(self, windows):
        windows = np.asarray(windows).astype(np.float32)
        predicitons = self.model.predict(windows)
        predicitons = self.threshold_results(predicitons)
        predicitons = DL.convert_from_one_hot(predicitons)
        return predicitons

    ''' Thresholding the vlaues to obtain the actuall output.
        Thresholds can be adjustd individiually for reach class
    '''
    def threshold_results(self, results):
        results = np.array(results)

        for x in range(len(self.thresholds)):
            col = results[:, x]
            col[col >= self.thresholds[x]] = 1
            col[col <= self.thresholds[x]] = 0
            results[:, x] = col
    
        return results.tolist()

train_x, train_y, test_x, test_y = DL.loda_and_split_data('data/training.mat', split = 0.95)
test_data_y_hot = DL.convert_to_one_hot(test_y, 4)

model = CNN()
model.train(train_x, train_y, val_split=0.01)
model.test_trained_model(test_x, test_data_y_hot)
print(model.calculate_metrics())
model.plot_metrics()

signal, _, _ = DL.load_dataset('data/submission.mat')
filtered = SP.filter_series(signal)
submission_x, submission_locations = DL.generate_images(signal, filtered, 60)
submission_y = model.predict(submission_x)


a = np.zeros(len(submission_y), 1)
PM.plot_confusion_matrix(submission_y, a)
DL.save_data(submission_y, submission_locations)