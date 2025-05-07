from dotenv import load_dotenv
import os

load_dotenv()

ssid = os.getenv("WIFI_SSID")
password = os.getenv("WIFI_PASSWORD")

with open("env_config.h", "w") as f:
    f.write(f'#define WIFI_SSID "{ssid}"\n')
    f.write(f'#define WIFI_PASSWORD "{password}"\n')
