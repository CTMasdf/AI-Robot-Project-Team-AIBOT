# 인공지능 로봇 AIbot

![AIbot](https://img.shields.io/badge/Python-3.9+-blue) ![Arduino](https://img.shields.io/badge/Arduino-Mega-lightgrey)

## 프로젝트 소개
라즈베리파이와 아두이노를 기반으로 Google의 생성형 AI **Gemini API**와 음성 인식(STT), 음성 합성(TTS), 이미지 인식 모듈을 활용하여 사용자의 질문과 상황에 자연스럽게 대응하는 **인공지능 로봇**을 구현하는 프로젝트입니다.

본 프로젝트는 가정, 교육, 서비스 환경 등 다양한 분야에서 실질적이고 확장 가능한 AI 로봇 플랫폼을 목표로 합니다.

## 시연 영상
- [유튜브 시연 영상 링크](#)

## 프로젝트 구조

chatbot_project/
│
├─ main.py # 라즈베리파이 챗봇 메인 코드
├─ conversation_history.json
├─ capture.jpg # 촬영된 이미지 저장 경로
└─ Arduino/
└─ AIbot.ino # 아두이노 로봇 제어 코드

markdown
복사
편집

### 시스템 구성
**라즈베리파이 (Raspberry Pi 4)**  
- 역할: AI 브레인, 음성 인식, Gemini API 연동, 음성 합성, 카메라 제어  
- 주요 모듈: 마이크, 스피커, 카메라 모듈

**아두이노 (Arduino Mega)**  
- 역할: 로봇 신체 제어, 모터 및 LCD 제어  
- 주요 모듈: 메카넘 휠용 DC 모터, L293D 모터 드라이버, TFT LCD

## 개발 환경

**하드웨어**
- Raspberry Pi 4, Arduino Mega
- 카메라 모듈, TFT LCD
- DC 모터, L293D 모터 드라이버

**운영체제**
- Raspberry Pi OS 32bit (Linux 기반)

**소프트웨어**
- Python 3.x, C++ (Arduino IDE)
- 라이브러리: SpeechRecognition, gTTS, PySerial, Adafruit_GFX, Adafruit_ST7735, AFMotor

**네트워크/통신**
- Serial (UART, USB 포트 기반)
- Wi-Fi (Raspberry Pi 연결)

**버전관리**
- GitHub

## 설치 및 실행

1. 라즈베리파이 환경 준비
```bash
sudo apt update
sudo apt install python3-pip mpg321
pip install -r requirements.txt
.env 파일 생성 후 Gemini API 키 설정

ini
복사
편집
GEMINI_API_KEY=YOUR_API_KEY
아두이노 코드 업로드

Arduino IDE에서 AIbot.ino 업로드

라즈베리파이에서 챗봇 실행

bash
복사
편집
python3 main.py
"마린"이라고 말하면 챗봇이 질문을 받을 준비를 합니다.

주요 기능
음성 인식(STT): 마이크 입력을 텍스트로 변환

Gemini AI 대화: 사용자의 질문에 자연스러운 대화 제공

음성 합성(TTS): 대화 내용을 음성으로 출력

이미지 인식: 카메라 촬영 후 이미지 분석

로봇 제어: 아두이노로 이동 및 표정 표시
