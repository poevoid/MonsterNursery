#pragma once

#define FRAME(x) x * 3 + arduboy.currentPlane()
#define MAX_FPS 10
int eggx = 70;
int y = 0;

struct Egg {
  uint8_t x, y;
  uint24_t sprite;
  long moodlevel;
  bool healthy;
  bool cold;
  bool hot;
  bool hatching;

};

struct Collection {
  bool magmalion = false;
  bool goop =false;
  bool bunnolio=false;
  bool unagi=false;
};

enum class Screen : uint8_t {
  Title,
  Game,
  Hatching,
  Hatched,
  Gallery,
  Nursery,
  Death
};

struct Monster {
  uint8_t x,y;
  uint8_t monsterSelect;
  uint24_t sprite;
  uint8_t frames;
};

struct Light {
  int centerX;
  int centerY;
  int radius;
 
};
Collection collection;
Light light = {64, 64, 5};
Monster monster = {32, 0, 1, unagi, 20};
Egg egg = {70, 0, eggy, 49991000, false, false, false ,false};
Screen screen = {Screen::Title};
float minimumTemp = 28.7;
float maximumTemp = 37.8;
bool eggleft = false;
uint8_t currentframe = 0;
bool screenwipe = false;
uint8_t firstframe = 0;
int last_frame = -1;
uint8_t framewait = 2;
int prevTime=0;
long hatchlevel = 50005000;
long deathlevel = 49990000;
sensors_event_t humidity, t;
uint8_t gamestate =0;

uint8_t framecount = 4; //1 less than actual number of frames, first frame = 0
int startcounter = 0;
