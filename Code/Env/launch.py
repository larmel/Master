#!/usr/bin/env python 

import subprocess

# With shell=True, the environment is PWD=/home/lars/Master/Code/Env
# Without shell, the environment is truly empty
# Default stdin and stdout is inherited from parent process.
#
# perf is adding PERF_BUILDID_DIR and PATH of 96 bytes. Seems pointless to try to avoid this.
# With shell=True, the PWD variable is added as well
#   PERF_BUILDID_DIR=.debug
#   PATH=/home/buildd/libexec/perf-core:/usr/bin:/usr/local/bin:/usr/bin:/bin
# 
if __name__ == '__main__':
    #executable = '/home/lars/Master/Code/Env/a.out'
    #executable = '/usr/bin/perf_3.2.0-40'
    #args = ' '.join([executable, 'stat', '-x,', '-e', 'cycles:u', '/home/lars/Master/Code/Env/a.out']) # shell=True
    #['perf stat -r', str(repeat), '-x","', '-e', e, program, '0>> stat.tmp.dat']
    #temp = '/home/lars/Master/Code/Env/temp'
    with open('output', 'w') as f:
        #command = 'perf stat ./a.out'
        #args = [executable, 'stat', '-x,', '-e', 'cycles:u', '/home/lars/Master/Code/Env/env'] # shell=False
        p = subprocess.Popen('perf stat -e cycles:u ./env', env={}, shell=True)
        #output, errors = p.communicate()
        p.wait()
        #print output, errors

