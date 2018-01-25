# encoderCoprocessor
Uses an Arduino UNO to monitor up to 6 quadrature encoders and send data over SPI to the main processor.

This code was created to fulfil the requirements in the following problem:

You are involved with designing the control system of a 6-DOF robot arm. The arm is driven by 6 DC motors, each with a quadrature encoder to measure relative position. The central control unit is a small System-on-a-chip that does not have the capabilities to manage all those simultaneous interrupt signals. Please design the circuitry for a daughter board to process these signals and relay to the main chip the positions over SPI. Assume a resolution of 100 ticks per degree and as much as 3 Pi/2 radian of rotation on a single joint. The joints can rotate at up to 2 radians per second. Please draw out your circuit. It can be be hand drawn or computer tools may be used. You may use any commercial off the shelf parts. Please provide links to datasheets. If you use any microcontrollers or programmable logic devices, please provide the code used.
