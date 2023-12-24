# flip flop starts with % | on or off | initially off | off -> sends high pulse | ignores high pulses  on -> sends low pulse
# conjunction modules start with & | initially remembers low pulse for all inputs 
# if remembers high pulse for all inputs -> sends low pulse else sends low pulse
# broadcaster sends received pulse to all destinations

from dataclasses import dataclass
from abc import ABC

@dataclass
class Broadcaster(ABC):
    destinations: list[str]

@dataclass
class FlipFlop(Broadcaster):
    on: bool = False

@dataclass
class Conjunction(Broadcaster):
    # 0 -> low pulse , 1 -> high pulse
    inputs: dict[str, int]

from util import read

initial: dict[str, Broadcaster] = {}
working: dict[str, Broadcaster] = {}

start_pulses: list[tuple[str, str, int]] = []

# parse input
for line in read().split("\n"):
    name = line.split("->")[0].strip()
    if name[0] in "%&":
        name = name[1:]
    destinations = line.split("->")[1].strip().split(", ")
    if line.startswith("broadcaster"):
        for destination in destinations:
            start_pulses.append(("broadcaster", destination, 0))
    elif line.startswith("%"):
        initial[name] = FlipFlop(destinations)
        working[name] = FlipFlop(destinations)
    elif line.startswith("&"):
        initial[name] = Conjunction(destinations, {})
        working[name] = Conjunction(destinations, {})


# intialize conjunctions
for key in initial:
    conjunction = initial[key]
    if not isinstance(conjunction, Conjunction):
        continue
    for sec_key in initial:
        if sec_key != key and key in initial[sec_key].destinations:
            conjunction.inputs[sec_key] = 0
    working[key] = conjunction

cycles: dict[str, dict[str, list[tuple[int, int]]]] = {
    "hb": {},
    "hf": {},
    "dl": {},
    "lq": {}
}

for key in cycles.keys():
    conjunction = working[key]
    assert isinstance(conjunction, Conjunction)
    for c_key in conjunction.inputs.keys():
        cycles[key][c_key] = [(0, 0)]

def count_pulses(iteration: int) -> None:
    global start_pulses
    pulses = start_pulses 
    while len(pulses) > 0:
        new_pulses: list[tuple[str, str, int]] = []
        for pulse in pulses:
            module = working.get(pulse[1])
            # print(module)
            if isinstance(module, FlipFlop) and pulse[2] == 0:
                new_pulse = int(not module.on)
                module.on = not module.on
                for destination in module.destinations:
                    new_pulses.append((pulse[1], destination, new_pulse))
            elif isinstance(module, Conjunction):
                module.inputs[pulse[0]] = pulse[2]
                #if pulse[1] in cycles.keys() and pulse[2]:
                     #if len(cycles[pulse[1]][pulse[0]]) < 6:
                        #cycles[pulse[1]][pulse[0]].append(iteration) 
                all_high = True
                for key in module.inputs.keys():
                    if not module.inputs[key]:
                        all_high = False
                        break
                for destination in module.destinations:
                    new_pulses.append((pulse[1], destination, int(not all_high)))
        pulses = new_pulses
    for key in cycles.keys():
        for c_key in cycles[key].keys():
            conjunction = working[key]
            assert isinstance(conjunction, Conjunction)
            rel_list = cycles[key][c_key]
            if conjunction.inputs[c_key] != rel_list[-1][1] and len(rel_list) < 10:
                cycles[key][c_key].append((iteration, conjunction.inputs[c_key]))

iteration = 0
while iteration < 100000:
    iteration += 1
    count_pulses(iteration)

for key in cycles.keys():
    print("")
    print(key)
    for c_key in cycles[key].keys():
        print(f"{c_key}: {cycles[key][c_key]}")
