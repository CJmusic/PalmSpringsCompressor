import soundfile as sf
import matplotlib.pyplot as plt 
import numpy as np

file1 = '440.wav'#'0002 7-Audio.aif'
file2 = '0004 7-Audio.aif'#'440.wav'

INPUT1, fs = sf.read(file1)
INPUT2, fs = sf.read(file2)


OUTPUT=[]
WET = []
THRESHOLD = []


Threshold = -12.0
Ratio = 2.0

Attack = 50.0
Release = 200.0

Gain = 0.0


t_att = 0
t_rel = 0
numSamples = 0
attack = False
wet = 0.0

count = 0
attacks=0
while numSamples < len(INPUT2):
	count += 1

	x_L = INPUT2[numSamples][0]
	x_R = INPUT2[numSamples][1]

	x_LdB = 20.0*np.log10(abs(x_L))
	x_RdB = 20.0*np.log10(abs(x_R))


	if x_LdB > Threshold or x_RdB > Threshold:
		attack = True


	if attack == True:
		if t_att < (Attack/1000.0)*fs:
			t_rel = 0
			t_att += 1
			wet = float(t_att)/((Attack/1000.0)*fs)
		else:
			wet = 1.0
			attack = False


	if attack == False:
		if t_rel < (Release/1000.0)*fs:
			t_att -= 1
			t_rel += 1 
		wet = 1.0 - float(t_rel)/((Release/1000.0)*fs)



	if abs(wet) > 1.0:
		wet = 1.0
		attack = False
		t_att = 0

	if abs(wet) < 0.0: 
		wet = 0.0
		t_rel = 0




	wet_LdB = Threshold + (x_LdB - Threshold)/Ratio
	wet_RdB = Threshold + (x_RdB - Threshold)/Ratio

	dry_LdB = x_LdB
	dry_RdB = x_RdB


	y_L = np.sign(x_L)*10.0**((wet_LdB*wet + dry_LdB*(1.0-wet))/20.0)
	y_R = np.sign(x_R)*10.0**((wet_RdB*wet + dry_RdB*(1.0-wet))/20.0)


	OUTPUT.append(y_L)
	WET.append(wet/2.0)
	THRESHOLD.append(10**(Threshold/20.0))
	# THRESHOLD.append(-10**(Threshold/20.0))

	numSamples += 1


INPUT =[]
for i in xrange(len(INPUT2)):
	INPUT.append(INPUT2[i][0])

THRESHOLD = np.asarray(THRESHOLD)

fig = plt.figure()
ax = fig.add_subplot(1,1,1)
# fig.subplot(2,1,1)
plt.plot(INPUT,'0.75', label = "Input")
plt.plot(OUTPUT, 'k', label = "Output")
plt.plot(WET,'c', label = "Amt of Comp/2")
plt.plot(THRESHOLD,'r', label = "Threshold")
plt.plot(-THRESHOLD,'r')
plt.legend()
# plt.plot(x)
plt.show()
sf.write('440_12_2.wav', OUTPUT ,fs)
