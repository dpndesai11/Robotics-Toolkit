# Robotics-Toolkit

A minimal toolkit for driving a DC motor with an Arduino and an H-bridge motor driver, controlled live from a keyboard over a serial connection.

The project has two halves:

- **`DC_Motorcontrol.ino`** — Arduino sketch that reads single-character commands over serial and drives a DC motor's direction and speed through an enable/direction (H-bridge) driver.
- **`Motorcontol.py`** — Python script that captures keystrokes on your computer and streams them to the Arduino over a serial port, printing back the motor's live status.

## Hardware

- Arduino (Uno or similar)
- DC motor
- H-bridge motor driver (e.g. L298N) wired to:
  - `enablePin` → pin 5 (PWM, speed control)
  - `in1Pin` → pin 4 (direction)
  - `in2Pin` → pin 3 (direction)
- USB cable from Arduino to the controlling computer

See `motor_control_circuit.png` in this repo for the wiring diagram.

## Setup

1. Open `DC_Motorcontrol.ino` in the Arduino IDE and upload it to your board.
2. On the computer that will send commands, install the Python serial dependency:

   ```
   pip install pyserial
   ```

3. In `Motorcontol.py`, update the serial port to match your system:
   - Linux: `/dev/ttyACM0` (default in the script)
   - macOS: `/dev/cu.usbmodemXXXX`
   - Windows: `COMx`

## Usage

Run the controller script:

```
python Motorcontol.py
```

Control the motor with the keyboard (no need to press Enter):

| Key | Action |
| --- | --- |
| `w` | Drive forward |
| `s` | Drive backward |
| `d` | Increase speed |
| `a` | Decrease speed |
| `x` | Stop |
| `q` | Quit and stop the motor |

The Arduino echoes back its current direction and speed after each command, which the Python script prints to the terminal in real time.

## License

MIT — see `LICENSE`.
