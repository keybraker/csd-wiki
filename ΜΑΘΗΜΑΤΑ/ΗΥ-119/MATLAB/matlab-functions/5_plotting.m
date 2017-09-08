clear all
clc

%% LET'S PLOT AN EQUATION 

x = -10:10;

y = 3*x-1;

plot(x,y);

%% ADD SOME INFORMATION TO THE PLOT

xlabel('x');
ylabel('y');
title('Plot of equation y=3x-1');

%shrink the axes
axis([-5 5 -20 20]);

%% LET'S ADD THE X AND Y AXES TWO 

%this command is needed in order to plot new things on the same figure
hold on
%plot x-axis
plot(zeros(1,length(y)), y, '--', 'Color', [.8 .8 .8]);
%plot y-axis, another way to plot a line
line([-5 5], [0 0], 'LineStyle', '--', 'LineWidth', 1, 'Color', [.8 .8 .8]);
