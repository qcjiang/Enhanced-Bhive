This repository is an improved version of Bhive (https://github.com/ithemal/bhive). The original Bhive version utilized system calls to read PMU counters and generate results, resulting in approximately 300 cycles of BIAS. In this version, we utilized REIGSTER MOVEMENT to perform the same operations, which can effectively remove the BIAS and get a accurate result compared with original Bhive tool.


- Simple Usage Example:
  
cd pmu_open

sudo ./load_module

cd ../

make

./bhive [binary_code] $iterations #for example, ./bive \x61\x68\x62\xfc 100

