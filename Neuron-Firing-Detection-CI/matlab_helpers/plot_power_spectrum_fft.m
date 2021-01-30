function plot_power_spectrum_fft(data, sampling_f)
    %PLOT_POWER_SPECTRUM_FFT Summary of this function goes here
    %   Detailed explanation goes here
    L = length(data);
    Y = fft(data);
    P2 = abs(Y/L);
    P1 = P2(1:L/2+1);
    P1(2:end-1) = 2*P1(2:end-1);
    f = sampling_f*(0:(L/2))/L;
    plot(f(1:end),P1) 
    title('Single-Sided Amplitude Spectrum of X(t)')
    xlabel('f (Hz)')
    ylabel('|P1(f)|')
end

