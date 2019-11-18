%% hist 91153
clear;
clc;


min_17 = load("min_cost_17.txt");
min_14 = load("min_cost_14.txt");
bb14 = load("bb_cost_14.txt");
max_14 = load("max_cost_14.txt");
max_17 = load("max_cost_17.txt");

subplot(2, 1, 1)
n_costs = bb14;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];

first1 = find(n_costs, 1, "first");
last1 = find(n_costs, 1, 'last');



plot_1 = plot(costs, n_costs, "b", "LineWidth", 2)
hold on
plot_2 = plot([costs(first1) costs(last1)], [n_costs(first1) n_costs(last1)], "bo", "LineWidth", 2)

title('Generate All Perm 91153')
xlabel('Costs')
ylabel('Uses nOccurrences')
xlim([0 1000])
%set(gca, 'YScale', 'log')

subplot(2, 1, 2)
n_costs = min_14;
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

xlim([0 1000])



n_costs = max_14;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];

first3 = find(n_costs, 1, "first")
last3 = find(n_costs, 1, 'last')

if first3 < first
    first = first3
end

if last3 > last
    last = last3
end


plot_5 = plot(costs, n_costs, "black", "LineWidth", 2)
hold on
plot_6 = plot([costs(first3) costs(last3)], [n_costs(first3) n_costs(last3)], "blacko", "LineWidth", 2)
hold on

title('Branch&Bound min/max 91153')
xlabel('Costs')
ylabel('Uses nOccurrences')
xlim([0 1000])
%set(gca, 'YScale', 'log')











