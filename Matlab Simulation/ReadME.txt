1. Run the sampling_debug.m file
Purpose: Take a demo sinusoidal signal. Resample to the ratio of 3/2 using both manual code and resample(x,3,2).
Compare the two results.

Notice that the last 2 plots in the first figure are similar.
The last plot is using resample(x,3,2) and the second last one is after resampling manually.

In the other figure, the error between the two resamplings is plotted. Notice the max error is very minimal compared to signal strength(40 times).


2. Download this .mat file from the following link.  https://drive.google.com/file/d/1aShftX6F_bBfsbXH9KTqvyle7zYE3Wpy/view?usp=sharing 

Run the following command. 'save A1_base_A2'

This will load the base audio, A2 and the sampled audio(using manual resampling) A1 into the workspace. 

Go to the end of the 'all_freq_raw.m' file. Run the last two sections. 
The second last section will first resample A2 using resample(x,2,1). 
Then it will play A1 twice. First the one found using resample(x,2,1) and second the manual one. 
Notice if the two sounds are the same.

The last section will plot the error between the two resampling methods. First one is for channel 1, second one is for channel 2.

Additional Information:

1. Base audio has been cut down. The first 100000 are kept and the rest are discarded. The main tone is in that part. You can plot and see for yourself.
2. The two channels are upsampled and downsampled independently. 
3. The upsampling operation takes a lot of time if the upsampling factor is kept large. 
For example, for generating B1 from A2, I was using an upsampling_factor = 25, downsampling_factor = 7. And, it took almost 1.5 hours to finish the upsampling.
It also takes up a lot of space since upsampled A2 is essentially 25 times larger than A2. 

So, we have to:
a) Keep the fractions as small as possible
b) Keep the results saved as text file/mat file 