EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title "QAZ 65% Keys"
Date "2021-05-30"
Rev "v1.1"
Comp "Anthony Needles"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 800  1200 0    50   Output ~ 0
ROW00
Text HLabel 800  2100 0    50   Output ~ 0
ROW01
Text HLabel 800  4800 0    50   Output ~ 0
ROW04
Text HLabel 1300 5800 3    50   Input ~ 0
COL00
Text HLabel 2000 5800 3    50   Input ~ 0
COL01
Text HLabel 11100 5800 3    50   Input ~ 0
COL14
Wire Wire Line
	1000 1900 1000 2000
Wire Wire Line
	1000 2900 1000 2800
$Comp
L Switch:SW_Push SW6
U 1 1 5F315CC3
P 1000 5000
AR Path="/5EEB2DAF/5F315CC3" Ref="SW6"  Part="1" 
AR Path="/600F2ED5/5F315CC3" Ref="SW?"  Part="1" 
F 0 "SW6" V 1000 4950 50  0000 R CNN
F 1 "Cherry MX" V 950 4900 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.25u_PCB" H 1000 5200 50  0001 C CNN
F 3 "~" H 1000 5200 50  0001 C CNN
	1    1000 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1000 5600 1000 5500
Text Notes 850  5050 2    50   ~ 0
LCTRL
$Comp
L Diode:1N4148 D8
U 1 1 5F315CBD
P 1000 5350
AR Path="/5EEB2DAF/5F315CBD" Ref="D8"  Part="1" 
AR Path="/600F2ED5/5F315CBD" Ref="D?"  Part="1" 
F 0 "D8" V 1100 5250 50  0000 C CNN
F 1 "1N4148" V 1100 5550 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1000 5175 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1000 5350 50  0001 C CNN
	1    1000 5350
	0    -1   -1   0   
$EndComp
Text Notes 850  1450 2    50   ~ 0
ESC
$Comp
L Switch:SW_Push SW2
U 1 1 5F30B6DF
P 1000 1400
AR Path="/5EEB2DAF/5F30B6DF" Ref="SW2"  Part="1" 
AR Path="/600F2ED5/5F30B6DF" Ref="SW?"  Part="1" 
F 0 "SW2" V 1000 1350 50  0000 R CNN
F 1 "Cherry MX" V 950 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 1000 1600 50  0001 C CNN
F 3 "~" H 1000 1600 50  0001 C CNN
	1    1000 1400
	0    -1   -1   0   
$EndComp
Text Notes 850  2350 2    50   ~ 0
TAB
$Comp
L Diode:1N4148 D4
U 1 1 5F2DC5D8
P 1000 1750
AR Path="/5EEB2DAF/5F2DC5D8" Ref="D4"  Part="1" 
AR Path="/600F2ED5/5F2DC5D8" Ref="D?"  Part="1" 
F 0 "D4" V 1100 1650 50  0000 C CNN
F 1 "1N4148" V 1100 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1000 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1000 1750 50  0001 C CNN
	1    1000 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D5
U 1 1 5F3117C8
P 1000 2650
AR Path="/5EEB2DAF/5F3117C8" Ref="D5"  Part="1" 
AR Path="/600F2ED5/5F3117C8" Ref="D?"  Part="1" 
F 0 "D5" V 1100 2550 50  0000 C CNN
F 1 "1N4148" V 1100 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1000 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1000 2650 50  0001 C CNN
	1    1000 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 5F3117CE
P 1000 2300
AR Path="/5EEB2DAF/5F3117CE" Ref="SW3"  Part="1" 
AR Path="/600F2ED5/5F3117CE" Ref="SW?"  Part="1" 
F 0 "SW3" V 1000 2250 50  0000 R CNN
F 1 "Cherry MX" V 950 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.50u_PCB" H 1000 2500 50  0001 C CNN
F 3 "~" H 1000 2500 50  0001 C CNN
	1    1000 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1000 2000 1300 2000
Wire Wire Line
	1300 2000 1300 2900
Wire Wire Line
	1000 5600 1300 5600
Wire Wire Line
	1000 2900 1300 2900
Wire Wire Line
	1300 4700 1300 5600
Wire Wire Line
	1700 1900 1700 2000
Wire Wire Line
	1700 2900 1700 2800
$Comp
L Switch:SW_Push SW11
U 1 1 5F447C77
P 1700 5000
AR Path="/5EEB2DAF/5F447C77" Ref="SW11"  Part="1" 
AR Path="/600F2ED5/5F447C77" Ref="SW?"  Part="1" 
F 0 "SW11" V 1700 4950 50  0000 R CNN
F 1 "Cherry MX" V 1650 4900 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.25u_PCB" H 1700 5200 50  0001 C CNN
F 3 "~" H 1700 5200 50  0001 C CNN
	1    1700 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1700 5600 1700 5500
$Comp
L Diode:1N4148 D13
U 1 1 5F447C9D
P 1700 5350
AR Path="/5EEB2DAF/5F447C9D" Ref="D13"  Part="1" 
AR Path="/600F2ED5/5F447C9D" Ref="D?"  Part="1" 
F 0 "D13" V 1800 5250 50  0000 C CNN
F 1 "1N4148" V 1800 5550 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1700 5175 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1700 5350 50  0001 C CNN
	1    1700 5350
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW7
U 1 1 5F447CA3
P 1700 1400
AR Path="/5EEB2DAF/5F447CA3" Ref="SW7"  Part="1" 
AR Path="/600F2ED5/5F447CA3" Ref="SW?"  Part="1" 
F 0 "SW7" V 1700 1350 50  0000 R CNN
F 1 "Cherry MX" V 1650 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 1700 1600 50  0001 C CNN
F 3 "~" H 1700 1600 50  0001 C CNN
	1    1700 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D9
U 1 1 5F447CA9
P 1700 1750
AR Path="/5EEB2DAF/5F447CA9" Ref="D9"  Part="1" 
AR Path="/600F2ED5/5F447CA9" Ref="D?"  Part="1" 
F 0 "D9" V 1800 1650 50  0000 C CNN
F 1 "1N4148" V 1800 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1700 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1700 1750 50  0001 C CNN
	1    1700 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D10
U 1 1 5F447CAF
P 1700 2650
AR Path="/5EEB2DAF/5F447CAF" Ref="D10"  Part="1" 
AR Path="/600F2ED5/5F447CAF" Ref="D?"  Part="1" 
F 0 "D10" V 1800 2550 50  0000 C CNN
F 1 "1N4148" V 1800 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1700 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1700 2650 50  0001 C CNN
	1    1700 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW8
U 1 1 5F447CB5
P 1700 2300
AR Path="/5EEB2DAF/5F447CB5" Ref="SW8"  Part="1" 
AR Path="/600F2ED5/5F447CB5" Ref="SW?"  Part="1" 
F 0 "SW8" V 1700 2250 50  0000 R CNN
F 1 "Cherry MX" V 1650 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 1700 2500 50  0001 C CNN
F 3 "~" H 1700 2500 50  0001 C CNN
	1    1700 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1700 2000 2000 2000
Wire Wire Line
	2000 2000 2000 2900
Wire Wire Line
	1700 5600 2000 5600
Wire Wire Line
	1700 2900 2000 2900
Wire Wire Line
	2000 4700 2000 5600
Wire Wire Line
	1000 4800 1700 4800
Wire Wire Line
	1000 2100 1700 2100
Wire Wire Line
	1000 1200 1700 1200
Wire Wire Line
	10800 1900 10800 2000
Wire Wire Line
	10800 2900 10800 2800
$Comp
L Switch:SW_Push SW69
U 1 1 5F4794A7
P 10800 5000
AR Path="/5EEB2DAF/5F4794A7" Ref="SW69"  Part="1" 
AR Path="/600F2ED5/5F4794A7" Ref="SW?"  Part="1" 
F 0 "SW69" V 10800 4950 50  0000 R CNN
F 1 "Cherry MX" V 10750 4900 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 10800 5200 50  0001 C CNN
F 3 "~" H 10800 5200 50  0001 C CNN
	1    10800 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10800 5600 10800 5500
$Comp
L Diode:1N4148 D71
U 1 1 5F4794CA
P 10800 5350
AR Path="/5EEB2DAF/5F4794CA" Ref="D71"  Part="1" 
AR Path="/600F2ED5/5F4794CA" Ref="D?"  Part="1" 
F 0 "D71" V 10900 5250 50  0000 C CNN
F 1 "1N4148" V 10900 5550 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 10800 5175 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 10800 5350 50  0001 C CNN
	1    10800 5350
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW65
U 1 1 5F4794D0
P 10800 1400
AR Path="/5EEB2DAF/5F4794D0" Ref="SW65"  Part="1" 
AR Path="/600F2ED5/5F4794D0" Ref="SW?"  Part="1" 
F 0 "SW65" V 10800 1350 50  0000 R CNN
F 1 "Cherry MX" V 10750 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 10800 1600 50  0001 C CNN
F 3 "~" H 10800 1600 50  0001 C CNN
	1    10800 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D67
U 1 1 5F4794D6
P 10800 1750
AR Path="/5EEB2DAF/5F4794D6" Ref="D67"  Part="1" 
AR Path="/600F2ED5/5F4794D6" Ref="D?"  Part="1" 
F 0 "D67" V 10900 1650 50  0000 C CNN
F 1 "1N4148" V 10900 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 10800 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 10800 1750 50  0001 C CNN
	1    10800 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D68
U 1 1 5F4794DC
P 10800 2650
AR Path="/5EEB2DAF/5F4794DC" Ref="D68"  Part="1" 
AR Path="/600F2ED5/5F4794DC" Ref="D?"  Part="1" 
F 0 "D68" V 10900 2550 50  0000 C CNN
F 1 "1N4148" V 10900 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 10800 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 10800 2650 50  0001 C CNN
	1    10800 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW66
U 1 1 5F4794E2
P 10800 2300
AR Path="/5EEB2DAF/5F4794E2" Ref="SW66"  Part="1" 
AR Path="/600F2ED5/5F4794E2" Ref="SW?"  Part="1" 
F 0 "SW66" V 10800 2250 50  0000 R CNN
F 1 "Cherry MX" V 10750 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 10800 2500 50  0001 C CNN
F 3 "~" H 10800 2500 50  0001 C CNN
	1    10800 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10800 2000 11100 2000
Wire Wire Line
	11100 2000 11100 2900
Wire Wire Line
	10800 5600 11100 5600
Wire Wire Line
	10800 2900 11100 2900
Wire Wire Line
	11100 4700 11100 5600
Wire Wire Line
	10100 4800 10800 4800
Wire Wire Line
	10100 2100 10800 2100
Wire Wire Line
	10100 1200 10800 1200
Wire Wire Line
	1000 1200 800  1200
Connection ~ 1000 1200
Wire Wire Line
	800  2100 1000 2100
Connection ~ 1000 2100
Wire Wire Line
	800  4800 1000 4800
Connection ~ 1000 4800
Wire Wire Line
	1300 5600 1300 5800
Wire Wire Line
	11100 5600 11100 5800
Wire Wire Line
	2000 5600 2000 5800
Connection ~ 1300 5600
Connection ~ 2000 5600
Connection ~ 11100 5600
Connection ~ 1700 2100
Connection ~ 1700 4800
Connection ~ 1700 1200
Text HLabel 2700 5800 3    50   Input ~ 0
COL02
Wire Wire Line
	2400 1900 2400 2000
Wire Wire Line
	2400 2900 2400 2800
$Comp
L Switch:SW_Push SW16
U 1 1 5FC5760A
P 2400 5000
AR Path="/5EEB2DAF/5FC5760A" Ref="SW16"  Part="1" 
AR Path="/600F2ED5/5FC5760A" Ref="SW?"  Part="1" 
F 0 "SW16" V 2400 4950 50  0000 R CNN
F 1 "Cherry MX" V 2350 4900 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.25u_PCB" H 2400 5200 50  0001 C CNN
F 3 "~" H 2400 5200 50  0001 C CNN
	1    2400 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2400 5600 2400 5500
$Comp
L Diode:1N4148 D18
U 1 1 5FC57612
P 2400 5350
AR Path="/5EEB2DAF/5FC57612" Ref="D18"  Part="1" 
AR Path="/600F2ED5/5FC57612" Ref="D?"  Part="1" 
F 0 "D18" V 2500 5250 50  0000 C CNN
F 1 "1N4148" V 2500 5550 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 2400 5175 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 2400 5350 50  0001 C CNN
	1    2400 5350
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW12
U 1 1 5FC57618
P 2400 1400
AR Path="/5EEB2DAF/5FC57618" Ref="SW12"  Part="1" 
AR Path="/600F2ED5/5FC57618" Ref="SW?"  Part="1" 
F 0 "SW12" V 2400 1350 50  0000 R CNN
F 1 "Cherry MX" V 2350 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 2400 1600 50  0001 C CNN
F 3 "~" H 2400 1600 50  0001 C CNN
	1    2400 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D14
U 1 1 5FC5761E
P 2400 1750
AR Path="/5EEB2DAF/5FC5761E" Ref="D14"  Part="1" 
AR Path="/600F2ED5/5FC5761E" Ref="D?"  Part="1" 
F 0 "D14" V 2500 1650 50  0000 C CNN
F 1 "1N4148" V 2500 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 2400 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 2400 1750 50  0001 C CNN
	1    2400 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D15
U 1 1 5FC57624
P 2400 2650
AR Path="/5EEB2DAF/5FC57624" Ref="D15"  Part="1" 
AR Path="/600F2ED5/5FC57624" Ref="D?"  Part="1" 
F 0 "D15" V 2500 2550 50  0000 C CNN
F 1 "1N4148" V 2500 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 2400 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 2400 2650 50  0001 C CNN
	1    2400 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW13
U 1 1 5FC5762A
P 2400 2300
AR Path="/5EEB2DAF/5FC5762A" Ref="SW13"  Part="1" 
AR Path="/600F2ED5/5FC5762A" Ref="SW?"  Part="1" 
F 0 "SW13" V 2400 2250 50  0000 R CNN
F 1 "Cherry MX" V 2350 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 2400 2500 50  0001 C CNN
F 3 "~" H 2400 2500 50  0001 C CNN
	1    2400 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2400 2000 2700 2000
Wire Wire Line
	2700 2000 2700 2900
Wire Wire Line
	2400 5600 2700 5600
Wire Wire Line
	2700 4700 2700 5600
Wire Wire Line
	1700 4800 2400 4800
Wire Wire Line
	1700 2100 2400 2100
Wire Wire Line
	1700 1200 2400 1200
Wire Wire Line
	2700 5600 2700 5800
Connection ~ 2700 5600
Connection ~ 2400 4800
Connection ~ 2400 2100
Connection ~ 2400 1200
Text HLabel 3400 5800 3    50   Input ~ 0
COL03
Wire Wire Line
	3100 1900 3100 2000
Wire Wire Line
	3100 2900 3100 2800
$Comp
L Switch:SW_Push SW17
U 1 1 5FC60232
P 3100 1400
AR Path="/5EEB2DAF/5FC60232" Ref="SW17"  Part="1" 
AR Path="/600F2ED5/5FC60232" Ref="SW?"  Part="1" 
F 0 "SW17" V 3100 1350 50  0000 R CNN
F 1 "Cherry MX" V 3050 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 3100 1600 50  0001 C CNN
F 3 "~" H 3100 1600 50  0001 C CNN
	1    3100 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D19
U 1 1 5FC60238
P 3100 1750
AR Path="/5EEB2DAF/5FC60238" Ref="D19"  Part="1" 
AR Path="/600F2ED5/5FC60238" Ref="D?"  Part="1" 
F 0 "D19" V 3200 1650 50  0000 C CNN
F 1 "1N4148" V 3200 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3100 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 3100 1750 50  0001 C CNN
	1    3100 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D20
U 1 1 5FC6023E
P 3100 2650
AR Path="/5EEB2DAF/5FC6023E" Ref="D20"  Part="1" 
AR Path="/600F2ED5/5FC6023E" Ref="D?"  Part="1" 
F 0 "D20" V 3200 2550 50  0000 C CNN
F 1 "1N4148" V 3200 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3100 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 3100 2650 50  0001 C CNN
	1    3100 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW18
U 1 1 5FC60244
P 3100 2300
AR Path="/5EEB2DAF/5FC60244" Ref="SW18"  Part="1" 
AR Path="/600F2ED5/5FC60244" Ref="SW?"  Part="1" 
F 0 "SW18" V 3100 2250 50  0000 R CNN
F 1 "Cherry MX" V 3050 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 3100 2500 50  0001 C CNN
F 3 "~" H 3100 2500 50  0001 C CNN
	1    3100 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 2000 3400 2000
Wire Wire Line
	3400 2000 3400 2900
Wire Wire Line
	3100 2900 3400 2900
Wire Wire Line
	2400 2100 3100 2100
Wire Wire Line
	2400 1200 3100 1200
Connection ~ 3100 1200
Connection ~ 3100 2100
Text HLabel 4100 5800 3    50   Input ~ 0
COL04
Wire Wire Line
	3800 1900 3800 2000
Wire Wire Line
	3800 2900 3800 2800
$Comp
L Switch:SW_Push SW21
U 1 1 5FC66C14
P 3800 1400
AR Path="/5EEB2DAF/5FC66C14" Ref="SW21"  Part="1" 
AR Path="/600F2ED5/5FC66C14" Ref="SW?"  Part="1" 
F 0 "SW21" V 3800 1350 50  0000 R CNN
F 1 "Cherry MX" V 3750 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 3800 1600 50  0001 C CNN
F 3 "~" H 3800 1600 50  0001 C CNN
	1    3800 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D23
U 1 1 5FC66C1A
P 3800 1750
AR Path="/5EEB2DAF/5FC66C1A" Ref="D23"  Part="1" 
AR Path="/600F2ED5/5FC66C1A" Ref="D?"  Part="1" 
F 0 "D23" V 3900 1650 50  0000 C CNN
F 1 "1N4148" V 3900 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3800 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 3800 1750 50  0001 C CNN
	1    3800 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D24
U 1 1 5FC66C20
P 3800 2650
AR Path="/5EEB2DAF/5FC66C20" Ref="D24"  Part="1" 
AR Path="/600F2ED5/5FC66C20" Ref="D?"  Part="1" 
F 0 "D24" V 3900 2550 50  0000 C CNN
F 1 "1N4148" V 3900 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3800 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 3800 2650 50  0001 C CNN
	1    3800 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW22
U 1 1 5FC66C26
P 3800 2300
AR Path="/5EEB2DAF/5FC66C26" Ref="SW22"  Part="1" 
AR Path="/600F2ED5/5FC66C26" Ref="SW?"  Part="1" 
F 0 "SW22" V 3800 2250 50  0000 R CNN
F 1 "Cherry MX" V 3750 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 3800 2500 50  0001 C CNN
F 3 "~" H 3800 2500 50  0001 C CNN
	1    3800 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3800 2000 4100 2000
Wire Wire Line
	4100 2000 4100 2900
Wire Wire Line
	3800 2900 4100 2900
Wire Wire Line
	3100 2100 3800 2100
Wire Wire Line
	3100 1200 3800 1200
Connection ~ 3800 2100
Connection ~ 3800 1200
Text HLabel 4800 5800 3    50   Input ~ 0
COL05
Wire Wire Line
	4500 1900 4500 2000
Wire Wire Line
	4500 2900 4500 2800
$Comp
L Switch:SW_Push SW29
U 1 1 5FC6B7CA
P 4500 5000
AR Path="/5EEB2DAF/5FC6B7CA" Ref="SW29"  Part="1" 
AR Path="/600F2ED5/5FC6B7CA" Ref="SW?"  Part="1" 
F 0 "SW29" V 4500 4950 50  0000 R CNN
F 1 "Cherry MX" V 4450 4900 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_6.25u_PCB" H 4500 5200 50  0001 C CNN
F 3 "~" H 4500 5200 50  0001 C CNN
	1    4500 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4500 5600 4500 5500
$Comp
L Diode:1N4148 D31
U 1 1 5FC6B7D1
P 4500 5350
AR Path="/5EEB2DAF/5FC6B7D1" Ref="D31"  Part="1" 
AR Path="/600F2ED5/5FC6B7D1" Ref="D?"  Part="1" 
F 0 "D31" V 4600 5250 50  0000 C CNN
F 1 "1N4148" V 4600 5550 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4500 5175 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 4500 5350 50  0001 C CNN
	1    4500 5350
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW25
U 1 1 5FC6B7D7
P 4500 1400
AR Path="/5EEB2DAF/5FC6B7D7" Ref="SW25"  Part="1" 
AR Path="/600F2ED5/5FC6B7D7" Ref="SW?"  Part="1" 
F 0 "SW25" V 4500 1350 50  0000 R CNN
F 1 "Cherry MX" V 4450 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 4500 1600 50  0001 C CNN
F 3 "~" H 4500 1600 50  0001 C CNN
	1    4500 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D27
U 1 1 5FC6B7DD
P 4500 1750
AR Path="/5EEB2DAF/5FC6B7DD" Ref="D27"  Part="1" 
AR Path="/600F2ED5/5FC6B7DD" Ref="D?"  Part="1" 
F 0 "D27" V 4600 1650 50  0000 C CNN
F 1 "1N4148" V 4600 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4500 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 4500 1750 50  0001 C CNN
	1    4500 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D28
U 1 1 5FC6B7E3
P 4500 2650
AR Path="/5EEB2DAF/5FC6B7E3" Ref="D28"  Part="1" 
AR Path="/600F2ED5/5FC6B7E3" Ref="D?"  Part="1" 
F 0 "D28" V 4600 2550 50  0000 C CNN
F 1 "1N4148" V 4600 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4500 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 4500 2650 50  0001 C CNN
	1    4500 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW26
U 1 1 5FC6B7E9
P 4500 2300
AR Path="/5EEB2DAF/5FC6B7E9" Ref="SW26"  Part="1" 
AR Path="/600F2ED5/5FC6B7E9" Ref="SW?"  Part="1" 
F 0 "SW26" V 4500 2250 50  0000 R CNN
F 1 "Cherry MX" V 4450 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 4500 2500 50  0001 C CNN
F 3 "~" H 4500 2500 50  0001 C CNN
	1    4500 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4500 2000 4800 2000
Wire Wire Line
	4800 2000 4800 2900
Wire Wire Line
	4500 5600 4800 5600
Wire Wire Line
	4500 2900 4800 2900
Wire Wire Line
	4800 4700 4800 5600
Wire Wire Line
	3800 2100 4500 2100
Wire Wire Line
	3800 1200 4500 1200
Wire Wire Line
	4800 5600 4800 5800
Connection ~ 4800 5600
Connection ~ 4500 2100
Connection ~ 4500 1200
Text HLabel 5500 5800 3    50   Input ~ 0
COL06
Wire Wire Line
	5200 1900 5200 2000
Wire Wire Line
	5200 2900 5200 2800
$Comp
L Switch:SW_Push SW30
U 1 1 5FC74678
P 5200 1400
AR Path="/5EEB2DAF/5FC74678" Ref="SW30"  Part="1" 
AR Path="/600F2ED5/5FC74678" Ref="SW?"  Part="1" 
F 0 "SW30" V 5200 1350 50  0000 R CNN
F 1 "Cherry MX" V 5150 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 5200 1600 50  0001 C CNN
F 3 "~" H 5200 1600 50  0001 C CNN
	1    5200 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D32
U 1 1 5FC7467E
P 5200 1750
AR Path="/5EEB2DAF/5FC7467E" Ref="D32"  Part="1" 
AR Path="/600F2ED5/5FC7467E" Ref="D?"  Part="1" 
F 0 "D32" V 5300 1650 50  0000 C CNN
F 1 "1N4148" V 5300 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5200 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5200 1750 50  0001 C CNN
	1    5200 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D33
U 1 1 5FC74684
P 5200 2650
AR Path="/5EEB2DAF/5FC74684" Ref="D33"  Part="1" 
AR Path="/600F2ED5/5FC74684" Ref="D?"  Part="1" 
F 0 "D33" V 5300 2550 50  0000 C CNN
F 1 "1N4148" V 5300 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5200 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5200 2650 50  0001 C CNN
	1    5200 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW31
U 1 1 5FC7468A
P 5200 2300
AR Path="/5EEB2DAF/5FC7468A" Ref="SW31"  Part="1" 
AR Path="/600F2ED5/5FC7468A" Ref="SW?"  Part="1" 
F 0 "SW31" V 5200 2250 50  0000 R CNN
F 1 "Cherry MX" V 5150 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 5200 2500 50  0001 C CNN
F 3 "~" H 5200 2500 50  0001 C CNN
	1    5200 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5200 2000 5500 2000
Wire Wire Line
	5500 2000 5500 2900
Wire Wire Line
	5200 2900 5500 2900
Wire Wire Line
	4500 2100 5200 2100
Wire Wire Line
	4500 1200 5200 1200
Connection ~ 5200 2100
Connection ~ 5200 1200
Text HLabel 6200 5800 3    50   Input ~ 0
COL07
Wire Wire Line
	5900 1900 5900 2000
Wire Wire Line
	5900 2900 5900 2800
$Comp
L Switch:SW_Push SW34
U 1 1 5FC7AB73
P 5900 1400
AR Path="/5EEB2DAF/5FC7AB73" Ref="SW34"  Part="1" 
AR Path="/600F2ED5/5FC7AB73" Ref="SW?"  Part="1" 
F 0 "SW34" V 5900 1350 50  0000 R CNN
F 1 "Cherry MX" V 5850 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 5900 1600 50  0001 C CNN
F 3 "~" H 5900 1600 50  0001 C CNN
	1    5900 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D36
U 1 1 5FC7AB79
P 5900 1750
AR Path="/5EEB2DAF/5FC7AB79" Ref="D36"  Part="1" 
AR Path="/600F2ED5/5FC7AB79" Ref="D?"  Part="1" 
F 0 "D36" V 6000 1650 50  0000 C CNN
F 1 "1N4148" V 6000 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5900 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5900 1750 50  0001 C CNN
	1    5900 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D37
U 1 1 5FC7AB7F
P 5900 2650
AR Path="/5EEB2DAF/5FC7AB7F" Ref="D37"  Part="1" 
AR Path="/600F2ED5/5FC7AB7F" Ref="D?"  Part="1" 
F 0 "D37" V 6000 2550 50  0000 C CNN
F 1 "1N4148" V 6000 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5900 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5900 2650 50  0001 C CNN
	1    5900 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW35
U 1 1 5FC7AB85
P 5900 2300
AR Path="/5EEB2DAF/5FC7AB85" Ref="SW35"  Part="1" 
AR Path="/600F2ED5/5FC7AB85" Ref="SW?"  Part="1" 
F 0 "SW35" V 5900 2250 50  0000 R CNN
F 1 "Cherry MX" V 5850 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 5900 2500 50  0001 C CNN
F 3 "~" H 5900 2500 50  0001 C CNN
	1    5900 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5900 2000 6200 2000
Wire Wire Line
	6200 2000 6200 2900
Wire Wire Line
	5900 2900 6200 2900
Wire Wire Line
	5200 2100 5900 2100
Wire Wire Line
	5200 1200 5900 1200
Connection ~ 5900 2100
Connection ~ 5900 1200
Text HLabel 6900 5800 3    50   Input ~ 0
COL08
Wire Wire Line
	6600 1900 6600 2000
Wire Wire Line
	6600 2900 6600 2800
$Comp
L Switch:SW_Push SW42
U 1 1 5FC82A1D
P 6600 5000
AR Path="/5EEB2DAF/5FC82A1D" Ref="SW42"  Part="1" 
AR Path="/600F2ED5/5FC82A1D" Ref="SW?"  Part="1" 
F 0 "SW42" V 6600 4950 50  0000 R CNN
F 1 "Cherry MX" V 6550 4900 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 6600 5200 50  0001 C CNN
F 3 "~" H 6600 5200 50  0001 C CNN
	1    6600 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6600 5600 6600 5500
$Comp
L Diode:1N4148 D44
U 1 1 5FC82A24
P 6600 5350
AR Path="/5EEB2DAF/5FC82A24" Ref="D44"  Part="1" 
AR Path="/600F2ED5/5FC82A24" Ref="D?"  Part="1" 
F 0 "D44" V 6700 5250 50  0000 C CNN
F 1 "1N4148" V 6700 5550 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6600 5175 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 6600 5350 50  0001 C CNN
	1    6600 5350
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW38
U 1 1 5FC82A2A
P 6600 1400
AR Path="/5EEB2DAF/5FC82A2A" Ref="SW38"  Part="1" 
AR Path="/600F2ED5/5FC82A2A" Ref="SW?"  Part="1" 
F 0 "SW38" V 6600 1350 50  0000 R CNN
F 1 "Cherry MX" V 6550 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 6600 1600 50  0001 C CNN
F 3 "~" H 6600 1600 50  0001 C CNN
	1    6600 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D40
U 1 1 5FC82A30
P 6600 1750
AR Path="/5EEB2DAF/5FC82A30" Ref="D40"  Part="1" 
AR Path="/600F2ED5/5FC82A30" Ref="D?"  Part="1" 
F 0 "D40" V 6700 1650 50  0000 C CNN
F 1 "1N4148" V 6700 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6600 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 6600 1750 50  0001 C CNN
	1    6600 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D41
U 1 1 5FC82A36
P 6600 2650
AR Path="/5EEB2DAF/5FC82A36" Ref="D41"  Part="1" 
AR Path="/600F2ED5/5FC82A36" Ref="D?"  Part="1" 
F 0 "D41" V 6700 2550 50  0000 C CNN
F 1 "1N4148" V 6700 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6600 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 6600 2650 50  0001 C CNN
	1    6600 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW39
U 1 1 5FC82A3C
P 6600 2300
AR Path="/5EEB2DAF/5FC82A3C" Ref="SW39"  Part="1" 
AR Path="/600F2ED5/5FC82A3C" Ref="SW?"  Part="1" 
F 0 "SW39" V 6600 2250 50  0000 R CNN
F 1 "Cherry MX" V 6550 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 6600 2500 50  0001 C CNN
F 3 "~" H 6600 2500 50  0001 C CNN
	1    6600 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6600 2000 6900 2000
Wire Wire Line
	6900 2000 6900 2900
Wire Wire Line
	6600 5600 6900 5600
Wire Wire Line
	6600 2900 6900 2900
Wire Wire Line
	6900 4700 6900 5600
Wire Wire Line
	5900 2100 6600 2100
Wire Wire Line
	5900 1200 6600 1200
Wire Wire Line
	6900 5600 6900 5800
Connection ~ 6900 5600
Connection ~ 6600 4800
Connection ~ 6600 2100
Connection ~ 6600 1200
Text HLabel 7600 5800 3    50   Input ~ 0
COL09
Wire Wire Line
	7300 1900 7300 2000
Wire Wire Line
	7300 2900 7300 2800
$Comp
L Switch:SW_Push SW47
U 1 1 5FC89A0A
P 7300 5000
AR Path="/5EEB2DAF/5FC89A0A" Ref="SW47"  Part="1" 
AR Path="/600F2ED5/5FC89A0A" Ref="SW?"  Part="1" 
F 0 "SW47" V 7300 4950 50  0000 R CNN
F 1 "Cherry MX" V 7250 4900 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 7300 5200 50  0001 C CNN
F 3 "~" H 7300 5200 50  0001 C CNN
	1    7300 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7300 5600 7300 5500
$Comp
L Diode:1N4148 D49
U 1 1 5FC89A11
P 7300 5350
AR Path="/5EEB2DAF/5FC89A11" Ref="D49"  Part="1" 
AR Path="/600F2ED5/5FC89A11" Ref="D?"  Part="1" 
F 0 "D49" V 7400 5250 50  0000 C CNN
F 1 "1N4148" V 7400 5550 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 7300 5175 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 7300 5350 50  0001 C CNN
	1    7300 5350
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW43
U 1 1 5FC89A17
P 7300 1400
AR Path="/5EEB2DAF/5FC89A17" Ref="SW43"  Part="1" 
AR Path="/600F2ED5/5FC89A17" Ref="SW?"  Part="1" 
F 0 "SW43" V 7300 1350 50  0000 R CNN
F 1 "Cherry MX" V 7250 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 7300 1600 50  0001 C CNN
F 3 "~" H 7300 1600 50  0001 C CNN
	1    7300 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D45
U 1 1 5FC89A1D
P 7300 1750
AR Path="/5EEB2DAF/5FC89A1D" Ref="D45"  Part="1" 
AR Path="/600F2ED5/5FC89A1D" Ref="D?"  Part="1" 
F 0 "D45" V 7400 1650 50  0000 C CNN
F 1 "1N4148" V 7400 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 7300 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 7300 1750 50  0001 C CNN
	1    7300 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D46
U 1 1 5FC89A23
P 7300 2650
AR Path="/5EEB2DAF/5FC89A23" Ref="D46"  Part="1" 
AR Path="/600F2ED5/5FC89A23" Ref="D?"  Part="1" 
F 0 "D46" V 7400 2550 50  0000 C CNN
F 1 "1N4148" V 7400 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 7300 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 7300 2650 50  0001 C CNN
	1    7300 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW44
U 1 1 5FC89A29
P 7300 2300
AR Path="/5EEB2DAF/5FC89A29" Ref="SW44"  Part="1" 
AR Path="/600F2ED5/5FC89A29" Ref="SW?"  Part="1" 
F 0 "SW44" V 7300 2250 50  0000 R CNN
F 1 "Cherry MX" V 7250 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 7300 2500 50  0001 C CNN
F 3 "~" H 7300 2500 50  0001 C CNN
	1    7300 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7300 2000 7600 2000
Wire Wire Line
	7600 2000 7600 2900
Wire Wire Line
	7300 5600 7600 5600
Wire Wire Line
	7300 2900 7600 2900
Wire Wire Line
	7600 4700 7600 5600
Wire Wire Line
	6600 2100 7300 2100
Wire Wire Line
	6600 1200 7300 1200
Wire Wire Line
	7600 5600 7600 5800
Connection ~ 7600 5600
Wire Wire Line
	6600 4800 7300 4800
Connection ~ 7300 4800
Connection ~ 7300 2100
Connection ~ 7300 1200
Text HLabel 8300 5800 3    50   Input ~ 0
COL10
Wire Wire Line
	8000 1900 8000 2000
Wire Wire Line
	8000 2900 8000 2800
$Comp
L Switch:SW_Push SW52
U 1 1 5FC95732
P 8000 5000
AR Path="/5EEB2DAF/5FC95732" Ref="SW52"  Part="1" 
AR Path="/600F2ED5/5FC95732" Ref="SW?"  Part="1" 
F 0 "SW52" V 8000 4950 50  0000 R CNN
F 1 "Cherry MX" V 7950 4900 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 8000 5200 50  0001 C CNN
F 3 "~" H 8000 5200 50  0001 C CNN
	1    8000 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8000 5600 8000 5500
$Comp
L Diode:1N4148 D54
U 1 1 5FC95739
P 8000 5350
AR Path="/5EEB2DAF/5FC95739" Ref="D54"  Part="1" 
AR Path="/600F2ED5/5FC95739" Ref="D?"  Part="1" 
F 0 "D54" V 8100 5250 50  0000 C CNN
F 1 "1N4148" V 8100 5550 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8000 5175 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 8000 5350 50  0001 C CNN
	1    8000 5350
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW48
U 1 1 5FC9573F
P 8000 1400
AR Path="/5EEB2DAF/5FC9573F" Ref="SW48"  Part="1" 
AR Path="/600F2ED5/5FC9573F" Ref="SW?"  Part="1" 
F 0 "SW48" V 8000 1350 50  0000 R CNN
F 1 "Cherry MX" V 7950 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 8000 1600 50  0001 C CNN
F 3 "~" H 8000 1600 50  0001 C CNN
	1    8000 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D50
U 1 1 5FC95745
P 8000 1750
AR Path="/5EEB2DAF/5FC95745" Ref="D50"  Part="1" 
AR Path="/600F2ED5/5FC95745" Ref="D?"  Part="1" 
F 0 "D50" V 8100 1650 50  0000 C CNN
F 1 "1N4148" V 8100 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8000 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 8000 1750 50  0001 C CNN
	1    8000 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D51
U 1 1 5FC9574B
P 8000 2650
AR Path="/5EEB2DAF/5FC9574B" Ref="D51"  Part="1" 
AR Path="/600F2ED5/5FC9574B" Ref="D?"  Part="1" 
F 0 "D51" V 8100 2550 50  0000 C CNN
F 1 "1N4148" V 8100 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8000 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 8000 2650 50  0001 C CNN
	1    8000 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW49
U 1 1 5FC95751
P 8000 2300
AR Path="/5EEB2DAF/5FC95751" Ref="SW49"  Part="1" 
AR Path="/600F2ED5/5FC95751" Ref="SW?"  Part="1" 
F 0 "SW49" V 8000 2250 50  0000 R CNN
F 1 "Cherry MX" V 7950 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 8000 2500 50  0001 C CNN
F 3 "~" H 8000 2500 50  0001 C CNN
	1    8000 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8000 2000 8300 2000
Wire Wire Line
	8300 2000 8300 2900
Wire Wire Line
	8000 5600 8300 5600
Wire Wire Line
	8000 2900 8300 2900
Wire Wire Line
	8300 4700 8300 5600
Wire Wire Line
	7300 2100 8000 2100
Wire Wire Line
	7300 1200 8000 1200
Wire Wire Line
	8300 5600 8300 5800
Connection ~ 8300 5600
Wire Wire Line
	7300 4800 8000 4800
Connection ~ 8000 4800
Connection ~ 8000 2100
Connection ~ 8000 1200
Text HLabel 9000 5800 3    50   Input ~ 0
COL11
Wire Wire Line
	8700 1900 8700 2000
Wire Wire Line
	8700 2900 8700 2800
$Comp
L Switch:SW_Push SW57
U 1 1 5FC9EB2D
P 8700 5000
AR Path="/5EEB2DAF/5FC9EB2D" Ref="SW57"  Part="1" 
AR Path="/600F2ED5/5FC9EB2D" Ref="SW?"  Part="1" 
F 0 "SW57" V 8700 4950 50  0000 R CNN
F 1 "Cherry MX" V 8650 4900 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 8700 5200 50  0001 C CNN
F 3 "~" H 8700 5200 50  0001 C CNN
	1    8700 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8700 5600 8700 5500
$Comp
L Diode:1N4148 D59
U 1 1 5FC9EB34
P 8700 5350
AR Path="/5EEB2DAF/5FC9EB34" Ref="D59"  Part="1" 
AR Path="/600F2ED5/5FC9EB34" Ref="D?"  Part="1" 
F 0 "D59" V 8800 5250 50  0000 C CNN
F 1 "1N4148" V 8800 5550 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8700 5175 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 8700 5350 50  0001 C CNN
	1    8700 5350
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW53
U 1 1 5FC9EB3A
P 8700 1400
AR Path="/5EEB2DAF/5FC9EB3A" Ref="SW53"  Part="1" 
AR Path="/600F2ED5/5FC9EB3A" Ref="SW?"  Part="1" 
F 0 "SW53" V 8700 1350 50  0000 R CNN
F 1 "Cherry MX" V 8650 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 8700 1600 50  0001 C CNN
F 3 "~" H 8700 1600 50  0001 C CNN
	1    8700 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D55
U 1 1 5FC9EB40
P 8700 1750
AR Path="/5EEB2DAF/5FC9EB40" Ref="D55"  Part="1" 
AR Path="/600F2ED5/5FC9EB40" Ref="D?"  Part="1" 
F 0 "D55" V 8800 1650 50  0000 C CNN
F 1 "1N4148" V 8800 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8700 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 8700 1750 50  0001 C CNN
	1    8700 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D56
U 1 1 5FC9EB46
P 8700 2650
AR Path="/5EEB2DAF/5FC9EB46" Ref="D56"  Part="1" 
AR Path="/600F2ED5/5FC9EB46" Ref="D?"  Part="1" 
F 0 "D56" V 8800 2550 50  0000 C CNN
F 1 "1N4148" V 8800 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8700 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 8700 2650 50  0001 C CNN
	1    8700 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW54
U 1 1 5FC9EB4C
P 8700 2300
AR Path="/5EEB2DAF/5FC9EB4C" Ref="SW54"  Part="1" 
AR Path="/600F2ED5/5FC9EB4C" Ref="SW?"  Part="1" 
F 0 "SW54" V 8700 2250 50  0000 R CNN
F 1 "Cherry MX" V 8650 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 8700 2500 50  0001 C CNN
F 3 "~" H 8700 2500 50  0001 C CNN
	1    8700 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8700 2000 9000 2000
Wire Wire Line
	9000 2000 9000 2900
Wire Wire Line
	8700 5600 9000 5600
Wire Wire Line
	8700 2900 9000 2900
Wire Wire Line
	9000 4700 9000 5600
Wire Wire Line
	8000 2100 8700 2100
Wire Wire Line
	8000 1200 8700 1200
Wire Wire Line
	9000 5600 9000 5800
Connection ~ 9000 5600
Wire Wire Line
	8000 4800 8700 4800
Connection ~ 8700 4800
Connection ~ 8700 2100
Connection ~ 8700 1200
Text HLabel 9700 5800 3    50   Input ~ 0
COL12
Wire Wire Line
	9400 1900 9400 2000
Wire Wire Line
	9400 2900 9400 2800
$Comp
L Switch:SW_Push SW58
U 1 1 5FCB4F03
P 9400 1400
AR Path="/5EEB2DAF/5FCB4F03" Ref="SW58"  Part="1" 
AR Path="/600F2ED5/5FCB4F03" Ref="SW?"  Part="1" 
F 0 "SW58" V 9400 1350 50  0000 R CNN
F 1 "Cherry MX" V 9350 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 9400 1600 50  0001 C CNN
F 3 "~" H 9400 1600 50  0001 C CNN
	1    9400 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D60
U 1 1 5FCB4F09
P 9400 1750
AR Path="/5EEB2DAF/5FCB4F09" Ref="D60"  Part="1" 
AR Path="/600F2ED5/5FCB4F09" Ref="D?"  Part="1" 
F 0 "D60" V 9500 1650 50  0000 C CNN
F 1 "1N4148" V 9500 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 9400 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 9400 1750 50  0001 C CNN
	1    9400 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D61
U 1 1 5FCB4F0F
P 9400 2650
AR Path="/5EEB2DAF/5FCB4F0F" Ref="D61"  Part="1" 
AR Path="/600F2ED5/5FCB4F0F" Ref="D?"  Part="1" 
F 0 "D61" V 9500 2550 50  0000 C CNN
F 1 "1N4148" V 9500 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 9400 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 9400 2650 50  0001 C CNN
	1    9400 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW59
U 1 1 5FCB4F15
P 9400 2300
AR Path="/5EEB2DAF/5FCB4F15" Ref="SW59"  Part="1" 
AR Path="/600F2ED5/5FCB4F15" Ref="SW?"  Part="1" 
F 0 "SW59" V 9400 2250 50  0000 R CNN
F 1 "Cherry MX" V 9350 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 9400 2500 50  0001 C CNN
F 3 "~" H 9400 2500 50  0001 C CNN
	1    9400 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9400 2000 9700 2000
Wire Wire Line
	9700 2000 9700 2900
Wire Wire Line
	9400 2900 9700 2900
Wire Wire Line
	8700 2100 9400 2100
Wire Wire Line
	8700 1200 9400 1200
Connection ~ 9400 2100
Connection ~ 9400 1200
Text HLabel 10400 5800 3    50   Input ~ 0
COL13
Wire Wire Line
	10100 1900 10100 2000
Wire Wire Line
	10100 2900 10100 2800
$Comp
L Switch:SW_Push SW64
U 1 1 5FCC0157
P 10100 5000
AR Path="/5EEB2DAF/5FCC0157" Ref="SW64"  Part="1" 
AR Path="/600F2ED5/5FCC0157" Ref="SW?"  Part="1" 
F 0 "SW64" V 10100 4950 50  0000 R CNN
F 1 "Cherry MX" V 10050 4900 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 10100 5200 50  0001 C CNN
F 3 "~" H 10100 5200 50  0001 C CNN
	1    10100 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10100 5600 10100 5500
$Comp
L Diode:1N4148 D66
U 1 1 5FCC015E
P 10100 5350
AR Path="/5EEB2DAF/5FCC015E" Ref="D66"  Part="1" 
AR Path="/600F2ED5/5FCC015E" Ref="D?"  Part="1" 
F 0 "D66" V 10200 5250 50  0000 C CNN
F 1 "1N4148" V 10200 5550 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 10100 5175 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 10100 5350 50  0001 C CNN
	1    10100 5350
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW60
U 1 1 5FCC0164
P 10100 1400
AR Path="/5EEB2DAF/5FCC0164" Ref="SW60"  Part="1" 
AR Path="/600F2ED5/5FCC0164" Ref="SW?"  Part="1" 
F 0 "SW60" V 10100 1350 50  0000 R CNN
F 1 "Cherry MX" V 10050 1300 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_2.00u_PCB" H 10100 1600 50  0001 C CNN
F 3 "~" H 10100 1600 50  0001 C CNN
	1    10100 1400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D62
U 1 1 5FCC016A
P 10100 1750
AR Path="/5EEB2DAF/5FCC016A" Ref="D62"  Part="1" 
AR Path="/600F2ED5/5FCC016A" Ref="D?"  Part="1" 
F 0 "D62" V 10200 1650 50  0000 C CNN
F 1 "1N4148" V 10200 1950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 10100 1575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 10100 1750 50  0001 C CNN
	1    10100 1750
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D63
U 1 1 5FCC0170
P 10100 2650
AR Path="/5EEB2DAF/5FCC0170" Ref="D63"  Part="1" 
AR Path="/600F2ED5/5FCC0170" Ref="D?"  Part="1" 
F 0 "D63" V 10200 2550 50  0000 C CNN
F 1 "1N4148" V 10200 2850 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 10100 2475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 10100 2650 50  0001 C CNN
	1    10100 2650
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW61
U 1 1 5FCC0176
P 10100 2300
AR Path="/5EEB2DAF/5FCC0176" Ref="SW61"  Part="1" 
AR Path="/600F2ED5/5FCC0176" Ref="SW?"  Part="1" 
F 0 "SW61" V 10100 2250 50  0000 R CNN
F 1 "Cherry MX" V 10050 2200 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.50u_PCB" H 10100 2500 50  0001 C CNN
F 3 "~" H 10100 2500 50  0001 C CNN
	1    10100 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10100 2000 10400 2000
Wire Wire Line
	10400 2000 10400 2900
Wire Wire Line
	10100 5600 10400 5600
Wire Wire Line
	10100 2900 10400 2900
Wire Wire Line
	10400 4700 10400 5600
Wire Wire Line
	9400 2100 10100 2100
Wire Wire Line
	9400 1200 10100 1200
Wire Wire Line
	10400 5600 10400 5800
Connection ~ 10400 5600
Connection ~ 10100 1200
Connection ~ 10100 2100
Connection ~ 10100 4800
Text HLabel 800  3000 0    50   Output ~ 0
ROW02
Wire Wire Line
	1000 3800 1000 3700
Text Notes 850  3250 2    50   ~ 0
CPCLK
$Comp
L Diode:1N4148 D6
U 1 1 5FD7894B
P 1000 3550
AR Path="/5EEB2DAF/5FD7894B" Ref="D6"  Part="1" 
AR Path="/600F2ED5/5FD7894B" Ref="D?"  Part="1" 
F 0 "D6" V 1100 3450 50  0000 C CNN
F 1 "1N4148" V 1100 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1000 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1000 3550 50  0001 C CNN
	1    1000 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW4
U 1 1 5FD78951
P 1000 3200
AR Path="/5EEB2DAF/5FD78951" Ref="SW4"  Part="1" 
AR Path="/600F2ED5/5FD78951" Ref="SW?"  Part="1" 
F 0 "SW4" V 1000 3150 50  0000 R CNN
F 1 "Cherry MX" V 950 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.75u_PCB" H 1000 3400 50  0001 C CNN
F 3 "~" H 1000 3400 50  0001 C CNN
	1    1000 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1000 3800 1300 3800
Wire Wire Line
	1700 3800 1700 3700
$Comp
L Diode:1N4148 D11
U 1 1 5FD7895A
P 1700 3550
AR Path="/5EEB2DAF/5FD7895A" Ref="D11"  Part="1" 
AR Path="/600F2ED5/5FD7895A" Ref="D?"  Part="1" 
F 0 "D11" V 1800 3450 50  0000 C CNN
F 1 "1N4148" V 1800 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1700 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1700 3550 50  0001 C CNN
	1    1700 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW9
U 1 1 5FD78960
P 1700 3200
AR Path="/5EEB2DAF/5FD78960" Ref="SW9"  Part="1" 
AR Path="/600F2ED5/5FD78960" Ref="SW?"  Part="1" 
F 0 "SW9" V 1700 3150 50  0000 R CNN
F 1 "Cherry MX" V 1650 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 1700 3400 50  0001 C CNN
F 3 "~" H 1700 3400 50  0001 C CNN
	1    1700 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2000 2900 2000 3800
Wire Wire Line
	1700 3800 2000 3800
Wire Wire Line
	1000 3000 1700 3000
Wire Wire Line
	10800 3800 10800 3700
$Comp
L Diode:1N4148 D69
U 1 1 5FD7896B
P 10800 3550
AR Path="/5EEB2DAF/5FD7896B" Ref="D69"  Part="1" 
AR Path="/600F2ED5/5FD7896B" Ref="D?"  Part="1" 
F 0 "D69" V 10900 3450 50  0000 C CNN
F 1 "1N4148" V 10900 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 10800 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 10800 3550 50  0001 C CNN
	1    10800 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW67
U 1 1 5FD78971
P 10800 3200
AR Path="/5EEB2DAF/5FD78971" Ref="SW67"  Part="1" 
AR Path="/600F2ED5/5FD78971" Ref="SW?"  Part="1" 
F 0 "SW67" V 10800 3150 50  0000 R CNN
F 1 "Cherry MX" V 10750 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 10800 3400 50  0001 C CNN
F 3 "~" H 10800 3400 50  0001 C CNN
	1    10800 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	11100 2900 11100 3800
Wire Wire Line
	10800 3800 11100 3800
Wire Wire Line
	10100 3000 10800 3000
Wire Wire Line
	800  3000 1000 3000
Connection ~ 1000 3000
Connection ~ 1700 3000
Wire Wire Line
	2400 3800 2400 3700
$Comp
L Diode:1N4148 D16
U 1 1 5FD7897F
P 2400 3550
AR Path="/5EEB2DAF/5FD7897F" Ref="D16"  Part="1" 
AR Path="/600F2ED5/5FD7897F" Ref="D?"  Part="1" 
F 0 "D16" V 2500 3450 50  0000 C CNN
F 1 "1N4148" V 2500 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 2400 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 2400 3550 50  0001 C CNN
	1    2400 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW14
U 1 1 5FD78985
P 2400 3200
AR Path="/5EEB2DAF/5FD78985" Ref="SW14"  Part="1" 
AR Path="/600F2ED5/5FD78985" Ref="SW?"  Part="1" 
F 0 "SW14" V 2400 3150 50  0000 R CNN
F 1 "Cherry MX" V 2350 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 2400 3400 50  0001 C CNN
F 3 "~" H 2400 3400 50  0001 C CNN
	1    2400 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2700 2900 2700 3800
Wire Wire Line
	2400 3800 2700 3800
Wire Wire Line
	1700 3000 2400 3000
Connection ~ 2400 3000
Wire Wire Line
	3100 3800 3100 3700
$Comp
L Diode:1N4148 D21
U 1 1 5FD78990
P 3100 3550
AR Path="/5EEB2DAF/5FD78990" Ref="D21"  Part="1" 
AR Path="/600F2ED5/5FD78990" Ref="D?"  Part="1" 
F 0 "D21" V 3200 3450 50  0000 C CNN
F 1 "1N4148" V 3200 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3100 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 3100 3550 50  0001 C CNN
	1    3100 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW19
U 1 1 5FD78996
P 3100 3200
AR Path="/5EEB2DAF/5FD78996" Ref="SW19"  Part="1" 
AR Path="/600F2ED5/5FD78996" Ref="SW?"  Part="1" 
F 0 "SW19" V 3100 3150 50  0000 R CNN
F 1 "Cherry MX" V 3050 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 3100 3400 50  0001 C CNN
F 3 "~" H 3100 3400 50  0001 C CNN
	1    3100 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3400 2900 3400 3800
Wire Wire Line
	3100 3800 3400 3800
Wire Wire Line
	2400 3000 3100 3000
Connection ~ 3100 3000
Wire Wire Line
	3800 3800 3800 3700
$Comp
L Diode:1N4148 D25
U 1 1 5FD789A1
P 3800 3550
AR Path="/5EEB2DAF/5FD789A1" Ref="D25"  Part="1" 
AR Path="/600F2ED5/5FD789A1" Ref="D?"  Part="1" 
F 0 "D25" V 3900 3450 50  0000 C CNN
F 1 "1N4148" V 3900 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3800 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 3800 3550 50  0001 C CNN
	1    3800 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW23
U 1 1 5FD789A7
P 3800 3200
AR Path="/5EEB2DAF/5FD789A7" Ref="SW23"  Part="1" 
AR Path="/600F2ED5/5FD789A7" Ref="SW?"  Part="1" 
F 0 "SW23" V 3800 3150 50  0000 R CNN
F 1 "Cherry MX" V 3750 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 3800 3400 50  0001 C CNN
F 3 "~" H 3800 3400 50  0001 C CNN
	1    3800 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4100 2900 4100 3800
Wire Wire Line
	3800 3800 4100 3800
Wire Wire Line
	3100 3000 3800 3000
Connection ~ 3800 3000
Wire Wire Line
	4500 3800 4500 3700
$Comp
L Diode:1N4148 D29
U 1 1 5FD789B2
P 4500 3550
AR Path="/5EEB2DAF/5FD789B2" Ref="D29"  Part="1" 
AR Path="/600F2ED5/5FD789B2" Ref="D?"  Part="1" 
F 0 "D29" V 4600 3450 50  0000 C CNN
F 1 "1N4148" V 4600 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4500 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 4500 3550 50  0001 C CNN
	1    4500 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW27
U 1 1 5FD789B8
P 4500 3200
AR Path="/5EEB2DAF/5FD789B8" Ref="SW27"  Part="1" 
AR Path="/600F2ED5/5FD789B8" Ref="SW?"  Part="1" 
F 0 "SW27" V 4500 3150 50  0000 R CNN
F 1 "Cherry MX" V 4450 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 4500 3400 50  0001 C CNN
F 3 "~" H 4500 3400 50  0001 C CNN
	1    4500 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4800 2900 4800 3800
Wire Wire Line
	4500 3800 4800 3800
Wire Wire Line
	3800 3000 4500 3000
Connection ~ 4500 3000
Wire Wire Line
	5200 3800 5200 3700
$Comp
L Diode:1N4148 D34
U 1 1 5FD789C3
P 5200 3550
AR Path="/5EEB2DAF/5FD789C3" Ref="D34"  Part="1" 
AR Path="/600F2ED5/5FD789C3" Ref="D?"  Part="1" 
F 0 "D34" V 5300 3450 50  0000 C CNN
F 1 "1N4148" V 5300 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5200 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5200 3550 50  0001 C CNN
	1    5200 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW32
U 1 1 5FD789C9
P 5200 3200
AR Path="/5EEB2DAF/5FD789C9" Ref="SW32"  Part="1" 
AR Path="/600F2ED5/5FD789C9" Ref="SW?"  Part="1" 
F 0 "SW32" V 5200 3150 50  0000 R CNN
F 1 "Cherry MX" V 5150 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 5200 3400 50  0001 C CNN
F 3 "~" H 5200 3400 50  0001 C CNN
	1    5200 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5500 2900 5500 3800
Wire Wire Line
	5200 3800 5500 3800
Wire Wire Line
	4500 3000 5200 3000
Connection ~ 5200 3000
Wire Wire Line
	5900 3800 5900 3700
$Comp
L Diode:1N4148 D38
U 1 1 5FD789D4
P 5900 3550
AR Path="/5EEB2DAF/5FD789D4" Ref="D38"  Part="1" 
AR Path="/600F2ED5/5FD789D4" Ref="D?"  Part="1" 
F 0 "D38" V 6000 3450 50  0000 C CNN
F 1 "1N4148" V 6000 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5900 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5900 3550 50  0001 C CNN
	1    5900 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW36
U 1 1 5FD789DA
P 5900 3200
AR Path="/5EEB2DAF/5FD789DA" Ref="SW36"  Part="1" 
AR Path="/600F2ED5/5FD789DA" Ref="SW?"  Part="1" 
F 0 "SW36" V 5900 3150 50  0000 R CNN
F 1 "Cherry MX" V 5850 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 5900 3400 50  0001 C CNN
F 3 "~" H 5900 3400 50  0001 C CNN
	1    5900 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6200 2900 6200 3800
Wire Wire Line
	5900 3800 6200 3800
Wire Wire Line
	5200 3000 5900 3000
Connection ~ 5900 3000
Wire Wire Line
	6600 3800 6600 3700
$Comp
L Diode:1N4148 D42
U 1 1 5FD789E5
P 6600 3550
AR Path="/5EEB2DAF/5FD789E5" Ref="D42"  Part="1" 
AR Path="/600F2ED5/5FD789E5" Ref="D?"  Part="1" 
F 0 "D42" V 6700 3450 50  0000 C CNN
F 1 "1N4148" V 6700 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6600 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 6600 3550 50  0001 C CNN
	1    6600 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW40
U 1 1 5FD789EB
P 6600 3200
AR Path="/5EEB2DAF/5FD789EB" Ref="SW40"  Part="1" 
AR Path="/600F2ED5/5FD789EB" Ref="SW?"  Part="1" 
F 0 "SW40" V 6600 3150 50  0000 R CNN
F 1 "Cherry MX" V 6550 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 6600 3400 50  0001 C CNN
F 3 "~" H 6600 3400 50  0001 C CNN
	1    6600 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6900 2900 6900 3800
Wire Wire Line
	6600 3800 6900 3800
Wire Wire Line
	5900 3000 6600 3000
Connection ~ 6600 3000
Wire Wire Line
	7300 3800 7300 3700
$Comp
L Diode:1N4148 D47
U 1 1 5FD789F6
P 7300 3550
AR Path="/5EEB2DAF/5FD789F6" Ref="D47"  Part="1" 
AR Path="/600F2ED5/5FD789F6" Ref="D?"  Part="1" 
F 0 "D47" V 7400 3450 50  0000 C CNN
F 1 "1N4148" V 7400 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 7300 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 7300 3550 50  0001 C CNN
	1    7300 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW45
U 1 1 5FD789FC
P 7300 3200
AR Path="/5EEB2DAF/5FD789FC" Ref="SW45"  Part="1" 
AR Path="/600F2ED5/5FD789FC" Ref="SW?"  Part="1" 
F 0 "SW45" V 7300 3150 50  0000 R CNN
F 1 "Cherry MX" V 7250 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 7300 3400 50  0001 C CNN
F 3 "~" H 7300 3400 50  0001 C CNN
	1    7300 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7600 2900 7600 3800
Wire Wire Line
	7300 3800 7600 3800
Wire Wire Line
	6600 3000 7300 3000
Connection ~ 7300 3000
Wire Wire Line
	8000 3800 8000 3700
$Comp
L Diode:1N4148 D52
U 1 1 5FD78A07
P 8000 3550
AR Path="/5EEB2DAF/5FD78A07" Ref="D52"  Part="1" 
AR Path="/600F2ED5/5FD78A07" Ref="D?"  Part="1" 
F 0 "D52" V 8100 3450 50  0000 C CNN
F 1 "1N4148" V 8100 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8000 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 8000 3550 50  0001 C CNN
	1    8000 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW50
U 1 1 5FD78A0D
P 8000 3200
AR Path="/5EEB2DAF/5FD78A0D" Ref="SW50"  Part="1" 
AR Path="/600F2ED5/5FD78A0D" Ref="SW?"  Part="1" 
F 0 "SW50" V 8000 3150 50  0000 R CNN
F 1 "Cherry MX" V 7950 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 8000 3400 50  0001 C CNN
F 3 "~" H 8000 3400 50  0001 C CNN
	1    8000 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8300 2900 8300 3800
Wire Wire Line
	8000 3800 8300 3800
Wire Wire Line
	7300 3000 8000 3000
Connection ~ 8000 3000
Wire Wire Line
	8700 3800 8700 3700
$Comp
L Diode:1N4148 D57
U 1 1 5FD78A18
P 8700 3550
AR Path="/5EEB2DAF/5FD78A18" Ref="D57"  Part="1" 
AR Path="/600F2ED5/5FD78A18" Ref="D?"  Part="1" 
F 0 "D57" V 8800 3450 50  0000 C CNN
F 1 "1N4148" V 8800 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8700 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 8700 3550 50  0001 C CNN
	1    8700 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW55
U 1 1 5FD78A1E
P 8700 3200
AR Path="/5EEB2DAF/5FD78A1E" Ref="SW55"  Part="1" 
AR Path="/600F2ED5/5FD78A1E" Ref="SW?"  Part="1" 
F 0 "SW55" V 8700 3150 50  0000 R CNN
F 1 "Cherry MX" V 8650 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 8700 3400 50  0001 C CNN
F 3 "~" H 8700 3400 50  0001 C CNN
	1    8700 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9000 2900 9000 3800
Wire Wire Line
	8700 3800 9000 3800
Wire Wire Line
	8000 3000 8700 3000
Connection ~ 8700 3000
Wire Wire Line
	10100 3800 10100 3700
$Comp
L Diode:1N4148 D64
U 1 1 5FD78A3A
P 10100 3550
AR Path="/5EEB2DAF/5FD78A3A" Ref="D64"  Part="1" 
AR Path="/600F2ED5/5FD78A3A" Ref="D?"  Part="1" 
F 0 "D64" V 10200 3450 50  0000 C CNN
F 1 "1N4148" V 10200 3750 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 10100 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 10100 3550 50  0001 C CNN
	1    10100 3550
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW62
U 1 1 5FD78A40
P 10100 3200
AR Path="/5EEB2DAF/5FD78A40" Ref="SW62"  Part="1" 
AR Path="/600F2ED5/5FD78A40" Ref="SW?"  Part="1" 
F 0 "SW62" V 10100 3150 50  0000 R CNN
F 1 "Cherry MX" V 10050 3100 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_2.25u_PCB" H 10100 3400 50  0001 C CNN
F 3 "~" H 10100 3400 50  0001 C CNN
	1    10100 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10400 2900 10400 3800
Wire Wire Line
	10100 3800 10400 3800
Connection ~ 10100 3000
Wire Wire Line
	1300 2900 1300 3800
Connection ~ 1300 2900
Connection ~ 2000 2900
Wire Wire Line
	2400 2900 2700 2900
Connection ~ 2700 2900
Connection ~ 3400 2900
Connection ~ 4100 2900
Connection ~ 4800 2900
Connection ~ 5500 2900
Connection ~ 6200 2900
Connection ~ 6900 2900
Connection ~ 7600 2900
Connection ~ 8300 2900
Connection ~ 9000 2900
Connection ~ 9700 2900
Connection ~ 10400 2900
Connection ~ 11100 2900
Text HLabel 800  3900 0    50   Output ~ 0
ROW03
Wire Wire Line
	1000 4700 1000 4600
Text Notes 850  4150 2    50   ~ 0
LSHFT
$Comp
L Diode:1N4148 D7
U 1 1 5FDB90FA
P 1000 4450
AR Path="/5EEB2DAF/5FDB90FA" Ref="D7"  Part="1" 
AR Path="/600F2ED5/5FDB90FA" Ref="D?"  Part="1" 
F 0 "D7" V 1100 4350 50  0000 C CNN
F 1 "1N4148" V 1100 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1000 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1000 4450 50  0001 C CNN
	1    1000 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW5
U 1 1 5FDB9100
P 1000 4100
AR Path="/5EEB2DAF/5FDB9100" Ref="SW5"  Part="1" 
AR Path="/600F2ED5/5FDB9100" Ref="SW?"  Part="1" 
F 0 "SW5" V 1000 4050 50  0000 R CNN
F 1 "Cherry MX" V 950 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_2.25u_PCB" H 1000 4300 50  0001 C CNN
F 3 "~" H 1000 4300 50  0001 C CNN
	1    1000 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1000 4700 1300 4700
Wire Wire Line
	1700 4700 1700 4600
$Comp
L Diode:1N4148 D12
U 1 1 5FDB9108
P 1700 4450
AR Path="/5EEB2DAF/5FDB9108" Ref="D12"  Part="1" 
AR Path="/600F2ED5/5FDB9108" Ref="D?"  Part="1" 
F 0 "D12" V 1800 4350 50  0000 C CNN
F 1 "1N4148" V 1800 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1700 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1700 4450 50  0001 C CNN
	1    1700 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW10
U 1 1 5FDB910E
P 1700 4100
AR Path="/5EEB2DAF/5FDB910E" Ref="SW10"  Part="1" 
AR Path="/600F2ED5/5FDB910E" Ref="SW?"  Part="1" 
F 0 "SW10" V 1700 4050 50  0000 R CNN
F 1 "Cherry MX" V 1650 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 1700 4300 50  0001 C CNN
F 3 "~" H 1700 4300 50  0001 C CNN
	1    1700 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2000 3800 2000 4700
Wire Wire Line
	1700 4700 2000 4700
Wire Wire Line
	1000 3900 1700 3900
Wire Wire Line
	10800 4700 10800 4600
$Comp
L Diode:1N4148 D70
U 1 1 5FDB9119
P 10800 4450
AR Path="/5EEB2DAF/5FDB9119" Ref="D70"  Part="1" 
AR Path="/600F2ED5/5FDB9119" Ref="D?"  Part="1" 
F 0 "D70" V 10900 4350 50  0000 C CNN
F 1 "1N4148" V 10900 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 10800 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 10800 4450 50  0001 C CNN
	1    10800 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW68
U 1 1 5FDB911F
P 10800 4100
AR Path="/5EEB2DAF/5FDB911F" Ref="SW68"  Part="1" 
AR Path="/600F2ED5/5FDB911F" Ref="SW?"  Part="1" 
F 0 "SW68" V 10800 4050 50  0000 R CNN
F 1 "Cherry MX" V 10750 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 10800 4300 50  0001 C CNN
F 3 "~" H 10800 4300 50  0001 C CNN
	1    10800 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	11100 3800 11100 4700
Wire Wire Line
	10800 4700 11100 4700
Wire Wire Line
	10100 3900 10800 3900
Wire Wire Line
	800  3900 1000 3900
Connection ~ 1000 3900
Connection ~ 1700 3900
Wire Wire Line
	2400 4700 2400 4600
$Comp
L Diode:1N4148 D17
U 1 1 5FDB912D
P 2400 4450
AR Path="/5EEB2DAF/5FDB912D" Ref="D17"  Part="1" 
AR Path="/600F2ED5/5FDB912D" Ref="D?"  Part="1" 
F 0 "D17" V 2500 4350 50  0000 C CNN
F 1 "1N4148" V 2500 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 2400 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 2400 4450 50  0001 C CNN
	1    2400 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW15
U 1 1 5FDB9133
P 2400 4100
AR Path="/5EEB2DAF/5FDB9133" Ref="SW15"  Part="1" 
AR Path="/600F2ED5/5FDB9133" Ref="SW?"  Part="1" 
F 0 "SW15" V 2400 4050 50  0000 R CNN
F 1 "Cherry MX" V 2350 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 2400 4300 50  0001 C CNN
F 3 "~" H 2400 4300 50  0001 C CNN
	1    2400 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2700 3800 2700 4700
Wire Wire Line
	2400 4700 2700 4700
Wire Wire Line
	1700 3900 2400 3900
Connection ~ 2400 3900
Wire Wire Line
	3100 4700 3100 4600
$Comp
L Diode:1N4148 D22
U 1 1 5FDB913E
P 3100 4450
AR Path="/5EEB2DAF/5FDB913E" Ref="D22"  Part="1" 
AR Path="/600F2ED5/5FDB913E" Ref="D?"  Part="1" 
F 0 "D22" V 3200 4350 50  0000 C CNN
F 1 "1N4148" V 3200 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3100 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 3100 4450 50  0001 C CNN
	1    3100 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW20
U 1 1 5FDB9144
P 3100 4100
AR Path="/5EEB2DAF/5FDB9144" Ref="SW20"  Part="1" 
AR Path="/600F2ED5/5FDB9144" Ref="SW?"  Part="1" 
F 0 "SW20" V 3100 4050 50  0000 R CNN
F 1 "Cherry MX" V 3050 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 3100 4300 50  0001 C CNN
F 3 "~" H 3100 4300 50  0001 C CNN
	1    3100 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3400 3800 3400 4700
Wire Wire Line
	3100 4700 3400 4700
Wire Wire Line
	2400 3900 3100 3900
Connection ~ 3100 3900
Wire Wire Line
	3800 4700 3800 4600
$Comp
L Diode:1N4148 D26
U 1 1 5FDB914F
P 3800 4450
AR Path="/5EEB2DAF/5FDB914F" Ref="D26"  Part="1" 
AR Path="/600F2ED5/5FDB914F" Ref="D?"  Part="1" 
F 0 "D26" V 3900 4350 50  0000 C CNN
F 1 "1N4148" V 3900 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3800 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 3800 4450 50  0001 C CNN
	1    3800 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW24
U 1 1 5FDB9155
P 3800 4100
AR Path="/5EEB2DAF/5FDB9155" Ref="SW24"  Part="1" 
AR Path="/600F2ED5/5FDB9155" Ref="SW?"  Part="1" 
F 0 "SW24" V 3800 4050 50  0000 R CNN
F 1 "Cherry MX" V 3750 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 3800 4300 50  0001 C CNN
F 3 "~" H 3800 4300 50  0001 C CNN
	1    3800 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4100 3800 4100 4700
Wire Wire Line
	3800 4700 4100 4700
Wire Wire Line
	3100 3900 3800 3900
Connection ~ 3800 3900
Wire Wire Line
	4500 4700 4500 4600
$Comp
L Diode:1N4148 D30
U 1 1 5FDB9160
P 4500 4450
AR Path="/5EEB2DAF/5FDB9160" Ref="D30"  Part="1" 
AR Path="/600F2ED5/5FDB9160" Ref="D?"  Part="1" 
F 0 "D30" V 4600 4350 50  0000 C CNN
F 1 "1N4148" V 4600 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4500 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 4500 4450 50  0001 C CNN
	1    4500 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW28
U 1 1 5FDB9166
P 4500 4100
AR Path="/5EEB2DAF/5FDB9166" Ref="SW28"  Part="1" 
AR Path="/600F2ED5/5FDB9166" Ref="SW?"  Part="1" 
F 0 "SW28" V 4500 4050 50  0000 R CNN
F 1 "Cherry MX" V 4450 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 4500 4300 50  0001 C CNN
F 3 "~" H 4500 4300 50  0001 C CNN
	1    4500 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4800 3800 4800 4700
Wire Wire Line
	4500 4700 4800 4700
Wire Wire Line
	3800 3900 4500 3900
Connection ~ 4500 3900
Wire Wire Line
	5200 4700 5200 4600
$Comp
L Diode:1N4148 D35
U 1 1 5FDB9171
P 5200 4450
AR Path="/5EEB2DAF/5FDB9171" Ref="D35"  Part="1" 
AR Path="/600F2ED5/5FDB9171" Ref="D?"  Part="1" 
F 0 "D35" V 5300 4350 50  0000 C CNN
F 1 "1N4148" V 5300 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5200 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5200 4450 50  0001 C CNN
	1    5200 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW33
U 1 1 5FDB9177
P 5200 4100
AR Path="/5EEB2DAF/5FDB9177" Ref="SW33"  Part="1" 
AR Path="/600F2ED5/5FDB9177" Ref="SW?"  Part="1" 
F 0 "SW33" V 5200 4050 50  0000 R CNN
F 1 "Cherry MX" V 5150 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 5200 4300 50  0001 C CNN
F 3 "~" H 5200 4300 50  0001 C CNN
	1    5200 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5500 3800 5500 4700
Wire Wire Line
	5200 4700 5500 4700
Wire Wire Line
	4500 3900 5200 3900
Connection ~ 5200 3900
Wire Wire Line
	5900 4700 5900 4600
$Comp
L Diode:1N4148 D39
U 1 1 5FDB9182
P 5900 4450
AR Path="/5EEB2DAF/5FDB9182" Ref="D39"  Part="1" 
AR Path="/600F2ED5/5FDB9182" Ref="D?"  Part="1" 
F 0 "D39" V 6000 4350 50  0000 C CNN
F 1 "1N4148" V 6000 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5900 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5900 4450 50  0001 C CNN
	1    5900 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW37
U 1 1 5FDB9188
P 5900 4100
AR Path="/5EEB2DAF/5FDB9188" Ref="SW37"  Part="1" 
AR Path="/600F2ED5/5FDB9188" Ref="SW?"  Part="1" 
F 0 "SW37" V 5900 4050 50  0000 R CNN
F 1 "Cherry MX" V 5850 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 5900 4300 50  0001 C CNN
F 3 "~" H 5900 4300 50  0001 C CNN
	1    5900 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6200 3800 6200 4700
Wire Wire Line
	5900 4700 6200 4700
Wire Wire Line
	5200 3900 5900 3900
Connection ~ 5900 3900
Wire Wire Line
	6600 4700 6600 4600
$Comp
L Diode:1N4148 D43
U 1 1 5FDB9193
P 6600 4450
AR Path="/5EEB2DAF/5FDB9193" Ref="D43"  Part="1" 
AR Path="/600F2ED5/5FDB9193" Ref="D?"  Part="1" 
F 0 "D43" V 6700 4350 50  0000 C CNN
F 1 "1N4148" V 6700 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6600 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 6600 4450 50  0001 C CNN
	1    6600 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW41
U 1 1 5FDB9199
P 6600 4100
AR Path="/5EEB2DAF/5FDB9199" Ref="SW41"  Part="1" 
AR Path="/600F2ED5/5FDB9199" Ref="SW?"  Part="1" 
F 0 "SW41" V 6600 4050 50  0000 R CNN
F 1 "Cherry MX" V 6550 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 6600 4300 50  0001 C CNN
F 3 "~" H 6600 4300 50  0001 C CNN
	1    6600 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6900 3800 6900 4700
Wire Wire Line
	6600 4700 6900 4700
Wire Wire Line
	5900 3900 6600 3900
Connection ~ 6600 3900
Wire Wire Line
	7300 4700 7300 4600
$Comp
L Diode:1N4148 D48
U 1 1 5FDB91A4
P 7300 4450
AR Path="/5EEB2DAF/5FDB91A4" Ref="D48"  Part="1" 
AR Path="/600F2ED5/5FDB91A4" Ref="D?"  Part="1" 
F 0 "D48" V 7400 4350 50  0000 C CNN
F 1 "1N4148" V 7400 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 7300 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 7300 4450 50  0001 C CNN
	1    7300 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW46
U 1 1 5FDB91AA
P 7300 4100
AR Path="/5EEB2DAF/5FDB91AA" Ref="SW46"  Part="1" 
AR Path="/600F2ED5/5FDB91AA" Ref="SW?"  Part="1" 
F 0 "SW46" V 7300 4050 50  0000 R CNN
F 1 "Cherry MX" V 7250 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 7300 4300 50  0001 C CNN
F 3 "~" H 7300 4300 50  0001 C CNN
	1    7300 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7600 3800 7600 4700
Wire Wire Line
	7300 4700 7600 4700
Wire Wire Line
	6600 3900 7300 3900
Connection ~ 7300 3900
Wire Wire Line
	8000 4700 8000 4600
$Comp
L Diode:1N4148 D53
U 1 1 5FDB91B5
P 8000 4450
AR Path="/5EEB2DAF/5FDB91B5" Ref="D53"  Part="1" 
AR Path="/600F2ED5/5FDB91B5" Ref="D?"  Part="1" 
F 0 "D53" V 8100 4350 50  0000 C CNN
F 1 "1N4148" V 8100 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8000 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 8000 4450 50  0001 C CNN
	1    8000 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW51
U 1 1 5FDB91BB
P 8000 4100
AR Path="/5EEB2DAF/5FDB91BB" Ref="SW51"  Part="1" 
AR Path="/600F2ED5/5FDB91BB" Ref="SW?"  Part="1" 
F 0 "SW51" V 8000 4050 50  0000 R CNN
F 1 "Cherry MX" V 7950 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 8000 4300 50  0001 C CNN
F 3 "~" H 8000 4300 50  0001 C CNN
	1    8000 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8300 3800 8300 4700
Wire Wire Line
	8000 4700 8300 4700
Wire Wire Line
	7300 3900 8000 3900
Connection ~ 8000 3900
Wire Wire Line
	8700 4700 8700 4600
$Comp
L Diode:1N4148 D58
U 1 1 5FDB91C6
P 8700 4450
AR Path="/5EEB2DAF/5FDB91C6" Ref="D58"  Part="1" 
AR Path="/600F2ED5/5FDB91C6" Ref="D?"  Part="1" 
F 0 "D58" V 8800 4350 50  0000 C CNN
F 1 "1N4148" V 8800 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8700 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 8700 4450 50  0001 C CNN
	1    8700 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW56
U 1 1 5FDB91CC
P 8700 4100
AR Path="/5EEB2DAF/5FDB91CC" Ref="SW56"  Part="1" 
AR Path="/600F2ED5/5FDB91CC" Ref="SW?"  Part="1" 
F 0 "SW56" V 8700 4050 50  0000 R CNN
F 1 "Cherry MX" V 8650 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.75u_PCB" H 8700 4300 50  0001 C CNN
F 3 "~" H 8700 4300 50  0001 C CNN
	1    8700 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9000 3800 9000 4700
Wire Wire Line
	8700 4700 9000 4700
Wire Wire Line
	8000 3900 8700 3900
Connection ~ 8700 3900
Wire Wire Line
	10100 4700 10100 4600
$Comp
L Diode:1N4148 D65
U 1 1 5FDB91E8
P 10100 4450
AR Path="/5EEB2DAF/5FDB91E8" Ref="D65"  Part="1" 
AR Path="/600F2ED5/5FDB91E8" Ref="D?"  Part="1" 
F 0 "D65" V 10200 4350 50  0000 C CNN
F 1 "1N4148" V 10200 4650 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 10100 4275 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 10100 4450 50  0001 C CNN
	1    10100 4450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW63
U 1 1 5FDB91EE
P 10100 4100
AR Path="/5EEB2DAF/5FDB91EE" Ref="SW63"  Part="1" 
AR Path="/600F2ED5/5FDB91EE" Ref="SW?"  Part="1" 
F 0 "SW63" V 10100 4050 50  0000 R CNN
F 1 "Cherry MX" V 10050 4000 50  0001 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 10100 4300 50  0001 C CNN
F 3 "~" H 10100 4300 50  0001 C CNN
	1    10100 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10400 3800 10400 4700
Wire Wire Line
	10100 4700 10400 4700
Connection ~ 10100 3900
Wire Wire Line
	1300 3800 1300 4700
Connection ~ 1300 3800
Connection ~ 2000 3800
Connection ~ 2700 3800
Connection ~ 3400 3800
Connection ~ 4100 3800
Connection ~ 4800 3800
Connection ~ 5500 3800
Connection ~ 6200 3800
Connection ~ 6900 3800
Connection ~ 7600 3800
Connection ~ 8300 3800
Connection ~ 9000 3800
Connection ~ 10400 3800
Connection ~ 11100 3800
Connection ~ 1300 4700
Connection ~ 2000 4700
Connection ~ 2700 4700
Connection ~ 3400 4700
Connection ~ 4100 4700
Connection ~ 4800 4700
Connection ~ 5500 4700
Connection ~ 6200 4700
Connection ~ 6900 4700
Connection ~ 7600 4700
Connection ~ 8300 4700
Connection ~ 9000 4700
Connection ~ 10400 4700
Connection ~ 11100 4700
Text Notes 1550 1450 2    50   ~ 0
1
Text Notes 2250 1450 2    50   ~ 0
2
Text Notes 2950 1450 2    50   ~ 0
3
Text Notes 3650 1450 2    50   ~ 0
4
Text Notes 4350 1450 2    50   ~ 0
5
Text Notes 5050 1450 2    50   ~ 0
6
Text Notes 5750 1450 2    50   ~ 0
7
Text Notes 6450 1450 2    50   ~ 0
8
Text Notes 7150 1450 2    50   ~ 0
9
Text Notes 7850 1450 2    50   ~ 0
0
Text Notes 8550 1450 2    50   ~ 0
DASH
Text Notes 9250 1450 2    50   ~ 0
EQUAL
Text Notes 9950 1450 2    50   ~ 0
BKSPC
Text Notes 10650 1450 2    50   ~ 0
GRAVE
Text Notes 1550 5050 2    50   ~ 0
LGUI
Text Notes 2250 5050 2    50   ~ 0
LALT
Text Notes 1550 2350 2    50   ~ 0
Q
Text Notes 1550 3250 2    50   ~ 0
A
Text Notes 1550 4150 2    50   ~ 0
Z
Text Notes 2250 2350 2    50   ~ 0
W
Text Notes 2950 2350 2    50   ~ 0
E
Text Notes 3650 2350 2    50   ~ 0
R
Text Notes 4350 2350 2    50   ~ 0
T
Text Notes 5050 2350 2    50   ~ 0
Y
Text Notes 5750 2350 2    50   ~ 0
U
Text Notes 6450 2350 2    50   ~ 0
I
Text Notes 7150 2350 2    50   ~ 0
O
Text Notes 7850 2350 2    50   ~ 0
P
Text Notes 8550 2350 2    50   ~ 0
LBRKT
Text Notes 9250 2350 2    50   ~ 0
RBRKT
Text Notes 9950 2350 2    50   ~ 0
BSLSH
Text Notes 10650 2350 2    50   ~ 0
DEL
Text Notes 2250 3250 2    50   ~ 0
S
Text Notes 2950 3250 2    50   ~ 0
D
Text Notes 3650 3250 2    50   ~ 0
F
Text Notes 4350 3250 2    50   ~ 0
G
Text Notes 5050 3250 2    50   ~ 0
H
Text Notes 5750 3250 2    50   ~ 0
J
Text Notes 6450 3250 2    50   ~ 0
K
Text Notes 7150 3250 2    50   ~ 0
L
Text Notes 7850 3250 2    50   ~ 0
SEMI
Text Notes 8550 3250 2    50   ~ 0
QUOTE
Wire Wire Line
	8700 3000 10100 3000
Text Notes 9950 3250 2    50   ~ 0
ENTER
Text Notes 10650 3250 2    50   ~ 0
PGUP
Text Notes 2250 4150 2    50   ~ 0
X
Text Notes 2950 4150 2    50   ~ 0
C
Text Notes 3650 4150 2    50   ~ 0
V
Text Notes 4350 4150 2    50   ~ 0
B
Text Notes 5050 4150 2    50   ~ 0
N
Text Notes 5750 4150 2    50   ~ 0
M
Text Notes 6450 4150 2    50   ~ 0
COMMA
Text Notes 7150 4150 2    50   ~ 0
PRIOD
Text Notes 7850 4150 2    50   ~ 0
FSLSH
Text Notes 7150 5050 2    50   ~ 0
RCTRL
Text Notes 8550 4150 2    50   ~ 0
RSHFT
Wire Wire Line
	8700 3900 10100 3900
Text Notes 4350 5050 2    50   ~ 0
SPACE
Text Notes 6450 5050 2    50   ~ 0
RALT
Wire Wire Line
	3400 4700 3400 5800
Wire Wire Line
	2400 4800 4500 4800
Wire Wire Line
	4100 4700 4100 5800
Connection ~ 4500 4800
Wire Wire Line
	5500 4700 5500 5800
Wire Wire Line
	4500 4800 6600 4800
Wire Wire Line
	6200 4700 6200 5800
Text Notes 7850 5050 2    50   ~ 0
FN
Wire Wire Line
	8700 4800 10100 4800
Wire Wire Line
	9700 2900 9700 5800
Text Notes 8550 5050 2    50   ~ 0
LARRW
Text Notes 10650 4150 2    50   ~ 0
PGDN
Text Notes 10650 5050 2    50   ~ 0
RARRW
Text Notes 9950 5050 2    50   ~ 0
DARRW
Text Notes 9950 4150 2    50   ~ 0
UARRW
$EndSCHEMATC
