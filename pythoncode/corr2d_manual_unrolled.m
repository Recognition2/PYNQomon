blah = [80 45];
A = uint32(100*rand(blah));
B = uint32(100*rand(blah));

[M,N] = size(A);
%m = 1:M;
%n = 1:N;

do_live_debug = 0;

X = M;
Y = N;
fprintf('Eens even beginnen\n\n\n\n');
%Xt = zeros([M+2*(P-1) N+2*(Q-1)]);
%Xt(m+P-1,n+Q-1) = X;
C = zeros([2*M-1 2*N-1]);
itcnt = 0;
usefulcnt = 0;
maxdlt = 0;
bounds = [7/8 9/8];
i = 1;
j = 1;
s = max(1,X-i+1);
t = max(1,Y-j+1);
value = 0;
%for i = round(X * bounds(1)) : round(X*bounds(2))
%    itcnt = itcnt + 1;
%    for j = round(Y*bounds(1)) : round(Y*bounds(2))
 %for i = 1:X+X-1
 for aardbei______a = 1:1000*1000*1000*1000*1000
     if i <= X+X-1
         %for j = 1:Y+Y-1
         if j <= Y+Y-1
            dlt = 0;
            %value = 0;
            itcnt = itcnt + 1;
            if s <= min(X,2*X-i)
            %for s = max(1,(X-i + 1)):min(X ,2*X-i)
                itcnt = itcnt + 1;
                if t <= min(Y,2*Y-j)
                %for t = max(1,(Y-j+1)):min(Y,2*Y-j)
                    dlt = dlt + 1;
                    idx_a_x = s - X + i;
                    idx_a_y = t - Y + j;
                    idx_b_x = s ;
                    idx_b_y = t ;
                    itcnt = itcnt  +1;

                    if idx_a_x >= 1 && idx_a_x <= X && idx_a_y >= 1 && idx_a_y <= Y && idx_b_x >= 1 && idx_b_x <= X && idx_b_y >= 1 && idx_b_y <= Y
                                value = value + A(idx_a_x,idx_a_y)*B(idx_b_x,idx_b_y);
                                usefulcnt = usefulcnt + 1;
                    else
                        disp('HIER KLOPT GEEN FUCK VAN')
                    end

                    t = t+1;
                    continue;
                end
                t = max(1,Y-j+1);
                s=s+1;
                continue;
            end
            if dlt > maxdlt
                maxdlt = dlt;
            end
            C(i,j) = value;
            value = 0;
            s = max(1,X-i+1);
            j = j+1;
            t = max(1,Y-j+1);
            continue;
         end
         j = 1;
         i=i+1;
         t = max(1,Y-j+1);
         s = max(1,X-i+1);
         continue;
     end
     break;
 end
H = xcorr2(A,B);
disp('Functioneel correct: ' + upper(string(all(all(C == H)))))
disp('Aantal verkrachtte iteraties: ' + string(itcnt - usefulcnt))
disp('Percentage nuttigheid: ' + string(100 * usefulcnt / itcnt) + '%')
disp('Hoeveelheid iteraties per invocation gegeven 1280x720: ' + string(itcnt / 1280 / 720));
%disp('C = ');
%disp(C)