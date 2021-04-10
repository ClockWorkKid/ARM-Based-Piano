clear all, close all, clc

%% Load Audio
% http://theremin.music.uiowa.edu/MISpiano.html

[A2, Fs] = audioread("Piano.pp.A2.aiff");

%% Samping rate conversion, Fundamental Frequency is A2
%The nearest rational number is chosen to represent 2^(i/12)

%first octave
A0 = resample(A2,4,1);
A0_sharp = resample(A2,1250,331);
B1 = resample(A2, 25, 7);
C1 = resample(A2,1000,297);
C1_sharp = resample(A2,200,63);
D1 = resample(A2,1000,333);
D1_sharp = resample(A2,2000,707);
E1 = resample(A2,2000,749);
F1 = resample(A2,625,248);
F1_sharp = resample(A2,2500,1051);
G1 = resample(A2,200,89);
G1_sharp = resample(A2,59,125);
A1 = resample(A2,2,1);

%third octave
A2_sharp = resample(A2, 185, 196);
B2 = resample(A2, 1250, 1403);
C3 = resample(A2,2500,2973);
C3_sharp = resample(A2,50,63);
D3 = resample(A2,2500,3337);
D3_sharp = resample(A2,500,707);
E3 = resample(A2,500,749);
F3 = resample(A2,1000,1587);
F3_sharp = resample(A2,500,841);
G3 = resample(A2,500,891);
G3_sharp = resample(A2,125,236);
A3 = resample(A2,1,2);

%fourth octave

%% Playback Audio

for i=1:10
    
    sound(20*A0,Fs);
    pause(3);
    
    sound(20*A1,Fs);
    pause(3);
    
    sound(20*A2,Fs);
    pause(3);
    
    sound(20*A3,Fs);
    pause(3);
    
end






