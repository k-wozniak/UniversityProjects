load('training.mat');

type1Window = spectraWindow(1,d,Index,Class);
type2Window = spectraWindow(2,d,Index,Class);
type3Window = spectraWindow(3,d,Index,Class);
type4Window = spectraWindow(4,d,Index,Class);

w = [type1Window ; type2Window ; type3Window ; type4Window];
%save('training_data.mat', 'w');

