%% Branch and Bound Max
% Seeds = 93195 93019 91153
clear;
clc;


T17_91153 = load("histo_cost_17_91153.txt");
T17_93195 = load("histo_cost_17_93195.txt");
T17_93019 = load("histo_cost_17_93019.txt");

%subplot(3, 1, 1)
n_costs = T17_91153;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];

first1 = find(n_costs, 1, "first");
last1 = find(n_costs, 1, 'last');

plot_1 = plot(costs, n_costs, "b", "LineWidth", 2)
hold on
plot_2 = plot([costs(first1) costs(last1)], [n_costs(first1) n_costs(last1)], "bo", "LineWidth", 2)
hold on

title('Branch&Bound Group Seeds')
xlabel('Costs')
ylabel('Uses nOccurrences')
xlim([first1 last1])
%set(gca, 'YScale', 'log')

%subplot(3, 1, 2)
n_costs = T17_93195;
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

title('Branch&Bound Group Seeds')
xlabel('Costs')
ylabel('Uses nOccurrences')
xlim([first last])
%set(gca, 'YScale', 'log')



n_costs = T17_93019;
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

legend([plot_1 plot_2, plot_3, plot_4 plot_5, plot_6], "91153", "Min/Max", "93195", "Min/Max", "93019", "Min/Max")


title('Branch&Bound Group Seeds')
xlabel('Costs')
ylabel('Uses nOccurrences')
xlim([first last])
%set(gca, 'YScale', 'log')











