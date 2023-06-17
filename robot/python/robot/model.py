import robot_c
import math
import numpy as np
import sympy as sym
import robot.utils






def translation_matrix_general(n):
    T=sym.Matrix(4, 4, lambda i,j: 0)
    x=sym.symbols('x' + str(n))
    y=sym.symbols('y' + str(n))
    z=sym.symbols('z' + str(n) )
    Rx=sym.symbols('Rx_' + str(n))
    Ry=sym.symbols('Ry_' + str(n))
    Rz=sym.symbols('Rz_' + str(n))
    Rx1=sym.symbols('Rx1_' + str(n))
    Ry1=sym.symbols('Ry1_' + str(n))
    Rz1=sym.symbols('Rz1_' + str(n))
    # rotte origin point (the place of chile axis
    xr,yr,zr,M1 = roate_pixel(x,y,z,Rx,Ry,Rz)
    xr,yr,zr,M2 = roate_pixel(xr,yr,zr,Rx1,Ry1,Rz1)
    M = M1 * M2
    # update matrix    
    T[0,0] = M[0,0] ;
    T[0,1] = M[0,1] ;
    T[0,2] = M[0,2] ;
    T[0,3] = xr;
    T[1,0] = M[1,0] ;
    T[1,1] = M[1,1] ;
    T[1,2] = M[1,2] ;
    T[1,3] = yr;    
    T[2,0] = M[2,0] ;
    T[2,1] = M[2,1] ;
    T[2,2] = M[2,2] ;
    T[2,3] = zr;
    T[3,0] = 0 
    T[3,1] = 0
    T[3,2] = 0;
    T[3,3] = 1;
    return T


def translation_matrix(joint,n):
    T=sym.Matrix(4, 4, lambda i,j: 0)
    x=joint['origin'][0];
    y=joint['origin'][1];
    z=joint['origin'][2];
    Rx = joint['rpy'][0];
    Ry = joint['rpy'][1];
    Rz = joint['rpy'][2];
    Rx1 = sym.symbols('Rx_' + str(n)) if type(joint['axis'][0]) == str   else joint['axis'][0];
    Ry1 = sym.symbols('Ry_' + str(n)) if type(joint['axis'][1]) == str   else joint['axis'][1];
    Rz1 = sym.symbols('Rz_'+ str(n)) if type(joint['axis'][2]) == str   else joint['axis'][2];
    # rotte origin point (the place of chile axis
    xr,yr,zr,M1 = roate_pixel(x,y,z,Rx,Ry,Rz)
    xr.simplify();
    yr.simplify();
    zr.simplify();
    M1.simplify();
    for k in range(3):
            for l in range(3):
                M1[k,l] = 0 if (type(M1[k,l]) == sym.core.numbers.Float and math.fabs(M1[k,l])<0.0000001) else M1[k,l]
                   # M1[k,l] = sym.symbols(str(M1[k,l]) + '_' + str(n)) if (type(M1[k,l]) != sympy.core.numbers.Float) else M1[k,l]
    xr,yr,zr,M2 = roate_pixel(xr,yr,zr,Rx1,Ry1,Rz1)
    xr.simplify();
    yr.simplify();
    zr.simplify();
    M2.simplify();
    for k in range(3):
            for l in range(3):
                M2[k,l] = 0 if (type(M2[k,l]) == sym.core.numbers.Float and math.fabs(M2[k,l])<0.0000001) else M2[k,l]
    M = M1 * M2
    # update matrix    
    T[0,0] = M[0,0] ;
    T[0,1] = M[0,1] ;
    T[0,2] = M[0,2] ;
    T[0,3] = xr;
    T[1,0] = M[1,0] ;
    T[1,1] = M[1,1] ;
    T[1,2] = M[1,2] ;
    T[1,3] = yr;    
    T[2,0] = M[2,0] ;
    T[2,1] = M[2,1] ;
    T[2,2] = M[2,2] ;
    T[2,3] = zr;
    T[3,0] = 0 
    T[3,1] = 0
    T[3,2] = 0;
    T[3,3] = 1;
  #  v = {};
  #  v['Rx'] = joint['rpy'][0];
  #  v['Ry'] = joint['rpy'][1];
  #  v['Rz'] = joint['rpy'][2];
  #  v['Rx1'] = joint['axis'][0] if type(joint['axis'][0]) == float else sym.symbols(joint['axis'][0])
  #  v['Ry1'] = joint['axis'][1] if type(joint['axis'][1]) == float else sym.symbols(joint['axis'][1]) 
  #  v['Rz1'] = joint['axis'][2] if type(joint['axis'][2]) == float else sym.symbols(joint['axis'][2])
  #  T.subs(v)
    var_list = [];
    if type(Rx1) == sym.core.symbol.Symbol:
        var_list.append(Rx1);
    if type(Ry1) == sym.core.symbol.Symbol:
        var_list.append(Ry1);
    if type(Rz1) == sym.core.symbol.Symbol:
        var_list.append(Rz1);
    return T, var_list

#xx = generate_rotate_matrix();
def rotate_matrix_template():
    x=sym.symbols('x')
    y=sym.symbols('y')
    z=sym.symbols('z')
    Rx=sym.symbols('Rx')
    Ry=sym.symbols('Ry')
    Rz=sym.symbols('Rz')
    x,y,z,M = roate_pixel(x,y,z, Rx,Ry,Rz)
    return {'x' : str(x), 'y': str(y), 'z': str(z)}    

def translation_matrix_template(T):
    element_str=[];
    for i in range(4):
        for k in range(4):
            #v = {'jacobian_matrix_row' : '*MAT(translation,{0},{1})'.format(i,k)+'='+str(T[i,k]) }
            element_str.append('*MAT(translation,{0},{1})'.format(i,k)+'='+str(T[i,k]));
    return element_str;


def translation_forward_kinetic_template(fk):
    return {'x' : str(fk[0]), 'y': str(fk[1]), 'z': str(fk[2])} 


def roate_pixel(x,y,z,Rx,Ry,Rz):
    #   Mx=sym.Matrix([[1,0,0],[0,sym.cos(Rx),sym.sin(Rx)],[0,-sym.sin(Rx),sym.cos(Rx)]]);
    #My=sym.Matrix([[sym.cos(Ry),0,-sym.sin(Ry)],[0,1,0],[sym.sin(Ry),0,sym.cos(Ry)]]);
    #Mz=sym.Matrix([[sym.cos(Rz),sym.sin(Rz),0],[-sym.sin(Rz1),sym.cos(Rz),0],[0,0,1]]);
    Mx=sym.Matrix([[1,0,0],[0,sym.cos(Rx),-sym.sin(Rx)],[0,sym.sin(Rx),sym.cos(Rx)]]);
    My=sym.Matrix([[sym.cos(Ry),0,sym.sin(Ry)],[0,1,0],[-sym.sin(Ry),0,sym.cos(Ry)]]);
    Mz=sym.Matrix([[sym.cos(Rz),-sym.sin(Rz),0],[sym.sin(Rz),sym.cos(Rz),0],[0,0,1]]);
    M=Mx@My@Mz
    for k in range(3):
            for l in range(3):
                M[k,l] = 0 if (type(M[k,l]) == sym.core.numbers.Float and math.fabs(M[k,l])<0.0000001) else M[k,l]
    mm =M*sym.Matrix([x,y,z])
    return mm[0,0],mm[1,0],mm[2,0],M

    
def calc_gradient(n):
    T=sym.Matrix(4, 4, lambda i,j: 1 if (i==j) else 0)
    x=sym.symbols('x')
    y=sym.symbols('y')
    z=sym.symbols('z')
    for i in range(n):
        T = T * translation_matrix(i)
    func = (T[0,0] - x)*(T[0,0] - x)  + (T[1,0] - y)*(T[1,0] - y) + (mm[2,0]-z)*(mm[2,0]-z);

def calc_gradient_mse_func(m):
    m.load();
    j = m.get()
    i = 0;
    MM=sym.Matrix(4, 4, lambda i,j: 1 if (i==j) else 0)
    var_list = [];
    forwad_kinetic=[];
    while i < len(j):
        T, v = translation_matrix(j[i],i)
        MM = MM * T
        i = i + 1
        var_list = var_list + v
        xx = MM[0,3];xx.simplify();
        yy = MM[1,3];yy.simplify();
        zz = MM[2,3];zz.simplify();
        forwad_kinetic.append([xx,yy,zz]);   
    MM.simplify()
    xx = MM[0,3];
    yy = MM[1,3];
    zz = MM[2,3];
    x=sym.symbols('x')
    y=sym.symbols('y')
    z=sym.symbols('z')
    func = (xx-x)*(xx-x) + (yy-y)*(yy-y) + (zz-z)*(zz-z);
    grad=[];
    for var in var_list: 
        grad.append(func.diff(var));
    return grad, forwad_kinetic,var_list


class Model(robot_c.Model):
    def __init__(self):
        pass
    def readUrdf(self):
        pass;
    def loss(self):
        pass
    def get(self):
        self.l = super(Model, self).get() 
        self.l.reverse()
        return self.l
    def train(self):
        pass
    def gradient_mse_func(self):
        super(Model, self).load();
        j = super(Model, self).get()
        i = 0;
        MM=sym.Matrix(4, 4, lambda i,j: 1 if (i==j) else 0)
        var_list = [];
        while i < len(j):
            T, v = translation_matrix(j[i],i)
            MM = MM * T
            i = i + 1
            var_list = var_list + v
        MM.simplify()
        xx = MM[0,3];
        yy = MM[1,3];
        zz = MM[2,3];
        forwad_kinetic = [xx,yy,zz];
        import pdb;pdb.set_trace();
        x=sym.symbols('x')
        y=sym.symbols('y')
        z=sym.symbols('z')
        func = (xx-x)*(xx-x) + (yy-y)*(yy-y) + (zz-z)*(zz-z);
        grad=[];
        for var in var_list: 
            grad.append(func.diff(var));
        return grad, forwad_kinetic


#import importlib
#if __name__ == "__main__":
#importlib.reload(model)        
    
#import model
#m = model.Model()
#calc_gradient_mse_func(m)




