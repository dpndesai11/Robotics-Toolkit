import serial
import sys
import tty
import termios
import time

# Open connection to the Arduino
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=0.1)
time.sleep(2) 

def get_keystroke():
    """ Captures keystrokes instantly without needing to press Enter """
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

print("--- Stanley Direct Keyboard Drive ---")
print("[w]=Forward, [s]=Backward, [a]=Slower, [d]=Faster, [x]=Stop, [q]=Quit Application\n")

try:
    while True:
        key = get_keystroke()
        if key == 'q':
            ser.write(b'x') # Turn off motor before quitting
            print("\nExiting controller script.")
            break
        elif key in ['w', 's', 'x', 'a', 'd']:
            ser.write(key.encode())
            time.sleep(0.05)
            if ser.in_waiting > 0:
                feedback = ser.readline().decode('utf-8').strip()
                print(f"\r{feedback}       ", end="", flush=True)
except KeyboardInterrupt:
    ser.write(b'x')
finally:
    ser.close()