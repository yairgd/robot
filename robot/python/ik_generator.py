#!/usr/bin/python
# https://www.cs.cmu.edu/~16311/current/schedule/ppp/Lec17-FK.pdf
import matplotlib.pyplot as plt
import numpy as np
import math
import sdl1

plt.style.use('_mpl-gallery')

#xy,grad,J,G = calc_roate_analitic_z(3)
def calc_roate_analitic_z(num_of_links):
    G=np.identity(4);   
    x = sym.symbols('x');
    y = sym.symbols('y');
    J = [];
    for i in range(num_of_links):
        phi=sym.symbols('phi' + str(i) )
        l=sym.symbols('l' + str(i))
        A = sym.Matrix([[sym.cos(phi), -sym.sin(phi),0,l*sym.cos(phi)], [sym.sin(phi), sym.cos(phi),0,l*sym.sin(phi)],[0,0,1,0],[0,0,0,1]])
        G=G@A
        print (G)
        p=np.array([0,0,0,1])
        x_est=(G@p)[0]
        y_est=(G@p)[1]
        J.append([])
        J.append([])
        for j in range (num_of_links):
            phi=sym.symbols('phi' + str(j) )
            J[len(J)-1].append (sym.diff(x_est,phi))
            J[len(J)-2].append (sym.diff(y_est,phi))
    # gradient of cost 
    p=np.array([0,0,0,1])
    x_est=(G@p)[0]
    y_est=(G@p)[1]
    cost = (x-x_est)**2 + (y-y_est)**2
    g=[];
    for i in range (num_of_links):
        phi=sym.symbols('phi' + str(i) )
        g.append(sym.diff(cost,phi))
    return [x_est,y_est],g,J,G


#xy,grad,J,G = calc_roate_analitic_z(3)
def calc_roate_analitic_z(num_of_links):
    import sympy as sym    
    G=np.identity(4);   
    x = sym.symbols('x');
    y = sym.symbols('y');
    J = [];
    for i in range(num_of_links):
        phi=sym.symbols('phi' + str(i) )
        l=sym.symbols('l' + str(i))
        A = sym.Matrix([[sym.cos(phi), -sym.sin(phi),0,l*sym.cos(phi)], [sym.sin(phi), sym.cos(phi),0,l*sym.sin(phi)],[0,0,1,0],[0,0,0,1]])
        G=G@A
    p=np.array([0,0,0,1])
    x_est=(G@p)[0]
    y_est=(G@p)[1]
    q_est=sym.symbols('phi0') +  sym.symbols('phi1') + sym.symbols('phi2');
    J.append([])
    J.append([])
    J.append([])
    for j in range (num_of_links):
        phi=sym.symbols('phi' + str(j) )
        J[0].append (sym.diff(x_est,phi))
        J[1].append (sym.diff(y_est,phi))
        J[2].append (sym.diff(q_est,phi))
    # gradient of cost 
    p=np.array([0,0,0,1])
    x_est=(G@p)[0]
    y_est=(G@p)[1]
    cost = (x-x_est)**2 + (y-y_est)**2
    g=[];
    for i in range (num_of_links):
        phi=sym.symbols('phi' + str(i) )
        g.append(sym.diff(cost,phi))
    return [x_est,y_est],g,J,G

#print_J(J)
def print_J(J):
    for i in range(len(J)):
        for k in range(3):
            txt = "*MAT(jacobian,{0},{1}) = {2};".format(i,k,str(J[i][k]))
            print (txt)

def calc_roate_analitic_z(phi,l):
sin_phi1=sym.symbols('sin(phi1)')
cos_phi1=sym.symbols('cos(phi1)')
l1=sym.symbols('l1')
A = sym.Matrix([[cos_phi1, -sin_phi1,0,l1*cos_phi1], [sin_phi1, cos_phi1,0,l1*sin_phi1],[0,0,1,0],[0,0,0,1]])

sin_phi2=sym.symbols('sin(phi2)')   
cos_phi2=sym.symbols('cos(phi2)')
l2=sym.symbols('l2')
B = sym.Matrix([[cos_phi2, -sin_phi2,0,l2*cos_phi2], [sin_phi2, cos_phi2,0,l2*sin_phi2],[0,0,1,0],[0,0,0,1]])

sin_phi3=sym.symbols('sin(phi3)')
cos_phi3=sym.symbols('cos(phi3)')
l3=sym.symbols('l3')
C = sym.Matrix([[cos_phi3, -sin_phi3,0,l3*cos_phi3], [sin_phi3, cos_phi3,0,l3*sin_phi3],[0,0,1,0],[0,0,0,1]])
p=np.array([0,0,0,1])
x=(A@B@C@p)[0]
y=(A@B@C@p)[1]


#calc_xy_3_analitic(link , [math.radians(29.19947465), math.radians(13.53225159),  math.radians(4.51121847)])
def calc_xy_3_analitic(l,phi):
    from math import cos
    from math import sin
    phi0 = phi[0];
    phi1 = phi[1];
    phi2 = phi[2];
    l0=l[0];
    l1=l[1];
    l2=l[2];
    x = 1.0*l0*cos(phi0) - 1.0*l1*sin(phi0)*sin(phi1) + 1.0*l1*cos(phi0)*cos(phi1) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2)
    y = 1.0*l0*sin(phi0) + 1.0*l1*sin(phi0)*cos(phi1) + 1.0*l1*sin(phi1)*cos(phi0) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*cos(phi2)
    return [x,y,0]


# j = ik_jacobian_func_analytic(link , [math.radians(29.19947465), math.radians(13.53225159),  math.radians(4.51121847)])
def ik_jacobian_func_analytic1(link,phi):
    J = np.zeros([6,3])
    from math import cos
    from math import sin
    phi0 = phi[0];
    phi1 = phi[1];
    phi2 = phi[2];
    l0=link[0];
    l1=link[1];
    l2=link[2];
    J[0][0] = 1.0*l0*cos(phi0)
    J[0][1] = 0
    J[0][2] = 0
    J[1][0] = -1.0*l0*sin(phi0)
    J[1][1] = 0
    J[1][2] = 0
    J[2][0] = 1.0*l0*cos(phi0) - 1.0*l1*sin(phi0)*sin(phi1) + 1.0*l1*cos(phi0)*cos(phi1)
    J[2][1] = -1.0*l1*sin(phi0)*sin(phi1) + 1.0*l1*cos(phi0)*cos(phi1)
    J[2][2] = 0
    J[3][0] = -1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0)
    J[3][1] = -1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0)
    J[3][2] = 0
    J[4][0] = 1.0*l0*cos(phi0) - 1.0*l1*sin(phi0)*sin(phi1) + 1.0*l1*cos(phi0)*cos(phi1) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2)
    J[4][1] = -1.0*l1*sin(phi0)*sin(phi1) + 1.0*l1*cos(phi0)*cos(phi1) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2)
    J[4][2] = l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*sin(phi2)
    J[5][0] = -1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) + l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2)
    J[5][1] = -1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) + l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2)
    J[5][2] = -l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2)    
    return J


def ik_jacobian_func_analytic(link,phi):
    J = np.zeros([3,3])
    from math import cos
    from math import sin
    phi0 = phi[0];
    phi1 = phi[1];
    phi2 = phi[2];
    l0=link[0];
    l1=link[1];
    l2=link[2];
    J[0][0] = -1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) + l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2)
    J[0][1] = -1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) + l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2)
    J[0][2] = -l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2)
    J[1][0] = 1.0*l0*cos(phi0) - 1.0*l1*sin(phi0)*sin(phi1) + 1.0*l1*cos(phi0)*cos(phi1) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2)
    J[1][1] = -1.0*l1*sin(phi0)*sin(phi1) + 1.0*l1*cos(phi0)*cos(phi1) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2)
    J[1][2] = l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*sin(phi2)
    J[2][0] = 1
    J[2][1] = 1
    J[2][2] = 1
    return J

#ik_cost_gradient_func_analytic(link,[10.411930818340064, 7.603239324984113,0],[math.radians(29.19947465), math.radians(13.53225159),  math.radians(4.51121847)])
def ik_cost_gradient_func_analytic(link,taget_xy,phi):
    from math import cos
    from math import sin
    l0=link[0];
    l1=link[1];
    l2=link[2];
    x = taget_xy[0];
    y = taget_xy[1];
    z = taget_xy[2];
    phi0 = phi[0];
    phi1 = phi[1];
    phi2 = phi[2];
    g0 =  (2.0*l0*sin(phi0) + 2.0*l1*sin(phi0)*cos(phi1) + 2.0*l1*sin(phi1)*cos(phi0) - 2*l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2))*(-1.0*l0*cos(phi0) + 1.0*l1*sin(phi0)*sin(phi1) - 1.0*l1*cos(phi0)*cos(phi1) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2) + x) + (-2.0*l0*cos(phi0) + 2.0*l1*sin(phi0)*sin(phi1) - 2.0*l1*cos(phi0)*cos(phi1) - 2*l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2))*(-1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) - l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*cos(phi2) + y);
    g1 = (2.0*l1*sin(phi0)*sin(phi1) - 2.0*l1*cos(phi0)*cos(phi1) - 2*l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2))*(-1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) - l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*cos(phi2) + y) + (2.0*l1*sin(phi0)*cos(phi1) + 2.0*l1*sin(phi1)*cos(phi0) - 2*l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2))*(-1.0*l0*cos(phi0) + 1.0*l1*sin(phi0)*sin(phi1) - 1.0*l1*cos(phi0)*cos(phi1) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2) + x)
    g2 = (2*l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2))*(-1.0*l0*cos(phi0) + 1.0*l1*sin(phi0)*sin(phi1) - 1.0*l1*cos(phi0)*cos(phi1) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2) + x) + (-2*l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + 2*l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*sin(phi2))*(-1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) - l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*cos(phi2) + y)
    return np.array([g0,g1,g2])

def roate_z(phi,l):
    mat = np.matrix([[math.cos(phi), -math.sin(phi),0 , 0],  [math.sin(phi), math.cos(phi), 0,0 ], [0,0,1,0],[0,0,0,1]])
    mat [0,3] = math.cos(phi)*l;
    mat [1,3] = math.sin(phi)*l;
    mat [2,3] = 0;
    return mat;


def calc_xy_3(link,phi):
    x=[0];
    y=[0];
    for k in  range(0,len(link)):
        H=np.identity(4);
        for i in range(0,k+1):
            m = roate_z(phi[i],link[i]);
            H=H@m; 
        xy = [0,0,0]
        xy.append(1)
        x.append((H@xy)[0,0])
        y.append((H@xy)[0,1])
    return [x[3],y[3]]

def ik_cost_func(link,taget_xy,phi):
  xy = calc_xy_3_analitic(link,phi);
  return (taget_xy[0]-xy[0])**2 + (taget_xy[1]-xy[1])**2

#ik_cost_gradient_func(link,[10.411930818340064, 7.603239324984113,0],[math.radians(29.19947465), math.radians(13.53225159),  math.radians(4.51121847)])
def ik_cost_gradient_func(link,xy,phi):
    h = 0.0000001;
    f = ik_cost_func(link, xy, phi);
    diff=[];
    diff.append ((ik_cost_func(link, xy, [phi[0]+h,phi[1],phi[2]]) - f)/h);
    diff.append ((ik_cost_func(link, xy, [phi[0],phi[1]+h,phi[2]]) - f)/h);
    diff.append ((ik_cost_func(link, xy, [phi[0],phi[1],phi[2]+h]) - f)/h);
    return np.array(diff)


#calc_grdient_decent(link,[10.411930818340064, 7.603239324984113,0])
def calc_grdient_decent(link, taget_xy,*args, **kwargs):
    phi = kwargs.get('phi', [0,0,0]) 
    norm = 100;
    #print (phi)
    alpha = 0.001;
    while norm > 0.1:
        diff_phi = ik_cost_gradient_func_analytic(link, taget_xy,phi);
        phi = phi - alpha*diff_phi;
        norm = math.sqrt(np.linalg.norm(diff_phi))
        #xy_new=calc_xy_3_analitic(link, [phi[0], phi[1], phi[2]] )
        #norm = math.sqrt(np.linalg.norm(np.array(xy_new)-np.array(taget_xy)))
       # print (norm)
        #print ([math.degrees(phi[0]), math.degrees(phi[1]) , math.degrees(phi[2])] ,diff_phi,norm,"!!!!!!!!!!!!")
    return [math.degrees(phi[0]), math.degrees(phi[1]) , math.degrees(phi[2])] 



def arm_xy_3(ll,phi):
    x=[0];
    y=[0];
    for k in  range(0,len(ll)):
        H=np.identity(4);
        print("calc H")
        for i in range(0,k+1):
            print(i)
            m = roate_z(phi[i],ll[i]);
            H=H@m; 
        xy = [0,0,0]
        xy.append(1)
        x.append((H@xy)[0,0])
        y.append((H@xy)[0,1])
    fig,ax = plt.subplots()
    ax.plot(x, y, marker='*',linewidth=2.0)
    plt.show()




link=[7.0,4,2]
phi=[30, 10, 10];

calc_xy_3(link,phi)
arm_xy_3(link,phi);


calc_grdient_decent(link,[10.411930818340064, 7.603239324984113,0])


arm_xy_3 (link,[29.19947465, 13.53225159,  4.51121847])
calc_xy_3(link,[29.19947465, 13.53225159,  4.51121847])




calc_grdient_decent(link,[10.411930818340064, 7.613239324984113,0])
calc_grdient_decent(link,[10.411930818340064, 7.613239324984113,0],phi=np.array([29.19947465, 13.53225159,  4.51121847]))

arm_xy_3 (link,[36.97357171,  0.09682712, -0.07411021])

link=[7.0,4,2]
phi=[0,0,0];
xy=[10.411930818340064, 7.603239324984113,0]
p1=[];
p2=[];
p3=[];
for i in range(1,1000):
    phi = calc_grdient_decent(link,xy,phi=phi);phi = np.deg2rad(phi)
    xy_new=calc_xy_3(link,phi);xy_new.append(0);print(np.linalg.norm(np.array(xy)-xy_new));xy=xy_new;xy[1]=xy[1]+0.01
    p1.append(phi[0]);
    p2.append(phi[1]);
    p3.append(phi[2]);



link=[2.0,8,4]
phi=[0,0,0];
p1=[];
p2=[];
p3=[];
yy=[];
xx=[];
xy=[5, 7.603239324984113,0]
for i in range(1,100):
    phi = calc_grdient_decent(link,xy,phi=[math.radians(phi[0]), math.radians(phi[1]), math.radians(phi[2])] );xy_new=calc_xy_3_analitic(link, [math.radians(phi[0]), math.radians(phi[1]), math.radians(phi[2])] );
    xy=xy_new;xy[1]=xy[1]-0.1;
    print (xy)
    p1.append(phi[0]);
    p2.append(phi[1]);
    p3.append(phi[2]);
    yy.append(xy_new[1]);
    xx.append(xy_new[0]);
fig,ax = plt.subplots()
ax.plot(xx, yy)
ax.set_xlim([4,6])
plt.show()


xy=[5, 13,0]
link=[7.0,4,8]
phi=[0,0,0];
k=100
p1=[];
p2=[];
p3=[];
yy=[];
xx=[];
while k != 0:
    phi = calc_grdient_decent(link,xy,phi=[math.radians(phi[0]), math.radians(phi[1]), math.radians(phi[2])] );xy_new=calc_xy_3_analitic(link, [math.radians(phi[0]), math.radians(phi[1]), math.radians(phi[2])] );
    print (xy_new)
    xy[1]=xy[1]-0.1;
    k=k-1
    p1.append(phi[0]);
    p2.append(phi[1]);
    p3.append(phi[2]);
    yy.append(xy_new[1]);
    xx.append(xy_new[0]);
fig,ax = plt.subplots()
ax.plot(xx, yy)
ax.set_xlim([4,6])
plt.show()


#http://www.boris-belousov.net/2016/07/29/jacobians/
#https://robotics-explained.com/jacobian
xy=np.array([8.411930818340064, 7.603239324984113,0]) #,10.411930818340064, 7.603239324984113,10.411930818340064, 7.603239324984113])
link=[7.0,4,2]
k=10000
p1=[];
p2=[];
p3=[];
yy=[];
xx=[];
phi=np.array([0.0001,0.0001,0.0001])
#phi = np.deg2rad(calc_grdient_decent(link,[xy[0],xy[1],0]))
xy[1]=xy[1]-0;
#phi = np.deg2rad(phi)
while True:

j = ik_jacobian_func_analytic(link ,phi)
xy_new=calc_xy_3_analitic(link, phi);
#xy_new=[xy_new[0], xy_new[1]]) #, xy_new[0], xy_new[1],xy_new[0], xy_new[1]]
delta = (np.linalg.inv(j.transpose()@j)@j.transpose())@np.array(xy-xy_new)
#delta = (j@np.linalg.inv(j.transpose()@j))@np.array(xy-xy_new).transpose()
phi = phi + delta*0.001

    if np.linalg.norm(xy_new-xy)<0.00000000001 or k<0:
        break;
    print(np.rad2deg(phi),xy_new )
    k=k-1



#http://www.boris-belousov.net/2016/07/29/jacobians/
xy=np.array([3,3])
link=[7.0,4,2]
k=10
p1=[];
p2=[];
p3=[];
yy=[];
xx=[];
phi=[0,0,0]
xy_new=[0,0]
#phi = np.deg2rad(calc_grdient_decent(link,[xy[0],xy[1],0]))
#xy_new=calc_xy_3_analitic(link, phi);
#xy_new=[xy_new[0], xy_new[1]] #, xy_new[0], xy_new[1],xy_new[0], xy_new[1]]
#xy_new
#phi = np.deg2rad(phi)
alpha=0.0001
#xy_new=[0,0]
#xy_new=calc_xy_3_analitic(link, phi);
#xy_new=np.array([xy_new[0], xy_new[1]]) #, xy_new[0], xy_new[1],xy_new[0], xy_new[1]])
last_norm=100;
dd=np.array([100,100,100])
e=100;
while np.linalg.norm(e) > 0.0001:
    xy_new=calc_xy_3_analitic(link, phi);
    xy_new=[xy_new[0], xy_new[1]] #, xy_new[0], xy_new[1],xy_new[0], xy_new[1]]    
    j = ik_jacobian_func_analytic(link ,phi)
    j=j[4:6:1];
    j_t = np.transpose(j)
    e=xy-xy_new
    dq = np.dot(j_t, e)
    phi = phi + dq*alpha
    #if (abs(last_norm - np.linalg.norm(xy_new - xy)) < 0.001):
     #       break;
   # if (last_norm < np.linalg.norm(xy_new - xy)):
    #    phi = phi - dd;
    #else:
    last_norm = np.linalg.norm(xy_new - xy)
    print(last_norm - np.linalg.norm(xy_new - xy) , np.rad2deg(phi),xy_new )




 #[29.19947465, 13.53225159,  4.51121847];



plt.plot(range(1,len(p1)),p1, linewidth=2.0)
plt.plot(range(1,len(p2)),p2, linewidth=2.0)
plt.plot(range(1,len(p3)),p3, linewidth=2.0)
plt.show()




fig,ax = plt.subplots()
ax.plot(xx, yy)
ax.set_xlim([4,6])
plt.show()

plt.plot(xx,yy, linewidth=2.0)
plt.show()

