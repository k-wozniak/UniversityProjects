function [typeWindow] = spectraWindow(type,d,Index,Class)

typeSpike = Index(Class == type);
typeWindow = [];
typeSpectra = zeros(1,1440000);

for w = 1:4   
   typeSpectra(Index(Class == w)) = w;
end

for x = typeSpike
    t = [];
    
    a = typeSpectra(x - 4:x + 45);
    
    for y = a(a > 0)
        t = [t, y]; 
    end
    
    obj.t = t;
    obj.d = d(x-4:x+45);
    typeWindow = [typeWindow; obj];
    
end

end

