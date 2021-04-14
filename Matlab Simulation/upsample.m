function [upsampled_x, upsampled_t] = upsample(x,t,upsampling_factor)

T = t(2)-t(1);
fs = 1/T;

fs_upsample = upsampling_factor*fs;
upsampled_t = 0:1/fs_upsample:1;

%Low pass filtering
sincM = repmat( upsampled_t, length(t), 1 ) - repmat( t', 1, length(upsampled_t) );
upsampled_x = x*sinc( sincM/T );
%stem(upsampled_t,upsampled_x);
%ylim([-4 4]);

end