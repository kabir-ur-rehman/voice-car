import requests
import time
import sounddevice as sd
import queue
import json
from vosk import Model, KaldiRecognizer

# -------------------- BLYNK SETUP --------------------
BLYNK_TOKEN = "-1jX90yi-D-vBdwzcMJonl88THQf92R8"
BLYNK_URL = f"http://blynk.cloud/external/api/update?token={BLYNK_TOKEN}"

# -------------------- LOAD VOSK MODEL --------------------
model = Model(r"C:\Users\A1\Desktop\New folder\vosk-model-small-en-us-0.15")
rec = KaldiRecognizer(model, 16000)

# -------------------- SHORT COMMANDS --------------------
commands = {
    "go": "V1",
    "back": "V2",
    "left": "V3",
    "right": "V4",
    "spin": "V5",
    "beep": "V6",
    "stop": "V0"
}

# -------------------- SEND COMMAND FUNCTION --------------------
def send_command(action):
    if action in commands:
        url = f"{BLYNK_URL}&{commands[action]}=1"
        requests.get(url)
        print(f"✅ Command Sent: {action}")

        # auto stop only for short actions
        if action in ["left", "right", "beep"]:
            time.sleep(0.5)
            requests.get(f"{BLYNK_URL}&{commands[action]}=0")
    else:
        print("❌ Invalid Command")

# -------------------- VOICE RECOGNITION SETUP --------------------
q = queue.Queue()

def callback(indata, frames, time_, status):
    if status:
        print(status)
    q.put(bytes(indata))

# -------------------- MAIN LOOP --------------------
print("🎤 Mic ready... bolo: go, back, left, right, spin, beep, stop (exit to quit)")

with sd.RawInputStream(samplerate=16000, blocksize=4000, dtype="int16",
                       channels=1, callback=callback):
    buffer_data = b""
    while True:
        try:
            # accumulate data
            while not q.empty():
                buffer_data += q.get()

            if rec.AcceptWaveform(buffer_data):
                result = json.loads(rec.Result())
                buffer_data = b""  # clear buffer after processing
            else:
                result = json.loads(rec.PartialResult())

            command = result.get("partial", "").lower() or result.get("text", "").lower()
            if command:
                print("🎧 You said:", command)

                if "go" in command:
                    send_command("go")
                elif "back" in command:
                    send_command("back")
                elif "left" in command:
                    send_command("left")
                elif "right" in command:
                    send_command("right")
                elif "spin" in command:
                    send_command("spin")
                elif "beep" in command:
                    send_command("beep")
                elif "stop" in command:
                    send_command("stop")
                elif "exit" in command:
                    print("👋 Exiting program...")
                    break

            time.sleep(0.1)  # check buffer every 0.1 sec for faster response

        except KeyboardInterrupt:
            print("👋 Exiting program...")
            break
