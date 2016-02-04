*realAnalog

V1 vdd 0 3.3
V2 vin 0 1.5
M1 vout vin 0 nch 1 1
M2 vout vin vdd pch 2 1
M3 vout2 vout 0 nch 1 1
M4 vout2 vout vdd pch 2 1
M5 vout3 vout2 0 nch 1 1
M6 vout3 vout2 vdd pch 2 1
C1 vout3 vin2 0.00000001 0
C2 vout 0 0.000001 0
C3 vout2 0 0.000001 0
C4 vout3 0 0.000001 0

.end
