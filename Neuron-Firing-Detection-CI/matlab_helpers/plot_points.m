function plot_points(type, Index, Class)

indexes = zeros(1,1440000);
indexes(Index(Class == type)) = 10;

stem(indexes(172313-100:172313+100));

end

