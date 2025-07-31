title inv4
.lib 'D:\model\models\PTM 32nm.lib' 32nmcmos_models
V1 1 0 dc=1


.SUBCKT feimen 1 0 in out
Mp0 out in 1 1 pmos W=0.2u L=32n 
Mn0 out in 0 0 nmos W=0.4u L=32n 
.ENDS 

.SUBCKT chuanshumen  1 0 in out clk clk1
mn1 in clk out 0 nmos w=0.2u l=32nm
mp1 in clk1 out 1 pmos  w=0.2u l =32n
.ENDS

X1 1 0 D A C C1 chuanshumen
X2 1 0 A Q1 feimen
X3 1 0 Q1 Q feimen
X4 1 0 A Q C1 C chuanshumen
X5 1 0 CLK C1 feimen
X6 1 0 C1 C feimen

V2 CLK 0 pulse(0 1 0.1u 0.1n 0.1n 1.3u 2.6u) 
V3 D 0 pulse(0 1 0.1u 0.1n 0.1n 0.4u 0.8u)


.probe v(CLK) v(D) v(Q) v(QF)

C1 Q 0 cc
.param cc=0.005p
.data ccdata
cc 0.005p 0.05p 0.5p 5p
.enddata

.measure tran average_vdd_power  
+AVG P(v1) from=0ns to=5u 
.measure D_Q_delay
+trig v(D) val=500mv fall=1
+targ v(Q) val=500mv fall=1  
.tran 0.1n 5u sweep data=ccdata
.end 