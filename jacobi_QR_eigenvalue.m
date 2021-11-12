function lab4
clc; clear all;
A = [-1,3,4; 3,-6,3; 4,3,5];
[m,~] = size(A);

fprintf('************* with QR *************')
B=A;
QQQ=eye(m);

index = 0;
%QR algorithm
for i=1:100
    [Q,R] = qr(B);
    B=R*Q;
    QQQ = QQQ*Q;
    for j=1:(size(A,1)-1)
        if(abs(B(j+1,j)) < eps*( abs(B(j,j)) + abs(B(j+1,j+1))))
            fprintf('\nstop "if" was true. break')
            B
            index = 1;
            break
        end
    end
    if index == 1
        break
    end
end


fprintf('************* with Jacobi *************')

jacobi_eigenvalue( A )

fprintf('************* функцией MATLAB eig *************')
[V,D] = eig(A)
end

function [ P,D ] = jacobi_eigenvalue( A )
[n,~]=size(A);
P=eye(n);
while ~off_diag_neg(A);
    max=0;
    a=0;
    b=0;
    for i=2:n
        for j=1:i-1
            if abs(A(i,j))>max
                max=abs(A(i,j));
                a=i;
                b=j;
            end
        end
    end
    

    theta=0;
    if A(a,a)~=A(b,b)
        theta=0.5*atan(2*A(a,b)/(A(b,b)-A(a,a)));
    elseif A(a,a)==A(b,b)
        theta=pi/4;
    end
    Q=eye(n);
    Q([a,b],[a,b])=[cos(theta) sin(theta);-sin(theta) cos(theta)];
    P=P*Q;
    A=Q'*A*Q;
end
qrgivens(A);
D=A;
end

function x = off_diag_neg(A)
[n,~]=size(A);
%tol=1e-10;
 for i=2:n
        for j=1:i-1
            tol = eps*abs(A(i,i))/100;%my addition
            if abs(A(i,j))>tol
                x=0;
                return;
            end
        end
 end
    x=1;
end


function [Q,R] = qrgivens(A)
  [m,n] = size(A);
  Q = eye(m);
  R = A;
  for j = 1:n
    for i = m:-1:(j+1)
      T = eye(m);
      [c,s] = givensrotation(R(i-1,j),R(i,j)); 
      T([i,i-1],[i,i-1]) = [c s; -s c];       
      R = T'*R; % проверка - должна быть верхнетреугольная (верно)
      Q = Q*T;  
    end
  end
  Lam = Q*R
end

function [c,s] = givensrotation(a,b)
  if b == 0 
      c = 1;
      s = 0;
  else
    c = a/sqrt(a^2 + b^2);
    s = b/sqrt(a^2 + b^2);
  end
end