# Askli Art
**Terminal ascii art paint tool with ncurses and shortcuts**

![Figure 1-1](examples/askli_art_screenshot1.jpg?raw=true)

---

## Compile

Required libraries:
- libncurses-dev libncurses5-dev
- gcc
- make

```bash
make compile
```

## Usage

Simply run it into any kind of terminal that support basic colors
```bash
./askliart
```

In the example folder you can find the name of this program made in askliart.

---

## Commands

* CTRL+q to quit
* arrows, tab, SHIFT+tab, home, end to change cursor position
* SHIFT+home return at the start of the line
* SHIFT+end goes at the end of the line
* TAB skip 4 chars at time
* SHIFT+TAB goes back 4 chars at time
* CTRL+r to reset canvas (and ask for queue reset)
* CTRL+z to undo
* CTRL+y to redo
* CRTL+m to switch from sequential input to same-position input or viceversa
* CTRL+s to save
* CTRL+l to load any compatible file (and ask to load queue if it's present)
