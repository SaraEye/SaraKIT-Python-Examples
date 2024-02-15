import alsaaudio
import time

mixinA_name = 'MasterA'
mixinB_name = 'MasterB'
mixinA = alsaaudio.Mixer(mixinA_name, cardindex=0)
mixinB = alsaaudio.Mixer(mixinB_name, cardindex=0)

# Set new volume value (in percent)
new_volume = 24 # Set the value between 0 and 100

# Apply the new volume value
mixinA.setvolume(new_volume)
mixinB.setvolume(new_volume)

# Read and display the new volume value to confirm the change
current_volume = mixinA.getvolume()
print(f"New volume: {current_volume[0]}%")