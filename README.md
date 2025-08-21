# 🤖 AIbot – 인공지능 로봇 프로젝트

![Python](https://img.shields.io/badge/Python-3.9+-blue)
![Arduino](https://img.shields.io/badge/Arduino-Mega-lightgrey)
![License](https://img.shields.io/badge/License-MIT-green)

---

## 📌 프로젝트 소개
AIbot은 **라즈베리파이 4**와 **Arduino Mega**를 기반으로, Google Gemini API, 음성 인식(STT), 음성 합성(TTS), 이미지 분석 기능을 융합한 **지능형 로봇**입니다.  

사용자의 음성과 환경을 인식하고 자연스럽게 대화하며, 로봇의 움직임과 표현을 제어할 수 있습니다.

---

## 🎬 시연 영상
[유튜브 시연 영상 링크](#)

---

## 🏗️ 시스템 구성
chatbot_project/
│
├─ main.py # 라즈베리파이 챗봇 메인 코드
├─ conversation_history.json
├─ capture.jpg # 촬영된 이미지 저장
└─ Arduino/
└─ AIbot.ino # 아두이노 로봇 제어 코드


### 🔹 하드웨어 구성
| 장치 | 역할 |
|------|------|
| Raspberry Pi 4 | AI 처리, STT/TTS, 카메라 제어 |
| Arduino Mega | 모터, LCD, 로봇 제어 |
| DC 모터 & L293D | 이동 제어 |
| TFT LCD | 상태/표정 표시 |
| 카메라 | 이미지 인식 |

### 🔹 소프트웨어 구성
- Python 3.x, C++ (Arduino IDE)
- 주요 라이브러리: `SpeechRecognition`, `gTTS`, `PySerial`, `Adafruit_GFX`, `Adafruit_ST7735`, `AFMotor`
- 통신: USB 시리얼 (UART), Wi-Fi
- 버전 관리: GitHub

---

## ⚡ 설치 및 실행

1. **라즈베리파이 환경 준비**
```bash
sudo apt update
sudo apt install python3-pip mpg321
pip install -r requirements.txt
Gemini API 키 설정

프로젝트 루트에 .env 파일 생성
GEMINI_API_KEY=YOUR_API_KEY


아두이노 코드 업로드
Arduino IDE에서 AIbot.ino 업로드

챗봇 실행
```bash
python3 Raspberry.py
"마린"이라고 말하면 챗봇이 대화를 시작합니다.

🛠️ 주요 기능
STT (Speech-to-Text): 음성을 텍스트로 변환

Gemini AI 대화: 자연스러운 AI 대화 제공

TTS (Text-to-Speech): 텍스트를 음성으로 출력

이미지 인식: 카메라 촬영 및 분석

로봇 제어: 모터, LCD 등 하드웨어 제어

📈 프로젝트 구조도
text
+------------------+       +-------------------+
| Raspberry Pi 4   | <-->  | Arduino Mega      |
| - Gemini API     |       | - DC Motor        |
| - STT/TTS        |       | - L293D Driver    |
| - Camera Module  |       | - TFT LCD         |
+------------------+       +-------------------+




