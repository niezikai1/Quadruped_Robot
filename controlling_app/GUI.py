#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
*******************************************************************************
  * Name    : GUI.py
  * Author  : KitaOvO
  * Function: Bleak Bluetooth BLE GUI Controller
  * Version : V1.0.0
  * Date    : 2025.3.15
*******************************************************************************
"""

#-------------import libraries---------------------------
import tkinter as tk
from tkinter import ttk, messagebox
import threading
import asyncio
import os
from BLE_Control import BLEController
from PIL import Image, ImageTk

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

#-------------class definition---------------------------
class BLEGUI:
    def __init__(self, master):
        self.img = None
        self.master = master
        self.ble = BLEController()
        self.current_device = None
        self.setup_ui()
        self.setup_async()

    # Because the tkinter thread is blocking, asyncio event loop cannot directly run.
    # Create a separate tread to run asyncio event loop
    def setup_async(self):
        """init asyncio event loop"""
        self.loop = asyncio.new_event_loop()
        self.thread = threading.Thread(
            target=self.run_loop,
            daemon=True
        )
        self.thread.start()

    def run_loop(self):
        asyncio.set_event_loop(self.loop)
        self.loop.run_forever()

    def run_async(self, coro):  # coro: coroutine
        """Execute asynchronous task"""
        return asyncio.run_coroutine_threadsafe(coro, self.loop)

    def setup_ui(self):
        """Create UI"""

        # Device Management
        device_frame = ttk.LabelFrame(self.master, text="Device Management")
        device_frame.pack(padx=0, pady=0, fill="x")
        # List of devices
        self.device_list = ttk.Treeview(    # use 'Treeview' to create a table which shows all devices
            master=device_frame,            # parent container
            columns=("name", "address"),    # name of each column
            show="headings",        # hide the first column
            height=5        # The number of rows displayed in the table
        )
        # Name text
        self.device_list.heading("name", text="Device Name")    # The definition of the head 'name'
        self.device_list.heading("address", text="Address")     # The definition of the head 'address'
        self.device_list.pack(side="left", fill="x", expand=True)   # Fill the area along the x-axis from the left side
        # Button to update and connect to devices
        btn_frame = ttk.Frame(device_frame)     # create a frame for button
        btn_frame.pack(side="right", padx=5)    # From the right side
        # update/scan
        ttk.Button(
            master=btn_frame,   # parent container
            text="Update",      # text of the button
            command=self.scan_devices   # the function of the button
        ).pack(pady=2)
        # connect
        self.connect_btn = ttk.Button(
            master=btn_frame,   # parent container
            text="Connect",     # text of the button
            state="disabled",   # state showed that whether this button can be clicked
            command=self.toggle_connection  # the function of the button
        )
        self.connect_btn.pack(pady=2)

        # State
        self.status_var = tk.StringVar(value="Done")
        ttk.Label(
            self.master,
            textvariable=self.status_var,
            relief="sunken"
        ).pack(fill="x", padx=10, pady=5)

        # Control Panel
        control_frame = ttk.LabelFrame(self.master, text="Move Control")
        control_frame.pack(padx=10, pady=5, side='left', fill="both", expand=False)
        # 4 buttons sending message to robot to control it
        controls = [
            ("Move Forward", "\u2191", 0x01),   # (Text, Symbol, Byte)
            ("Move Backward", "\u2193", 0x02),
            ("Turn Left", "\u2190", 0x03),
            ("Turn Right", "\u2192", 0x04)
        ]
        for text, symbol, code in controls:
            btn = ttk.Button(
                master=control_frame,   # parent container
                text=f"{symbol}\n{text}",   # text of each button
                width=15,       # width of buttons
                command=lambda c=code: self.send_control(c)     # functions of buttons
            )
            btn.pack(side="left", padx=5, pady=5, expand=True)
        self.setup_image()

    def scan_devices(self):
        """Scan bluetooth devices"""
        self.set_status("Scanning Devices...")
        future = self.run_async(self.ble.scan_devices())
        future.add_done_callback(self.update_device_list)

    def update_device_list(self, future):
        """Update device list"""
        try:
            devices = future.result()
            self.device_list.delete(*self.device_list.get_children())

            for d in devices:
                name = d["name"] or "Unknown device."
                self.device_list.insert(
                    "",
                    "end",
                    values=(name, d["address"])
                )

            if devices:
                if len(devices) == 1:
                    self.set_status(f"Found {len(devices)} device")
                else:
                    self.set_status(f"Found {len(devices)} devices")
                self.connect_btn.config(state="normal")
            else:
                self.set_status("No device found")
                self.connect_btn.config(state="disabled")

        except Exception as e:
            tk.messagebox.showerror("Error", f"Fail to scan: {str(e)}")
            self.set_status("Fail to scan")

    def toggle_connection(self):
        """Toggle connection status"""
        if self.ble.is_connected():
            self.run_async(self.ble.disconnect())
            self.set_status("Disconnected")
            self.connect_btn.config(text="Connect")
        else:
            self.connect_selected_device()

    def connect_selected_device(self):
        """Connect to selected device"""
        selection = self.device_list.selection()
        if not selection:
            messagebox.showwarning("Warning", "Please select device!")
            return

        item = self.device_list.item(selection[0])
        device_info = {
            "name": item["values"][0],
            "address": item["values"][1]
        }

        self.set_status("Connecting...")
        future = self.run_async(self.ble.connect_device(device_info))
        future.add_done_callback(
            lambda f: self.handle_connection_result(f, device_info)
        )

    def handle_connection_result(self, future, device_info):
        """Handle connection result"""
        try:
            if future.result():
                self.set_status(f"Already connected to: {device_info['name']}")
                self.connect_btn.config(text="Disconnect")
                self.enable_controls(True)
            else:
                self.set_status("Fail to connect")
        except Exception as e:
            messagebox.showerror("Error", str(e))
            self.set_status("Fail to connect")

    def send_control(self, command):
        """Send control command"""
        if not self.ble.is_connected():
            messagebox.showerror("Error", "Please connect to device first")
            return

        try:
            self.run_async(self.ble.send_command(command, [10]))
            self.set_status(f"Already sent command: {command:02X}")
        except Exception as e:
            messagebox.showerror("Error", str(e))

    def set_status(self, message):
        """Update status bar"""
        self.master.after(0, self.status_var.set, message)

    def enable_controls(self, enable):
        """Enable/disable control buttons"""
        state = "normal" if enable else "disabled"
        for child in self.master.winfo_children():
            if isinstance(child, ttk.Button):
                child.config(state=state)

    def setup_image(self):
        try:
            image_frame = ttk.Frame(self.master)
            image_frame.pack(side='right', anchor='se', padx=10, pady=5)
            path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "Avatar.png")
            print(f"Looking for image at: {path}")
            self.img = ImageTk.PhotoImage(Image.open(path).resize((300, 300)))
            ttk.Label(image_frame, text="Built by KitaOvO").pack()
            img_label = ttk.Label(image_frame, image=self.img)
            img_label.pack()
        except FileNotFoundError as e:
            print(f'Picture Not Found: {e}')
        except Exception as e:
            print(f"Fail to Load: {e}")

if __name__ == "__main__":
    root = tk.Tk()
    root.title("Bluetooth Controller")
    root.geometry("900x600")
    app = BLEGUI(root)
    root.mainloop()
