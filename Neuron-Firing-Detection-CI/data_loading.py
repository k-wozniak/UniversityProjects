''' data_loading module

Funcion used to load the files, generate windows and convert notations.s
'''

import os
import scipy.io as scipy
import numpy as np
import signal_processing as sp

from matplotlib import pyplot as plt

''' Loads the .mat file. If file do not contains a set, returns empty list '''
def load_dataset(file_name_and_path):
    THIS_FOLDER = os.path.dirname(os.path.abspath(__file__))
    my_file = os.path.join(THIS_FOLDER, file_name_and_path)
    mat = scipy.loadmat(my_file, squeeze_me=True)

    # Get data if exist from the loaded structure 
    data = mat['d'] if 'd' in mat else []
    Index = mat['Index'] if 'Index' in mat else []
    Class = mat['Class'] if 'Class' in mat else []

    return data, Index, Class

''' Saves computed data (series, Class Index) to the .mat file '''
def save_data(data_y, locations, file_name = "11525.mat"):
    Class = []
    Index = []
    
    # Computes class and index information from a windows & locations
    # Required as in one windows multiple peaks could be found
    # If true, peaks will be placed at the begining location next to each other
    for i in range(0, len(data_y)):
        if isinstance(data_y[i], list):
            for j in range(0, len(data_y[i])):            
                Class.append(data_y[i][j])
                Index.append(locations[i]+j)
        else:
            Class.append(data_y[i])
            Index.append(locations[i])

    # Generates final structure
    mat = {
        "Class": Class,
        "Index": Index
    }

    scipy.savemat(file_name, mat)

''' Performs similar operation to an (Mathematical Morphology) opening 
    Where the signal of values above 0 is extended on each side based on the
    input values. For example: (front = 3, tail = 1)
    MASK: 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1 0
    OUT : 0 0 0 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1
'''
def extend_mask(mask, front = 5, tail = 10):
    for index in np.nonzero(mask)[0]:
        for position in range(index-front-1, index+tail):
            if position < len(mask):
                mask[position] = 1
    return mask

''' Generates images from a signal based on the filtered signal
    Returns windows and their begining location
'''
def generate_images(series, filtered, window_size=60):
    # Generate mask (extended filtered image). Then apply mask to the series
    # Removing all nosie. Consequenlty, any value should have a peak in it.
    # Marking the begining of the window
    mask = extend_mask(filtered)
    series = sp.bandpass_filter(series)
    series = np.where(mask > 0, series, 0)
    
    locations = []
    output = []
    is_peak = False
    peak_start_position = 0
    peak_end_position = 0

    # Checks every non zero value in the filtered signal
    # Then records length wehre peak has ended 
    # Lastly, copies the range to the new window
    # Consequenlty, a window should consist of only one peak or multiple 
    # Combined peaks
    for i in range(len(filtered)):
        if (filtered[i] > 0):
            if  (is_peak == False):
                is_peak = True
                peak_start_position = i
        if filtered[i] == 0.0 and is_peak:
            is_peak = False
            peak_end_position = i
            peak_range = peak_end_position - peak_start_position

            peak_range, peak_end_position = boundry_check(peak_range, 
                                            peak_start_position, window_size)
            i = peak_end_position # in case the peak must be cut off 

            output.append(get_new_window(series, peak_start_position, 
                            peak_end_position, window_size))
            locations.append(peak_start_position)

    return output, locations

''' Function equivalent to the generate_images but rather than automatically
    detect peaks, it base the starting positins on the index position provided
'''
def generate_training_images(series, filtered, Index, Class, window_size=60):
    # Generate mask (extended filtered image). Then apply mask to the series
    # Removing all nosie. Consequenlty, any value should have a peak in it.
    # Marking the begining of the window
    mask = extend_mask(filtered)
    series = sp.bandpass_filter(series)
    series = np.where(mask > 0, series, 0)
    
    locations = []
    data_y = []
    data_x = []

    # Generates a histogram with every class at it's position
    # Amplitude denotes the class type
    spectra = np.zeros(len(series), dtype=int)
    for x in range(len(Class)):
        spectra[Index[x]] = Class[x]

    # Generates a window with a constant size but adaptive fitering 
    # To avoide multiple spikes in a window
    for i in Index:
        SHIFT_LEFT = 5 # Shifts the window left to include multiple peaks together
        start_position = i - SHIFT_LEFT
        j = SHIFT_LEFT

        is_peak = series[start_position] > 0

        # Finds the range where the peak existis and then copies it to the window
        while start_position+j < len(series):
            current_val = series[start_position+j]
            # If peak was already detected and the value hits 0.0 (filtered mask)
            # stop the range search
            if current_val == 0.0 and is_peak:
                break
            
            # If value larger than 0 begining of a peak
            if current_val > 0.0:
                is_peak = True

            j = j + 1 

        r, e_pos = boundry_check(j, start_position, window_size)
        data_x.append(get_new_window(series, start_position, e_pos, window_size))    
        data_y.append(sorted(k for k in spectra[start_position-5:e_pos] if k > 0))
        locations.append(start_position)

    return data_y, data_x, locations

''' Checks if the range is allowed, if not shifts the range to max_range
    and returns correct end position
'''
def boundry_check(window_range, start_pos, max_range):
    if window_range > max_range:
        window_range = max_range
        end_pos = start_pos + max_range
    else:
        end_pos = start_pos + window_range

    return window_range, end_pos

''' Generates a new empty window and copies the range from a signal '''
def get_new_window(spike_series, start, end, window_size):
    window = np.zeros(window_size)
    window[0:(end-start)] = spike_series[start:end]
    return window

''' Converts an y_data encoding to a one hot values (of given length n)
    For example: [2, 3] (Window contains classes 2 and 3, with n = 4)
    Output: 0 1 1 0
'''
def convert_to_one_hot(data, n):
    arr = []
    for data_row in data: # itterates through each data row
        types = [0] * n # allocates all zero (non active)
        if isinstance(data_row, list): # If multiple classes present
            for t in data_row:
                types[t-1] = 1
        else: # if only one class present
            types[data_row-1] = 1

        arr.append(types)

    return arr

''' Converts a list of one hot values to a list of natural values '''
def convert_from_one_hot(data):
    return [one_hot_to_array(d) for d in data]

''' Converts a list of one hot values to corresponding class values
    For example: [0 1 1 0]
    Return [2, 3]
'''
def one_hot_to_array(data_row):
    arr = []
    for i in range(len(data_row)):
        if data_row[i] > 0:
            arr.append(i)

    return arr

''' Splits the data set to two section sections based on the split_value '''
def split_dataset_for_training_and_testing(signal, Index, Class, split_value = 0.95):
    split_count = int(len(signal)*split_value)

    train_index = []
    train_class = []
    test_index = []
    test_class = []

    # If before index add to training data if affter append to the training
    for position in range(len(Index)):
        if Index[position] < split_count:
            train_index.append(Index[position])
            train_class.append(Class[position])
        else:
            test_index.append(Index[position]-split_count)
            test_class.append(Class[position])

    return signal[:split_count], train_index, train_class, signal[split_count:], test_index, test_class

''' Generates the window informaiton from predicted windows for testing '''
def generate_y_classes_from_proximity_to_window(locations, test_index, test_class, signal_size):
    max_dist = 30
    
    # Produces a histogram of locations of classes 
    histogram = np.zeros((signal_size + 2*max_dist), dtype=int)
    for x in range(len(test_index)):
        histogram[test_index[x]+max_dist] = test_class[x]

    test_y = []
    for loc in locations:
        his_slice = histogram[loc:loc+max_dist+max_dist]
        test_y.append([i for i in his_slice if i > 0])

    return test_y

''' Loads training data and separates it into data_y and data_x variables '''
def loda_and_split_data(file_path = 'data/training.mat', wsize = 60, split = 0.9):
    # Load data and split into two components
    signal, indexes, classes = load_dataset(file_path)
    dtr, itr, ctr, dte, ite, cte = split_dataset_for_training_and_testing(signal, indexes, classes, split)

    # Find Classes in each window based on the Index function for training
    filtered = sp.filter_series(dtr)
    data_y, data_x, locations = generate_training_images(dtr, filtered, itr, ctr, wsize)

    # Find Classes in each predicted window
    filtered = sp.filter_series(dte)
    test_data_x, test_locations = generate_images(dte, filtered, wsize)
    test_data_y = generate_y_classes_from_proximity_to_window(test_locations, ite, cte, len(dte))

    return data_x, data_y, test_data_x, test_data_y