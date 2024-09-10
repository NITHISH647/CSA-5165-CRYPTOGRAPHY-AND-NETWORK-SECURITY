 def decrypt_simple_substitution(ciphertext, key):
 decryption = ""
 for char in ciphertext:
 if char.isalpha():
 decrypted_char = key[char]
 decryption += decrypted_char
 else:
 decryption += char
 return decryption
 