%% Speed BBMinMax Permutations 

clear;
clc;

T91153 = readtable("bb_minmax_result_91153.txt");
T93019 = readtable("bb_minmax_result_93019.txt");
T93195 = readtable("bb_minmax_result_93195.txt");

n91153 = T91153.Var3;
time91153 = T91153.Var7;

n93019 = T93019.Var3;
time93019 = T93019.Var7;

n93195 = T93195.Var3;
time93195 = T93195.Var7;

plot_1 = plot(n91153, time91153, 'b', 'LineWidth', 2)
hold on
plot_2 = plot(n93019, time93019, 'g', 'LineWidth', 2)
hold on
plot_3 = plot(n93195, time93195, 'r', 'LineWidth', 2)

title('Branch and Bound Min Max')
xlabel('n')
ylabel('Time(s)')
%xlim([first1 last1])
set(gca, 'YScale', 'log')

legend([plot_1 plot_2, plot_3], "91153", "93019", "93195")
