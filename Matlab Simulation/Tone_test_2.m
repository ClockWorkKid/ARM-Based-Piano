clear all, close all, clc

%% Load Audio
% http://theremin.music.uiowa.edu/MISpiano.html
filename = "Piano.pp.A2.aiff"
[A2, Fs] = audioread(filename);
A2 = A2(1:100000, :); %cutting the sound part

new_filename = '8_bit.wav';
audiowrite(new_filename, A2 ,Fs, 'BitsPerSample',8);

[A2_mod, Fs_mod] = audioread(new_filename);

sound(A2*20, Fs);
pause(5)
sound(A2_mod*20, Fs_mod);

%A2_mod = resample(A2, 44100, 16000);
% sound(A2*20, Fs)
% pause(5)
%sound(A2_mod*20, 16000)
%% Resample Audio

A3 = resample(A2,1,2); 
A4 = resample(A2,1,4);
A5 = resample(A2,1,8);
A6 = resample(A2,1,16);

E2 = resample(A2,4,3);
E3 = resample(A2,2,3);
E4 = resample(A2,1,3);
E5 = resample(A2,1,6);
E6 = resample(A2,1,12);

C2 = resample(E2,5,4);
C3 = resample(E3,5,4);
C4 = resample(E4,5,4);
C5 = resample(E5,5,4);
C6 = resample(E6,5,4);

Cs2= resample(A2,8,5);
Cs3= resample(A2,4,5);
Cs4= resample(A2,2,5);
Cs5= resample(A2,1,5);
Cs6= resample(A2,1,10);

G2 = resample(A2,8,7);
G3 = resample(A2,4,7);
G4 = resample(A2,2,7);
G5 = resample(A2,1,7);
G6 = resample(A2,1,14);


%% Playback Audio

sound(10*Cs2, Fs);




