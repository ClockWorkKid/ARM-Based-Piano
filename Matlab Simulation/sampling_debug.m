clc
close all
clear all

%% generating a sinusoidal signal
fs = 16; %inital sampling rate
t = 0:1/fs:1;
x = 2*sin(2*pi*2*t);
subplot(211), stem(t,x)
ylim([-4 4])

%upsampling by L
upsampling_factor = 3;
fs_upsample = upsampling_factor*fs;
upsampled_t = 0:1/fs_upsample:1;

%Low pass filtering
T = t(2)-t(1);
sincM = repmat( upsampled_t, length(t), 1 ) - repmat( t', 1, length(upsampled_t) );
upsampled_x = x*sinc( sincM/T );
subplot(212), stem(upsampled_t,upsampled_x);
ylim([-4 4]);

%% Downsampling
downsampling_factor = 2;
downsampled_x = zeros(round((1/downsampling_factor)*length(x)),1);
fs_downsample = fs/downsampling_factor;
downsampled_t = 0:1/fs_downsample:1;

for i=1:length(downsampled_x)
    downsampled_x(i) = x(i*downsampling_factor - downsampling_factor + 1);
end
stem(downsampled_t, downsampled_x);
ylim([-4 4])

%% Resampling in 3/2 ratio

fs = 16; %inital sampling rate
t = 0:1/fs:1;
x = 2*sin(2*pi*2*t);
subplot(311), stem(t,x)
ylim([-4 4])
title('Original signal');

upsampling_factor = 3;
[upsampled_x, upsampled_t] = upsample(x,t,upsampling_factor);
subplot(312), stem(upsampled_t,upsampled_x);
ylim([-4 4])
title('Upsampled Filtered signal');

downsampling_factor = 2;
[downsampled_x, downsampled_t] = downsample(upsampled_x,upsampled_t,downsampling_factor);
subplot(313), stem(downsampled_t,downsampled_x);
ylim([-4 4])
title('Final signal after downsampling');










