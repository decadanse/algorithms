function lab2
clc; clear all;
A = [3 1 2 -1; 2 -1 2 2; 2 1 -1 -1; 1 1 -3 2]
b = 0.005;

fprintf('************* LU *************')%LU разложение без выбора  ведущего элемента (схема единственного деления);
LUfunc(A,b);
fprintf('************* QR *************')%.
qrgivens(A);
fprintf('************* функциями матлаба *************')
[L,U] = lu(A)
matlab_A_LU = L*U

[Q,R] = qr(A)
matlab_A_QR = Q*R
end

%LU разложение без выбора  ведущего элемента;
function [x,L,U] = LUfunc(A,b)
n = size(A);
A0 = A;
A1 = zeros(n);
A2 = zeros(n);
A3 = zeros(n);
A4 = zeros(n);
all_A = {A0;A1;A2;A3;A4};
L = eye(n);%единицы на главной диагонали
Lp = eye(n);
U = zeros(n);
if det(A) == 0
    fprintf('error')
    return
else
    a=A; %добавила   
    for i = 1:1:n-1
        i=i;
        Lp=eye(n);
        for j = (i+1):1:n
            l = a(j,i)/a(i,i);
            Lp(j,i) = -l;
            L(j,i) = l;
        end
        Lp= Lp;
        L= L;
        a= Lp*a;
    end
    U=a;
    U 
    L
    x=inv(U)*inv(L)*b';
    A_LU_my = L*U %  сходится. A = L*U
end 
end


%__________________________________________________________________________________________________________
%base from https://stackru.com/questions/17667359/algoritm-qr-razlozheniya-s-ispolzovaniem-vraschenij-givensa
%работает
%QR разложение с использованием метода вращения
function [Q,R] = qrgivens(A)
  [m,n] = size(A);
  Q = eye(m);
  R = A;

  for j = 1:n
    for i = m:-1:(j+1)
      T = eye(m);
      [c,s] = givensrotation(R(i-1,j),R(i,j)); %тут берутся элементы a11 и тд a 
                                               %T12A=(T12a1,T12a2,...T12ai,...,T12an)
%       T([i-1,i],[i-1,i]) = [c -s; s c] %если так, то все верно. но тут -s в другом месте
%fixed. изменения нужно было также внести в T часть
      T([i,i-1],[i,i-1]) = [c s; -s c] ;       %определяем матрицу вращения T1i, положив xk=a11, xl=ai1
      
      R = T'*R;     %Tn-1Tn-2...T1A=R %должна ыть верхнетреугольная
      % для (поиска проблемы) проверки стоит:
      % проверять обнуляет ли матрица вращения на каждом шаге элемент матрицы А или
      % нет (Т12 -> а21)
      Q = Q*T;      %Q= T1T  T2T...Tn-1T  %Q^-1 - Q' =0 должно быть тоже
    end
  end
  Q
  R
  A_QR_my = Q*R
end

function [c,s] = givensrotation(a,b)
  if b == 0 
      c = 1;
      s = 0;
  else
%     if abs(b) > abs(a) %r<1 тк это должен быть угол
%       r = a / b; 
%       s = 1 / sqrt(1 + r^2);
%       c = s*r;
%     else
%       r = b / a;
%       c = 1 / sqrt(1 + r^2);
%       s = c*r;
%     end

%можно и так и так - работает оба

    c = a/sqrt(a^2 + b^2);
    s = b/sqrt(a^2 + b^2);
  end

end