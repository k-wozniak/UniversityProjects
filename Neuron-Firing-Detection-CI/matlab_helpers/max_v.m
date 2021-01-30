function arr_max = max_v(arr)
    arr_max = [];
    
    for x = 1:length(arr)
        arr_max = [arr_max; max(arr(x).d)];
    end
end

