# Điều khiển LED bằng nút nhấn sử dụng ESP32-C3-Zero thư viện OneButton

Dự án phát triển trên nền tảng **PlatformIO (VS Code)** sử dụng vi điều khiển **ESP32-C3 Zero** (`esp32-c3-devkitm-1`) để điều khiển 2 đèn LED thông qua một nút nhấn duy nhất, áp dụng thư viện quản lý sự kiện `OneButton` và thư viện tùy chỉnh `LED`.

---

## 1. Linh kiện sử dụng
* **Vi điều khiển:** ESP32-C3 Zero (hoặc ESP32-C3 DevKitM-1).
* **LED 1:** Kết nối qua chân **GPIO 7** (`LED_PIN_1 = 7`, mức kích hoạt `HIGH`).
* **LED 2:** Kết nối qua chân **GPIO 8** (`LED_PIN_2 = 8`, mức kích hoạt `HIGH`).
* **Nút nhấn (Push Button):** Kết nối qua chân **GPIO 9** (`BTN_PIN = 9`, cấu hình kéo lên nội bộ, mức kích hoạt `LOW`).
* **Phụ kiện khác:** Testboard, dây cắm tín hiệu, điện trở hạn dòng cho LED (nếu cần).

---

## 2. Cấu trúc dự án
```text
blinkLed/
├── .pio/
├── .vscode/
├── include/
├── lib/
│   └── LED/
│       └── LED.h         # Thư viện tùy chỉnh điều khiển LED
├── src/
│   ├── blink.cpp         # Chương trình nháy LED cơ bản
│   ├── doubleClick.cpp   # Chương trình điều khiển 1 LED với bấm đơn/đúp
│   └── 2leds.cpp         # Chương trình chính điều khiển 2 LED bằng 1 nút bấm
├── test/
├── .gitignore
├── platformio.ini        # File cấu hình môi trường và cờ biên dịch (Build flags)
└── README.md             # Tài liệu mô tả dự án