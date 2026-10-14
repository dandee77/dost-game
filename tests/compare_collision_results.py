"""Compare records produced by the original and optimized real Game loops."""
import difflib
import sys
from pathlib import Path


def main():
    if len(sys.argv) != 3:
        raise SystemExit("Usage: python tests/compare_collision_results.py original.log grid.log")
    before = Path(sys.argv[1]).read_text().splitlines()
    after = Path(sys.argv[2]).read_text().splitlines()
    if len(before) != 480 or before != after:
        for line in list(difflib.unified_diff(before, after, fromfile=sys.argv[1], tofile=sys.argv[2]))[:20]:
            print(line)
        raise SystemExit("FAIL: expected 480 identical real-game collision frames")
    deaths = set()
    for line in after:
        fields = line.split("|")[0].split(":")
        if len(fields) > 8:
            deaths.add(fields[8])
    if deaths != {"0", "1", "2"}:
        raise SystemExit("FAIL: missing enemy-bullet, enemy-contact or debris death coverage")
    print("PASS: 480 identical gameplay frames; all three killer types covered")


if __name__ == "__main__":
    main()
