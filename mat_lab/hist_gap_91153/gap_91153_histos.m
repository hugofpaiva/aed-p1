%% Generate All Permutations 91153
clear;
clc;

T1 = readtable("histo_cost_1.txt");
T2 = readtable("histo_cost_2.txt");
T3 = readtable("histo_cost_3.txt");
T4 = readtable("histo_cost_4.txt");
T5 = readtable("histo_cost_5.txt");
T6 = readtable("histo_cost_6.txt");
T7 = readtable("histo_cost_7.txt");
T8 = readtable("histo_cost_8.txt");
T9 = readtable("histo_cost_9.txt");
T10 = readtable("histo_cost_10.txt");
T11 = readtable("histo_cost_11.txt");
T12 = readtable("histo_cost_12.txt");
T13 = readtable("histo_cost_13.txt");
T14 = readtable("histo_cost_14.txt");

n_costs = T1.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

n_costs = T2.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

n_costs = T3.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

n_costs = T4.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

n_costs = T5.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

n_costs = T6.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

n_costs = T7.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

n_costs = T8.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

n_costs = T9.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

n_costs = T10.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

n_costs = T11.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

n_costs = T12.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

n_costs = T13.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

n_costs = T14.x0;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];
plot(costs, n_costs)
hold on

title('GAP 91153')
xlabel('Costs')
ylabel('Uses nOccurrences')
set(gca, 'YScale', 'log')


