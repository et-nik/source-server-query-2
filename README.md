# Source Server Query 2 (Electric Boogaloo)

It's the same thing I did a couple years ago in Python. Now I've done it in C.
Works for source engine games like tf2 and csgo.
The source server query protocol is doucmented [here][1].

# Build

```
git clone https://github.com/et-nik/source-server-query-2
cd source-server-query-2
make
```
This will compile `ssq.c` and place the binary `ssq` in the folder.

# Usage

```
./ssq server port
```

# Examples

```
[nik@source-server-query]$ ./ssq hldm.org 27018
Given parameters:
     Host: hldm.org
     Port: 27018
GunGame 2.1 - HLDM.ORG
the_beach
valve
Half-Life
```

# To do

- Add ability to see players currently on server (A2S\_PLAYER)

[1]: https://developer.valvesoftware.com/wiki/Server_queries
