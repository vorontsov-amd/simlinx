from jinja2 import Template

execute_cc_tmpl = Template("""
  #include "cpu/execute.gen.hh"
  #include "cpu/core.hh"

  namespace simlinx {
    struct Core;
  }

  namespace ISA {
    using reg_t = uint64_t;
    #define rs1 ((curI->rs1))
    #define rs2 ((curI->rs2))
    #define rd ((curI->rd))
    #define csr ((curI->csr))
    #define imm ((curI->imm))

    {% for instruction in implInstrSet %}
    void execute{{ instruction.instruction }}(simlinx::Core &core, BasedInstruction* bbsI, BasedInstruction* curI) {
      {#std::cout << __PRETTY_FUNCTION__ << std::endl;#}
      core.regs[0] = 0;
      {% if instruction.updateCoreState %} 
        core.pc_reg += (curI-bbsI)*sizeof(uint32_t); 
        core.executedI += (curI-bbsI+1); 
      {% endif %}
      {#{% if instruction.isEBB %} core.pc_reg += (curI-bbsI)*sizeof(uint32_t);  {% endif %}#}
      {{ instruction.execute | indent(2)}}
      {#core.dump(); std::cout << std::endl;#}
      {% if not instruction.isEBB %} (curI+1)->exec(core, 
      {% if instruction.updateCoreState %} curI {% else %} bbsI {% endif %}
      , curI+1);{% endif %}
    };
    {% endfor %}
                           
    void executeEbbc(simlinx::Core &core, BasedInstruction* bbsI, BasedInstruction* curI) {
      {#std::cout << __PRETTY_FUNCTION__ << std::endl;#}
      core.pc_reg += (curI-bbsI)*sizeof(uint32_t);
      core.executedI += (curI-bbsI);
    }
    #undef rs1
    #undef rs2
    #undef rd
    #undef csr
    #undef imm
    }
///TODO: must be in instruction.hh or enum.gen.cc
std::array<const char*, {{ implInstrSet|length + 2 }}> InstrNames = 
{ {% for instruction in implInstrSet %}"{{ instruction.instruction }}", {% endfor %}"EBBC", "NONE" };
""")

execute_hh_tmpl = Template("""
  #pragma once
  #include "cpu/fault.hh"
  #include "cpu/instruction.hh"
  #include "syscall/syscall.gen.hh"
  #include "cpu/enum.gen.hh"
  namespace ISA {
    {% for instruction in implInstrSet %}
    void execute{{ instruction.instruction }}(simlinx::Core &core, BasedInstruction* bbsI, BasedInstruction* curI);
    {% endfor %}

    void executeEbbc(simlinx::Core &core, BasedInstruction* bbsI, BasedInstruction* curI);
    {#
    static const std::array<void(*)(simlinx::Core&, BasedInstruction*, BasedInstruction*), {{ implInstrSet|length }}> executeFunctions = { 
    {% for instruction in implInstrSet %}  &execute{{ instruction.instruction }}{{ ", " if not loop.last else ""}}
    {% endfor %}};
    #}
  }
""")

enum_hh_tmpl = Template("""
#pragma once
#include <array>
enum InstrId {
{% for instruction in implInstrSet %}{{ instruction.instruction.upper() }} = {{ loop.index0 }},
{% endfor %} EBBC, //basic block end canary
NONE
};

extern std::array<const char *, {{ implInstrSet|length + 2 }}> InstrNames;                
""")


decoder_block_tmpl = Template(
"""{{' '*tab}}decodedInstr.matchBitsId(decodedBits, InstrId::{{ instr_id }});
// assignements
{{' '*tab}}{{ decode | indent(tab)}} // end assignments

// metainformation
setExec({{'execute'+instr_id[0].upper()+instr_id[1:].lower()}});
{% if isEBB %} decodedInstr.setEBB();{% endif %} //end metainformation

""")

bitfields_hh_tmpl = Template("""
#pragma once
{% for field in fields %}
#define {{ field[0].upper() + ' '*(13 - field[0] | length) }} bitsFrom(decodedBits,{{ "%4s" | format(field[1]) }},{{ "%4s" | format(field[2]) }}){% endfor %}
""")

undef_bitfields_tmpl = Template("""
{% for field in fields %}
#undef {{ field[0].upper() }}{% endfor %}
""")