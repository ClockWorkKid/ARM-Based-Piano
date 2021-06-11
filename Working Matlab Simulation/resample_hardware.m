%The purpose of this code is to compare the resampling done in C code with
%MATLAB's dedicated function resample(x,u,d)

clear all, close all, clc

%% Load Audio
% http://theremin.music.uiowa.edu/MISpiano.html
[A2, fs] = audioread("Piano.pp.A2.aiff");
A2 = A2(1:100000, :)*10;
t = 0:1/fs:((length(A2)-1)/fs);

%% Playback A1
tone_C = readtable('C Tones/A1_C.txt');
tone_C = table2array(tone_C);
A1 = resample(A2,2,1);
fs = 44100;
sound(tone_C, fs);
pause(5);
sound(A1, fs);

%% Playback A1 sharp

tone_C = readtable('C Tones/A1_sharp_C.txt');
tone_C = table2array(tone_C);
A1_sharp = resample(A2,100,53);
fs = 44100;
sound(tone_C, fs);
pause(5);
sound(A1_sharp, fs);

%% Playback B2

tone_C = readtable('C Tones/B2_C.txt');
tone_C = table2array(tone_C);
B2 = resample(A2,25,28);
fs = 44100;
sound(tone_C, fs);
pause(5);
sound(B2, fs);














