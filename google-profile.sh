
env CPUPROFILE_REALTIME=1 CPUPROFILE_FREQUENCY=10000 CPUPROFILE=/tmp/gprofile ./test ../../index/.imgs/3950538.flv/ >/dev/null

env CPUPROFILE_REALTIME=1 CPUPROFILE_FREQUENCY=100000000 CPUPROFILE=/tmp/gprofile ./test ../../index/.imgs/3950538.flv/ >/dev/null
