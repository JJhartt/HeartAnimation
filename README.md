# Arduino LED Matrix Controller
A project for controlling the Arduino LED Matrix through serial commands. This code allows you to display, animate, and manipulate patterns on the matrix with simple text commands.

# Features
Display predefined patterns

Turn the matrix on/off

Invert displayed pattern (swap)

Animate patterns with left and right shifting

Serial command interface

Hardware Requirements
Arduino board with LED Matrix (e.g., Arduino UNO R4 WiFi)

Arduino_LED_Matrix library

Installation
Connect your Arduino board to your computer

Install the Arduino_LED_Matrix library via the Arduino Library Manager

Upload this sketch to your board

Open the Serial Monitor (set to 9600 baud)

# Usage
After uploading the code, open the Serial Monitor and send one of the following commands:

On - Display the predefined pattern

Off - Clear the matrix

Swap - Invert the displayed pattern

Left - Start left-shifting animation

Right - Start right-shifting animation

For animations, type any character in the Serial Monitor to stop the animation.

Code Overview
The project uses bit manipulation to control the 12×8 LED matrix. Key functions include:

HexBin(): Converts hexadecimal frame data to binary strings

BinHex(): Converts binary strings back to hexadecimal format

Animate_Right(): Shifts the pattern to the right

Animate_Left(): Shifts the pattern to the left

# Examples
Animation Demo

![Turning On](On.gif)

![Turning Off](Off.gif)



![Animating Left](LeftMove.gif)

![Animating Right](RightMove.gif)



Pattern Inversion Demo

![Swapping Indicies](Swap.gif)

Circuit Diagram
No external wiring is needed as this uses the built-in LED matrix on compatible Arduino boards.

Customization
You can modify the frame array to create your own patterns:

uint32_t frame[] = {   
  0x3184a444,   // Modify these values
  0x42081100,   // to create your
  0xa0040000    // own patterns
};

License
This project is open source and available under the MIT License.
