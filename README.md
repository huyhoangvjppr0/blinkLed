# Điều khiển LED bằng nút nhấn sử dụng ESP32-C3-Zero thư viện OneButton

Dự án phát triển trên nền tảng **PlatformIO (VS Code)** sử dụng vi điều khiển **ESP32-C3 Zero** (`esp32-c3-devkitm-1`) để điều khiển 2 đèn LED thông qua một nút nhấn duy nhất, áp dụng thư viện quản lý sự kiện `OneButton` và thư viện tùy chỉnh `LED`.

---

## 1. Linh kiện sử dụng
* **Vi điều khiển:** ESP32-C3 Zero (hoặc ESP32-C3 DevKitM-1).
* **LED 1:** Kết nối qua chân **GPIO 7**.
* **LED 2:** Kết nối qua chân **GPIO 8**.
* **Nút nhấn (Push Button):** Kết nối qua chân **GPIO 9**.
* **Linh kiện khác:** Testboard, dây cắm, điện trở 1k Ohm.

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
## 3. Cấu hình môi trường (`platformio.ini`)
Dự án sử dụng cơ chế chia nhiều môi trường (`env`) độc lập trong một project thông qua `build_src_filter` và `build_flags` để định nghĩa chân cắm trực tiếp mà không cần sửa code:

| Môi trường (Env) | File nguồn (`src/`) | Chân phần cứng (`build_flags`) | Chức năng chính |
|---|---|---|---|
| `[env:blink]` | `blink.cpp` | LED: `GPIO 7` | Nháy LED đơn thuần với chu kỳ 500ms |
| `[env:double_click]` | `doubleClick.cpp` | LED: `GPIO 7`, Nút: `GPIO 0` (Boot) | Bấm đơn bật/tắt, bấm đúp nháy LED |
| `[env:2leds]` | `2leds.cpp` | LED1: `GPIO 7`, LED2: `GPIO 8`, Nút: `GPIO 9` | Điều khiển nâng cao 2 LED bằng 1 nút nhấn |

---

## 4. Chi tiết chức năng & Logic điều khiển (File `2leds.cpp`)
Sử dụng duy nhất một nút nhấn (tại chân **GPIO 9**) để tương tác với hệ thống 2 đèn LED:

* **Trạng thái khởi động:** 
  * LED 1 (chân 7) sáng, LED 2 (chân 8) tắt.
  * Hệ thống chọn sẵn quyền điều khiển ở LED 1 (`led_select = 1`).
* **Single Click (Bấm đơn):** 
  * Đảo trạng thái (`flip()`) Bật/Tắt của LED đang được chọn.
  * *Lưu ý:* Nếu đèn đang ở chế độ nhấp nháy, bấm đơn sẽ dừng nháy và tắt đèn.
* **Double Click (Bấm đúp):** 
  * Chuyển đổi quyền điều khiển qua lại giữa LED 1 và LED 2 (`1 ⇄ 2`). 
  * Khi chuyển, LED vừa được chọn sẽ bật sáng, LED còn lại tự động tắt.
* **Long Press / Hold (Giữ nút):** 
  * Kích hoạt chế độ nhấp nháy liên tục với chu kỳ **200ms** (`blink(200)`) cho LED đang được chọn.

---

## 5. Hướng dẫn cách chạy dự án trên PlatformIO
1. Mở thư mục dự án bằng **VS Code** đã cài đặt extension **PlatformIO**.
2. Nhìn xuống **thanh trạng thái (Status Bar)** ở góc dưới bên trái màn hình:
   * Bấm vào ô chọn môi trường (mặc định có thể là `Default`).
   * Chọn đúng môi trường muốn chạy, ví dụ: **`env:2leds`** *(tránh để chế độ Default vì PlatformIO sẽ build và nạp lần lượt tất cả các env)*.
3. Nhấn biểu tượng **Upload** (mũi tên hướng sang phải ở thanh trạng thái) hoặc chạy lệnh qua Terminal:
   ```bash
   pio run -e 2leds -t upload