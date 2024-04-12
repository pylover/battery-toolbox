#! /usr/bin/env python3


def calcv(r1, r2, pot, v, vref, vmax):
    r = r1 + r2 + pot
    c = v / r
    print(f"VDD:               {v:8.4f} V")
    print(f"Current:           {c * 1000000:8.4f} µA")
    print(f"R1 voltage:        {c * r1:8.4f} V");
    print(f"R2 voltage:        {c * r2:8.4f} V");
    print(f"R2 + POT voltage:  {c * (r2 + pot):8.4f} V");
    print(f"ADC input voltage: {v * vref / vmax:8.4f} V");
    print(f"ADC read value:    {int(v * 1024 // vmax):8d}");
    print()


def calc(r1, r2, pot, vref, vmax):
    calcv(r1, r2, pot, 1, vref, vmax)
    calcv(r1, r2, pot, vmax / 2, vref, vmax)
    calcv(r1, r2, pot, vmax, vref, vmax)
    print()
    print(f"ADC resolutino({vmax}V/1024):   {vmax / 1024:8.4f} V")


if __name__ == '__main__':
    # calc(44200, 1000, 1000, 2.2, 30.72)
    calc(20000, 2800, 500, 2.2, 16.384)
    # calc(100000, 10000, 1000, 2.2, 20.48)


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
