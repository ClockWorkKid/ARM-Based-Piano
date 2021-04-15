clear all, close all, clc

%% Load Audio
% http://theremin.music.uiowa.edu/MISpiano.html

[A2, fs] = audioread("Piano.pp.A2.aiff");
A2 = A2(1:100000, :);
t = 0:1/fs:((length(A2)-1)/fs);

%% Upsampling and filtering
upsampling_factor = 2;
[upsampled_A2, upsampled_t] = upsample_mod(A2(:,1)',t,upsampling_factor);

upsampled_A2_total = zeros(length(upsampled_t), 2);
upsampled_A2_total(:,1) = upsampled_A2;

[upsampled_A2, upsampled_t] = upsample_mod(A2(:,2)',t,upsampling_factor);
upsampled_A2_total(:,2) = upsampled_A2;

%% Downsampling
downsampling_factor = 1;
[A1, downsampled_t] = downsample(upsampled_A2_total(:,1), upsampled_t, downsampling_factor);

A1_total = zeros(length(downsampled_t), 2);
A1_total(:,1) = A1;

[A1, downsampled_t] = downsample(upsampled_A2_total(:,2), upsampled_t, downsampling_factor);
A1_total(:,2) = A1;

%% Playback
A1_real = resample(A2,2,1);
sound(20*A1_real, fs);
pause(3);
sound(20*A1_total, fs);

%% Error in manual resampling
A1_real = A1_real(1:length(A1_total), :);

error_C1 = A1_real(:,1) - A1_total(:,1);
subplot(211), plot(error_C1);
title('Error per sample in channel 1');

error_C2 = A1_real(:,2) - A1_total(:,2);
subplot(212), plot(error_C2);
title('Error per sample in channel 2');




