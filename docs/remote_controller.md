# Orion remote controller description.

![Orion Mini remote](../media/orion_mini_remote.jpg)

Orion Mini remote is heavily modifier RC helicopter controller. In terms of controls, it provides

* 4 analog joypads
  * 2 from original remote
    * Left one has static Y axis and springed X axis
    * Right one is standard springed joypad
  * 2 chinese ones, added by Dr. Maciejewski
    * Very poor quality, enormous dead zone, but at least they have buttons
* 4 analog knobs (two in front, two upper ones)
* 2 three-position switches (down-off-up) located behind upper knobs, not visible on photo
* 5 clicky buttons on the front
* Power switch at the centre
* Calibration sliders for original joypads

In terms of electronics, it has been mostly reworked by Dr. Maciejewski
* Modified power supply, made from several 3.7V li-ion cells
* TP4056 module with safety circut and MicroUSB input for charging
* Battery voltage indicator
* nRF24L01 communication module with external antenna
* USB port for charging on the top, next to antenna, providing 500mA@5V DC throught step-up module from mentioned li-ion cells
* Arduino Mega as motherboard

Since this remote is a literal beast, i intend to create software which will allow to utilize it not only for Orion Mini, but also for different robots (like original Orion rover) with little effort.