# GAME OF CELLS <!-- INSERT LOGO HERE -->
#### Based on the classical <a href="https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life">Conway's Game of Life (1970)</a>,<br>but this time you are one of the cells!


<!-- INSERT SCREENSHOT HERE -->

---

### Index of game modes
<div>
    "Game of Cells" has several game modes:
    <ol>
        <li> Singleplayer
        <ul>
            <li> Tutorial
            <li> Highscore
            <li> Sandbox
            <li> Waves
        </ul>
        <li> Multiplayer (or vs bots)
        <ul>
            <li> Last-man Standing
            <li> Sector Conquest
            <li> Team Deathseekers
        </ul>
        <li> 0-player
        <ul>
            <li> Map Generation
            <li> Screensaver
            <li> Music
        </ul>
    </ol>
</div>

---

## Installation guide

Download this repo's ZIP, or fork it and then copy-paste following code snippets
(personalize repo directory name first)



### Dependencies

<code style="color:#66ffff;">gcc</code> for compile<br>
<code style="color:#66ffff;">make</code> for build<br>
<code style="color:#66ffff;">git</code> for contribute<br>

---

## Game Description

##### General rules:

Conway Game of Life rules, aka "underpopulation", "next generation", "overpopulation" and "reproduction" <br>
is condensed in SURVIVE (when a cell stay alive or die) and BORN (when a cell become alive).

Player command 1 cell, which is always alive (not killed by game of cells SURVIVE rules),<br>
and can move it in the 8 directions (N, NE, E, SE, S, SO, O, NO), or stay in the current position for a determined number of cycles.

After a move, the last position become a child, which is affected by SURVIVE and BORN rules.<br>

When every player has finished his/her/its move, then rules are applied.

If the cell controlled by one player is overlapped by a generated cell of another player, he/she/it is dead.<br>
Two controlled cells cannot destroy eachother.

SO, possible states of a cell are:<br>
* Dead cell
* Player cell
* contest cell
    * player-on-player: nothing happens
    * player-on-its-generation: if lobby rules permits it, it's ok
    * enemy-generation-on-player: the player is dead
    * generation-on-other-generation: depends on lobby rules (number of cells, matrix scan order, ecc...)
* alive cell (generated or map cell)

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

## License
_MIT License_

_Copyright (c) 2018 Basso Nicola_

_Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:_

_The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software._

_THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE._
