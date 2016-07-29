# Rechord

###### ADC_Controller2 - code for controlling 1 ADC0848 chip with multiplexing. Use this to test individual chips
###### ADC_Controller4 - code for controlling 3 ADC0848 chips with multiplexing. Use this to test 3 chips working in harmony
###### Arduino_Interface2(NOT WORKING) - code for controlling the chips to digitize the signal. This uses interrupts and faster versions of pinMode and digitalWrite/Read to shorten the execution time of each loop cycle which translates to faster sampling time. 

###### Arduino_Interface3 and arduinocomm3 (WORKING!) - arduino and matlab code for controlling 1 ADC0848 chip. Channels 1 and 2 are multiplexed. This is basically the working version of Arduino_Interface2 and is optimized as well. Running time without FFT is almost 1 second.
###### Arduino_Interface4 and arduinocomm4 (WON'T WORK!) - this should control 3 chips but the Arduino Mega 2560 does not have enough space to store 6(strings)*2048(samples)*uint8(data type).

---