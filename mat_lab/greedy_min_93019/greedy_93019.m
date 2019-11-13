%% Seed 93019 Greedy 

clear;
clc;

T = readtable("greedy_result_93019.txt")

%teste = T.Var1(1)
n = T.Var3;
visited = T.Var5;
t = T.Var7;
logt = log10(t);


figure
plot(n, t, "-or", "LineWidth", 1)
title('Greedy 93019')
xlabel('n')
ylabel('t(seg)')
xlim([-1 33])
ylim([-1 1])

figure
plot(n, t, "-or", "LineWidth", 1)
title('Greedy 93019')
xlabel('n')
ylabel('t(seg)')
set(gca, 'YScale', 'log')
xlim([-1 33])
ylim([-20 20])

