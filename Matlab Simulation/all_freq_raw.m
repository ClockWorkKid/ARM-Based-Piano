clear all, close all, clc

%% Load Audio
% http://theremin.music.uiowa.edu/MISpiano.html

[A2, Fs] = audioread("Piano.pp.A2.aiff");
t = 0:1/Fs:((length(A2)-1)/Fs);

%%
upsampling_factor = 25;
[upsampled_A2, upsampled_t] = upsample(A2,t,upsampling_factor);

%%
downsampling_factor = 7;
[B1, downsampled_t] = downsample(upsampled_A2, upsampled_t, downsampling_factor);






