load('training.mat');
N = 5;

% Filtering
highfilt_d = highpass(d,120,25000);         % High-Pass Filter
medfilt_d = medfilt1(highfilt_d,6);         % Median Filter
filt_d = movmean(medfilt_d,4);              % Moving Mean Filter

% Thresholding
MAD = median(abs(filt_d - median(filt_d))); % Find the Median Absolute Deviation
std_dev = MAD/0.67449;                      % Use the MAD to find an approximation of the Standard Deviation of the noise
thrshld = N*std_dev;                        % Sets a threshold depending

filt_d(filt_d<(thrshld)) = 0;               % Any data outside this threshold is set to 0

% Plotting Graphs of raw and filtered data
subplot(2,1,1); plot(d);                    % Plots the raw data
subplot(2,1,2); plot(filt_d);               % Plots the filtered data

% Finding the spikes within the filtered dataset
[pks,loc,w,p] = findpeaks(filt_d);             % Finds the amplitude and location of the peaks in the filtered data

% Can be used to compare raw spike data with detected spike data
%[rawData, foundData] = Comparison(Index, loc);