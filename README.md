# CasaliShooter instructions

*This note provides some useful instructions (to ?) for a good use of the game.*
*It's splited in two parts : the first one is about the menu and the last one is concerning the game itself.*


============================================================================================

### __Menu__
The following part contains all the informations needeed for a proper use of the menu.

`z` <-- Allows you to move in the menu. Pressing this key will direct you to the button above.

`s` <-- Allows you to move in the menu. Pressing this key will directo you to the button at the bottom.

`ENTER` <-- Allows you to select the button at your current position in the menu.

============================================================================================


### __Game__
The following part contains all the informations needeed for good game experience.

`q` <-- Allows you to move your sprite to the left.

`d` <-- Allows you to move your sprite to the right.

`x` <-- Allows you to shoot a missile.

============================================================================================


### __YAML__
All the previous cases are variable and can be change in the `config.yaml` file.

Other option can be change in the `config.yaml` file, like the size of the missile.

The basic file looks like this : 

```yaml
KMovingDownMenu : 115
KMovingUpMenu : 122
KMovingLeftGame : 113
KMovingRightGame : 100
KShootGame : 120
KWidthMissile : 2
KLenghtMissile : 10
KWidthTorpedoPPs : 5
KLenghtTorpedoPPs : 10
KWidthTorpedoUFO : 5
KLenghtTorpedoUFO : 10
```

**/!\\** The first four numbers are ASCII references and must be changed by ASCII reference **/!\\**
