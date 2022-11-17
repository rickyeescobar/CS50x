from string import digits, ascii_letters, punctuation
from itertools import product

for passcode in product(ascii_letters + digits + punctuation, repeat=4):
    print(*passcode)