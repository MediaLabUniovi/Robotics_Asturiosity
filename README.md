<div align="right">

[![english](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/gb.png)](./README.md) | [![spanish](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/es.png)](./README_ES.md)

</div>


# Asturiosity - 3D Printed Rover 🚀

The **Asturiosity** project focuses on developing a 3D-printed exploration rover at the scale of the Perseverance rover. This project allows both advancements in the knowledge of robotic systems within the university community, as well as the dissemination and creation of educational activities related to space exploration.

## Features

- **3D Printed Rover**: The rover is primarily built using 3D-printed components, making it accessible and customizable for anyone interested in building their own exploration robot.
- **Arduino Mega 2650**: The rover is powered by an Arduino Mega 2650 microcontroller, providing ample capacity for controlling sensors and actuators.
- **Remote Control**: Equipped with a **FlySky FS-i6X 10ch + RX ia6b** remote control system for wireless navigation.
- **Power Supply**: Uses **3S batteries** to provide the necessary energy to the rover's motors and electronic components.
- **Educational Outreach**: The project includes educational activities for schools, where students can learn about robotics and space exploration through hands-on experience.

## Hardware Requirements

- **Arduino Mega 2650** microcontroller
- **FlySky FS-i6X 10ch** remote controller and **RX ia6b** receiver
- **3S batteries** for powering the rover
- 3D-printed components (files and instructions available in the repository)
- Motors, sensors, and other electronics as detailed in the project documentation

## Software Requirements

- **Arduino IDE** or any compatible platform for programming the Arduino Mega 2650
- Required libraries:
  - `Servo.h`: For controlling the rover's motors
  - Additional libraries based on the sensors and actuators used in the project

## Installation

1. **Clone the repository**:

   Clone this repository to your local machine using:

   ```bash
   git clone https://github.com/MediaLabUniovi/Asturiosity.git
   ```

2. **Set up the environment**:

   Open the project in **Arduino IDE** and install any required libraries for the rover's operation.

3. **3D Print the Components**:

   Follow the instructions in the repository to print the necessary parts for assembling the rover.

4. **Connect your hardware**:

   Assemble the rover using the 3D-printed parts, and connect the **Arduino Mega 2650**, **FlySky FS-i6X**, and other electronics according to the wiring diagram provided.

5. **Upload the code**:

   Upload the control software to the **Arduino Mega 2650** using the Arduino IDE.

## Usage

1. **Power on the rover**: 

   Turn on the 3S batteries to power the rover and establish communication with the FlySky remote control.

2. **Control the rover**:

   Use the **FlySky FS-i6X** to control the rover's movement and explore various terrains, simulating the missions carried out by the real Perseverance rover.

3. **Educational outreach**:

   The **Asturiosity** project is designed to be a tool for educational outreach in schools. Students can interact with the rover and learn about robotics and space exploration in an engaging way.

   <img src="https://github.com/MediaLabUniovi/Asturiosity/blob/master/img/asturiosity.png" alt="Asturiosity" width="300"/>

## About the Educational Outreach 🌍

The **Asturiosity** project plays an essential role in **educational outreach** by introducing students to the world of robotics and space exploration. By engaging with the rover, students can learn about complex concepts such as robotic systems, sensors, and wireless communication in a hands-on environment. The project is also open to collaboration with schools and educational institutions, promoting STEM education through interactive activities.


## About MediaLab Uniovi

<img src="https://pbs.twimg.com/profile_images/1116343775171891205/ZMsvYRrG_400x400.png" alt="MediaLab Uniovi Logo" width="200"/>

**MediaLab Uniovi** is a university laboratory of technology and design that was created in 2018 as a result of a collaboration between the **City Council of Gijón**, **Gijón Impulsa**, and the **University of Oviedo**. Its mission is to bring new technologies and project creation methodologies closer to people. MediaLab is based at the **School of Engineering of Gijón** and works to foster technological innovation and creativity.

## How to Contribute

Contributions to the Asturiosity project are welcome! Whether you want to improve the rover's design, add new features, or share your own educational resources, feel free to open a **pull request** or create an **issue** in this repository.

## License

This project is licensed under the [MIT License](LICENSE).
