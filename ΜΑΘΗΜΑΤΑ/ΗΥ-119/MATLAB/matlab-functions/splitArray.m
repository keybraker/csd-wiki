function [y z] = splitArray( x )
%SPLITARRAY Summary of this function goes here
%   Detailed explanation goes here

i = floor(length(x)/2);

y = x(1:i);
z = x(i+1:end);

end

