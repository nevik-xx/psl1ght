@echo off
set PS3SDK=C:/ps3sdk
set PATH=%PS3SDK%/host/bin;%PS3SDK%/host/ppu/bin;%PS3SDK%/host/spu/bin;%PS3SDK%/mingw/bin;%PS3SDK%/mingw/msys/1.0/bin;%PS3SDK%/mingw/Python27;%PATH%
set PSL1GHT=%PS3SDK%
set PS3DEV=%PS3SDK%
rem make clean
make 

pause