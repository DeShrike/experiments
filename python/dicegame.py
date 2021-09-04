import random

num_games = 1000

def play_game():
    credits = 10
    rolls = 0
    while credits > 0 and credits < 1000:
        rolls += 1
        credits -= 1
        roll = random.randint(1, 6)
        if roll == 6:
            credits += 7

        # print(f"Games: {rolls} Credits: {credits}")
    return credits, rolls

def main():
    wins = 0
    losses = 0
    min_loss_rolls = 1_000_000
    max_loss_rolls = 0
    min_win_rolls = 1_000_000
    max_win_rolls = 0
    for g in range(num_games):
        cr, ro = play_game()
        if cr == 0:
            losses += 1
            if ro > max_loss_rolls:
                max_loss_rolls = ro
            if ro < min_loss_rolls:
                min_loss_rolls = ro
        else:
            wins += 1
            if ro > max_win_rolls:
                max_win_rolls = ro
            if ro < min_win_rolls:
                min_win_rolls = ro

        print(f"Wins: {wins} - Losses: {losses}")
        print(f"  Win Rolls: {min_win_rolls} to {max_win_rolls}")
        print(f"  Loss Rolls: {min_loss_rolls} to {max_loss_rolls}")
        print("")

if __name__ == "__main__":
    main()
