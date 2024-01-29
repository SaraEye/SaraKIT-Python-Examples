import sarakitdevices as sk

sk.Encoder_On(0,True)

while 1:
    print("Angle in degrees: %.2f" % (sk.Encoder_Get(0).angleDeg))
    sk.sleepms(50)
