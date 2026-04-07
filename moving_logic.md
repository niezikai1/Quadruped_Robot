# Quadruped Robot Movement Logic

## Overview

Divide the 4 legs into 2 balanced groups:
- **Group 1**: Left front leg (ID 0) and right back leg (ID 3)
- **Group 2**: Right front leg (ID 1) and left back leg (ID 2)

**Basic assumption**: The robot can maintain balance on any group of legs.

---

## Forward Movement Logic

### Main Loop Steps

1. **Lift Group 1 and swing forward**
   - Left front leg lifts and swings forward
   - Right back leg lifts and swings forward

2. **Reset Group 2**
   - Right front leg returns to initial position
   - Left back leg returns to initial position

3. **Lower Group 1**
   - Left front leg lowers to ground (maintaining forward swing angle)
   - Right back leg lowers to ground (maintaining forward swing angle)

4. **Lift Group 2 and swing forward**
   - Right front leg lifts and swings forward
   - Left back leg lifts and swings forward

5. **Reset Group 1**
   - Left front leg returns to initial position
   - Right back leg returns to initial position

6. **Lower Group 2**
   - Right front leg lowers to ground (maintaining forward swing angle)
   - Left back leg lowers to ground (maintaining forward swing angle)

**Important**: There must be a delay function between each two steps.

---

## Backward Movement Logic

The backward movement logic is essentially the same as the forward movement logic, only with opposite swing directions.

### Main Loop Steps

1. **Lift Group 1 and swing backward**
   - Left front leg lifts and swings backward
   - Right back leg lifts and swings backward

2. **Reset Group 2**
   - Right front leg returns to initial position
   - Left back leg returns to initial position

3. **Lower Group 1**
   - Left front leg lowers to ground (maintaining backward swing angle)
   - Right back leg lowers to ground (maintaining backward swing angle)

4. **Lift Group 2 and swing backward**
   - Right front leg lifts and swings backward
   - Left back leg lifts and swings backward

5. **Reset Group 1**
   - Left front leg returns to initial position
   - Right back leg returns to initial position

6. **Lower Group 2**
   - Right front leg lowers to ground (maintaining backward swing angle)
   - Left back leg lowers to ground (maintaining backward swing angle)

**Important**: There must be a delay function between each two steps.

---

## Turning Logic

### Right Turn Logic

#### Main Loop Steps

1. **Lift Group 1**
   - Simultaneously swing left front leg (ID 0) forward
   - Simultaneously swing right back leg (ID 3) backward

2. **Reset Group 2**
   - Right front leg returns to initial position
   - Left back leg returns to initial position

3. **Lower Group 1**
   - Left front leg lowers to ground (maintaining forward swing angle)
   - Right back leg lowers to ground (maintaining backward swing angle)

4. **Lift Group 2**
   - Simultaneously swing right front leg (ID 1) backward
   - Simultaneously swing left back leg (ID 2) forward

5. **Reset Group 1**
   - Left front leg returns to initial position
   - Right back leg returns to initial position

6. **Lower Group 2**
   - Right front leg lowers to ground (maintaining backward swing angle)
   - Left back leg lowers to ground (maintaining forward swing angle)

### Left Turn Logic

#### Main Loop Steps

1. **Lift Group 2**
   - Simultaneously swing right front leg (ID 1) forward
   - Simultaneously swing left back leg (ID 2) backward

2. **Reset Group 1**
   - Left front leg returns to initial position
   - Right back leg returns to initial position

3. **Lower Group 2**
   - Right front leg lowers to ground (maintaining forward swing angle)
   - Left back leg lowers to ground (maintaining backward swing angle)

4. **Lift Group 1**
   - Simultaneously swing left front leg (ID 0) backward
   - Simultaneously swing right back leg (ID 3) forward

5. **Reset Group 2**
   - Right front leg returns to initial position
   - Left back leg returns to initial position

6. **Lower Group 1**
   - Left front leg lowers to ground (maintaining backward swing angle)
   - Right back leg lowers to ground (maintaining forward swing angle)

**Important**: There must be a delay function between each two steps.

---

## Delay Explanation

All movement steps require appropriate delays to ensure:
1. Servos have sufficient time to reach target positions
2. The robot maintains stability
3. Avoid mechanical stress caused by rapid switching

Recommended delay times:
- Basic movement: 400ms
- Quick testing: 100ms

---

## Implementation Notes

1. **Leg function naming**:
   - `Left_Front_leg(vertical_angle, horizontal_angle)`
   - `Right_Front_leg(vertical_angle, horizontal_angle)`
   - `Left_Back_leg(vertical_angle, horizontal_angle)`
   - `Right_Back_leg(vertical_angle, horizontal_angle)`

2. **Reset functions**:
   - `Reset_Group1()`: Reset Group 1 legs to initial position
   - `Reset_Group2()`: Reset Group 2 legs to initial position

3. **Initial angles**:
   - Refer to `angles_relevent_to_hardware.md` file for initial angles of each leg

4. **Swing directions**:
   - Refer to `angles_relevent_to_hardware.md` file for swing direction symbols (+/-) of each leg