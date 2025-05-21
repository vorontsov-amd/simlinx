<p align="center">
    <img src="https://capsule-render.vercel.app/api?type=waving&height=200&color=0:020024,35:090979,100:00d4ff&text=SIMLINX&fontColor=ffffff&reversal=false&section=header&textBg=false&fontAlignY=36" alt="Description of Image" />
</p>

<p align="center" style="text-align: center;">
    <a href="https://github.com/Naminar/simlinx/actions/workflows/build.yml"><img src="https://github.com/Naminar/simlinx/actions/workflows/build.yml/badge.svg" alt="Build simulator" /></a>
    <a href="https://opensource.org/licenses/MIT"><img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="License MIT" /></a>
    <a href="#"><img src="https://img.shields.io/badge/using-c%2B%2B23-blue" alt="C++23" /></a>
</p>



## Manuals
* [The RISC-V Instruction Set Manual Volume I (Unprivileged Architecture)](https://drive.google.com/file/d/1uviu1nH-tScFfgrovvFCrj7Omv8tFtkp/view)
* [The RISC-V Instruction Set Manual: Volume II (Privileged Architecture)](https://drive.google.com/file/d/17GeetSnT5wW3xNuAHI95-SI1gPGd5sJ_/view)

## Preparing
To set python's environment:
```shell
python3 -m venv .venv

# for fish
source .venv/bin/activate.fish
# for bash .venv/bin/activate 
```

To install python's dependents:
```shell
pip install -r requirements.txt
pip install -e .
```


## Building
Run this command from the root directory of this repository:
```shell
cmake -B build
cmake --build build
```

## Run test
```shell
python3 installTests.py
bash run_tests.sh > run_tests.txt
```

## Some customization as ninja or build in parallel:
```shell
# to install ninja
sudo apt-get update
sudo apt-get install ninja-build cmake

cmake -G Ninja .  -B build # if you want to use your compiler add -DCMAKE_CXX_COMPILER={path_to_compiler}

# if you want to build in parallel:
# for fish
cmake --build build --parallel -j(nproc)
# for bash $(nproc)
```

How to compile bin files for simulation:
```shell
riscv64-linux-gnu-gcc -nostdlib -march=rv64i -mabi=lp64 --static -Wl,-emain riscv-examples/src/fib.cc
riscv64-linux-gnu-objdump -M no-aliases -M numeric -d
```

Gprof usage (use `-pg` key in cmake)
```shell
gprof ./build/bin/simlinx {workload}
gprof ./build/bin/simlinx gmon.out > analysis.txt
```

## Workloads compilation 

Queens workload
```
riscv64-linux-gnu-gcc -nostdl
ib -fno-builtin -fno-lto -ffreestanding -march=rv64i -mabi=lp64 --static -Wl,-emain riscv-
examples/src/queens.c -o queens
```

MMU integration test
```
riscv64-linux-gnu-gcc -nostdlib -fno-builtin -fno-lto -ffreestanding -march=rv64izicsr -mabi=lp64 --static -Wl,-emain riscv-examples/src/mmu.cc  page-table-
api/sv39/sv39.cc  -I./page-table-api/sv39/ -O0 -o mmu
```
