blah = 4;
A = uint32(100*rand([blah blah]));
B = uint32(100*rand([blah blah]));

[M,N] = size(A);
m = 1:M;
n = 1:N;

X = M;
Y = N;

%Xt = zeros([M+2*(P-1) N+2*(Q-1)]);
%Xt(m+P-1,n+Q-1) = X;
C = zeros([2*M-1 2*N-1]);

for i = 1:X+Y-1
    for j = 1:X+Y-1
        value = 0;
        for s = 1:X+X - 1
            for t = 1:Y+Y - 1
                idx_a_x = s - X + i;
                idx_a_y = t - Y + j;
                idx_b_x = s ;
                idx_b_y = t ;


                if idx_a_x >= 1 && idx_a_x <= X && idx_a_y >= 1
                    if idx_a_y <= Y && idx_b_x >= 1 && idx_b_x <= X
                        if idx_b_y >= 1 && idx_b_y <= Y
                            value = value + A(idx_a_x,idx_a_y)*B(idx_b_x,idx_b_y);
                            
                        end
                    end
                end
            end
        end
        C(i,j) = value;
    end
end
H = xcorr2(A,B);
all(all(C == H))