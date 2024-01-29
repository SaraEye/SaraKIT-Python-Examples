import sarakitdevices as sk

#number of motor pole pairs
sk.BLDCMotor_PolePairs(0,11);

#When the movement is finished, use 10% of the motor power to maintain the position after 3 seconds
#Attention, BLDC motors get very hot, do not leave them running at too high power - there is a risk of burns and fire!
sk.BLDCMotor_IdleTorque(0, 10, 2500);

sk.BLDCMotor_On(0,True);



print('180 degree rotation of motor 0 to the right')
sk.BLDCMotor_MoveByAngle(0, 180, 1, 40, True)
sk.sleepms(2000)

print('rotation to zero degrees')
sk.BLDCMotor_MoveToAngle(0, 0, 2, 40, True)
sk.sleepms(2000)

print('rotation to 180 degrees')
sk.BLDCMotor_MoveToAngle(0, 180, 2, 40, True)
sk.sleepms(2000)

print('rotation by -10.5 radians')
sk.BLDCMotor_MoveByAngle(0, -10.5, 10, 40, False)
sk.sleepms(2000)

print('continuous movement 5 seconds')
sk.BLDCMotor_MoveContinuousVelocity(0, 1, 40, 20, False)
sk.sleepms(5000)
   
sk.BLDCMotor_MoveStop(0)
