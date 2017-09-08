len = 100;

% Initialize the vectors a and b.
a = rand(len, 1);
b = rand(len, 1);

% Vectorized
c1 = zeros(len, 1); % Preallocate c
tic; %tic-toc counts the time passed from the 'tic' untill the 'toc'  
c1 = a .* b; 
toc;

% FOR loop
c2 = zeros(len, 1); % Preallocate c

tic; 

for i = 1:len
    c2(i) = a(i) * b(i);
end;

toc;