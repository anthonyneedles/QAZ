EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title "QAZ Testboard Keys"
Date "2020-09-26"
Rev "v1.0"
Comp "Anthony Needles"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 4650 2400 0    50   Output ~ 0
ROW00
Text HLabel 4650 3300 0    50   Output ~ 0
ROW01
Text HLabel 4650 4200 0    50   Output ~ 0
ROW02
Text HLabel 5150 5200 3    50   Input ~ 0
COL00
Text HLabel 5850 5200 3    50   Input ~ 0
COL01
Text HLabel 6550 5200 3    50   Input ~ 0
COL02
Wire Wire Line
	4850 3100 4850 3200
Wire Wire Line
	4850 4100 4850 4000
$Comp
L Switch:SW_Push SW4
U 1 1 5F315CC3
P 4850 4400
F 0 "SW4" V 4850 4350 50  0000 R CNN
F 1 "Cherry MX" V 4800 4300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 4850 4600 50  0001 C CNN
F 3 "~" H 4850 4600 50  0001 C CNN
	1    4850 4400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4850 5000 4850 4900
Text Notes 4600 4450 0    50   ~ 0
gG
$Comp
L Diode:1N4148 D3
U 1 1 5F315CBD
P 4850 4750
F 0 "D3" V 4950 4650 50  0000 C CNN
F 1 "1N4148" V 4950 4950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4850 4575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 4850 4750 50  0001 C CNN
	1    4850 4750
	0    -1   -1   0   
$EndComp
Text Notes 4600 2650 0    50   ~ 0
aA
$Comp
L Switch:SW_Push SW2
U 1 1 5F30B6DF
P 4850 2600
F 0 "SW2" V 4850 2550 50  0000 R CNN
F 1 "Cherry MX" V 4800 2500 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 4850 2800 50  0001 C CNN
F 3 "~" H 4850 2800 50  0001 C CNN
	1    4850 2600
	0    -1   -1   0   
$EndComp
Text Notes 4600 3550 0    50   ~ 0
dD
$Comp
L Diode:1N4148 D1
U 1 1 5F2DC5D8
P 4850 2950
F 0 "D1" V 4950 2850 50  0000 C CNN
F 1 "1N4148" V 4950 3150 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4850 2775 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 4850 2950 50  0001 C CNN
	1    4850 2950
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D2
U 1 1 5F3117C8
P 4850 3850
F 0 "D2" V 4950 3750 50  0000 C CNN
F 1 "1N4148" V 4950 4050 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4850 3675 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 4850 3850 50  0001 C CNN
	1    4850 3850
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 5F3117CE
P 4850 3500
F 0 "SW3" V 4850 3450 50  0000 R CNN
F 1 "Cherry MX" V 4800 3400 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 4850 3700 50  0001 C CNN
F 3 "~" H 4850 3700 50  0001 C CNN
	1    4850 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4850 3200 5150 3200
Wire Wire Line
	5150 3200 5150 4100
Wire Wire Line
	4850 5000 5150 5000
Wire Wire Line
	4850 4100 5150 4100
Connection ~ 5150 4100
Wire Wire Line
	5150 4100 5150 5000
Wire Wire Line
	5550 3100 5550 3200
Wire Wire Line
	5550 4100 5550 4000
$Comp
L Switch:SW_Push SW7
U 1 1 5F447C77
P 5550 4400
F 0 "SW7" V 5550 4350 50  0000 R CNN
F 1 "Cherry MX" V 5500 4300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 5550 4600 50  0001 C CNN
F 3 "~" H 5550 4600 50  0001 C CNN
	1    5550 4400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5550 5000 5550 4900
Text Notes 5300 4450 0    50   ~ 0
hH
$Comp
L Diode:1N4148 D6
U 1 1 5F447C9D
P 5550 4750
F 0 "D6" V 5650 4650 50  0000 C CNN
F 1 "1N4148" V 5650 4950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5550 4575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5550 4750 50  0001 C CNN
	1    5550 4750
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW5
U 1 1 5F447CA3
P 5550 2600
F 0 "SW5" V 5550 2550 50  0000 R CNN
F 1 "Cherry MX" V 5500 2500 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 5550 2800 50  0001 C CNN
F 3 "~" H 5550 2800 50  0001 C CNN
	1    5550 2600
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D4
U 1 1 5F447CA9
P 5550 2950
F 0 "D4" V 5650 2850 50  0000 C CNN
F 1 "1N4148" V 5650 3150 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5550 2775 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5550 2950 50  0001 C CNN
	1    5550 2950
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D5
U 1 1 5F447CAF
P 5550 3850
F 0 "D5" V 5650 3750 50  0000 C CNN
F 1 "1N4148" V 5650 4050 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5550 3675 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5550 3850 50  0001 C CNN
	1    5550 3850
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW6
U 1 1 5F447CB5
P 5550 3500
F 0 "SW6" V 5550 3450 50  0000 R CNN
F 1 "Cherry MX" V 5500 3400 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 5550 3700 50  0001 C CNN
F 3 "~" H 5550 3700 50  0001 C CNN
	1    5550 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5550 3200 5850 3200
Wire Wire Line
	5850 3200 5850 4100
Wire Wire Line
	5550 5000 5850 5000
Wire Wire Line
	5550 4100 5850 4100
Connection ~ 5850 4100
Wire Wire Line
	5850 4100 5850 5000
Wire Wire Line
	4850 4200 5550 4200
Wire Wire Line
	4850 3300 5550 3300
Wire Wire Line
	4850 2400 5550 2400
Text Notes 5300 3550 0    50   ~ 0
eE
Text Notes 5300 2650 0    50   ~ 0
bB
Wire Wire Line
	6250 3100 6250 3200
Wire Wire Line
	6250 4100 6250 4000
$Comp
L Switch:SW_Push SW10
U 1 1 5F4794A7
P 6250 4400
F 0 "SW10" V 6250 4350 50  0000 R CNN
F 1 "Cherry MX" V 6200 4300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 6250 4600 50  0001 C CNN
F 3 "~" H 6250 4600 50  0001 C CNN
	1    6250 4400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6250 5000 6250 4900
Text Notes 6000 4450 0    50   ~ 0
Fn
$Comp
L Diode:1N4148 D9
U 1 1 5F4794CA
P 6250 4750
F 0 "D9" V 6350 4650 50  0000 C CNN
F 1 "1N4148" V 6350 4950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6250 4575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 6250 4750 50  0001 C CNN
	1    6250 4750
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW8
U 1 1 5F4794D0
P 6250 2600
F 0 "SW8" V 6250 2550 50  0000 R CNN
F 1 "Cherry MX" V 6200 2500 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 6250 2800 50  0001 C CNN
F 3 "~" H 6250 2800 50  0001 C CNN
	1    6250 2600
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D7
U 1 1 5F4794D6
P 6250 2950
F 0 "D7" V 6350 2850 50  0000 C CNN
F 1 "1N4148" V 6350 3150 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6250 2775 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 6250 2950 50  0001 C CNN
	1    6250 2950
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D8
U 1 1 5F4794DC
P 6250 3850
F 0 "D8" V 6350 3750 50  0000 C CNN
F 1 "1N4148" V 6350 4050 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6250 3675 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 6250 3850 50  0001 C CNN
	1    6250 3850
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW9
U 1 1 5F4794E2
P 6250 3500
F 0 "SW9" V 6250 3450 50  0000 R CNN
F 1 "Cherry MX" V 6200 3400 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 6250 3700 50  0001 C CNN
F 3 "~" H 6250 3700 50  0001 C CNN
	1    6250 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6250 3200 6550 3200
Wire Wire Line
	6550 3200 6550 4100
Wire Wire Line
	6250 5000 6550 5000
Wire Wire Line
	6250 4100 6550 4100
Connection ~ 6550 4100
Wire Wire Line
	6550 4100 6550 5000
Wire Wire Line
	5550 4200 6250 4200
Wire Wire Line
	5550 3300 6250 3300
Wire Wire Line
	5550 2400 6250 2400
Text Notes 6000 3550 0    50   ~ 0
fF
Text Notes 5950 2650 0    50   ~ 0
cC
Text Notes 6650 4450 0    50   ~ 0
dD
Text Notes 6650 3550 0    50   ~ 0
eE
Text Notes 6650 2650 0    50   ~ 0
3#
Connection ~ 5550 2400
Connection ~ 5550 3300
Connection ~ 5550 4200
Wire Wire Line
	4850 2400 4650 2400
Connection ~ 4850 2400
Wire Wire Line
	4650 3300 4850 3300
Connection ~ 4850 3300
Wire Wire Line
	4650 4200 4850 4200
Connection ~ 4850 4200
Wire Wire Line
	5150 5000 5150 5200
Wire Wire Line
	6550 5000 6550 5200
Wire Wire Line
	5850 5000 5850 5200
Connection ~ 5150 5000
Connection ~ 5850 5000
Connection ~ 6550 5000
$EndSCHEMATC
