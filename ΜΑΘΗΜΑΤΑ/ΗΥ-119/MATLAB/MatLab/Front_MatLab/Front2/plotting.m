x = 0:0.5:50;

y1 = 2 * x + 3;
y2 = 3 * x.^2 - 3;
y3 = y2 - y1;

figure,
hold on, 
plot(x,y1,'r');
plot(x,y2,'b');
plot(x,y3,'g');

%%

x = [0 10];
y = [5 5];
plot(x,y)