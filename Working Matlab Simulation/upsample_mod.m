function [upsampled_x_raw, upsampled_t] = upsample_mod(x,t,upsampling_factor)

T = t(2)-t(1);
fs = 1/T;

fs_upsample = upsampling_factor*fs;
upsampled_t = 0:1/fs_upsample:((length(x)-1)/fs);
upsampled_x_raw = zeros(length(upsampled_t), 1);

%Low pass filtering
%sincM = repmat( upsampled_t, length(t), 1 ) - repmat( t', 1, length(upsampled_t) );
%upsampled_x = x*sinc( sincM/T );

%alternative to repmat
%first I need to copy the first element of upsampled_t by length(t) times
%then I need to subtract t' from this
%now I have the first column of sincM
%pass this to the sinc function
%now do matrix multiplication
%so we have the first element of upsampled_x
%do this for all elements of upsampled_t

a = zeros(length(t),1);

for i = 1:length(upsampled_t)
    a(:,1) = upsampled_t(i);
    b = a - t';
    d = sinc(b/T);
    upsampled_x_raw(i) = sum(x'.*d);
end

end

