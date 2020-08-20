from random import shuffle, choice

def game(x, change = False):
   doors = ["goat", "goat", "car"]
   shuffle(doors)
   wins, losses = 0, 0

   def no_switch():
      nonlocal wins, losses
      if "car" == choice(doors):
         wins += 1
      else:
         losses += 1

   def switch():
      nonlocal wins, losses
      door = ["goat", "goat", "car"]
      d = door.pop(choice(range(len(doors))))
      door.remove("goat")
      second_choice = door[0]
      if second_choice == "car":
         wins += 1
      else:
         losses += 1

   for i in range(x):
      if change:
         switch()
      else:
         no_switch()

   print(f"Wins: {wins} - {(wins / x)}%")
   print(f"Losses: {losses} - {(losses / x)}%")


game(10000, False)
print("")
game(10000, True)

