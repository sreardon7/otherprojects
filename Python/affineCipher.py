# y = ax + b, where y is cipher text and a is plaintext
#decryption is x = inverse(a) * (y - b)

def encrypt(clearText, key1, key2):
	cipherText = ""
	for i in range(0, len(clearText)):
		if(clearText[i] >= 'a' and clearText[i] <= 'z'):
			ch = ord(clearText[i])
			ch = ch - ord('a')
			ch = ch * key1 + key2
			ch = ch % 26
			ch = ch + ord('a')
			char = chr(ch)
			cipherText += char
		elif(clearText[i] >= 'A' and clearText[i] <= 'Z'):
			ch = ord(clearText[i])
			ch = ch - ord('A')
			ch = ch * key1 + key2
			ch = ch % 26
			ch = ch + ord('A')
			char = chr(ch)
			cipherText += char
		else:
			cipherText += clearText[i]
	return cipherText

def decrypt(cipherText, key1, key2):
	clearText = ""
	for i in range(0, len(cipherText)):
		if(cipherText[i] >= 'a' and cipherText[i] <= 'z'):
			ch = ord(cipherText[i])
			ch = ch - ord('a')
			ch = ch - key2
			ch = ch * key1
			ch = ch % 26
			ch = ch + ord('a')
			char = chr(ch)
			clearText += char	
		elif(cipherText[i] >= 'A' and cipherText[i] <= 'Z'):
			ch = ord(cipherText[i])
			ch = ch - ord('A')
			ch = ch - key2
			ch = ch * key1
			ch = ch % 26
			ch = ch + ord('A')
			char = chr(ch)
			clearText += char
		else:
			clearText += cipherText[i]
	return clearText


clearText = "Once upon a time in a land far far away"
cipherText = encrypt(clearText, 5, 1)
print(cipherText)
print(decrypt(cipherText, 21, 1))


