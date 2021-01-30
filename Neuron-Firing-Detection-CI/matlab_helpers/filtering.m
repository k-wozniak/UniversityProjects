<<<<<<< HEAD
function [difference, locs, data] = filtering(data, med, mean, aim)
    data = bandpass(data, [100 10000], 25000);

    data = medfilt1(data, med);
    data = movmean(data, mean);
    
    N = 2.55;
    MAD = median(abs(data - median(data)));
    SD = 1.4826 * MAD;
    THR = N * SD;
    data(data < THR) = 0;
=======
function [difference, locs] = filtering(data, med, mean, aim)
    md = medfilt1(data, med);
    md = movmean(md, mean);
    threshold = 5 * median( abs(md) / 0.6745 );
    
    data = md;
    data(data < threshold) = 0;
>>>>>>> b4c77f8e62981a9357e51d5c0219a69ae47e9504
    
    [pks, locs] = findpeaks(data);
    
    difference = length(locs) - aim;
<<<<<<< HEAD
end
=======
end

>>>>>>> b4c77f8e62981a9357e51d5c0219a69ae47e9504
