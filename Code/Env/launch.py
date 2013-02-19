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
def launch():
    #executable = '/home/lars/Master/Code/Env/a.out'
    executable = '/usr/bin/perf_3.2.0-29' # 37
    #args = ' '.join([executable, 'stat', '-x,', '-e', 'cycles:u', '/home/lars/Master/Code/Env/a.out']) # shell=True
    #['perf stat -r', str(repeat), '-x","', '-e', e, program, '0>> stat.tmp.dat']
    temp = '/home/lars/Master/Code/Env/temp'
    with open('/home/lars/Master/Code/Env/output', 'w') as f:
        #command = 'perf stat ./a.out'
        environment = {}
        args = [executable, 'stat', '-x,', '-e', 'cycles:u', '/home/lars/Master/Code/Env/a.out'] # shell=False
        p = subprocess.Popen(' '.join(args), env=environment, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        output, errors = p.communicate()
        p.wait()
        print output, errors

if __name__ == '__main__':
    launch()

