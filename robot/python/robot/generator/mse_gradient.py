import math
import numpy as np
import sympy as sym
import utils
from jinja2 import Template



m = Model()
m.load()
mse_grad, forwad_kinetic,var_list =calc_gradient_mse_func(m);
var_list = [str(var) for var  in  var_list]


# Load the template file
with open('/home/yair/trees/project/robot/python/robot/templates/jacobian_template.c') as file:
    template_content = file.read()

# Create a Jinja2 Template object
template = Template(template_content)

# Render the template with the function and call data
rendered_content = template.render(forwad_kinetic=forwad_kinetic, var_list= var_list, mse_grad=mse_grad)

# Write the rendered content to a C file
with open('/home/yair/trees/project/generated/output.c', 'w') as file:
    file.write(rendered_content)





