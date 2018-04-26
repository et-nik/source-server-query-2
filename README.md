# Source Server Query 2 (Electric Boogaloo)

It's the same thing I did a couple years ago in Python. Now I've done it in C.
Works for source engine games like tf2 and csgo.
The source server query protocol is doucmented [here][1].

# Build

```
git clone https://github.com/Giggybyte/source-server-query-2
cd source-server-query-2
make
```
This will compile `ssq.c` and place the binary `ssq` in the folder.

# Usage

```
./ssq server port
```

# Example

```
[dws@refrigerator source-server-query]$ ./ssq 216.52.148.47 27015
Given parameters:
     Host: 216.52.148.47
     Port: 27015
[GFLClan.com]Zombie Escape 24/7 | Rank | Recruiting | NoBlock |
ze_ShroomForest3_p
csgo
Counter-Strike: Global Offensive
```

# To do

- Add ability to see players currently on server (A2S\_PLAYER)

[1]: https://developer.valvesoftware.com/wiki/Server_queries
