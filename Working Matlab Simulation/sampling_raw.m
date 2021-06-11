clc
close all
clear all

%% generating a sinusoidal signal
fs = 16; %inital sampling rate
t = 0:1/fs:1;
x = 2*sin(2*pi*2*t);
subplot(311), stem(t,x)
ylim([-4 4])

%upsampling by L
upsampling_factor = 3;
upsampled_x = zeros(upsampling_factor*length(x) - upsampling_factor + 1, 1);
fs_upsample = upsampling_factor*fs;
upsampled_t = 0:1/fs_upsample:1;

for i=3:length(upsampled_x)
    if(mod(i,upsampling_factor)) == 0
        upsampled_x(i- upsampling_factor + 1) = x(i/upsampling_factor);
    else
        upsampled_x(i) = 0;
    end
end
subplot(312), stem(upsampled_t, upsampled_x);
ylim([-4 4])

%Low pass filtering
T = t(2)-t(1);
sincM = repmat( upsampled_t, length(t), 1 ) - repmat( t', 1, length(upsampled_t) );
y = x*sinc( sincM/T );
subplot(313), stem(upsampled_t,y);
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

%% 

function y = sinc_interp(x,s,u)
    T = s(2)-s(1);
    sincM = repmat( u, length(s), 1 ) - repmat( s', 1, length(u) );
    y = x*sinc( sincM/T );
end








