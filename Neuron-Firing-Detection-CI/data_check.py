import scipy.io as spio, signal
import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

mat = spio.loadmat('data/training.mat', squeeze_me=True)

d = mat['d']
Index = mat['Index']
Class = mat['Class']

x = np.linspace(0,5,100)
#d = np.sin(2*np.pi*x)
freqs, psd = signal.welch(d)
#Y = np.fft.fft(d)
#F = np.fft.fftfreq(len(d), 1)
plt.semilogx(freqs, psd)
plt.xlabel('Frequency')
plt.ylabel('Power')
plt.tight_layout()
#plt.plot(F, abs(Y)**2)
plt.show()