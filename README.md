# Self Driven Vacuum Cleaner

In this Project we have designed a self driven vacuum cleaning robot. The body of the robot is made of PVC cut in a circular shape. The robot moves around the house, detects and avoids obstacles, takes a random walk around the room and all the while uses a vacuum cleaning unit to clean dust off the floor. The robot uses a sonar sensor to detect and avoid obstacles and gear motors to drive itself. Two gear motors motorize two 65 mm wheels. A caster ball is used to assist in movement. The three wheels are placed approximately 120 degrees apart around the circumference of the circular body.

### Required Equipment

- PVC Board (2'x 2')
- 2 ATmega32 microcontrollers
- 1 Sonar (HC-SR04)
- 2 Gear Motors (rated 5V, 300 rpm)
- 2 Lithium Polymer Batteries (3 x 3.7V each)
- 1 Motor Driver (L298N)
- 1 Bluetooth Module (HC05)
- 1 Vacuum Suction Pump (rated 12V)
- 2 Bread Boards
- 2 Wheels(65mm)
- 1 Caster Ball
- Lots of Wires

### Connections


Our project has two units of connections and wiring with the two Atmega32's - the sonar unit and the motor unit.

1. **Sonar Unit:** The sonar unit consists of one bread board, one Atmega32 and a HC-SR04 sonar. The four pins on the sonar are connected appropriately to the VCC, Ground, Trigger port and Echo interrupt on the Atmega32. This allows the sonar to communicate to and fro with the Atmega32. The sonar is placed centrally directly above the caster ball.
2. **Motor Unit:** The motor unit consists of one bread board, containing the Atmega32 that drives the motors. The Atmega32 is connected to the two gear motors through the motor driver. The Atmega32 sends pulse width modulation waves through the configured enable pins and direction control signals through the direction control pins. The motor driver unit is powered by one of the two Lithium Polymer batteries used for the project. The motor driver has a 5V source output which we use to power both the Atmega32 units. In addition to all this, we have a HC05 bluetooth module interfaced with this Atmega32, which we can use in association with an Android app from a phone to initialize the motor speed, set driving speed, set turning speed, start operation and stop operation remotely.

### Integration

The integration between the two Atmega32 units includes one wire from the sonar unit Atmega32 to the motor unit Atmega32. The wire is used to send an interrupt to the motor unit Atmega32 upon detection of an obstacle by the sonar unit Atmega32. This allows the robot to stop, turn and thus avoid collisions with obstacles.

### Operation

- **Obstacle Detection:** To detect obstacle using the sonars, we used polling. The reason we didn't go for interrupts for the detection is because the sonar unit Atmega32 does not have any other function that can be stalled by the use of polling. The Atmega32 sends a trigger signal or a high 5V on the trigger pin of the sonar. The sonar upon receiving a high input continuously for 10 micro seconds on the Trigger pin sends out a sound wave and immediately sets the Echo pin output to be high. Upon receiving the reflected sound wave, it sets the Echo pin output to be low. The interval between these consevutive highs and lows can be used to calculate the distance of an object infront of the sonar. For the polling we used 30 cm as our intended distance of detection. So the sonar unit Atmega32 generated an interrupt for the motor driver unit Atmega32 upon detecting any object within 30 cm of the sonar.
- **Motor Control:** To control the gear motors we sent pulse width modulated signals to the two enable pins of the motor driver. The signal is basically an amount of voltage that changes in proportion with the speed set for the motor. We used 60% of the max speed of the motors as the operational driving speed and 50% of the max speed as the turning speed. Upon receiving an interrupt from the sonar unit Atmega32, the motor driver unit Atmega32 immediately sets the rotation control pins to be 00, which is the mode for stalling or halting the motor. After that it reverses the direction of motor to run the robot back a few inches and then turns left as a preset. The turn degree is randomized since we wanted to execute a random walk. The reason for the reversal of direction for a few inches is to avoid collision with corners. After executing the turn, the robot resumes normal operation.
- **Vacuum Control:** The vacuum pump is a 12V vacuum cleaning unit that we bought from the market. Since this was a prototype we didn't bother making our own compressor-suction unit. We powered this unit with one of the two Lithium Polymer batteries used for the project. The suction pump is constantly on for the entire duration of an operational session.
- **Remote Control:** We used a bluetooth module (HC05) to remotely initialize the motor pins, set turning speed, set driving speed and also stop the motor. We used USART communication to transmit speed as a percentage of the max speed. So our transmission was a 4 character string of the form cSSS where c can be 'i' for initialization or 's' for start driving. SSS stands for a percentage of the speed from 0 to 100%. There is another single character transmission where we transmit the character 'z' to tell the robot to stop immediately. This is used to end a vacuuming session remotely.

### Block Diagram

![]()

### Algorithm

1. Start

2. Turn on vacuum unit

3. Turn on motor driver switch

4. Pair android app with bluetooth module

5. Initialize motor driver pins

6. Start operation

7. Operational block

8. 1. Start motor

   2. Obstacle within 30 cm?

   3. 1. Yes : Go to step iii
      2. No : Go to step viii

   4. Stop motor

   5. Reverse direction and drive for 500 ms

   6. Stop motor

   7. Turn left for 500 ms

   8. Stop motor

   9. Received stop signal?

   10. 1. Yes : Go to step 8
       2. No : Go to step i

9. Stop motor

10. Stop

### Problems Faced

1. Initially we had to face a lot of problems to figure out the speed control mechanism for our gear motors. Even though the pulse width modulation allows us to send voltage from 0V to 5V and therefore should allow for a speed control range of 0 to 100%, in practicality the motors fail to drive the vehicle at speeds less than 50%. We assume it is because of the weight of the robot.
2. During operation, the two motors don't always perform optimally and as a result, the speeds vary. This causes the robot to sometimes not drive in a straight line and rather drift off to one side. We thought of incorporating hall sensors to accurate control rotations and therefore ensure linear traversal and accurate turning mechanisms, but due to shortage of time we decided to opt out of that idea.
3. The vacuum unit draws a large current. While initial testing we used jumper wires to power the unit and it ended in the wires being burnt to a crisp. We decided to use copper wires to avoid this in subsequent trial runs.
4. We had a hard time eliminating garbage transmission in the bluetooth module, since we didn't know proper baud rate settings. Later on we figured out what was wrong and set the proper baud rate and achieved garbage free transmission.

### Group Members Information

- Aniruddha Ganguly
- Anisha Islam
- Najrin Sultana
- Zahin Ahmed