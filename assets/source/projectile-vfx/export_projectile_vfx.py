from pathlib import Path

from PIL import Image


ROOT = Path(__file__).resolve().parents[3]
SOURCE = Path(__file__).with_name("projectile-impact-source.png")
OUTPUT = ROOT / "assets" / "textures" / "projectile_impact.png"
FRAME_SIZE = 64
COLS = 4
ROWS = 2


def main() -> None:
    source = Image.open(SOURCE).convert("RGBA")
    sheet = Image.new("RGBA", (FRAME_SIZE * COLS * ROWS, FRAME_SIZE), (0, 0, 0, 0))

    frame_index = 0
    for row in range(ROWS):
        top = round(row * source.height / ROWS)
        bottom = round((row + 1) * source.height / ROWS)
        for col in range(COLS):
            left = round(col * source.width / COLS)
            right = round((col + 1) * source.width / COLS)
            frame = source.crop((left, top, right, bottom)).resize(
                (FRAME_SIZE, FRAME_SIZE), Image.Resampling.NEAREST
            )
            pixels = frame.load()
            for y in range(FRAME_SIZE):
                for x in range(FRAME_SIZE):
                    red, green, blue, alpha = pixels[x, y]
                    pixels[x, y] = (red, green, blue, 255 if alpha >= 96 else 0)
            sheet.alpha_composite(frame, (frame_index * FRAME_SIZE, 0))
            frame_index += 1

    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    sheet.save(OUTPUT, optimize=True)
    print(f"wrote {OUTPUT} ({sheet.width}x{sheet.height}, {frame_index} frames)")


if __name__ == "__main__":
    main()
