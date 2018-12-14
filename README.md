# :rainbow: Modular-robotic-manipulator :octocat:


## Calculando a aceleração no sentido do movimento

 ![2](https://latex.codecogs.com/gif.latex?A%20%3D%20-k*g*sin%28%5CTheta%20%29)

Calcularemos as componentes da aceleração Ax e Ay criando um vetor de coordenadas e aproximando a um polinômio de grau 2. [Código da aproximação MMQ](https://github.com/LuizFelipeLemon/CN/blob/master/MMQ%2BEDO/MMQ/mmq.sci)

![E1](https://latex.codecogs.com/gif.latex?x%20%3D%20a_%7B0%7D%20&plus;%20a_%7B1%7Dt%20&plus;%20%5Cfrac%7Ba_%7B2%7D%7D%7B2%7D%20t)
```
t = [0.434 0.567 0.7 0.833 0.966 1.1 1.233 1.357 1.5 1.636 1.767 1.9];
x = [116 125 144 173 210 257 313 378 449 525 611 701]; 
plot(t,x,'o');
a = mmq(t,x,2);
```
>a  = [124.66413  -128.75248  228.43345]

**2*Ax = 228.43345** 

**Ax = 114.21672**
```
plot(p , a(1) + a(2).*p + a(3).*(p.^2),'r')
```

![Aproximação por MMQ](https://github.com/LuizFelipeLemon/CN/blob/master/MMQ%2BEDO/MMQ/x(t).png)

![E1](https://latex.codecogs.com/gif.latex?y%20%3D%20a_%7B0%7D%20&plus;%20a_%7B1%7Dt%20&plus;%20%5Cfrac%7Ba_%7B2%7D%7D%7B2%7D%20t)
```
t = [0.434 0.567 0.7 0.833 0.966 1.1 1.233 1.357 1.5 1.636 1.767 1.9];
y = [300 298 296 295 292 288 284 281 278 276 274 269]; 
plot(t,y,'o');
a = mmq(t,y,2);
```
>a  = [307.70819  -14.871749  -2.8316649]

**2*Ay = -2.8316649**

**Ay = -1.4158324**

```
plot(p,a(1) + a(2).*p + a(3).*(p.^2),'r')
```
![Aproximação por MMQ](https://github.com/LuizFelipeLemon/CN/blob/master/MMQ%2BEDO/MMQ/y(t).png)

![EQ](https://latex.codecogs.com/gif.latex?A%20%3D%20%5Csqrt%7BA_%7Bx%7D%20&plus;%20A_%7By%7D%7D)

**A = 114.2255**