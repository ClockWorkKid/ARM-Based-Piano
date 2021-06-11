function [C] = matrix_multiplication(x, sincM) 

A = x;
B = sincM;

C = zeros(size(A,1), size(B,2));

%go over all the rows of the first matrix
for i=1:size(A,1)
    sum = 0;
    %go over all the columns of the second matrix
    for j=1:size(B,2)
        %go over all the rows of the first matrix
        for k=1:size(A,2)
            sum = sum + A(i,k)*B(k,j);
        end 
        C(i,j) = sum;
        sum = 0;
    end
end
