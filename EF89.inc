* EF89 spice model
******************
.subckt pentode1 1 2 3 4 MU=9.98 EX=0.944 KG1=165.6 KG2=4500 KP=38.07 KVB=35.4 VCT=0 RGI=1000 CCG=14p CPG1=0.8p CCP=12p $ A G2 G1 C
.func limpow(x,y) { (x <= 0) ? 0  : 2*PWR(x,y) }
.func plog(x)   { (x <= 0) ? 1u : log(x) }
RE1  7 0  1MEG    $ dummy so node 7 has 2 connections
E1   7 0  value = { v(2,4)/kp*plog(1+exp((1/mu+v(3,4)/v(2,4))*kp)) } $ E1 breaks up long equation for g1.
G1   1 4  value = { limpow(v(7),ex)/kg1*atan(v(1,4)/kvb) }
G2   2 4  value = { (exp(ex*(plog((v(2,4)/mu)+v(3,4)))))/kg2 }
RCP  1 4  1G      $ for convergence	A  - C
C1   3 4  {ccg}   $ cathode-grid 1	C  - G1
C2   1 3  {cpg1}  $ grid 1-plate	G1 - A
C3   1 4  {ccp}   $ cathode-plate	A  - C
R1   3 5  {rgi}   $ for grid current	G1 - 5
D3   5 4  DX      $ for grid current	5  - C
.MODEL DX D(IS=1N RS=1 CJO=10PF TT=1N)
.ends pentode1
******************
.SUBCKT EF89  1 2 3 4 		$ A G2 G1 C (Pentode)
* La Radiotechnique AKA 6DA6
X1 1 2 3 4 PENTODE1 MU=30.52 EX=1.350 KG1=926.7 KG2=4500 KP=39.49 KVB=23.6 VCT=0.00 RGI=2000 CCG=5.5p CPG1=0.0p CCP=5.1p
.ENDS EF89
