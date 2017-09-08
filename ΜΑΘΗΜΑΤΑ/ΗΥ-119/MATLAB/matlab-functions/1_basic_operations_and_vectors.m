%you don't have to preallocate a variable
a = 5;
b = 6;

c = a + b;

d = a ^ b;


%% VECTORS: special cases of matrices with one of their dimension equal to 1(1xN or Nx1)

a = [2 4 1];
b = [-1 2 3];


c = a + b; 

d = a * b'; %inner product
e = a' * b;


%%
d1 = a .* b; 

d2 = a * 2; %multiply the vector by 2

d3 = a .^ 2; %get a vector with its value of the 'a' squared


%%
a = [1:15]; %a vector that has all the numbers from 1 to 15 with step 1
b =  5:-0.5:-10;
c = 0:2:16;


%% USEFUL FUNCTIONS

a'

transpose(a)

length(a)

size(a)


%% INDEXING

a = [1 6 4 1 9 -1];

a(1)

ind1 = a > 2; %boolean vector of the same length as a with 1 on the values 
              %that are greater than 2 and zeros to all the other values 

a(ind1)    %get only the values that are greater than 2


ind2 = [5 2 1];

a(ind2) %take the values that are at the positions 5, 2 and 1(in this order)

%%

m = max(a);

