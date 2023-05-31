# FOC Motor Controller
This project was a multi-year effort to develop a ground-up, brushless motor (BLDC) controller for use in underwater robotics. 

The final controller is designed for T200 or T100 thrusters from BlueRobotics, boasting sensorless FOC and a miniature form-factor that is built right into the thruster.

## Key Features
- Sensorless FOC / sinusoidal commutation
- Input voltage up to 14V
- 250W Continuous Power
- CAN Bus telemetry and control
- Built into the T200 thruster, water-cooled
- Low underwater acoustic noise
- Up to 10-20% better efficiency than standard ESCs
- Great low-RPM operation and control
- *Ludicrous* mode, able to overmodulate and reach higher RPMs


![PCB Front](https://github.com/mark-belbin/motor-controller/blob/master/docs/images/pcb_front.png)

> FOC Thruster Controller V2 Top View

![PCB Back](https://github.com/mark-belbin/motor-controller/blob/master/docs/images/pcb_back.png)

> FOC Thruster Controller V2 Bottom View

# Table of Contents
1. [Introduction](#Introduction)
1. [FOC Benefits](#FOC-Benefits)
   1. [Phase Currents](#Phase-Currents)
   1. [Operating Noise](#Operating-Noise)
   1. [Efficiency](#Efficiency)
   1. [Other Benefits](#Other-Benefits)
1. [Motor Controller PCB](#Motor-Controller-PCB)
1. [Controller Firmware](#Controller-Firmware)
1. [T200 Thruster Mount](#T200-Thruster-Mount)
1. [Repository Content](#Repository-Content)


# Introduction
Brushless motors, such as BLDC or PMSM motors, have no physical link between the stator and rotor like in a standard DC motor. Therefore, these motors must be commutated (spun properly) using an external controller. The key is knowing where the motor's rotor is relative to the stator, such that the magnetic field of the stator can be generated with accuracy in order to successfully push along the rotor and get the motor to spin. 

For most hobby BLDC controllers, commonly referred to as electronic speed controllers (ESCs), motor commutation is accomplished through sensorless trapezoidal 6-step control. This commutation method steps through 6 distinct stator magnetic field positions in order to keep the motor spinning, based only on the feedback of the back-EMF voltage of the three motor phases. With only 6 available control positions, this method of commutation lacks maximum possible efficiency, but it remains a simple, reliable, and cheap control method. 

This motor controller design implements Field-oriented control (FOC), also known as sinusoidal control or sine wave control. The FOC algorithm used is provided by Texas Instrument's InstaSPIN product line. This enables FOC using sensorless feedback, meaning no extra encoders or sensors are attached to the motor. The TI sensorless system measures only the 3 phase voltages and 3 phase currents of the motor in order to estimate the current rotor position with high accuracy. Also important is the intrinsic properties of the motor, such as the phase resistance, inductance, and the motor flux linkage. InstaSPIN requires a motor calibration procedure be run on each unique motor to automatically determine these intrinsic values, if not the FOC algorithm will not run.

This custom FOC controller design was evaluated by comparing against the BlueRobotics Basic ESC R3, a standard hobby-style ESC. Both will run the same BlueRobotics T200 thruster, which is the intended use-case of the custom developed controller. 

![T200 and Basic ESC](https://github.com/mark-belbin/motor-controller/blob/master/docs/images/T200_BR_ESC.PNG)

> BlueRobotics T200 Thruster and Basic ESC R3.


# FOC Benefits
FOC has numerous potential benefits compared to traditional trapezoidal control. The most striking are the increase in efficiency and reduction in motor noise. This is possible since FOC control applies the most optimal stator magnetic field to push the rotor forward, and as a result generates clean and noise-free sine-wave current wave forms.

## Phase Currents

A comparison of current waveforms is shown below. Both the custom FOC controller and the Blue Robotics Basic ESC R3 are controlling a submerged T200 thruster at 2000 RPM. The FOC phase currents are much cleaner and closer to sinewaves, while the Basic ESC waveforms are more choppy and trapezoidal.

![FOC Currents](https://github.com/mark-belbin/motor-controller/blob/master/docs/images/phase_currents.PNG)

> FOC phase currents vs the BR Basic ESC R3 at 2000 RPM.

## Operating Noise

A significant difference in operating noise is observed because of the current waveform difference. This is very noticeable underwater too, as the louder electrical sounds generated by the Basic ESC travel far. By comparison the custom FOC controller runs quiet, especially for low to mid-range speeds of 0-2000 RPM.

## Efficiency

An efficiency test was completed for both the custom and off-the-shelf controllers. A T200 was secured and submerged in a relatively large tub full of water. A separate waterproof, magnetic RPM sensor was attached to the shaft of the T200 to independently measure the RPM of the thruster. Measurements were taken of the input power of the motor controller under test for RPM settings in steps of 100 RPM.

![Controller Testing](https://github.com/mark-belbin/motor-controller/blob/master/docs/images/controller_testing.PNG)

> FOC Controller Testing

The FOC controller is more efficient across nearly the entire RPM range. The graph below is shows superiority up until about 2500 RPM, beyond which the FOC controller has the same or slightly worse performance. This is a limitation of FOC, where at a certain voltage the controller will switch to overmodulation control, where the controller will gradually transition to trapezoidal control as the RPM increases. To remain efficient at upper RPMs, a higher input voltage would need to be supplied.

![Efficiency Graph](https://github.com/mark-belbin/motor-controller/blob/master/docs/images/eff_graph.PNG)

> FOC Controller vs the BR Basic ESC R3.

Here's how the efficiency difference changes over the course of the RPM range: 

- From 0 to 600 RPM, the FOC controller consumes about 50% less power, a percent increase in efficiency of 100-150%
- From 600 to 1500 RPM, 20% less power is consumed, a percent increase in efficiency of 25-30%.
- From 1500 to 2000 RPM, 15% less power is consumed, a percent increase in efficiency of 15-20%.
- From 2000 to 2500 RPM, 5-10% less power is consumed, a percent increase in efficiency of 8-10%.
- Beyond 2500 RPM, the FOC controller consumes 0-5% more power than the Basic ESC.

The outperformance at lower RPMs is significant, since many underwater robotics applications operate in this range, such as Autonomous Underwater Vehicles (AUVs) or Autonomous Surface Vessels (ASVs). Battery life is critical for these types of vehicles, and the reduction in motor power from FOC control could have a big impact. 

## Other Benefits

A few other minor benefits were observed with the custom controller and FOC:

1. Great low speed control; The controller can operate at speeds down to a few RPM, where the Basic ESC cuts out under about 100 RPM.
2. Clean forward / reverse switching; During 0 RPM crossings, the FOC controller is much more stable, and can make these forward / reverse jumps with much quicker acceleration (about 25kRPM/s vs 14kRPM/s). This could improve position locking or increase accuracy for delicate maneuvers. 
3. *Ludicrous mode*; The FOC controller's overmodulation feature can push the thruster faster than the Basic ESC for the same input voltage, about 100 more RPM at 12V. Since thrust is proportional to the square of the RPM, this extra 100 RPM is a nice power boost.

# Motor Controller PCB
The motor controller PCB design was created using KiCAD. It's a 4 layer board, approximately in the shape of a xx diameter circle. The notches in the design allow it to be dropped in a mount for the T200 thruster. The PCB project is located in "hardware/Thruster_Controller_V2". An older version of the controller is found in "hardware/Thruster_Controller_V1", with the main difference being a different TI microcontroller.

![PCB Angled](https://github.com/mark-belbin/motor-controller/blob/master/docs/images/pcb_angle.png)

> FOC Thruster Controller V2 Angled View

The board itself is dense, and probably could have benefitted from a 6 layer design instead. However, limiting the design to 4 layers keeps the prototype costs very cheap. In total, for an order of 10 PCBAs, the total cost for the boards were about $2 each thanks to JLCPCB, and the total component cost is about $36.50 per board. So in total, less than $40 CAD per PCBA for only a 10 order quantity, not bad! At scale, this can shrink further, but probably not less than $25 per board.

Some major components are:
- TMS320F280041C -> TI microcontroller with InstaSPIN.
- DRV8320S -> Motor driver from TI.
- SIZF906DT -> Dual-MOSFETs in a compact package
- ATA6561 -> CAN Transceiver

# Controller Firmware
The controller firmware is based on MotorControl SDK 3.01 from TI. This SDK enables sensorless FOC with select TI microcontrollers. The microcontrollers have a proprietary InstaSPIN sensorless algorithm embedded in the ROM, which restricts this system to compatible TI MCUs only. 

The code is modified from a MotorControl SDK example lab, with extra drivers written for CAN communication. There is also some modification to disable a built-in overcurrent feature using the CMPSS. For whatever reason the feature seems to be bugged. I haven't yet figured out a good solution to either fix it or replace the overcurrent protection. So take caution if using this project as a base for something else! 

The IDE used is TIs Code Composer Studio, a customized version of Eclipse. The most up-to-date project is found in "firmware/TI_ESC_V2". The project is completely separated from TIs MotorControl SDK libraries, so it should be portable and importable in to Code Composer Studio from any computer with/without MotorControl SDK installed.


# T200 Thruster Mount
The motor controller PCBA was designed to be integrated into the back of the T200. The PCBA is first placed in an aluminum mount. Then, the thruster phase wires are soldered to the PCB. These wires are exposed by hacking away the jacket of the thruster very delicately. A new 10-conductor cable is then soldered to the PCB, replacing the original thruster cable. The final assembly is then potted, and mounted to the back of the thruster using the existing two screw holes originally for the back nose-cone. With this integration, the controller is water-cooled by the the thruster itself as water is forced passed it. 


![CNC Mounts](https://github.com/mark-belbin/motor-controller/blob/master/docs/images/CNC_mounts.PNG)

> Fresh-cut aluminum PCBA mounts

![Controller Mount](https://github.com/mark-belbin/motor-controller/blob/master/docs/images/PCBA_and_mount.PNG)

> Anodized mount + PCBA

An interesting aspect of the mount design is the inclusion of a sealing disk. This disk, plus an o-ring, seals a programming port on the controller. This allows for reprogramming of the TI microcontroller while still maintaining water resistance. In the future it might be nice to include a bootloader on the microcontroller, which would allow programming over CAN instead, eliminating the need for this extra sealing disk! 


![T200 + Controller Angled](https://github.com/mark-belbin/motor-controller/blob/master/docs/images/T200_and_mount.PNG)

> T200 + Controller Angled View

![T200 + Controller Top](https://github.com/mark-belbin/motor-controller/blob/master/docs/images/T200_and_mount_top_view.PNG)

> T200 + Controller Top View


# AUV Integration

An immediate application of the FOC thruster controller was in my final-year engineering senior design project; an autonomous underwater vehicle (AUV). The AUV includes six thrusters in the design, and I built an FOC controller in each one. In the end, the project was a resounding success, and a very good test scenario for the custom controllers. The controllers were smooth, operating well at low speeds, which is all the AUV needed. The thrusters also operated very quietly, even when pushing the AUV to higher speeds for fun. 

![AUV Top](https://github.com/mark-belbin/motor-controller/blob/master/docs/images/AUV_2.PNG)

> Capstone AUV Top View

![AUV Bottom](https://github.com/mark-belbin/motor-controller/blob/master/docs/images/AUV_1.PNG)

>  Capstone AUV Bottom View

Check out the AUV in action here -> https://www.youtube.com/watch?v=-c5bOXZom5M


# Repository Content
The repository is organized into 3 categories; hardware, firmware, and docs. Included in the hardware folder is the latest FOC controller V2, as well as an older version V1, and many test boards built to test and evaluate the project along the way. The firmware folder includes the latest V2 firmware, as well as the V1 firmware and sample test projects that were provided by TI and were useful for debugging. 
