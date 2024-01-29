import sarakitdevices as sk

#number of motors pole pairs
sk.BLDCMotor_PolePairs(0,11);
sk.BLDCMotor_PolePairs(1,11);

#search for encoder zero position

#run once, get info
sk.BLDCMotor_InitFOC(0,0,0,0)
#exit(0)
#and paste below
#sk.BLDCMotor_InitFOC(0,0,-1,1.268451);

#Attention, BLDC motors get very hot, do not leave them running at too high power - there is a risk of burns and fire!

print('Rotate motor 0 (with encoder) - motor 1 will rotate exactly the same as motor 0')

while 1:
    e0=-sk.Encoder_Get(0).angle
    sk.BLDCMotor_MoveToAngle(1, e0*sk.RAD_TO_DEG, 1, 50, True)
    sk.sleepms(1)


sk.BLDCMotor_MoveStop(0)
