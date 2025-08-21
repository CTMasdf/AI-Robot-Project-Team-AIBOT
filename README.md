# AIBOT – 지능형 로봇 플랫폼

## ​ GitHub 리포지토리
- [Arduino 제어 코드](https://github.com/CTMasdf/AI-Robot-Project-Team-AIBOT/blob/main/arduino_code.ino)
- [Raspberry Pi 챗봇 코드](https://github.com/CTMasdf/AI-Robot-Project-Team-AIBOT/blob/main/Raspberrypi.py)
- [이 README 문서](https://github.com/CTMasdf/AI-Robot-Project-Team-AIBOT/blob/main/README.md)

---

##  시연 영상  
- GitHub 기반 전체 기능이 동작하는 모습을 유튜브 영상으로 확인할 수 있습니다:  
  ▶ [시연 영상 보기](https://www.youtube.com/watch?v=zz5ADG3Mypc&t=194s)

---

##  프로젝트 개요  
**목표**: 사용자와 자연스럽게 소통하고 상황에 대응할 수 있는 지능형 로봇 플랫폼 구현.  
이 프로젝트는 음성 인식(STT/TTS), 이미지 인식, 그리고 Gemini API 기반 자연어 처리 기능을 통합하여, 사용자 명령에 유연히 반응하며 하드웨어를 제어하는 로봇입니다.

---

##  시스템 구성  
| 구성 | 설명 |
|------|------|
| **Ar​duino 제어** | `arduino_code.ino` – 모터, TFT LCD 제어 및 시리얼 수신 |
| **Raspberry Pi 챗봇** | `Raspberrypi.py` – STT/TTS, 이미지 촬영 및 Gemini API 연동 |
| **시연 영상** | 실제 로봇 작동 모습 및 화면 입력 기능 시연 |

---

##  주요 기능

### 캐릭터 얼굴 표시  
TFT LCD에 눈 모양 아이콘으로 상태 표현 (홈 화면)

### 모터 제어 (메카넘 휠 기반)  
- 전진 / 후진 / 좌회전 / 우회전 / 정지 – 음성 명령 또는 키워드로 제어

### 날씨 아이콘 표시  
TFT LCD에 날씨 상태 (맑음, 구름, 비, 눈 등)를 시각적으로 보여줌

### 이미지 촬영 및 분석  
사용자의 “사진 찍어줘” 명령 시 카메라로 촬영 후 Gemini API로 분석 결과를 언어로 응답

---

##  설치 및 사용 방법

1. **레포지토리 클론**  
   ```bash
   git clone https://github.com/CTMasdf/AI-Robot-Project-Team-AIBOT.git
   cd AI-Robot-Project-Team-AIBOT
