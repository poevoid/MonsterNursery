#include "Arduino.h"
#include "Arduboy2Core.h"
#include "vars.h"


void resetGame() {
  //egg.moodlevel = 50000000;
  screenwipe = false;
  light = { 64, 64, 5 };
  currentframe = 0;
  startcounter = 0;
  egg = { 70, 0, eggy, 49991000, false, false, false, false };
  monster.monsterSelect = random(0, 23);
}
void checkHealth() {
  temp.getEvent(&humidity, &t);
  if (t.temperature < minimumTemp) {
    egg.cold = true;
    egg.hot = false;
    egg.healthy = false;
  } else if (t.temperature > maximumTemp) {
    egg.hot = true;
    egg.cold = false;
    egg.healthy = false;
  } else {
    egg.healthy = true;
    egg.cold = false;
    egg.hot = false;
  }

  if (egg.cold) {
    egg.moodlevel--;
  }
  if (egg.hot) {
    egg.moodlevel--;
  }
  if (egg.healthy) {
    egg.moodlevel++;
  }
  if (egg.moodlevel == hatchlevel) {
    screen = Screen::Hatching;
  }
  if (egg.moodlevel == deathlevel) {
    screen = Screen::Death;
  }
}
void animateMonster() {
  if (startcounter % (framewait * 5) == 0) {
    if (currentframe < framecount) {
      currentframe++;

    } else {
      currentframe = firstframe;
    }
  }
  startcounter++;
}
void animate() {

  if (startcounter % (framewait * 5) == 0) {
    if (currentframe == framecount) {
      eggleft = true;
    }
    if (currentframe == firstframe) {
      eggleft = false;
    }

    if (eggleft == true) {
      currentframe--;
    }
    if (eggleft == false) {
      currentframe++;
    }
  }
  //if (startcounter % (7) == 0) {}
  ++startcounter;
}
void hatchEgg() {

  if (startcounter <= 100) {
    currentframe = 0;
  }
  if (startcounter > 100 && startcounter < 200) {
    currentframe = 1;
  }
  if (startcounter >= 200 && startcounter < 300) {
    currentframe = 2;
  }
  if (startcounter >= 300 && startcounter < 400) {
    currentframe = 3;
  }
  if (startcounter >= 400) {
    currentframe = 4;
  }
  if (startcounter >= 420) {
    screenwipe = true;  //clears the screen in a fun way that builds tenson for the monster reveal!
  } else {
    ++startcounter;
    screenwipe = false;
  }
}
void playerInput() {
  if (arduboy.pressed(LEFT_BUTTON)) { egg.x--; }
  if (arduboy.pressed(UP_BUTTON)) { egg.y--; }
  if (arduboy.pressed(DOWN_BUTTON)) { egg.y++; }
  if (arduboy.pressed(RIGHT_BUTTON)) { egg.x++; }
}


void update() {
  switch (screen) {
    case Screen::Title:
      if (arduboy.justPressed(A_BUTTON)) {

        arduboy.initRandomSeed();
        monster.monsterSelect = random(0, 23);
        screen = Screen::Game;
      }
      if (arduboy.justPressed(LEFT_BUTTON)) {
        collection.bunnolio = false;
        collection.goop = false;
        collection.magmalion = false;
        collection.unagi = false;
        arduboy.digitalWriteRGB(LOW, LOW, LOW);
        FX::saveGameState(collection);
        arduboy.digitalWriteRGB(HIGH, HIGH, HIGH);
        delay(150);
        arduboy.digitalWriteRGB(LOW, LOW, LOW); 
        FX::loadGameState(collection);
        arduboy.digitalWriteRGB(HIGH, HIGH, HIGH);
      }

      break;

    case Screen::Game:
      /*if (egg.sprite != eggy){
        egg.sprite = eggy;
        framecount = 4;
        currentframe = 0;
        startcounter = 0;
      }*/
      checkHealth();
      //playerInput();
      if (arduboy.pressed(UP_BUTTON)) {
        screen = Screen::Hatching;
      }
      animate();
      break;

    case Screen::Hatching:
      egg.x = 36;
      egg.sprite = hatchingegg;
      if (light.radius <= 126) {
        egg.sprite = hatchingegg;
        framewait = 2;
        framecount = 4;
      }
      hatchEgg();


      break;

    case Screen::Hatched:
      if (arduboy.justPressed(LEFT_BUTTON)) {
        resetGame();
        screen = Screen::Game;
      }
      if (arduboy.justPressed(RIGHT_BUTTON)) {
        resetGame();
        FX::loadGameState(collection);
        screen = Screen::Nursery;
      }
      if (monster.monsterSelect == 0) {
        monster.x = 48;
        monster.y = 5;
        monster.sprite = magmalion;
        collection.magmalion = true;
        framewait = 1;
        framecount = 19;
        animateMonster();
      }
      if (monster.monsterSelect == 1) {
        monster.sprite = bun;
        collection.bunnolio = true;
        monster.x = 48;
        monster.y = 5;
      }
      if (monster.monsterSelect == 2) {
        monster.sprite = goop;
        collection.goop = true;
        monster.x = 48;
        monster.y = 5;
      }
      if (monster.monsterSelect == 3) {
        monster.sprite = unagi;
        collection.unagi = true;
        monster.x = 48;
        monster.y = 5;
      }
      if (monster.monsterSelect == 4) {
        monster.sprite = spiker;

        monster.x = 48;
        monster.y = 5;
      }
      if (monster.monsterSelect == 5) {
        monster.sprite = octo;

        monster.x = 48;
        monster.y = 5;
      }
      if (monster.monsterSelect == 6) {
        monster.sprite = msnake;

        monster.x = 48;
        monster.y = 5;
      }
      if (monster.monsterSelect == 7) {
        monster.sprite = chicky;

        monster.x = 48;
        monster.y = 5;
      }if (monster.monsterSelect == 8) {
        monster.sprite = hypnot;

        monster.x = 48;
        monster.y = 5;
      }if (monster.monsterSelect == 9) {
        monster.sprite = hornet;

        monster.x = 48;
        monster.y = 5;
      }
      if (monster.monsterSelect == 10) {
        monster.sprite = bull;

        monster.x = 48;
        monster.y = 5;
      }if (monster.monsterSelect == 11) {
        monster.sprite = harpy;

        monster.x = 48;
        monster.y = 5;
      }if (monster.monsterSelect == 12) {
        monster.sprite = frex;

        monster.x = 48;
        monster.y = 5;
      }
      
      if (monster.monsterSelect == 13) {
        monster.sprite = horsey;

        monster.x = 48;
        monster.y = 5;
      }
      if (monster.monsterSelect == 14) {
        monster.sprite = fishy;

        monster.x = 48;
        monster.y = 5;
      }
      if (monster.monsterSelect == 15) {
        monster.sprite = froggy;

        monster.x = 48;
        monster.y = 5;
      }
      if (monster.monsterSelect == 16) {
        monster.sprite = shelly;

        monster.x = 48;
        monster.y = 5;
      }if (monster.monsterSelect == 17) {
        monster.sprite = crab;

        monster.x = 48;
        monster.y = 5;
      }
      if (monster.monsterSelect == 18) {
        monster.sprite = puppy;

        monster.x = 48;
        monster.y = 5;
      }
      if (monster.monsterSelect == 19) {
        monster.sprite = lizard;

        monster.x = 48;
        monster.y = 5;
      }
      if (monster.monsterSelect == 20) {
        monster.sprite = chimp;

        monster.x = 48;
        monster.y = 5;
      }if (monster.monsterSelect == 21) {
        monster.sprite = goatwiggle;

        monster.x = 48;
        monster.y = 5;
        framecount =19;
        animateMonster();
      }
      if (monster.monsterSelect == 22) {
        monster.sprite = tortoise;

        monster.x = 48;
        monster.y = 5;
      }
      FX::saveGameState(collection);
      break;

    case Screen::Gallery:

      break;

    case Screen::Nursery:
      if (arduboy.justPressed(A_BUTTON)) {
        resetGame();
        screen = Screen::Game;
      }
      animateMonster();
      break;

    case Screen::Death:
      framecount = 3;
      egg.sprite = badegg;
      animate();
      if (arduboy.justPressed(A_BUTTON)) {
        screen = Screen::Title;
      }
      if (arduboy.justPressed(B_BUTTON)) {
        resetGame();
        screen = Screen::Game;
      }
      break;
  }




  // if ()
}


void render() {
  uint16_t currentPlane = arduboy.currentPlane();

  switch (screen) {
    case Screen::Title:


      if (currentPlane <= 0) {  //dark gray
      }

      if (currentPlane <= 1) {  //gray
      }

      if (currentPlane <= 2) {  //white
        arduboy.setCursor(0, 0);
        arduboy.println("Monster Nursery");
        if (!FX::loadGameState(collection)) {
          arduboy.setCursor(0, 32);
          arduboy.println("No save data detected!");
        }
      }
      break;

    case Screen::Game:
      framecount = 4;
      egg.sprite = eggy;
      SpritesU::drawOverwriteFX(egg.x, egg.y, egg.sprite, FRAME(currentframe));

      //arduboy.setCursor(0,0);
      //
      if (currentPlane <= 0) {
        arduboy.setCursor(0, 0);
        arduboy.print(egg.moodlevel);
      }

      if (currentPlane <= 1) {
        arduboy.setCursor(0, 10);
        arduboy.println(egg.x);
      }

      if (currentPlane <= 2) {
        arduboy.setCursor(0, 20);
        arduboy.print("T");
        arduboy.println(t.temperature);
      }
      break;

    case Screen::Hatching:

      if (currentPlane <= 2) {
        arduboy.setCursor(0, 20);
        arduboy.print("Oh..?");
      }

      if (light.radius <= 126) {

        SpritesU::drawOverwriteFX(egg.x, egg.y, egg.sprite, FRAME(currentframe));
      }

      if (screenwipe) {

        arduboy.fillCircle(light.centerX, light.centerY, light.radius, WHITE);
        if (light.radius < 150) {
          light.radius += 5;
        } else {
          FX::saveGameState(collection);
          screen = Screen::Hatched;
        }
      }
      //if (currentPlane <= 0) {
      // arduboy.setCursor(0, 0);
      //arduboy.print(light.radius);
      //}

      break;
    case Screen::Hatched:

      SpritesU::drawOverwriteFX(0, monster.y + 10, eggcon, currentPlane);
      SpritesU::drawOverwriteFX(0, monster.y + 30, dpad, FRAME(2));  ///0 = up ; 1 = down; 2 = left ; 3 = right
      SpritesU::drawOverwriteFX(WIDTH - 16, monster.y + 10, hydraicon, currentPlane);
      SpritesU::drawOverwriteFX(WIDTH - 16, monster.y + 30, dpad, FRAME(3));


      if (monster.monsterSelect == 0) {

        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, FRAME(currentframe));
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("A Magmalion! Wow!");
        }
      }
      if (monster.monsterSelect == 1) {

        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("It's a Bunnolio!");
        }
      }
      if (monster.monsterSelect == 2) {

        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("A Goop! It stinks...");
        }
      }
      if (monster.monsterSelect == 3) {

        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("Be careful with the Unagi...");
        }
      }
      if (monster.monsterSelect == 4) { //spiker
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("Be careful with the Unagi...");
        }
      }
      if (monster.monsterSelect == 5) {//octo
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("An Octo!");
        }
      }
      if (monster.monsterSelect == 6) {//msnake
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("aww a snek!");
        }
      }
      if (monster.monsterSelect == 7) {//chicky
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("Bruh. That's jus a chicken.");
        }
      }if (monster.monsterSelect == 8) {//hypnot
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("ALL HAIL HYPNOTAPIR");
        }
      }if (monster.monsterSelect == 9) {//hornet
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("A hornet! Get it?");
        }
      }
      if (monster.monsterSelect == 10) {//bull
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("The Divine Bull");
        }
      }if (monster.monsterSelect == 11) {//harpy
       SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("A weird lookin harpy...");
        }
      }if (monster.monsterSelect == 12) {//frex
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("Fungusaurus Rex?!");
        }
      }
      
      if (monster.monsterSelect == 13) {//horsey
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("That horse is HOT");
        }
      }
      if (monster.monsterSelect == 14) {//fishy
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("Ah, The Dread Carp, Leavo.");
        }
      }
      if (monster.monsterSelect == 15) {//froggy
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("A dead frog? No, a deathfrog!");
        }
      }
      if (monster.monsterSelect == 16) {//shelly
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("Shellyyy lookit so cute");
        }
      }if (monster.monsterSelect == 17) {//crab
       SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("Crab Y_(*||*)_Y ");
        }
      }
      if (monster.monsterSelect == 18) {//puppy
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("Aww, a puppy!");
        }
      }
      if (monster.monsterSelect == 19) {//lizard
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("Baloonor. Biiiiig neck.");
        }
      }
      if (monster.monsterSelect == 20) {//chimp
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("Yo, this chimp IS a bug.");
        }
      }if (monster.monsterSelect == 21) {//goat
       SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("My, my. This is Satan's Goat, Herb.");
        }
        animateMonster(); 
      }
      if (monster.monsterSelect == 22) {//tortoise
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, 0);
        if (currentPlane <= 2) {
          arduboy.setCursor(0, 55);
          arduboy.print("Holy shit! Adamantoise");
        }
      }
      break;

    case Screen::Gallery:

      break;

    case Screen::Nursery:
      framecount = 19;
      if (collection.goop) {
        monster.sprite = goopsphere;
        monster.x = 18;
        monster.y = 0;

        SpritesU::drawPlusMaskFX(monster.x, monster.y, monster.sprite, FRAME(currentframe));
      }
      if (collection.magmalion) {
        monster.sprite = magmalionsphere;
        monster.x = 56;
        monster.y = 0;

        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, FRAME(currentframe));
      }
      if (collection.unagi) {
        monster.sprite = unagisphere;
        monster.x = 36;
        monster.y = 0;
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, FRAME(currentframe));
      }
      if (collection.bunnolio) {
        monster.sprite = bunsphere;
        monster.x = 0;
        monster.y = 0;
        SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, FRAME(currentframe));
      }
      /*
      monster.sprite = spikersphere;
      monster.x = 54;
      monster.y = 0;
      framecount = 19;
      SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, FRAME(currentframe));
      monster.sprite = chimpsphere;
      monster.x = 54+18;
      monster.y = 0;
      framecount = 19;
      SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, FRAME(currentframe));
      monster.sprite = puppysphere;
      monster.x = 54+18+18;
      monster.y = 0;
      framecount = 19;
      SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, FRAME(currentframe));
      monster.sprite = hensphere;
      monster.x = 54+18+18+18;
      monster.y = 0;
      framecount = 19;
      SpritesU::drawOverwriteFX(monster.x, monster.y, monster.sprite, FRAME(currentframe));
      */
      break;

    case Screen::Death:


      SpritesU::drawOverwriteFX(egg.x, egg.y, egg.sprite, FRAME(currentframe));
      if (currentPlane <= 0) {  // darktext
        arduboy.setCursor(0, 0);
        arduboy.println("Oh gosh...");
        arduboy.println("he died :(");
      }

      break;
  }
}