function points = slope_to_line(d)
    p = false;
    points = zeros(1, length(d));
    
    max_slope = 0;
    c_slope = 0;
    
    for x = 1:length(d)
        if d(x) > 0
            if p == false
                p = true;
                points(x) = 20;
            end
        else
            p = false;
        end
    end
end