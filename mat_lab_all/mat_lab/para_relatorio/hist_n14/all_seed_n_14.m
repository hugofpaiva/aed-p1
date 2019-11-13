%% Generate All Permutations 
% Seeds = 93195 93019 91153
clear;
clc;

%T14 = readtable("histo_cost_14_91153.txt");

T14_91153 = load("histo_cost_14_91153.txt");
T14_93195 = load("histo_cost_14_93195.txt");
T14_93019 = load("histo_cost_14_93019.txt");

%subplot(3, 1, 1)
n_costs = T14_91153;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];

c = costs';
h = n_costs;
m = sum(c.*h)/sum(h);
v = sum((c-m).^2.*h)/sum(h);
p = 1/sum(h);
d = sqrt(2)*erfinv(2*p);

first1 = find(h, 1, "first");
last1 = find(h, 1, 'last');

plot_1 = plot(c, h, "b", "LineWidth", 2)
hold on
plot_2 = plot(c, exp(-(c-m).^2/(2*v))./sqrt(2*pi*v).*sum(h), "r", "LineWidth", 1)
hold on
plot_3 = plot([c(first1) c(last1)], [h(first1) h(last1)], "bo", "LineWidth", 2)
hold on

title('GAP Group Seeds')
xlabel('Costs')
ylabel('Uses nOccurrences')
xlim([first1 last1])
%set(gca, 'YScale', 'log')

%subplot(3, 1, 2)
n_costs = T14_93195;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];

c = costs';
h = n_costs;
m = sum(c.*h)/sum(h);
v = sum((c-m).^2.*h)/sum(h);
p = 1/sum(h);
d = sqrt(2)*erfinv(2*p);

first2 = find(h, 1, "first")
last2 = find(h, 1, 'last')

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


plot_4 = plot(c, h, "g", "LineWidth", 2)
hold on
plot_5 = plot(c, exp(-(c-m).^2/(2*v))./sqrt(2*pi*v).*sum(h), "r", "LineWidth", 1)
hold on
plot_6 = plot([c(first2) c(last2)], [h(first2) h(last2)], "go", "LineWidth", 2)
hold on

title('GAP Group Seeds')
xlabel('Costs')
ylabel('Uses nOccurrences')
xlim([first last])
%set(gca, 'YScale', 'log')





n_costs = T14_93019;
[lin, col] = size(n_costs);
costs = [1 : 1 : lin];

c = costs';
h = n_costs;
m = sum(c.*h)/sum(h);
v = sum((c-m).^2.*h)/sum(h);
p = 1/sum(h);
d = sqrt(2)*erfinv(2*p);

first3 = find(h, 1, "first")
last3 = find(h, 1, 'last')

if first3 < first
    first = first3
end

if last3 > last
    last = last3
end


plot_7 = plot(c, h, "black", "LineWidth", 2)
hold on
plot_8 = plot(c, exp(-(c-m).^2/(2*v))./sqrt(2*pi*v).*sum(h), "r", "LineWidth", 1)
hold on
plot_9 = plot([c(first3) c(last3)], [h(first3) h(last3)], "blacko", "LineWidth", 2)
hold on

legend([plot_1 plot_2, plot_3, plot_4 plot_5, plot_6, plot_7, plot_8, plot_9], "91153", "Gauss", "Min/Max", "93195", "Gauss", "Min/Max", "93019", "Gauss", "Min/Max")


title('GAP Group Seeds')
xlabel('Costs')
ylabel('Uses nOccurrences')
xlim([first last])
%set(gca, 'YScale', 'log')











