Build with
cmake -B build -G "Ninja Multi-Config"
cmake --build build --config Release

Copy dll file to GAMS directory and add the record from gamsconfig.yaml to the GAMS config file.

Use with
gams file.gms solvelink=5 cns=aaa
