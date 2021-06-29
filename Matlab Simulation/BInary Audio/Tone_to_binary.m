clear all, close all, clc

%%

filename = "Piano.pp.A2.aiff"
[A2, Fs] = audioread(filename);
Fs = 8000;

A2 = 20*A2(1:400000, 1); %cutting the sound part

%% generating tones at 44.1kHz

C3  = resample(A2, 11000, 13081);
C3s = resample(A2, 11000, 13859);
D3  = resample(A2, 11000, 14683);
D3s = resample(A2, 11000, 15556);
E3  = resample(A2, 11000, 16481);
F3  = resample(A2, 11000, 17461);
F3s = resample(A2, 11000, 18500);
G3  = resample(A2, 11000, 19600);
G3s = resample(A2, 11000, 20765);
A3  = resample(A2, 11000, 22000);
A3s = resample(A2, 11000, 23308);
B3  = resample(A2, 11000, 24694);

C4  = resample(C3,  1, 2);
C4s = resample(C3s, 1, 2);
D4  = resample(D3,  1, 2);
D4s = resample(D3s, 1, 2);
E4  = resample(E3,  1, 2);
F4  = resample(F3,  1, 2);
F4s = resample(F3s, 1, 2);
G4  = resample(G3,  1, 2);
G4s = resample(G3s, 1, 2);
A4  = resample(A3,  1, 2);
A4s = resample(A3s, 1, 2);
B4  = resample(B3,  1, 2);

C5  = resample(C3,  1, 4);
C5s = resample(C3s, 1, 4);
D5  = resample(D3,  1, 4);
D5s = resample(D3s, 1, 4);
E5  = resample(E3,  1, 4);
F5  = resample(F3,  1, 4);
F5s = resample(F3s, 1, 4);
G5  = resample(G3,  1, 4);
G5s = resample(G3s, 1, 4);
A5  = resample(A3,  1, 4);
A5s = resample(A3s, 1, 4);
B5  = resample(B3,  1, 4);

%% downsampling for Fs=8000

C3  = resample(C3,  8000, 44100);
C3s = resample(C3s, 8000, 44100);
D3  = resample(D3,  8000, 44100);
D3s = resample(D3s, 8000, 44100);
E3  = resample(E3,  8000, 44100);
F3  = resample(F3,  8000, 44100);
F3s = resample(F3s, 8000, 44100);
G3  = resample(G3,  8000, 44100);
G3s = resample(G3s, 8000, 44100);
A3  = resample(A3,  8000, 44100);
A3s = resample(A3s, 8000, 44100);
B3  = resample(B3,  8000, 44100);

C4  = resample(C4,  8000, 44100);
C4s = resample(C4s, 8000, 44100);
D4  = resample(D4,  8000, 44100);
D4s = resample(D4s, 8000, 44100);
E4  = resample(E4,  8000, 44100);
F4  = resample(F4,  8000, 44100);
F4s = resample(F4s, 8000, 44100);
G4  = resample(G4,  8000, 44100);
G4s = resample(G4s, 8000, 44100);
A4  = resample(A4,  8000, 44100);
A4s = resample(A4s, 8000, 44100);
B4  = resample(B4,  8000, 44100);

C5  = resample(C5,  8000, 44100);
C5s = resample(C5s, 8000, 44100);
D5  = resample(D5,  8000, 44100);
D5s = resample(D5s, 8000, 44100);
E5  = resample(E5,  8000, 44100);
F5  = resample(F5,  8000, 44100);
F5s = resample(F5s, 8000, 44100);
G5  = resample(G5,  8000, 44100);
G5s = resample(G5s, 8000, 44100);
A5  = resample(A5,  8000, 44100);
A5s = resample(A5s, 8000, 44100);
B5  = resample(B5,  8000, 44100);

%% quantize to 8 bits

C3  = uint8((C3  + 1)/2*255);
C3s = uint8((C3s + 1)/2*255);
D3  = uint8((D3  + 1)/2*255);
D3s = uint8((D3s + 1)/2*255);
E3  = uint8((E3  + 1)/2*255);
F3  = uint8((F3  + 1)/2*255);
F3s = uint8((F3s + 1)/2*255);
G3  = uint8((G3  + 1)/2*255);
G3s = uint8((G3s + 1)/2*255);
A3  = uint8((A3  + 1)/2*255);
A3s = uint8((A3s + 1)/2*255);
B3  = uint8((B3  + 1)/2*255);

C4  = uint8((C4  + 1)/2*255);
C4s = uint8((C4s + 1)/2*255);
D4  = uint8((D4  + 1)/2*255);
D4s = uint8((D4s + 1)/2*255);
E4  = uint8((E4  + 1)/2*255);
F4  = uint8((F4  + 1)/2*255);
F4s = uint8((F4s + 1)/2*255);
G4  = uint8((G4  + 1)/2*255);
G4s = uint8((G4s + 1)/2*255);
A4  = uint8((A4  + 1)/2*255);
A4s = uint8((A4s + 1)/2*255);
B4  = uint8((B4  + 1)/2*255);

C5  = uint8((C5  + 1)/2*255);
C5s = uint8((C5s + 1)/2*255);
D5  = uint8((D5  + 1)/2*255);
D5s = uint8((D5s + 1)/2*255);
E5  = uint8((E5  + 1)/2*255);
F5  = uint8((F5  + 1)/2*255);
F5s = uint8((F5s + 1)/2*255);
G5  = uint8((G5  + 1)/2*255);
G5s = uint8((G5s + 1)/2*255);
A5  = uint8((A5  + 1)/2*255);
A5s = uint8((A5s + 1)/2*255);
B5  = uint8((B5  + 1)/2*255);

%% write binary audio file

fileID = fopen('C3.bin' ,'w'); fwrite(fileID, C3 ); fclose(fileID);
fileID = fopen('C3s.bin','w'); fwrite(fileID, C3s); fclose(fileID);
fileID = fopen('D3.bin' ,'w'); fwrite(fileID, D3 ); fclose(fileID);
fileID = fopen('D3s.bin','w'); fwrite(fileID, D3s); fclose(fileID);
fileID = fopen('E3.bin' ,'w'); fwrite(fileID, E3 ); fclose(fileID);
fileID = fopen('F3.bin' ,'w'); fwrite(fileID, F3 ); fclose(fileID);
fileID = fopen('F3s.bin','w'); fwrite(fileID, F3s); fclose(fileID);
fileID = fopen('G3.bin' ,'w'); fwrite(fileID, G3 ); fclose(fileID);
fileID = fopen('G3s.bin','w'); fwrite(fileID, G3s); fclose(fileID);
fileID = fopen('A3.bin' ,'w'); fwrite(fileID, A3 ); fclose(fileID);
fileID = fopen('A3s.bin','w'); fwrite(fileID, A3s); fclose(fileID);
fileID = fopen('B3.bin' ,'w'); fwrite(fileID, B3 ); fclose(fileID);

fileID = fopen('C4.bin' ,'w'); fwrite(fileID, C4 ); fclose(fileID);
fileID = fopen('C4s.bin','w'); fwrite(fileID, C4s); fclose(fileID);
fileID = fopen('D4.bin' ,'w'); fwrite(fileID, D4 ); fclose(fileID);
fileID = fopen('D4s.bin','w'); fwrite(fileID, D4s); fclose(fileID);
fileID = fopen('E4.bin' ,'w'); fwrite(fileID, E4 ); fclose(fileID);
fileID = fopen('F4.bin' ,'w'); fwrite(fileID, F4 ); fclose(fileID);
fileID = fopen('F4s.bin','w'); fwrite(fileID, F4s); fclose(fileID);
fileID = fopen('G4.bin' ,'w'); fwrite(fileID, G4 ); fclose(fileID);
fileID = fopen('G4s.bin','w'); fwrite(fileID, G4s); fclose(fileID);
fileID = fopen('A4.bin' ,'w'); fwrite(fileID, A4 ); fclose(fileID);
fileID = fopen('A4s.bin','w'); fwrite(fileID, A4s); fclose(fileID);
fileID = fopen('B4.bin' ,'w'); fwrite(fileID, B4 ); fclose(fileID);

fileID = fopen('C5.bin' ,'w'); fwrite(fileID, C5 ); fclose(fileID);
fileID = fopen('C5s.bin','w'); fwrite(fileID, C5s); fclose(fileID);
fileID = fopen('D5.bin' ,'w'); fwrite(fileID, D5 ); fclose(fileID);
fileID = fopen('D5s.bin','w'); fwrite(fileID, D5s); fclose(fileID);
fileID = fopen('E5.bin' ,'w'); fwrite(fileID, E5 ); fclose(fileID);
fileID = fopen('F5.bin' ,'w'); fwrite(fileID, F5 ); fclose(fileID);
fileID = fopen('F5s.bin','w'); fwrite(fileID, F5s); fclose(fileID);
fileID = fopen('G5.bin' ,'w'); fwrite(fileID, G5 ); fclose(fileID);
fileID = fopen('G5s.bin','w'); fwrite(fileID, G5s); fclose(fileID);
fileID = fopen('A5.bin' ,'w'); fwrite(fileID, A5 ); fclose(fileID);
fileID = fopen('A5s.bin','w'); fwrite(fileID, A5s); fclose(fileID);
fileID = fopen('B5.bin' ,'w'); fwrite(fileID, B5 ); fclose(fileID);

