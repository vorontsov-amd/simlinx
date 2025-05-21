from jinja2 import Template
from termcolor import colored
import copy
import csv

from syscall.sysParser import parse_yaml
from syscall.sysGen import find_simlinx_dir
from templates import *

class YamlHandler:
    implInstrSet = []
    implDecodedInstrSet = []
    implInstrNames = []
    implInstrNotInTree = []
    foundInstr = None

    def __init__(self):
        self.path = find_simlinx_dir()

    def find_impl_instr(self, name: str):
        for instr in self.implInstrSet:
            if instr['instruction'] == name:
                self.implInstrNotInTree.remove(name)
                self.set_decoded_instr(instr)
                self.foundInstr = instr
                return instr
        return None

    def get_impl_set(self, yamls: list):
        for yaml in yamls:
            # print(path + yaml)
            self.implInstrSet = self.implInstrSet + parse_yaml(self.path + yaml)
        return self.implInstrSet

    def get_impl_names(self):
        for instr in self.implInstrSet:
            self.implInstrNames.append(instr['instruction'])
        self.implInstrNotInTree = copy.copy(self.implInstrNames)
        return self.implInstrNames

    def set_decoded_instr(self, implemInstr: dict):
        implemInstr['instruction'] = implemInstr['instruction'][0].upper() + implemInstr['instruction'][1:]
        if 'isEBB' not in implemInstr.keys():
            implemInstr['isEBB'] = False
        else:
            implemInstr['isEBB'] = True
        
        if 'updateCoreState' not in implemInstr.keys():
            implemInstr['updateCoreState'] = False
        else:
            implemInstr['updateCoreState'] = True

        for sign in ['+=', '-=', '=']:
            for gap in [' ', '']:
                token = 'pc_reg' + gap + sign
                if token in implemInstr['execute']:
                    implemInstr['isEBB'] = True
                    break
        if 'pc_reg' in implemInstr['execute']:
            implemInstr['updateCoreState'] = True
        implemInstr['unusedCore'] = ''
        implemInstr['unusedBasedInstr'] = ''
        if 'core' not in implemInstr['execute']:
            implemInstr['unusedCore'] = '[[maybe_unused]]'

        if 'instr' not in implemInstr['execute']:
            implemInstr['unusedBasedInstr'] = '[[maybe_unused]]'

        self.implDecodedInstrSet.append(implemInstr)

    def print_warning(self):
        for instr in self.implInstrNotInTree:
            print(colored(f'WARNING: {instr} not in decode tree.', 'yellow'))

    def creat_decoder_block(self, tab):
        return decoder_block_tmpl.render(instr_id=self.foundInstr['instruction'].upper(), decode=self.foundInstr['decode'], isEBB=self.foundInstr['isEBB'], tab=tab)

    def handle_execute(self):
        with open(self.path+'src/cpu/execute.gen.cc', 'w', encoding='utf-8') as executeCC:
            executeCC.write(execute_cc_tmpl.render(implInstrSet=self.implDecodedInstrSet))

        with open(self.path+'include/cpu/execute.gen.hh', 'w', encoding='utf-8') as executeHH:
            executeHH.write(execute_hh_tmpl.render(implInstrSet=self.implDecodedInstrSet))

    def handle_enum(self):
        with open(self.path+'include/cpu/enum.gen.hh', 'w', encoding='utf-8') as enumHH:
            enumHH.write(enum_hh_tmpl.render(implInstrSet=self.implDecodedInstrSet))


    def handle_bitfields(self):
        with open(self.path+'generate/arg_lut.csv', 'r') as bitfieldsCSV:
            bitfields = csv.reader(bitfieldsCSV)
            with open(self.path+'include/cpu/bitfields.gen.hh', 'w', encoding='utf-8') as bitfieldsHH:
                bitfieldsHH.write(bitfields_hh_tmpl.render(fields=bitfields))

    def handle_undef_bitfields(self):
        bitfields = []
        with open(self.path+'generate/arg_lut.csv', 'r') as bitfieldsCSV:
            for _ in csv.reader(bitfieldsCSV):
                bitfields.append(_)
        return undef_bitfields_tmpl.render(fields=bitfields)

# if __name__ == '__main__':
#     path=find_simlinx_dir()+'generate/isa/execDecodeRvZicsr.isa.yaml'
#     implInstrSet = parse_yaml(path)

#     for implemInstr in implInstrSet:
#         implemInstr['instruction'] = implemInstr['instruction'][0].upper() + implemInstr['instruction'][1:]

#         implemInstr['unusedCore'] = ''
#         implemInstr['unusedBasedInstr'] = ''

#         if 'core' not in implemInstr['execute']:
#             implemInstr['unusedCore'] = '[[maybe_unused]]'

#         if 'instr' not in implemInstr['execute']:
#             implemInstr['unusedBasedInstr'] = '[[maybe_unused]]'


#     print(execute_cc_tmpl.render(implInstrSet=implInstrSet))

if __name__ == '__main__':
    handler = YamlHandler()
    handler.get_impl_set(['generate/isa/execDecodeRvZicsr.isa.yaml'])
    handler.get_impl_names()
    handler.print_warning()