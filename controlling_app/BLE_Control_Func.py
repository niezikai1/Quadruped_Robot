#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
*******************************************************************************
  * Name    : BLE_Control_Func.py
  * Author  : KitaOvO
  * Function: BLE Control Functions with Command Line Interface
  * Version : V1.0.0
  * Date    : 2025.3.15
*******************************************************************************
"""

#-------------import libraries---------------------------
import asyncio
from bleak import BleakScanner, BleakClient

#-------------configuration constants--------------------
# uuid
SERVICE_UUID = "_"
CHARACTERISTIC_UUID = "_"

# Protocol header and footer are the same, can be separated
FRAME_HEAD = 0xFE
FRAME_END = 0xEF


async def send_command(client, command_type, params):
    """Send command to robot"""
    try:
        # Complete command
        command_bytes = (
                bytes([FRAME_HEAD, command_type])
                + bytes(params)
                + bytes([FRAME_END])
        )

        # Get characteristic object
        service = client.services.get_service(SERVICE_UUID)
        if not service:
            print("Service not found")
            return False
        characteristic = service.get_characteristic(CHARACTERISTIC_UUID)
        if not characteristic:
            print("Characteristic not found")
            return False

        # Send command
        await client.write_gatt_char(characteristic, command_bytes, response=True)
        print('Successfully sent command')
        return True
    except Exception as e:
        print(f'Failed to send command: {e}')
        return False


async def control_panel(client):
    """Direct control"""
    while client.is_connected:
        print('\n==== Control Panel ====')
        print('1. Foot Control')
        print('2. Whole Control')
        print('3. Quit')

        choice = input("Enter your choice: ")

        try:
            if choice == '1':   # Single foot control
                foot_num = int(input('Enter foot number: '))
                vertical = int(input('Enter vertical number: '))
                horizontal = int(input('Enter horizontal number: '))
                await send_command(client, 0x01, [foot_num, vertical, horizontal])

            elif choice == '2': # Whole robot control
                direction = int(input('Enter direction: '))
                distance = int(input('Enter distance: '))
                await send_command(client, 0x02, [direction, distance])

            elif choice == '3':
                print("Disconnected")
                await client.disconnect()

            else:
                print("Invalid choice")

        except ValueError:
            print("Please enter an integer")


async def search_ble_devices(target_name=None, timeout=5):
    """Search for nearby BLE devices, timeout after 5 seconds"""
    print("Searching BLE devices...")
    devices = await BleakScanner.discover(timeout=timeout)

    if not devices:
        print("No BLE devices found")
        return None

    print("Found BLE devices below")
    found_devices = []
    for device in devices:
        print(f"- name: {device.name} | address: {device.address}")
        found_devices.append(device)

    # If target name is specified, return matching device
    if target_name:
        target_device = next((d for d in found_devices if d.name == target_name), None)
        return target_device

    return found_devices


async def connect_to_ble_device(target_name):
    """Connect to BLE device with specified name"""
    # Search for target device
    target_device = await search_ble_devices(target_name)

    if not target_device:
        print("No such BLE device")
        return None

    print(f"Trying to connect to {target_name}")
    client = BleakClient(target_device.address)

    try:
        await client.connect()
        if client.is_connected:
            print("Successfully connected")
            return client
        else:
            print("Failed to connect")
            return None

    except Exception as e:
        print("Connection abnormal")
        await client.disconnect()
        return None


async def main():
    target_name = input("Input BLE device name: ")
    client = await connect_to_ble_device(target_name)

    if client.is_connected:
        await control_panel(client)
    else:
        print("Can't connect")

asyncio.run(main())
