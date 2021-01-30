''' feature_extraction_KNN module

Contains functions which allow to extract features from a given signal window.
'''
import numpy as np

''' FeatureExtraction class contains the extraction functions '''
class FeatureExtraction:
    ''' Extracts features for a set of windows and returns an array '''
    def extract_features_from_dataset(self, data_set):
        return [self.extract_features_from_window(i) for i in data_set]

    ''' Extracts all avaliable features from the given window '''
    def extract_features_from_window(self, data):
        self.data = data

        features = []
        features.append(self.integration())
        features.append(self.modified_mean_absolute_value())
        features.append(self.simple_square_integral())
        features.append(self.signal_variance())
        features.append(self.root_mean_square())
        #features.append(self.willison_amplitude())

        f_mean, f_median = self.mean_and_median_frequency()
        features.append(f_mean)
        features.append(f_median)

        return features

    ''' Estimates the area under the graph '''
    def integration(self):
        return np.trapz(self.data, axis=0)

    ''' Estimates mean absolut value with adaptable weighting '''
    def modified_mean_absolute_value(self):
        self.N = len(self.data)
        s = np.sum([(self.weight(i) * i) for i in self.data])
        
        return (s/self.N)

    ''' Generates the weight for the modifed mean values '''
    def weight(self, n):
        N = self.N
        if n < (0.25*N): # Below 25% of the values
            return (4*n)/N
        if n > (0.75*N): # Above 75% of the values
            return (4*(n - N)) / N
        return 1    # Else

    ''' Finds the sum of the squares of every point '''
    def simple_square_integral(self):
        return np.sum(np.square(self.data))

    ''' Estimates Varience in the window '''
    def signal_variance(self):
        return np.var(self.data)

    ''' Estimates MRS in the window '''
    def root_mean_square(self):
        return np.sqrt(np.mean(np.square(self.data)))

    ''' Estimates Willson amplitude 
        Further information about the technique in the report '''
    def willison_amplitude(self):
        # Value found experimentally by plotting a graph of different
        # values and finding one where non of the values were 0 or max
        THRESHOLD = 0.08

        WAMP = 0
        for x in range(0, len(self.data) - 1):
            diff = self.data[x] - self.data[x+1]
            abs_diff = abs(diff)

            if abs_diff > THRESHOLD:
                WAMP = WAMP + 1

        return WAMP

    ''' Estimated the mean and median frequency (FFT based)'''
    def mean_and_median_frequency(self):
        ps = np.abs(np.fft.rfft(self.data, axis=0))*2
        return np.mean(ps), np.median(ps)