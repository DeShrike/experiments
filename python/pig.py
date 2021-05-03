# See https://www.youtube.com/watch?v=ULhRLGzoXQ0

import random

NUM_GAMES = 100_000
TURNS_PER_GAME = 100

def play(rolls):
   totscore = 0
   deads = 0
   for _ in range(TURNS_PER_GAME):
      score = 0
      for i in range(rolls):
         dice = random.randint(1, 6)
         if dice == 1: # this should be a 1
            score = 0
            deads += 1
            break
         score += dice

      totscore += score

   return totscore, deads

def simulate(rolls):
   totscore = 0
   totdeads = 0
   for g in range(NUM_GAMES):
      if g % 100 == 0:
         p = g / NUM_GAMES * 100
         print(f"{g} / {NUM_GAMES} ({p:2f}% )  ", end = "\r", flush = True)
      score, deads = play(rolls)
      totscore += score
      totdeads += deads
   print("")
   return totscore / NUM_GAMES, totdeads / NUM_GAMES

def main():
   stats = {}
   for rolls in range(1,10):
      print(rolls)
      avg, avgdeads = simulate(rolls)
      stats[rolls] = (avg, avgdeads)

   for a in stats:
      print(f"{a} rolls: Average score: {stats[a][0]} - {stats[a][1]} deads")

if __name__ == "__main__":
   main()

