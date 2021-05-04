clc
clear all
close all
mp3filename = 'E:\song.mp3';
wavFileName = 'E:song_wav.wav';
signal   = audioread(mp3filename);
info = audioinfo(mp3filename);
Fs = info.SampleRate;
audiowrite(wavFileName, signal, Fs);