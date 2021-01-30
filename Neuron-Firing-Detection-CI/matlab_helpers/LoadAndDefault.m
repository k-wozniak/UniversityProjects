<<<<<<< HEAD
t = load('C:\Users\admin\Documents\Projects\UniversityProjects\Neuron-Firing-Detection-CI\data\training.mat');
s = load('C:\Users\admin\Documents\Projects\UniversityProjects\Neuron-Firing-Detection-CI\data\submission.mat');

[f, locs, newd] = filtering(t.d, 6, 4, 3704);


% 59 was the maximum length
% 90 for the longest?
=======
t = load('C:\Users\Kamil\Documents\Projects\UniversityProjects\Neuron-Firing-Detection-CI\data\training.mat');
s = load('C:\Users\Kamil\Documents\Projects\UniversityProjects\Neuron-Firing-Detection-CI\data\submission.mat');

[f, locs] = filtering(d, 6, 4, 3704);
>>>>>>> b4c77f8e62981a9357e51d5c0219a69ae47e9504

% = movmean(d, 5);
% = medfilt1(d, 5);
% 
% q = median(abs(d)/0.6745);
% threshold = 5 * q;
% 
% data = d;
% data(data < threshold) = 0;
% 
% [pks, locs] = findpeaks(data);