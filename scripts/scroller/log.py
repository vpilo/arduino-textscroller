import sys

_VERBOSE = True

def l(message):
  print(message)

def v(message):
  if _VERBOSE:
    print(message)

def e(message):
  print(message, file=sys.stderr)
  exit(1)
