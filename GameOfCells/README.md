# GAME OF CELLS <!-- INSERT LOGO HERE -->
#### Based on the classical <a href="https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life">Conway's Game of Life (1970)</a>,<br>but this time you are one of the cells!


<!-- INSERT SCREENSHOT HERE -->

---

### Index of game modes

*Game of Cells* has several game modes:
1. **Singleplayer**
    - Tutorial
    - Highscore
    - Sandbox
    - Waves
1. **Multiplayer** (or vs bots)
    - Last-man Standing
    - Sector Conquest
    - Team Deathseekers
1. **0-player**
    - Map Generation
    - Screensaver
    - Music

---

## Installation guide

### RELEASES

Choose any executable from [releases](https://github.com/Lince99/ASCIIGames/tree/dev/GameOfCells/releases) folder, simple as is.
<br><br>
#### CONTRIBUTORS ONLY

For beginners I think MarcDiethelm guide is a good start: [HowToContribute](https://github.com/MarcDiethelm/contributing/blob/master/README.md).<br>
Or use Joshnh list of commonly used Git commands, which is also useful for beginners:
[HowToGit](https://github.com/joshnh/Git-Commands).<br>
Or this official github guide:
[Contributing on Github](https://github.com/MarcDiethelm/contributing/blob/master/README.md).

**Dependencies**

- gcc for compile:
```bash
#For Ubuntu-based machines
sudo apt-get update && sudo apt-get install gcc -y
```
- make for build:
```bash
#For Ubuntu-based machines
sudo apt-get install make -y
```
- git for contribute:
```bash
#For Ubuntu-based machines
sudo apt-get install git -y
```


**Step by Step guide** <br>

First clone this repo:
```bash
git clone https://github.com/Lince99/ASCIIGames
git checkout master #or dev or everything else you want work onto
```
Do something useful following code style of the project.<br>
Then push to your local branch:
```bash
#go on you higher level of project directory
git add .
git commit -am "Some useful and descriptive message"
git push upstream master #or dev or everything else
```

And when you're ready, create a new PR (push request):
```bash
git push -u origin master
```

---

## Game Description

##### General rules:

Conway Game of Life rules, <br>
aka "underpopulation", "next generation", "overpopulation" and "reproduction"<br>
int Game Of Cells are condensed into two arrays of rules: <br>
> SURVIVE_RULE (when a cell stay alive or die)<br>
> BORN_RULE (when a cell become alive)

Player controls 1 cell, which is always alive (not killed by SURVIVE_RULE rules),<br>
and it can moves in the 8 directions (N, NE, E, SE, S, SO, O, NO), <br>
or stay in the current position for a determined number of cycles.
> After a move, the last player position become a child,<br>
> which is affected by SURVIVE and BORN rules.

When every player has finished his/her/its move, then arrays of rules are applied.<br>
> If the cell controlled by one player<br>
>  is overlapped by a generated cell of another player, <br>
> he/she/it is dead.<br>
Two player-controlled cells cannot destroy each other.


*SO, possible states of a cell are:<br>*
* **Dead cell**
* **Player cell**
* contested cell
    * **player-on-player**: nothing happens
    * **player-on-its-generation**: if lobby rules permits it, it's ok
    * **enemy-generation-on-player**: the player is dead
    * **generation-on-other-generation**: depends by the lobby rules<br> (number of cells, matrix scan order, ecc...)
* **alive cell** (generated or map cell)

---

## Game modes


### Singleplayer

##### Tutorial
In this mode you can learn and practice with various rules and patterns

##### Highscore
This gamemode permit to test your skills in this game,<br>
then your scoreboard can be uploaded to check who is the best at this game!

##### Sandbox
Here you can destroy Game of Cells

##### Waves
This gamemode try to kill you with patterns of generated waves, <br>faster and faster,<br>
too fast that will become unpredictable to avoid the death.


### Multiplayer

##### Last-man Standing
Requiring an Internet connection, you can play versus other players in the world,<br>
where the one who survive in his current map, win.<br>
Every lobby can have modified rules and personalized maps.

##### Sector Conquest
Map is divided in equal or incremental parts, where players have to conquest.<br>
To get 1 sector you have to fill it with your childs.
To get access to the neighbourhood sectors, you have to add your childs into it,
you can't move inside it without these.

##### Team Deathseekers
Red vs Blue, classic team deathmatch where win depends on the kills counter.


### 0-player

##### Map Generation
With specific rules, this mode can generate maze or Game_of_cells Singleplayer/Multiplayer maps

##### Screensaver
Using some pre-generated draws, it runs without any type of required interaction<br>
Only "pause/stop" or "prev/next draw" options can be used

##### Music
What can you do with a sequence of bits and a bitrate?<br>(with colors you can add different tones)


---

## Contributing

Help these poor bytes with throwing to they [SO MANY ISSUES](https://github.com/Lince99/ASCIIGames/issues) .<br>
Remember to always follow [Code of Conduct](https://github.com/Lince99/ASCIIGames/tree/dev/GameOfCells/CODE_OF_CONDUCT.md) .

---

## License
This project is under MIT license, you can find a copy at [LICENSE](https://github.com/Lince99/ASCIIGames/tree/dev/GameOfCells) .
