function [ a ] = fitPolynomial( x, y )
% x: n+1 x 1
% y: n+1 x 1
% a: n+1 x 1
% poluonimo bathmou n

% solve Ax = b
% x = A^-1*b, x = inv(A)*b, x = A\b

a = A\y;

end

