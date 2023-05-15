import numpy as np
import pysym as sym


#xy,grad,J,G = calc_roate_analitic_z(3)
def calc_roate_analitic_z(num_of_links):
    G=np.identity(4);   
    x = sym.symbols('x');
    y = sym.symbols('y');
    J = [];
    for i in range(num_of_links):
        Rz=sym.symbols('Rz' + str(i) )
        l=sym.symbols('l' + str(i))
        A = sym.Matrix([[sym.cos(Rz), -sym.sin(Rz),0,l*sym.cos(Rz)], [sym.sin(Rz), sym.cos(Rz),0,l*sym.sin(Rz)],[0,0,1,0],[0,0,0,1]])
        G=G@A
    p=np.array([0,0,0,1])
    x_est=(G@p)[0]
    y_est=(G@p)[1]
    q_est=sym.symbols('Rz0') +  sym.symbols('Rz1') + sym.symbols('Rz2');
    J.append([])
    J.append([])
    J.append([])
    for j in range (num_of_links):
        Rz=sym.symbols('Rz' + str(j) )
        J[0].append (sym.diff(x_est,Rz))
        J[1].append (sym.diff(y_est,Rz))
        J[2].append (sym.diff(q_est,Rz))
    # gradient of cost 
    p=np.array([0,0,0,1])
    x_est=(G@p)[0]
    y_est=(G@p)[1]
    cost = (x-x_est)**2 + (y-y_est)**2
    g=[];
    for i in range (num_of_links):
        Rz=sym.symbols('Rz' + str(i) )
        g.append(sym.diff(cost,Rz))
    return [x_est,y_est],g,J,G



def print_J(J):
    for i in range(len(J)):
        for k in range(3):
            txt = "J[{0}][{1}] = {2}".format(i,k,str(J[i][k]))
            print (txt)


