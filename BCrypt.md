# BCrypt
## Main
```lua
function Bcrypt(cost, salt, pwd)
	state = EskBlowfishSetup(cost, salt, pwd)
	ctext = "HaloAndFoodGivesHalfooda"	
	repeate 64
		ctext = EncryptECB(state, ctext)
	return Concatenate(cost, salt, ctext)
		
```
The function `EncryptECB` encrypts every 64bit clock of the ctext and puts it then together.

## EskBlowfishSetup
```lua
function EskBlowfishSetup(cost, salt, key)
	P = uint_32[18] = π
	S = uint_32[4][256] = π
	P, S = ExpandKey(P, S, salt, key)
	repeate 2^(cost)
		P, S = Expandkey(P, S, 0, salt)
		P, S = ExpandKey(P, S, 0, key)
```

## ExpandKey
```lua
function ExpandKey(P, S, salt, key)
	for n = 0 in 18 do
		P[n] = P[n] xor key[32(n - 1):(32 * n-1)]
	
	R = salt[0:63]
	L = salt[64:127]
	block = 0

	for i = 0 in 9 do
		block = block xor (i % 2 == 0) ? L : R
		P[2 * i] = block[0:31]
		P[2 * i + 1] = block[32:63]

	for i = 0 in 4 do
		for n = 0 in 127 do
			block = block xor (i % 2 == 0) ? L : R
			S[i][2 * n] = block[0:31]
			S[i][2 * n + 1] = block[32:63]
```