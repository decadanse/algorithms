function main
clc; clear all;
%f=5*y'''(t)+9.7*y''(t)+1.5*y'(t)+0.4*y(t)=4 
E = [1 0 0; 0 1 0; 0 0 1];
A = [0 1 0; 0 0 1; -0.08 -0.3 -1.94];
B = [0; 0; 0.2];
u = 4;
X0 = [0; 0; 0];
h = 0.1; %0.00001;
N = 80/h;

%расчет X1
eil_Xk_plus_1 = eiler_with_E(h, X0, B, u, E, A);
X1=eil_Xk_plus_1; 

n = floor(N) %округление в меньшую сторону
a{1} = X0;
a{2} = X1;
delta = 0;

for i=3:N  
    Xk = a{i-1};
    Xk_m_1 = a{i-2};
    Xk_p_1 = adams_bashfort_2_with_E(h, Xk, Xk_m_1, B, u, E, A)
    a{i} = Xk_p_1;
    
    delta = delta + (a{i}-a{i-1});
    i=i+h;
end
delta_mid = abs(delta/(N-1))

%------------------------------------------- Runge-Kutta 4
tspan = [0 80];
t = 0:h:80;
n = numel(t);
x = zeros(3, n);
x(:, 1) = [0; 0; 0];
y(:, 1) = [0;0;0];

f = @(t,y) myf_v2(t,y,A,B,u);
t(1) = 0;
 for j = 1:(n-1)
   k1 = f( t(j), y(:, j) );
   k2 = f( t(j) + h/2, y(:, j) + k1/2 );
   k3 = f( t(j) + h/2, y(:, j) + k2/2 );
   k4 = f( t(j) + h, y(:, j) + k3 );
   y(:, j+1) = y(:, j) + h*(k1 + 2*k2 + 2*k3 + k4)/6;
   t(j+1)=t(j)+h;
 end
figure(1)
plot(t, y)
title('Runge-Kutta 4')
xlabel('Time t');
ylabel('Solution x');
%извлечение зависимости с 1й линией
Y1 = y(1,:);
figure(2)
plot(t, Y1)
%------------------------------------------- ode45
tspan = [0 80];
f = @(t,x) myf_v2(t,x,A,B,u);
[t,x] = ode45(f, tspan, X0);
figure(3)
plot(t, x)
title('ode45')
xlabel('Time t');
ylabel('Solution x');
%извлечение зависимости с 1й линией
S = [t,x];
S1 = S(:,1);
S2 = S(:,2);
figure(4)
plot(S1, S2)
end

function eil_Xk_plus_1=eiler_with_E(h, Xk, B, u, E, A)
eil_Xk_plus_1 = (E + h*A)*Xk + h*B*u;
end

function Xk_p_1=adams_bashfort_2_with_E(h, Xk, Xk_m_1, B, u, E, A)
Xk_p_1 = (E + 1.5*h*A)*Xk + 1.5*h*B*u - 0.5*h*A*Xk_m_1 - 0.5*h*B*u;
end

function dxdt = myf(~,x,A,B,u)
dxdt = A*x + B*u;
end

function dxdt = myf_v2(~,X,A,B,u)
dxdt = zeros(3,1);
dxdt(1) = X(2);
dxdt(2) = X(3);
dxdt(3) = -1.94*X(3)-0.3*X(2)-0.08*X(1)+0.8; 
end
