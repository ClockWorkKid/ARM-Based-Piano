clc
close all
clear all

%% generating a sinusoidal signal
fs = 16; %inital sampling rate
t = 0:1/fs:1;
x = 2*sin(2*pi*2*t);
subplot(411), stem(t,x)
ylim([-4 4])
title('Original Signal');

%%Upsampling
upsampling_factor = 3;
[upsampled_x, upsampled_t] = upsample_mod(x, t, upsampling_factor);
subplot(412), stem(upsampled_t,upsampled_x)
ylim([-4 4])
title('Upsampled and filtered Signal');

%%Downsampling
downsampling_factor = 2;
[downsampled_x, downsampled_t] = downsample(upsampled_x, upsampled_t, downsampling_factor);
subplot(413), stem(downsampled_t, downsampled_x);
ylim([-4 4])
title('Downsampled signal');

%%Using Resample
resampled_x = resample(x,3,2);
resampled_x = resampled_x(1:end-1);
resampled_t = downsampled_t;
subplot(414), stem(resampled_t, resampled_x);
ylim([-4 4])
title('Resampled signal using resample(x,3,2)');

%%Error between resample and manual code
error = resampled_x' - downsampled_x;
figure, plot(error);




