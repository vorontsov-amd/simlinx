from jinja2 import Template
from generate.syscall.sysParser import parse_linux_syscalls, parse_yaml
from termcolor import colored
import os
import subprocess
import re

def runcmd(cmd, verbose = False, *args, **kwargs):

    process = subprocess.Popen(
        cmd,
        stdout = subprocess.PIPE,
        stderr = subprocess.PIPE,
        text = True,
        shell = True
    )
    std_out, std_err = process.communicate()
    if verbose:
        print(std_out.strip(), std_err)
    pass


def find_simlinx_dir():
    path = os.getcwd()
    if 'simlinx' in path:
        match = re.match(r"(.*simlinx)\s*(.*)", path)
        path = match.group(1) + '/'
    else:
        print(colored('simlinx directory not found', 'red'))
        exit()
    return path

if __name__ == "__main__":
    template_cc = Template("""
        #include "syscall/syscall.gen.hh"
        #include "cpu/core.hh"

        namespace Syscall {
            {% for syscall in syscalls %}
            // {{ syscall.enum}}
            // args [{% for i in range(syscall.args|length) %} a{{ i }} {{ syscall.args[i] }}{{ ", " if not loop.last else "" }}{% endfor %}]
            Fault {{ syscall.name }}(

            {%- if syscall.name == 'not_implemented_syscall' -%}
                [[maybe_unused]] 
            {%- endif -%}

            Core& core) {
            {{ syscall.do | indent(4) }}
                return Fault::NoFault;
            }
            {% endfor %}

            std::array<SyscallFunctionType, {{ max_sys_enum }}> syscalls = {
            {% for _ in enum_range %}
            {% if _ not in sys_enum_dict.keys() %}
            not_implemented_syscall{{ ", " if not loop.last else "" }}{% else %}
            {{ sys_enum_dict[_] }}{{ ", " if not loop.last else "" }}{% endif %}
            {%- endfor -%}
            {% if true -%}\n{%- endif %}
            };                       
        }
    """)

    template_hh = Template("""
        #pragma once
        #include <functional>
        #include <stdint.h>
        #include <stdio.h>
        #include "cpu/fault.hh"

        namespace simlinx {
            struct Core;
        }

        namespace Syscall {
            using simlinx::Core;

            {% for syscall in syscalls %}
            Fault {{ syscall.name }}(Core&);
            {% endfor %}

            using SyscallFunctionType = std::function<Fault(Core&)>;
            extern std::array<SyscallFunctionType, {{ max_sys_enum }}> syscalls;
        }
    """)

    path = find_simlinx_dir()

    if not os.path.exists(path + 'generate/syscall/linux'):
        print(colored('Director was not found, createing simlinx/generate/syscall/linux', 'yellow'))
        os.makedirs(path + 'generate/syscall/linux')

    if not os.path.exists(path + 'generate/syscall/linux/syscalls.h'): 
        runcmd(f'cd {path+'generate/syscall/linux'}; wget https://raw.githubusercontent.com/torvalds/linux/refs/heads/master/include/linux/syscalls.h', verbose = True)

    if not os.path.exists(path + 'generate/syscall/linux/unistd.h'): 
        runcmd(f'cd {path+'generate/syscall/linux'}; wget https://raw.githubusercontent.com/torvalds/linux/refs/heads/master/include/uapi/asm-generic/unistd.h', verbose=True)

    syscalls=parse_yaml(path+'generate/syscall/syscalls.yaml')
    sys_enum = parse_linux_syscalls(path+'generate/syscall/')
    sys_enum_int_list = [sys[1] for sys in sys_enum]
    sys_enum_dict = {}
    for i in range(len(sys_enum_int_list)):
        sys_enum_int_list[i] = int(sys_enum_int_list[i])
    max_sys_enum = max(sys_enum_int_list) + 1

    for syscall in syscalls:
        if syscall['name'] != 'not_implemented_syscall':
            syscall['enum'] = [sys for sys in sys_enum if sys[0] == syscall['name']][0][1]
            sys_enum_dict[syscall['enum']] = syscall['name']
        else:
            syscall['enum'] = 'not implemented'
    output = template_cc.render(syscalls=syscalls, sys_enum_dict=sys_enum_dict, max_sys_enum=max_sys_enum, enum_range=[str(_) for _ in range(max_sys_enum)])

    if not os.path.exists(path + 'src/syscall'):
        print(colored('Director was not found, createing simlinx/src/syscall', 'yellow'))
        os.makedirs(path + 'src/syscall')
    with open(path + 'src/syscall/syscall.gen.cc', 'w', encoding='utf-8') as f:
        f.write(output)

    if not os.path.exists(path + 'include/syscall'):
        print(colored('Director was not found, createing simlinx/include/syscall', 'yellow'))
        os.makedirs(path + 'include/syscall')
    with open(path + 'include/syscall/syscall.gen.hh', 'w', encoding='utf-8') as f:
        f.write(template_hh.render(syscalls=syscalls, sys_enum_dict=sys_enum_dict, max_sys_enum=max_sys_enum))
