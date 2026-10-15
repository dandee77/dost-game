import math
import random
import struct
import wave
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]
OUTPUT = ROOT / "assets" / "sounds" / "bullet_impact.wav"
SAMPLE_RATE = 44_100
DURATION = 0.12
SEED = 7_319


def main() -> None:
    random_source = random.Random(SEED)
    sample_count = round(SAMPLE_RATE * DURATION)
    samples: list[int] = []
    for index in range(sample_count):
        time = index / SAMPLE_RATE
        envelope = math.exp(-34.0 * time)
        snap = random_source.uniform(-1.0, 1.0) * math.exp(-72.0 * time)
        body = math.sin(2.0 * math.pi * (920.0 - 4_100.0 * time) * time)
        shimmer = math.sin(2.0 * math.pi * 2_600.0 * time) * math.exp(-58.0 * time)
        value = max(-1.0, min(1.0, envelope * (0.52 * body + 0.28 * shimmer) + 0.32 * snap))
        samples.append(round(value * 24_000))

    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    with wave.open(str(OUTPUT), "wb") as output:
        output.setnchannels(1)
        output.setsampwidth(2)
        output.setframerate(SAMPLE_RATE)
        output.writeframes(b"".join(struct.pack("<h", sample) for sample in samples))
    print(f"wrote {OUTPUT} ({DURATION:.2f}s mono PCM)")


if __name__ == "__main__":
    main()
