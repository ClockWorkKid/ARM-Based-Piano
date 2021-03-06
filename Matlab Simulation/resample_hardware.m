clear all, close all, clc

%% Load Audio
% http://theremin.music.uiowa.edu/MISpiano.html
[A2, fs] = audioread("Piano.pp.A2.aiff");
A2 = A2(1:100000, :)*10;
t = 0:1/fs:((length(A2)-1)/fs);

%% Upsampling and filtering
upsampling_factor = 2;
[upsampled_A2, upsampled_t] = upsample_mod(A2(:,1)',t,upsampling_factor);

%% Downsampling
downsampling_factor = 1;
[A1_M, downsampled_t] = downsample(upsampled_A2, upsampled_t, downsampling_factor);

save 'Matlab Tones/A1_m.mat' A1_M
%% Playback

tone_C = readtable('C Tones/A1_sharp_C.txt');
tone_C = table2array(tone_C);
A1_sharp = resample(A2,53,100);
fs = 44100;
sound(tone_C, fs); %from C code
pause(5);
sound(A1_sharp, fs); %from using matlab's dedicated function

















