function array = only_close(array)
    range = 5;
    l = length(array);
    
    array = sort(array);
    
    % Check first
    if (array(1) + range) < array(2)
        array(1) = 0;
    end
    % check last
    if (array(l) - range) > array(l-1)
        array(l) = 0;
    end
    
    for x = 2:length(array) - 1
        if (array(x) - range) >  array(x-1) && (array(x) + range) <=  array(x+1)
            array(x) = 0;
        end
    end
    
    array = array(array > 0);
end


