# ax + b = y affine cipher where x is the plain text and y is the cipher text

#hacks an affine cipher, 


#inverses for decryption
def computeInverses():
	inverses = [[1,1], [3,9], [5,21], [7,15], [9,3], [11,19], [15,7], [17,23], [19,11], [21,5], [23,17], [25,25]]
	return inverses


def crackAffineCipher(cipherText, match):
	x = len(match)
	cipher = cipherText[0:x]
	inverses = computeInverses()
	print(cipher)
	for i in range(0, 12):
		for j in range(0, 26):
			queryString = ""
			for k in range(0, len(cipher)):
				if(cipher[k] >= 'a' and cipher[k] <= 'z'): 
					ch = ord(cipher[k])
					ch = ch - ord('a')
					ch = ch - j
					ch = ch * inverses[i][1]
					ch = ch % 26
					ch = ch + ord('a')
					char = chr(ch)
					queryString += char
				elif(cipher[k] >= 'A' and cipher[k] <= 'Z'): 
					ch = ord(cipher[k])
					ch = ch - ord('A')
					ch = ch - j
					ch = ch * inverses[i][1]
					ch = ch % 26
					ch = ch + ord('A')
					char = chr(ch)
					queryString += char
				else:
					queryString += cipher[k]
				#print(queryString)
				if(queryString == match):
					keypair = [0] * 2
					keypair[0] = inverses[i][0]
					keypair[1] = j
					return (keypair)
	return (None)
			

		
#got these from the affine cipher, Onc is the plaintext pairs with Tol
key = crackAffineCipher("Tolv xyto b spjv po b eboq abi abi bhb", "Onc")
if (key != None):
	print(key[0], key[1])
else:
	print("failed")

