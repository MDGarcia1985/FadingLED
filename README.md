# FadingLED
Potentiometer with LEDs
# **Fading LEDs Project**

## **Project Overview**
The **Fading LEDs** project demonstrates the control of LED brightness using both hardware and software PWM, alongside an interrupt-driven blinking mechanism. The project is coded in C++ and is compatible with Arduino IDE, Atmel Studio, and Visual Studio 2022.

The project achieves the following:
1. **Port D LEDs (Pins 2–7)** fade in and out, controlled by a potentiometer.
2. **Port B LEDs (Pins 8 and 9)** blink at a 1-second interval, independent of Port D fading.

---

## **Hardware Components**
1. **Arduino Uno R3**
2. **8 LEDs**
3. **8 Resistors (220Ω)**
4. **Potentiometer (10kΩ)**
5. **Breadboard**
6. **Connecting Wires**

---

## **Hardware Setup**
### **Pin Connections**
| **Component** | **Arduino Pin** | **Description**                     |
|---------------|------------------|-------------------------------------|
| LED1          | PD6 (Pin 6)      | Fading with hardware PWM            |
| LED2          | PD5 (Pin 5)      | Fading with hardware PWM            |
| LED3          | PD4 (Pin 4)      | Fading with software PWM            |
| LED4          | PD3 (Pin 3)      | Fading with software PWM            |
| LED5          | PD2 (Pin 2)      | Fading with software PWM            |
| LED6          | PD7 (Pin 7)      | Fading with software PWM            |
| LEDB1         | PB0 (Pin 8)      | Blinking LED                        |
| LEDB2         | PB1 (Pin 9)      | Blinking LED                        |
| Potentiometer | A0               | Adjusts brightness for Port D LEDs  |

### **Power and Ground**
- Potentiometer Pin 1 → 5V
- Potentiometer Pin 3 → GND
- Wiper → A0

---

## **Functional Requirements**
1. LEDs on **Port D (Pins 2–7)**:
   - Fades in and out based on the potentiometer input.
   - **Hardware PWM** on Pins 5 and 6 provides smooth fading.
   - **Software PWM** on Pins 2–4 and 7 approximates fading.

2. LEDs on **Port B (Pins 8 and 9)**:
   - Blink at a 1-second interval using a timer interrupt.
   - Blinking occurs at half brightness.

3. **Concurrency**:
   - Fading and blinking operate independently without interfering.

---

## **Code Description**
### **Key Features**
- **Hardware PWM**:
  - Smooth brightness transitions on Pins 5 and 6.
- **Software PWM**:
  - Simulates PWM on non-PWM pins (Pins 2–4, 7).
- **Timer Interrupt**:
  - Uses Timer1 to blink LEDs on Port B.

### **Included Libraries**
- `<Arduino.h>`: Core Arduino functions.
- `<avr/interrupt.h>`: Enables and manages interrupts.

---

## **How to Use**
1. **Upload the Code**:
   - Load the project onto the Arduino using a compatible IDE.
2. **Adjust Brightness**:
   - Turn the potentiometer to control the fade of Port D LEDs.
3. **Observe Blinking**:
   - LEDs on Port B blink independently of fading.

---

## **Troubleshooting**
- **All LEDs on Port D Are Steady**:
  - Check potentiometer wiring (5V, GND, and wiper to A0).
- **No Blinking on Port B**:
  - Verify timer setup in the code.
- **Port D LEDs Blinking**:
  - This is expected behavior for non-PWM pins using software PWM.

---

## **Known Limitations**
- Software PWM introduces slight blinking artifacts on non-PWM pins.
- Hardware PWM pins (5 and 6) fade smoothly without issues.

---

## **Future Improvements**
- Replace non-PWM pins with hardware PWM-capable pins for smooth fading.
- Enhance software PWM timing for reduced blinking artifacts.
- Add user-adjustable blinking intervals via another potentiometer.

---

## **Conclusion**
The **Fading LEDs** project successfully integrates PWM and timer interrupts to create an interactive lighting demonstration. Despite minor artifacts on non-PWM pins, the system achieves the intended functionality, showcasing concurrent operation of fading and blinking LEDs.

