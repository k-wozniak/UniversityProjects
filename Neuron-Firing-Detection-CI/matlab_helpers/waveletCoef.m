function [cd1,cd2,cd3] = waveletCoef(d)

n = fix(log2(length(d)));

[c,l] = wavedec(d,n,'db1');
[cd1,cd2,cd3] = detcoef(c,l,[1 2 3]);

subplot(4,1,1);
plot(d);
title('Original Signal');
subplot(4,1,2);
plot(cd3);
title('Level 3 Detail Coefficients');
subplot(4,1,3);
plot(cd2);
title('Level 2 Detail Coefficients');
subplot(4,1,4);
plot(cd1);
title('Level 1 Detail Coefficients');

end