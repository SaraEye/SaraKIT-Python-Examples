# sudo apt install python3-alsaaudio

import alsaaudio
import time
import math
import sys
import subprocess

def scale_dBov_to_percentage(power_value, min_dBov=-90, max_dBov=0):
    if power_value==0:
        return 0
    dBov = 10 * math.log10(power_value) - 10 * math.log10(2**30)
    
    if dBov < min_dBov:
        return 0
    elif dBov > max_dBov:
        return 100
    else:
        return (dBov - min_dBov) / (max_dBov - min_dBov) * 100

def display_progress_bar(value, max_value=100, bar_length=50, max_position=None):
    percent = int((value / max_value) * 100)
    fill_length = int(percent * bar_length // 100)
    bar = ''
    for i in range(bar_length):
        if i == max_position:
            bar += '\033[91m|\033[0m'
        elif i < fill_length:
            bar += '#'
        else:
            bar += '-'
    sys.stdout.write(f'\r[{bar}] -{100-percent}dBFS')
    sys.stdout.flush()

# print sound card
for card in alsaaudio.cards():
    print(card)

#Tap-off Points:
# -----                 0x0000 Silence (measurement off)
# SIN_A                 0x0005 Sin1 input
# AEC_IN_A              0x0006 Input to AEC 1
# AEC_OUT_A             0x0008 Output of AEC 1
# SIN_B                 0x0009 Sin2 input
# AEC_IN_B              0x000A Input to AEC 2
# AEC_OUT_B             0x000C Output of AEC 2
# SIN_C                 0x000D Sin3 input
# AEC_IN_C              0x000E Input to AEC 3
# AEC_OUT_C             0x0010 Output of AEC 3
# SOUT2                 0x0016 Sout2 after Beamformer output
# SOUT1                 0x0017 Sout1 before the master bypass point
# RIN_LEFT/RIN_RIGHT    0x0018 Rin_Left/Rin_Right after the Receive High

#AEC_IN_A = 6 (from Mic1)
print("Sin1 input (Mic1)")
subprocess.run(['amixer', '-c0', 'cset', 'name=Power Meter', '6'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

mixin_name = 'Power Meter'
max_value_seen = 0
max_value_time = time.time()
max_position = None

try:
    while True:

        mixin = alsaaudio.Mixer(mixin_name,cardindex=0)
        vol=mixin.getvolume()      
        power_value = vol[0]
        percentage = scale_dBov_to_percentage(power_value)

        if percentage > max_value_seen or time.time() - max_value_time > 2:
            max_value_seen = percentage
            max_value_time = time.time()
            max_position = int((max_value_seen / 100) * 50)
        
        if time.time() - max_value_time <= 2: #1 second
            display_position = max_position
        else:
            display_position = None

        display_progress_bar(percentage, max_value=100, bar_length=50, max_position=display_position)

        time.sleep(0.1)
except KeyboardInterrupt:
    print("\nEnd.")


