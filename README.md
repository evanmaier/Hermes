# Hermes - Electronic Speed Controller running Sensorless Field-Oriented Control

During the pandemic, many industries were faced with supply shortages; chipset manufacturing was one. With the high demand of hardware and not enough supply, this most hurt smaller companies. Going forward, companies need to develop products such that they aren't heavily relying on chipsets from a single source and use more generic parts.

The purpose of our speed controller, Hermes, is to create a product that can perform better than current solutions, while being built with common componenets for a robust product that is unaffected by supply-chain shortages.

## Project Requirements

- Simulate the sensorless FOC algorithm using MATLAB
- Design a simple GUI/Terminal for communicating with the ESC
- A website to market the product
- Design and build a prototype.
- Compare performance to alternative products.

## Specifications:

- Current: 30A to 40A
- Voltage: 8.4 - 25.2V
- SBEC: 3A/12V
- Dimensions: TBD
- Weight: TBD

## Features:

- ARM Cortex-M4 MCU
- Programmable
- On-board Temperature Sensor
- Multiple Communication methods: PWM, USB, CAN
- LED Fuse Indicator
- Stalled Motor Protection
- Safe power-on (throttle lockout)
- Current Limiting
- Smooth and linear throttle control
- Fast response to throttle input
- Brake
- Buzzer Alert

### Future Features:
- Stepper-Motor feature
- Field Weakening control (increase max speed while decreasing torque)
- Regenerative braking


## BLDC-Under-Test

Hermes will be run on a [Multi-star Turnigy 3508-580 ](https://hobbyking.com/en_us/3508-580kv-turnigy-multistar-14-pole-brushless-multi-rotor-motor-with-extra-long-leads.html?___store=en_us) by hobbyking. This is a common quadcopter motor.
![BLDC](./resources/Images/Screenshot%202023-06-05%20153641.png)