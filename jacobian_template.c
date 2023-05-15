/*
 * =====================================================================================
 *
 *       Filename:  jacobian_template.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/17/2023 08:32:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#include <stdio.h>

{% for function in functions %}
void {{ function.name }}({% for param in function.parameters %}{{ param.type }} {{ param.name }}{% if not loop.last %}, {% endif %}{% endfor %}) {
    // Function body
    {{ function.body }}
}
{% endfor %}

int main() {
    {% for call in function_calls %}
    {{ call.function_name }}({% for arg in call.arguments %}{{ arg }}{% if not loop.last %}, {% endif %}{% endfor %});
    {% endfor %}

    return 0;
}
