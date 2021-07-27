clear all, close all, clc
%%
name = "B5";
filename = "Piano.ff." + name + ".aiff";
[tone, Fs] = audioread(filename);

tone = tone(:, 1);
tone_power = tone(:, 1).^2; 

subplot(211)
plot(tone);
subplot(212)
plot(tone_power);

%%
tone = 2*tone(10000:45000, 1); %cutting the sound part
sound(tone, 44100)

%% generating tones at 44.1kHz


tone  = resample(tone, 8000, 44100);

tone  = uint8((tone  + 1)/2*255);

fileID = fopen(name + ".bin" ,'w'); fwrite(fileID, tone ); fclose(fileID);

disp("DONE");
