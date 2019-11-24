%% Random New Mins and Maxs

clear;
clc;

Tmin14 = readtable("min_random_14.txt");
Tmin13 = readtable("min_random_13.txt");

Tmax14 = readtable("max_random_14.txt");
Tmax13 = readtable("max_random_13.txt");

min14 = Tmin14.Var1;
iter14 = Tmin14.Var2;

min13 = Tmin13.Var1;
iter13 = Tmin13.Var2;

max13 = Tmax13.Var1;
iter13 = Tmax13.Var2;

max14 = Tmax14.Var1;
iter14 = Tmax14.Var2;

plot_1 = plot(iter13, min13, 'b', 'LineWidth', 1)
hold on
plot_2 = plot(iter14, min14, 'g', 'LineWidth', 1)
hold on
plot_3 = plot(iter13, max13, 'b', 'LineWidth', 1)
hold on
plot_4 = plot(iter14, max14, 'g', 'LineWidth', 1)

real_min13 = 213;
real_min14 = 251;

real_max13 = 631;
real_max14 = 694;

plot_5 = line([-50, 1000000],[real_min13, real_min13])
hold on
plot_6 = line([-50, 1000000],[real_min14, real_min14])
hold on
plot_7 = line([-50, 1000000],[real_max13, real_max13])
hold on
plot_8 = line([-50, 1000000],[real_max14, real_max14])

title('Iterations New Mins/Max')
xlabel('Iterations')
ylabel('Max/Min')
%set(gca, 'YScale', 'log')
xlim([-10 1000010])
ylim([-10 800])
grid on
legend([plot_1 plot_2 plot_3 plot_4 plot_5 plot_6 plot_7 plot_8], "MinN13", "MinN14", "MaxN13", "MaxN14", "RealMin13", "RealMin14", "RealMax13", "RealMax14")
