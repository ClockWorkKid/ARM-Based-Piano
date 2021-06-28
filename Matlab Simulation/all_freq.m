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

%second octave
A1 = resample(A2,2,1);
A1_sharp = resample(A2,53,100);
B2 = resample(A2, 14, 25);
C2 = resample(A2, 297,500);
C2_sharp = resample(A2,63,100);
D2 = resample(A2,667,1000);
D2_sharp = resample(A2,707,1000);
E2 = resample(A2,749,1000);
F2 = resample(A2,793,1000);
F2_sharp = resample(A2,21,25);
G2 = resample(A2,89,100);
G2_sharp = resample(A2,943,1000);

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

%fourth octave
A3 = resample(A2,1,2);
A3_sharp = resample(A3, 185, 196);
B3 = resample(A3, 1250, 1403);
C4 = resample(A3,2500,2973);
C4_sharp = resample(A3,50,63);
D4 = resample(A3,2500,3337);
D4_sharp = resample(A3,500,707);
E4 = resample(A3,500,749);
F4 = resample(A3,1000,1587);
F4_sharp = resample(A3,500,841);
G4 = resample(A3,500,891);
G4_sharp = resample(A3,125,236);

%fifth octave
A4 = resample(A3,1,2);
A4_sharp = resample(A4, 185, 196);
B4 = resample(A4, 1250, 1403);
C5 = resample(A4,2500,2973);
C5_sharp = resample(A4,50,63);
D5 = resample(A4,2500,3337);
D5_sharp = resample(A4,500,707);
E5 = resample(A4,500,749);
F5 = resample(A4,1000,1587);
F5_sharp = resample(A4,500,841);
G5 = resample(A4,500,891);
G5_sharp = resample(A4,125,236);

%sixth octave
A5 = resample(A4,1,2);
A5_sharp = resample(A5, 185, 196);
B5 = resample(A5, 1250, 1403);
C6 = resample(A5,2500,2973);
C6_sharp = resample(A5,50,63);
D6 = resample(A5,2500,3337);
D6_sharp = resample(A5,500,707);
E6 = resample(A5,500,749);
F6 = resample(A5,1000,1587);
F6_sharp = resample(A5,500,841);
G6 = resample(A5,500,891);
G6_sharp = resample(A5,125,236);

%seventh octave
A6 = resample(A5,1,2);
A6_sharp = resample(A6, 185, 196);
B6 = resample(A6, 1250, 1403);
C7 = resample(A6,2500,2973);
C7_sharp = resample(A6,50,63);
D7 = resample(A6,2500,3337);
D7_sharp = resample(A6,500,707);
E7 = resample(A6,500,749);
F7 = resample(A6,1000,1587);
F7_sharp = resample(A6,500,841);
G7 = resample(A6,500,891);
G7_sharp = resample(A6,125,236);

%eighth octave
A7 = resample(A6,1,2);
A7_sharp = resample(A7, 185, 196);
B7 = resample(A7, 1250, 1403);
C8 = resample(A7,2500,2973);


%% Playback Audio

for i=1:10
    
    sound(20*C1,Fs);
    pause(3);
    
    sound(20*C2,Fs);
    pause(3);
    
    sound(20*C3,Fs);
    pause(3);
    
    sound(20*C4,Fs);
    pause(3);
    
    sound(20*C5,Fs);
    pause(3);
    
    sound(20*C6,Fs);
    pause(3);
    
    sound(20*C7,Fs);
    pause(3);
    
    sound(20*C8,Fs);
    pause(3);
    
end






