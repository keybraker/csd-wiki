clear all
clc

a = [1 6 4 1 9 -1];

len = length(a);


%% FOR  
for i = 1:len
    a(i) = a(i) * a(i);
end


%% WHILE
i = 1;
while i<=len
    a(i) = a(i) * a(i);
    i = i + 1;
end

%%

a = a .* a;

