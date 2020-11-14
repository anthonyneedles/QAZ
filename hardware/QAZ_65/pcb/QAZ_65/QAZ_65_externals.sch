EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title "QAZ 65% External"
Date "2020-11-04"
Rev "v1.0"
Comp "Anthony Needles"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+3.3V #PWR?
U 1 1 5F98A26F
P 5800 2650
AR Path="/5F98A26F" Ref="#PWR?"  Part="1" 
AR Path="/5F96C310/5F98A26F" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 5800 2500 50  0001 C CNN
F 1 "+3.3V" H 5800 2800 50  0000 C CNN
F 2 "" H 5800 2650 50  0001 C CNN
F 3 "" H 5800 2650 50  0001 C CNN
	1    5800 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 5F98A28C
P 5700 3550
AR Path="/5F98A28C" Ref="R?"  Part="1" 
AR Path="/5F96C310/5F98A28C" Ref="R16"  Part="1" 
F 0 "R16" H 5900 3500 50  0000 R CNN
F 1 "10k" H 5900 3600 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5700 3550 50  0001 C CNN
F 3 "~" H 5700 3550 50  0001 C CNN
	1    5700 3550
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 5F98A292
P 5600 2750
AR Path="/5F98A292" Ref="R?"  Part="1" 
AR Path="/5F96C310/5F98A292" Ref="R15"  Part="1" 
F 0 "R15" H 5800 2700 50  0000 R CNN
F 1 "10k" H 5800 2800 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5600 2750 50  0001 C CNN
F 3 "~" H 5600 2750 50  0001 C CNN
	1    5600 2750
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F98A299
P 5600 2650
AR Path="/5F98A299" Ref="#PWR?"  Part="1" 
AR Path="/5F96C310/5F98A299" Ref="#PWR033"  Part="1" 
F 0 "#PWR033" H 5600 2500 50  0001 C CNN
F 1 "+3.3V" H 5550 2800 50  0000 C CNN
F 2 "" H 5600 2650 50  0001 C CNN
F 3 "" H 5600 2650 50  0001 C CNN
	1    5600 2650
	1    0    0    -1  
$EndComp
Text Notes 4900 2400 0    50   ~ 0
SWD/Serial Debugger Header
$Comp
L QAZ:USB2.0_TYPE_C CN?
U 1 1 5F98A2C3
P 5400 5550
AR Path="/5F98A2C3" Ref="CN?"  Part="1" 
AR Path="/5F96C310/5F98A2C3" Ref="CN1"  Part="1" 
F 0 "CN1" H 5750 6615 50  0000 C CNN
F 1 "USB2.0_TYPE_C" H 5750 6524 50  0000 C CNN
F 2 "QAZ:USB_C_GCT_USB4085" H 5850 6700 50  0001 C CNN
F 3 "" H 4850 5900 50  0001 C CNN
	1    5400 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5F98A2C9
P 5050 4750
AR Path="/5F98A2C9" Ref="#PWR?"  Part="1" 
AR Path="/5F96C310/5F98A2C9" Ref="#PWR032"  Part="1" 
F 0 "#PWR032" H 5050 4600 50  0001 C CNN
F 1 "+5V" H 5065 4923 50  0000 C CNN
F 2 "" H 5050 4750 50  0001 C CNN
F 3 "" H 5050 4750 50  0001 C CNN
	1    5050 4750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5F98A2D1
P 6450 4750
AR Path="/5F98A2D1" Ref="#PWR?"  Part="1" 
AR Path="/5F96C310/5F98A2D1" Ref="#PWR038"  Part="1" 
F 0 "#PWR038" H 6450 4600 50  0001 C CNN
F 1 "+5V" H 6465 4923 50  0000 C CNN
F 2 "" H 6450 4750 50  0001 C CNN
F 3 "" H 6450 4750 50  0001 C CNN
	1    6450 4750
	1    0    0    -1  
$EndComp
NoConn ~ 6250 5250
NoConn ~ 5250 5250
Wire Wire Line
	5250 5350 5150 5350
Wire Wire Line
	5150 5350 5150 5450
Wire Wire Line
	5150 5450 5250 5450
Wire Wire Line
	5150 5450 5150 5700
Wire Wire Line
	5150 5700 5750 5700
Connection ~ 5150 5450
Wire Wire Line
	6250 5350 6350 5350
Wire Wire Line
	6350 5350 6350 5450
Wire Wire Line
	6350 5700 5750 5700
Connection ~ 5750 5700
Wire Wire Line
	6250 5450 6350 5450
Connection ~ 6350 5450
Wire Wire Line
	6350 5450 6350 5700
$Comp
L power:GND #PWR?
U 1 1 5F98A2F4
P 5750 5700
AR Path="/5F98A2F4" Ref="#PWR?"  Part="1" 
AR Path="/5F96C310/5F98A2F4" Ref="#PWR035"  Part="1" 
F 0 "#PWR035" H 5750 5450 50  0001 C CNN
F 1 "GND" H 5755 5527 50  0001 C CNN
F 2 "" H 5750 5700 50  0001 C CNN
F 3 "" H 5750 5700 50  0001 C CNN
	1    5750 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 5150 4950 5150
$Comp
L Device:R_Small_US R?
U 1 1 5F98A2FB
P 4950 5350
AR Path="/5F98A2FB" Ref="R?"  Part="1" 
AR Path="/5F96C310/5F98A2FB" Ref="R14"  Part="1" 
F 0 "R14" H 5100 5300 50  0000 R CNN
F 1 "5.1k" H 5200 5400 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4950 5350 50  0001 C CNN
F 3 "~" H 4950 5350 50  0001 C CNN
	1    4950 5350
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F98A302
P 4950 5450
AR Path="/5F98A302" Ref="#PWR?"  Part="1" 
AR Path="/5F96C310/5F98A302" Ref="#PWR031"  Part="1" 
F 0 "#PWR031" H 4950 5200 50  0001 C CNN
F 1 "GND" H 4955 5277 50  0001 C CNN
F 2 "" H 4950 5450 50  0001 C CNN
F 3 "" H 4950 5450 50  0001 C CNN
	1    4950 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 5150 6550 5150
$Comp
L Device:R_Small_US R?
U 1 1 5F98A30A
P 6550 5350
AR Path="/5F98A30A" Ref="R?"  Part="1" 
AR Path="/5F96C310/5F98A30A" Ref="R17"  Part="1" 
F 0 "R17" H 6700 5300 50  0000 R CNN
F 1 "5.1k" H 6800 5400 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6550 5350 50  0001 C CNN
F 3 "~" H 6550 5350 50  0001 C CNN
	1    6550 5350
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F98A311
P 6550 5450
AR Path="/5F98A311" Ref="#PWR?"  Part="1" 
AR Path="/5F96C310/5F98A311" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 6550 5200 50  0001 C CNN
F 1 "GND" H 6555 5277 50  0001 C CNN
F 2 "" H 6550 5450 50  0001 C CNN
F 3 "" H 6550 5450 50  0001 C CNN
	1    6550 5450
	-1   0    0    -1  
$EndComp
Text Notes 4650 4350 0    50   ~ 0
USB
Wire Notes Line
	4650 4350 4650 5900
Wire Notes Line
	4650 5900 6850 5900
Wire Notes Line
	4650 4350 6850 4350
Text HLabel 5550 3100 0    50   Input ~ 0
DBG_TX
Text HLabel 5550 3000 0    50   Output ~ 0
SWDIO
Text HLabel 5550 3400 0    50   Output ~ 0
nRESET
Wire Wire Line
	5900 3200 5800 3200
Wire Wire Line
	5900 2900 5700 2900
Text HLabel 5550 2900 0    50   BiDi ~ 0
SWCLK
Wire Notes Line
	6600 3850 4850 3850
Wire Notes Line
	4850 2400 6600 2400
Wire Wire Line
	6250 4950 6450 4950
Wire Wire Line
	6250 5050 6450 5050
Wire Wire Line
	6450 4850 6450 4750
Wire Wire Line
	6250 4850 6450 4850
Wire Wire Line
	6250 4750 6450 4750
Connection ~ 6450 4750
Wire Wire Line
	5250 4750 5050 4750
Wire Wire Line
	5050 4850 5050 4750
Wire Wire Line
	5050 4850 5250 4850
Connection ~ 5050 4750
Wire Wire Line
	6550 5150 6550 5250
Wire Wire Line
	4950 5150 4950 5250
Text HLabel 6450 5050 2    50   BiDi ~ 0
USB_D-
Text HLabel 6450 4950 2    50   BiDi ~ 0
USB_D+
Wire Wire Line
	5250 5050 5050 5050
Wire Wire Line
	5250 4950 5050 4950
Text HLabel 5050 5050 0    50   BiDi ~ 0
USB_D-
Text HLabel 5050 4950 0    50   BiDi ~ 0
USB_D+
Wire Notes Line
	6850 4350 6850 5900
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 603DD2B3
P 6100 3100
F 0 "J1" H 6180 3092 50  0000 L CNN
F 1 "1x6 2.54mm" H 5900 2700 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Horizontal" H 6100 3100 50  0001 C CNN
F 3 "~" H 6100 3100 50  0001 C CNN
	1    6100 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 3300 5800 3300
$Comp
L power:GND #PWR?
U 1 1 603F090B
P 5800 3650
AR Path="/603F090B" Ref="#PWR?"  Part="1" 
AR Path="/5F96C310/603F090B" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 5800 3400 50  0001 C CNN
F 1 "GND" H 5805 3477 50  0001 C CNN
F 2 "" H 5800 3650 50  0001 C CNN
F 3 "" H 5800 3650 50  0001 C CNN
	1    5800 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 603F0CED
P 5700 3650
AR Path="/603F0CED" Ref="#PWR?"  Part="1" 
AR Path="/5F96C310/603F0CED" Ref="#PWR034"  Part="1" 
F 0 "#PWR034" H 5700 3400 50  0001 C CNN
F 1 "GND" H 5705 3477 50  0001 C CNN
F 2 "" H 5700 3650 50  0001 C CNN
F 3 "" H 5700 3650 50  0001 C CNN
	1    5700 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2650 5800 3200
Wire Wire Line
	5700 2900 5700 3450
Wire Wire Line
	5600 2850 5600 3000
Wire Wire Line
	5600 3000 5900 3000
Wire Wire Line
	5800 3300 5800 3650
Wire Wire Line
	5900 3400 5550 3400
Wire Wire Line
	5550 3100 5900 3100
Wire Wire Line
	5600 3000 5550 3000
Connection ~ 5600 3000
Wire Wire Line
	5700 2900 5550 2900
Connection ~ 5700 2900
Wire Notes Line
	6600 2400 6600 3850
Wire Notes Line
	4850 2400 4850 3850
$EndSCHEMATC