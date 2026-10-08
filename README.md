# Điều khiển LED bằng nút nhấn sử dụng ESP32-C3-Zero & OneButton

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
```

---

## 3. Cấu hình môi trường (`platformio.ini`)

Dự án sử dụng cơ chế chia nhiều môi trường (`env`) độc lập trong một project thông qua `build_src_filter` và `build_flags` để định nghĩa chân cắm trực tiếp mà không cần sửa code:

| Môi trường (Env) | File nguồn (`src/`) | Chân phần cứng (`build_flags`) | Chức năng chính |
| :--- | :--- | :--- | :--- |
| `[env:blink]` | `blink.cpp` | LED: **GPIO 7** | Nháy LED đơn thuần với chu kỳ 500ms |
| `[env:double_click]` | `doubleClick.cpp` | LED: **GPIO 7**, Nút: **GPIO 0** (Boot) | Bấm đơn bật/tắt, bấm đúp nháy LED |
| `[env:2leds]` | `2leds.cpp` | LED1: **GPIO 7**, LED2: **GPIO 8**, Nút: **GPIO 9** | Điều khiển nâng cao 2 LED bằng 1 nút nhấn |

---

## 4. Chi tiết chức năng & Logic điều khiển các file

* **`blink.cpp` (Nháy cơ bản):** 
  * Điều khiển 1 LED (GPIO 7) nhấp nháy liên tục theo chu kỳ để kiểm tra phần cứng.

* **`doubleClick.cpp` (1 LED - Bấm đơn/đúp):** 
  * Điều khiển 1 LED (GPIO 7) bằng nút bấm (GPIO 0).
  * **Bấm đơn:** Đảo trạng thái Bật/Tắt (Blink/Off).
  * **Bấm đúp:** Kích hoạt chế độ nhấp nháy 200ms.

* **`2leds.cpp` (2 LED - Chương trình chính):** 
  * Quản lý 2 LED (GPIO 7, 8) qua 1 nút nhấn (GPIO 9). Khởi động LED 1 sáng, LED 2 tắt.
  * **Single Click:** Đảo trạng thái Bật/Tắt của LED đang chọn (đang nháy thì bấm sẽ dừng và tắt).
  * **Double Click:** Chuyển đổi quyền điều khiển qua lại giữa LED 1 và LED 2 (LED chọn sáng, LED kia tắt).
  * **Long Press (Giữ nút):** Kích hoạt nhấp nháy liên tục 200ms cho LED đang chọn.

---

## 5. Hướng dẫn cách vận hành trên PlatformIO

1. Mở thư mục dự án bằng **VS Code** đã cài đặt extension **PlatformIO**.
2. Nhìn xuống **thanh trạng thái (Status Bar)** ở góc dưới bên trái màn hình:
   * Bấm vào ô chọn môi trường (mặc định có thể là `Default`).
   * Chọn đúng môi trường muốn chạy, ví dụ: **`env:2leds`** *(tránh để chế độ Default vì PlatformIO sẽ build và nạp lần lượt tất cả các env)*.
3. Nhấn biểu tượng **Upload** (mũi tên hướng sang phải) hoặc chạy lệnh qua Terminal:
   ```bash
   pio run -e 2leds -t upload

---
## Thư viện sử dụng

- [mathertel/OneButton](https://github.com/mathertel/OneButton) `^2.6.1`: nhận diện click, double click, giữ nút
- `lib/LED/LED.h`: lớp điều khiển LED không chặn (non-blocking), tác giả Nguyen Anh Tuan