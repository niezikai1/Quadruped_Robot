#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
*******************************************************************************
  * Name    : BLE_Control.py
  * Author  : KitaOvO
  * Function: BLE Controller Class for Quadruped Robot
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

# the head and end of the communication protocol
FRAME_HEAD = 0xFE
FRAME_END = 0xEF

#-------------class definition---------------------------
class BLEController:
    def __init__(self):
        self.client = None  # client = BleakClient
        self.connected = False

    async def scan_devices(self):
        """search all the BLE devices."""
        devices = await BleakScanner.discover()
        return [{
            "name": d.name,
            "address": d.address,
            "details": str(d.details),
        } for d in devices]

    async def connect_device(self, device_info):
        """Connect to specific device."""
        self.client = BleakClient(device_info["address"])
        await self.client.connect()
        self.connected = self.client.is_connected
        return self.connected

    async def send_command(self, command_type, params):
        """Send a command to the device."""
        if not self.connected or not self.client:
            raise Exception("device not connected.")

        # the whole command
        command_bytes = (
                bytes([FRAME_HEAD, command_type])
                + bytes(params)
                + bytes([FRAME_END])
        )   # The type of 'params' is 'list'

        # send command
        await self.client.write_gatt_char(CHARACTERISTIC_UUID, command_bytes)
        return True

    async def disconnect(self):
        """Disconnect."""
        if self.connected and self.client:
            await self.client.disconnect()
            self.connected = False

    def is_connected(self):
        return self.connected