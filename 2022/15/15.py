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

y = 2000000

ranges: list[pair] = []
for sensor in sensors:
    distance = abs(sensor.sensor.a - sensor.beacon.a) + abs(sensor.sensor.b - sensor.beacon.b)
    dy = abs(sensor.sensor.b - y)
    if dy <= distance:
        dx = distance - dy
        ranges.append(pair(sensor.sensor.a - dx, sensor.sensor.a + dx))
ranges = join(ranges)
total = 0
for range in ranges:
    total += (range.b - range.a)
print(total)
