print("Sets")

items = { "red", "green", "yellow" }

print(items)

items.add("blue")
items.add("white")
items.add("green")

print(items)

conjunctions = {"for", "and", "nor", "but", "or", "yet", "so" }

seen = set()

poem = """I still hear your voice when you sleep next to me
I still feel your touch in my dreams
Forgive me my weakness, but I don't know why
Without you it's hard to survive
'Cause every time we touch, I get this feeling
And every time we kiss I swear I could fly
Can't you feel my heart beet fast, I want this to last
Need you by my side"""

data = poem.split()

for word in data:
   if str.lower(word) in conjunctions:
      seen.add(str.lower(word))

print(seen)
