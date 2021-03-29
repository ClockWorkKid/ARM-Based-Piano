clear all
close all
clc

[C5, Fs] = audioread("C5.m4a");

%%

C7 = resample(C5,1,4);
C6 = resample(C5,1,2);

C4 = resample(C5,2,1);
C3 = resample(C5,4,1);
C2 = resample(C5,8,1);

%%

sound(C7, Fs);
pause(1);
sound(C6, Fs);
pause(1);
sound(C5, Fs);
pause(1);
sound(C4, Fs);
pause(1);
sound(C3, Fs);
pause(1);


