#include <WiFiManager.h>

#include "Audio.h"

#define I2S_DOUT 11

#define I2S_BCLK 12

#define I2S_LRC 10

#define PIN_BUTTON_LEFT 21
#define PIN_BUTTON_RIGHT 47

Audio audio;

int volume = 10;

void setup() {

  Serial.begin(115200);

  WiFiManager wm;
  wm.setDebugOutput(true);
  wm.setConnectRetries(2);

  bool res;
  res = wm.autoConnect("ESP32-SETUP");
  if(!res) {
      Serial.println("Failed to connect to WIFI");
  }
  else {
      Serial.println("Connected to WIFI");
  }

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);

  audio.setVolume(volume);

  //audio.connecttohost("http://vis.media-ice.musicradio.com/CapitalMP3");

  //audio.connecttohost("https://github.com/schreibfaul1/ESP32-audioI2S/raw/master/additional_info/Testfiles/Olsen-Banden.mp3");

  pinMode(PIN_BUTTON_LEFT, INPUT_PULLUP);
  pinMode(PIN_BUTTON_RIGHT, INPUT_PULLUP);

  bool ok = false;

  while (ok == false){
    delay(5000);
    ok = audio.connecttohost("http://mp3.ffh.de/radioffh/hqlivestream.mp3");
  }

}

void loop()
{

  int buttonState = digitalRead(PIN_BUTTON_LEFT);
  bool leftButtonPressed = buttonState == LOW;
  if (leftButtonPressed){
    Serial.println("LEFT BUTTON PRESSED");
    if (volume > 0) volume--;
    audio.setVolume(volume/10);
    Serial.println(volume);
  }

  buttonState = digitalRead(PIN_BUTTON_RIGHT);
  bool rightButtonPressed = buttonState == LOW;
  if (rightButtonPressed){
    Serial.println("RIGHT BUTTON PRESSED");
    if (volume < 210) volume++;
    audio.setVolume(volume/10);
    Serial.println(volume);
  }

  audio.loop();

}

void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}