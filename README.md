# 🚦 2-Way Traffic Light (Arduino + Proteus)  
**Dual 7-segment countdown (1→7) • Stable multiplexing • Clean Proteus sim**

![Arduino](https://img.shields.io/badge/Arduino-UNO-00979D?logo=arduino&logoColor=white)
![Simulator](https://img.shields.io/badge/Simulator-Proteus%208-6F42C1)
![Displays](https://img.shields.io/badge/7--Segment-Common%20Cathode-2EA043)
![Made%20With](https://img.shields.io/badge/Built%20With-C%2B%2B%20%7C%20Markdown-0366D6)

🚦 A compact junction controller where upper & lower roads alternate 🛣️, and each GREEN(🟢)/YELLOW (🟡) & RED (🔴) phase shows a crisp 1→7 countdown ⏱️ on a single-digit 7-segment display 🔢.
Built on Arduino UNO 🤖, simulated in Proteus 8 🧪, using common-cathode digits ⚡ with stable multiplexing ⚙️.

---

[![🖼️ Schematic / Preview](https://img.shields.io/badge/Schematic-Preview-blueviolet?style=for-the-badge)](#schematic-preview)

<img width="700" height="461" alt="image" src="https://github.com/user-attachments/assets/5f2daaa3-c029-4094-883f-570eb2cbe3eb" />

---

[![🌟 Features](https://img.shields.io/badge/Features-Highlights-brightgreen?style=for-the-badge)](#features)

- ✔️ Sequence: **Upper RED / Lower GREEN → Both YELLOW → Upper GREEN / Lower RED → Both YELLOW** (loop)
- ✔️ Two single-digit **CC** 7-segment displays (multiplexed, no ghosting)
- ✔️ Countdown **1→7** on GREEN and YELLOW phases
- ✔️ Simple timings & pin map that match the schematic

---

[![🧩 Hardware (this build)](https://img.shields.io/badge/Hardware-this_build-orange?style=for-the-badge)](#hardware-this-build)
- **Arduino UNO (ATmega328P)**
- **2 ×** single-digit **common-cathode** 7-segment displays
- **2 ×** **traffic-light modules** (each: Red / Yellow / Green)
- **Resistors (simulation choice):** **2 × 330 Ω** — *one per display common*

> ℹ️ **Note:** For real hardware, the classic approach is **one resistor per segment** (A..G) for uniform brightness and pin protection.

---

[![🔌 Pin Map](https://img.shields.io/badge/Pin-Map-1f6feb?style=for-the-badge)](#pin-map)

### Segments (shared A..G)
| Segment | Arduino |
|:------:|:-------:|
| A | D0 |
| B | D1 |
| C | D2 |
| D | D3 |
| E | D4 |
| F | D5 |
| G | D6 |

### Digit enables (common cathodes)
| Display | Arduino | Active |
|:------:|:-------:|:------:|
| Top    | A1      | **LOW = ON** |
| Bottom | A2      | **LOW = ON** |

### Traffic-light modules
| Module | Red | Yellow | Green |
|:-----:|:---:|:------:|:-----:|
| Upper | D13 | D12    | D11   |
| Lower | D10 | D9     | D8    |

> 🔗 Tie **all grounds** together (Arduino GND, both displays, both modules).  
> 📢 Using **D0/D1** for segments → **don’t** open the Serial Monitor while running.

---

[![🛠️ Build & Run](https://img.shields.io/badge/Build-%26_Run-1E90FF?style=for-the-badge)](#build--run)
1. Open `2Way_Traffic_Lights_System.ino` in **Arduino IDE**.  
2. **Board:** Arduino Uno → **Verify (✓)** and copy the generated `.hex` path (enable verbose output if needed).  
3. In **Proteus**: double-click the UNO → set **Program File** to the `.hex` → **Run**.  
4. Enjoy the cycle:  
   - **Phase A:** Upper **RED**, Lower **GREEN** → lower display counts **1→7**  
   - **Phase Y:** **Both YELLOW** → both displays count **1→7**  
   - **Phase B:** Upper **GREEN**, Lower **RED** → upper display counts **1→7**  
   - **Phase Y:** **Both YELLOW** → both displays count **1→7**

---


[![💡 Usage & Applications](https://img.shields.io/badge/Usage-%26_Applications-ff69b4?style=for-the-badge)](#usage--applications)

- 🎓 **Classroom demos / labs** — timing, state machines, multiplexing basics  
- 🧪 **Prototyping** — mini intersections, robot crossings, queue simulators  
- 🗂️ **Portfolio / viva** — clean, visual project that’s easy to present  
- 🧭 **HMI mockups** — pair with a small UI/dashboard to simulate phases  
- 🔁 **Extensions** — add sensors (LDR/ultrasonic), pedestrian button, IoT logging

---

[![🧰 Troubleshooting](https://img.shields.io/badge/Troubleshooting-Tips-red?style=for-the-badge)](#troubleshooting)
- **Only “1” & “7” look correct:** If you ever wire physical digits, avoid a single resistor on the common; use per-segment resistors (A..G).  
- **Digits scrambled:** Ensure wiring truly follows **A..G → D0..D6**; if your footprint differs, adjust the sketch pin array.  
- **Flicker/ghosting:** In 2Way_Traffic_Lights_System.ino, set segment pattern **before** enabling a digit; increase digit dwell slightly if needed.

---


[![📜 License](https://img.shields.io/badge/License-MIT-lightgrey?style=for-the-badge)](#license)

**MIT** — see `LICENSE`.

---





