clc
clear all
close all

%% original signal

fs = 16;
T = 1/fs;
t = 0:1/fs:1; %nT
x = 2*sin(2*pi*2*t);
stem(t,x,'LineWidth',2);
xlabel('Time, t', 'fontweight', 'bold');
ylabel('Signal, x', 'fontweight', 'bold');
title('Pure Sinusoid Signal');

%% sinc interpretation
upsampling_factor = 3;
fs_u = fs*upsampling_factor;
t_u = 0:1/fs_u:((length(t)-1)/fs); %t
x_u = zeros(length(t_u),1);

i=1;
a = zeros(length(t), 1);
a(:,1) = t_u(i);
b = a-t'; %t-nT
d = sinc(b/T); %sinc((t-NT)/T)
x_u(i) = sum(x'.*d);

figure()
stem(t,x,'LineWidth',2);
hold on
stem(t,d,'LineWidth',2);
stem(t_u(1), x_u(1), 'LineWidth', 2);
legend('Original Signal', 'Sinc Interpolator', 'Upsampled Signal');
xlabel('Time, t', 'fontweight', 'bold');
ylabel('Signal Amplitude', 'fontweight', 'bold');


%%
i=2;
a = zeros(length(t), 1);
a(:,1) = t_u(i);
b = a-t'; %t-nT
d = sinc(b/T); %sinc((t-NT)/T)
x_u(i) = sum(x'.*d);

figure()
stem(t,x,'LineWidth',2);
hold on
stem(t,d,'LineWidth',2);
stem(t_u(1:2), x_u(1:2), 'LineWidth', 2);
legend('Original Signal', 'Sinc Interpolator', 'Upsampled Signal');
xlabel('Time, t', 'fontweight', 'bold');
ylabel('Signal Amplitude', 'fontweight', 'bold');

%%
for i=1:length(t_u)
    a = zeros(length(t), 1);
    a(:,1) = t_u(i);
    b = a-t'; %t-nT
    d = sinc(b/T); %sinc((t-NT)/T)
    x_u(i) = sum(x'.*d);
end

stem(t_u, x_u, 'LineWidth', 2);
xlabel('Time, t', 'fontweight', 'bold');
ylabel('Signal Amplitude', 'fontweight', 'bold');
title('Upsampled Signal');

%%

x_u = zeros(length(t_u),1);

for i=1:length(t_u)
a = zeros(length(t), 1);
a(:,1) = t_u(i);
b = a-t'; %t-nT
d = sinc(b/T); %sinc((t-NT)/T)
x_u(i) = sum(x'.*d);
end

fig = figure;
subplot(211), stem(t,x,'LineWidth',2);
title('Original Signal');
subplot(212), stem(t_u, x_u, 'LineWidth', 2);
title('Upsampled Signal');

han=axes(fig,'visible','off'); 
han.Title.Visible='on';
han.XLabel.Visible='on';
han.YLabel.Visible='on';
xlabel(han,'Time', 'fontweight', 'bold');
ylabel(han,'Signal', 'fontweight', 'bold');


%% downsampling

downsampling_factor = 2;
x_d = zeros(round((1/downsampling_factor)*length(x_u)),1);
fs_u = fs*(upsampling_factor);
fs_d = fs_u/downsampling_factor;
t_d = 0:1/fs_d:((length(t_u)-1)/fs_u);

for i=1:length(x_d)
    x_d(i) = x_u(i*downsampling_factor - downsampling_factor + 1);
end

fig = figure;
% subplot(311), stem(t,x,'LineWidth',2);
% title('Original Signal');
subplot(211), stem(t_u, x_u, 'LineWidth', 2);
title('Upsampled Signal');
subplot(212), stem(t_d, x_d, 'LineWidth', 2);
title('Downsampled Signal');

han=axes(fig,'visible','off'); 
han.Title.Visible='on';
han.XLabel.Visible='on';
han.YLabel.Visible='on';
xlabel(han,'Time', 'fontweight', 'bold');
ylabel(han,'Signal', 'fontweight', 'bold');

%%
fig = figure;
subplot(311), stem(t,x,'LineWidth',2);
title('Original Signal');
subplot(312), stem(t_u, x_u, 'LineWidth', 2);
title('Upsampled Signal');
subplot(313), stem(t_d, x_d, 'LineWidth', 2);
title('Downsampled Signal');

han=axes(fig,'visible','off'); 
han.Title.Visible='on';
han.XLabel.Visible='on';
han.YLabel.Visible='on';
xlabel(han,'Time', 'fontweight', 'bold');
ylabel(han,'Signal', 'fontweight', 'bold');

%%

figure(), stem(t,x,'LineWidth',2);
xlabel('Time, t', 'fontweight', 'bold');
ylabel('Signal, x', 'fontweight', 'bold');

figure(), stem(t(length(t)/4 + 2: length(t)/2 + 1), ...
    x(length(t)/4 + 2: length(t)/2 + 1), 'LineWidth',2);

xlabel('Time, t', 'fontweight', 'bold');
ylabel('Signal, x', 'fontweight', 'bold');

figure(), stem(t_u(length(t_u)/4 + 2: length(t_u)/2 + 1), ...
    x_u(length(t_u)/4 + 2: length(t_u)/2 + 1), 'LineWidth',2);
xlabel('Time, t', 'fontweight', 'bold');
ylabel('Signal, x', 'fontweight', 'bold');

figure(), stem(t_d(length(t_d)/4 + 2: length(t_d)/2 + 1), ...
    x_d(length(t_d)/4 + 2: length(t_d)/2 + 1), 'LineWidth',2);
xlabel('Time, t', 'fontweight', 'bold');
ylabel('Signal, x', 'fontweight', 'bold');

%%
stem(t_d,x_d,'LineWidth',2);
xlabel('Time, t', 'fontweight', 'bold');
ylabel('Signal, x', 'fontweight', 'bold');
title('Resampled Signal');

%% video of upsampling

upsampling_factor = 3;
fs_u = fs*upsampling_factor;
t_u = 0:1/fs_u:((length(t)-1)/fs); %t
x_u = zeros(length(t_u),1);

figure()
for i=1:length(t_u)
    a = zeros(length(t), 1);
    a(:,1) = t_u(i);
    b = a-t'; %t-nT
    d = sinc(b/T); %sinc((t-NT)/T)
    x_u(i) = sum(x'.*d);
    
    stem(t,x,'LineWidth',2);
    hold on
    stem(t,d,'LineWidth',2);
    stem(t_u(1:i), x_u(1:i), 'LineWidth', 2);
    legend('Original Signal', 'Sinc Interpolator', 'Upsampled Signal');
    xlabel('Time, t', 'fontweight', 'bold');
    ylabel('Signal Amplitude', 'fontweight', 'bold');
    pause(3);
    saveas(gcf,strcat('Upsample',string(i),'.png'));
    hold off
end

%%

fs = 16;
T = 1/fs;
t = 0:1/fs:(1/4 - 1/fs); %nT
%t = 1/4:1/fs:(1/2-1/fs);
x = 2*sin(2*pi*2*t);

upsampling_factor = 3;
fs_u = fs*upsampling_factor;
t_u = 0:1/fs_u:((length(t)-1)/fs); %t
%t_u = 1/4:1/fs_u:(1/2-1/fs);
x_u = zeros(length(t_u),1);

for i=1:length(t_u)
    a = zeros(length(t), 1);
    a(:,1) = t_u(i);
    b = a-t'; %t-nT
    d = sinc(b/T); %sinc((t-NT)/T)
    x_u(i) = sum(x'.*d);
end

% downsampling_factor = 2;
% x_d = zeros(round((1/downsampling_factor)*length(x_u)),1);
% fs_u = fs*(upsampling_factor);
% fs_d = fs_u/downsampling_factor;
% t_d = 0:1/fs_d:((length(t_u)-1)/fs_u);
% %t_d = 1/4:1/fs_d:(1/2 - 1/fs);
% 
% for i=1:length(x_d)
%     x_d(i) = x_u(i*downsampling_factor - downsampling_factor + 1);
% end

%saveas(gca, 'Downslice_2.png');

%%
stem(t_d,x_d,'LineWidth',2);
xlabel('Time, t', 'fontweight', 'bold');
ylabel('Signal, x', 'fontweight', 'bold');


%% 

fs = 16;
T = 1/fs;
t = 0:1/fs:1; %nT
x = 2*sin(2*pi*2*t);

upsampling_factor = 3;
fs_u = fs*upsampling_factor;
t_u = 0:1/fs_u:((length(t)-1)/fs); %t
x_u = zeros(length(t_u),1);

for i=1:length(t_u)
    a = zeros(length(t), 1);
    a(:,1) = t_u(i);
    b = a-t'; %t-nT
    d = sinc(b/T); %sinc((t-NT)/T)
    x_u(i) = sum(x'.*d);
end

stem(t_u, x_u, 'LineWidth', 2);
saveas(gca, strcat('Downsample0.png'));
pause(1)

for i=2:length(x_u)
    x_u(i) = [];
    t_u(i) = [];
    stem(t_u, x_u, 'LineWidth', 2);
    saveas(gca, strcat('Downsample', string(i), '.png'));
    pause(1)
end
















