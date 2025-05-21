import argparse
import json
import csv
import os
import isaTemplateHandler as tmph
from autoClangFormat import make_clang_format

decoder_tree_header = """
#define assign(left, right) decodedInstr.left = right ;

#define useRS1 assign(rs1, RS1)
#define useRS2 assign(rs2, RS2)
#define useRD assign(rd, RD)
#define useCSR assign(csr, CSR)
#define setExec(_set_exec_func) assign(exec, _set_exec_func)

using ISA::bitsFrom;
void simlinx::Core::decode(uint32_t decodedBits, ISA::BasedInstruction& decodedInstr) {
"""

class Generator:
    gap=0
    out=''
    pointer=0
    tab=2

    hereDir = os.getcwd()
    cpuDir = 'cpu'
    cpuDirCC = f'../src/{cpuDir}/'
    cpuDirHH = f'../include/{cpuDir}/'

    def __init__(self, text: list):
        self.txt = text
        self.enum = []

        self.handler = tmph.YamlHandler()
        self.handler.get_impl_set(['generate/isa/execDecodeRvZicsr.isa.yaml', 'generate/isa/execDecode.isa.yaml', 'generate/isa/m.isa.yaml'])
        self.impl_instr = self.handler.get_impl_names()


    def get_token(self, who:str='noone')->str:
        token = self.txt[self.pointer] if self.pointer < len(self.txt) else None
        self.pointer += 1
        return token


    def return_token(self)->None:
        if self.pointer > 0:
            self.pointer -= 1


    def ID(self)->str|None:
        instr = self.get_token('id')
        if self.handler.find_impl_instr(instr.lower()):
            self.enum.append(f'{instr}')
            return self.handler.creat_decoder_block(tab=self.gap+self.tab)
        else:
            return None


    def decode(self)->None:
        token = self.get_token('decode')
        if token[:7] == 'decode(' and token[-1] == ')':
            if self.get_token('decode') == '{':
                token = token[7:-1]
                token = token.split('-')

                switch_arg = ''
                if isinstance(token, list):
                    if len(token) > 1:
                        switch_arg = f'(bitsFrom(decodedBits, {token[1]}, {token[0]}))'
                    else:
                        switch_arg = f'(bitsFrom(decodedBits, {token[0]}, {token[0]}))'

                out_line = ' '*self.gap + f'switch({switch_arg}) {{\n'

                self.gap += self.tab
                case = self.case()

                token = self.get_token('decode')
                if token == '}':
                    self.gap -= self.tab
                    if case:
                        out_line += case
                        out_line += ' '*(self.gap+self.tab) + 'default: {decodedInstr.matchBitsId(decodedBits, InstrId::NONE);}\n'
                        out_line += ' '*self.gap + f'}}\n'
                    else:
                        out_line = ''
                return (True, out_line)
            else:
                raise ValueError
        else:
            self.return_token()
            return None, ''


    def case(self)->None:
        out_line = ''
        while True:
            token = self.get_token('case')
            if token[-1] == ':':
                token = token[:-1]
                self.gap += self.tab
                decode = self.decode()
                self.gap -= self.tab
                if not decode[0]:
                    id = self.ID()
                    if id:
                        out_line += ' '*self.gap + f'case 0{token}: {{\n'\
                                    + id\
                                    + ' '*(self.gap+self.tab) + f'break;\n' + ' '*self.gap + '}\n'
                else:
                    if decode[1]:
                        out_line += ' '*self.gap + f'case 0{token}: {{\n'\
                                    + decode[1]\
                                    + ' '*(self.gap+self.tab) + f'break;\n' + ' '*self.gap + '}\n'
            else:
                self.return_token()
                break
        return out_line


    def make_decode_tree(self)->None:
        with open(self.cpuDirCC+'decodeTree.gen.cc', 'w', encoding='utf-8') as f:
            f.write(self.make_header('decodeTree', 'cpu'))
            f.write(self.make_header('bitfields', 'cpu'))
            f.write(decoder_tree_header + self.out + '}\n')
            f.write(self.handler.handle_undef_bitfields())


    def make_header(self, file_name:str, dirHH:str)->str:
        path = os.getcwd()
        include_str = '#pragma once\n'
        madeHeader = dirHH+f'/{file_name}.gen.hh'
        for fileToInclude in ['core']:
            include_str = include_str+ f'#include "cpu/{fileToInclude}.hh"\n'
        open(path+'/../include/'+madeHeader, 'w', encoding='utf-8').write(include_str)
        return f'#include "{madeHeader}"\n'


    def start(self)->None:
        _, self.out = self.decode()
        self.make_decode_tree()
        self.handler.print_warning()
        self.handler.handle_execute()
        self.handler.handle_enum()
        self.handler.handle_bitfields()
        # make_clang_format()


if __name__ == '__main__':
    current_directory = os.path.dirname(os.path.abspath(__file__))
    os.chdir(current_directory)

    text = []
    with open('isa/decoderTree.isa', 'r', encoding="utf-8") as f:
        for line in f:
            line = line.split()
            if line:
                text  = text + line
    gen = Generator(text)
    gen.gap = gen.tab
    gen.start()