function main
clc; clear all;
% https://www.mathworks.com/matlabcentral/fileexchange/72481-secant-method/
% Метод секущих
% –x^4+3x^3+x–1=0
% -x*x*x*x+3*x*x*x+x-1 = 0
%с погрешностью 10^-6

%Secant Method

f=@(x)-x*x*x*x+3*x*x*x+x-1; %Write your function f(x), where f(x)=0.
% Root lies between in the interval (x0, x1).
% ввод -3 и 1 тк см тетр: (-1-3-1-1)*(-12-18)>0  (f(x0)*f''(x0)>0)
x0=input('\n Enter left point of interval: '); %here x0=-3 
x1=input('\n Enter right point of interval: ');%here x1=1
max_error=input('\n Enter the error: '); %error of tolerance you want. for exmple 0.000001 = 10^-6

err=abs(x1-x0);
%Formula: x2=(x0*f(x1)-x1*f(x0))/(f(x1)-f(x0));
% if f(x0)*f(x1)> 0
%     disp('Enter valid interval !!!')
% else
    while err > max_error
        x2=(x0*f(x1)-x1*f(x0))/(f(x1)-f(x0));
        x0=x1;
        x1=x2;
        err=abs(x1-x0);
        root=x2;
    end
    fprintf('\n The root is %4.6f \n',root);
    f(root)
% end


% % from https://www.codewithc.com/secant-method-matlab-program/ but i dont
% % clearly understand abs((x(i)-x(i-1))/x(i))*100<n  so below
% % is also this method but v2
% % v"2"
% % a=input('Enter function:','s');
% % f=inline(a)
% f=@(x)-x*x*x*x+3*x*x*x+x-1; 
% x(1)= -3; %input('Enter first point of guess interval: ');
% x(2)= 1; %input('Enter second point of guess interval: ');
% n= 0.000001; %input('Enter allowed Error in calculation: ');
% iteration=0;
% itr=input('Enter number of iteration=');
% index=1;
% for i=3:itr
%     x(i) = x(i-1) - (f(x(i-1)))*((x(i-1) - x(i-2))/(f(x(i-1)) - f(x(i-2))));
%     iteration=iteration+1;
%     if abs((x(i)-x(i-1)))<n %/x(i))*100<n
%         root=x(i);
%         iteration=iteration;
%         fprintf('Solution is %f at iterations %i \n',root,iteration)
%         index=0;
%         break
%     end 
% end
% if index == 1
%     fprintf('No convergent solution exist in the given number iteration \n')
% end
end