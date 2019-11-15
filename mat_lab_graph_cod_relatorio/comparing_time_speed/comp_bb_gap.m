%% Speed Comparsion

clear;
clc;

TGAP91153 = readtable("gap_result_91153.txt");
TBB91153 = readtable("bb_minmax_result_91153.txt");

ngap91153 = TGAP91153.Var3;
timegap91153 = TGAP91153.Var7;

nbb91153 = TBB91153.Var3;
timebb91153 = TBB91153.Var7;

plot_1 = plot(ngap91153, timegap91153, 'b', 'LineWidth', 2)
hold on
plot_2 = plot(nbb91153, timebb91153, 'g', 'LineWidth', 2)

title('Compare Branch&Bound vs GenAllPerm')
xlabel('n')
ylabel('Time(s)')
%xlim([first1 last1])
set(gca, 'YScale', 'log')
grid on
legend([plot_1 plot_2], "GAP", "B&B")
