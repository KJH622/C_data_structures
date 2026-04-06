import sys

text = sys.stdin.read()

if not text:
    print("0 0 0")
else:
    line_count = len(text.splitlines())
    word_count = len(text.split())
    text_count = len(text)
    print(line_count, word_count, text_count)