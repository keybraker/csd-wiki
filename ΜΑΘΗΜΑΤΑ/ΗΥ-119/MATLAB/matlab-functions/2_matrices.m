clear all
clc

%%

A = [1 2 1; 3 5 1; 6 1 2];
B = [-1 2 0; 1 -4 -1; 0 9 2];

size(A)


%% ACCESSING THE CELLS OF A MATRIX
A(2,2) %select the value at position (2,2)

A(1,:) %select from the first row all the values of the row

A(1,end) %select from the 1 row the value in the last column

%% BASIC OPERATIONS

C = A * B; 
D = A + B; 


E = A .* B;

G = A ^ 2; % it is the same as A * A

H = A .^ 2; 


%%

A1 = [1 2 1  6;
      3 5 1 -2];
 
B1 = [-1  2  0;
       1 -4 -1;
       0  3  2;
       8  1 -1];

size(A1)
size(B1)

%try the length() function to a matrix. what happens? it gives you only the
%greater value returned by size()

%%   
   

C1 = A1 * B1; %you are able to do the multiplication because A1 = 2x4 and B1 = 4x3
D1 = A1 + B1; %in this example the two matrices must have the same dimensions, do they?


%% WE WANT TO DOUBLE THE FIRST LINE AND TRIPLE THE SECOND 
x = [2; 3];

y = repmat(x, 1, 4);
A2 = A1.*y;


%% OTHER WAYS TO ACHIEVE THIS
A3 = zeros(size(A1)); %creates a matrix with the same dimensions A1 has but that has only 0 as values

A3(1,:) = A1(1,:) * 2;
A3(2,:) = A1(2,:) * 3;


%%
Z = eye(2);
Z(1,1) = 2;
Z(2,2) = 3;

A4 = Z*A1;

%% USEFUL FUNCTIONS

inv(A) %inverse
transpose(A)
A'

%% LU
A = [1 1 1; 1 4 4; 1 4 8];

[L U] = lu(A);

