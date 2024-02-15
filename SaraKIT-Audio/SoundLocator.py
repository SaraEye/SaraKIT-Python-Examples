import alsaaudio
import time
import subprocess

def ReadZL38063(register, firstTime=False):
    if firstTime:
        register &= 0xFFFF
        register = (register << 16) | 0x40000000    
        subprocess.run(['amixer', '-c0', 'cset', 'name=Registers', str(register)], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        
    result = subprocess.run(['amixer', '-c0', 'cget', 'name=Registers'], capture_output=True, text=True)
    output = result.stdout
    last_line = output.strip().split('\n')[-1]
    value = last_line.split('=')[-1] if last_line else None
    return value

def WriteZL38063(register,value):
    register &= 0xFFFF
    value &= 0xFFFF
    register = (register << 16) | value | 0x20000000
    subprocess.run(['amixer', '-c0', 'cset', 'name=Registers', str(register)], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)     
    return 0
    

#define ZL380xx_SND_LOC_DIR_REG 0x00A0
ReadZL38063(0x00A0,True)

while True:
    print("Angle: %s°" % ReadZL38063(0xA0))
    time.sleep(0.1)
