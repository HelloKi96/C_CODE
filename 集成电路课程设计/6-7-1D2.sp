.title inv2
.lib 'D:\model\models\PTM 32nm.lib' 32nmcmos_models

.global VDD GND

.subckt feimen IN OUT VDD GND
mn1 OUT IN GND GND nmos w=0.2u l=32n  
mp1 OUT IN VDD VDD pmos w=0.4u l=32n  
.ends

.subckt chuanshumen IN OUT cl cl1 VDD GND
mn1 IN cl OUT GND nmos w=0.2u l=32n  
mp1 IN cl1 OUT VDD pmos w=0.4u l=32n  
.ends
X1 CLK C1 VDD GND feimen
X2 C1 C VDD GND feimen
X3 D B C1 C VDD GND chuanshumen
X4 B Q21 VDD GND feimen
X5 Q21 Q2 VDD GND feimen
X6 B Q2 C C1 VDD GND chuanshumen
X7 Q21 K C C1 VDD GND chuanshumen
X8 K Q VDD GND feimen
X9 Q Q1 VDD GND feimen
X10 K Q1 C1 C VDD GND chuanshumen
c1 Q 0 0.0001p
VDD VDD 0 1
VIN1  D 0 PULSE(0 1 2n 0.0001n 0.0001n 8n 16n)
VIN2  CLK 0 PULSE(0 1 1n 0.0001n 0.0001n 4n 8n)
.tran 1n 32n
.end