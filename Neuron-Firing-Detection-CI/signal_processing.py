''' signal_processing module

The module provides a simple singal processing toolbox for noise removal.
'''

import numpy as np
from scipy.signal import butter, lfilter, medfilt

''' Applies all filters in the module to the signal. '''
def filter_series(series, median_w = 7, mean_w = 3):
    series = bandpass_filter(series)
    series = median_filter(series, median_w)
    series = moving_mean_filter(series, mean_w)
    series = remove_values_below_MAD(series)
    return series

''' Applies an median filter to the signal'''
def median_filter(series, size):
    return medfilt(series, size)

''' Applies moving mean filter to the signal '''
def moving_mean_filter(series, size):
    # np.covolve applies convoution with a mean filter
    return (np.convolve(series, np.ones(size), 'same') / size) 

''' Applies butterfly filter to the signal '''
def bandpass_filter(sig, order = 1, lf=30, hf=5000):
    # butter is the butterfly filter from the scipy.signal
    b, a = butter(order, [lf, hf], btype='band', analog=False, fs=25000)
    sig = lfilter(b, a, sig)    # Applies filter
    sig[0:(2*lf)] = 0          # Clears noise from the begining of the signal
    return sig

''' Using Median absolute deviation, removes noise from the signal
    N has been chooses based on the training data and is specific to the 
    signal signature '''
def remove_values_below_MAD(series, N = 2.55):
    series = np.array(series)
    MAD = np.median(abs(series - np.median(series)))
    SD = 1.4826 * MAD
    THR = N * SD

    series = np.where(series > THR, series, 0)
    return series

