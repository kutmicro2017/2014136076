#define Up_Red 2
#define Up_Yellow 3
#define Up_Green 4 //위쪽 불
#define Down_Red 22
#define Down_Yellow 24
#define Down_Green 26  //아래쪽 불
#define Right_Red 11
#define Right_Yellow 12
#define Right_Green 10  //오른쪽 불
#define Left_Red 23
#define Left_Yellow 25
#define Left_Green 27  //왼쪽 불
#define SW 30       //위아래 스위치


int timePinRow[8] = { 40, 41, 42, 43, 44, 45, 46, 47 };
int timePinCol[8] = { 32, 33, 34, 35, 36, 37, 38, 39 };
// 보행자 신호 출력용 매트릭스 핀 번호 배열
int signPinRow[8] = { A8, A9, A10, A11, A12, A13, A14, A15 };
int signPinCol[8] = { A0, A1, A2, A3, A4, A5, A6, A7 };

//기타 기호상수
#define DRIVABLE_DURATION           10000u                                                  //주행 가능 시간, 녹색등 유지시간(20sec)
#define LED_Yellow_BLINK_DURATION   5000u                                                   //경고등 점멸 시간(5sec)
#define BLINK_TIME                  LED_Yellow_BLINK_DURATION / 1000                        //점멸 횟수(1초당 1회)
#define TRAFFIC_LIGHT_IDLE_TIME     3000u                                                   //입력 받았을 시 대기 시간(3sec)
#define ARRAY_LENGTH                8                                                       //배열 길이
#define CYCLE                       (DRIVABLE_DURATION + LED_Yellow_BLINK_DURATION) / 1000  //신호 바뀔 때까지의 걸리는 시간
#define WALK_DURATION               CYCLE * 1000                                            //

//폴링시 필요한 변수
bool gbChange = false;
//DotMatrix 타이머 출력을 위한 변수
int gNumbers[10][8][4] =
{
  // ZERO
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // ONE
  {
    { 0, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 1, 1, 1, 1 }
  },
  // TWO
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 1, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 1 }
  },
  // THREE
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // FOUR
  {
    { 0, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 }
  },
  // FIVE
  {
    { 1, 1, 1, 1 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 1, 1, 1, 1 }
  },
  // SIX
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // SEVEN
  {
    { 1, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 }
  },
  // EIGHT
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // NINE
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  }
};
//DotMatrix 보행자 그림 출력을 위한 변수
int gWalkerSigns[2][8][8] =
{
  // Red : Cannot Cross
  {
   { 0, 0, 0, 1, 1, 0, 0, 0 },
   { 0, 0, 0, 1, 1, 0, 0, 0 },
   { 0, 0, 1, 1, 1, 1, 0, 0 },
   { 0, 0, 1, 1, 1, 1, 0, 0 },
   { 0, 0, 1, 1, 1, 1, 0, 0 },
   { 0, 0, 1, 1, 1, 1, 0, 0 },
   { 0, 0, 0, 1, 1, 0, 0, 0 },
   { 0, 0, 0, 1, 1, 0, 0, 0 }
  },

  // Green : Can Cross
  {
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 1, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 }
  }
};

void setup()
{
  //상하 출력 핀 모드 설정
  pinMode(Up_Red, OUTPUT);
  pinMode(Down_Red, OUTPUT);
  pinMode(Up_Yellow, OUTPUT);
  pinMode(Down_Yellow, OUTPUT);
  pinMode(Up_Green, OUTPUT);
  pinMode(Down_Green, OUTPUT);
  //좌우 출력 핀 모드 설정
  pinMode(Left_Red, OUTPUT);
  pinMode(Right_Red, OUTPUT);
  pinMode(Left_Yellow, OUTPUT);
  pinMode(Right_Yellow, OUTPUT);
  pinMode(Left_Green, OUTPUT);
  pinMode(Right_Green, OUTPUT);
  //DotMatrix 핀 모드 설정 및 초기화
  for(int i = 0; i < ARRAY_LENGTH; ++i)
  {
    pinMode(timePinRow[i], OUTPUT);
    pinMode(timePinCol[i], OUTPUT);
    pinMode(signPinRow[i], OUTPUT);
    pinMode(signPinCol[i], OUTPUT);

    digitalWrite(timePinRow[i], LOW);
    digitalWrite(timePinCol[i], HIGH);
    digitalWrite(signPinRow[i], LOW);
    digitalWrite(signPinCol[i], HIGH);
  }
  //입력 핀 모드 설정
  pinMode(SW, INPUT_PULLUP);
}

void loop()
{
  //상하 주행
  digitalWrite(Left_Red, HIGH);
  digitalWrite(Right_Red, HIGH);
  digitalWrite(Up_Green, HIGH);
  digitalWrite(Down_Green, HIGH);
  for (int t = CYCLE; t > 0; --t)
  {
     int former = t / 10;
     int later = t % 10;
     if (t > BLINK_TIME)
     {
        DisplayStopSignWithPolling(1000, former, later);
        if (gbChange)
       {
        gbChange = false;
        break;
       }
     }
     else if (digitalRead(Up_Red) == LOW && digitalRead(Down_Red) == LOW)
     {
       digitalWrite(Up_Green, LOW);
       digitalWrite(Down_Green, LOW);
       UD_BlinkYellow(former, later);
     }
  }
  digitalWrite(Left_Red, LOW);
  digitalWrite(Right_Red, LOW);

  //좌우 주행
  digitalWrite(Up_Red, HIGH);
  digitalWrite(Down_Red, HIGH);
  digitalWrite(Left_Green, HIGH);
  digitalWrite(Right_Green, HIGH);
  for (int t = CYCLE; t > 0; --t)
  {
     int former = t / 10;
     int later = t % 10;
     if (t > BLINK_TIME)
     {
        DisplayWalkSign(1000);
        if(gbChange)
       {
        gbChange = false;
        break;
       }
     }
     else if (digitalRead(Left_Red) == LOW && digitalRead(Right_Red) == LOW)
     {
       digitalWrite(Left_Green, LOW);
       digitalWrite(Right_Green, LOW);
       LR_BlinkYellow();
     }
  }
  digitalWrite(Up_Red, LOW);
  digitalWrite(Down_Red, LOW);
}

void LR_BlinkYellow()
{
  static const int delayTime = LED_Yellow_BLINK_DURATION / (BLINK_TIME + BLINK_TIME);
  
  digitalWrite(Left_Yellow, HIGH);
  digitalWrite(Right_Yellow, HIGH);
  DisplayWalkSign(delayTime);
  digitalWrite(Left_Yellow, LOW);
  digitalWrite(Right_Yellow, LOW);
  DisplayWalkSign(delayTime);
}

void LR_LED()
{
  for (int t = (TRAFFIC_LIGHT_IDLE_TIME + LED_Yellow_BLINK_DURATION) / 1000; t > 0; --t)
  {
    if (t > BLINK_TIME)
    {
      //1초간 보행 신호 출력
      DisplayWalkSign(1000);
    }
    else
    {
      digitalWrite(Left_Green, LOW);
      digitalWrite(Right_Green, LOW);
      LR_BlinkYellow();
    }
  }
  digitalWrite(Left_Red, HIGH);
  digitalWrite(Right_Red, HIGH);
  DisplayWalkSign(WALK_DURATION);
  gbChange = true;
}

void UD_BlinkYellow(int former, int later)
{
  static const int delayTime = LED_Yellow_BLINK_DURATION / (BLINK_TIME + BLINK_TIME);
  
  digitalWrite(Up_Yellow, HIGH);
  digitalWrite(Down_Yellow, HIGH);
  DisplayStopSign(delayTime, former, later);
  digitalWrite(Up_Yellow, LOW);
  digitalWrite(Down_Yellow, LOW);
  DisplayStopSign(delayTime, former, later);
}

void UD_LED()
{
  for (int t = (TRAFFIC_LIGHT_IDLE_TIME + LED_Yellow_BLINK_DURATION) / 1000; t > 0; --t)
  {
    if (t > BLINK_TIME)
    {
      //1초간 타이머 출력
      DisplayStopSign(1000, t / 10, t % 10);
    }
    else
    {
      digitalWrite(Up_Green, LOW);
      digitalWrite(Down_Green, LOW);
      UD_BlinkYellow(t / 10, t % 10);
    }
  }
  digitalWrite(Up_Red, HIGH);
  digitalWrite(Down_Red, HIGH);
  digitalWrite(Left_Green, HIGH);
  digitalWrite(Right_Green, HIGH);
  digitalWrite(Right_Red, LOW);
  digitalWrite(Left_Red, LOW);
  DisplayWalkSign(WALK_DURATION);
  gbChange = true;
}

void DisplayStopSignWithPolling(int duration, int former, int later)
{
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    StopSign();
    DisplayNumber(gNumbers[former], gNumbers[later]);
    //Polling
    if (digitalRead(SW) == LOW && digitalRead(Up_Green) == HIGH && digitalRead(Down_Green) == HIGH)
      UD_LED();
    timeEnd = millis();
  }
}

void ClearUpperDisplay()
{
  for (int i = 0; i < ARRAY_LENGTH; ++i)
  {
    digitalWrite(timePinRow[i], LOW);
    digitalWrite(timePinCol[i], HIGH);
  }
}

void ClearLowerDisplay()
{
  for (int i = 0; i < ARRAY_LENGTH; ++i)
  {
    digitalWrite(signPinRow[i], LOW);
    digitalWrite(signPinCol[i], HIGH);
  }
}

void DisplayNumber(int former[][4], int later[][4])
{
  for(int r = 0; r < 8; ++r)
  {
    ClearLowerDisplay();
    digitalWrite(signPinRow[r], HIGH);
    //십의 자리 출력
    for(int c = 0; c < 4; ++c)
    {
      if (former[r][c])
      {
        digitalWrite(signPinCol[c], LOW);
      }
    }
    //일의 자리 출력
    for(int c = 0; c < 4; ++c)
    {
      if (later[r][c])
      {
        digitalWrite(signPinCol[c + 4], LOW);
      }
    }
    //HACK : 이 함수가 없을 시, 출력 신호가 뚜렷하게 보이지 않음
    delay(1);
  }
}

void StopSign()
{
  for(int r = 0; r < 8; ++r)
  {
    ClearUpperDisplay();
    digitalWrite(timePinRow[r], HIGH);
    for(int c = 0; c < 8; ++c)
    {
      if(gWalkerSigns[0][r][c])
      {
        digitalWrite(timePinCol[c], LOW);
      }
    }
    //HACK : 출력 신호를 유지하기 위해 사용
    delay(1);
  }
}

void WalkSign()
{
  for(int r = 0; r < 8; ++r)
  {
    ClearUpperDisplay();
    ClearLowerDisplay();
    digitalWrite(signPinRow[r], HIGH);
    for(int c = 0; c < 8; ++c)
    {
      if(gWalkerSigns[1][r][c])
      {
        digitalWrite(signPinCol[c], LOW);
      }
    }
    //HACK : 출력 신호를 유지하기 위해 사용
    delay(1);
  }
}

void DisplayStopSign(int duration, int former, int later)
{
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    StopSign();
    DisplayNumber(gNumbers[former], gNumbers[later]);
    timeEnd = millis();
  }
}

void DisplayWalkSign(unsigned duration)
{
  ClearUpperDisplay();
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    WalkSign();
    timeEnd = millis();
  }
}

