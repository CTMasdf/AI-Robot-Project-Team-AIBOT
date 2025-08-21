import os                       # For interacting with the operating system / 운영체제와 상호작용
import subprocess               # To run external commands (like rpicam-still) / 외부 명령 실행 (rpicam-still)
import time                     # For time-related functions / 시간 관련 함수
import json                     # To handle JSON data for conversation history / 대화 기록을 위한 JSON 데이터 처리
import serial                   # For serial communication with Arduino / 아두이노와의 시리얼 통신
import speech_recognition as sr # For Speech-to-Text (STT) / 음성-텍스트 변환 (STT)
from gtts import gTTS           # For Text-to-Speech (TTS) / 텍스트-음성 변환 (TTS)
from dotenv import load_dotenv  # To load environment variables from .env file / .env 파일에서 환경 변수 로드
import google.generativeai as genai # For using the Gemini API / Gemini API 사용

# ------------------- Environment Variables & Gemini API -------------------
# ------------------- 환경 변수 & Gemini API -------------------
load_dotenv()
GEMINI_API_KEY = os.getenv("GEMINI_API_KEY") # Load API key from environment / 환경 변수에서 API 키 로드
genai.configure(api_key=GEMINI_API_KEY)     # Configure Gemini with the API key / API 키로 Gemini 설정
model = genai.GenerativeModel("gemini-1.5-flash") # Initialize the Gemini model / Gemini 모델 초기화

# ------------------- Path Settings -------------------
# ------------------- 경로 설정 -------------------
IMAGE_PATH = "/home/aibot/chatbot_project/capture.jpg" # Path for the captured image / 촬영된 사진 경로
HISTORY_FILE = "conversation_history.json"            # Path for conversation history file / 대화 기록 파일 경로

# ------------------- Arduino Serial Communication -------------------
# ------------------- 아두이노 시리얼 통신 -------------------
# List of keywords that can be sent as commands to the Arduino
# 아두이노로 보낼 수 있는 명령어 키워드 목록
COMMAND_KEYWORDS = [
    'M_Sunny', 'M_partly_cloudy', 'M_cloudy', 'M_rainy', 'M_sleet', 'M_snowy',
    'M_stop', 'M_forward', 'M_backward', 'M_turn_left', 'M_turn_right',
    'M_spin_left', 'M_spin_right', 'M_home'
]

try:
    # Attempt to establish a serial connection with the Arduino
    # 아두이노와 시리얼 연결 시도
    arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    print("아두이노 연결 성공")
except Exception as e:
    # Handle connection failure
    # 연결 실패 처리
    print(f"❌ 아두이노 연결 실패: {e}")
    arduino = None # Set arduino to None if connection fails / 연결 실패 시 None으로 설정
time.sleep(2) # Wait for the serial connection to initialize / 시리얼 연결 초기화를 위해 대기

# ------------------- Conversation History Management -------------------
# ------------------- 대화 기록 관리 -------------------
def load_conversation_history():
    # Load conversation history from a JSON file
    # JSON 파일에서 대화 기록 로드
    if os.path.exists(HISTORY_FILE):
        with open(HISTORY_FILE, "r", encoding="utf-8") as f:
            return json.load(f)
    return [] # Return an empty list if the file does not exist / 파일이 없으면 빈 목록 반환

def save_conversation_history():
    # Save the current conversation history to a JSON file
    # 현재 대화 기록을 JSON 파일에 저장
    with open(HISTORY_FILE, "w", encoding="utf-8") as f:
        json.dump(conversation_history, f, ensure_ascii=False, indent=2)

conversation_history = load_conversation_history() # Load history at startup / 시작 시 기록 로드

# ------------------- Speech-to-Text (STT) -------------------
# ------------------- 음성-텍스트 변환 (STT) -------------------
def recognize_speech(prompt=None):
    # Recognize speech from the microphone using Google's API
    # 마이크를 통해 음성을 인식하고 구글 API 사용
    r = sr.Recognizer()
    with sr.Microphone() as source:
        if prompt:
            print(prompt)
        audio = r.listen(source) # Listen for audio from the microphone / 마이크에서 음성 듣기
        try:
            # Use Google Web Speech API for recognition / 구글 웹 음성 API를 사용하여 인식
            text = r.recognize_google(audio, language="ko-KR")
            print("인식된 텍스트:", text)
            return text
        except:
            # Handle cases where speech recognition fails / 음성 인식 실패 시 처리
            print("음성 인식 실패")
            return ""

# ------------------- Text-to-Speech (TTS) -------------------
# ------------------- 텍스트-음성 변환 (TTS) -------------------
def speak_text(text):
    # Convert text to speech and play it
    # 텍스트를 음성으로 변환하여 재생
    print("🤖 Gemini:", text)
    tts = gTTS(text=text, lang="ko") # Create a gTTS object with Korean language / 한국어 gTTS 객체 생성
    tts.save("response.mp3")         # Save the audio to a file / 오디오 파일을 저장
    os.system("mpg321 -q response.mp3") # Play the audio file using mpg321 / mpg321을 사용하여 오디오 파일 재생

# ------------------- Arduino Command Handling -------------------
# ------------------- 아두이노 명령어 처리 -------------------
def extract_command(text):
    # Check if the text contains any predefined command keywords
    # 텍스트에 미리 정의된 명령어 키워드가 포함되어 있는지 확인
    text_lower = text.lower()
    for keyword in COMMAND_KEYWORDS:
        if keyword.lower() in text_lower:
            return keyword
    return None # Return None if no command is found / 명령어가 없으면 None 반환

def send_to_arduino(command):
    # Send a command string to the Arduino via serial
    # 시리얼을 통해 아두이노로 명령어 문자열 전송
    if command and arduino:
        try:
            # Encode the command and send it with a newline character
            # 명령어를 인코딩하고 줄바꿈 문자와 함께 전송
            arduino.write((command + '\n').encode('utf-8'))
            print("아두이노로 전송:", command)
        except Exception as e:
            # Handle serial transmission errors / 시리얼 전송 오류 처리
            print("아두이노 전송 오류:", e)

# ------------------- Gemini API Interaction -------------------
# ------------------- Gemini API 상호작용 -------------------
def generate_response(prompt):
    # Generate a text response using the Gemini model
    # Gemini 모델을 사용하여 텍스트 응답 생성
    try:
        response = model.generate_content(prompt)
        return response.text
    except Exception as e:
        # Handle Gemini API errors / Gemini API 오류 처리
        return f"Gemini 오류: {e}"

def build_prompt():
    # Build a full conversation prompt from the history
    # 기록으로부터 전체 대화 프롬프트 구축
    prompt = ""
    for msg in conversation_history:
        role = "User" if msg["role"] == "user" else "Chatbot"
        prompt += f"{role}: {msg['parts']}\n"
    return prompt

# ------------------- Image Capture & Analysis -------------------
# ------------------- 사진 촬영 및 분석 -------------------
def take_picture():
    # Use rpicam-still to capture an image from the Raspberry Pi camera
    # 라즈베리파이 카메라로 사진을 촬영하기 위해 rpicam-still 사용
    subprocess.run(["rpicam-still", "-o", IMAGE_PATH])
    print("사진 촬영 완료:", IMAGE_PATH)

def ask_gemini_about_image():
    # Send the captured image to Gemini for analysis
    # 촬영된 이미지를 Gemini로 보내 분석 요청
    if not os.path.exists(IMAGE_PATH):
        return "사진이 존재하지 않습니다."
    with open(IMAGE_PATH, "rb") as f:
        image_data = f.read()
    response = model.generate_content(
        ["방금 찍은 사진에 대해 설명해줘.", {"mime_type": "image/jpeg", "data": image_data}]
    )
    return response.text

# ------------------- Main Command Handler -------------------
# ------------------- 주요 명령어 처리기 -------------------
def handle_command(user_text):
    # Main function to handle user's commands and generate responses
    # 사용자의 명령어를 처리하고 응답을 생성하는 주요 함수
    if "사진" in user_text and ("찍" in user_text or "촬영" in user_text):
        take_picture()
        answer = ask_gemini_about_image()
    else:
        # If not a picture command, interact with Gemini for text
        # 사진 명령어가 아니면 텍스트로 Gemini와 상호작용
        conversation_history.append({"role": "user", "parts": user_text})
        prompt = build_prompt()
        answer = generate_response(prompt)
        conversation_history.append({"role": "model", "parts": answer})
        save_conversation_history() # Save history after each turn / 매 턴마다 기록 저장

    # Extract Arduino command from Gemini's response and send it
    # Gemini의 응답에서 아두이노 명령어를 추출하여 전송
    command = extract_command(answer)
    send_to_arduino(command)

    speak_text(answer) # Speak the final response / 최종 응답을 음성으로 출력

# ------------------- Chatbot Main Loop -------------------
# ------------------- 챗봇 메인 루프 -------------------
def chat_bot():
    # The main loop for the voice chatbot
    # 음성 챗봇의 메인 루프
    print("아이봇 음성 챗봇 시작. '마린'이라고 말하면 질문을 받을게요.")
    while True:
        # Listen for the wake word "마린"
        # '마린'이라는 깨우기 단어를 듣기
        trigger = recognize_speech("'마린'라고 말해주세요")
        if "마린" in trigger:
            speak_text("질문하세요")
            question = recognize_speech("질문을 말해주세요")
            if not question:
                continue

            # Check for termination keywords / 종료 키워드 확인
            if "종료" in question or "그만" in question:
                speak_text("대화를 종료합니다. 안녕히 계세요!")
                break

            handle_command(question) # Process the user's question / 사용자의 질문 처리

# ------------------- Execution -------------------
# ------------------- 실행 -------------------
if __name__ == "__main__":
    # The program starts here
    # 프로그램이 여기서 시작됨
    chat_bot()