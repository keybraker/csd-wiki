if(x == 1 && y == 2)
    
elseif(x ~= 1 && y == 2)
    
end

if(x == 1 && y == 2)
    
else
    if(x ~= 1 && y == 2)
        
    end
end

%%
% Athroisma apo 1 eos 10

s = 0;
for i = 1:10
    s = s + i;
end

a = [1,2,3,6,7];
s = 0;
% Athroisma olon ton stoixeion tou dianismatos a
for i = 1:length(a)
    s = s + a(i);
end
%%
% Pinakas me tixaious aritmous
A = rand(5,4,6);

s = 0;

% Athroisma olon ton stoixeion tou 3-d pinaka A
for i = size(A,1):-1:1
    for j = 1:size(A,2)
        for k = 1:size(A,3)
            s = s + A(i,j,k);
        end
    end
end

