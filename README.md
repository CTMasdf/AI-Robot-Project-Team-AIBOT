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

프로젝트 기획 및 개발: CTMasdf 외 팀원들

임베디드 제어, AI API 연동, UI 구현 등 협업 진행

혹시 이 README를 좀 더 **보고서 스타일(학술적)**로 다듬을까요, 아니면 GitHub용 간단·실용적 스타일로 맞출까요?

나의 말:
리드미가 마음에 안들어 처음부터 다시 만들어줘
ChatGPT의 말:

알겠어 👍 처음부터 새롭게 깔끔하고 보기 좋은 리드미(README.md) 템플릿을 만들어줄게.

너가 올린 깃허브 코드(Arduino, Raspberry Pi), 시연 영상, 프로젝트 목적/기능 등을 종합해서 전문적인 프로젝트 문서 스타일로 구성해줄게.

🤖 AI Robot Project – Team AIBOT
<img src="https://img.shields.io/badge/Platform-Arduino%20%7C%20RaspberryPi-blue" /> <img src="https://img.shields.io/badge/Language-C++%20%7C%20Python-green" /> <img src="https://img.shields.io/badge/AI-Gemini%20API-orange" />
📌 프로젝트 개요

본 프로젝트는 AI와 임베디드 기술을 융합한 지능형 로봇을 구현하는 것을 목표로 합니다.
라즈베리파이와 아두이노를 기반으로 음성 인식(STT), 음성 출력(TTS), 이미지 인식, 자연어 처리(NLP) 기능을 통합하여
사용자의 질문과 상황에 유연하게 대응할 수 있는 스마트 AI 로봇 플랫폼을 개발했습니다.

🔗 시연 영상 보기: YouTube Demo

🎯 개발 목적

STT/TTS 및 이미지 인식 기반의 자연스러운 대화형 로봇 구현

Gemini API 기반 맞춤형 대화 및 상황 대응

다양한 환경(가정, 교육, 서비스 분야)에 적용 가능한 확장형 AI 로봇 플랫폼 구축

⚙️ 주요 기능
🤖 캐릭터 표현

TFT LCD에 로봇 얼굴 및 눈 표현

사용자와 소통 시 표정 변화 출력

🔊 음성 대화

STT (Speech-to-Text) : 사용자의 음성 입력 인식

TTS (Text-to-Speech) : Gemini API 응답을 음성으로 출력

📸 이미지 인식

카메라로 촬영 명령 수행

Gemini API를 통해 이미지 분석 및 설명 제공

🚗 모터 제어

메카넘 휠 기반 주행

전진 / 후진

좌회전 / 우회전

정지

🌦️ 날씨 표현

TFT LCD를 활용한 날씨 시각화

맑음 / 구름 조금 / 흐림 / 비 / 눈

🛠️ 시스템 구성
하드웨어

Arduino Mega 2560

Raspberry Pi 4

DC 모터 + 메카넘 휠

카메라 모듈

TFT LCD 디스플레이

소프트웨어

Arduino IDE (C++)

Python (Raspberry Pi)

Gemini API (Google AI)

Serial 통신 (USB, UART 기반)

네트워크/통신

USB Serial (Arduino ↔ Raspberry Pi)

Wi-Fi (라즈베리파이 인터넷 연결)

📂 프로젝트 구조
AI-Robot-Project-Team-AIBOT/
│
├── arduino_code.ino      # 아두이노 메가 코드 (모터 제어, TFT LCD, 센서)
├── Raspberrypi.py        # 라즈베리파이 코드 (STT, TTS, 이미지 인식, Gemini API)
├── README.md             # 프로젝트 문서

🚀 실행 방법
Arduino

Arduino IDE에서 arduino_code.ino 업로드

보드: Arduino Mega 2560 선택

USB로 Raspberry Pi와 연결

Raspberry Pi

Python 가상환경 실행

필수 패키지 설치

pip install -r requirements.txt


실행

python Raspberrypi.py

📹 시연 예시

🤝 사용자와 음성 대화

🌦️ 날씨 정보 출력

🚗 메카넘 휠 이동

📸 사진 촬영 및 이미지 분석

👨‍💻 팀원

Team AIBOT

📜 라이선스

이 프로젝트는 MIT License 하에 배포됩니다.

👉 이렇게 하면 깔끔하고, 기능별로 보기 좋게 정리된 README가 돼.
혹시 내가 이걸 연구보고서 느낌으로 더 길고 전문적으로 써줄까, 아니면 실습용 깃허브 README처럼 간단하게 정리해줄까?

나의 말:
전문적인 느낌으로 만들어줘
ChatGPT의 말:

알겠습니다. 아래는 전문적이고 체계적인 느낌의 README.md 초안입니다. 프로젝트 목적, 기능, 시스템 구성, 사용 방법, 시연 영상, 파일 구조까지 정리했습니다.

🤖 AI Robot Project - Team AIBOT
📌 프로젝트 개요

본 프로젝트는 라즈베리파이(Raspberry Pi)와 아두이노(Arduino)를 기반으로 인공지능(AI) 기술을 접목한 지능형 로봇 시스템 개발을 목표로 한다.
로봇은 자연어 명령 인식, 카메라 기반 이미지 분석, TFT LCD를 통한 시각적 표현, 메카넘 휠 기반 이동 제어 기능을 수행한다.
이를 통해 사용자는 로봇과 자연스럽게 상호작용할 수 있으며, 스마트 홈/교육/연구 분야에서 활용 가능한 플랫폼을 제시한다.

🎯 개발 배경 및 목적

인공지능 융합: 음성 인식, 이미지 처리, 대화형 인터페이스를 결합하여 실생활에서 직관적으로 사용할 수 있는 로봇 구현

임베디드 시스템 학습: Raspberry Pi와 Arduino를 연동하여 센서/액추에이터 제어 및 네트워크 통신 학습

확장성 고려: 모듈화된 구조로 다양한 기능(센서 추가, IoT 연동 등) 확장 가능

⚙️ 주요 기능
🔹 감정 및 시각 표현

캐릭터 얼굴 표시: TFT LCD를 이용한 로봇의 눈, 표정 표현

날씨 표현: "맑음, 구름, 비, 눈" 등 기상 정보를 직관적으로 시각화

🔹 이동 제어

메카넘 휠 기반 주행: 전진, 후진, 좌회전, 우회전, 정지 가능

정밀 제어: Arduino를 통해 모터 제어 및 안정적인 주행 구현

🔹 카메라 및 인공지능

사진 촬영: 음성 명령에 따라 카메라 동작

이미지 분석: Gemini API를 활용한 촬영 이미지 분석 및 설명 제공

🔹 음성/텍스트 기반 상호작용

STT (Speech-to-Text): 음성 명령 입력 지원

TTS (Text-to-Speech): 로봇 응답을 음성으로 출력

🖥️ 시스템 구성
📡 하드웨어

Raspberry Pi 4: AI 연산, 카메라 제어, 음성 입출력 처리

Arduino Mega: 모터, TFT LCD, LED 제어

메카넘 휠 4개: 자유로운 방향 이동

TFT LCD (ST7735): 시각적 인터페이스

USB 카메라: 이미지 촬영 및 분석

🔗 네트워크/통신

Serial (UART): Raspberry Pi ↔ Arduino 데이터 통신

Wi-Fi: API 서버 및 네트워크 연결

🛠️ 소프트웨어

Arduino IDE (펌웨어 작성)

Python (Raspberry Pi, venv 환경)

Gemini API (AI 대화 및 이미지 분석)

📂 파일 구조
AI-Robot-Project-Team-AIBOT/
│
├── arduino_code.ino       # Arduino Mega 제어 코드 (모터, TFT LCD, LED)
├── Raspberrypi.py         # Raspberry Pi 제어 코드 (STT, TTS, 카메라, AI)
├── README.md              # 프로젝트 설명 문서

▶️ 시연 영상

📺 유튜브 시연 영상 보기

영상에서는 로봇이 음성 명령을 인식하고 이동, 날씨 표현, 사진 촬영 및 분석을 수행하는 과정을 확인할 수 있다.

🚀 실행 방법

Arduino 코드 업로드

arduino_code.ino 파일을 Arduino Mega 보드에 업로드

TFT LCD, 모터, LED 연결 확인

Raspberry Pi 환경 세팅

# 가상환경 생성
python3 -m venv venv
source venv/bin/activate

# 라이브러리 설치
pip install -r requirements.txt


Python 코드 실행

python Raspberrypi.py


음성 명령을 통해 로봇 제어

예시 명령어:

"앞으로 가" → 전진

"날씨 알려줘" → LCD에 날씨 표시

"사진 찍어" → 사진 촬영 및 분석

👥 팀 소개 - Team AIB
