#define ABG_IMPLEMENTATION
#define ABG_SYNC_PARK_ROW
#define SPRITESU_IMPLEMENTATION
#define OLED_SH1106  //for arduboy mini, set ABG_REFRESH_HZ TO 95
#define SPRITESU_OVERWRITE
#define SPRITESU_PLUSMASK
#define SPRITESU_FX
#include <Wire.h>
#include "Adafruit_SHTC3.h"
#include <ArduboyFX.h>
#include "src/ArduboyG.h"
#include "src/SpritesU.hpp"
#include "fxdata/fxdata.h"
Adafruit_SHTC3 temp = Adafruit_SHTC3();  //environmental sensor (temp/humidity)

ArduboyG_Config<ABG_Mode::L4_Triplane> arduboy;
#include "func.h"

void setup() {

  arduboy.boot();
  arduboy.startGray();
  FX::begin(FX_DATA_PAGE, FX_SAVE_PAGE);
  // FX::disableOLED();
  //FX::begin(FX_DATA_PAGE);
  // FX::setCursorRange(0,128);
  FX::loadGameState(collection);
  Wire.setClock(400000);
  // TWSR = 0b00000011;
  //TWBR = 1;
  PRR0 &= ~_BV(PRTWI);
  temp.begin();
  temp.lowPowerMode(SHTC3_LOWPOW_MEAS_TFIRST_STRETCH);
  
  arduboy.setCursor(0, 0);
}

void loop() {

  FX::enableOLED();

  arduboy.waitForNextPlane(BLACK);
  FX::disableOLED();
  if (arduboy.needsUpdate()) {
    arduboy.pollButtons();
    update();
  }
  render();
}