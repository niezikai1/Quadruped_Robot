# Quadruped Robot Communication Protocol Documentation

## Version Information
- **Document Version**: V1.0
- **Last Updated**: 2025 (inferred from file content)

## Communication Methods
- **Primary Communication**: Bluetooth BLE/SPP
- **Backup Communication**: Serial Port

## Data Format

### Basic Format
Data is transmitted in binary 8-bit (1 byte) units, converted to HEX (hexadecimal) format when sending.

**Example**: `0xFE 0x01 0x01 0x55 0x55 0xEF`

### Byte Ranges
- Data byte range: `0x00` - `0xEE` (0-238 decimal)
- Control byte range: `0x01` - `0x09`

---

## Protocol Frame Structure

### General Frame Format
All communication frames follow this structure:

```
+--------+-------------------+-------------------+-------------------+--------+
| Header | Control Type/Mode | Parameter1/Data   | Parameter2/Data   | Footer |
+--------+-------------------+-------------------+-------------------+--------+
|  0xFE  |    0x01-0x09      |     0x00-0xEE     |     0x00-0xEE     |  0xEF  |
+--------+-------------------+-------------------+-------------------+--------+
```

### Frame Field Descriptions
1. **Frame Header**: `0xFE` - Fixed value, identifies frame start
2. **Control Type**: `0x01` - `0x09` - Specifies control type
3. **Parameters/Data**: `0x00` - `0xEE` - Specific control parameters
4. **Frame Footer**: `0xEF` - Fixed value, identifies frame end

---

## Control Types

### 1. Single Leg Control
- **Control Type**: `0x01`
- **Parameter1**: Leg ID
- **Parameter2**: Vertical Angle
- **Parameter3**: Horizontal Angle

**Frame Structure**:
```
0xFE | 0x01 | Leg ID | Vertical Angle | Horizontal Angle | 0xEF
```

**Example**: Control left front leg, vertical angle 0x55, horizontal angle 0x56
```
0xFE 0x01 0x01 0x55 0x56 0xEF
```

**Leg ID Mapping**:
- `0x01`: Left Front Leg
- `0x02`: Right Front Leg
- `0x03`: Left Back Leg
- `0x04`: Right Back Leg

### 2. Whole Robot Control
- **Control Type**: `0x02`
- **Parameter1**: Direction
- **Parameter2**: Distance

**Frame Structure**:
```
0xFE | 0x02 | Direction | Distance | 0xEF
```

**Example**: Control robot to move in a certain direction for a certain distance
```
0xFE 0x02 0x57 0x58 0xEF
```

### 3. Specific Action Control
- **Control Type**: `0x03`
- **Parameter1**: Action ID
- **Parameter2**: Duration/Additional Parameter
- **Parameter3**: Count/Additional Parameter

**Frame Structure**:
```
0xFE | 0x03 | Action ID | Duration | Count | 0xEF
```

**Example**: Execute specific action
```
0xFE 0x03 0x59 0x5A 0x5B 0xEF
```

---

## Specific Command Definitions

### Single Leg Control Detailed Instructions

| Control Mode | Command ID | Command Name | Parameter1 | Parameter2 |
|--------------|------------|--------------|------------|------------|
| Single Leg | 0x01 | Left Front Leg Control | Vertical Angle (0x00-0xEE) | Horizontal Angle (0x00-0xEE) |
| Single Leg | 0x02 | Right Front Leg Control | Vertical Angle (0x00-0xEE) | Horizontal Angle (0x00-0xEE) |
| Single Leg | 0x03 | Left Back Leg Control | Vertical Angle (0x00-0xEE) | Horizontal Angle (0x00-0xEE) |
| Single Leg | 0x04 | Right Back Leg Control | Vertical Angle (0x00-0xEE) | Horizontal Angle (0x00-0xEE) |

**Note**:
- Angle value range: 0x00-0xEE (0-238 decimal)
- Actual angle mapping requires calibration based on servo characteristics

---

## Angle Mapping Explanation

### Angle Value Conversion
Since the protocol uses single byte (0x00-0xEE) to represent angles, the actual angle mapping relationship is:

```
Protocol angle value (0x00-0xEE) → Actual angle (0°-238°)
```

**Example conversions**:
- 0x00 = 0°
- 0x55 = 85° (0x55 = 85 decimal)
- 0xAA = 170° (0xAA = 170 decimal)
- 0xEE = 238° (maximum value)

### Practical Usage Limitations
Most servos operate in the range of 0°-180°, therefore:
- Actual effective angle range: 0x00-0xB4 (0-180 decimal)
- Values exceeding 0xB4 may be limited or ignored

---

## Communication Flow

### Transmission Flow
1. Construct complete frame data
2. Send via BLE or serial port
3. Wait for acknowledgment (if implemented)

### Reception Flow (Robot Side)
1. Detect frame header 0xFE
2. Parse control type
3. Read corresponding parameters based on control type
4. Detect frame footer 0xEF
5. Execute corresponding action

---

## Error Handling

### Frame Error Detection
1. **Header Error**: If not 0xFE, discard the byte and continue searching
2. **Footer Error**: If not 0xEF at expected position, discard entire frame
3. **Length Error**: Verify parameter count based on control type
4. **Range Error**: Verify parameter values are within valid range (0x00-0xEE)

### Timeout Handling
- Frame reception timeout: Reset state if complete frame not received within reasonable time
- Response timeout: If waiting for response times out, retransmit or report error

---

## Implementation Notes

### Python Implementation
```python
# Frame header and footer definitions
FRAME_HEAD = 0xFE
FRAME_END = 0xEF

# Construct command frame
def build_command(command_type, params):
    return bytes([FRAME_HEAD, command_type]) + bytes(params) + bytes([FRAME_END])
```

### Embedded Implementation (C Language)
```c
// Frame parsing state machine
typedef enum {
    STATE_IDLE,
    STATE_HEADER_RECEIVED,
    STATE_TYPE_RECEIVED,
    STATE_PARAM1_RECEIVED,
    STATE_PARAM2_RECEIVED,
    STATE_COMPLETE
} FrameState;
```

---

## Extended Command Space

### Reserved Control Types
- `0x04` - `0x09`: Reserved for future extensions

### Suggested Extension Features
1. **Status Query**: Query current robot status
2. **Configuration Read**: Read current configuration parameters
3. **Firmware Upgrade**: Support OTA firmware upgrade
4. **Diagnostic Mode**: Enter diagnostic and debugging mode

---

## Version Compatibility

### Backward Compatibility
- New control types should not affect existing functionality
- New parameters should be extensions of existing frame structure

### Forward Compatibility
- Receiving end should ignore unknown control types
- Receiving end should handle frames with missing optional parameters

---

## Appendix

### HEX to Decimal Conversion Table
| HEX | Decimal | HEX | Decimal | HEX | Decimal |
|-----|---------|-----|---------|-----|---------|
| 0x00 | 0 | 0x55 | 85 | 0xAA | 170 |
| 0x01 | 1 | 0x56 | 86 | 0xAB | 171 |
| ... | ... | ... | ... | ... | ... |
| 0x54 | 84 | 0xA9 | 169 | 0xEE | 238 |

### Common Angle Value Reference
| Action | Angle Value (HEX) | Angle Value (Decimal) |
|--------|-------------------|-----------------------|
| Initial Position | 0x55-0xAA | 85-170 |
| Maximum Lift | ±0x1E | ±30° |
| Maximum Swing | ±0x1E | ±30° |

**Note**: Specific angle values need to be determined based on actual hardware calibration.