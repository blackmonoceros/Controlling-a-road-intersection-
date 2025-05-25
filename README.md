# Controlling-a-road-intersection-

## Project Description

Controlling a road intersection with a semaphore enriched with pedestrian signaling and displaying the text:


The project was created in the **TINKERCAD** environment according to the command of the following experiment:

> Design a “real traffic light” in which traffic lights are switched in accordance with the following rhythm.  
> In addition, a pedestrian button will be introduced. It will switch additional lights for pedestrians, i.e. red/stop and green/go.  
> When pressed, the pedestrian clearway request button will interrupt the sequence of main light changes and light the pedestrian clearway.

---

## Sequence of Operation

1. **Initial state:**
   - 🚦 Red light for pedestrians
   - 🚗 Green light for vehicles

2. **Pedestrian button pressed:**
   - 🚦 Red light for pedestrians
   - 🚗 Yellow light for vehicles _(5 seconds)_

3. **Next change:**
   - 🚦 Green light for pedestrians
   - 🚗 Red light for vehicles _(6 seconds)_

4. **Restoring sequence:**
   - 🚦 Red light for pedestrians
   - 🚗 Red and yellow light for vehicles _(about 2 seconds)_

5. **Return to normal sequence:**
   - 🚦 Red light for pedestrians
   - 🚗 Green light for vehicles

---

## ADDITIONAL

- Extend the above experiment to control the intersection with a light semaphore enriched with pedestrian signaling and displaying the words **GO** and **STOP** on a **2x16 LCD display** compatible with the I2C bus.
- It is necessary to implement control with the help of Arduino not only for the pedestrian traffic light (red/green) but also simultaneous display of the message:
    - for red light: `STOP`
    - for green light: `GO`
    - for orange light: `PREPARE TO WALK`

---

**Last update:** May 25, 2025

---
