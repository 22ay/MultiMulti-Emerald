#!/usr/bin/env python3
import sys
import re
from collections import Counter

ROM = sys.argv[1] if len(sys.argv) > 1 else 'pokeemerald.gba'
CHART = 'charmap.txt'

# Build mapping from byte values (hex in charmap) to characters
mapping = {}
for line in open(CHART, 'r', encoding='utf-8', errors='ignore'):
    line=line.strip()
    if not line or line.startswith('@') or line.startswith('#'):
        continue
    m = re.match(r"^'(.+?)'\s*=\s*([0-9A-Fa-f]{2})$", line)
    if m:
        ch, hx = m.groups()
        try:
            b = int(hx,16)
            mapping[b] = ch
        except:
            pass
    else:
        # some lines have NAME = HEX or multi-byte sequences; ignore
        m2 = re.match(r"^([A-Z0-9_]+)\s*=\s*([0-9A-Fa-f]{2})(?:\s+([0-9A-Fa-f]{2}))*", line)
        if m2:
            name, hx = m2.group(1), m2.group(2)
            # ignore tokens
            continue

# Add space mapping
mapping[0x00] = ' '
# safe fallback for common bytes
for b in range(0xBB, 0xBB+26):
    mapping[b] = chr(ord('A') + (b - 0xBB))
for b in range(0xD5, 0xD5+26):
    mapping[b] = chr(ord('a') + (b - 0xD5))
for i,b in enumerate(range(0xA1, 0xA1+10)):
    mapping[b] = str(i)
# common punctuation
punct = {0xAD:'.',0xAE:'-',0xAB:'!',0xAC:'?',0xB8:',',0xBA:'/'}
for k,v in punct.items(): mapping[k]=v

# LZ77 decompressor for GBA
def lz77_decompress(data):
    if len(data) < 4 or data[0] != 0x10:
        return None
    size = data[1] | (data[2]<<8) | (data[3]<<16)
    out = bytearray()
    pos = 4
    while len(out) < size and pos < len(data):
        flag = data[pos]; pos += 1
        for i in range(8):
            if flag & 0x80:
                if pos+1>=len(data): return None
                b1 = data[pos]; b2 = data[pos+1]; pos+=2
                disp = ((b1 & 0xF) << 8) | b2
                length = (b1 >> 4) + 3
                start = len(out) - disp - 1
                if start < 0: return None
                for _ in range(length):
                    out.append(out[start]); start+=1
            else:
                if pos >= len(data): return None
                out.append(data[pos]); pos+=1
            flag = (flag << 1) & 0xFF
            if len(out) >= size:
                break
    return bytes(out)

rom = open(ROM,'rb').read()
N = len(rom)
print('ROM size',N)

candidates = Counter()

# Scan for LZ77 blocks
for i in range(N-4):
    if rom[i] == 0x10:
        dec = lz77_decompress(rom[i:])
        if dec and len(dec) > 10:
            # extract sequences of 3..24 bytes consisting of mapped bytes
            j=0
            L=len(dec)
            while j<L:
                # find next run
                if dec[j] in mapping:
                    k=j
                    while k<L and dec[k] in mapping and (k-j)<40:
                        k+=1
                    s = bytes(dec[j:k])
                    if len(s)>=3 and len(s)<=24:
                        # decode
                        try:
                            text = ''.join(mapping.get(b,'?') for b in s).strip()
                        except Exception:
                            text = None
                        if text and re.search(r'[A-Za-z]', text):
                            candidates[text]+=1
                    j=k
                else:
                    j+=1

            # Also decode full decompressed block and look for Title-like words
            dec_text = ''.join(mapping.get(b,'?') for b in dec)
            for m in re.finditer(r"\b[A-Z][A-Za-z\-]{2,18}(?: [A-Z][A-Za-z\-]{2,18})?\b", dec_text):
                txt = m.group(0)
                candidates[txt]+=1

# Also scan raw ROM for sequences of mapped bytes
j=0
while j<N:
    if rom[j] in mapping:
        k=j
        while k<N and rom[k] in mapping and (k-j)<40:
            k+=1
        s = rom[j:k]
        if 3 <= len(s) <= 24:
            text = ''.join(mapping.get(b,'?') for b in s).strip()
            if text and re.search(r'[A-Za-z]', text):
                candidates[text]+=1
        j=k
    else:
        j+=1

# Print top candidates that look like ability names
print('\nTop candidate strings:')
for txt,count in candidates.most_common(400):
    # filter out obvious junk
    if len(txt) < 3: continue
    if re.match(r'^[A-Za-z-!\.\/ ]+$', txt):
        print(f'{count:4d}  {txt}')

# Print candidates containing keywords
keywords = ['rain','boost','damage','critical','repel','contact','protect','heal','raises','restore','increases','silence','paral','poison']
print('\nCandidates containing keywords:')
for txt,count in candidates.most_common(2000):
    low = txt.lower()
    if any(k in low for k in keywords):
        print(f'{count:4d}  {txt}')

# Dump unique candidates to file for manual review
with open('ability_candidates.txt','w',encoding='utf-8') as fh:
    for text,count in sorted(candidates.items(), key=lambda kv: -kv[1]):
        fh.write(f"{count:4d} {text}\n")
print('\nWrote ability_candidates.txt')
