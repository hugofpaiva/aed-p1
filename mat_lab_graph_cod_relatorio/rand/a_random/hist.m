%% Histogram For Random
clear;
clc;


T_13 = load("histo_cost_13.txt");
T_14 = load("histo_cost_14.txt");

n_costs = T_13;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];

first1 = find(n_costs, 1, "first");
last1 = find(n_costs, 1, 'last');

plot_1 = plot(costs, n_costs, "b", "LineWidth", 2)
hold on
plot_2 = plot([costs(first1) costs(last1)], [n_costs(first1) n_costs(last1)], "bo", "LineWidth", 2)
hold on

n_costs = T_14;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];

first2 = find(n_costs, 1, "first")
last2 = find(n_costs, 1, 'last')

if first2 < first1
    first = first2
else
    first = first1
end

if last2 > last1
    last = last2
else
    last = last1
end

plot_3 = plot(costs, n_costs, "g", "LineWidth", 2)
hold on
plot_4 = plot([costs(first2) costs(last2)], [n_costs(first2) n_costs(last2)], "go", "LineWidth", 2)
hold on

legend([plot_1 plot_2 plot_3, plot_4], "13", "Min/Max", "14", "Min/Max")


title('Permutations Histo')
xlabel('Costs')
ylabel('Uses nOccurrences')
xlim([100 800])
%set(gca, 'YScale', 'log')











