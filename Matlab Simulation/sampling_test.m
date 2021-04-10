clc
close all
clear all

%% generating a sinusoidal signal
fs = 16; %inital sampling rate
t = 0:1/fs:1;
x = 2*sin(2*pi*2*t);
%stem(t,x)
%ylim([-4 4])

%% upsampling and downsampling
upsampled_x = upsample(x,2);
upsampled_t = 0:1/fs:(2+1/fs);
downsampled_x = downsample(x,2);
downsampled_t = 0:2/fs:1;

figure
subplot(311), stem(t,x)
xlim([0 1])
ylim([-3 3])
title('Original signal')
subplot(312), stem(upsampled_t,upsampled_x)
xlim([0 1])
ylim([-3 3])
title('Upsampled by 2')
subplot(313), stem(downsampled_t,downsampled_x)
xlim([0 1])
ylim([-3 3])
title('Downsampled by 2')


%% resampling (this is basically upsampling/downsampling + filtering)
resampled_up_x = resample(x,2,1);
resampled_up_t = 0:1/fs:(2+1/fs);
figure
subplot(221), stem(upsampled_t,upsampled_x)
xlim([0 1])
ylim([-3 3])
title('Upsampled by 2 using upsample(x,2)')
subplot(222), stem(resampled_up_t,resampled_up_x)
xlim([0 1])
ylim([-3 3])
title('Upsampled by 2 using resample(x,2,1)')


resampled_down_x = resample(x,1,2);
resampled_down_t = 0:2/fs:1;
subplot(223), stem(downsampled_t,downsampled_x)
xlim([0 1])
ylim([-3 3])
title('Downsampled by 2 using downsample(x,2)')
subplot(224), stem(resampled_down_t,resampled_down_x)
xlim([0 1])
ylim([-3 3])
title('Downsampled by 2 using resample(x,1,2)')




