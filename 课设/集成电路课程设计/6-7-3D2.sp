.title inv4
.lib 'D:\model\models\PTM 32nm.lib' 32nmcmos_models

.global VDD GND
.data cv
cload
0.0005p
0.005p
0.05p
0.5p
5p
.enddata

.subckt feimen in out GND VDD
mn1 out in GND GND nmos w=0.2u l=32nm
mp1 out in VDD VDD pmos w=0.4u l=32nm
.ends

.subckt chuanshumen in out C1 C2 GND VDD 
mn1 in C2 out GND nmos  w=0.2u l=32nm
mp1 in C1 out VDD pmos  w=0.4u l=32nm
.ends

VDD VDD 0 1
x1 clk e1  GND VDD feimen
x2 e1  e2  GND VDD feimen
x3  D   b  e2  e1 GND VDD chuanshumen
x4  b   g1 GND VDD feimen
x5  g1  g  GND VDD feimen
x6  b   g  e1  e2 GND VDD chuanshumen
x7  g1  f  e1  e2 GND VDD chuanshumen
x8  f   q1 e2  e1 GND VDD chuanshumen
x9  f   q  GND VDD feimen
x10 q   q1 GND VDD feimen
C q GND cload
VIN1  D 0 PULSE(0 1 2n 0.0001n 0.0001n 8n 16n)
VIN2  CLK 0 PULSE(0 1 1n 0.0001n 0.0001n 4n 8n)

.measure T_delay 
+trig v(D)   val=0.5  rise=1
+targ v(q)   val=0.5  rise=1
.measure tran average_VDD_power   AVG  P(X1)   from=0ns to=32ns

.tran 1ns 32ns sweep data=cv
.END