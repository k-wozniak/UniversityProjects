function longest = longest_sequence(x)
    zpos = find(~[0 x 0]);
    [~, grpidx] = max(diff(zpos));
    longest = x(zpos(grpidx):zpos(grpidx+1)-2);
end

