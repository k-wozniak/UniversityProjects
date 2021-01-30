function [rawData,foundData] = Comparison(Index,loc)

rawData = zeros(1,1440000);
foundData = zeros(1,1440000);
rawData(Index) = 10;
foundData(loc) = 20;

plot(rawData);
hold on;
plot(foundData);
hold off;

end

