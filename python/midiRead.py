import matplotlib.pyplot as plt
import time
import mido
from mido import MidiFile, Message, MidiTrack
import serial
import time

ser = serial.Serial("COM6", 115200)
time.sleep(5)

# перевести в полушаговый режим
# настроить частоты

mid = MidiFile("C:\\Users\\Herobib\\Desktop\\11.mid")
current_time = 0

current_time_sec = 0
active_notes = {}
result = []


for msg in mid:
    current_time += msg.time

    if msg.type == "note_on" and msg.velocity > 0:
        active_notes[msg.note] = current_time

    elif msg.type == "note_off" or (msg.type == "note_on" and msg.velocity == 0):
        if msg.note in active_notes:
            start_time = active_notes.pop(msg.note)
            duration = current_time - start_time
            result.append(
                {
                    "start": round(start_time, 3),
                    "MyHg": int((msg.note - (msg.note % 3)) * 7.25),
                    "duration": int(round(duration, 3) * 1000000),
                }
            )

result.sort(key=lambda x: x["start"])

print(f"{'Старт (сек)':<12} | {'Нота':<6} | {'Длительность':<12}")
Hg = []
massTS = []
dur = []
for item in result:
    if item["duration"] > 0.01 * 1000000:
        Hg.append(item["MyHg"])
        massTS.append(item["start"])
        dur.append(item["duration"])

start_time = time.time()
last_note = 0

while True:
    if massTS[last_note] <= time.time() - start_time:
        print(
            bytes(
                f"M {(750 - Hg[last_note]) * 22 // 10} {dur[last_note]}\n",
                encoding="utf8",
            )
        )
        ser.write(
            bytes(
                f"M {(1000 - (Hg[last_note])) * 14 // 10} {dur[last_note]}\n",
                encoding="utf8",
            )
        )
        last_note += 1
