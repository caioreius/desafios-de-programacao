import math

def triangle_area(a, b, c):
  s = (a + b + c) / 2
  return math.sqrt(s * (s - a) * (s - b) * (s - c))

def round_table_radius(a, b, c):
  if a + b <= c or a + c <= b or b + c <= a:
    return 0
  area = triangle_area(a, b, c)
  s = (a + b + c) / 2
  return area / s

while True:
  try:
    a, b, c = map(float, input().split())
    radius = round_table_radius(a, b, c)
    print("The radius of the round table is: {:.3f}".format(radius))
  except EOFError:
    break
