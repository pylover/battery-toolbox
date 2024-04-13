#! /usr/bin/env python3


def calc(v, zv, zw, rs):
    cmax = zw / zv
    rsmax = (v - zv) / cmax
    print()
    print(f"VDD:              {v:9.4f} V")
    print(f"Current(max):     {cmax:9.4f} A")
    print(f"RS(min):          {rsmax:9.4f} Ω");
    print(f"RS voltage(max):  {rsmax * cmax:9.4f} V");

    c = (v - zv) / rs
    print(f"RS:               {rs:9.4f} Ω")
    print(f"Power:            {c * zv:9.4f} W")
    print(f"Current:          {c:9.4f} A")


if __name__ == '__main__':
    # rs = 150
    # calc(5, 2.2, .5, rs)
    rs = 22
    calc(5, 4.7, .5, rs)
