blah = [80 45];
A = uint32(100*rand(blah));
%B = uint32(100*rand(blah));
B = A;
[X,Y] = size(A);
%B = A(:,2:end);
%B = [B, A(:,1)];



x_start_value = floor((X * 7) / 8);
x_end_value = floor((X * 9) / 8);
y_start_value = floor((Y * 7) / 8);
y_end_value = floor((Y * 9) / 8);
a_start_value = (max(0,X-x_start_value));
b_start_value = (max(0,Y-y_start_value));

x = x_start_value;
y = y_start_value;
a = a_start_value;
b = b_start_value;
add=0;
value=0;
valuemax=0;
xmax=0;
ymax=0;
C = zeros(1,1);

for i=1:9999999
    ida_x = floor(a-X+x+1);
    ida_y = floor(b-Y+y+1);
    idb_x = floor(a);
    idb_y = floor(b);
    add = A(ida_x, ida_y)*B(idb_x, idb_y);
    
    if x<x_end_value
        if y<y_end_value
            if a<min(X-1, 2*X-x-1)
                if b<min(Y-1, 2*Y-y-1)
                    value=value+add;
                    b=b+1;  
                    continue
                end
                b=b_start_value;
                a=a+1;
                continue
            end
            a=a_start_value;
            if value > valuemax
                valuemax=value;
                xmax=x;
                ymax=y;
            end
            C(x,y) = value;
            value=0;
            y=y+1;
            continue
        end
        y=y_start_value;
        x=x+1;
        continue  
    end
end

disp('max val: ' + string(valuemax))
disp('x: ' + string(xmax))
disp('y: ' + string(ymax))
imagesc(C(70:end,39:end))
colorbar
