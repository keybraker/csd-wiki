function [ a ] = fitPolynomial( x,y )
for i=1:size(x)
    for j=1:size(x)
        A(i,j)=x(i)
    end
end
a = A\y;
end

