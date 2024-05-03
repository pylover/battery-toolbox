#! /usr/bin/env python3


def calcv(r1, r2, v, vref, vmax):
    r = r1 + r2
    c = v / r
    print(f"VDD:               {v:8.4f} V")
    print(f"Current:           {c * 1000000:8.4f} µA")
    print(f"R1 voltage:        {c * r1:8.4f} V");
    print(f"R2 voltage:        {c * r2:8.4f} V");
    print(f"ADC read value:    {int(c * r2 * 1023 / vref):8d}");
    print()


def calc(r1, r2, vref, vmax):
    calcv(r1, r2, 1, vref, vmax)
    calcv(r1, r2, vmax / 2, vref, vmax)
    calcv(r1, r2, vmax, vref, vmax)
    print()
    print(f"ADC resolutino({vmax}V/1023):   {vmax / 1023:9.4f} V")
    print(f"R1:                             {r1:9.4f} Ω");
    print(f"R2:                             {r2:9.4f} Ω");


if __name__ == '__main__':
    # calc(20000, 6190, 4.8, 16.384)
    # calc(44200, 13000, 4.85, 16.384)
    calc(10000, 2800, 4.85, 16.384)


"""
# 1% resistors

10
100
301
1K
2.15K
2.8K
10K
13K
20K
44.2K
100K
200K
"""
