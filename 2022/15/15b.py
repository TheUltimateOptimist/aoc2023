from util import read, pair, join, numbers
from dataclasses import dataclass

@dataclass(frozen=True)
class Sensor:
    sensor: pair
    beacon: pair

sensors: list[Sensor] = []
lines = read().splitlines()
for line in lines:
    values = numbers(line)
    sensor = Sensor(
        pair(values[0], values[1]),
        pair(values[2], values[3])
    )
    sensors.append(sensor)

def y_ranges(y: int) -> list[pair]:
    ranges: list[pair] = []
    for sensor in sensors:
        distance = abs(sensor.sensor.a - sensor.beacon.a) + abs(sensor.sensor.b - sensor.beacon.b)
        dy = abs(sensor.sensor.b - y)
        if dy <= distance:
            dx = distance - dy
            ranges.append(pair(sensor.sensor.a - dx, sensor.sensor.a + dx))
    ranges = join(ranges)
    return ranges

for i in range(4_000_001):
    ranges = y_ranges(i)
    if len(ranges) > 1:
        print((ranges[0].b + 1)*4_000_000 + i)
        break