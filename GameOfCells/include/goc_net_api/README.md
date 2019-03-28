## Game of Cells Network libraries

### Contents

#### *Server side functions*

- Receive players data from each client when they connect to one lobby
- Receive players position with POLL_RATE
- Receive admin commands about:
    - Managing lobby
    - Managing current match
    - Managing connected players
    - Managing general rules (aka other rules)
- Generate players' children cells and manage GOC cell states

#### Server RULES:

- POLL_RATE : how many times server receives data from clients (data/s)
- SERVER_IP : server public IP (or local for LAN matches)
- SERVER_PORTS : list of ports range and type
- LOBBY_LIST : list of rooms where players can connect to
- LOBBY_PLAYER_LIST : list of connected players on the current active lobby
- LOBBY_BAN_LIST : list of players banned from the lobby
- LOBBY_MIN_PLAYERS : minimum players requested to start a match
- LOBBY_MAX_PLAYERS : number of maximum players connected on one lobby
- LOBBY_ADMIN : player name promoted from one present on LOBBY_PLAYER_LIST
- LOBBY_MAX_TIME : maximum play time for one match
- LOBBY_MAX_SCORE : the first player who reach this score win and the match ends
- LOBBY_BOT_ENABLE : flag that, when it's set on true, fill lobby with bots
- LOBBY_BOT_MAX : maximum number of bots present on the lobby
- MAP_CURRENT : get current running map data
- MAP_SET : stop current running match to change map
- MAP_ALLOW_DYN_RESIZE : allow dynamic map resizing while the match is running
- MAP_MAX_SIZE_Y : limit number of rows on the map (require MAP_ALLOW_DYN_RESIZE set to false)
- MAP_MAX_SIZE_X : limit number of columns on the map (require MAP_ALLOW_DYN_RESIZE set to false)

---

#### *Client side functions*

- When the user enter into the online mode, the game request PLAYER_NAME and PLAYER_COLOR
- Send player data to server (name, color)
- Send player position following POLL_RATE
- Send chat messages and commands asynchronously
- Receive updates:
    - Lobby changes (new players, rules changes, ...)
    - Match changes (start, dead, win, ...)
    - Map changes (players positions, generated cells, ...)
    - Chat messages (asynchronously from the game)

#### Client RULES:

- PLAYER_NAME : player name that hasn't to be unique (unique tag added by server at creation time)
- PLAYER_COLOR : player preferred color (PeRsOnAlIzAtIoN), easily overwritten by server necessity (1 unique color per player on the same lobby)
- PLAYER_IP : public IP read by the server for unique identification
- PLAYER_STATS : structure containing player statistics
- CHAT_ENABLE : hide or show chat during matches

---

## Contributing

Help these poor bytes with throwing to they [SO MANY ISSUES](https://github.com/Lince99/ASCIIGames/issues) .<br>
Remember to always follow [Code of Conduct](https://github.com/Lince99/ASCIIGames/tree/dev/GameOfCells/CODE_OF_CONDUCT.md) .

---

## License
This project is under MIT license, you can find a copy at [LICENSE](https://github.com/Lince99/ASCIIGames/tree/dev/GameOfCells) .
