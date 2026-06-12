Build with
cmake -B build -G Ninja
cmake --build build

Copy dll file to GAMS directory and add the record from gamsconfig.yaml to the GAMS config file.

Use with
gams file.gms solvelink=5 cns=aaa
