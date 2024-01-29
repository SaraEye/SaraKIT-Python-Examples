import sarakitdevices as sk

sk.Sensors_On(True)

while 1:
    InfoAccGyro=sk.getAccGyro()
    print("Temp: %.1f; AccX: %.2f; AccY: %.2f; AccZ: %.2f; GyroX: %.2f; GyroY: %.2f; GyroZ: %.2f; " % (sk.getTemperature(),InfoAccGyro.accX,InfoAccGyro.accY,InfoAccGyro.accZ,InfoAccGyro.gyroX,InfoAccGyro.gyroY,InfoAccGyro.gyroZ))
    sk.sleepms(50)

