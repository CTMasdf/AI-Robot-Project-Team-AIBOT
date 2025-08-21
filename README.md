🤖 AI Robot Project - Team AIBOT
📌 프로젝트 개요

본 프로젝트는 AI와 임베디드 기술을 융합하여 인간과 자연스럽게 소통할 수 있는 지능형 로봇 플랫폼을 개발하는 것을 목표로 합니다.
라즈베리파이와 아두이노를 기반으로 STT(음성 인식), TTS(음성 출력), 이미지 인식, Gemini API 기반 자연어 처리 기술을 활용하여 사용자의 질문과 상황에 맞게 대응할 수 있도록 설계되었습니다.

🎥 시연 영상: YouTube 링크

🛠 주요 기능
1. 캐릭터 얼굴 표현

TFT LCD를 통해 로봇의 눈 그림 출력

감정이나 상태를 직관적으로 전달

2. 모터 제어

메카넘 휠을 이용한 자유로운 이동

전진 / 후진 / 좌회전 / 우회전 / 정지

3. 날씨 표현

TFT LCD를 활용하여 다양한 날씨 표현 가능

맑음 ☀

살짝 구름 🌤

구름 ☁

비 🌧

눈 ❄

4. 카메라 & 이미지 인식

음성 명령을 통해 사진 촬영

Gemini API를 활용해 촬영한 이미지 분석 및 결과 제공

5. 음성 기반 대화

STT : 사용자의 음성을 텍스트로 변환

TTS : 분석된 응답을 다시 음성으로 출력

Gemini API 기반 자연어 처리를 통해 유연한 대화 가능

📂 프로젝트 구조
🔹 Arduino Code

arduino_code.ino

TFT LCD 출력 제어

모터 제어 (메카넘 휠)

시리얼 통신 기반 데이터 송수신

🔹 Raspberry Pi Code

Raspberrypi.py

음성 인식(STT) & 음성 출력(TTS)

Gemini API 기반 대화 처리

카메라 제어 및 이미지 분석

⚙️ 개발 환경

하드웨어

Raspberry Pi 4

Arduino Mega

TFT LCD

메카넘 휠 모터

USB 카메라

스피커 & 마이크

소프트웨어 & 툴

Arduino IDE

Python (venv 가상환경)

Gemini API

OpenCV (이미지 처리)

Pyttsx3 / SpeechRecognition (STT/TTS)

통신 방식

USB Serial (라즈베리파이 ↔ 아두이노)

Wi-Fi (라즈베리파이 네트워크 연결)

버전 관리

GitHub

🚀 설치 및 실행 방법
1. Arduino
# 아두이노 IDE에서 arduino_code.ino 업로드

2. Raspberry Pi
# 가상환경 실행
python3 -m venv venv
source venv/bin/activate

# 패키지 설치
pip install -r requirements.txt

# 실행
python3 Raspberrypi.py

📌 기대 효과

가정, 교육, 서비스 환경에서 활용 가능한 확장형 AI 로봇

인간과 자연스럽게 소통 가능한 지능형 인터페이스 구현

음성, 이미지, 센서 데이터를 융합한 차세대 스마트 로봇 기술 연구 기반 제공

👥 팀 소개 - Team AIBOT
