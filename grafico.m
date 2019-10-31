clear
clc
file = fopen('ocorrencias.txt');
x=[0:1:1919]';
y = fscanf(file,'%f');
fclose(file);


bar(x, y);
xlabel('Custos');
ylabel('Nº de Ocorrências');
title('Histograma');
