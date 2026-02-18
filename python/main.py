import serial
import time

ser = serial.Serial("COM6", 115200)
time.sleep(5)

# ser.write(b"M 1000 5000000\n")
# ser.write(b"M 1000 2000000\n")
# ser.write(b"M 1000 7000000\n")
bad = []
for i in range(50, 1000, 5):
    ser.write(bytes(f"M {(1000 - i) * 22 // 10} 1000000\n", encoding="utf8"))
    a = input()
    if a == "n":
        bad.append(i)

print(bad)
