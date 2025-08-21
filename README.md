# 🤖 AI Robot Project - Team AIBOT

[![Platform](https://img.shields.io/badge/Platform-Arduino%20|%20RaspberryPi-blue)](https://www.raspberrypi.com/) 
[![Language](https://img.shields.io/badge/Language-C++%20|%20Python-green)](https://www.python.org/) 
[![AI](https://img.shields.io/badge/AI-Gemini%20API-orange)](https://developers.google.com/gemini)

---

## 📌 프로젝트 개요

본 프로젝트는 라즈베리파이(Raspberry Pi)와 아두이노(Arduino)를 기반으로 **인공지능(AI) 기술을 접목한 지능형 로봇 시스템**을 개발하는 것을 목표로 합니다.  
로봇은 **음성 명령 인식, 카메라 기반 이미지 분석, TFT LCD 시각 표현, 메카넘 휠 기반 이동 제어** 기능을 수행하며, 스마트 홈·교육·연구 분야에서 활용 가능한 플랫폼을 제공합니다.

---

## 🎯 개발 배경 및 목적

- **인공지능 융합:** 음성 인식, 이미지 처리, 대화형 인터페이스를 결합하여 실생활에서 직관적으로 사용할 수 있는 로봇 구현  
- **임베디드 시스템 학습:** Raspberry Pi와 Arduino를 연동하여 센서/액추에이터 제어 및 네트워크 통신 학습  
- **확장성 고려:** 모듈화된 구조로 다양한 기능(센서 추가, IoT 연동 등) 확장 가능

---

## ⚙️ 주요 기능

### 🤖 감정 및 시각 표현
- TFT LCD를 이용한 로봇 얼굴/눈 표정 표현  
- 날씨 시각화: 맑음 ☀ / 구름 조금 🌤 / 흐림 ☁ / 비 🌧 / 눈 ❄  

### 🚗 이동 제어
- 메카넘 휠 기반 주행: 전진, 후진, 좌회전, 우회전, 정지  
- Arduino 기반 정밀 모터 제어

### 📸 카메라 & 이미지 인식
- 음성 명령으로 사진 촬영  
- Gemini API 기반 이미지 분석 및 설명 제공

### 🔊 음성 기반 대화
- **STT (Speech-to-Text):** 사용자의 음성 입력 인식  
- **TTS (Text-to-Speech):** Gemini API 응답을 음성으로 출력

---

## 🖥️ 시스템 구성

### 📡 하드웨어
| 구성 | 용도 |
|------|------|
| Raspberry Pi 4 | AI 연산, 카메라/음성 입출력 처리 |
| Arduino Mega | 모터, TFT LCD, LED 제어 |
| 메카넘 휠 4개 | 자유로운 방향 이동 |
| TFT LCD (ST7735) | 시각적 인터페이스 |
| USB 카메라 | 이미지 촬영 및 분석 |
| 스피커 & 마이크 | 음성 입출력 |

### 🔗 네트워크/통신
- USB Serial (Arduino ↔ Raspberry Pi)  
- Wi-Fi (Raspberry Pi 인터넷 연결)

### 🛠️ 소프트웨어
- Arduino IDE (C++)  
- Python (Raspberry Pi, venv 환경)  
- Gemini API (AI 대화 및 이미지 분석)  
- OpenCV, PyAudio, SpeechRecognition, pyttsx3, gTTS, PySerial  

---

## 📂 프로젝트 구조

- AI-Robot-Project-Team-AIBOT/
- │
- ├── arduino_code.ino # Arduino Mega 제어 코드 (모터, TFT LCD, LED)
- ├── Raspberrypi.py # Raspberry Pi 제어 코드 (STT, TTS, 카메라, AI)
- ├── README.md # 프로젝트 설명 문서
- ├── requirements.txt # Python 패키지 목록


면서 깔끔하게 보일 수 있도록 마크다운 스타일을 예쁘게 다듬어 드릴게요.
아이콘, 구분선, 코드 블록 정리, 강조 포인트를 넣어서 깔끔하게 꾸몄습니다.

---

## 🚀 설치 및 실행 방법

### 🔹 1️⃣ Raspberry Pi 가상환경 생성
```bash
python3 -m venv venv
source venv/bin/activate

🔹 2️⃣ 필수 패키지 설치
pip install -r requirements.txt

🔹 3️⃣ Python 코드 실행
python3 Raspberrypi.py

🔹 4️⃣ Arduino 코드 업로드

Arduino IDE 실행 후 arduino_code.ino 업로드

보드 : Arduino Mega 2560 선택

연결 : USB 케이블로 Raspberry Pi ↔ Arduino 연결

📦 requirements.txt 예시
# 음성 인식
SpeechRecognition==3.8.1
PyAudio==0.2.13

# TTS
gTTS==2.3.1
pyttsx3==2.90

# 이미지 처리 / 카메라
opencv-python==4.8.1.78
numpy==1.25.2
Pillow==10.0.1

# 시리얼 통신
pyserial==3.6

# HTTP 요청 (Gemini API)
requests==2.31.0

# 환경 변수 관리
python-dotenv==1.0.1


💡 Raspberry Pi Tip

sudo apt-get install portaudio19-dev python3-pyaudio


PyAudio 설치 전에 위 패키지를 설치해야 정상 동작합니다.

🎥 시연 영상

🔗 YouTube Demo

영상에서는 로봇이 음성 명령을 인식 → 이동 → 날씨 표현 → 사진 촬영 및 분석을 수행하는 과정을 확인할 수 있습니다.

👥 팀 소개

Team AIBOT

🧑‍💻 프로젝트 기획 및 개발: CTMasdf 외 팀원

⚙️ 임베디드 제어

🤖 AI API 연동

🖥️ UI 구현

모든 파트를 협업하여 개발을 진행했습니다.
