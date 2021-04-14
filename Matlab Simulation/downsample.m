function [downsampled_x, downsampled_t] = downsample(x,t,downsampling_factor)

T = t(2)-t(1);
fs = 1/T;

downsampled_x = zeros(round((1/downsampling_factor)*length(x)),1);
fs_downsample = fs/downsampling_factor;
downsampled_t = 0:1/fs_downsample:1;

for i=1:length(downsampled_x)
    downsampled_x(i) = x(i*downsampling_factor - downsampling_factor + 1);
end

%stem(downsampled_t, downsampled_x);
%ylim([-4 4])

end