function Minimum(a,b,eps)
%Minimum(a,b,eps) функция нахождения минимума функции f(x)
% методом "Дихотомии" на отрезке [a, b] с точностью eps.
% Функция f(x) задаётся в M-файле, находящимся в той же дирекктории.
% (!) Для правильной работы функции необходимо, чтоб a<b и
% искомое значение было б единствено на [a, b].
fx=@(x)-x^4+3*x^3-3*x-1;
a=-0.4; 
b=2;
eps=0.00001;

fx=inline('-x.^4+3*x.^3-3*x-1');%2*x.^2-exp(x)');
x=-0.4:0.1:2;
y=fx(x);
figure(2);
plot(x,y), grid on;
% a = 0;
% b = 1;
% eps = 0.001
x1=(a+b)/2-eps; x2=(a+b)/2+eps;
% del0=(a+b)/2;
A=fx(x1); B=fx(x2);
while 1
    if A<=B
        a=a;
        b=x2;
        if b-a<eps break;
        else x2=x1; B=A; x1=(a+b)/2-eps; A=fx(x1); %?: долго считает при "x1=(a+b)/2-eps" формуле
  													%?: считает быстро но не корректно при "x1=(a+b-eps)/2"
        end;
    else
        a=x1;
        b=b;
        if b-a<eps break;
        else x1=x2; A=B; x2=(a+b)/2+eps; B=fx(x2);
        end;
    end;
end;
x=(a+b)/2;
disp(sprintf('%s %.15f','Минимум функции f(x) = ',x));