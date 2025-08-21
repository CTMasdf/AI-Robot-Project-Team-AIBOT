// AIBOT - Arduino Robot Control Code
// 아이봇 - 아두이노 로봇 제어 코드

// Include necessary libraries for TFT display, motor control, and interrupts
// TFT 디스플레이, 모터 제어 및 인터럽트에 필요한 라이브러리 포함
#include <Adafruit_GFX.h>       // Core graphics library / 그래픽 코어 라이브러리
#include <Adafruit_ST7735.h>    // TFT display library / TFT 디스플레이 라이브러리
#include <AFMotor.h>            // Motor shield library / 모터 쉴드 라이브러리
#include <SPI.h>                // SPI communication library / SPI 통신 라이브러리
#include <avr/interrupt.h>      // Interrupt header file / 인터럽트 헤더 파일

// Define pin connections for the TFT screen
// TFT 스크린의 핀 연결 정의
#define TFT_CS      45  // Chip Select pin / 칩 선택 핀
#define TFT_DC      42  // Data/Command pin / 데이터/명령 핀
#define TFT_RST     44  // Reset pin / 리셋 핀
#define MAX_BUFFER_SIZE 20 // Max string length 20 characters / 문자열 최대 길이 20자
#define ST77XX_LIGHTGREY 0xC618 // Define custom light grey color / 사용자 정의 밝은 회색 색상

// Global variables for serial communication and mode control
// 시리얼 통신 및 모드 제어를 위한 전역 변수
char Serial_Buffer[MAX_BUFFER_SIZE] = {0}; // String buffer / 문자열 버퍼
unsigned int buffer_index = 0;             // Current buffer index / 현재 버퍼 인덱스
unsigned int mode = 6;                     // Default mode (character face) / 기본 모드 (캐릭터 얼굴)
int time;                                  // Timer variable / 타이머 변수
volatile bool modeChangeRequested = false; // Flag for mode change request / 모드 변경 요청 플래그

// Define motor objects for each wheel
// 각 바퀴에 대한 모터 객체 정의
AF_DCMotor motorFR(3); // Front Right motor, connected to M3 on the shield
AF_DCMotor motorFL(4); // Front Left motor, connected to M4 on the shield
AF_DCMotor motorRL(1); // Rear Left motor, connected to M1 on the shield
AF_DCMotor motorRR(2); // Rear Right motor, connected to M2 on the shield

// Define a default speed for the motors
// 모터의 기본 속도 정의
const int DEFAULT_SPEED = 150;

// Initialize the TFT display object
// TFT 디스플레이 객체 초기화
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Interrupt Service Routine for Timer2 Overflow
// 타이머2 오버플로우를 위한 인터럽트 서비스 루틴
ISR(TIMER2_OVF_vect) {
  TCNT2 = 0xE7; // 10us (This is likely to reset the timer for consistent timing)
                // 10us (일정한 타이밍을 위해 타이머를 재설정하는 용도)

  /* The following commented-out code is for a 1-second timer that can be used for state changes.
     아래 주석 처리된 코드는 상태 변화에 사용될 수 있는 1초 타이머입니다. */
  /*
  time++;
  if (time > 10000) { // 1 second elapsed / 1초 경과
    modeChangeRequested = true; // Request mode change / 모드 전환 요청
    time = 0;
  }
  */
}

void setup(void) {
  // Initialize the TFT screen with a black tab
  // TFT 스크린을 검정 탭으로 초기화
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);  // Fill the screen with black color / 화면을 검정색 배경으로 채우기
  tft.setRotation(2);            // Set landscape orientation / 가로 방향 설정
  delay(500);

  // Initialize all motors and set their default speed
  // 모든 모터 초기화 및 기본 속도 설정
  motorFR.setSpeed(DEFAULT_SPEED);
  motorFL.setSpeed(DEFAULT_SPEED);
  motorRL.setSpeed(DEFAULT_SPEED);
  motorRR.setSpeed(DEFAULT_SPEED);

  // Set initial state to RELEASE (stopped) to ensure the robot is still
  // 초기 상태를 RELEASE(정지)로 설정하여 로봇이 멈춰 있도록 함
  motorFR.run(RELEASE);
  motorFL.run(RELEASE);
  motorRL.run(RELEASE);
  motorRR.run(RELEASE);

  // Prepare serial communication for Raspberry Pi
  // 라즈베리파이와의 시리얼 통신을 준비합니다.
  Serial.begin(9600);    // Set communication speed to 9600 baud / 통신 속도를 9600으로 설정
  Serial.flush();        // Clear any leftover data in the serial buffer / 시리얼 상의 잔여 데이터를 초기화시킨다.

  // Configure Timer2 (1ms period, prescaler 128)
  // Timer2 설정 (1ms 주기, 프리스케일러 128)
  TCCR2A = 0x00;
  TCCR2B = 0x05;     // Set prescaler to 128 / 프리스케일러 128로 설정
  TCNT2 = 0xE7;      // Generate an interrupt every ~1ms / 약 1ms 간격으로 인터럽트 발생
  TIMSK2 = 0x01;     // Enable overflow interrupt / 오버플로우 인터럽트 허용
  sei();             // Enable global interrupts / 전역 인터럽트 허용
}

void loop() {
  // Main loop to continuously draw the graph based on the current mode
  // 현재 모드에 따라 그래프를 계속 그리는 메인 루프
  graph();

  /************** Serial communication code for Raspberry Pi ****************/
  /************** 라즈베리파이 간의 시리얼 통신코드 ****************/
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Read a string until a newline character / '\n'까지 문자열을 읽음
    input.trim(); // Remove leading/trailing whitespace / 앞뒤 공백 제거

    Serial.print("입력된 문자열: "); // Print the received string to the serial monitor for debugging
    Serial.println(input);         // 디버깅을 위해 수신된 문자열을 시리얼 모니터에 출력

    // Compare the received string and set the mode accordingly
    // 수신된 문자열을 비교하여 모드 설정
    if (input == "M_Sunny") {
        mode = 0;
        tft.fillScreen(ST77XX_BLACK);
    }
    else if (input == "M_partly_cloudy") {
        mode = 1;
        tft.fillScreen(ST77XX_BLACK);
    }
    else if (input == "M_cloudy") {
        mode = 2;
        tft.fillScreen(ST77XX_BLACK);
    }
    else if (input == "M_rainy") {
        mode = 3;
        tft.fillScreen(ST77XX_BLACK);
    }
    else if (input == "M_sleet") {
        mode = 4;
        tft.fillScreen(ST77XX_BLACK);
    }
    else if (input == "M_snowy") {
        mode = 5;
        tft.fillScreen(ST77XX_BLACK);
    }
    else if (input == "M_home") {
        mode = 6; tft.fillScreen(ST77XX_BLACK);
    }
    else if (input == "M_stop") {
        mode = 6; tft.fillScreen(ST77XX_BLACK);
        stopMotors();
    }
    else if (input == "M_forward") {
        mode = 7; tft.fillScreen(ST77XX_BLACK);
        moveForward();
    }
    else if (input == "M_backward") {
        mode = 8; tft.fillScreen(ST77XX_BLACK);
        moveBackward();
    }
    else if (input == "M_turn_left") {
        mode = 9; tft.fillScreen(ST77XX_BLACK);
        strafeLeft();
    }
    else if (input == "M_turn_right") {
        mode = 10; tft.fillScreen(ST77XX_BLACK);
        strafeRight();
    }
    else if (input == "M_spin_left") {
        mode = 11; tft.fillScreen(ST77XX_BLACK);
        turnCounterClockwise();
    }
    else if (input == "M_spin_right") {
        mode = 12; tft.fillScreen(ST77XX_BLACK);
        turnClockwise();
    }
  }
}

// Function to draw graphics on the TFT screen based on the current mode
// 현재 모드에 따라 TFT 스크린에 그래픽을 그리는 함수
void graph() {
  switch(mode) {
  // 0: Sunny / 맑음
  case 0:
    tft.fillCircle(59, 64, 20, ST77XX_YELLOW); // Sun center moved 5 pixels left / 태양 중심 왼쪽으로 5픽셀 이동
    for (int angle = 0; angle < 360; angle += 30) {
      float rad = angle * 3.14159 / 180;
      int x1 = 59 + cos(rad) * 25;
      int y1 = 64 + sin(rad) * 25;
      int x2 = 59 + cos(rad) * 35;
      int y2 = 64 + sin(rad) * 35;
      tft.drawLine(x1, y1, x2, y2, ST77XX_ORANGE); // Sun rays / 태양 광선
    }
    break;

  // 1: Partly cloudy / 구름 낀 해
  case 1:
    tft.fillCircle(45, 50, 18, ST77XX_YELLOW); // Sun / 태양
    for (int angle = 0; angle < 360; angle += 45) {
      float rad = angle * 3.14159 / 180;
      int x1 = 45 + cos(rad) * 22;
      int y1 = 50 + sin(rad) * 22;
      int x2 = 45 + cos(rad) * 30;
      int y2 = 50 + sin(rad) * 30;
      tft.drawLine(x1, y1, x2, y2, ST77XX_ORANGE); // Sun rays behind cloud / 구름 뒤 태양 광선
    }
    // Cloud / 구름
    tft.fillCircle(65, 60, 18, ST77XX_WHITE);
    tft.fillCircle(80, 55, 15, ST77XX_WHITE);
    tft.fillCircle(55, 55, 15, ST77XX_WHITE);
    tft.fillRect(55, 55, 30, 15, ST77XX_WHITE);
    break;

  // 2: Cloudy / 흐림
  case 2:
    tft.fillCircle(45, 60, 20, ST77XX_LIGHTGREY);
    tft.fillCircle(70, 55, 20, ST77XX_LIGHTGREY);
    tft.fillCircle(90, 60, 20, ST77XX_LIGHTGREY);
    tft.fillRect(50, 60, 40, 20, ST77XX_LIGHTGREY);
    break;

  // 3: Rainy / 비
  case 3:
    tft.fillCircle(45, 45, 20, ST77XX_WHITE);
    tft.fillCircle(70, 40, 20, ST77XX_WHITE);
    tft.fillCircle(90, 45, 20, ST77XX_WHITE);
    tft.fillRect(50, 45, 40, 15, ST77XX_WHITE);
    for (int i = 0; i < 5; i++) {
      tft.drawLine(50 + i * 15, 65, 55 + i * 15, 80, ST77XX_BLUE); // Raindrops / 빗방울
    }
    break;

  // 4: Sleet / 진눈깨비
  case 4:
    tft.fillCircle(45, 45, 20, ST77XX_WHITE);
    tft.fillCircle(70, 40, 20, ST77XX_WHITE);
    tft.fillCircle(90, 45, 20, ST77XX_WHITE);
    tft.fillRect(50, 45, 40, 15, ST77XX_WHITE);
    for (int i = 0; i < 3; i++) {
      tft.drawLine(50 + i * 20, 65, 55 + i * 20, 80, ST77XX_BLUE); // Rain / 비
      tft.drawCircle(60 + i * 20, 90, 2, ST77XX_CYAN);              // Snow / 눈
      tft.fillCircle(60 + i * 20, 90, 2, ST77XX_CYAN);
    }
    break;

  // 5: Snowy / 눈
  case 5:
    tft.fillCircle(45, 45, 20, ST77XX_WHITE);
    tft.fillCircle(70, 40, 20, ST77XX_WHITE);
    tft.fillCircle(90, 45, 20, ST77XX_WHITE);
    tft.fillRect(50, 45, 40, 15, ST77XX_WHITE);
    for (int i = 0; i < 5; i++) {
      int x = 40 + i * 15;
      int y = 70 + (i % 2) * 10;
      tft.drawCircle(x, y, 3, ST77XX_CYAN);     // Snowflake / 눈송이
      tft.drawLine(x - 3, y, x + 3, y, ST77XX_CYAN);
      tft.drawLine(x, y - 3, x, y + 3, ST77XX_CYAN);
    }
    break;

  // 6: Character's eyes (Home/Initial state) / 캐릭터 눈 (홈/초기 상태)
  case 6:
    tft.fillRoundRect(15, 45, 40, 30, 8, ST77XX_CYAN); // Left eye / 왼쪽 눈
    tft.fillRoundRect(75, 45, 40, 30, 8, ST77XX_CYAN); // Right eye / 오른쪽 눈
    break;

  // 7: Forward movement display / 전진 이동 표시
  case 7:
    tft.fillRoundRect(15, 45, 40, 30, 8, ST77XX_CYAN); // Left eye / 왼쪽 눈
    tft.fillRoundRect(75, 45, 40, 30, 8, ST77XX_CYAN); // Right eye / 오른쪽 눈
    tft.setCursor(20, 100);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(2);
    tft.print("Forward");
    break;

  // 8: Backward movement display / 후진 이동 표시
  case 8:
    tft.fillRoundRect(15, 45, 40, 30, 8, ST77XX_CYAN); // Left eye / 왼쪽 눈
    tft.fillRoundRect(75, 45, 40, 30, 8, ST77XX_CYAN); // Right eye / 오른쪽 눈
    tft.setCursor(20, 100);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(2);
    tft.print("Backward");
    break;

  // 9: Turn left display / 좌회전 표시
  case 9:
    tft.fillRoundRect(15, 45, 40, 30, 8, ST77XX_CYAN); // Left eye / 왼쪽 눈
    tft.fillRoundRect(75, 45, 40, 30, 8, ST77XX_CYAN); // Right eye / 오른쪽 눈
    tft.setCursor(10, 100);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(2);
    tft.print("Turn Left");
    break;

  // 10: Turn right display / 우회전 표시
  case 10:
    tft.fillRoundRect(15, 45, 40, 30, 8, ST77XX_CYAN); // Left eye / 왼쪽 눈
    tft.fillRoundRect(75, 45, 40, 30, 8, ST77XX_CYAN); // Right eye / 오른쪽 눈
    tft.setCursor(2, 100);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(2);
    tft.print("Turn Right"); // Corrected spelling / 철자 수정
    break;

  // 11: Spin left display / 좌회전(제자리) 표시
  case 11:
    tft.fillRoundRect(15, 45, 40, 30, 8, ST77XX_CYAN); // Left eye / 왼쪽 눈
    tft.fillRoundRect(75, 45, 40, 30, 8, ST77XX_CYAN); // Right eye / 오른쪽 눈
    tft.setCursor(10, 100);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(2);
    tft.print("Spin Left");
    break;

  // 12: Spin right display / 우회전(제자리) 표시
  case 12:
    tft.fillRoundRect(15, 45, 40, 30, 8, ST77XX_CYAN); // Left eye / 왼쪽 눈
    tft.fillRoundRect(75, 45, 40, 30, 8, ST77XX_CYAN); // Right eye / 오른쪽 눈
    tft.setCursor(5, 100);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(2);
    tft.print("Spin Right"); // Corrected spelling / 철자 수정
    break;
  }
}

// --- Movement Functions (remain the same) ---
// --- 이동 함수 (동일) ---

// All wheels move FORWARD / 모든 바퀴를 앞으로 움직임
void moveForward() {
  motorFR.run(FORWARD);
  motorFL.run(FORWARD);
  motorRL.run(FORWARD);
  motorRR.run(FORWARD);
}

// All wheels move BACKWARD / 모든 바퀴를 뒤로 움직임
void moveBackward() {
  motorFR.run(BACKWARD);
  motorFL.run(BACKWARD);
  motorRL.run(BACKWARD);
  motorRR.run(BACKWARD);
}

// Strafe Left:
// Front Right: FORWARD, Front Left: BACKWARD
// Rear Left: FORWARD, Rear Right: BACKWARD
// 왼쪽으로 횡이동:
// 전방 오른쪽: FORWARD, 전방 왼쪽: BACKWARD
// 후방 왼쪽: FORWARD, 후방 오른쪽: BACKWARD
void strafeLeft() {
  motorFR.run(FORWARD);
  motorFL.run(BACKWARD);
  motorRL.run(FORWARD);
  motorRR.run(BACKWARD);
}

// Strafe Right:
// Front Right: BACKWARD, Front Left: FORWARD
// Rear Left: BACKWARD, Rear Right: FORWARD
// 오른쪽으로 횡이동:
// 전방 오른쪽: BACKWARD, 전방 왼쪽: FORWARD
// 후방 왼쪽: BACKWARD, 후방 오른쪽: FORWARD
void strafeRight() {
  motorFR.run(BACKWARD);
  motorFL.run(FORWARD);
  motorRL.run(BACKWARD);
  motorRR.run(FORWARD);
}

// Turn Clockwise:
// Front Right: BACKWARD, Front Left: FORWARD
// Rear Left: FORWARD, Rear Right: BACKWARD
// 시계 방향으로 회전:
// 전방 오른쪽: BACKWARD, 전방 왼쪽: FORWARD
// 후방 왼쪽: FORWARD, 후방 오른쪽: BACKWARD
void turnClockwise() {
  motorFR.run(BACKWARD);
  motorFL.run(FORWARD);
  motorRL.run(FORWARD);
  motorRR.run(BACKWARD);
}

// Turn Counter-Clockwise:
// Front Right: FORWARD, Front Left: BACKWARD
// Rear Left: BACKWARD, Rear Right: FORWARD
// 반시계 방향으로 회전:
// 전방 오른쪽: FORWARD, 전방 왼쪽: BACKWARD
// 후방 왼쪽: BACKWARD, 후방 오른쪽: FORWARD
void turnCounterClockwise() {
  motorFR.run(FORWARD);
  motorFL.run(BACKWARD);
  motorRL.run(BACKWARD);
  motorRR.run(FORWARD);
}

// Diagonal Front-Right:
// Front Right: RELEASE, Front Left: FORWARD
// Rear Left: FORWARD, Rear Right: RELEASE
// 대각선 전진-오른쪽:
// 전방 오른쪽: RELEASE, 전방 왼쪽: FORWARD
// 후방 왼쪽: FORWARD, 후방 오른쪽: RELEASE
void moveDiagonalFR() {
  motorFR.run(RELEASE); // Can also set a very low speed FORWARD / 아주 낮은 속도 FORWARD로 설정 가능
  motorFL.run(FORWARD);
  motorRL.run(FORWARD);
  motorRR.run(RELEASE); // Can also set a very low speed FORWARD / 아주 낮은 속도 FORWARD로 설정 가능
}

// Diagonal Front-Left:
// Front Right: FORWARD, Front Left: RELEASE
// Rear Left: RELEASE, Rear Right: FORWARD
// 대각선 전진-왼쪽:
// 전방 오른쪽: FORWARD, 전방 왼쪽: RELEASE
// 후방 왼쪽: RELEASE, 후방 오른쪽: FORWARD
void moveDiagonalFL() {
  motorFR.run(FORWARD);
  motorFL.run(RELEASE); // Can also set a very low speed FORWARD / 아주 낮은 속도 FORWARD로 설정 가능
  motorRL.run(RELEASE); // Can also set a very low speed FORWARD / 아주 낮은 속도 FORWARD로 설정 가능
  motorRR.run(FORWARD);
}

// Diagonal Rear-Left:
// Front Right: RELEASE, Front Left: BACKWARD
// Rear Left: BACKWARD, Rear Right: RELEASE
// 대각선 후진-왼쪽:
// 전방 오른쪽: RELEASE, 전방 왼쪽: BACKWARD
// 후방 왼쪽: BACKWARD, 후방 오른쪽: RELEASE
void moveDiagonalRL() {
  motorFR.run(RELEASE); // Can also set a very low speed BACKWARD / 아주 낮은 속도 BACKWARD로 설정 가능
  motorFL.run(BACKWARD);
  motorRL.run(BACKWARD);
  motorRR.run(RELEASE); // Can also set a very low speed BACKWARD / 아주 낮은 속도 BACKWARD로 설정 가능
}

// Diagonal Rear-Right:
// Front Right: BACKWARD, Front Left: RELEASE
// Rear Left: RELEASE, Rear Right: BACKWARD
// 대각선 후진-오른쪽:
// 전방 오른쪽: BACKWARD, 전방 왼쪽: RELEASE
// 후방 왼쪽: RELEASE, 후방 오른쪽: BACKWARD
void moveDiagonalRR() {
  motorFR.run(BACKWARD);
  motorFL.run(RELEASE); // Can also set a very low speed BACKWARD / 아주 낮은 속도 BACKWARD로 설정 가능
  motorRL.run(RELEASE); // Can also set a very low speed BACKWARD / 아주 낮은 속도 BACKWARD로 설정 가능
  motorRR.run(BACKWARD);
}

// Stop all motors
// 모든 모터 정지
void stopMotors() {
  motorFR.run(RELEASE);
  motorFL.run(RELEASE);
  motorRL.run(RELEASE);
  motorRR.run(RELEASE);
}
