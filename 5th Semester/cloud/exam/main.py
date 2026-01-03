import json
import random
import time


class bcolors:
    CORRECT = '\033[92m'
    INCORRECT = '\033[91m'
    NORMAL = '\033[0m'
    BLUE = '\033[94m'


# Import questions from questions.json
print("Welcome to the quiz!")
print(
    "You will be asked a series of multiple choice questions, and you must answer them correctly. Write with lowercase all the corresponding letters of the answers you think are correct")
print("For the answers that are not multiple choice, write the answer you think is correct")

# Load questions from the JSON file
questions = []
with open('questions.json', 'r', encoding='utf-8-sig') as f:
    questions = json.load(f)

while True:
    # Ask user how many questions they want to answer
    user_input = input("How many questions do you want to answer?(write all if you want to answer all questions): ")
    nr_of_questions = len(questions)
    if user_input != "all":
        user_input = int(user_input)
        if user_input < nr_of_questions:
            nr_of_questions = user_input

    user_score = 0
    indexes_of_questions = [i for i in range(len(questions))]  # Track asked questions
    wrong_questions = []
    shuffle = False
    user_input = input("Do you want to shuffle the options?(y/n): ")
    if user_input.lower() == "y":
        shuffle = True
    for i in range(nr_of_questions):
        # Select a random question
        index_of_question = random.choice(indexes_of_questions)
        indexes_of_questions.remove(index_of_question)
        q = questions[index_of_question]

        if shuffle:
            random.shuffle(q['answers'])

        print(bcolors.NORMAL + "Question " + str(i + 1) + "/" + str(nr_of_questions))
        print(bcolors.NORMAL + q['question'])

        for i, answer in enumerate(q['answers']):
            print(f"{chr(i + 97)}) {answer['statement']}")

        # Get user input
        user_answer = input("Your answer: ").strip()
        correct_answers = [chr(97 + idx) for idx, ans in enumerate(q['answers']) if ans['correct']]

        # Check if user input is correct
        if sorted(user_answer) == sorted(correct_answers):
            print(bcolors.CORRECT + "Correct!")
            user_score += 1
        else:
            print(bcolors.INCORRECT + "Incorrect!")
            print("The correct answer was: " + "".join(correct_answers))
            wrong_questions.append((q, user_answer))

    # Convert user score to percentage
    user_score = user_score / nr_of_questions * 100
    print(bcolors.BLUE + "You got " + str(user_score) + "%\n")

    # Review mistakes
    user_input = input(bcolors.NORMAL + "Do you want to review your mistakes?(y/n): ")
    if user_input.lower() == "y":
        for (q, user_answer) in wrong_questions:
            print(bcolors.NORMAL + q['question'])
            for i, answer in enumerate(q['answers']):
                print(f"{chr(i + 97)}) {answer['statement']}")
            print(f"Your answer was: {user_answer}")
            correct_answers = "".join([chr(97 + idx) for idx, ans in enumerate(q['answers']) if ans['correct']])
            print(f"The correct answer was: {correct_answers}")

    # Ask user if they want to play again
    user_input = input("Do you want to play again?(y/n): ")
    if user_input.lower() == "n":
        print("Thank you for playing!")
        time.sleep(2)
        break
    else:
        print("Starting again...")
        time.sleep(1)
