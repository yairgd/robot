import math
import numpy as np
import sympy as sym
import utils

def roate_z(Rz,l):
    mat = np.matrix([[math.cos(Rz), -math.sin(Rz),0 , 0],  [math.sin(Rz), math.cos(Rz), 0,0 ], [0,0,1,0],[0,0,0,1]])
    mat [0,3] = math.cos(Rz)*l;
    mat [1,3] = math.sin(Rz)*l;
    mat [2,3] = 0;
    return mat;


#forward([4,6,6,],[0.000000, 0.401455, 0.666982]) 
def forward(links):
    x=[0];
    y=[0];
    H=np.identity(4);
    for k in  range(0,len(link)):
        m = roate_z(links[k].rotation_angle[2],link.size);
        H=H@m; 
        xy = [0,0,0]
        xy.append(1)
        x.append((H@xy)[0,0])
        y.append((H@xy)[0,1])
        print (x[len(x)-1],y[len(y)-1])
    return [x[3],y[3]]


#xy,grad,J,G  = calc_roate_analitic(links, [Rz1, Rz2, Rz3])
def calc_roate_analitic_j2(links, variables):
    G=np.identity(4);   
    J = [];
    for i in range(len(links)):
        for j in range (2,3,1):
            ang = links[i].rotation_angle[j]            
            l= links[i].link_symbol
            A = sym.Matrix([[sym.cos(ang), -sym.sin(ang),0,l*sym.cos(ang)], [sym.sin(ang), sym.cos(ang),0,l*sym.sin(ang)],[0,0,1,0],[0,0,0,1]])
            G=G@A
        p=np.array([0,0,0,1])
        x_est=(G@p)[0]
        y_est=(G@p)[1]
        for j in range (2):
            J.append([])
        for j in range (len(variables)):
            var = variables[j];
            J[len(J)-2].append (sym.diff(x_est,var))
            J[len(J)-1].append (sym.diff(y_est,var))
    q_est= variables[0] + variables[1] + variables[2] 
    J.append([])
    for j in range (len(variables)):
            var = variables[j];
            J[len(J)-1].append (sym.diff(q_est,var))
    # gradient of cost 
    x = sym.symbols('x');
    y = sym.symbols('y');
    p=np.array([0,0,0,1])
    x_est=(G@p)[0]
    y_est=(G@p)[1]
    cost = (x-x_est)**2 + (y-y_est)**2
    g=[];
    for i in range (len(links)):
        Rz=sym.symbols('Rz' + str(i) )
        g.append(sym.diff(cost,Rz))
    return [x_est,y_est],g,J,G


#xy,grad,J,G  = calc_roate_analitic(links, [Rz1, Rz2, Rz3])
def calc_roate_analitic_j1(links, variables):
    import sympy as sym    
    G=np.identity(4);   
    J = [];
    for i in range(len(links)):
        for j in range (2,3,1):
            ang = links[i].rotation_angle[j]            
            l= links[i].link_symbol
            A = sym.Matrix([[sym.cos(ang), -sym.sin(ang),0,l*sym.cos(ang)], [sym.sin(ang), sym.cos(ang),0,l*sym.sin(ang)],[0,0,1,0],[0,0,0,1]])
            G=G@A
        p=np.array([0,0,0,1])
        x_est=(G@p)[0]
        y_est=(G@p)[1]
        for j in range (2):
            J.append([])
        for j in range (len(variables)):
            var = variables[j];
            J[len(J)-2].append (sym.diff(x_est,var))
            J[len(J)-1].append (sym.diff(y_est,var))
    q_est= variables[0] + variables[1] + variables[2] 
    J.append([])
    for j in range (len(variables)):
            var = variables[j];
            J[len(J)-1].append (sym.diff(q_est,var))
    # gradient of cost 
    x = sym.symbols('x');
    y = sym.symbols('y');
    p=np.array([0,0,0,1])
    x_est=(G@p)[0]
    y_est=(G@p)[1]
    cost = (x-x_est)**2 + (y-y_est)**2
    g=[];
    for i in range (len(links)):
        Rz=sym.symbols('Rz' + str(i) )
        g.append(sym.diff(cost,Rz))
    return [x_est,y_est],g,J,G


def calc_roate_analitic(links, variables):
     import sympy as sym  
     G=np.identity(4);   
     J = [];
     for i in range(len(links)):
         for j in range (2,3,1):
             ang = links[i].rotation_angle[j]            
             l= links[i].link_symbol
             A = sym.Matrix([[sym.cos(ang), -sym.sin(ang),0,l*sym.cos(ang)], [sym.sin(ang), sym.cos(ang),0,l*sym.sin(ang)],[0,0,1,0],[0,0,0,1]])
             G=G@A
         p=np.array([0,0,0,1])
         x_est=(G@p)[0]
         y_est=(G@p)[1]
         z_est=(G@p)[2]
         for j in range (3):
             J.append([])
         for j in range (len(variables)):
             var = variables[j];
             J[len(J)-3].append (sym.diff(x_est,var))
             J[len(J)-2].append (sym.diff(y_est,var))
             J[len(J)-1].append (sym.diff(z_est,var))
     q_est= variables[0] + variables[1] + variables[2] 
     J.append([])
     for j in range (len(variables)):
             var = variables[j];
             J[len(J)-1].append (sym.diff(q_est,var))
     # gradient of cost 
     x = sym.symbols('x');
     y = sym.symbols('y');
     p=np.array([0,0,0,1])
     x_est=(G@p)[0]
     y_est=(G@p)[1]
     cost = (x-x_est)**2 + (y-y_est)**2
     g=[];
     for i in range (len(links)):
         Rz=sym.symbols('Rz' + str(i) )
         g.append(sym.diff(cost,Rz))
     return [x_est,y_est],g,J,G



def print_J(J):
    for i in range(len(J)):
        for k in range(len(J[i])):
            txt = "J[{0}][{1}] = {2}".format(i,k,str(J[i][k]))
            print (txt)






class Link:
    size = 0;
    rotation_angle = [];
    link_symbol = None
    def __init__(self):
        pass


Rz1  = sym.symbols('Rz1');
Rz2  = sym.symbols('Rz2');
Rz3  = sym.symbols('Rz3');
Rx3  = sym.symbols('Rx3');


links=[Link(),Link(), Link()];
links[0].size= 4;
links[0].rotation_angle = [0,0,Rz1];
links[0].link_symbol = sym.symbols('l1')

links[1].size= 6;
links[1].rotation_angle = [0,0,Rz2];
links[1].link_symbol = sym.symbols('l2')

links[2].size= 6;
links[2].rotation_angle = [0,0,Rz3];
links[2].link_symbol = sym.symbols('l3')


xy,grad,J,G  = calc_roate_analitic(links, [Rz1, Rz2, Rz3 ])
print_J(J)

class CodeGen:
    def __init__(self):
        pass
    def jacobian(self, links, variables):
        xy,grad,J,G  = calc_roate_analitic(links, variables);
        jacobian_str=[];
        for i in range(len(J)):
            for k in range(len(J[i])):
                if all(num == 0 for num in J[i]):
                    continue;
                print (i,k)
                v = {'jacobian_matrix_row' : '*MAT(jacobian,{0},{1})'.format(i,k)+'='+str(J[i][k]) }
                jacobian_str.append(v);
        return jacobian_str
    def  jacobian_template(self, links, variables):
        jacobian_fuc={};
        jacobian_fuc['matrix_rows'] = self.jacobian(links, variables)
        jacobian_fuc['variables'] = [ str(R) for R in  variables]
        jacobian_fuc['links'] = [str(link.link_symbol)  for link in links];
        # Load the template file
        path = str(utils.get_project_root());
        path= "/home/yair/trees/project/robot/python/robot/templates"
        with open(path + '/jacobian_template.c') as file:
            template_content = file.read()
        # Create a Jinja2 Template object
        template = Template(template_content)
        # Render the template with the function and call data
        rendered_content = template.render(jacobian_fuc=jacobian_fuc)
        # Write the rendered content to a C file
        with open('/home/yair/trees/project/generated/jacobian.c', 'w') as file:
            file.write(rendered_content)



            

cg = CodeGen();
v = cg.jacobian (links, [Rz1, Rz2, Rz3 ]);
cg.jacobian_template (links, [Rz1, Rz2, Rz3 ]);


from jinja2 import Template

# Define the function and call data
functions = [
    {
        'name': 'add',
        'parameters': [{'type': 'int', 'name': 'a'}, {'type': 'int', 'name': 'b'}],
        'body': 'printf("Sum: %d\\n", a + b);'
    },
    {
        'name': 'subtract',
        'parameters': [{'type': 'int', 'name': 'a'}, {'type': 'int', 'name': 'b'}],
        'body': 'printf("Difference: %d\\n", a - b);'
    }
]
function_calls = [
    {
        'function_name': 'add',
        'arguments': [5, 3]
    },
    {
        'function_name': 'subtract',
        'arguments': [10, 7]
    }
]
# Load the template file
with open('/home/yair/trees/project/jacobian_template.c') as file:
    template_content = file.read()

# Create a Jinja2 Template object
template = Template(template_content)

# Render the template with the function and call data
rendered_content = template.render(functions=functions, function_calls=function_calls)

# Write the rendered content to a C file
with open('output.c', 'w') as file:
    file.write(rendered_content)


