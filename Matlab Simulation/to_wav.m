clc
clear all
close all

%%
filename = 'Piano.pp.A2.aiff';
wavFileName = 'tone_A2.wav';
signal   = audioread(filename);
signal = signal(1:100000, :);
info = audioinfo(filename);
Fs = info.SampleRate;
sound(signal*20,Fs)
% audiowrite(wavFileName, signal*20, Fs);
% subplot(121), plot(signal(:,1))
% title('channel\_1');
% subplot(122), plot(signal(:,2))
% title('channel\_2');

%%
Fs = 8000; %sampling rate
t = 0:1/Fs:2;
x = sin(2*pi*100*t); %f=2
%plot(t,x)

wavFileName = 'sin.wav';
audiowrite(wavFileName, x*5, Fs);

signal   = audioread(wavFileName)';
info = audioinfo(wavFileName);
Fs_d = info.SampleRate;
sound(x*5, Fs_d);













