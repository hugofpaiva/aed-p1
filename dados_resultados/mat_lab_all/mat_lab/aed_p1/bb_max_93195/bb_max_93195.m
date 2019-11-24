%% Seed 93195 Branch and Bound

clear;
clc;

T = readtable("bb_max_result_93195.txt")

%teste = T.Var1(1)
n = T.Var3;
visited = T.Var5;
t = T.Var7;
logt = log10(t);


figure
plot(n, t, "-or", "LineWidth", 1)
title('BnB 93195')
xlabel('n')
ylabel('t(seg)')
xlim([-1 18])
ylim([-1 550])

figure
plot(n, t, "-or", "LineWidth", 1)
title('BnB 93195')
xlabel('n')
ylabel('t(seg)')
set(gca, 'YScale', 'log')
xlim([-1 18])
ylim([-1 500])

