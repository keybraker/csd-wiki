% Orizoume mia timh gia to A
A=0;
% Diamerizoume ton a3ona tou xronou ana dt
dt = 0.01;
% Orizoume mia timh gia thn periodo T0
T0 = 1;
% Orizoume ton a3ona tou xronou (4 periodoi)
t = 0:dt:4*T0;
% Posa hmitona 8eloume? Estw 40...
N = 40;
% pollaplasia tou k me bhma 1
k = 1:1:N;
% H mesh timh
C0 = A/2;
% Oi syntelestes twn synhmitonwn
Ck = 4./((k*pi).^2);
% Pra3h! (prose3te pws apofeugoume th xrhsh for loop)
x = C0 + Ck*cos(2*pi*k'/T0*t );
% Apeikonish
plot(t, x); xlabel('Time (s)'); 


%b)
% Orizoume mia timh gia to A
A=2/5;
% Diamerizoume ton a3ona tou xronou ana dt
dt = 0.01;
% Orizoume mia timh gia thn periodo T0
T0 = 1;
% Orizoume ton a3ona tou xronou (4 periodoi)
t = 0:dt:4*T0;
% Posa hmitona 8eloume? Estw 40...
N = 40;
% pollaplasia tou k me bhma 1
k = 1:1:N;
% H mesh timh
C0 = A/2;
% Oi syntelestes twn synhmitonwn
Ck = 2./(k*pi);
% Pra3h! (prose3te pws apofeugoume th xrhsh for loop)
x = C0 + Ck*sin(pi*k'/5)*cos(2*pi*k'/T0*t );
% Apeikonish
plot(t, x); xlabel('Time (s)'); 

%to sxima miazei me sima radiofwnikwn stathmwn


%c
% Orizoume mia timh gia to A
A=0;
% Diamerizoume ton a3ona tou xronou ana dt
dt = 0.01;
% Orizoume mia timh gia thn periodo T0
T0 = 1;
% Orizoume ton a3ona tou xronou (4 periodoi)
t = 0:dt:4*T0;
% Posa hmitona 8eloume? Estw 40...
N = 40;
% pollaplasia tou k me bhma 1
k = 1:2:N;
% H mesh timh
C0 = A/2;
% Oi syntelestes twn synhmitonwn
Ck = 4./(k*pi);
% Pra3h! (prose3te pws apofeugoume th xrhsh for loop)
x = C0 + Ck*sin(2*pi*k'/T0*t );
% Apeikonish
plot(t, x); xlabel('Time (s)');

%d)

% Orizoume mia timh gia to A
A=6/4;
% Diamerizoume ton a3ona tou xronou ana dt
dt = 0.01;
% Orizoume mia timh gia thn periodo T0
T0 = 1;
% Orizoume ton a3ona tou xronou (4 periodoi)
t = 0:dt:4*T0;
% Posa hmitona 8eloume? Estw 40...
N = 40;
% pollaplasia tou k me bhma 1
k = 1:1:N;
% H mesh timh
C0 = A/2;
% Oi syntelestes twn synhmitonwn
Ck = 1./(k*pi);
Ck2 = 2./(((2*k-1).^2)*pi^2);

% Pra3h! (prose3te pws apofeugoume th xrhsh for loop)
x = C0 + Ck*sin(2*pi*k'/T0*t) ; %*cos(2*pi*(2*k -1)./T0 .* t);
x2 = Ck2 *cos(2*pi*(2*k' -1)./T0 * t);
x3=x-x2;
plot(t,x3); xlabel('Time (s)');

