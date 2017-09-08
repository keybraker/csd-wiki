%askisi 13
%a)
Dt=0.001;
t = 0:Dt:2*pi;
% Orizoume th synarthsh
f = (1./(5/4 -cos(t)));
 
apotelesma = Dt *sum(f);
%apotelesma =   8.3808

% Epibebaiwsh
ans = 8 * pi / 3;

%b)
%ksekinaw apo 0.001 giati ln(0) den orizetai 
%sto matlab to log einai to ln
Dt=0.001;
t = Dt:Dt:1;
% Orizoume th synarthsh
f= (log(t)./(1+t));
apotelesma = Dt *sum(f);
%apotelesma =   -0.8181

% Epibebaiwsh
ans = - pi*pi / 12;

%c)
Dt=0.001;
t = 1:Dt:2;
% Orizoume th synarthsh
f = ((t+2).*(t-2))./(t.^t);
 
apotelesma = Dt *sum(f);
%apotelesma =   -1.1428

% Epibebaiwsh
ans = -1;

%d)
%xrisimopoiw anw orio ena megalo arithmo (1000) kai ksekinaw apo
% mikro Dt alla oxi miden gia na orizetai o paronomastis
Dt=0.0001;
t = Dt:Dt:1000;
% Orizoume th synarthsh
f =   (t./(exp(t)-1));
 
apotelesma = Dt *sum(f);

%apotelesma =1.6449
 
 
ans=pi*pi /6;
%ans =  1.6449


